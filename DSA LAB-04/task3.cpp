#include <iostream>
#include <string>
using namespace std;

// Doubly Linked List Node representing a single binary bit
struct Node {
    int bit;        // 0 or 1
    Node* next;     // Pointer to next bit (towards LSB)
    Node* prev;     // Pointer to previous bit (towards MSB)

    Node(int b) {
        bit = b;
        next = nullptr;
        prev = nullptr;
    }
};

class BinaryNumber {
private:
    Node* head; // Points to Most Significant Bit (MSB)
    Node* tail; // Points to Least Significant Bit (LSB)

public:
    BinaryNumber() {
        head = nullptr;
        tail = nullptr;
    }

    // Clean up memory
    ~BinaryNumber() {
        clear();
    }

    void clear() {
        Node* current = head;
        while (current != nullptr) {
            Node* nextNode = current->next;
            delete current;
            current = nextNode;
        }
        head = tail = nullptr;
    }

    // Append bit at tail (LSB side)
    void appendBit(int bit) {
        Node* newNode = new Node(bit);
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    // Prepend bit at head (MSB side) - useful when calculating addition results
    void prependBit(int bit) {
        Node* newNode = new Node(bit);
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    // 1. Store Binary Number from string input
    void loadFromString(string binaryStr) {
        clear();
        for (char c : binaryStr) {
            if (c == '0' || c == '1') {
                appendBit(c - '0');
            }
        }
    }

    // Create a copy of the current DLL
    BinaryNumber copy() const {
        BinaryNumber newNum;
        Node* temp = head;
        while (temp != nullptr) {
            newNum.appendBit(temp->bit);
            temp = temp->next;
        }
        return newNum;
    }

    // Display the binary number grouped in 8-bit blocks
    void display() const {
        if (head == nullptr) {
            cout << "0";
            return;
        }

        // Count total bits to format in 8-bit groups
        int totalBits = 0;
        Node* temp = head;
        while (temp != nullptr) {
            totalBits++;
            temp = temp->next;
        }

        temp = head;
        int bitCount = 0;
        while (temp != nullptr) {
            cout << temp->bit;
            bitCount++;
            if ((totalBits - bitCount) % 8 == 0 && temp->next != nullptr) {
                cout << " ";
            }
            temp = temp->next;
        }
        cout << endl;
    }

    // 2. 1's Complement - Flip all bits
    BinaryNumber onesComplement() const {
        BinaryNumber result;
        Node* temp = head;
        while (temp != nullptr) {
            result.appendBit(temp->bit == 0 ? 1 : 0);
            temp = temp->next;
        }
        return result;
    }

    // 4. Binary Addition using DLL pointers starting from LSB (tail)
    static BinaryNumber add(const BinaryNumber& num1, const BinaryNumber& num2) {
        BinaryNumber result;
        Node* p1 = num1.tail;
        Node* p2 = num2.tail;
        int carry = 0;

        while (p1 != nullptr || p2 != nullptr || carry != 0) {
            int sum = carry;
            if (p1 != nullptr) {
                sum += p1->bit;
                p1 = p1->prev;
            }
            if (p2 != nullptr) {
                sum += p2->bit;
                p2 = p2->prev;
            }

            result.prependBit(sum % 2);
            carry = sum / 2;
        }

        return result;
    }

    // 3. 2's Complement - 1's Complement + 1
    BinaryNumber twosComplement() const {
        BinaryNumber onesComp = onesComplement();
        BinaryNumber one;
        one.appendBit(1);
        return add(onesComp, one);
    }

    // Left shift by appending zeros at the tail
    BinaryNumber shiftLeft(int shiftAmount) const {
        BinaryNumber shifted = copy();
        for (int i = 0; i < shiftAmount; i++) {
            shifted.appendBit(0);
        }
        return shifted;
    }

    // 5. Binary Multiplication using repeated addition + shifting
    static BinaryNumber multiply(const BinaryNumber& num1, const BinaryNumber& num2) {
        BinaryNumber result;
        result.appendBit(0); // Initialize sum as 0

        Node* p2 = num2.tail; // Traverse multiplier from LSB to MSB
        int shiftCount = 0;

        while (p2 != nullptr) {
            if (p2->bit == 1) {
                BinaryNumber shiftedNum1 = num1.shiftLeft(shiftCount);
                result = add(result, shiftedNum1);
            }
            shiftCount++;
            p2 = p2->prev;
        }

        return result;
    }

    // 6. Conversion to Decimal
    long long toDecimal() const {
        long long decimalVal = 0;
        Node* temp = head;
        while (temp != nullptr) {
            decimalVal = (decimalVal * 2) + temp->bit;
            temp = temp->next;
        }
        return decimalVal;
    }
};

int main() {
    string str1, str2;

    cout << "=== Binary Arithmetic using Doubly Linked List ===" << endl;
    cout << "Enter first binary number: ";
    cin >> str1;
    cout << "Enter second binary number: ";
    cin >> str2;

    BinaryNumber b1, b2;
    
    // 1. Store Binary Numbers
    b1.loadFromString(str1);
    b2.loadFromString(str2);

    cout << "\n--------------------------------------------------" << endl;
    cout << "Number 1 (Stored in 8-bit DLL format): ";
    b1.display();
    cout << "Decimal Equivalent: " << b1.toDecimal() << endl;

    cout << "\nNumber 2 (Stored in 8-bit DLL format): ";
    b2.display();
    cout << "Decimal Equivalent: " << b2.toDecimal() << endl;

    // 2. 1's Complement
    cout << "\n--------------------------------------------------" << endl;
    cout << "1's Complement of Number 1: ";
    b1.onesComplement().display();

    // 3. 2's Complement
    cout << "2's Complement of Number 1: ";
    b1.twosComplement().display();

    // 4. Binary Addition
    cout << "\n--------------------------------------------------" << endl;
    BinaryNumber sumResult = BinaryNumber::add(b1, b2);
    cout << "Binary Addition (Num1 + Num2): ";
    sumResult.display();
    cout << "Decimal Result: " << sumResult.toDecimal() << endl;

    // 5. Binary Multiplication
    cout << "\n--------------------------------------------------" << endl;
    BinaryNumber mulResult = BinaryNumber::multiply(b1, b2);
    cout << "Binary Multiplication (Num1 * Num2): ";
    mulResult.display();
    cout << "Decimal Result: " << mulResult.toDecimal() << endl;

    return 0;
}
