#pragma once
#include <algorithm>
#include <assert.h>

template<class TElement>
class DynamicArray{
private:
	TElement* elements;
	int capacity;
	int size;

	void resize()
	{
		this->capacity *= 2;
		TElement* elems = new TElement[this->capacity];
		std::copy(this->elements, this->elements + this->size, elems);

		delete[] this->elements;
		this->elements = elems;
	}
public:
	DynamicArray(int capacity) :
		capacity{capacity}, size{0}, elements{new TElement[capacity]}
	{}

	DynamicArray():
		capacity{2}, size{0}, elements{new TElement[capacity]}
	{}
	
	~DynamicArray()
	{
		delete[] this->elements;
	}

	TElement* getElements() const
	{
		return this->elements;
	}

	int getSize() const
	{
		return this->size;
	}

	void modify(int index, TElement element)
	{
		this->elements[index] = element;
	}

	void push_back(TElement element)
	{
		if (this->capacity == this->size)
		{
			resize();
		}
		this->elements[size++] = element;
	}

	void pop_back()
	{
		this->size--;
	}
};