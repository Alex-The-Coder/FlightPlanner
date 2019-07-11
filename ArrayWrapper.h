#ifndef ARRAYWRAPPER_H_
#define ARRAYWRAPPER_H_

#include "IndexOutOfBoundsException.h"

template <typename T>
class ArrayWrapper
{
private:
	T* internal;
	unsigned int length;
public:
	ArrayWrapper(T*, unsigned int, bool = false);

	ArrayWrapper(const ArrayWrapper&);

	~ArrayWrapper();

	ArrayWrapper& operator=(const ArrayWrapper&);

	T& operator[](const unsigned int);

	unsigned int arrayLength();
};

template <typename T>
ArrayWrapper<T>::ArrayWrapper(T* array, unsigned int length, bool deleteOld)
{
	this->internal = new T[length];
	this->length = length;
    
	for (unsigned int i = 0; i < this->length; i++)
	{
		this->internal[i] = array[i];
	}
    
	if (deleteOld)
	{
		delete[] array;
	}
}

template <typename T>
ArrayWrapper<T>::ArrayWrapper(const ArrayWrapper<T>& copy)
{
	internal = new T[copy.length];
	length = copy.length;
    
	for (unsigned int i = 0; i < length; i++)
	{
		internal[i] = copy.internal[i];
	}
}

template <typename T>
ArrayWrapper<T>::~ArrayWrapper()
{
	delete[] internal;
}

template <typename T>
ArrayWrapper<T>& ArrayWrapper<T>::operator=(const ArrayWrapper<T>& copy)
{
	if (this != &copy)
	{
		delete[] internal;
		internal = new T[copy.length];
		length = copy.length;
        
		for (unsigned int i = 0; i < length; i++)
		{
			internal[i] = copy.internal[i];
		}
	}

	return *this;
}

template <typename T>
T& ArrayWrapper<T>::operator[](const unsigned int index)
{
	if (index < 0 || index >= length)
	{
		throw IndexOutOfBoundsException();
	}

	return internal[index];
}

template <typename T>
unsigned int ArrayWrapper<T>::arrayLength()
{
	return length;
}

#endif /* ARRAYWRAPPER_H_ */
