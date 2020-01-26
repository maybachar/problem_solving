#ifndef PROBLEM_SOLVING_POINT_H
#define PROBLEM_SOLVING_POINT_H

using namespace std;

/**
 * Point Class
 *
 * This class representing a point which hold x and y value-
 * the point's location. This class knows to get the x and y values
 * and compare if a given point is equals to this point.
 */
class Point {
    int xPos;
    int yPos;
public:
    Point(int x, int y);
    ~Point();
    int getX();
    int getY();
    bool equals(Point point);
};

#endif //PROBLEM_SOLVING_POINT_H
