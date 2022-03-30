#pragma once
#include "SortedSet.h"

//DO NOT CHANGE THIS PART
class SortedSetIterator
{
	friend class SortedSet;
private:
	const SortedSet& multime;
	SortedSetIterator(const SortedSet& m);

	//TODO - Representation
	TComp* list;
	int length;
	int currentPosition;

public:
	void first();
	void next();
	TElem getCurrent();
	bool valid() const;

	//moves the current element from the iterator k steps forward, or makes the iterator invalid if there are less than k elements left in the SortedSet.
	//throws an exception if the iterator is invalid or if k is negative or zero
	void jumpForward(int k);
};

