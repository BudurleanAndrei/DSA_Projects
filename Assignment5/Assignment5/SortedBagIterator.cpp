#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>

using namespace std;

SortedBagIterator::SortedBagIterator(const SortedBag& b) : bag(b)
{
	//TODO - Implementation
	first();
}
// Best case: Theta(1), Worst case: Theta(length), Average case: O(length)

TComp SortedBagIterator::getCurrent() 
{
	//TODO - Implementation
	if (!valid())
		throw std::exception();

	return currentNode->value;
}
// Theta(1)

bool SortedBagIterator::valid() 
{
	//TODO - Implementation
	return currentNode != nullptr;
}
// Theta(1)

void SortedBagIterator::next() 
{
	//TODO - Implementation
	if (!valid())
		throw std::exception();

	if (currentNode->right != nullptr)
	{
		currentNode = currentNode->right;
		while (currentNode->left != nullptr)
		{
			currentNode = currentNode->left;
		}
	}
	else
	{
		while (currentNode->parent != nullptr && currentNode->parent->right == currentNode)
			currentNode = currentNode->parent;
		currentNode = currentNode->parent;
	}
}
// Best case: Theta(1), Worst case: Theta(length), Average case: O(length)

void SortedBagIterator::first()
{
	//TODO - Implementation
	currentNode = bag.head;
	if (currentNode != nullptr)
	{
		while (currentNode->left != nullptr)
			currentNode = currentNode->left;
	}
}
// Best case: Theta(1), Worst case: Theta(length), Average case: O(length)
