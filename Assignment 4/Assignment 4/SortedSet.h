#pragma once
//DO NOT INCLUDE SETITERATOR

//DO NOT CHANGE THIS PART
typedef int TElem;
typedef TElem TComp;
typedef bool(*Relation)(TComp, TComp);
#define NULL_TELEM -11111111
class SortedSetIterator;


class SortedSet {
	friend class SortedSetIterator;
private:
	//TODO - Representation
	struct Element {
		TComp value;
		int next;
	};
	Element* set;
	int capacity;
	int length;
	int firstEmpty;

	Relation r;

	int hash(TComp elem) const;
	void resize();
public:
	//constructor
	SortedSet(Relation r);

	void changeFirstEmpty();
	//adds an element to the sorted set
	//if the element was added, the operation returns true, otherwise (if the element was already in the set) 
	//it returns false
	bool add(TComp e);

	//removes an element from the sorted set
	//if the element was removed, it returns true, otherwise false
	bool remove(TComp e);

	//checks if an element is in the sorted set
	bool search(TElem elem) const;

	//returns the number of elements from the sorted set
	int size() const;

	//checks if the sorted set is empty
	bool isEmpty() const;

	//returns an iterator for the sorted set
	SortedSetIterator iterator() const;

	// destructor
	~SortedSet();


};
