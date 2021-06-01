#pragma once
#include"priorityNode.h"
#include "linkedqueue.h"

template <typename T>
class priorityqueue:public LinkedQueue<T>
{
	int t;
	priorityNode <T>* Head;
	priorityNode <T>* rare;


public:
	bool isEmpty() {
		return (Head == nullptr);
	}
	priorityqueue() {

		rare = nullptr;
		Head = nullptr;


	}
	bool enqueue(const T& newitem, int sig) {
		bool b = true;
		priorityNode<T>* newNodePtr = new priorityNode<T>(newitem, sig);
		priorityNode<T>* itrator = Head;
		if (isEmpty())
		{
			Head = newNodePtr;
			rare = newNodePtr;
			b = false;
		}
		else if (*itrator->getsignificant() < sig)
		{
			b = false;
			newNodePtr->setNext(Head);
			Head = newNodePtr;

		}
		else while (itrator->getNext() &&*itrator->getNext()->getsignificant() < sig)
		{
			b = false;
			newNodePtr->setNext(itrator->getNext());
			itrator->setNext(newNodePtr);
			itrator = itrator->getNext();
		}
		if (b) {
			itrator->setNext(newNodePtr);
			rare = newNodePtr;
		}
		return true;
	}
	/*bool enqueue(priorityNode<T>* newnode, int sig) {
		bool b = true;
		priorityNode<T>* itrator = Head;
		if (isEmpty())
		{
			Head = newnode;
			rare = newnode;
			b = false;
		}
		else if (itrator->getsignificant() < sig)
		{
			b = false;
			newnode->setnext(Head);
			Head = newnode;

		}
		else while (itrator->getNext()->getsignificant() < sig)
		{
			b = false;
			newnode->setnext(itrator->getNext());
			itrator->setNext(newnode);
			itrator = itrator->getNext();
		}
		if (b) {
			itrator->setNext(newnode);
			rare = newnode;
		}
		return true;
	}*/
	bool dequeue(T& hd)
	{
		if (isEmpty())
			return false;

		priorityNode<T>* Deletednode = Head;
		hd = Head->getItem();
		Head = Head->getNext();

		if (Deletednode == rare)
			rare = nullptr;
		delete Deletednode;
		return true;
	}
	/*bool dequeue(priorityNode<T>*newnode)
	{
		if (isEmpty())
			return false;

		newnode = Head;
		Head = Head->getNext();

		if (newnode == rare)
			rare = nullptr;
		newnode->setNext(nullptr);
		return true;
	}*/
	bool peek(T& hd) {
		if (isEmpty())
			return false;
		hd = Head->getItem();
		return true;
	}
	/*bool peek(priorityNode<T>* newnode) {
		if (isEmpty())
			return false;
		newnode = Head;
		return true;
	}*/
};
