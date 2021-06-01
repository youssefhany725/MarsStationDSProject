#pragma once

#include "Node.h"

template <typename T>
class LinkedList
{
private:
	Node<T> *Head;	//Pointer to the head of the list
	//You can add tail pointer too (depending on your problem)
	Node<T>* last;
public:

	LinkedList()
	{
		Head = nullptr;
		last = nullptr;
	}

	//List is being desturcted ==> delete all items in the list
	~LinkedList()
	{
		DeleteAll(); 
	}
  void DeleteAll()
	{
		Node<T> *P = Head;
		while (Head)
		{
			P = Head->getNext();
			delete Head;
			Head = P;
		}
	}
  void InsertEnd(const T &data)
	{
		Node<T>* p;
		Node<T>* newnode = new Node<T>;
		newnode->setItem(data);
		if(Head==nullptr)
		{
			Head= last = newnode;
			newnode->setNext(nullptr);
		}
		else
		{
			p = last;
			while(p)
			{
				last->setNext(newnode);
				last = newnode;
				newnode->setNext(nullptr);
				p->setNext(newnode->getNext());
			}
		}
	}
  T* peek()
  {
	  return Head;
  }
};
