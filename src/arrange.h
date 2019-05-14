#ifndef SERIALIZER_H
#define SERIALIZER_H

#include "Storage.h"
#include "Ellipse.h"
#include "Line.h"
#include "Polygon.h"
#include "PolyLine.h"
#include "Rectangle.h"
#include "Text.h"


#include <ostream>

std::ostream& operator<<(std::ostream& out, const vector_t &shapes);

#endif // SERIALIZER_H
