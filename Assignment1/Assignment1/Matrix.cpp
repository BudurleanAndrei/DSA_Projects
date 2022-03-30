#include "Matrix.h"
#include <exception>
#include <iostream>
#include <algorithm>
using namespace std;


Matrix::Matrix(int nrLines, int nrCols) {
	
	this->cols = new int[2];
	this->values = new TElem[2];
	this->size = 0;
	this->capacity = 2;

	this->nLines = nrLines;
	this->nCols = nrCols;
	this->lines = new int[nrLines + 1];
	for (int i = 0; i <= nrLines; ++i)
		this->lines[i] = 0;
}


int Matrix::nrLines() const {
	return this->nLines;
}
// Theta(1)

int Matrix::nrColumns() const {
	return this->nCols;
}
// Theta(1)

TElem Matrix::element(int i, int j) const {
	if (i < 0 || j < 0 || i >= this->nLines || j >= this->nCols)
		throw exception();
	for (int index = this->lines[i]; index < this->lines[i + 1]; ++index)
		if (j == this->cols[index])
			return this->values[index];

	return NULL_TELEM;
}
// Best case: Theta(1) (the first element is the one we want), Worst case: Theta(size) -> Average case: O(size)

TElem Matrix::modify(int i, int j, TElem e) {
	if (i < 0 || j < 0 || i >= this->nLines || j >= this->nCols)
		throw exception();

	for (int index = this->lines[i]; index < this->lines[i + 1]; ++index)
		// We found the element
		if (j == this->cols[index])
		{
			TElem val = this->values[index];
			// We have to delete it
			if (e == NULL_TELEM)
			{
				for (int index2 = index; index2 < this->size - 1; ++index2)
				{
					this->cols[index2] = this->cols[index2 + 1];
					this->values[index2] = this->values[index2 + 1];
				}
				this->size -= 1;

				for (int index2 = i + 1; index2 <= this->nLines; ++index2)
					this->lines[index2]--;
			}
			// We have to change it's value
			else
			{
				this->values[index] = e;
			}
			return val;
		}

	// We need to add the element

	if (e == NULL_TELEM)
		return NULL_TELEM;

	// Resizing the arrays if needed
	if (this->size == this->capacity)
	{
		int* newCols = new int[this->capacity * 2];
		TElem* newValues = new TElem[this->capacity * 2];

		for (int i = 0; i < this->size; ++i)
		{
			newCols[i] = this->cols[i];
			newValues[i] = this->values[i];
		}

		delete[] this->cols;
		delete[] this->values;

		this->cols = newCols;
		this->values = newValues;

		this->capacity *= 2;
	}

	this->size += 1;

	for (int index = this->size - 1; index > this->lines[i + 1]; --index)
	{
		this->cols[index] = this->cols[index - 1];
		this->values[index] = this->values[index - 1];
	}

	this->cols[this->lines[i + 1]] = j;
	this->values[this->lines[i + 1]] = e;

	for (int index = i + 1; index <= this->nLines; ++index)
		this->lines[index]++;

	return NULL_TELEM;
}
// Best case: Theta(1) (the first element is the one we want), Worst case: Theta(size) -> Average case: O(size)

pair<int, int> Matrix::positionOf(TElem elem) const
{
	for (int index = 0; index < this->size; ++index)
		if (this->values[index] == elem)
		{
			for (int i = 0; i < this->nLines; ++i)
				if (this->lines[i] <= index && index < this->lines[i + 1])
					return pair<int, int>(i, this->cols[index]);
		}

	return pair<int, int>(-1, -1);
}
// Best case: Theta(1) (the first element is the one we want), Worst case: Theta(size) -> Average case: O(size)

Matrix::~Matrix()
{
	delete[] this->cols;
	delete[] this->values;
	delete[] this->lines;
}
// Theta(1)