#include <iostream>

using namespace std;

struct Point{
	int x;
	int y;
	Point() : x(0), y(0) {};
	Point(int xx, int yy) : x(xx), y(yy) {};
	Point& operator=(const Point& p){
		x = p.x;
		y = p.y;
	}
};

class Shape{
protected:
	Point center;
public:
	Shape(Point p) : center(p) {};
	virtual void print() = 0; 
};

class Circle : public Shape{
private:
	int radius;
public:
	Circle(Point p, int r) : Shape(p), radius(r) {};
	void print() { cout << "Circle: " << center.x << ' ' << center.y << ' ' << radius << '\n'; }
};

class Square : public Shape{
private:
	int side;
public:
	Square(Point p, int s) : Shape(p), side(s) {};
	void print() { cout << "Square: " << center.x << ' ' << center.y << ' ' << side << '\n'; }
};
