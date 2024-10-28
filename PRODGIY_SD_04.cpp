/*
 * PRODIGY_SD_04.cpp
 *  Sudoku Solver
 *  Created on: Oct 28, 2024
 *  Author: Omar Eltoutongy
 */
#include <iostream>
#include <vector>
#include <sstream> /*Very important library*/
using namespace std;

/*Function prototypes*/
typedef struct
{
	int row;
	int col;
}CellPosition;

CellPosition position;

CellPosition NextEmptyCell(const vector<vector<int>>& grid_numbers);
bool NumberIsSafe(const vector<vector<int>>& grid_numbers, const CellPosition& position, const int number);


int main()
{
	const int grid_size = 9;
	int grid_data;
	string line;

	cout << "Welcome to our Sudoku solver\n\n";

	// 2D vector to store the entire Sudoku grid
	vector<vector<int>> grid_numbers(grid_size, vector<int>(grid_size));

	cout << "Please fill the grid with numbers to solve it\n"
		<< "Enter each row with numbers separated by spaces (use 0 for empty cells):\n";

	// Loop through each row of the grid
	for (int i = 0; i < grid_size; i++)
	{
		bool valid_row = false;

		// Repeat until a valid row is entered
		while (!valid_row)
		{
			cout << "Row number " << (i + 1) << ": ";
			getline(cin, line);

			istringstream iss(line);
			vector<int> temp_row;
			bool row_has_error = false;

			// Try to extract exactly 9 numbers
			while (iss >> grid_data)
			{
				if (grid_data < 0 || grid_data > 9)
				{
					cout << "Invalid entry detected. Each number must be between 0 and 9.\n";
					row_has_error = true;
					break;
				}
				temp_row.push_back(grid_data);
			}

			// Check if there were exactly 9 numbers and no errors
			if (temp_row.size() == grid_size && !row_has_error)
			{
				grid_numbers[i] = temp_row;
				valid_row = true;
			}
			else
			{
				cout << "Please re-enter the entire row with exactly 9 numbers between 0 and 9.\n";
			}
		}
	}

	cout << "\nThe current grid:\n";
	for (const auto& row : grid_numbers)
	{
		for (int num : row)
		{
			cout << num << " ";
		}
		cout << endl;
	}


	/*Algorithm for solving the sudoku*/

	return 0;
}

CellPosition NextEmptyCell(const vector<vector<int>>& grid_numbers)
{
	for (int i = 0; i < grid_numbers.size(); i++)
	{
		for (int j = 0; j < grid_numbers.size(); j++)
		{
			if (grid_numbers.at(i).at(j) == 0)
			{
				return CellPosition{ i, j };
			}
		}
	}
	return CellPosition{ -1 , -1 }; /*If there is no next empty cell*/
}

bool NumberIsSafe(const vector<vector<int>>& grid_numbers, const CellPosition& position, const int number)
{
	bool flag_safe = true;

	/*To check every row with constant column*/
	for (int i = 0; i < grid_numbers.size(); i++)
	{
		if (grid_numbers.at(i).at(position.col) == number)
		{
			flag_safe = false;
			return flag_safe;
		}
	}

	/*To check every column with constant row*/
	for (int j = 0; j < grid_numbers.size(); j++)
	{
		if (grid_numbers.at(position.row).at(j) == number)
		{
			flag_safe = false;
			return flag_safe;
		}
	}

	/*To check the number with the 3*3 grid itself*/

	CellPosition start_check{ 1,1 };
	int flag_grid = 1;

		for (int i = 0; i < grid_numbers.size(); i++)
		{
			if (flag_grid == 0)
				break;

			for (int j = 0; j < grid_numbers.size(); j++)
			{
				/*First 3 rows*/
				if ((i / 3) <= 1)
				{
					/*First 3 columns*/
					if ((j / 3) <= 1)
					{
						start_check.row = 1;
						start_check.col = 1;
						flag_grid = 0;
					}

					/*Second 3 columns*/
					else if ((j / 3) <= 2)
					{
						start_check.row = 1;
						start_check.col = 4;
						flag_grid = 0;
					}

					/*Third 3 columns*/
					else if ((j / 3) <= 3)
					{
						start_check.row = 1;
						start_check.col = 7;
						flag_grid = 0;
					}

				}
				else if ((i / 3) <= 2)
				{

					/*First 3 columns*/
					if ((j / 3) <= 1)
					{
						start_check.row = 4;
						start_check.col = 1;
						flag_grid = 0;
					}

					/*Second 3 columns*/
					else if ((j / 3) <= 2)
					{
						start_check.row = 4;
						start_check.col = 4;
						flag_grid = 0;
					}

					/*Third 3 columns*/
					else if ((j / 3) <= 3)
					{
						start_check.row = 4;
						start_check.col = 7;
						flag_grid = 0;
					}
				}
				else if ((i / 3) <= 3)
				{
					/*First 3 columns*/
					if ((j / 3) <= 1)
					{
						start_check.row = 7;
						start_check.col = 1;
						flag_grid = 0;
					}

					/*Second 3 columns*/
					else if ((j / 3) <= 2)
					{
						start_check.row = 7;
						start_check.col = 4;
						flag_grid = 0;
					}

					/*Third 3 columns*/
					else if ((j / 3) <= 3)
					{
						start_check.row = 7;
						start_check.col = 7;
						flag_grid = 0;
					}
				}
			}
		}

		
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (grid_numbers[start_check.row + i][start_check.col + j] == number) {
					flag_safe = false;
					return flag_safe;
				}
			}
		}
		return flag_safe;
}

bool BackTracking(vector<vector<int>>& grid_numbers) {
	// Find the next empty cell
	position = NextEmptyCell(grid_numbers);

	// Base case: If there are no more empty cells, the puzzle is solved
	if (position.row == -1 && position.col == -1) {
		cout << "Sudoku is Solved!\n\n";
		return true;
	}

	// Try placing numbers 1 through 9 in the current empty cell
	for (int num = 1; num <= 9; num++) {
		if (NumberIsSafe(grid_numbers, position, num)) {
			
			// Place the number
			grid_numbers.at(position.row).at(position.col) = num;

			// Recur to check if this leads to a solution
			if (BackTracking(grid_numbers)) {
				return true;
			}

			// If placing num doesn't lead to a solution, reset (backtrack)
			grid_numbers.at(position.row).at(position.col) = 0;
		}
	}

	// If no number can be placed, trigger backtracking
	return false;
}
