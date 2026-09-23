#include <iostream>
using namespace std;

// STEP 1: Define the Node Structure for the Singly Linked List
struct Node {
    int data;     // Data field to store the integer value
    Node* next;   // Pointer field to store the address of the next node

    // Constructor to initialize a node with a given value
    Node(int val) {
        data = val;
        next = nullptr; // Initialize the next pointer to NULL
    }
};

// STEP 2: Define the Singly Linked List Class containing all required operations
class SinglyLinkedList {
private:
    Node* head; // Pointer to the first node in the list

public:
    // Constructor: Initialize head pointer to NULL when list is created
    SinglyLinkedList() {
        head = nullptr;
    }

    // REQUIREMENT 1: Function to insert a node at the head (beginning)
    void insertAtHead(int val) {
        // Step 1.1: Dynamically allocate a new node with the input value
        Node* newNode = new Node(val);
        
        // Step 1.2: Point the new node's next pointer to the current head
        newNode->next = head;
        
        // Step 1.3: Update head to point to the new node
        head = newNode;
        
        cout << "Inserted " << val << " at the head.\n";
    }

    // REQUIREMENT 2: Function to insert a node at the 3rd location
    void insertAtThird(int val) {
        int count = countNodes();
        
        // Step 2.1: Check if the list has fewer than 2 nodes
        if (count < 2) {
            cout << "List has fewer than 2 nodes (Current count: " << count 
                 << "). Cannot insert at 3rd position. Inserting at end instead.\n";
            
            // Handle insertion at end for smaller lists
            Node* newNode = new Node(val);
            if (head == nullptr) {
                head = newNode;
            } else {
                Node* temp = head;
                while (temp->next != nullptr) {
                    temp = temp->next;
                }
                temp->next = newNode;
            }
            return;
        }

        // Step 2.2: Create the new node
        Node* newNode = new Node(val);
        
        // Step 2.3: Traverse to the 2nd node so the new node can be linked as the 3rd
        Node* temp = head;
        for (int i = 1; i < 2; i++) { // Loop once to reach index 2 (2nd node)
            temp = temp->next;
        }

        // Step 2.4: Adjust pointers to insert the node at position 3
        newNode->next = temp->next; // Point new node to old 3rd node
        temp->next = newNode;       // Link 2nd node to new node
        
        cout << "Inserted " << val << " at 3rd position.\n";
    }

    // REQUIREMENT 3: Function to display the contents of the linked list
    void displayList() const {
        // Step 3.1: Handle empty list case
        if (head == nullptr) {
            cout << "List is empty (NULL)\n";
            return;
        }

        // Step 3.2: Traverse from head to end and print values separated by arrows
        Node* temp = head;
        cout << "List: ";
        while (temp != nullptr) {
            cout << temp->data << " -> ";
            temp = temp->next; // Move to the next node
        }
        cout << "NULL\n"; // Mark termination at NULL
    }

    // REQUIREMENT 4: Function to delete the last node of the list
    void deleteLast() {
        // Step 4.1: Special Case 1 - List is empty
        if (head == nullptr) {
            cout << "List is empty! Nothing to delete.\n";
            return;
        }

        // Step 4.2: Special Case 2 - List has only one node
        if (head->next == nullptr) {
            delete head;        // Deallocate memory
            head = nullptr;     // Set head to NULL
            cout << "Deleted the only node in the list.\n";
            displayList();      // Confirm operation
            return;
        }

        // Step 4.3: Traverse to the second-to-last node
        Node* temp = head;
        while (temp->next->next != nullptr) {
            temp = temp->next;
        }

        // Step 4.4: Delete the last node and update pointer
        delete temp->next;      // Free dynamic memory of last node
        temp->next = nullptr;   // Disconnect last node pointer
        
        cout << "Deleted last node successfully.\n";
        displayList();          // Confirm updated list
    }

    // REQUIREMENT 5: Function to count the total number of nodes
    int countNodes() const {
        int count = 0;
        Node* temp = head;
        
        // Traverse through all nodes and increment counter
        while (temp != nullptr) {
            count++;
            temp = temp->next;
        }
        return count; // Return total count
    }

    // REQUIREMENT 6: Function to reverse the linked list iteratively
    void reverseList() {
        // Step 6.1: Handle empty or single-node list
        if (head == nullptr || head->next == nullptr) {
            cout << "List reversed.\n";
            displayList();
            return;
        }

        // Step 6.2: Initialize 3 pointers for iterative reversal
        Node* prev = nullptr;
        Node* current = head;
        Node* nextNode = nullptr;

        // Step 6.3: Iterate through nodes and reverse links
        while (current != nullptr) {
            nextNode = current->next; // Store next node
            current->next = prev;     // Reverse current node's pointer
            prev = current;           // Move prev one step forward
            current = nextNode;       // Move current one step forward
        }

        // Step 6.4: Update head pointer to the new first node (prev)
        head = prev;
        
        cout << "List reversed iteratively.\n";
        displayList(); // Confirm updated list
    }

    // REQUIREMENT 7: Function to search for a value and display its position
    void searchValue(int val) const {
        Node* temp = head;
        int index = 1; // 1-based position indexing

        // Traverse and check if data matches target value
        while (temp != nullptr) {
            if (temp->data == val) {
                cout << "Value " << val << " found at position (index) " << index << ".\n";
                return;
            }
            temp = temp->next;
            index++;
        }
        
        // If loop completes without finding value
        cout << "Value " << val << " not found in the list.\n";
    }

    // STEP 3: Destructor to automatically free dynamic memory and prevent leaks
    ~SinglyLinkedList() {
        Node* temp = head;
        while (temp != nullptr) {
            Node* nextNode = temp->next;
            delete temp;
            temp = nextNode;
        }
    }
};

// REQUIREMENT 8: Interactive Menu-Driven Interface in main()
int main() {
    SinglyLinkedList list;
    int choice, val;

    // Loop repeatedly until the user chooses to exit (option 8)
    do {
        cout << "\n================ SINGLY LINKED LIST MENU ================\n";
        cout << "1. Insert at Head\n";
        cout << "2. Insert at 3rd Position\n";
        cout << "3. Display List\n";
        cout << "4. Delete Last Node\n";
        cout << "5. Count Nodes\n";
        cout << "6. Reverse List Iteratively\n";
        cout << "7. Search Value\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        // Dispatch user option to appropriate class function
        switch (choice) {
            case 1:
                cout << "Enter integer value to insert at head: ";
                cin >> val;
                list.insertAtHead(val);
                break;

            case 2:
                cout << "Enter integer value to insert at 3rd position: ";
                cin >> val;
                list.insertAtThird(val);
                break;

            case 3:
                list.displayList();
                break;

            case 4:
                list.deleteLast();
                break;

            case 5:
                cout << "Total nodes present: " << list.countNodes() << endl;
                break;

            case 6:
                list.reverseList();
                break;

            case 7:
                cout << "Enter value to search: ";
                cin >> val;
                list.searchValue(val);
                break;

            case 8:
                cout << "Exiting program...\n";
                break;

            default:
                cout << "Invalid choice! Please select a option between 1 and 8.\n";
        }

    } while (choice != 8);

    return 0;
}
