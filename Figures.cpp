#include <cmath>
#include <iostream>

using namespace std;

class Point {
public:
  virtual void draw() const = 0;
  virtual void remove() const = 0;
  virtual void move(double dx, double dy) = 0;
  virtual void rotate() const = 0;
  virtual ~Point() { cout << "Point destructor called." << endl; }
};

class Shape : public Point {
protected:
  double x, y;

public:
  Shape(double x, double y) : x(x), y(y) {}

  void move(double dx, double dy) override {
    x += dx;
    y += dy;
    cout << "Shape moved to (" << x << ", " << y << ")" << endl;
  }

  virtual ~Shape() { cout << "Shape destructor called." << endl; }
};

class Line : public Shape {

protected:
  double length;

public:
  Line(double x, double y, double length) : Shape(x, y), length(length) {}

  void draw() const override {
    cout << "Line from (" << x << ", " << y << ") with length " << length
         << endl;
  }

  void remove() const override { cout << "Line removed." << endl; }

  void rotate() const override { cout << "Line rotated." << endl; }

  ~Line() { cout << "Line destructor called." << endl; }
};

class Parallelogram : public Shape {
protected:
  double sideA, sideB;
  double angle;

public:
  Parallelogram(double x, double y, double a, double b, double angle)
      : Shape(x, y), sideA(a), sideB(b), angle(angle) {}

  void draw() const override {
    cout << "Parallelogram with side A: " << sideA << ", side B: " << sideB
         << " and angle: " << angle << " degrees at (" << x << ", " << y << ")"
         << endl;
  }

  void remove() const override { cout << "Parallelogram removed." << endl; }

  void rotate() const override { cout << "Parallelogram rotated." << endl; }

  ~Parallelogram() { cout << "Parallelogram destructor called." << endl; }
};

class Rectangle : public Parallelogram {
public:
  Rectangle(double x, double y, double width, double height)
      : Parallelogram(x, y, width, height, 90.0) {}

  void draw() const override {
    cout << "Rectangle with width: " << sideA << ", height: " << sideB
         << " at (" << x << ", " << y << ")" << endl;
  }

  void remove() const override { cout << "Rectangle removed." << endl; }

  void rotate() const override { cout << "Rectangle rotated." << endl; }

  ~Rectangle() { cout << "Rectangle destructor called." << endl; }
};

class Rhombus : public Parallelogram {
public:
  Rhombus(double x, double y, double side, double angle)
      : Parallelogram(x, y, side, side, angle) {}

  void draw() const override {
    cout << "Rhombus with sides: " << sideA << " at (" << x << ", " << y << ")"
         << " and angle: " << angle << " degrees" << endl;
  }

  void remove() const override { cout << "Rhombus removed." << endl; }

  void rotate() const override { cout << "Rhombus rotated." << endl; }

  ~Rhombus() { cout << "Rhombus destructor called." << endl; }
};

class Square : public Rectangle {
public:
  Square(double x, double y, double side) : Rectangle(x, y, side, side) {}

  void draw() const override {
    cout << "Square with side: " << sideA << " at (" << x << ", " << y << ")"
         << endl;
  }

  void remove() const override { cout << "Square removed." << endl; }

  void rotate() const override { cout << "Square rotated." << endl; }

  ~Square() { cout << "Square destructor called." << endl; }
};

int main() {
  Line line(0, 0, 10);
  line.draw();
  line.move(5, 5);
  line.rotate();
  line.remove();

  Rectangle rect(0, 0, 10, 5);
  rect.draw();
  rect.move(5, 5);
  rect.rotate();
  rect.remove();

  Rhombus rhombus(0, 0, 10, 60);
  rhombus.draw();
  rhombus.move(5, 5);
  rhombus.rotate();

  Square square(0, 0, 10);
  square.draw();
  square.move(5, 5);
  square.rotate();
  square.remove();

  // Создаем массив указателей на Point и инициализируем их адресами объектов
  Point *points[3];
  points[0] = &line;
  points[1] = &rect;
  points[2] = &square;

  // Демонстрируем позднее связывание, вызывая методы через указатели на базовый класс
  for (int i = 0; i < 3; i++) {
    points[i]->draw();
    points[i]->move(1, 1);
    points[i]->rotate();
    points[i]->remove();
    cout << endl;
  }

  return 0;
}