#include "Sort.h"
#include "Comparator.h"

#include <iostream>
#include <ctime>

//seq_type
//1 = Min-Max Ordered
//2 = Max-Min Ordered
//3 = Unordered (Random)

template<typename Seq>
void generateNodeSequence(int n, int seq_type, Seq& S)
{
	if (id == 1) {
		for (int i = 0; i < n; ++i) {
			S.insertLast(i);
		}
	}
	else if (id == 2) {
		for (int i = 0; i < n; ++i) {
			S.insertLast(n-i);
		}
	}
	else if (id == 3) {
		for (int i = 0; i < n; ++i) {
			S.insertLast(rand());
		}
	}
	return S;
}

template<typename Seq>
void testMem(int n, bool isList) {
	if (isList) {
		Seq S;
		generateNodeSequence(n,3,S);
	}
	else {
		VectorSequence S;
		generateVectorSequence(n,3,S);
	}
}

template<template<typename, typename> class Sort, template<typename Seq> >
void testSort(int n, int seq_type, int iter) 
{
	Sort sorter;
	Seq S;
	gnerateNodeSequence(n,seq_type,S);
	for (int i = 0; i < iter; ++i) {
		sorter.sort(S);
	}
}

int Main () 
{

}