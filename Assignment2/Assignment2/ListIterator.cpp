#include "ListIterator.h"
#include "IteratedList.h"
#include <exception>

ListIterator::ListIterator(const IteratedList& list) : list(list) {
	//TODO - Implementation
	this->current = this->list.head;
}
// Theta(1)

void ListIterator::first() {
	//TODO - Implementation
	this->current = this->list.head;
}
// Theta(1)

void ListIterator::next() {
	//TODO - Implementation
	if (!this->valid())
		throw std::exception();

	this->current = this->current->next;
}
// Theta(1)

bool ListIterator::valid() const {
	//TODO - Implementation
	if (this->current != nullptr)
		return true;
	return false;
}
// Theta(1)

TElem ListIterator::getCurrent() const {
	//TODO - Implementation
	if (!this->valid())
		throw std::exception();
	return this->current->value;
}
// Theta(1)


//changes the current element from the iterator to the previous element, or, if the current element was the first, makes the iterator invalid
//throws an exception if the iterator is not valid
void ListIterator::previous()
{
	if (!this->valid())
		throw std::exception();

	if (this->current == this->list.head)
	{
		this->current = nullptr;
		return;
	}

	Node* node = this->current;
	this->first();

	while (this->current->next != node)
		this->next();
}
// Best case: Theta(1), Worst case: Theta(length) -> Average case: O(length)