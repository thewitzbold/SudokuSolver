/*
	0  1  2    3  4  5    6  7  8
	9  10 11   12 13 14   15 16 17
	18 19 20   21 22 23   24 25 26

	27 28 29   30 31 32   33 34 35
	36 37 38   39 40 41   42 43 44
	45 46 47   48 49 50   51 52 53

	54 55 56   57 58 59   60 61 62
	63 64 65   66 67 68   69 70 71
	72 73 74   75 76 77   78 79 80
*/

#include <iostream>

using std::cout;
using std::endl;

const int SIZE = 81;
const int ROW_COL = 9;

void print(int* input)
{
	cout << endl;
	cout << "--------------------------" << endl;
	for(int index = 0; index < SIZE; index++){
		if(index % ROW_COL == 0 && index != 0)
			cout << endl;
		if(index % (ROW_COL*3) == 0 && index != 0)
			cout << endl;
		cout << input[index] << " ";
	}
	cout << endl;
}

bool check(int* input,int position){

	//Check row & col at the same time
	int col = position % ROW_COL;
	int row = position - col;
	int count = 0;
	for(int i=0; i<ROW_COL ;col += 9, row++, i++)
	{
		if(input[col] == input[position])
			count++;
		if(input[row] == input[position])
			count++;
		if(count >= 3)
			return false;
	}

	//Check for 3x3 square
	int temp_position = position;
	while(true)
	{
		col = temp_position % ROW_COL;
		if(col % 3 == 0 )
			break;
		else
			--temp_position;
	}

	while(true)
	{
		if(position >= col && position < (col+27) )
			break;
		else
			col = col + 27;
	}

	int pos = col;
	count = 0;
	for(int i=0; i<3; i++) // 3 times
	{
		--pos;
		for(int j=0; j<3; j++) // 3 times
		{
			pos = pos+1;
			if(input[pos] == input[position])
				count++;
			if(count >= 2)
				return false;
		}
		pos = pos + 9 - 2;
	}

	return true;
}

bool backtracking(int* input, int position)
{
	if( position == SIZE)
		return true;

	if(input[position] == 0)
	{
		while( input[position] != 9 )
		{
			input[position] += 1;
			if( !check(input, position) )
				continue;
			if( backtracking(input, position + 1) )
				return true;
		}
	}
	else
		return backtracking(input, position + 1);

	input[position] = 0;
	return false;
}

int main()
{
	// A soduko unsolved
	int input[SIZE] = {		8,0,0, 0,0,0, 0,0,0,
							0,0,3, 6,0,0, 0,0,0,
							0,7,0, 0,9,0, 2,0,0,

							0,5,0, 0,0,7, 0,0,0,
							0,0,0, 0,4,5, 7,0,0,
							0,0,0, 1,0,0, 0,3,0,

							0,0,1, 0,0,0, 0,6,8,
							0,0,8, 5,0,0, 0,1,0,
							0,9,0, 0,0,0, 4,0,0, };
	print(input);
	backtracking(input, 0);
	print(input);
}