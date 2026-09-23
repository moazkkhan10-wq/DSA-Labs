#include <iostream>
#include <string>
using namespace std;

// Function to check if a string is a palindrome using iteration
bool isPalindrome(const string& str) {
    int start = 0;
    int end = str.length() - 1;

    while (start < end) {
        if (str[start] != str[end]) {
            return false; // Characters don't match
        }
        start++;
        end--;
    }
    return true; // All character pairs matched
}

int main() {
    string input;

    cout << "Enter a string: ";
    cin >> input;

    if (isPalindrome(input)) {
        cout << "\"" << input << "\" is a palindrome." << endl;
    } else {
        cout << "\"" << input << "\" is NOT a palindrome." << endl;
    }

    return 0;
}
