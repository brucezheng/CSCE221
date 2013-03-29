/* BinaryTree.h:
 * A C++ template which implements a binary tree ADT.
 */
#ifndef BINARYTREE_H
#define BINARYTREE_H
#include <iostream>
#include <deque>
#include "EulerTour.h"
#include "ListStack.h"

using namespace std;

template<typename Object>
class BinaryTree {


public:
  class Node {						// node in the BinaryTree
    private:
      Object element;					// element
      Node*  parent;					// parent
      Node*  leftchild;					// left child
      Node*  rightchild;				// right child
      int    depth;					// depth of node
	  
	  
    public:
      Node(const Object& e = Object(), Node* p = NULL, Node* l = NULL, Node* r = NULL) : element(e), parent(p), leftchild(l), rightchild(r) { 	// constructor for Node
	if(p!=NULL)
	  depth=p->depth+1;
	else depth = 0; 
      }

      ~Node(){	// destructor for Node
	  delete rightchild;
	  rightchild = NULL;
	  delete leftchild;
	  leftchild = NULL;
	  }	
      
      //accessor functions:
      Object getElement(){return element;}
      Node* getParent(){return parent;}
      Node* getLeftChild(){return leftchild;}
      Node* getRightChild(){return rightchild;}
      int getDepth(){return depth;}
      bool isExternal(){return leftchild == NULL && rightchild == NULL;}

      //modifier functions
      void setElement(const Object& e){element = e;}
      void setParent(Node* p){parent = p;}
      void setLeftChild(Node* l){leftchild = l;}
      void setRightChild(Node* r){rightchild = r;}
      
  };

  typedef Node* NodePtr;				// pointer to the node
  typedef deque<NodePtr> NodeDeque;

private:
  NodePtr root;						// root of binary tree
  int size;						// number of nodes
  int depth;						// depth of tree  

public:
	NodePtr copy(NodePtr source) //helper function for copy ctor and assign operator
	{
		if (source == NULL) return NULL;
		else {
			NodePtr target = new Node(source->getElement());
			target->setRightChild(copy(source->getRightChild()));
			target->setLeftChild(copy(source->getLeftChild()));
			return target;
		}
	}
  BinaryTree():root(new Node()),size(0),depth(0){ }	// default constructor for BinaryTree
  BinaryTree(const Object& e):root(new Node(e)),size(1),depth(0){ }  // creates a BinaryTree and initializes the root
  ~BinaryTree(){					// destructor for BinaryTree
      delete root;
      root = NULL;
  }
  BinaryTree(const BinaryTree& bt)
  {
	  size = bt.size;
	  depth = bt.depth;
	  root = copy(bt.root);
  }
  BinaryTree& operator=(const BinaryTree& bt) // deep copy
  {	  
	  size = bt.size;
	  depth = bt.depth;
	  delete root;
	  root = copy(bt.root);
	  return *this;
  }
  int getSize() const{					// return size of BinaryTree
    return size;
  }
  int getDepth() const{					// return the depth of the BinaryTree
    return depth;
  }
  bool isEmpty(){					// is the BinaryTree empty?
    return size == 0;
  }
  NodePtr getRoot(){					// returns the root of the BinaryTree
    return root;
  }
  friend ostream &operator<<( ostream &out, BinaryTree<Object> &T ){   // prints out the tree
    deque<NodePtr> in;
    in.clear();
    T.inorder(in,T.getRoot());
    for (int i=0; i < in.size(); i++) {
      for (int j=0; j < in[i]->getDepth(); j++)
        out << "  ";
      out << in[i]->getElement() << endl;
    }
  }
  NodePtr insertLeft(NodePtr p, const Object& e)   // inserts a Node with element e to the left of p
  {
	//check nothing is there
	if(p->getLeftChild() != NULL)
		return NULL;
	//create node called l with parent set to p, then set p's left node to l
	NodePtr l = new Node(e,p);
	p->setLeftChild(l);
	//update depth and size
	++size;
	if(l->getDepth() > depth)
		depth = l->getDepth();
	return l;
  }
  NodePtr insertRight(NodePtr p, const Object& e)	// inserts a Node with element e to the right of p
  {
	//check nothing is there
	if(p->getRightChild() != NULL)
		return NULL;
	//create node called r with parent set to p, then set p's right node to r
	NodePtr r = new Node(e,p);
	p->setRightChild(r);
	//update depth and size
	++size;
	if(r->getDepth() > depth)
		depth = r->getDepth();
	return r;
  }
  void preorder(deque<NodePtr> &v,NodePtr r)		// gives a deque that contains the preorder traversal of the BinaryTree
  {
    //creates an object of RecursivePostorder and then calls its respective tour
	RecursivePreorder<Object> tour(v);
	tour.eulerTour(r);
  }
  void inorder(deque<NodePtr> &v,NodePtr r)		// gives a deque that contains the inorder traversal of the BinaryTree
  {
	// implemented interatively, using a stack to follow tree structure
	ListStack<NodePtr> ls;
	NodePtr i = r;
	bool done = false;
	while (!done) {
		if (i != NULL) { // look down the left branch
			ls.push(i);
			i = i->getLeftChild();
		}
		else {
			if (ls.isEmpty()) { // when the stack is empty, we've run out of left branches
				done = true;
			}
			else { // last node onto the deque, then look at next left branch
				i = ls.pop();
				v.push_back(i);
				i = i->getRightChild();
			}
		}
	}
  }
  void recursiveInorder(deque<NodePtr> &v,NodePtr r) // gives a deque that contains the inorder traversal of the BinaryTree
  {
	// implemented recursively, creates an object of RecursivePostorder and then calls its respective tour
	RecursiveInorder<Object> tour(v);
	tour.eulerTour(r);
  }

  void postorder(deque<NodePtr> &v,NodePtr r)		// gives a deque that contains the postorder traversal of the BinaryTree
  {
    //creates an object of RecursivePostorder and then calls its respective tour
	RecursivePostorder<Object> tour(v);
	tour.eulerTour(r);
  }
  void dequelessRecInorder(NodePtr r) 		// same as recursive inorder but DOESN'T make a deque; for memory testing
  {
    //creates an object of RecursivePostorder and then calls its respective tour
	DequelessRecursiveInorder<Object> tour;
	tour.eulerTour(r);
  }
  void dequelessInorder(NodePtr r) 		// same as inorder but DOESN'T make a deque; for memory testing
  {
	// implemented interatively, using a stack to follow tree structure
	ListStack<NodePtr> ls;
	NodePtr i = r;
	bool done = false;
	while (!done) {
		if (i != NULL) { // look down the left branch
			ls.push(i);
			i = i->getLeftChild();
		}
		else {
			if (ls.isEmpty()) { // when the stack is empty, we've run out of left branches
				done = true;
			}
			else { // last node onto the deque, then look at next left branch
				i = ls.pop();
				Object o = i->getElement();
				i = i->getRightChild();
			}
		}
	}
  }
  NodePtr simpleSearch(const Object& e)			// searches the BinaryTree for the element e
  {
	//construct deque by traversing the tree in order to lok through e
	deque<NodePtr> d;
	postorder(d,root);
	//n will point to the correct node or null depending on successful search
	NodePtr n = NULL;
	// look through the whole deque
	for(int i = 0; i < d.size(); ++i){
		if(d.at(i)->getElement() == e)
		// if our current element matches we set n to its node
			n = d.at(i);
	}
	return n;
  }

};


#endif

