#ifndef STORAGE_H
#define STORAGE_H

#include "Shape.h"

#include "ShapeListModel.h"


struct Storage
{
	Storage();
	~Storage();
	
	vector_t shapes;
	ShapeListModel model;
};

#endif // STORAGE_H
