#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class Point {
private:
    double x_;
    double y_;
public:
    Point(double x, double y) : x_(x), y_(y) {}

    double getX() const {
        return x_;
    }

    double getY() const {
        return y_;
    }

    string toString() const {
        std::stringstream ss;
        ss << "(" << getX() << ", " << getY() << ")";
        return ss.str();
    }
};

class Rectangle {
private:
    Point top_left_;
    Point bot_left_;
    Point bot_right_;
    Point top_right_;

public:

    Rectangle(const Point &topLeft, int length, int width) :
            top_left_(topLeft),
            top_right_(Point(top_left_.getX() + width, top_left_.getY())),
            bot_left_(Point(top_left_.getX(), top_left_.getY() - length)),
            bot_right_(Point(top_left_.getX() + width, top_left_.getY() - length)) {}

    const Point &getTopLeft() const {
        return top_left_;
    }

    const Point &getBotRight() const {
        return bot_right_;
    }

    bool intersects(Rectangle &rect2) {
        /*
        Condition 1: If the left edge of this rect is to the right of rect2's right edge, then this
                     rectangle is to the right of rect2.
        Condition 2: Condition 1 but left and right are switched so this rectangle is to the left
                     of rect2.
        Condition 3: If the top edge of this rect is below rect2's bottom edge, then this rectangle
                     is below rect2
        Condition 4: Condition 3 but top and bottom switched so this rect is on top.

        If all conditions are not met then rects are intersecting.
        
        De Morgan's law: Not (Cond1 or Cond2 or Cond3 or Cond 4) is Not Cond1 and Not Cond2 and Not
                         Not Cond3 and Not Cond4
        */
        double r2LEdge = rect2.getTopLeft().getX(); // rect2 left edge.
        double r2TEdge = rect2.getTopLeft().getY(); // rect2 top edge.

        double r2REdge = rect2.getBotRight().getX(); // rect2 right edge.
        double r2BEdge = rect2.getBotRight().getY(); // rect2 bottom edge.


        return (top_left_.getX() < r2REdge && // !(cond1)
                bot_right_.getX() > r2LEdge && // !(cond2)
                top_left_.getY() < r2BEdge && // !(cond3)
                bot_right_.getY() > r2TEdge); // !(cond4)
    }

    string toString() {
        stringstream ss;
        ss << top_left_.toString();
        ss << ", " << bot_left_.toString();
        ss << ", " << bot_right_.toString();
        ss << ", " << top_right_.toString();
        return ss.str();
    }
};

class Assignment1 {
public:
    static void start() {
        cout << "Please input data for the first rectangle" << endl;
        Rectangle r1 = askForRectInput();
        cout << "Please input data for the second rectangle" << endl;
        Rectangle r2 = askForRectInput();

        cout << "\nRectangle 1 Points:" << endl;
        cout << r1.toString() << endl;
        cout << "\nRectangle 2 Points:" << endl;
        cout << r2.toString() << "\n" << endl;

        string intersectOut = collided(r1, r2) ? "The two rectangles intersect."
                                               : "The two rectangles does not intersect.";
        cout << intersectOut << endl;
    }

    static bool collided(Rectangle &r1, Rectangle &r2) {
        return r1.intersects(r2);
    }

    static Rectangle askForRectInput() {
        double x, y;
        int length, width;
        x = askForNumInput("Top left x-coordinate:");
        y = askForNumInput("Top left y-coordinate:");
        length = (int) askForNumInput("Length:");
        width = (int) askForNumInput("Width:");
        return *new Rectangle(Point(x, y), length, width);;
    }

    static double askForNumInput(char const *prompt) {
        cout << prompt;
        double choice;
        std::cin >> choice;
        //Number validation for input.
        while (!std::cin.good()) {
            std::cin.clear();
            std::cin.ignore(INT_MAX, '\n');
            std::cout << "That's not a number!" << endl;
            cout << prompt << endl;
            std::cin >> choice;
        }
        return choice;
    }
};

int main() {
    Assignment1::start();
}