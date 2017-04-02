#pragma once
#include <fstream>
#include "Level.h"
class File
{
public:
	File();
	virtual ~File();
	void save(Level &level);
	void load(Level &level);
	std::fstream file;
};

