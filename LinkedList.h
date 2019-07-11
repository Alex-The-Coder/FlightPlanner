#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include <functional>

#include "IndexOutOfBoundsException.h"
#include "LinkedListIterator.h"
#include "ListNode.h"

using namespace std;

template<typename T>
class LinkedList
{
private:
	ListNode<T>* front;
	ListNode<T>* back;
	unsigned int size = 0;
	unsigned long* mods = new unsigned long(0);
public:
	LinkedList();
	~LinkedList();
	LinkedList(const LinkedList<T>&);
	LinkedList<T>& operator=(const LinkedList<T>&);

	unsigned int getSize();
	bool isEmpty();

	LinkedListIterator<T> begin();
	LinkedListIterator<T> end();

	bool containsElement(T&);
	bool containsElementByValue(T);

	T& getElement(unsigned int);

	void getElement(function<bool(T&)>, function<void(T&, unsigned int)>);

	unsigned int indexOf(T&);
	unsigned int indexOfByValue(T);

	void addElement(T&);
	void addElementByValue(T);

	void insertElement(T&, unsigned int);
	void insertElementByValue(T, unsigned int);

	void removeElement(T&);
	void removeElementByValue(T);

	T removeElementAt(unsigned int);

	T& peekBack();
	T popBack();
private:
	ListNode<T>* nodeAt(unsigned int);
	void addNode(T&, ListNode<T>*);
	void removeNode(ListNode<T>*);
};

template<typename T>
LinkedList<T>::LinkedList()
{
	front = nullptr;
	back = nullptr;
}

template<typename T>
LinkedList<T>::~LinkedList()
{
	while (back != nullptr)
	{
		ListNode<T>* next = back->getPrev();
		delete back;
		back = next;
	}
    
	delete mods;
}

template<typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& copy)
{
	if (copy.front != nullptr)
	{
		front = copy.front->deepCopy();
		back = front;
        
		while (back->getNext() != nullptr)
		{
			back = back->getNext();
		}
        
		size = copy.size;
		*mods = *(copy.mods);
	}
	else
	{
		front = nullptr;
		back = nullptr;
	}
}

template<typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& copy)
{
	if (this != &copy)
	{
		while (back != nullptr)
		{
			ListNode<T>* next = back->getPrev();
			delete back;
			back = next;
		}

		if (copy.front != nullptr)
		{
			front = copy.front->deepCopy();
			back = front;
            
			while (back->getNext() != nullptr)
			{
				back = back->getNext();
			}
            
			size = copy.size;
			*mods = *(copy.mods);
		}
		else
		{
			front = nullptr;
			back = nullptr;
		}
	}

	return *this;
}

template<typename T>
unsigned int LinkedList<T>::getSize()
{
	return size;
}

template<typename T>
bool LinkedList<T>::isEmpty()
{
	return size == 0;
}

template<typename T>
LinkedListIterator<T> LinkedList<T>::begin()
{
	return LinkedListIterator<T>(front, mods);
}

template<typename T>
LinkedListIterator<T> LinkedList<T>::end()
{
	return LinkedListIterator<T>(nullptr, mods);
}

template<typename T>
bool LinkedList<T>::containsElement(T& element)
{
	ListNode<T>* cur = front;
    
	while (cur != nullptr)
	{
		if (cur->getData() == element)
		{
			return true;
		}
        
		cur = cur->getNext();
	}

	return false;
}

template<typename T>
bool LinkedList<T>::containsElementByValue(T element)
{
	return containsElement(element);
}

template<typename T>
T& LinkedList<T>::getElement(unsigned int index)
{
	if (index >= size)
	{
		throw IndexOutOfBoundsException();
	}

	ListNode<T>* node = nodeAt(index);

	return node->getData();
}

template<typename T>
void LinkedList<T>::getElement(function<bool(T&)> predicate, function<void(T&, unsigned int)> consumer)
{
	unsigned int index = 0;
    
	for (T& element : *this)
	{
		if (predicate(element))
		{
			consumer(element, index);
		}
        
		index++;
	}
}

template<typename T>
unsigned int LinkedList<T>::indexOf(T& element)
{
	ListNode<T>* cur = front;
	unsigned int index = 0;
    
	while (cur != nullptr)
	{
		if (cur->getData() == element)
		{
			return index;
		}
        
		cur = cur->getNext();
		index++;
	}

	return size;
}

template<typename T>
unsigned int LinkedList<T>::indexOfByValue(T element)
{
	return indexOf(element);
}

template<typename T>
void LinkedList<T>::addElement(T& element)
{
	addNode(element, back);
}

template<typename T>
void LinkedList<T>::addElementByValue(T element)
{
	addElement(element);
}

template<typename T>
void LinkedList<T>::insertElement(T& element, unsigned int index)
{
	if (index > size)
	{
		throw IndexOutOfBoundsException();
	}

	if (index == size)
	{
		addElement(element);
		return;
	}

	if (index == 0)
	{
		addNode(element, nullptr);
		return;
	}

	ListNode<T>* prev = nodeAt(index - 1);
	addNode(element, prev);
}

template<typename T>
void LinkedList<T>::insertElementByValue(T element, unsigned int index)
{
	insertElement(element, index);
}

template<typename T>
void LinkedList<T>::removeElement(T& element)
{
	ListNode<T>* cur = front;
    
	while (cur != nullptr)
	{
		if (cur->getData() == element)
		{
			removeNode(cur);
			return;
		}
        
		cur = cur->getNext();
	}
}

template<typename T>
void LinkedList<T>::removeElementByValue(T element)
{
	removeElement(element);
}

template<typename T>
T LinkedList<T>::removeElementAt(unsigned int index)
{
	if (index >= size)
	{
		throw IndexOutOfBoundsException();
	}
    
	ListNode<T>* node = nodeAt(index);

	T data = node->getData();
	removeNode(node);

	return data;
}

template<typename T>
T& LinkedList<T>::peekBack()
{
	if (size < 1)
	{
		throw IndexOutOfBoundsException();
	}

	return back->getData();
}

template<typename T>
T LinkedList<T>::popBack()
{
	if (size < 1)
	{
		throw IndexOutOfBoundsException();
	}

	T data = back->getData();
	removeNode(back);
	return data;
}

template<typename T>
ListNode<T>* LinkedList<T>::nodeAt(unsigned int index)
{
	if (index == 0)
	{
		return front;
	}

	if (index == size - 1)
	{
		return back;
	}

	ListNode<T>* cur;
    
	if (index < (size / 2))
	{
		cur = front;
        
		for (unsigned int i = 0; i < index; i++)
		{
			cur = cur->getNext();
		}
	}
	else
	{
		cur = back;
        
		for (unsigned int i = 0; i < (size - index - 1); i++)
		{
			cur = cur->getPrev();
		}
	}

	return cur;
}

template<typename T>
void LinkedList<T>::addNode(T& data, ListNode<T>* previous)
{
	ListNode<T>* insert = new ListNode<T>(data, previous);

	if (insert->getPrev() == nullptr)
	{
		insert->getNext() = front;
        
		if (front != nullptr)
		{
			front->getPrev() = insert;
		}
        
		front = insert;
	}
	else
	{
		insert->getNext() = previous->getNext();
		previous->getNext() = insert;
        
		if (insert->getNext() != nullptr)
		{
			insert->getNext()->getPrev() = insert;
		}
	}

	if (previous == back)
	{
		back = insert;
	}

	size++;
	(*mods)++;
}

template<typename T>
void LinkedList<T>::removeNode(ListNode<T>* node)
{
	if (node->getPrev() == nullptr)
	{
		front = node->getNext();
        
		if (front != nullptr)
		{
			front->getPrev() = nullptr;
		}
	}
	else
	{
		node->getPrev()->getNext() = node->getNext();
        
		if (node->getPrev()->getNext() != nullptr)
		{
			node->getPrev()->getNext()->getPrev() = node->getPrev();
		}
	}

	if (back == node)
	{
		back = node->getPrev();
	}

	delete node;
	size--;
	(*mods)++;
}

#endif /* LINKEDLIST_H_ */
