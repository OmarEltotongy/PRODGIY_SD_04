/*
 * PRODIGY_SD_04.cpp
 *  Sudoku Solver
 *  Created on: Oct 25, 2024
 *  Author: Omar Eltoutongy
 */
#include <iostream>
#include <vector>
#include <sstream> /*Very important library*/

using namespace std;

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

    return 0;
}
