#include "SortedSetIterator.h"
#include <exception>

using namespace std;

SortedSetIterator::SortedSetIterator(const SortedSet& m) : 
	multime(m), currentPosition{ 0 }, length{ 0 }, list{ new TComp[m.size()] }
{
	//TODO - Implementation
	for (int i = 0; i < m.capacity; ++i)
		if (m.set[i].value != NULL_TELEM)
			list[length++] = m.set[i].value;

	for (int i = 0; i < length - 1; ++i)
		for (int j = i + 1; j < length; ++j)
			if (m.r(list[j], list[i]))
			{
				TComp aux = list[i];
				list[i] = list[j];
				list[j] = aux;
			}
}
// Theta(capacity^2) - because of sorting algorithm

void SortedSetIterator::first() {
	//TODO - Implementation
	currentPosition = 0;
}
// Theta(1)

void SortedSetIterator::next() {
	//TODO - Implementation
	if (!valid())
		throw exception();

	currentPosition++;
}
// Theta(1)

TElem SortedSetIterator::getCurrent()
{
	//TODO - Implementation
	if (!valid())
		throw exception();

	return list[currentPosition];
}
// Theta(1)

bool SortedSetIterator::valid() const {
	//TODO - Implementation
	return currentPosition < length;
}
// Theta(1)

//moves the current element from the iterator k steps forward, or makes the iterator invalid if there are less than k elements left in the SortedSet.
//throws an exception if the iterator is invalid or if k is negative or zero
void SortedSetIterator::jumpForward(int k)
{
	if (k < 0)
		throw exception();
	if (!valid())
		throw exception();

	currentPosition += k;
}
// Theta(1)