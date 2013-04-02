//seq_type
//0 = Min-Max Ordered
//1 = Max-Min Ordered
//2 = Unordered (Random)
//3 = Nearly Sorted

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

using namespace std;

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
		for (int i = 0; i < n; ++i) {
			S.insertLast(rand()%n);
		}
	}
	else if (seq_type == 3) {
		for (int i = 0; i < n; ++i) {
			S.insertLast(n + (n/10) - (rand()%(n/5)));
		}
	}
	else 
		cerr << "You suck at typing";
}

template<template<typename, typename> class Sort, template<typename> class Seq >
void testSort(int n, int seq_type, int iter) 
{
	Sort<int,Comp> sorter;
	Seq<int> copied;
	generateSequence(n,seq_type,copied);
	clock_t start = clock();
	for (int i = 0; i < iter; ++i) {
		Seq<int> S = copied;
		sorter.sort(S);
	}
	clock_t end = clock();
	double avg = double(end - start) / (CLOCKS_PER_SEC * iter);
	cout << avg << endl;
}

int main(int argc, char* argv[]) 
{
	// THE STUFF
	int test_type = atoi(argv[1]);
	int seq_type = atoi(argv[2]);
	int size = atoi(argv[3]);
	
	int iter = 10;
	
	switch(test_type) {
		case 0: testSort<HeapSort,NodeSequence>(size,seq_type,iter); break;
		case 1: testSort<InsertionSort,NodeSequence>(size,seq_type,iter); break;
		case 2: testSort<SelectionSort,NodeSequence>(size,seq_type,iter); break;
		case 3: testSort<MergeSort,NodeSequence>(size,seq_type,iter); break;
		case 4: testSort<QuickSortLast,VectorSequence>(size,seq_type,iter); break;
		case 5: testSort<QuickSortMedian,VectorSequence>(size,seq_type,iter); break;
		case 6: testSort<QuickSortRandom,VectorSequence>(size,seq_type,iter); break;
		case 7: testSort<RadixSort,VectorSequence>(size,seq_type,iter); break;
		default: cerr << "You suck at typing"; break;
	}
	
}