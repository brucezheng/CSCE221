//seq_type
//0 = Min-Max
//1 = Max-Min
//2 = Random
//3 = Nearly Min-Max
//4 = Nearly Max-Min

//test_type
//0 = HeapSort
//1 = InsertionSort
//2 = SelectionSort
//3 = MergeSort
//4 = QuickSortLast
//5 = QuickSortMedian
//6 = QuickSortRandom
//7 = RadixSort

#include "Sort.h"
#include "Comparator.h"

#include <iostream>
#include <ctime>
#include <cmath>
#include <iomanip>

using namespace std;

// generate a sequence of some type; only data from 2,3,4 was used in report
template<typename Seq>
void generateSequence(int n, int seq_type, Seq& S)
{
	if (seq_type == 0) {
		for (int i = 0; i < n; ++i) {
			S.insertLast(i);
		}
	}
	else if (seq_type == 1) {
		for (int i = 0; i < n; ++i) {
			S.insertLast(n-i);
		}
	}
	else if (seq_type == 2) {
		srand (time(NULL));
		for (int i = 0; i < n; ++i) {
			S.insertLast(rand()%n);
		}
	}
	else if (seq_type == 3) {
		srand (time(NULL));
		for (int i = 0; i < n; ++i) {
			S.insertLast(abs(i+5-(rand()%10)));
		}
	}
	else if (seq_type == 4) {
		srand (time(NULL));
		for (int i = 0; i < n; ++i) {
			S.insertLast(abs(n-i+5-(rand()%10)));
		}
	}
	else 
		cerr << "ERROR: Unknown seq_type" << endl;
}

// returns avg time of sort for size n
template<template<typename, typename> class Sort, template<typename> class Seq >
void testSort(int n, int seq_type, int iter) 
{
	Sort<int,Comp> sorter;
	Seq<int> copied;
	generateSequence(n,seq_type,copied);
	clock_t start = clock();
	for (int i = 0; i < iter; ++i) {
		Seq<int> S(copied);
		sorter.sort(S);
	}
	clock_t end = clock();
	double avg = double(end - start) / double(CLOCKS_PER_SEC) / double(iter);
	cout << avg << endl;
}

int main(int argc, char* argv[]) 
{
	// argv values
	int sort_type = atoi(argv[1]);
	int seq_type = atoi(argv[2]);
	int power = atoi(argv[3]);
	int iter = atoi(argv[4]);
	
	int size = pow(2,power);
	
	switch(sort_type) {
		case 0: testSort<HeapSort,NodeSequence>(size,seq_type,iter); break;
		case 1: testSort<InsertionSort,NodeSequence>(size,seq_type,iter); break;
		case 2: testSort<SelectionSort,NodeSequence>(size,seq_type,iter); break;
		case 3: testSort<MergeSort,NodeSequence>(size,seq_type,iter); break;
		case 4: testSort<QuickSortLast,VectorSequence>(size,seq_type,iter); break;
		case 5: testSort<QuickSortMedian,VectorSequence>(size,seq_type,iter); break;
		case 6: testSort<QuickSortRandom,VectorSequence>(size,seq_type,iter); break;
		case 7: testSort<RadixSort,VectorSequence>(size,seq_type,iter); break;
		default: cerr << "ERROR: Unkown sort_type"; break;
	}
}