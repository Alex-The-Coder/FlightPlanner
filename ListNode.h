#ifndef LISTNODE_H_
#define LISTNODE_H_

template<typename T>
class ListNode
{
private:
	T data;
	ListNode* prev;
	ListNode* next;
public:
	ListNode(T, ListNode<T>* = nullptr, ListNode<T>* = nullptr);
	ListNode<T>* deepCopy();

	T& getData();
	ListNode<T>*& getPrev();
	ListNode<T>*& getNext();
};

template<typename T>
ListNode<T>::ListNode(T data, ListNode<T>* prev, ListNode<T>* next) : data(data)
{
	this->prev = prev;
	this->next = next;
}

template<typename T>
ListNode<T>* ListNode<T>::deepCopy()
{
	ListNode<T>* newNode = new ListNode<T>(data);
    
	if (next != nullptr)
	{
		newNode->next = next->deepCopy();
		newNode->next->prev = newNode;
	}

	return newNode;
}

template<typename T>
T& ListNode<T>::getData()
{
	return data;
}

template<typename T>
ListNode<T>*& ListNode<T>::getPrev()
{
	return prev;
}

template<typename T>
ListNode<T>*& ListNode<T>::getNext()
{
	return next;
}

#endif /* LISTNODE_H_ */
