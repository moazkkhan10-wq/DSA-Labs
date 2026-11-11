/* 
 * Design Explanation:
 * 1. Fixed-Size Array: Used to store student records up to a capacity limit (MAX_SIZE), 
 *    allowing us to demonstrate a full-array boundary check as required by the lab instructions.
 * 2. Binary Search Tree (BST): Used for structured, hierarchical storage and efficient 
 *    searching of student records ordered alphabetically by their roll numbers.
 * 3. Queue (Linked List-based): Used for managing help requests in First-In-First-Out (FIFO) 
 *    order, ensuring students must exist in the system before requesting help.
 * 
 * Time Complexities:
 * - Adding to Array / BST: O(N) worst-case for array scan/BST insertion.
 * - Searching in BST: O(log N) average case / O(N) worst-case.
 * - Queue Enqueue / Serve: O(1).
 */
#include <iostream>
#include <string>
using namespace std;
const int MAX_SIZE = 5; // Fixed capacity for array testing
// Structure for Student Record
struct Student {
    string rollNo;
    string name;
};
// BST Node for sorted student storage and fast searching
struct BSTNode {
    string rollNo;
    string name;
    BSTNode* left;
    BSTNode* right;
};
// Queue Node for help desk requests
struct QueueNode {
    string rollNo;
    QueueNode* next;
};
// Queue structure tracking front and rear
struct HelpQueue {
    QueueNode* front;
    QueueNode* rear;

    HelpQueue() {
        front = nullptr;
        rear = nullptr;
    }
};
// Function prototypes
bool searchArray(Student arr[], int count, const string& rollNo);
void addStudent(Student arr[], int& count, BSTNode*& bstRoot);
void searchStudent(BSTNode* bstRoot);
void displayArray(Student arr[], int count);
void enqueueRequest(BSTNode* bstRoot, HelpQueue& q);
void serveRequest(HelpQueue& q);
BSTNode* insertBST(BSTNode* root, const string& rollNo, const string& name);
bool searchBST(BSTNode* root, const string& rollNo);
void freeBST(BSTNode* root);
void freeQueue(HelpQueue& q);
int main() {
    Student studentArray[MAX_SIZE];
    int arrayCount = 0;
    BSTNode* bstRoot = nullptr;
    HelpQueue helpQueue;
    int choice;
    do {
        cout << "\n==============================\n";
        cout << "   STUDENT HELP DESK SYSTEM   \n";
        cout << "==============================\n";
        cout << "1. Add Student (Array & BST)\n";
        cout << "2. Search Student (via BST)\n";
        cout << "3. Display Student Array (Fixed-Size)\n";
        cout << "4. Register Help Request (Queue)\n";
        cout << "5. Serve Next Help Request (Queue)\n";
        cout << "6. Exit & Clean Memory\n";
        cout << "Enter your choice (1-6): ";
        if (!(cin >> choice)) {
            cout << "Invalid input. Exiting.\n";
            break;
        }
        cin.ignore(); // Clear newline buffer

        switch (choice) {
            case 1:
                addStudent(studentArray, arrayCount, bstRoot);
                break;
            case 2:
                searchStudent(bstRoot);
                break;
            case 3:
                displayArray(studentArray, arrayCount);
                break;
            case 4:
                enqueueRequest(bstRoot, helpQueue);
                break;
            case 5:
                serveRequest(helpQueue);
                break;
            case 6:
                freeBST(bstRoot);
                freeQueue(helpQueue);
                cout << "Memory cleaned successfully. Exiting program.\n";
                break;
            default:
                cout << "Invalid choice! Please select between 1 and 6.\n";
        }
    } while (choice != 6);
    return 0;
}
// Check if student exists in the fixed-size array
bool searchArray(Student arr[], int count, const string& rollNo) {
    for (int i = 0; i < count; i++) {
        if (arr[i].rollNo == rollNo) {
            return true;
        }
    }
    return false;
}
// Insert into BST recursively
BSTNode* insertBST(BSTNode* root, const string& rollNo, const string& name) {
    if (root == nullptr) {
        BSTNode* newNode = new BSTNode;
        newNode->rollNo = rollNo;
        newNode->name = name;
        newNode->left = newNode->right = nullptr;
        return newNode;
    }
    if (rollNo < root->rollNo) {
        root->left = insertBST(root->left, rollNo, name);
    } else if (rollNo > root->rollNo) {
        root->right = insertBST(root->right, rollNo, name);
    }
    return root;
}
// Search student in BST
bool searchBST(BSTNode* root, const string& rollNo) {
    if (root == nullptr) return false;
    if (root->rollNo == rollNo) return true;
    if (rollNo < root->rollNo) return searchBST(root->left, rollNo);
    return searchBST(root->right, rollNo);
}
// Add student record (checks array full boundary and adds to both Array and BST)
void addStudent(Student arr[], int& count, BSTNode*& bstRoot) {
    // Boundary check for fixed-size array
    if (count >= MAX_SIZE) {
        cout << "\nError: Fixed-size array is full! Maximum capacity (" << MAX_SIZE << ") reached.\n";
        return;
    }
   string rollNo, name;
    cout << "\nEnter Roll Number: ";
    getline(cin, rollNo);
    // Check duplicate
    if (searchArray(arr, count, rollNo)) {
        cout << "Error: Roll number '" << rollNo << "' already exists!\n";
        return;
    }
    cout << "Enter Student Name: ";
    getline(cin, name);
    // Store in Fixed-Size Array
    arr[count].rollNo = rollNo;
    arr[count].name = name;
    count++;
    // Insert into BST for searching
    bstRoot = insertBST(bstRoot, rollNo, name);

    cout << "Success: Student record added to Array and BST!\n";
}
// Search interface using BST
void searchStudent(BSTNode* bstRoot) {
    if (bstRoot == nullptr) {
        cout << "\nError: No student records available in the BST.\n";
        return;
    }
    string rollNo;
    cout << "\nEnter Roll Number to search: ";
    getline(cin, rollNo);
    if (searchBST(bstRoot, rollNo)) {
        cout << "Search Successful: Student with roll number '" << rollNo << "' found in BST.\n";
    } else {
        cout << "Search Failed: No student found with roll number '" << rollNo << "'.\n";
    }
}
// Display fixed-size array contents
void displayArray(Student arr[], int count) {
    if (count == 0) {
        cout << "\nFixed-size array is currently empty.\n";
        return;
    }
    cout << "\n--- Students Stored in Fixed-Size Array (" << count << "/" << MAX_SIZE << ") ---\n";
    for (int i = 0; i < count; i++) {
        cout << i + 1 << ". Roll No: " << arr[i].rollNo << " | Name: " << arr[i].name << "\n";
    }
}
// Register help request in Queue (validates via BST)
void enqueueRequest(BSTNode* bstRoot, HelpQueue& q) {
    if (bstRoot == nullptr) {
        cout << "\nError: Cannot add help request. No students registered yet.\n";
        return;
    }
    string rollNo;
    cout << "\nEnter Roll Number for help request: ";
    getline(cin, rollNo);
    if (!searchBST(bstRoot, rollNo)) {
        cout << "Error: Roll number '" << rollNo << "' is not registered in the system.\n";
        return;
    }
    QueueNode* newNode = new QueueNode;
    newNode->rollNo = rollNo;
    newNode->next = nullptr;
    if (q.rear == nullptr) {
        q.front = q.rear = newNode;
    } else {
        q.rear->next = newNode;
        q.rear = newNode;
    }
    cout << "Success: Help request added to Queue for Roll No: " << rollNo << "\n";
}
// Serve help request from Queue
void serveRequest(HelpQueue& q) {
    if (q.front == nullptr) {
        cout << "\nQueue is empty. No pending help requests.\n";
        return;
    }
    QueueNode* temp = q.front;
    cout << "\n[Serving Help Request]\n";
    cout << "Processed request for Roll Number: " << temp->rollNo << "\n";

    q.front = q.front->next;
    if (q.front == nullptr) {
        q.rear = nullptr;
    }

    delete temp;
}
// Free BST memory recursively
void freeBST(BSTNode* root) {
    if (root != nullptr) {
        freeBST(root->left);
        freeBST(root->right);
        delete root;
    }
}
// Free Queue memory
void freeQueue(HelpQueue& q) {
    while (q.front != nullptr) {
        QueueNode* temp = q.front;
        q.front = q.front->next;
        delete temp;
    }
    q.rear = nullptr;
}