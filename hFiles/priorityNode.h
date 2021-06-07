#pragma once
template <typename T>

class priorityNode
{

	T Item;
	int significant;
	priorityNode<T>* Next;
public:

	priorityNode()
	{
		Next = nullptr;
	}

	priorityNode(T newItem, int s)
	{
		Item = newItem;
		Next = nullptr;
		significant = s;

	}
	void setsignificant(int s)
	{
		significant = s;
	}
	int getsignificant()
	{
		return significant;
	}
	void setItem(T newItem)
	{
		Item = newItem;
	}

	void setNext(priorityNode<T>* nextNodePtr)
	{
		Next = nextNodePtr;
	}

	T getItem() const
	{
		return Item;
	}

	priorityNode<T>* getNext() const
	{
		return Next;
	}

};
