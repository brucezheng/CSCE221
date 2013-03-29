#include <iostream>

using namespace std;

class Point{
private:
	int x;
	int y;
public:
	Point() : x(0), y(0) {};
	Point(int xx, int yy) : x(xx), y(yy) {};
	void print() { cout << '[' <<  x << ' ' << y << ']'; }
};

int main() {
	Point p1[10];
	Point *p2 = new Point[10];
	
	for(int i = 0; i < 10; ++i){
		Point a(i,i);
		Point b(i+1,i+1);
		p1[i] = a;
		p2[i] = b;
	}
	
	for(int i = 0; i < 10; ++i){
		p1[i].print();
	}
	cout << '\n';
	
	for(int i = 0; i < 10; ++i){
		(p2 + i)->print();
	}
	cout << '\n';
}
