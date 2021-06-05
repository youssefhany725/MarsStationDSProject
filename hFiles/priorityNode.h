#pragma once
template <typename T>

class priorityNode
{

	T item;
	int significant;
	priorityNode<T>* next;
public:

	priorityNode()
	{
		next = nullptr;
	}

	priorityNode(T newItem, int s)
	{
		item = newItem;
		next = nullptr;
		significant = s;

	}
	void setsignificant(int& s)
	{
		significant = &s;
	}
	int getsignificant()
	{
		return significant;
	}
	void setItem(T newItem)
	{
		item = newItem;
	}

	void setNext(priorityNode<T>* nextNodePtr)
	{
		next = nextNodePtr;
	}

	T getItem() const
	{
		return item;
	}

	priorityNode<T>* getNext() const
	{
		return next;
	}

};