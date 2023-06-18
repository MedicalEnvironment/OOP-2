#include <iostream>
#include <cmath>

enum class Color {
    Red = 0,
    Blue = 1,
    Green = 2
};

class Shape {
protected:
    double centerX;
    double centerY;
    Color color;

public:
    Shape(double x, double y, Color c) : centerX(x), centerY(y), color(c) {}

    virtual double getArea() const = 0;
    virtual std::string getShapeType() const = 0;
    virtual std::string getDescription() const {
        return getShapeType() + ": Color = " + getColorName(color) + ", Area = " + std::to_string(getArea());
    }

    virtual double getWidth() const {
        return 0.0; // Placeholder for base class
    }

    double getHeight() const {
        return 0.0; // Placeholder for base class
    }

    void displayCircumscribingRectangle() const {
        double width = getWidth();
        double height = getHeight();
        double left = centerX - (width / 2.0);
        double top = centerY - (height / 2.0);
        double right = left + width;
        double bottom = top + height;

        std::cout << "Circumscribing Rectangle: Left = " << left << ", Top = " << top << ", Right = " << right << ", Bottom = " << bottom << std::endl;
    }

    std::string getColorName(Color c) const {
        switch (c) {
            case Color::Red:
                return "Red";
            case Color::Blue:
                return "Blue";
            case Color::Green:
                return "Green";
            default:
                return "None";
        }
    }
};

class Circle : public Shape {
private:
    double radius;

public:
    Circle(double x, double y, Color c, double r) : Shape(x, y, c), radius(r) {}

    double getArea() const override {
        return atan(1) * 4 * radius * radius;
    }

    std::string getShapeType() const override {
        return "Circle";
    }
};

class Square : public Shape {
private:
    double edgeLength;

public:
    Square(double x, double y, Color c, double length) : Shape(x, y, c), edgeLength(length) {}

    double getArea() const override {
        return edgeLength * edgeLength;
    }

    std::string getShapeType() const override {
        return "Square";
    }
};

class Rectangle : public Square {
private:
    double height;

public:
    Rectangle(double x, double y, Color c, double width, double h) : Square(x, y, c, width), height(h) {}

    double getArea() const override {
        return getWidth() * height;
    }

    std::string getShapeType() const override {
        return "Rectangle";
    }

    double getHeight() const override {
        return height;
    }
};

int main() {
    double centerX, centerY, dimension1, dimension2;
    Color color;

    std::cout << "Enter shape type (circle, square, rectangle): ";
    std::string shapeType;
    std::cin >> shapeType;

    std::cout << "Enter center coordinates (x y): ";
    std::cin >> centerX >> centerY;

    std::cout << "Enter color (0 = Red, 1 = Blue, 2 = Green): ";
    int colorInput;
    std::cin >> colorInput;
    color = static_cast<Color>(colorInput);

    Shape* shape = nullptr;
    if (shapeType == "circle") {
        std::cout << "Enter radius: ";
        std::cin >> dimension1;
        shape = new Circle(centerX, centerY, color, dimension1);
    } else if (shapeType == "square") {
        std::cout << "Enter edge length: ";
        std::cin >> dimension1;
        shape = new Square(centerX, centerY, color, dimension1);
    } else if (shapeType == "rectangle") {
        std::cout << "Enter width and height: ";
        std::cin >> dimension1 >> dimension2;
        shape = new Rectangle(centerX, centerY, color, dimension1, dimension2);
    } else {
        std::cout << "Invalid shape type!" << std::endl;
        return 0;
    }

    if (shape) {
        std::cout << shape->getDescription() << std::endl;
        shape->displayCircumscribingRectangle();
        delete shape;
    }

    return 0;
}
