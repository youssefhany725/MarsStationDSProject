#ifndef LINKED_QUEUE_
#define LINKED_QUEUE_

#include "Node.h"
#include "QueueADT.h"
#include <vector>
using namespace std;


template <typename T>
class LinkedQueue :public QueueADT<T>
{
private:

	Node<T>* backPtr;
	Node<T>* frontPtr;
public:
	LinkedQueue();
	bool isEmpty() const;
	bool enqueue(const T& newEntry);
	//bool enqueue(Node<T>* newnode);
	bool dequeue(T& frntEntry);
	//bool dequeue(Node*<T> newnode);
	bool peek(T& frntEntry)  const;
	//bool peek(Node<T>* newnode);
	~LinkedQueue();

	//copy constructor
	LinkedQueue(const LinkedQueue<T> & LQ);
};
/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: Queue()
The constructor of the Queue class.

*/

template <typename T>
LinkedQueue<T>::LinkedQueue()
{
	backPtr = nullptr;
	frontPtr = nullptr;

}
/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: isEmpty
Sees whether this queue is empty.

Input: None.
Output: True if the queue is empty; otherwise false.
*/
template <typename T>
bool LinkedQueue<T>::isEmpty() const
{
	return (frontPtr == nullptr);
}

/////////////////////////////////////////////////////////////////////////////////////////

/*Function:enqueue
Adds newEntry at the back of this queue.

Input: newEntry .
Output: True if the operation is successful; otherwise false.
*/

template <typename T>
bool LinkedQueue<T>::enqueue(const T& newEntry)
{
	Node<T>* newNodePtr = new Node<T>(newEntry);
	// Insert the new node
	if (isEmpty())	//special case if this is the first node to insert
		frontPtr = newNodePtr; // The queue is empty
	else
		backPtr->setNext(newNodePtr); // The queue was not empty

	backPtr = newNodePtr; // New node is the last node now
	return true;
} // end enqueue
//template<typename T>
//bool LinkedQueue<T>::enqueue(Node<T>* newnode)
//{
//	newnode->setNext(nullptr);
//	if (isEmpty())	//special case if this is the first node to insert
//		frontPtr = newnode; // The queue is empty
//	else
//		backPtr->setNext(newnode); // The queue was not empty
//
//	backPtr = newnode; // New node is the last node now
//	return true;
//}

  /////////////////////////////////////////////////////////////////////////////////////////////////////////

  /*Function: dequeue
  Removes the front of this queue. That is, removes the item that was added
  earliest.

  Input: None.
  Output: True if the operation is successful; otherwise false.
  */

template <typename T>
bool LinkedQueue<T>::dequeue(T& frntEntry)
{
	if (isEmpty())
		return false;

	Node<T>* nodeToDeletePtr = frontPtr;
	frntEntry = frontPtr->getItem();
	frontPtr = frontPtr->getNext();
	// Queue is not empty; remove front
	if (nodeToDeletePtr == backPtr)	 // Special case: last node in the queue
		backPtr = nullptr;

	// Free memory reserved for the dequeued node
	delete nodeToDeletePtr;

	return true;

}
//template<typename T>
//bool LinkedQueue<T>::dequeue(Node<T>* newnode)
//{
//	if (isEmpty())
//		return false;
//
//	newnode = frontPtr;
//	frontPtr = frontPtr->getNext();
//	// Queue is not empty; remove front
//	if (newnode == backPtr)	 // Special case: last node in the queue
//		backPtr = nullptr;
//	newnode->setNext(nullptr);
//	return true;
//
//}
/////////////////////////////////////////////////////////////////////////////////////////
/*
Function: peek
copies the front of this queue to the passed param. The operation does not modify the queue.

Input: None.
Output: The front of the queue.
*/
template <typename T>
bool LinkedQueue<T>::peek(T& frntEntry) const
{
	if (isEmpty())
		return false;

	frntEntry = frontPtr->getItem();
	return true;

}
//template <typename T>
//bool LinkedQueue<T>::peek(Node<T>*newnode)
//{
//	if (isEmoty())
//		return false;
//	newnode = frontPtr;
//	return true;
//}
///////////////////////////////////////////////////////////////////////////////////
/*
Function: destructor
removes all nodes from the queue by dequeuing them
*/
template <typename T>
LinkedQueue<T>::~LinkedQueue()
{
	T temp;

	//Free (Dequeue) all nodes in the queue
	while (dequeue(temp));
}
/////////////////////////////////////////////////////////////////////////////////////////
/*
Function: Copy constructor
To avoid shallow copy,
copy constructor is provided

Input: LinkedQueue<T>: The Queue to be copied
Output: none
*/

template <typename T>
LinkedQueue<T>::LinkedQueue(const LinkedQueue<T> & LQ)
{
	Node<T>* NodePtr = LQ.frontPtr;
	if (!NodePtr) //LQ is empty
	{
		frontPtr = backPtr = nullptr;
		return;
	}

	//insert the first node
	Node<T>* ptr = new Node<T>(NodePtr->getItem());
	frontPtr = backPtr = ptr;
	NodePtr = NodePtr->getNext();

	//insert remaining nodes
	while (NodePtr)
	{
		Node<T>* ptr = new Node<T>(NodePtr->getItem());
		backPtr->setNext(ptr);
		backPtr = ptr;
		NodePtr = NodePtr->getNext();
	}
}

#endif
