#include "Sort.h"

bool compareID(Shape* left, Shape* right) {
    return ((*left).getID() < (*right).getID());
}

bool compareArea(Shape* left, Shape* right) {
    return ((*left).getArea() < (*right).getArea());
}

bool comparePerimeter(Shape* left, Shape* right) {
    return ((*left).getPerimeter() < (*right).getPerimeter());
}

bool validArea(Shape* shape) {
    return ((*shape).getArea() >= 0);
}

bool validPerimeter(Shape* shape) {
    return ((*shape).getPerimeter() >= 0);
}

bool validID(Shape* /*shape*/) {
    return true;  // No value for ID is considered invalid
}

