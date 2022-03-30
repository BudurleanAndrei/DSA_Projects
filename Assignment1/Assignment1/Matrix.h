#pragma once
#include "DynamicArray.h"
#include <vector>
using namespace std;
//DO NOT CHANGE THIS PART
typedef int TElem;
#define NULL_TELEM 0

class Matrix {
private:
	int* lines;

	int* cols;
	TElem* values;
	int size;
	int capacity;

	int nLines, nCols;
public:
	//constructor
	Matrix(int nrLines, int nrCols);

	~Matrix();
	//returns the number of lines
	int nrLines() const;

	//returns the number of columns
	int nrColumns() const;

	//returns the element from line i and column j (indexing starts from 0)
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem element(int i, int j) const;

	//modifies the value from line i and column j
	//returns the previous value from the position
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem modify(int i, int j, TElem e);

	//returns the position of element elem from the Matrix (as a line, column pair). If elem occurs multiple times, any position where it appears is fine. If elem is not in the Matrix, return the pair <-1, -1>.
	pair<int, int> positionOf(TElem elem) const;

};
