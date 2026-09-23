#include <iostream>
#include <string>
using namespace std;

class StringPool {
private:
    string* stringPool; // Dynamic array of strings
    int currentSize;   // Current number of strings in the pool
    int maxSize;       // Maximum size of the pool

public:
    // Constructor to initialize fields
    StringPool() {
        maxSize = 5;
        currentSize = 0;
        stringPool = new string[maxSize];
    }

    // Method to add a string to the pool
    void addString(const string& str) {
        if (currentSize < maxSize) {
            stringPool[currentSize] = str;
            currentSize++;
            cout << "Successfully added: \"" << str << "\"\n";
        } else {
            cout << "Error: Pool is full! Maximum limit is " << maxSize << ".\n";
        }
    }
    // Method that removes a string from pool without freeing memory
    void removeString() {
        if (currentSize > 0) {
            currentSize--; // Decrements active counter (simulating memory leak)
            cout << "Removed string from pool view (memory not deallocated).\n";
        } else {
            cout << "Error: Pool is already empty.\n";
        }
    }

    // Display pool contents and status
    void displayPool() const {
        cout << "\n--- Current Pool Status ---" << endl;
        cout << "Active Strings: " << currentSize << "/" << maxSize << endl;
        if (currentSize == 0) {
            cout << "[ No active strings in pool ]\n";
        } else {
            for (int i = 0; i < currentSize; i++) {
                cout << "[" << i + 1 << "] " << stringPool[i] << endl;
            }
        }
        cout << "---------------------------\n" << endl;
    }

    // Destructor to fix memory leaks by deleting the dynamic array
    ~StringPool() {
        delete[] stringPool;
        cout << "\n[System] Destructor called: Dynamic memory deallocated successfully." << endl;
    }
};
int main() {
    StringPool pool;
    int choice;
    string inputStr;

    do {
        cout << "====== STRING POOL MENU ======\n";
        cout << "1. Add String to Pool\n";
        cout << "2. Remove String (Simulate Memory Leak)\n";
        cout << "3. Display Pool Status\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter a string to add: ";
                cin >> inputStr;
                pool.addString(inputStr);
                break;

            case 2:
                pool.removeString();
                break;

            case 3:
                pool.displayPool();
                break;

            case 4:
                cout << "Exiting program...\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
        cout << endl;

    } while (choice != 4);
   return 0;
}
    return 0;
}
