#include "OBJManager.h"

#include <OBJ_Loader/OBJ_Loader.h>
#include <pystring/pystring.h>
#include <fstream>
#include <vector>
#include <regex>
#include <string>
#include <algorithm>

OBJManager::OBJManager()
{
}

OBJManager::~OBJManager()
{
}

RawModel* OBJManager::getRawModelFromObj(const std::string& p_filepath)
{
    RawModel* newRawModel = new RawModel();
    objl::Loader loader;
    loader.LoadFile(p_filepath);

	// get the vertices and color and texture coordinates
	std::vector<float> vertexArray;
	std::vector<std::string> recordedData;
	
	std::vector<unsigned int> indices;

	unsigned int counter = 0;

	for (auto& mesh : loader.LoadedMeshes)
	{
		for (int i = 0; i < mesh.Vertices.size(); i++)
		{
			// position
			vertexArray.push_back(mesh.Vertices.at(i).Position.X);
			vertexArray.push_back(mesh.Vertices.at(i).Position.Y);
			vertexArray.push_back(mesh.Vertices.at(i).Position.Z);

			// color
			vertexArray.push_back(mesh.MeshMaterial.Kd.X);
			vertexArray.push_back(mesh.MeshMaterial.Kd.Y);
			vertexArray.push_back(mesh.MeshMaterial.Kd.Z);

			// texture coordinates
			vertexArray.push_back(mesh.Vertices.at(i).TextureCoordinate.X);
			vertexArray.push_back(mesh.Vertices.at(i).TextureCoordinate.Y);

			indices.push_back(static_cast<unsigned int>(counter));

			counter++;
		}
	}
	
	
	// get the index array
	
	//std::vector<std::string> appendedEntries;
	//std::fstream inFile;
	//inFile.open(p_filepath, std::ios::out | std::ios::in);
	//std::string line;
	//unsigned int indexCounter = 0;
	//
	//while (getline(inFile, line))
	//{
	//	// only want the indices
	//	if (line[0] != 'f')
	//		continue;
	//	
	//	std::vector<std::string> indexCollections;
	//	pystring::split(line, indexCollections);
	//	
	//	for (int i = 1; i < 4; i++)
	//	{
	//		unsigned int index = -1;
	//		
	//		// find index
	//		auto it = std::find(appendedEntries.begin(), appendedEntries.end(), indexCollections.at(i));

	//		// If element was found
	//		if (it != appendedEntries.end())
	//		{
	//			index = it - appendedEntries.begin();
	//			indices.push_back(index);
	//			continue;
	//		}
	//		else {
	//			index = -1;
	//			appendedEntries.push_back(indexCollections.at(i));
	//			indices.push_back(indexCounter);
	//			indexCounter += 1;
	//		}
	//		
	//		//std::vector<std::string> triangleIndices;
	//		//pystring::split(indexCollections.at(i), triangleIndices, "/");
	//		//
	//		//for (int j = 0; j < 3; j++) {
	//		//	unsigned long index = std::stoul(triangleIndices[j]);
	//		//	indices.push_back(static_cast<unsigned int>(index - 1));
	//		//}
	//	}
	//	
	//}

	
	newRawModel->addVertexAttr(vertexArray.data(), vertexArray.size());
	newRawModel->bindIndexBuffer(indices.data(), indices.size());

    return  newRawModel;
}
