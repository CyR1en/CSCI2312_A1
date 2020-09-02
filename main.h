#ifndef ASSIGNMENT1_MAIN_H
#define ASSIGNMENT1_MAIN_H

#include <string>

/**
 * Class that represents a point on a Cartesian Plane.
 */
class Point {
private:
    double x_;
    double y_;
public:
    // Constructor
    Point(double x, double y);

    // Immutable accessor.
    double getX() const;

    // Immutable accessor.
    double getY() const;

    // toString.
    std::string toString() const;
};

//Class that represents a Rectangle.
class Rectangle {
private:
    Point top_left_;
    Point bot_left_;
    Point bot_right_;
    Point top_right_;
public:
    // Constructor
    Rectangle(const Point &topLeft, int length, int width);

    // const reference accessor.
    const Point &getTopLeft() const;

    // const reference accessor.
    const Point &getBotRight() const;

    // const reference accessor.
    bool intersects(Rectangle &rect2) const;

    // const reference accessor.
    std::string toString() const;
public:
};

#endif
