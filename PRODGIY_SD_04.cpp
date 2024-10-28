/*
 * PRODIGY_SD_04.cpp
 *  Sudoku Solver
 *  Created on: Oct 25, 2024
 *  Author: Omar Eltoutongy
 */

#include <iostream>
using namespace std;

int main()
{
    int grid_size=0;

    cout << "Welcome to our Sudoku solver\n\n";
    cout << "Please enter the grid size (eg. 3 , 6 , 9): ";
    cin >> grid_size;

    while (grid_size % 3 != 0)
    {
        cout << "Invalid grid, Please enter number is divided by 3: ";
        cin >> grid_size;
    }
    
    return 0;
}
