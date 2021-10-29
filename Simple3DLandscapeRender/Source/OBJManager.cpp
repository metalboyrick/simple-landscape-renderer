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

int checkVertexInArray(std::vector<objl::Vertex>& p_vertexVector, objl::Vertex& p_targetVertex)
{
	int vectorSize = p_vertexVector.size();
	for (int i = 0; i < vectorSize; i++)
	{
		if (p_vertexVector.at(i).Position.X == p_targetVertex.Position.X && 
			p_vertexVector.at(i).Position.Y == p_targetVertex.Position.Y &&
			p_vertexVector.at(i).Position.Z == p_targetVertex.Position.Z)
		{
			return i;
		}
	}

	return -1;
}

RawModel* OBJManager::getRawModelFromObj(const std::string& p_filepath)
{
    RawModel* newRawModel = new RawModel();
    objl::Loader loader;
    loader.LoadFile(p_filepath);

	// get the vertices and color and texture coordinates
	std::vector<float> vertexArray;
	std::vector<objl::Vertex> recordedVertices;
	
	std::vector<unsigned int> indices;

	unsigned int counter = 0;

	for (auto& mesh : loader.LoadedMeshes)
	{
		for (int i = 0; i < mesh.Vertices.size(); i++)
		{
			int vertexIndex = checkVertexInArray(recordedVertices, mesh.Vertices.at(i));
			if (vertexIndex != -1)
			{
				indices.push_back(vertexIndex);
				continue;
			}
			
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

			recordedVertices.push_back(mesh.Vertices.at(i));

			indices.push_back(static_cast<unsigned int>(counter));
			counter++;
		}
	}
	
	newRawModel->addVertexAttr(vertexArray.data(), vertexArray.size());
	newRawModel->bindIndexBuffer(indices.data(), indices.size());

    return  newRawModel;
}
