#include "SortedBag.h"
#include "SortedBagIterator.h"
#include <iostream>

SortedBag::SortedBag(Relation r) :
	head{nullptr}, length{0}, r{r}
{
	//TODO - Implementation
}

void SortedBag::add(TComp e)
{
	//TODO - Implementation
	length++;

	Node* newNode = new Node();
	newNode->value = e;
	newNode->left = nullptr;
	newNode->right = nullptr;
	newNode->parent = nullptr;

	Node* prev = nullptr;
	Node* node = head;

	while (node != nullptr)
	{
		prev = node;
		if (r(node->value, e))
			node = node->right;
		else
			node = node->left;
	}

	if (prev == nullptr)
	{
		head = newNode;
		return;
	}

	if (r(prev->value, e))
		prev->right = newNode;
	else
		prev->left = newNode;

	newNode->parent = prev;
}
// Best case: Theta(1), Worst case: Theta(length), Average case: O(length)

bool SortedBag::remove(TComp e)
{
	//TODO - Implementation
	Node* node = head;
	Node* prev = nullptr;

	while (node != nullptr && node->value != e) 
	{
		prev = node;
		if (r(node->value, e))
			node = node->right;
		else
			node = node->left;
	}
	if (node == nullptr)
		return false;

	length -= 1;
	if (node->left == nullptr || node->right == nullptr) 
	{
		Node* curr;
		if (node->left == nullptr)
			curr = node->right;
		else
			curr = node->left;

		if (prev == nullptr)
		{
			delete node;
			head = curr;
			return true;
		}

		if (node == prev->left)
			prev->left = curr;
		else
			prev->right = curr;

		if (curr != nullptr)
			curr->parent = prev;

		delete node;
		return true;
	}
	prev = nullptr;
	Node* curr;

	curr = node->right;
	while (curr->left != nullptr)
	{
		prev = curr;
		curr = curr->left;
	}
	if (prev != nullptr)
		prev->left = curr->right;
	else
		node->right = curr->right;
	node->value = curr->value;
	delete curr;
	return true;
}
// Best case: Theta(1), Worst case: Theta(length), Average case: O(length)

bool SortedBag::search(TComp elem) const
{
	//TODO - Implementation
	Node* node = head;

	while (node != nullptr)
	{
		if (node->value == elem)
			return true;

		if (r(node->value, elem))
			node = node->right;
		else
			node = node->left;
	}
	return false;
}
// Best case: Theta(1), Worst case: Theta(length), Average case: O(length)

int SortedBag::nrOccurrences(TComp elem) const
{
	//TODO - Implementation
	int count = 0;
	Node* node = head;

	while (node != nullptr)
	{
		if (node->value == elem)
			count++;

		if (r(node->value, elem))
			node = node->right;
		else
			node = node->left;
	}
	return count;
}
// Best case: Theta(1), Worst case: Theta(length), Average case: O(length)

int SortedBag::size() const 
{
	//TODO - Implementation
	return length;
}
// Theta(1)

bool SortedBag::isEmpty() const
{
	//TODO - Implementation
	return length == 0;
}
// Theta(1)

SortedBagIterator SortedBag::iterator() const 
{
	return SortedBagIterator(*this);
}
// Theta(1)

void SortedBag::cleanup(Node* node)
{
	if (node == nullptr)
		return;

	cleanup(node->left);
	cleanup(node->right);

	delete node;
}
// Theta(length)

SortedBag::~SortedBag() 
{
	//TODO - Implementation
	cleanup(head);
}
