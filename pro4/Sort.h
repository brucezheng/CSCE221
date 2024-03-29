#ifndef SORT_H_
#define SORT_H_

#include "VectorSequence.h"
#include "NodeSequence.h"
#include "SortedSeqPriorityQueue.h"
#include "UnsortedSeqPriorityQueue.h"
#include "HeapPriorityQueue.h"

//============== PQ Sort ==============

template<typename PQ>
class PriorityQueueSort{ //PQ Sort class
  typedef typename PQ::ItemPair::element_type Object;
  public:
    void sort(NodeSequence<Object>& s){
		PQ p;
		Object empty;
		// transfer elements into pq then back to sequence
		while (!s.isEmpty()) {
			p.insertItem(s.elemAtRank(0),s.elemAtRank(0));
			s.removeAtRank(0);
		}
		while (!p.isEmpty()) {
			s.insertLast(p.minElement());
			p.removeMin();
		}
    }
};

template <typename Object, typename Comp>
class HeapSort
 : public PriorityQueueSort<HeapPriorityQueue<Object, Object, Comp> >
{ };

template <typename Object, typename Comp>
class SelectionSort
 : public PriorityQueueSort<UnsortedSeqPriorityQueue<Object, Object, Comp> >
{ };

template <typename Object, typename Comp>
class InsertionSort
 : public PriorityQueueSort<SortedSeqPriorityQueue<Object, Object, Comp> >
{ };

//============= Merge Sort =============

template <typename Object, typename Comp>
class MergeSort {
protected:   						// utility functions
  Comp comp;
  void merge(NodeSequence<Object>& S1, NodeSequence<Object>& S2, NodeSequence<Object>& S);	// merge utility
  void appendFirst(NodeSequence<Object>& src, NodeSequence<Object>& dst) {	// append utility
    Object obj = src.first().element();			// first of source
    src.remove(src.first());				// remove it
    dst.insertLast(obj);				// append to dest
  }
public:
  MergeSort() : comp() {}
  void sort(NodeSequence<Object>& S);				// merge sort S
};

template <typename Object, typename Comp>
void MergeSort<Object, Comp>::
merge(NodeSequence<Object>& S1, NodeSequence<Object>& S2, NodeSequence<Object>& S) {	// merge S1 and S2 to S
  while(!S1.isEmpty() && !S2.isEmpty())			// until either is empty
    if(comp(S1.first().element(),S2.first().element()) <= 0)	// copy smaller element
      appendFirst(S1, S);
    else
      appendFirst(S2, S);
  while(!S1.isEmpty())					// copy remainder of S1
    appendFirst(S1, S);
  while(!S2.isEmpty())					// copy remainder of S2
    appendFirst(S2, S);
}

template <typename Object, typename Comp>
void MergeSort<Object, Comp>::
sort(NodeSequence<Object>& S) {				// sort S
  NodeSequence<Object> S1, S2;
  int i;
  int n = S.size();
  if (n <= 1) return;					// 0 or 1 elements
  for (i = n  ; i > n/2  ; i--) appendFirst(S, S1);	// put half in S1
  for (       ; i > 0    ; i--) appendFirst(S, S2);	// put remainder in S2
  sort(S1);					// sort S1
  sort(S2);					// sort S2
  merge(S1, S2, S);					// merge S1 and S2 into S
}

//============= Quick Sort =============

template <typename Object, typename Comp, class Pivot>
class QuickSort {					// QuickSort class
protected:
  Comp comp;
  void quickSortStep(VectorSequence<Object>& S, int leftBound, int rightBound); // recursive utility
public:
  QuickSort() : comp() {}
  void sort(VectorSequence<Object>& S);				// main entry point
};

template <typename Object, typename Comp, class Pivot>
void QuickSort<Object, Comp, Pivot>:: 			// recursive portion
quickSortStep(VectorSequence<Object>& S, int leftBound, int rightBound) {
  if (leftBound >= rightBound) return;			// 0 or 1 elements
  Pivot p;
  int pivot = p.SelectPivot(S, leftBound, rightBound, comp);	// select pivot
  S.swapElements(S.atRank(pivot), S.atRank(rightBound)); //put pivot element at end
  Object pivotobj = S.atRank(rightBound).element(); 
  int leftIndex = leftBound; 				// will scan rightward
  int rightIndex = rightBound - 1;			// will scan leftward
  while (leftIndex <= rightIndex) {
    while ((leftIndex <= rightIndex) &&			// scan right to larger
    	    comp(S.atRank(leftIndex).element(), pivotobj) <= 0)
      leftIndex++; 
    while ((rightIndex >= leftIndex) &&			// scan left to smaller
    	    comp(S.atRank(rightIndex).element(), pivotobj) >= 0)
      rightIndex--;
    if (leftIndex < rightIndex)				// both elements found
      S.swapElements(S.atRank(leftIndex), S.atRank(rightIndex));
  }							// until indices cross
  
  // Shift right the right half of the sequence
  // instead of swapping the last element with the middle element
	int i = rightBound;
  while (i > leftIndex) {
    S.replaceAtRank(i, S.atRank(i-1).element());
    i--;
  }
  // pivot at leftIndex
  S.replaceAtRank(leftIndex, pivotobj);
  
  // Swap the last element with the middle element
  //S.swapElements(S.atRank(leftIndex), S.atRank(rightBound));
  
  quickSortStep(S, leftBound, leftIndex-1);		// recur on both sides
  quickSortStep(S, leftIndex+1, rightBound);
}

template <typename Object, typename Comp, class Pivot>
void QuickSort<Object, Comp, Pivot>::
sort(VectorSequence<Object>& S) {				// main entry point
  if (S.size() <= 1) return;				// 0 or 1 elements
  quickSortStep(S, 0, S.size()-1);			// call sort utility
}

struct PivotLast{
  template<typename Seq, typename Comp>
  int SelectPivot(Seq& s, int leftBound, int rightBound, Comp& c){
    return rightBound;	// select last as pivot
  }
};

template <typename Object, typename Comp>
class QuickSortLast : public QuickSort<Object, Comp, PivotLast>{};

struct PivotMedian{
  template<typename Seq, typename Comp>
  int SelectPivot(Seq& s, int leftBound, int rightBound, Comp& c){
    int midRank = (leftBound + rightBound) / 2;
	bool leftLessRight = c(s.elemAtRank(leftBound),s.elemAtRank(rightBound)) < 0;
	bool leftLessMid = c(s.elemAtRank(leftBound),s.elemAtRank(midRank)) < 0;
	bool midLessRight = c(s.elemAtRank(midRank),s.elemAtRank(rightBound)) < 0;
	
	if (leftLessRight) { //find and return the median of the elements of our 3 elements
		if (leftLessMid) {
			if (midLessRight) return midRank; 	// L M R
			else return rightBound; 		// L R M
		}
		else return leftBound; 				// M L R
	}
	else {
		if (leftLessMid) return leftBound; 		// R L M
		else {
			if (midLessRight) return rightBound; 	// M R L
			else return midRank; 			// R M L
		}
	}
  }
};

template <typename Object, typename Comp>
class QuickSortMedian : public QuickSort<Object, Comp, PivotMedian>{};

struct PivotRandom{
  template<typename Seq, typename Comp>
  int SelectPivot(Seq& s, int leftBound, int rightBound, Comp& c){
	srand (time(NULL));
    return leftBound + (rand() % (rightBound - leftBound + 1)); // select pivot from range of leftbound to rightbound, inclusive
  }
};

template <typename Object, typename Comp>
class QuickSortRandom : public QuickSort<Object, Comp, PivotRandom>{};


//============= Radix Sort =============

template <typename Object, typename Comp>
class RadixSort {					// QuickSort class
protected:
  Comp comp;
public:
  RadixSort() : comp() {}
  void sort(VectorSequence<Object>& S);				// main entry point
};

//#define SHOWPASS
template <typename Object, typename Comp>
void RadixSort<Object, Comp>::
sort(VectorSequence<Object>& S) {				// main entry point
   int i,m=0,exp=1;
   int n = S.size(); 
   VectorSequence<Object> b;

   //fill b with last values (just needs to be initialized to right size)
   //also find max
   for(i=0;i<n;i++)
   {
      b.insertLast( S.elemAtRank( i ) );
      if( S.elemAtRank(i)>m )
	 m= S.elemAtRank( i );
   }

   while(m/exp>0)
   {
      int bucket[10]={0};
      for(i=0;i<n;i++) {
	 bucket[S.elemAtRank(i)/exp%10]++;
      }

      for(i=1;i<10;i++)
	 bucket[i]+=bucket[i-1];
      

      for(i=n-1;i>=0;i--) {
	 b.replaceAtRank(--bucket[S.elemAtRank(i)/exp%10], S.elemAtRank(i) );
      }

      for(i=0;i<n;i++)
	 S.replaceAtRank( i, b.elemAtRank(i) );
      exp*=10;

#ifdef SHOWPASS
      printf("\nPASS   : ");
      for(i=0;i<n;i++)
      {
	 cout << S.elemAtRank( i ) << " " ;
      }
      cout << endl;
#endif
   }		

}

#endif
