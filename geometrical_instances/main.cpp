#include <iostream>
#include <cmath>

enum Color { None, Red, Blue, Green };

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
        return getShapeType() + ": Color=" + std::to_string(color) + ", Area=" + std::to_string(getArea());
    }

    double getWidth() const {
        return 0.0; // Placeholder for base class
    }

    double getHeight() const {
        return 0.0; // Placeholder for base class
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

    double getWidth() const {
        return radius * 2;
    }

    double getHeight() const {
        return radius * 2;
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

    double getWidth() const {
        return edgeLength;
    }

    double getHeight() const {
        return edgeLength;
    }
};

class EquilateralTriangle : public Shape {
private:
    double sideLength;

public:
    EquilateralTriangle(double x, double y, Color c, double length) : Shape(x, y, c), sideLength(length) {}

    double getArea() const override {
        return sideLength * sideLength * std::sqrt(3) / 4;
    }

    std::string getShapeType() const override {
        return "Equilateral Triangle";
    }

    double getWidth() const {
        return sideLength;
    }

    double getHeight() const {
        return sideLength * std::sqrt(3) / 2;
    }
};

class Rectangle : public Shape {
private:
    double width;
    double height;

public:
    Rectangle(double x, double y, Color c, double w, double h) : Shape(x, y, c), width(w), height(h) {}

    double getArea() const override {
        return width * height;
    }

    std::string getShapeType() const override {
        return "Rectangle";
    }

    double getWidth() const {
        return width;
    }

    double getHeight() const {
        return height;
    }
};

int main() {
    double centerX, centerY, dimension1, dimension2;
    Color color;

    std::cout << "Enter shape type (circle, square, triangle, rectangle): ";
    std::string shapeType;
    std::cin >> shapeType;

    std::cout << "Enter center coordinates (x y): ";
    std::cin >> centerX >> centerY;

    std::cout << "Enter color (0 = None, 1 = Red, 2 = Blue, 3 = Green): ";
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
    } else if (shapeType == "triangle") {
        std::cout << "Enter side length: ";
        std::cin >> dimension1;
        shape = new EquilateralTriangle(centerX, centerY, color, dimension1);
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
        delete shape;
    }

    return 0;
}
