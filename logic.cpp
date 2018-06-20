// Home

// Sudoku Solver 1.0, thinking as a human
#include <iostream>
#include <vector>
using namespace std;

class oneByOne
{
public:
  vector<int> num_class;
  bool constant;
};

void print();
void solve();
void delete_num(int, int, int);
void _3by3(int, int);
void _row(int, int);
void _col(int,int);
void _3by3_onlyplace(int,int);
void _col_onlyplace(int,int);
void _row_onlyplace(int,int);


oneByOne box[9][9];

int main()
{
  int input[9][9] = { {0,0,0, 0,9,0, 4,0,3},
                      {0,0,3, 0,1,0, 0,9,6},
                      {2,0,0, 6,4,0, 0,0,7},

                      {4,0,0, 5,0,0, 0,6,0},
                      {0,0,1, 0,0,0, 8,0,0},
                      {0,6,0, 0,0,1, 0,0,2},

                      {1,0,0, 0,7,4, 0,0,5},
                      {8,2,0, 0,6,0, 7,0,0},
                      {7,0,4, 0,5,0, 0,0,0}, };
  //A vector that contains 1-9
  vector<int> full;
  for(int i=1; i<10; i++)
    full.push_back(i);

  //Initialize
  for(int i=0; i<9; i++)
    for(int j=0; j<9; j++)
    {
      oneByOne temp;
      temp.constant = false;
      if(input[i][j] == 0 )
        temp.num_class = full;
      else
        temp.num_class.push_back( input[i][j] );
      box[i][j] = temp;
    }

  //Ready to solve it.
  print();
  int goal_81 = 81*9; //81 squares, each 9,
  int temp, loop = 0;
  while(true)
  {
    cout << "Loop" << ++loop << endl;
    temp = 0;
    solve();

    for(int i=0; i<9; i++)
      for(int j=0; j<9; j++)
        temp += box[i][j].num_class.size();

    if(temp == 81) break; //Sudoku solved
    else if(temp < goal_81) goal_81 = temp; //eliminated more than one, so one more loop.
    else break; //Didnt do any changes, cannot solve it.
  }
  print();
}

void solve()
{
  int row = 0, col = 0;
  while(true)
  {
    //cout << "____" << row << "_____" << col << endl;

    if(box[row][col].num_class.size() == 1 && box[row][col].constant == false )
    {
      _3by3(row, col);
      _row(row, col);
      _col(row, col);

      box[row][col].constant = true;
    }

    if(row%3 == 0 && col%3 == 0 )
      _3by3_onlyplace(row,col);

    if(col%3 == 0)
      _col_onlyplace(row,col);

    if(row%3 == 0)
      _row_onlyplace(row,col);

    //Next little square
    if(col == 8)
    {
      col = -1;
      row++;
    }
    if(row == 9) break;
    col++;
  }
}

void print()
{
  cout << "----------------------" << endl;

  for (int row = 0; row < 9; row++)
  {
    if(row%3 == 0) cout << endl;
    for (int col = 0; col < 9; col++)
    {
        if(col%3 == 0) cout << " ";
        if( box[row][col].num_class.size() == 1 )
          cout << box[row][col].num_class[0];
        else
          cout << " ";
    }
    cout << endl;
  }
}

void delete_num(int num, int row, int col)
{
  for(int i=0; i< box[row][col].num_class.size(); i++)
    if( box[row][col].num_class[i] == num )
    {
      box[row][col].num_class.erase(box[row][col].num_class.begin()+i);
      return;
    }
}




/*     example
xxx 123 xxx
xxx 456 xxx
xxx 789 xxx

xxx xxx xxx
xxx xxx xxx
xxx xxx xxx

xxx xxx xxx
xxx xxx xxx
xxx xxx xxx
*/
void _3by3(int row, int col)
{
  int temp_r = row;
  int temp_c = col;

  //Set the position of temp_r and temo_c in the top left of 3x3 box
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
      if(row == temp_r+i && col == temp_c+j) continue;
      delete_num(box[row][col].num_class[0],temp_r+i,temp_c+j);
    }
}

/*     example
123 456 789
xxx xxx xxx
xxx xxx xxx

xxx xxx xxx
xxx xxx xxx
xxx xxx xxx

xxx xxx xxx
xxx xxx xxx
xxx xxx xxx
*/
void _row(int row, int col)
{
  for(int i=0; i<9; i++)
  {
    if(col == i) continue;
    delete_num(box[row][col].num_class[0],row,i);
  }
}




/*     example
xxx x1x xxx
xxx x2x xxx
xxx x3x xxx

xxx x4x xxx
xxx x5x xxx
xxx x6x xxx

xxx x7x xxx
xxx x8x xxx
xxx x9x xxx
*/
void _col(int row, int col)
{
  for(int i=0; i<9; i++)
  {
    if(row == i) continue;
    delete_num(box[row][col].num_class[0],i,col);
  }
}



/* For simplicity, lets imagine this 3x3
  [...] means the numbers that can be in that box,
  # means a constant number, its filled.

  [0,1,2,3]   4    [6,7,8,9]
   [0,1,2]  [0,1]      5
   [0,1,2]  [0,1]  [6,7,8,9]

   In this example, we can see that there is only one place to put a 3.
   so it must go there.

       3       4    [6,7,8,9]
    [0,1,2]  [0,1]      5
    [0,1,2]  [0,1]  [6,7,8,9]

*/
void _3by3_onlyplace(int row,int col)
{
  //If a number is found only once from a empty square, it must be there.
  int temp_row, temp_col;
  int only_one;
  for(int k=1; k<10; k++)
  {
    only_one = 0;
    for(int i=0; i<3; i++)
      for(int j=0; j<3; j++)
        for(int g=0; g < box[i+row][j+col].num_class.size(); g++)
          if(box[i+row][j+col].num_class[g] == k)
          {
            if(only_one == 0)
            {
              temp_row = i+row;
              temp_col = j+col;
              only_one = 1;
            }
            else
              only_one++;
          }

    if(box[temp_row][temp_col].num_class.size() == 1)continue;

    if(only_one == 1)
    {
      box[temp_row][temp_col].num_class.clear();
      box[temp_row][temp_col].num_class.push_back(k);
    }
  }
}

void _col_onlyplace(int row,int col)
{
  int temp_row;
  int only_one;
  for(int k=1; k<10; k++)
  {
    only_one = 0;
    for(int i=0; i<9; i++)
      for(int g=0; g < box[i][col].num_class.size(); g++)
        if(box[i][col].num_class[g] == k)
        {
          if(only_one == 0)
          {
            temp_row = i;
            only_one = 1;
          }
          else
            only_one++;
        }

    if(box[temp_row][col].num_class.size() == 1)continue;

    if(only_one == 1)
    {
      box[temp_row][col].num_class.clear();
      box[temp_row][col].num_class.push_back(k);
    }
  }
}

void _row_onlyplace(int row,int col)
{
  int temp_col;
  int only_one;
  for(int k=1; k<10; k++)
  {
    only_one = 0;
    for(int i=0; i<9; i++)
      for(int g=0; g < box[row][i].num_class.size(); g++)
        if(box[row][i].num_class[g] == k)
        {
          if(only_one == 0)
          {
            temp_col = i;
            only_one = 1;
          }
          else
            only_one++;
        }

    if(box[row][temp_col].num_class.size() == 1)continue;

    if(only_one == 1)
    {
      box[row][temp_col].num_class.clear();
      box[row][temp_col].num_class.push_back(k);
    }
  }
}
