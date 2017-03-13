#include "Resource.h"

Resource::~Resource() 
{
	//printf("DEBUG: resource freed\n");
}

std::string Resource::getResourceFilePath()
{
	return this->path;
}

void Resource::setResourceFilePath(std::string filepath)
{
	this->path = filepath;
}

std::string Resource::getResourceID()
{
	return this->ID;
}

void Resource::setResourceID(std::string id)
{
	this->ID = id;
}

std::string Resource::getResourceType()
{
	return this->type;
}

void Resource::setResourceType(std::string type)
{
	this->type = type;
}