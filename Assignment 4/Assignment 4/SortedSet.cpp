#include "SortedSet.h"
#include "SortedSetIterator.h"
#include <stdlib.h>
#include <cmath>

SortedSet::SortedSet(Relation r) :
	set{ new Element[2] }, capacity{ 2 }, length{ 0 }, firstEmpty{ 0 }, r{ r }
{
	//TODO - Implementation
	for (int i = 0; i < capacity; ++i)
	{
		set[i].value = NULL_TELEM;
		set[i].next = -1;
	}
}
// Theta(capacity)


int SortedSet::hash(TComp elem) const
{
	//return abs(elem % capacity);
	double x, y;
	x = (sqrt(5) - 1) / 2;
	x = x * capacity;
	return floor(capacity * (modf(x, &y)));
}
// Theta(1)

void SortedSet::resize()
{
	int oldCapacity = capacity;
	Element* oldSet = set;

	capacity *= 2;
	set = new Element[capacity];
	for (int i = 0; i < capacity; ++i)
	{
		set[i].value = NULL_TELEM;
		set[i].next = -1;
	}
	length = 0;
	firstEmpty = 0;

	for (int i = 0; i < oldCapacity; ++i)
		add(oldSet[i].value);

	delete[] oldSet;
}
// Theta(capacity^2)

void SortedSet::changeFirstEmpty()
{
	firstEmpty += 1;

	while (firstEmpty < capacity && set[firstEmpty].value != NULL_TELEM)
		firstEmpty += 1;
}
// Best case: Theta(1), Worst case: Theta(length), Average Case: O(n)

bool SortedSet::add(TComp elem)
{
	//TODO - Implementation
	if (firstEmpty == capacity)
		resize();

	int position = hash(elem);
	if (set[position].value == NULL_TELEM)
	{
		set[position].value = elem;
		set[position].next = -1;
		length++;

		if (firstEmpty == position)
			changeFirstEmpty();

		return true;
	}

	if (set[position].value == elem)
		return false;

	while (set[position].next != -1)
	{
		position = set[position].next;
		if (set[position].value == elem)
			return false;
	}

	set[firstEmpty].value = elem;
	set[firstEmpty].next = -1;
	set[position].next = firstEmpty;
	length++;

	changeFirstEmpty();
	return true;
}
// Best case: Theta(1), Worst Case: Theta(capacity^2) - because of resize, Average case: Theta(1) amortised

bool SortedSet::remove(TComp elem) 
{
	//TODO - Implementation

	int position = hash(elem);
	int prev = -1;

	// Trying to find the element
	while (position != -1 && set[position].value != elem)
	{
		prev = position;
		position = set[position].next;
	}

	// If nothing found
	if (position == -1)
		return false;

	// Finding another element with the same hash value
	bool done = false;
	do
	{
		int pos = set[position].next;
		int ppos = position;
		while (pos != -1 && hash(set[pos].value) != position)
		{
			ppos = pos;
			pos = set[pos].next;
		}
		if (pos == -1)
			done = true;
		else // If we find another element with the same hash value, we swap them
		{
			set[position].value = set[pos].value;
			position = pos;
			prev = ppos;
		}
	} while (!done);

	// Trying to find a previous element
	if (prev == -1)
	{
		int index = 0;
		while (index < capacity && prev == -1)
			if (set[index].next == position)
				prev = index;
			else
				index++;
	}

	if (prev != -1)
		set[prev].next = set[position].next;

	set[position].value = NULL_TELEM;
	set[position].next = -1;

	if (firstEmpty > position)
		firstEmpty = position;

	length--;
	return true;
}
// Best case: Theta(1), Worst case: Theta(capacity), Average Case: Theta(1)

bool SortedSet::search(TComp elem) const
{
	//TODO - Implementation
	int position = hash(elem);

	if (set[position].value == elem)
		return true;

	while (set[position].next != -1)
	{
		position = set[position].next;
		if (set[position].value == elem)
			return true;
	}

	return false;
}
// Best case: Theta(1), Worst case: Theta(length), Average case: Theta(1)

int SortedSet::size() const 
{
	//TODO - Implementation
	return length;
}
// Theta(1)


bool SortedSet::isEmpty() const 
{
	//TODO - Implementation
	return length == 0;
}
// Theta(1)

SortedSetIterator SortedSet::iterator() const
{
	return SortedSetIterator(*this);
}
// Theta(1)

SortedSet::~SortedSet() 
{
	//TODO - Implementation
	delete[] set;
}


