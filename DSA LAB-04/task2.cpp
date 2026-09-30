#include <iostream>
using namespace std;

// Each node represents a person in the circle
struct Node {
    int id;       // Person ID (integer)
    Node* next;   // Pointer to the next person (circular linkage)

    Node(int val) {
        id = val;
        next = nullptr;
    }
};

class JosephusSimulation {
private:
    Node* head;

public:
    JosephusSimulation() {
        head = nullptr;
    }

    // 3a. Create Circle - Build a circular linked list of N people
    void createCircle(int n) {
        if (n <= 0) return;

        head = new Node(1);
        Node* prev = head;

        // Assign IDs from 2 up to N
        for (int i = 2; i <= n; i++) {
            Node* newNode = new Node(i);
            prev->next = newNode;
            prev = newNode;
        }
        
        // Connect the last person back to the first to complete the circle
        prev->next = head; 
        cout << "Circle of " << n << " people created successfully." << endl;
    }

    // 3b, 3c, 3d. Elimination Process, Display Eliminated Order, and Display Survivor
    void runSimulation(int k) {
        if (head == nullptr) {
            cout << "The circle is empty." << endl;
            return;
        }

        Node* current = head;
        Node* prev = nullptr;

        // First, locate the last node so we can update links properly when eliminating the head
        while (current->next != head) {
            current = current->next;
        }
        prev = current; 
        current = head; 

        cout << "\nElimination Order: ";
        
        // Continue eliminating until only one person remains (current->next == current)
        while (current->next != current) {
            
            // Skip k-1 people to find the k-th person
            for (int count = 1; count < k; count++) {
                prev = current;
                current = current->next;
            }

            // Print the ID of the person being eliminated
            cout << current->id << " ";

            // Update the links to remove the eliminated person from the circle
            prev->next = current->next;
            
            // Delete the node
            Node* temp = current;
            current = prev->next; // Move current to the next person in line
            delete temp;
        }

        // The loop finishes when only one person is left
        cout << "\n\nSurvivor: Person " << current->id << " is the last one remaining!" << endl;

        // Clean up the final surviving node
        delete current;
        head = nullptr;
    }
};

int main() {
    int n, k;

    // 1. Input Requirements
    cout << "--- Josephus Problem Simulation ---" << endl;
    cout << "Enter the total number of people (N): ";
    cin >> n;
    
    cout << "Enter the step count for elimination (k): ";
    cin >> k;

    JosephusSimulation game;
    
    // Build the circle and run the simulation
    game.createCircle(n);
    game.runSimulation(k);

    return 0;
}
