#include "shape.h"
#include <iostream>

using namespace std;

int main(){
	Point a(1,2);
	Point b;
	Point c = b;
	cout << a.x << ' ' << a.y << '\n';
	cout << b.x << ' ' << b.y << '\n';

	Shape* circle  = new Circle(a, 5);
	Shape* square  = new Square(c, 4);
	circle->print();
	square->print();

	cin.clear();
	cout << "Enter char to continue";
	char ch;
	cin >> ch;
}
