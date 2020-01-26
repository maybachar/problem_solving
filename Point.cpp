#include "Point.h"

using namespace std;

/// Constructor
Point::Point(int x, int y) {
    this->xPos = x;
    this->yPos = y;
}

/// Destructor
Point::~Point() {}

/**
 * This function return the x value of this point.
 *
 * @return x value of this point.
 */
int Point:: getX() {
    return this->xPos;
}

/**
 * This function return the y value of this point.
 *
 * @return y value of this point.
 */
int Point::getY() {
    return yPos;
}

/**
 * This function get another point and check if it equals to this point
 * by Comparing their X and Y values and return true if they are equals and false
 * if not.
 *
 * @param point another point that we want to check if it equals to this point.
 * @return true if there equals or false if not.
 */
bool Point::equals(Point point) {
    return (this->xPos == point.getX() && this->yPos == point.getY());
}
