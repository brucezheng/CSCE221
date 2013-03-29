//ListStack.h -- a list-based implementation of the stack
//Refer to ArrayStack.h (Stack implemenation) 
//for array based implemenation.

#ifndef LISTSTACK_H_
#define LISTSTACK_H_

#include "RuntimeException.h"

using namespace std;

template <typename Object>
class ListStack {
  public:
    class StackEmptyException : public RuntimeException {
      public:
        StackEmptyException() : RuntimeException("Access to empty stack") {}
    };

    //constructor - simply set top element to NULL and size to 0
    ListStack();

    // copy constructor
    ListStack(const ListStack& st); 

    //destructor
    ~ListStack();

    // assignment operator
    ListStack& operator=(const ListStack& st); 

    // is the stack empty?
    bool isEmpty() const {return m_size == 0;} 

    // number of elements in the stack
    size_t size() const {return m_size;} 

    // number of elements in the stack
    size_t mySize();

    // return the top of the stack
    Object& top() throw(StackEmptyException);

    // push object onto the stack
    void push(const Object& elem); 

    // pop the stack
    Object pop() throw(StackEmptyException); 

  protected:

    // node in the NodeList
    struct Node {						
      Object  m_element; //element
      Node*   m_next;    // next node

      // constructor
      Node(const Object& e = Object(), Node* n = NULL) : m_element(e), m_next(n) {}
    };
    
    typedef Node* NodePtr; // pointer to a Node

  private:
    // member data
    size_t  m_size; // current length of stack 
    NodePtr m_head; //top of the stack
};

//constructor - simply set top element to NULL and size to 0
template <typename Object>
ListStack<Object>::ListStack() : m_head(NULL), m_size(0) {}

//copy constructor
template <typename Object>
ListStack<Object>::ListStack(const ListStack& st) {
  //source gets the elements of st, target is used to copy elements to this stack
  NodePtr source;
  NodePtr target;
  source = st.m_head->m_next;
  //first we copy the first element
  target = new Node(st.m_head->m_element);
  m_head = target;
  //next we copy all elements from 1 to n
  while (source != NULL) {
	//copy this node
	target->m_next = new Node(source->m_element);
	target = target->m_next;
	//iterate to next node of source stack
	source = source->m_next;
  }
  m_size = st.m_size;
}

//destructor
template <typename Object>
ListStack<Object>::~ListStack() { 
  //iter is used to preserve location of nodes while temp is used to delete nodes
  NodePtr iter;
  NodePtr temp;
  iter = m_head;
  //loops through all stack elements
  while (iter != NULL) {
	//set temp to current node
	temp = iter;
	//preserve pointer to next node
	iter = iter->m_next;
	//delete current node
	delete temp;
  }
}

//assignment operator
template <typename Object>
ListStack<Object>&
ListStack<Object>::operator=(const ListStack& st) {
	//source points to nodes of st, target is used to copy elements to this
	NodePtr source;
	NodePtr target;
	source = st.m_head;
	//first we copy the first element
	//create a new node if the first node doesn't exist
	if (this->m_head == NULL) {
		this->m_head = new Node(source->m_element);
		target = this->m_head;
	}
	else {
		target = this->m_head;
		target->m_element = source->m_element;
	}
	//now we copy all elements from 1 to n
	while (source->m_next != NULL) {
		//simple element replacement if the nodes already exist
		if (target->m_next != NULL) {
			target->m_next->m_element = source->m_next->m_element;
		}
		//have to extend the list otherwise
		else {
			target->m_next = new Node(source->m_next->m_element);
		}
		target = target->m_next;
		source = source->m_next;
	}
	this->m_size = st.m_size;
  return *this;
}

// number of elements in the stack
template <typename Object>
size_t
ListStack<Object>::mySize() {
  size_t size = 0;
  ListStack<Object> temp;
  //shift elements from this stack to temp stack
  while (m_size > 0) {
	temp.push(pop());
	++size;
  }
  //shift elements from temp stack back to this stack
  while (temp.m_size > 0) {
	push(temp.pop());
  }
  return size;
}

// return the top of the stack
template <typename Object>
Object&
ListStack<Object>::top() throw(StackEmptyException) {
  if (isEmpty())
    throw StackEmptyException();
  //simply return m_head's element
  return m_head->m_element;  
}

// push object onto the stack
template <typename Object>
void
ListStack<Object>::push(const Object& elem) {
  //increments size, create new node to hold elem, then set that node to be the new top of the stack
  m_size = m_size + 1;
  NodePtr temp = new Node(elem);
  temp->m_next = m_head;
  m_head = temp;
}

// pop the stack
template <typename Object>
Object
ListStack<Object>::pop() throw(StackEmptyException) {
  //decrement size, hold element in a new variable, shift head pointer and delete old head, then retun element
  m_size = m_size - 1;
  Object elem = m_head->m_element;
  NodePtr temp = m_head;
  m_head = m_head->m_next;
  delete temp;
  return elem;
}

#endif
