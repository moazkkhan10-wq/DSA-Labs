#include <iostream>
using namespace std;
int main()
{
    int rows, cols;
    // 1 & 2. Read and validate input, allocate dynamic memory
    cout << "Enter number of students (rows) and subjects (cols): ";
    cin >> rows >> cols;
    if (rows <= 0 || cols <= 0)
    {
        cout << "Invalid input. Rows and columns must be positive." << endl;
        return 1;
    }
    // Allocate array of row pointers
    int **marks = new int*[rows];
    for (int r = 0; r < rows; r++)
    {
        marks[r] = new int[cols];
    }
    // 3. Read marks and display matrix using pointer arithmetic
    cout << "Enter marks for each student:\n";
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            cin >> *(*(marks + r) + c); // Pointer notation for input
        }
    }
    cout << "\nMarks Matrix:\n";
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            cout << *(*(marks + r) + c) << " "; // Pointer notation for output
        }
        cout << endl;
    }
    // 4. Calculate total for each student and find the top student
    int maxTotal = -1;
    int topStudent = 1;

    for (int r = 0; r < rows; r++)
    {
        int currentTotal = 0;
        for (int c = 0; c < cols; c++) 
        {
            currentTotal += marks[r][c];
        }
        cout << "Student " << (r + 1) << " Total: " << currentTotal << endl;
        if (r == 0 || currentTotal > maxTotal)
        {
            maxTotal = currentTotal;
            topStudent = r + 1; // 1-based student index
        }
    }
    cout << "Top student: " << topStudent << " with total " << maxTotal << endl;
    // 5. Deallocate memory
    for (int r = 0; r < rows; r++)
    {
        delete[] marks[r]; // Delete each individual row array
    }
    delete[] marks;        // Delete row-pointer array
    marks = nullptr;

    return 0;
}
