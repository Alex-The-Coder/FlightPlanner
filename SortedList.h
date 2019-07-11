#ifndef SORTEDLIST_H_
#define SORTEDLIST_H_

#include "LinkedList.h"
using namespace std;

template<typename T>
class SortedList
{
private:
	LinkedList<T> backing;
	function<bool(T&, T&)> calculator;
public:
	SortedList(function<bool(T&, T&)>);

	unsigned int getSize();
	bool isEmpty();

	LinkedListIterator<T> begin();
	LinkedListIterator<T> end();

	T& getElement(unsigned int);
	bool containsElement(T&);
	bool containsElementByValue(T);
	void addElement(T&);
	void addElementByValue(T);
	T removeElement(unsigned int);
};

template<typename T>
SortedList<T>::SortedList(function<bool(T&, T&)> calculator):
	calculator(calculator) {}

template<typename T>
unsigned int SortedList<T>::getSize()
{
	return backing.getSize();
}

template<typename T>
bool SortedList<T>::isEmpty()
{
	return backing.isEmpty();
}

template<typename T>
LinkedListIterator<T> SortedList<T>::begin()
{
	return backing.begin();
}

template<typename T>
LinkedListIterator<T> SortedList<T>::end()
{
	return backing.end();
}

template<typename T>
T& SortedList<T>::getElement(unsigned int index)
{
	return backing.getElement(index);
}

template<typename T>
bool SortedList<T>::containsElement(T& element)
{
	return backing.containsElement(element);
}

template<typename T>
bool SortedList<T>::containsElementByValue(T element)
{
	return containsElement(element);
}

template<typename T>
void SortedList<T>::addElement(T& element)
{
	unsigned int index = 0;

	for (T& val : backing)
	{
		if (calculator(element, val))
		{
			break;
		}
        
		index++;
	}

	backing.insertElement(element, index);
}

template<typename T>
void SortedList<T>::addElementByValue(T element)
{
	addElement(element);
}

template<typename T>
T SortedList<T>::removeElement(unsigned int index)
{
	return backing.removeElementAt(index);
}

#endif /* SORTEDLIST_H_ */
