#pragma once

#include "Model.h"
#include <string>

/* This class converts obj to Model*/
class OBJManager
{
public:
	OBJManager();
	~OBJManager();

	static Model* getModelFromObj(const std::string& p_filepath);

};

