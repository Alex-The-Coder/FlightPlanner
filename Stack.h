#ifndef STACK_H_
#define STACK_H_

#include "LinkedList.h"
using namespace std;

template<typename T>
class Stack
{
private:
	LinkedList<T> backing;
public:
	bool isEmpty();

	T& peek();
	T pop();
	void push(T&);
	void pushByValue(T);
};

template<typename T>
bool Stack<T>::isEmpty()
{
	return backing.isEmpty();
}

template<typename T>
T& Stack<T>::peek()
{
	return backing.peekBack();
}

template<typename T>
T Stack<T>::pop()
{
	return backing.popBack();
}

template<typename T>
void Stack<T>::push(T& element)
{
	backing.addElement(element);
}

template<typename T>
void Stack<T>::pushByValue(T element)
{
	push(element);
}

#endif /* STACK_H_ */
