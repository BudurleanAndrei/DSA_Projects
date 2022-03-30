#pragma once
#include "MultiMap.h"

class MultiMap;

class MultiMapIterator
{
	friend class MultiMap;

private:
	const MultiMap& col;
	//TODO - Representation

	int currentKey;
	int currentElement;

	//DO NOT CHANGE THIS PART
	MultiMapIterator(const MultiMap& c);

public:
	TElem getCurrent()const;
	bool valid() const;
	void next();
	void first();
	//changes the current element from the iterator to the previous element, or, if the current element was the first, makes the iterator invalid
	//throws an exception if the iterator is not valid
	void previous();
};

