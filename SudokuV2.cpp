// Home

#include <iostream>

using namespace std;

class Square
{
public:
  int num;
  bool visited;g++
  bool constant; //From input
};

void print();
bool check(int, int);
bool Backtracking(int, int);

Square box[9][9];
int row, col;
bool direction;// 1 -> forward, 0 -> backwards

int main()
{
  int input[9][9] = {   {8,0,0, 0,0,0, 0,0,0},
                        {0,0,3, 6,0,0, 0,0,0},
                        {0,7,0, 0,9,0, 2,0,0},

                        {0,5,0, 0,0,7, 0,0,0},
                        {0,0,0, 0,4,5, 7,0,0},
                        {0,0,0, 1,0,0, 0,3,0},

                        {0,0,1, 0,0,0, 0,6,8},
                        {0,0,8, 5,0,0, 0,1,0},
                        {0,9,0, 0,0,0, 4,0,0}, };

  for (row = 0; row < 9; row++)
    for (col = 0; col < 9; col++)
    {
      Square temp;
      if(input[row][col] == 0)
      {
        temp.visited = false;
        temp.constant = false;
      }
      else
      {
        temp.visited = true;
        temp.constant = true;
        temp.num = input[row][col];
      }
      box[row][col] = temp;
    }

  //Done input, ready to solve it.
  direction = true;
  print();
  if ( Backtracking(0,0) )
    print();
  else
    cout << "Impossible to solve it..." << endl;
}

void print()
{
  cout << "----------------------" << endl;

  for (row = 0; row < 9; row++)
  {
    if(row%3 == 0) cout << endl;
    for (col = 0; col < 9; col++)
    {
        if(col%3 == 0) cout << " ";
        if(box[row][col].visited == true)
          cout << box[row][col].num;
        else
          cout << " ";
    }
    cout << endl;
  }
}

bool Backtracking(int r, int c)
{
  if(r == 9) return true;

  if(box[r][c].constant == true)
  {
    if(direction == true)
    {
      if(c==8)
      {
        c = -1;
        r++;
      }
      return Backtracking(r,c+1);
    }
    else
    {
      if(c==0)
      {
        c = 9;
        r--;
      }
      return Backtracking(r,c-1);
    }
  }

  box[r][c].num = 0;
  box[r][c].visited = true;

  while(true)
  {
    box[r][c].num++;

    if(box[r][c].num == 10)
    {
      box[r][c].visited = false;
      return false;
    }

    if( check(r,c) )
    {
      direction = true;
      if(c==8)
      {
        c = -1;
        r = r+1;
      }

      if ( Backtracking(r,c+1) )
      {
        direction = false;
        return true;
      }
      else
        direction = false;
    }
  }
}

bool check(int r, int c)
{
  //Check row
  for(int i=0; i < 9; i++)
  {
    if(i == c) continue;

    if(box[r][i].visited == true)
      if(box[r][i].num == box[r][c].num)
        return false;
  }

  //Check col
  for(int i=0; i < 9; i++)
  {
    if(i == r) continue;

    if(box[i][c].visited == true)
      if(box[i][c].num == box[r][c].num)
        return false;
  }

  //Check 3x3 box
  int temp_r = r;
  int temp_c = c;

  while(true)
  {
    if(temp_r % 3 != 0) temp_r--;
    else break;
  }
  while(true)
  {
    if(temp_c % 3 != 0) temp_c--;
    else break;
  }

  for(int i=0; i<3; i++)
    for(int j=0; j<3; j++)
    {
      if(temp_r+i == r && temp_c+j == c) continue;

      if(box[temp_r+i][temp_c+j].visited == true)
        if(box[temp_r+i][temp_c+j].num == box[r][c].num)
          return false;
    }
  return true;
}
