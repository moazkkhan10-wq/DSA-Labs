#include <iostream>
using namespace std;
int main()
 {
    int n = 3;
    int* values = new int[n];
    // Read 3 integers (fixed: i < n)
    for (int i = 0; i < n; i++)
     {
        cin >> values[i];
    }
    // Display 3 integers (fixed: moved before delete)
    for (int i = 0; i < n; i++) 
    {
        cout << values[i] << " ";
    }
    cout << endl;
    // Release memory & reset pointer (fixed: delete[] and nullptr)
    delete[] values;
    values = nullptr;
    return 0;
}
