
#include <exception>
#include "ListIterator.h"
#include "IteratedList.h"

IteratedList::IteratedList() {
	//TODO - Implementation
	this->length = 0;
	this->head = nullptr;
}

int IteratedList::size() const {
	//TODO - Implementation
	return this->length;
}
// Theta(1)

bool IteratedList::isEmpty() const {
	//TODO -  Implementation
	if (this->length == 0)
		return true;
	return false;
}
// Theta(1)

ListIterator IteratedList::first() const {
	return ListIterator(*this);
}
// Theta(1)

TElem IteratedList::getElement(ListIterator pos) const {
	if (!pos.valid())
		throw std::exception();
	return pos.getCurrent();
}
// Theta(1)

TElem IteratedList::remove(ListIterator& pos) {
	if (!pos.valid())
		throw std::exception();

	Node* current = this->head;
	Node* prev = this->head;
	TElem oldValue = pos.getCurrent();

	if (current == pos.current && current != nullptr)
	{
		this->head = this->head->next;
		pos.next();
		delete current;
		this->length -= 1;
		return oldValue;
	}
	
	while (current != pos.current)
	{
		prev = current;
		current = current->next;
	}

	prev->next = current->next;
	pos.next();
	current = nullptr;
	delete current;
	this->length -= 1;

	return oldValue;
}
// Best case: Theta(1), Worst case: Theta(length) -> Average case: O(length)

ListIterator IteratedList::search(TElem e) const{
	ListIterator it(*this);

	while (it.current != nullptr && it.getCurrent() != e)
		it.next();

	return it;
}
// Best case: Theta(1), Worst case: Theta(length) -> Average case: O(length)

TElem IteratedList::setElement(ListIterator pos, TElem e) {
	if (!pos.valid())
		throw std::exception();

	TElem oldValue = pos.current->value;
	pos.current->value = e;
	return oldValue;
}
// Theta(1)

void IteratedList::addToBeginning(TElem e)
{
	Node* node = new Node;

	node->value = e;

	node->next = this->head;
	this->head = node;

	this->length += 1;
}
// Theta(1)

void IteratedList::addToPosition(ListIterator& pos, TElem e) {
	if (!pos.valid())
		throw std::exception();

	Node* node = new Node;

	node->value = e;
	node->next = pos.current->next;
	pos.current->next = node;

	pos.next();

	this->length += 1;
}
// Theta(1)

void IteratedList::addToEnd(TElem e) {
	Node* node = new Node;
	node->value = e;
	node->next = nullptr;

	if (this->head == nullptr)
		this->head = node;
	else
	{
		Node* current = this->head;

		while (current->next != nullptr)
			current = current->next;

		current->next = node;
	}
	this->length += 1;
}
// Theta(length)

IteratedList::~IteratedList() {
	//TODO - Implementation

	Node* node;
	while (this->head != nullptr)
	{
		node = this->head->next;
		delete this->head;
		this->head = node;
	}
	this->head = nullptr;
	delete this->head;
}
// Theta(length)