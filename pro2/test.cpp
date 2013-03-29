#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <iomanip>

#include "ArrayStack.h"
#include "ListStack.h"

void sizeTest(int cap, int iter)
{
	ListStack<int> l;
	//create stack of random vars
	for (int i = 0; i < cap; ++i){
		int r = rand();
		l.push(r);
	}
	//time size for iter times
	clock_t start = clock();
	for (int i = 0; i < iter; ++i)
		l.size();
	clock_t end = clock();
	//calculate andprint average
	double avg = double(end - start) / double(CLOCKS_PER_SEC) / iter;
	cout << "s " << cap << ' ' << iter << ' ' << setprecision (10) << avg << '\n';
}

void mySizeTest(int cap, int iter)
{
	ListStack<int> l;
	//create stack of random vars
	for (int i = 0; i < cap; ++i){
		int r = rand();
		l.push(r);
	}
	//time mySize for iter times
	clock_t start = clock();
	for (int i = 0; i < iter; ++i)
		l.mySize();
	clock_t end = clock();
	//calculate andprint average
	double avg = double(end - start) / double(CLOCKS_PER_SEC) / iter;
	cout << "mS " << cap << ' ' << iter << ' ' << setprecision (10) << avg << '\n';
}

void arrayPushTest(int init, int final, int iter)
{
	//time push for iter times
	clock_t start = clock();
	for (int i = 0; i < iter; ++i) {
		//create array based stack
		ArrayStack<int> a(init);
		//push elements in
		for (int j = 0; j < final; ++j) {
			int r = rand();
			a.pushDouble(r);
		}
	}
	clock_t end = clock();
	//calculate andprint average
	double avg = double(end - start) / double(CLOCKS_PER_SEC) / iter / final;
	cout << "aP " << init << ' ' << final << ' ' << iter << ' ' << setprecision (10) << avg << '\n';
}

void listPushTest(int cap, int iter)
{
	//time push for iter times
	clock_t start = clock();
	for (int i = 0; i < iter; ++i) {
		//create list based stack
		ListStack<int> l;
		//push elements in
		for (int j = 0; j < cap; ++j) {
			int r = rand();
			l.push(r);
		}
	}
	clock_t end = clock();
	//calculate and print average
	double avg = double(end - start) / double(CLOCKS_PER_SEC) / iter / cap;
	cout << "lP " << cap << ' ' << iter << ' ' << setprecision (10) << avg << '\n';
}

int main()
{
	//size test; size: 2^1 to 2^20; iterations: 2^30
	for (int i = 1; i < 21; ++i)
		sizeTest(pow(2,i),pow(2,25));
	//mySize test; size: 2^1 to 2^20; iterations: 10*2^20 to 10, inversly propotional to size
	for (int i = 1; i < 21; ++i)
		mySizeTest(pow(2,i),(10*pow(2,21-i)));
	//list based push test; size: 2^1 to 2^20; iterations: 10*2^20 to 10, inversly propotional to size
	for (int i = 1; i < 21; ++i) 
		listPushTest(pow(2,i),(10*pow(2,21-i)));
	//array based push test; iterations: 10*2^20 to 10, inversly oproportiona to size
	//best case scenario: max size = 2^k*capacity
	for (int i = 1; i < 21; ++i) {
		//first case: init size is 32
		arrayPushTest(32,pow(2,i),10*pow(2,20-i));
		//first case: init size is 128
		arrayPushTest(128,pow(2,i),10*pow(2,20-i));
	}
	//worst case scenario: max size = 2^k*capacity + 1
	for (int i = 1; i < 21; ++i) {
		//first case: init size is 32
		arrayPushTest(32,pow(2,i)+1,10*pow(2,20-i));
		//first case: init size is 128
		arrayPushTest(128,pow(2,i)+1,10*pow(2,20-i));
	}
}
