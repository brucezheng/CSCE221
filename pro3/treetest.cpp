/* This program tests the BinaryTree implmentation */

#include "BinaryTree.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <cmath>
#include <ctime>

using namespace std;

// generate functions taken from correctness.cpp

BinaryTree<int> generateLinkedList(int n)
{
  BinaryTree<int> T(0);
  BinaryTree<int>::Node* p = T.getRoot();
  for(int i = 0; i < n - 1; i++){
    BinaryTree<int>::Node* c = T.insertLeft(p,i+1);
    p = c;
  }
  return T;
}

BinaryTree<int> generateCompleteTree(int n)
{
  BinaryTree<int> T(0);
  int I = 0;
  deque<BinaryTree<int>::NodePtr> leaves;
  deque<BinaryTree<int>::NodePtr> tmpleaves;
  leaves.push_back(T.getRoot());
  while(I < n){
    int size = leaves.size();
    tmpleaves.clear();
    for(int i=0;i<size&&I<n;i++){
      BinaryTree<int>::Node* l = T.insertLeft(leaves[i],++I);
      tmpleaves.push_back(l);
      BinaryTree<int>::Node* r = T.insertRight(leaves[i],++I);
      tmpleaves.push_back(r);
    }
    leaves.clear();
    leaves = tmpleaves;
  }
  return T;
}

void timeInorder(int size, int iter, bool linear, bool recur)
{
	BinaryTree<int> bt;
	// different tree structure depending on function parameters
	if (linear) bt = generateLinkedList(size);
	else bt = generateCompleteTree(size);
	// time for iter iterations
	clock_t start = clock();
	// different method called depending on test type
	if (recur) {
		// do iter iterations
		for (int i = 0; i <iter; ++i) {
			deque<BinaryTree<int>::NodePtr> d;
			bt.recursiveInorder(d,bt.getRoot());
		}
	}
	else {
		// do iter iterations
		for (int i = 0; i <iter; ++i) {
			deque<BinaryTree<int>::NodePtr> d;
			bt.inorder(d,bt.getRoot());
		}
	}
	clock_t end = clock();
	double avg = double(end - start) / double(CLOCKS_PER_SEC) / iter;
	// print out test params/results
	string test_type = "InO ";
	if (linear) test_type += "Lin ";
	else test_type += "Bal ";
	if (recur) test_type += "Re ";
	else test_type += "It ";
	cout << test_type << size << ' ' << iter << ' ' << setprecision(10) << avg << endl;
}

void memTree(int size, bool linear)
{
	BinaryTree<int> bt;
	if (linear) bt = generateLinkedList(size);
	else bt = generateCompleteTree(size-1);
	for(int i = 0; i < pow(2,15); ++i) {
		int j = 1;
	}
}

void memInorder(int size, bool linear, bool recur)
{
	BinaryTree<int> bt;
	// different method called depending on test type
	if (linear) bt = generateLinkedList(size);
	else bt = generateCompleteTree(size-1);
	// loops are for easier reading of massif graph
	for(int i = 0; i < pow(2,10); ++i) {
		int j = 1;
	}
	for(int i = 0; i < 5; ++i) {
		if (recur) bt.dequelessRecInorder(bt.getRoot());
		else bt.dequelessInorder(bt.getRoot());
	}
}

int main(int argc, char* argv[])
{
	// command line arguments
	// determines which test to run
	int memtest = atoi(argv[1]);
	int choice = atoi(argv[2]);
	// power input is the power of 2 you wish to test
	int power = atoi(argv[3]);

	if (power < 0 || power > 20)
		cerr << "Bad power size!";
	
	int size = pow(2,power);
	int iter;

	iter = 10 * pow(2,20-power);
	
	// depending on arguments, different tests/test parameters are called
	
	if (memtest == 0){
		switch (choice) {
			case 1: timeInorder(size, iter, true, true); break;
			case 2: timeInorder(size, iter, true, false); break;
			case 3: timeInorder(size, iter, false, true); break;
			case 4: timeInorder(size, iter, false, false); break;
			default: cerr << "Bad choice!"; break;
		}
	}
	else if (memtest == 1) {
		switch (choice) {
			case 1: memInorder(size, true, true); break;
			case 2: memInorder(size, true, false); break;
			case 3: memInorder(size, false, true); break;
			case 4: memInorder(size, false, false); break;
			default: cerr << "Bad choice!"; break;
		}
	}
	else if (memtest == 2) {
		switch (choice) {
			case 1: memTree(size, true); break;
			case 2: memTree(size, false); break;
			default: cerr << "Bad choice!"; break;
		}
	}
	else cerr << "Bad choice!";
}	


