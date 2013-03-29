#include <iostream>
#include <fstream>
#include <ctime>

#include "RuntimeException.h"
#include "ArrayStack.h"

using namespace std;

void sizeTest(int cap, int iter){ //Compares the original and modified size functions
	ofstream of ("data.txt", fstream::app);
	ArrayStack<int> a(cap);
	clock_t start = clock();
	for(int i = 0; i < iter; ++i){
		a.size();
	}
	clock_t mid = clock();
	for(int i = 0; i < iter; ++i){
		a.mySize();
	}
	clock_t end = clock();
	int t1 = mid - start;
	int t2 = end - mid;
	double a1 = t1 / iter;
	double a2 = t2 / iter;
	of << "S " << cap << ' ' << iter << ' ' << a1 << ' ' << a2 << '\n';
	cout << "S " << cap << ' ' << iter << ' ' << a1 << ' ' << a2 << '\n';
}

void pushTest(int init, int final, int iter){ //Compares time of the two new push functions
	ofstream of ("data.txt", fstream::app);
	ArrayStack<int> l(init);
	ArrayStack<int> e(init);
	clock_t start = clock();
	for(int i = 0; i < iter; ++i){
		for(int j = 0; j < final; ++j)
			l.lin_push(0);
	}
	clock_t mid = clock();
	for(int i = 0; i < iter; ++i){	
		for(int j = 0; j < final; ++j)
			e.exp_push(0);
	}
	clock_t end = clock();
	int t1 = mid - start;
	int t2 = end - mid;
	double a1 = t1 / iter;
	double a2 = t2 / iter;
	of << "S " << init << ' ' << final << ' ' << iter << ' ' << a1 << ' ' << a2 << '\n';
	cout << "P " << init << ' ' << final << ' ' << iter << ' ' << a1 << ' ' << a2 << '\n';
} 

int main(){ //User interface for running tests
	bool finished = false;
	while(!finished){ //Outer loop determines which test to run; returns to menu until q is pressed
		cout << "Which test are you running?\n" << "(A) size vs mysize\n" 
	   	     << "(B) lin_push vs exp_push\n" << "(Q) quit\n" << ':';
		char choice;
		cin >> choice;
		if(choice == 'A' | choice == 'a'){ 
			bool loopfin = false;
			cout << "Size Test (Q to stop testing)\n"; 
			while(!loopfin){ //Takes input and runs sizetest until q is pressed
				cout <<  "Capacity? 2^";
				int cap;
				char c;
				c = cin.get();
				if(isspace(c)){ //Prevents issues with detecting enter as a valid char
					c = cin.get();
				}
				if(c == 'Q' | c == 'q'){ //Gets out of local loop
					loopfin = true;
				}
				else{	
					cin.unget();		
					cin >> cap;
					cout << "Iter? ";
					int iter;
					cin >> iter;
					sizeTest(2^cap,iter);
				}
			}
		}
		if(choice == 'B' | choice == 'b'){
			bool loopfin = false;
			cout << "Push Test (Q to stop testing) \n";
			while(!loopfin){ //Takes input and runs pushtest until q is pressed
				cout << "Init cap? ";
				int ini;
				char c;
				c = cin.get();
				if(isspace(c)){
					c = cin.get();
				}
				if(c == 'Q' | c == 'q'){
					loopfin = true;
				}
				else{
					cin.unget();
					cin >> ini;
					cout << "Final cap? 2^";
					int fin;
					cin >> fin;
					cout << "Iter? ";
					int iter;
					cin >> iter;
					pushTest(ini,2^fin,iter);
				}
			}				
		}
		if(choice == 'Q' | choice == 'q'){ //Quits out of outer menu loop
			cout << "Quitting...\n";
			finished = true;
		}
	}
}
