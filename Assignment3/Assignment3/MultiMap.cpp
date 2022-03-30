#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <exception>
#include <iostream>

using namespace std;


MultiMap::MultiMap() : 
	nodes{ new Node[2] }, capacity{ 1 }, head{ -1 }, tail{ -1 }, firstEmpty{ 0 }, length{ 0 }, nrElements{ 0 }
{
	//TODO - Implementation
	this->nodes[0].next = -1;
}
// Theta(1)

void MultiMap::add(TKey c, TValue v) {
	//TODO - Implementation
	int currentNode = head;

	while (currentNode != -1 && nodes[currentNode].key != c)
		currentNode = nodes[currentNode].next;

	// If the key does not exist
	if (currentNode == -1)
	{
		// If the array is full, resize
		if (firstEmpty == -1)
		{
			capacity *= 2;
			Node* newNodes = new Node[capacity];
			for (int i = 0; i < length; ++i)
				newNodes[i] = nodes[i];

			for (int i = length; i < capacity; ++i)
				if (i + 1 < capacity)
					newNodes[i].next = i + 1;
				else
					newNodes[i].next = -1;

			delete[] nodes;
			nodes = newNodes;
			firstEmpty = length;
		}

		int insert = firstEmpty;
		firstEmpty = nodes[firstEmpty].next;

		nodes[insert].key = c;
		nodes[insert].next = -1;
		
		if (head == -1)
		{
			head = insert;
		}
		else
		{
			nodes[tail].next = insert;
		}
		tail = insert;

		nodes[insert].values.nodes = new ArrayNode[1];
		nodes[insert].values.firstEmpty = -1;
		nodes[insert].values.capacity = 1;
		nodes[insert].values.length = 1;
		nodes[insert].values.head = 0;
		nodes[insert].values.tail = 0;
		nodes[insert].values.nodes[0].info = v;
		nodes[insert].values.nodes[0].next = -1;

		++length;
		++nrElements;
	}
	else // The key exists
	{
		// If the array is full
		if (nodes[currentNode].values.firstEmpty == -1)
		{
			nodes[currentNode].values.capacity *= 2;
			ArrayNode* newNodes = new ArrayNode[nodes[currentNode].values.capacity];
			for (int i = 0; i < nodes[currentNode].values.length; ++i)
				newNodes[i] = nodes[currentNode].values.nodes[i];
			for (int i = 0; i < nodes[currentNode].values.capacity; ++i)
				if (i + 1 < nodes[currentNode].values.capacity)
					newNodes[i].next = i + 1;
				else
					newNodes[i].next = -1;

			delete[] nodes[currentNode].values.nodes;
			nodes[currentNode].values.nodes = newNodes;
			nodes[currentNode].values.firstEmpty = nodes[currentNode].values.length;
		}

		int insert = nodes[currentNode].values.firstEmpty;
		nodes[currentNode].values.firstEmpty = nodes[currentNode].values.nodes[insert].next;

		nodes[currentNode].values.nodes[insert].info = v;
		nodes[currentNode].values.nodes[insert].next = -1;
		nodes[currentNode].values.nodes[nodes[currentNode].values.tail].next = insert;
		nodes[currentNode].values.tail = insert;

		++nodes[currentNode].values.length;
		++nrElements;
	}
}
// Best case: Theta(1), Worst case: Theta(nrKeys), Average case: O(nrKeys)


bool MultiMap::remove(TKey c, TValue v) {
	//TODO - Implementation
	int currentNode = head;

	while (currentNode != -1 && nodes[currentNode].key != c)
		currentNode = nodes[currentNode].next;

	// Key not found
	if (currentNode == -1)
		return false;

	int currentValue = nodes[currentNode].values.head;

	while (currentValue != -1 && nodes[currentNode].values.nodes[currentValue].info != v)
		currentValue = nodes[currentNode].values.nodes[currentValue].next;

	// Value not found
	if (currentValue == -1)
		return false;

	int next = nodes[currentNode].values.nodes[currentValue].next;

	int prev = nodes[currentNode].values.head;
	while (prev != -1 && nodes[currentNode].values.nodes[prev].next != currentValue)
		prev = nodes[currentNode].values.nodes[prev].next;

	// The element we found is the first one
	if (prev == -1)
		nodes[currentNode].values.head = next;
	else
		nodes[currentNode].values.nodes[prev].next = next;

	// The element we found is the last one
	if (next == -1)
		nodes[currentNode].values.tail = prev;

	int posEmpty = nodes[currentNode].values.firstEmpty;
	nodes[currentNode].values.firstEmpty = currentValue;
	nodes[currentNode].values.nodes[nodes[currentNode].values.firstEmpty].next = posEmpty;

	nrElements -= 1;
	nodes[currentNode].values.length -= 1;

	// If we have no elements for a certain key, we delete that key
	if (nodes[currentNode].values.head == -1)
	{
		int next = nodes[currentNode].next;
		int prev = head;

		while (prev != -1 && nodes[prev].next != currentNode)
			prev = nodes[prev].next;

		// We delete the first key
		if (prev == -1)
			head = next;
		else
			nodes[prev].next = next;

		if (next == -1)
			tail = prev;

		posEmpty = firstEmpty;
		firstEmpty = currentNode;
		nodes[firstEmpty].next = posEmpty;

		length -= 1;
	}

	return true;
}
// Best case: Theta(1), Worst case: Theta(nrElements), Average case: O(nrElements)

vector<TValue> MultiMap::search(TKey c) const {
	//TODO - Implementation
	vector<TValue> result;
	int currentNode = head;

	while (currentNode != -1 && nodes[currentNode].key != c)
		currentNode = nodes[currentNode].next;

	// Key not found
	if (currentNode == -1)
		return result;

	int currentValue = nodes[currentNode].values.head;
	while (currentValue != -1)
	{
		result.push_back(nodes[currentNode].values.nodes[currentValue].info);
		currentValue = nodes[currentNode].values.nodes[currentValue].next;
	}

	return result;
}
// Best case: Theta(1), Worst case: Theta(nrElements), Average case: O(nrElements)

int MultiMap::size() const {
	//TODO - Implementation
	return this->nrElements;
}
// Theta(1)

bool MultiMap::isEmpty() const {
	//TODO - Implementation
	if (this->nrElements == 0)
		return true;
	return false;
}
// Theta(1)

MultiMapIterator MultiMap::iterator() const {
	return MultiMapIterator(*this);
}
// Theta(1)

MultiMap::~MultiMap() {
	//TODO - Implementation

	int node = this->head;
	while (node != -1)
	{
		delete[] this->nodes[node].values.nodes;
		node = this->nodes[node].next;
	}
	delete[] this->nodes;
}
// Theta(nrKeys)