#include <iostream>
#include <string>
#include <sstream>
#include "main.h"

using namespace std;

/**
  * 2 param constructor for this class.
  *
  * @param x x-coordinate value for the point.
  * @param y y-coordinate value for the point.
  */
Point::Point(double x, double y) : x_(x), y_(y) {}

/**
 * Immutable accessor for the x-coordinate of the point.
 *
 * @return x-coordinate of the point.
 */
double Point::getX() const { return x_; }

/**
* Immutable accessor for the y-coordinate of the point.
*
* @return y-coordinate of the point.
*/
double Point::getY() const { return y_; }

/**
 * Immutable string representation of the point for easy printing.
 *
 * @return string representation of the point.
 */
string Point::toString() const {
    std::stringstream ss;
    ss << "(" << getX() << ", " << getY() << ")";
    return ss.str();
}

/**
 * Rectangle Constructor.
 *
 * This constructor initializes the class using initializer list because the class Point does
 * not have a default constructor.
 *
 * @param topLeft Top-left point of the rectangle.
 * @param length length of the rectangle.
 * @param width width of the rectangle.
 */
Rectangle::Rectangle(const Point &topLeft, int length, int width) :
        top_left_(topLeft),
        top_right_(Point(top_left_.getX() + width, top_left_.getY())),
        bot_left_(Point(top_left_.getX(), top_left_.getY() - length)),
        bot_right_(Point(top_left_.getX() + width, top_left_.getY() - length)) {}


/**
 * const reference accessor for the top-left point of the rectangle for immutability.
 * (Have a different function handle mutability of points.)
 *
 * @return top-left point of the rectangle.
 */

const Point &Rectangle::getTopLeft() const {
    return top_left_;
}

/**
 * const reference accessor for the bottom-right point of the rectangle for immutability.
 * (Have a different function handle mutability of points.)
 *
 * @return bottom-right point of the rectangle.
 */

const Point &Rectangle::getBotRight() const {
    return bot_right_;
}

/**
 * Function that checks if this rectangle intersects with another rectangle.
 *
 * Condition 1: If the left edge of this rect is to the right of rect2's right edge, then this
 *              rectangle is to the right of rect2.
 * Condition 2: Condition 1 but left and right are switched so this rectangle is to the left
 *              of rect2.
 * Condition 3: If the top edge of this rect is below rect2's bottom edge, then this rectangle
 *              is below rect2
 * Condition 4: Condition 3 but top and bottom switched so this rect is on top.
 *
 * If all conditions are not met then rects are intersecting.
 *
 * De Morgan's law: Not (Cond1 or Cond2 or Cond3 or Cond 4) is Not Cond1 and Not Cond2 and Not
 *                  Not Cond3 and Not Cond4
 *
 * @param rect2 Another rectangle to check for collision.
 * @return true if this rectangle intersects param rect2, false if not.
 */
bool Rectangle::intersects(Rectangle &rect2) const {
    double r2LEdge = rect2.getTopLeft().getX(); // rect2 left edge.
    double r2TEdge = rect2.getTopLeft().getY(); // rect2 top edge.

    double r2REdge = rect2.getBotRight().getX(); // rect2 right edge.
    double r2BEdge = rect2.getBotRight().getY(); // rect2 bottom edge.


    return (top_left_.getX() < r2REdge && // !(cond1)
            bot_right_.getX() > r2LEdge && // !(cond2)
            top_left_.getY() > r2BEdge && // !(cond3)
            bot_right_.getY() < r2TEdge); // !(cond4)
}

/**
 * Immutable string representation of this rectangle for easier printing.
 *
 * This returns all the corner points of the rectangle and ordered according to the
 * instructions on Canvas--(top-left), (bot-left), (bot-right), (top-right).
 *
 * @return string representation of this rectangle.
 */
string Rectangle::toString() const {
    stringstream ss;
    ss << top_left_.toString();
    ss << ", " << bot_left_.toString();
    ss << ", " << bot_right_.toString();
    ss << ", " << top_right_.toString();
    return ss.str();
}


class Assignment1 {
public:
    /**
     * Actual procedure for the assignment is in this function.
     *
     * This is a single shot execution of assignment 1. The instruction from Canvas was
     * carefully followed and used the same value to get the same output.
     */
    static void start() {
        Rectangle r1 = askForRectInput("Please input data for the first rectangle \n");
        Rectangle r2 = askForRectInput("Please input data for the second rectangle \n");

        cout << "\nRectangle 1 Points:" << endl;
        cout << r1.toString() << endl;
        cout << "\nRectangle 2 Points:" << endl;
        cout << r2.toString() << "\n" << endl;

        string intersectOut = rectangles_intersect(r1, r2) ?
                              "The two rectangles intersect." : "The two rectangles does not intersect.";
        cout << intersectOut << endl;
    }

    /**
     * Checks if two rectangles intersect.
     *
     * This doesn't have any implementation and just uses the intersects function inside of
     * the Rectangle class.
     *
     * @param r1 First Rectangle
     * @param r2 Second Rectangle
     * @return  true if they intersect, false if not.
     */
    static bool rectangles_intersect(Rectangle &r1, Rectangle &r2) {
        return r1.intersects(r2);
    }

    /**
     * Function that takes care of all the prompt for inputting rectangle
     * data.
     *
     * Made it to a separate function to get rid of code duplication when asking for data
     * of multiple rectangles.
     *
     * @return Returns an instance of Rectangle that used input data.
     */
    static Rectangle askForRectInput(const char *prompt) {
        cout << prompt;
        double x, y;
        int length, width;
        x = askForNumInput("Top left x-coordinate:");
        y = askForNumInput("Top left y-coordinate:");
        length = (int) askForNumInput("Length:");
        width = (int) askForNumInput("Width:");
        return *new Rectangle(Point(x, y), length, width);;
    }

    /**
     * Function that prompts the user for a number.
     *
     * This function will not exit until the user enters a valid number. This function
     * returns a double to "cover" all of the possible numbers.
     *
     * If an integer is needed, just cast it to an int--with the consequence of doing so in mind.
     *
     * @param prompt Prompt to be printed out before opening up cin.
     * @return return the inputted number.
     */
    static double askForNumInput(const char *prompt) {
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

/*
 * Main method for the class.
 *
 * statically call start() from Assignment1 class.
 */
int main() {
    Assignment1::start();
}