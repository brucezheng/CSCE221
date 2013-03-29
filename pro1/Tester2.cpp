//Bruce Zheng
//CSCE 221H Programming Assignment 1
//cpp file for testing the avg run speed of new functions in modified ArrayStack

#include <iostream>
#include <iomanip>
#include <fstream>
#include <ctime>
#include <cmath>

#include "RuntimeException.h"
#include "ArrayStack.h"

using namespace std;

//Determines avg time of mysize functions, writes results to screen and text doc
void mySizeTest(int cap, int iter, ofstream& of)
{
	ArrayStack<int> a;
	
	for(int i = 0; i < cap; ++i){
		a.exp_push(0);
	}
	
	clock_t start = clock();
	for(int i = 0; i < iter; ++i){
		a.mySize();
	}
	clock_t end = clock();
	
	double avg = double(end - start) / double(CLOCKS_PER_SEC) / iter;
	of << "mS " << cap << ' ' << iter << ' ' << setprecision (10) << avg << '\n';
	cout << "mS " << cap << ' ' << iter << ' ' << setprecision (10) << avg << '\n';

}

//Determines avg time of size functions, writes results to screen and text doc
void sizeTest(int cap, int iter, ofstream& of)
{
	ArrayStack<int> a;
	
	for(int i = 0; i < cap; ++i){
		a.exp_push(0);
	}
	
	clock_t start = clock();
	for(int i = 0; i < iter; ++i){
		a.size();
	}
	clock_t end = clock();
	
	double avg = double(end - start) / double(CLOCKS_PER_SEC) / iter;
	of << "S " << cap << ' ' << iter << ' ' << setprecision (10) << avg << '\n';
	cout << "S " << cap << ' ' << iter << ' ' << setprecision (10) << avg << '\n';

}

//Determines avg time doubling resizing push function
void expPushTest(int init, int final, int iter, ofstream& of)
{
	clock_t start = clock();
	for(int i = 0; i < iter; ++i) {
	ArrayStack<int> a(init);
		for(int j = 0; j < final; ++j) {
			a.exp_push(0);
		}
	}
	clock_t end = clock();

	double avg = double(end - start) / double(CLOCKS_PER_SEC) / iter;
	cout << "eP " << init << ' ' << final << ' ' << iter << ' ' << setprecision (10) << avg << '\n';
	of  << "eP " << init << ' ' << final << ' ' << iter << ' ' << setprecision (10) << avg << '\n';
}

//Determines avg time of linearly resizing push function
void linPushTest(int init, int final, int iter, ofstream& of)
{
	clock_t start = clock();
	for(int i = 0; i < iter; ++i) {
	ArrayStack<int> a(init);
		for(int j = 0; j < final; ++j) {
			a.lin_push(0);
		}
	}
	clock_t end = clock();

	double avg = double(end - start) / double(CLOCKS_PER_SEC) / iter;
	cout << "lP " << init << ' ' << final << ' ' << iter << ' ' << setprecision (10) << avg << '\n';
	of  << "lP " << init << ' ' << final << ' ' << iter << ' ' << setprecision (10) << avg << '\n';
}

//Runs sizeTest and pushTest for different inital conditions
int main()
{
	ofstream of("data.txt"); 
	
	for(int i = 1; i <= 20; ++i){
		int cap = pow(2,i);
		int iter = 10 * pow(2,20-i);
		mySizeTest(cap,iter,of);
	}
	cout << '\n';
	of << '\n';
	for(int i = 1; i <= 20; ++i){
		int cap = pow(2,i);
		int iter = 10 * pow(2,22);
		sizeTest(cap,iter,of);
	}
	cout << '\n';
	of << '\n';
	for(int i = 1; i <= 20; ++i){
		int cap = pow(2,i);
		int iter = 10*pow(2,20-i);
		expPushTest(10,cap,iter,of);
		expPushTest(20,cap,iter,of);
		expPushTest(40,cap,iter,of);
	}
	cout << '\n';
	of << '\n';
	for(int i = 1; i <= 17; ++i){
		int cap = pow(2,i);
		int iter;
		if(10-i > 0)
			iter = 10*pow(4,10-i);
		else
			iter = 10;
		linPushTest(10,cap,iter,of);
		linPushTest(20,cap,iter,of);
		linPushTest(40,cap,iter,of);
	}	
}
