#pragma once

#include "RawModel.h"
#include <string>

/* This class converts obj to RawModel*/
class OBJManager
{
public:
	OBJManager();
	~OBJManager();

	static RawModel* getRawModelFromObj(const std::string& p_filepath);

};

