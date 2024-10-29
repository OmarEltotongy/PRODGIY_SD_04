/*
 * PRODIGY_SD_04.cpp
 *  Sudoku Solver
 *  Created on: Oct 28, 2024
 *  Author: Omar Eltoutongy
 */
#include <iostream>
#include <vector>
#include <sstream> /*Very important library (used in alot of applications*/
#include <chrono> // This library for timing


using namespace std;

/*Struct definition*/
typedef struct
{
	int row;
	int col;
}CellPosition;


/*Function prototypes*/
CellPosition NextEmptyCell(const vector<vector<int>>& grid_numbers);
bool NumberIsSafe(const vector<vector<int>>& grid_numbers, const CellPosition& position, const int number);
bool BackTracking(vector<vector<int>>& grid_numbers);


int main()
{
	const int grid_size = 9;
	int grid_data;
	string line;

	cout << "Welcome to our Sudoku solver\n\n";

	//To store the entire Sudoku grid, 2D vectro is required
	vector<vector<int>> grid_numbers(grid_size, vector<int>(grid_size));

	cout << "Please fill the grid with numbers to solve it\n"
		<< "Enter each row with numbers separated by spaces (use 0 for empty cells):\n";

	// Loop through each row of the grid from 1 to 9
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

	cout << "\n\nThe current grid:\n";
	for (const auto& row : grid_numbers)
	{
		for (int num : row)
		{
			cout << num << " ";
		}
		cout << endl;
	}

	// Start the time
	auto start = chrono::high_resolution_clock::now();

	/*Algorithm for solving the sudoku*/
	if (BackTracking(grid_numbers))
	{
		/*End of time*/
		auto end = chrono::high_resolution_clock::now(); 

		/*Difference between the start and the end*/
		auto duration = chrono::duration_cast<chrono::seconds>(end - start);

		int hours = duration.count() / 3600;
		int minutes = (duration.count() % 3600) / 60;
		int seconds = duration.count() % 60;

		cout << "\nThe Solved grid:\n\n";
		for (const auto& row : grid_numbers)
		{
			for (int num : row)
			{
				cout << num << " ";
			}
			cout << endl;
		}

		/*Display the time taken in hours, minutes, and seconds*/ 

		cout << "\nTime taken to solve the Sudoku: "
			<< hours << " hours, "
			<< minutes << " minutes, and "
			<< seconds << " seconds.\n";
	}
	else
	{
		cout << "This sudoku cannot be solved!\n\n";
	}
	
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
	// Check the row
	for (int col = 0; col < 9; col++) {
		if (grid_numbers[position.row][col] == number) {
			return false; // Found the number in the row
		}
	}

	// Check the column
	for (int row = 0; row < 9; row++) {
		if (grid_numbers[row][position.col] == number) {
			return false; // Found the number in the column
		}
	}

	// Check the 3x3 box
	/*First try: */
		/* To check the number with the 3*3 grid itself */

	//CellPosition start_check{ 1,1 };
	//int flag_grid = 1;

	//for (int i = 0; i < grid_numbers.size(); i++)
	//{
	//	if (flag_grid == 0)
	//		break;

	//	for (int j = 0; j < grid_numbers.size(); j++)
	//	{
	//		// First 3 rows
	//		if ((i / 3) <= 1)
	//		{
	//			// First 3 columns
	//			if ((j / 3) <= 1)
	//			{
	//				start_check.row = 1;
	//				start_check.col = 1;
	//				flag_grid = 0;
	//			}

	//			// Second 3 columns
	//			else if ((j / 3) <= 2)
	//			{
	//				start_check.row = 1;
	//				start_check.col = 4;
	//				flag_grid = 0;
	//			}

	//			// Third 3 columns
	//			else if ((j / 3) <= 3)
	//			{
	//				start_check.row = 1;
	//				start_check.col = 7;
	//				flag_grid = 0;
	//			}
	//		}
	//		else if ((i / 3) <= 2)
	//		{
	//			// First 3 columns
	//			if ((j / 3) <= 1)
	//			{
	//				start_check.row = 4;
	//				start_check.col = 1;
	//				flag_grid = 0;
	//			}

	//			// Second 3 columns
	//			else if ((j / 3) <= 2)
	//			{
	//				start_check.row = 4;
	//				start_check.col = 4;
	//				flag_grid = 0;
	//			}

	//			// Third 3 columns
	//			else if ((j / 3) <= 3)
	//			{
	//				start_check.row = 4;
	//				start_check.col = 7;
	//				flag_grid = 0;
	//			}
	//		}
	//		else if ((i / 3) <= 3)
	//		{
	//			// First 3 columns
	//			if ((j / 3) <= 1)
	//			{
	//				start_check.row = 7;
	//				start_check.col = 1;
	//				flag_grid = 0;
	//			}

	//			// Second 3 columns
	//			else if ((j / 3) <= 2)
	//			{
	//				start_check.row = 7;
	//				start_check.col = 4;
	//				flag_grid = 0;
	//			}

	//			// Third 3 columns
	//			else if ((j / 3) <= 3)
	//			{
	//				start_check.row = 7;
	//				start_check.col = 7;
	//				flag_grid = 0;
	//			}
	//		}
	//	}
	//}

	/*Second try from ChatGPT: integer Division */
	int boxRowStart = (position.row / 3) * 3;
	int boxColStart = (position.col / 3) * 3;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (grid_numbers[boxRowStart + i][boxColStart + j] == number) {
				return false; // Found the number in the 3x3 box
			}
		}
	}

	return true;
}

bool BackTracking(vector<vector<int>>& grid_numbers) {
	
	// Find the next empty cell
	CellPosition position= NextEmptyCell(grid_numbers);

	// Base case
	if (position.row == -1 && position.col == -1) {
		cout << "\nSudoku is Solved!\n\n";
		return true;
	}

	// Place numbers from 1 to 9 in the current empty cell
	for (int num = 1; num <= 9; num++) {
		if (NumberIsSafe(grid_numbers, position, num)) {

			grid_numbers.at(position.row).at(position.col) = num;

			if (BackTracking(grid_numbers)) {
				return true;
			}

			grid_numbers.at(position.row).at(position.col) = 0;
			cout << "Backtracking from position (" << position.row + 1 << "," << position.col + 1 << ")\n";
		}
	}

	// If no number can be placed, backtracking again
	return false;
}
