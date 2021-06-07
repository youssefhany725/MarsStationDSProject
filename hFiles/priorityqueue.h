#pragma once
#include"../hFiles/priorityNode.h"
#include "linkedqueue.h"

template <typename T>
class priorityqueue
{

	priorityNode <T>* Head = nullptr;
	priorityNode <T>* rear = nullptr;
	int Count;

public:
	bool isEmpty() {
		return (Head == nullptr);
	}
	priorityqueue()
	{

		rear = nullptr;
		Head = nullptr;
		Count = 0;

	}
	priorityqueue(const priorityqueue<T>& LQ)
	{
		priorityNode<T>* NodePtr = LQ.Head;
		if (!NodePtr) //LQ is empty
		{
			Head = rear = nullptr;
			Count = 0;
			return;
		}
		priorityNode<T>* ptr = new priorityNode<T>(NodePtr->getItem(),NodePtr->getsignificant());
		Head = rear = ptr;
		NodePtr = NodePtr->getNext();
		Count = 1;
		while (NodePtr)
		{
			priorityNode<T>* ptr = new priorityNode<T>(NodePtr->getItem(),NodePtr->getsignificant());
			rear->setNext(ptr);
			rear = ptr;
			NodePtr = NodePtr->getNext();
			Count++;
		}
	}
	bool enqueue(const T& newitem, int sig) {
		bool b = true;
		priorityNode<T>* newNodePtr = new priorityNode<T>(newitem, sig);
		priorityNode<T>* itrator = Head;
		if (isEmpty() || sig > Head->getsignificant())
		{
			newNodePtr->setNext(Head);
			Head = newNodePtr;
		}
		else
		{
			itrator = Head;
			while (itrator->getNext() && itrator->getNext()->getsignificant() >= sig)

				itrator = itrator->getNext();
			newNodePtr->setNext(itrator->getNext());
			itrator->setNext(newNodePtr);


		}
		Count++;
		return true;
	}
	bool dequeue(T& hd)
	{
		if (isEmpty())
			return false;

		priorityNode<T>* Deletednode = Head;
		hd = Head->getItem();
		Head = Head->getNext();

		if (Deletednode == rear)
			rear = nullptr;


		delete Deletednode;
		Count--;
		return true;
	}
	bool peek(T& hd) {
		if (isEmpty())
			return false;

		hd = Head->getItem();
		return true;
	}

	int getCount()
	{
		return Count;
	}
};