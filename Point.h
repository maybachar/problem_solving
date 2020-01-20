#ifndef PROBLEM_SOLVING_POINT_H
#define PROBLEM_SOLVING_POINT_H

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
