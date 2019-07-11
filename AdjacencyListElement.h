#ifndef ADJACENCYLISTELEMENT_H_
#define ADJACENCYLISTELEMENT_H_

template<typename K, typename V>
class AdjacencyListElement
{
private:
	K key;
	V value;
public:
	AdjacencyListElement(const K& key, const V& value);

	K& getKey();
	V& getValue();
};

template<typename K, typename V>
AdjacencyListElement<K, V>::AdjacencyListElement(const K& key, const V& value):
	key(key), value(value) {}

template<typename K, typename V>
K& AdjacencyListElement<K, V>::getKey()
{
	return key;
}

template<typename K, typename V>
V& AdjacencyListElement<K, V>::getValue()
{
	return value;
}

#endif /* ADJACENCYLISTELEMENT_H_ */
