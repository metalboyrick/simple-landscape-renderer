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

	// clean up the index to remove duplicates

	
	newRawModel->addVertexAttr(vertexArray.data(), vertexArray.size());
	newRawModel->bindIndexBuffer(indices.data(), indices.size());

    return  newRawModel;
}
