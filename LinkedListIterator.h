#ifndef LINKEDLISTITERATOR_H_
#define LINKEDLISTITERATOR_H_

#include "ConcurrentModificationException.h"
#include "IndexOutOfBoundsException.h"
#include "ListNode.h"

template<typename T>
class LinkedListIterator
{
private:
	ListNode<T>* node;
	unsigned long initialMods;
	unsigned long* totalMods;
public:
	LinkedListIterator(ListNode<T>*, unsigned long*);

	T& operator*();
	void operator++();
	bool operator!=(const LinkedListIterator<T>&);
private:
	void checkForModification();
};

template<typename T>
LinkedListIterator<T>::LinkedListIterator(ListNode<T>* node, unsigned long* totalMods)
{
	this->node = node;
	this->initialMods = *totalMods;
	this->totalMods = totalMods;
}

template<typename T>
T& LinkedListIterator<T>::operator*()
{
	if (node == nullptr)
	{
		throw IndexOutOfBoundsException();
	}
    
	checkForModification();

	return node->getData();
}

template<typename T>
void LinkedListIterator<T>::operator++()
{
	if (node == nullptr)
	{
		return;
	}
    
	checkForModification();
	node = node->getNext();
}

template<typename T>
bool LinkedListIterator<T>::operator!=(const LinkedListIterator<T>& rhs)
{
	return node != rhs.node;
}

template<typename T>
void LinkedListIterator<T>::checkForModification()
{
	if (initialMods != *totalMods)
	{
		throw ConcurrentModificationException();
	}
}

#endif /* LINKEDLISTITERATOR_H_ */
