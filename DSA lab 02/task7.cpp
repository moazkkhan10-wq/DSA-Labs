#include <iostream>
using namespace std;
int main()
{
    int n;
    // Read n (1 to 10)
    cout << "Enter n (1-10): ";
    cin >> n;
    if (n < 1 || n > 10) 
    {
        cout << "Invalid n." << endl;
        return 1;
    }
    // Allocate initial dynamic array of n integers
    int *marks = new int[n];
    // Read n initial marks using pointer notation
    cout << "Enter " << n << " marks: ";
    for (int i = 0; i < n; i++)
    {
        cin >> *(marks + i);
    }
    // Read the new mark to append
    int newMark;
    cout << "Enter new mark: ";
    cin >> newMark;
    // Step 1: Allocate a second block of n + 1 integers
    int *temp = new int[n + 1];
    // Copy original values into the new block using pointer notation
    for (int i = 0; i < n; i++)
    {
        *(temp + i) = *(marks + i);
    }
    // Store new mark in the final position
    *(temp + n) = newMark;
    // Step 2: Release old block, redirect original pointer, update size
    delete[] marks;
    marks = temp;
    temp = nullptr; // Prevents temp from being a dangling pointer
    n = n + 1;
    // Display all values using pointer notation
    cout << "Updated marks: ";
    for (int i = 0; i < n; i++)
    {
        cout << *(marks + i) << " ";
    }
    cout << endl;
    // Step 3: Release final block exactly once
    delete[] marks;
    marks = nullptr;
    return 0;
}
