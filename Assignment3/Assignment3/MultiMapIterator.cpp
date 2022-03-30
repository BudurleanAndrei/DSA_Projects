#include "MultiMapIterator.h"
#include "MultiMap.h"


MultiMapIterator::MultiMapIterator(const MultiMap& c): 
	col(c), currentKey{ c.head }, currentElement{c.nodes[currentKey].values.head} 
{
	//TODO - Implementation
}

TElem MultiMapIterator::getCurrent() const{
	//TODO - Implementation
	if (!valid())
		throw std::exception();

	TKey key = col.nodes[currentKey].key;
	TValue val = col.nodes[currentKey].values.nodes[currentElement].info;

	return TElem(key, val);
}
// Theta(1)

bool MultiMapIterator::valid() const {
	//TODO - Implementation
	if (currentKey == -1)
		return false;
	return true;
}
// Theta(1)

void MultiMapIterator::next() {
	//TODO - Implementation
	if (!valid())
		throw std::exception();

	currentElement = col.nodes[currentKey].values.nodes[currentElement].next;
	if (currentElement == -1)
	{
		currentKey = col.nodes[currentKey].next;
		if (currentKey != -1)
			currentElement = col.nodes[currentKey].values.head;
	}
}
// Theta(1)

void MultiMapIterator::first() {
	//TODO - Implementation
	currentKey = col.head;
	currentElement = col.nodes[currentKey].values.head;
}
// Theta(1)

void MultiMapIterator::previous()
{
	if (!valid())
		throw exception();

	if (currentElement == col.nodes[col.head].values.head)
	{
		// If the iterator points to the first element
		if (currentKey == col.head)
		{
			currentKey = -1;
			return;
		}
		int prev = col.head;
		while (prev -= 1 && col.nodes[prev].next != currentKey)
			prev = col.nodes[prev].next;

		currentKey = prev;
		currentElement = col.nodes[prev].values.tail;

		return;
	}

	int prev = col.nodes[currentKey].values.head;

	while (prev -= 1 && col.nodes[currentKey].values.nodes[prev].next != currentElement)
		prev = col.nodes[currentKey].values.nodes[prev].next;

	currentElement = prev;
	return;
}
// Best case: Theta(1), Worst case: Theta(max(nrKeys, nrElements)), Average case: O(max(nrKeys, nrElements));