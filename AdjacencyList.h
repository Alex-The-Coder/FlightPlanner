#ifndef ADJACENCYLIST_H_
#define ADJACENCYLIST_H_

#include "AdjacencyListElement.h"
#include "LinkedList.h"

template<typename K, typename V>
class AdjacencyList
{
private:
	unsigned int size = 0;
	LinkedList<AdjacencyListElement<K, V>>* buckets;
	V defaultValue;
	function<long(const K&)> hasher;
public:
	AdjacencyList(const V&, function<long(const K&)>);
	~AdjacencyList();
	AdjacencyList(const AdjacencyList<K, V>&);
	AdjacencyList<K, V>& operator=(const AdjacencyList<K, V>&);

	unsigned int getSize();

	V& operator[](const K&);
	void remove(K&);
};

template<typename K, typename V>
AdjacencyList<K, V>::AdjacencyList(const V& defaultValue, function<long(const K&)> hashFunction):
	defaultValue(defaultValue)
{
	buckets = new LinkedList<AdjacencyListElement<K, V>>[16];
	hasher = hashFunction;
}

template<typename K, typename V>
AdjacencyList<K, V>::~AdjacencyList()
{
	delete[] buckets;
}

template<typename K, typename V>
AdjacencyList<K, V>::AdjacencyList(const AdjacencyList<K, V>& copy)
{
	buckets = new LinkedList<AdjacencyListElement<K, V>>[16];

	for (unsigned int i = 0; i < 16; i++)
	{
		buckets[i] = copy.buckets[i];
	}

	hasher = copy.hasher;
	size = copy.size;
}

template<typename K, typename V>
AdjacencyList<K, V>& AdjacencyList<K, V>::operator=(const AdjacencyList<K, V>& copy)
{
	if (this != &copy)
	{
		delete[] buckets;
		buckets = new LinkedList<AdjacencyListElement<K, V>>[16];
		hasher = copy.hasher;

		for (unsigned int i = 0; i < 16; i++)
		{
			buckets[i] = copy.buckets[i];
		}

		size = copy.size;
	}

	return *this;
}

template<typename K, typename V>
unsigned int AdjacencyList<K, V>::getSize()
{
	return size;
}

template<typename K, typename V>
V& AdjacencyList<K, V>::operator[](const K& key)
{
	long hash = hasher(key);

	LinkedList<AdjacencyListElement<K, V>>& bucket = buckets[hash & 15];

	AdjacencyListElement<K, V>* val = nullptr;

	bucket.getElement([&](AdjacencyListElement<K, V>& element)
	{
		return element.getKey() == key;
	},
	[&](AdjacencyListElement<K, V>& element, unsigned int index)
	{
		val = &element;
	});

	if (val == nullptr)
	{
		AdjacencyListElement<K, V> element(key, defaultValue);

		bucket.addElement(element);
		size++;

		val = &(bucket.getElement(bucket.getSize() - 1));
	}

	return val->getValue();
}

template<typename K, typename V>
void AdjacencyList<K, V>::remove(K& key)
{
	long hash = hasher(key);

	LinkedList<AdjacencyListElement<K, V>>& bucket = buckets[hash & 15];
	LinkedList<unsigned int> toRemove;

	bucket.getElement([&](AdjacencyListElement<K, V>& element)
	{
		return element.getKey() == key;
	},
	[&](AdjacencyListElement<K, V>& element, unsigned int index)
	{
		toRemove.addElement(index);
	});

	for (unsigned int& index : toRemove)
	{
		bucket.removeElementAt(index);
		size--;
	}
}

#endif /* ADJACENCYLIST_H_ */
