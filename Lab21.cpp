/*  Lab 21: Modifying dll demo to create a goat class
    Objectives: Amend the code as follows:
        0. Write a class Goat that has these private member variables:
            - age (int)
            - name (string)
            - color (string)
            - names[] - a string array of 15 names. Use the replit AI feature to develop a quick list of names.
            - colors[] - a string array of 15 colors. Use AI again.
        1. The Goat class will have two constructors, as expected:
            + The default constructor will randomly assign:
                - an age, 1-20
                - a name, randomly selected from the 15-element names[] array
                - a color, randomly selected from the 15-element colors[] array
        2. The parameter constructor will be a typical 3-element parameter setup.
        3. Modify the DoublyLinkedList class's push_front() and push_back() functions such that it has a Goat object as a parameter, rather than an int. 
        4. In main(), create a DoublyLinkedList object. Append to it a random number of Goat objects, range 5-20 or so.
        5. In main(), call your methods to print both forward and backward to show the proper traversals.
        6. Use srand(time(0)); as one of your first lines in main() to randomize your random numbers.
        7. Update both of the print() methods that are in the class. Both should display the text "List is empty" if the list is empty; otherwise, output the list as shown in the sample output below.

    Design decisions:
        
*/

#include <iostream>
#include <ctime> // For time needed by srand
using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

class DoublyLinkedList {
private:
    struct Node {
        int age;
        string name;
        string color;
        Node* prev;
        Node* next;
        Node(int val, Node* p = nullptr, Node* n = nullptr) {
            data = val; 
            prev = p;
            next = n;
        }
    };

    Node* head;
    Node* tail;

public:
    // constructor
    DoublyLinkedList() { head = nullptr; tail = nullptr; }
    DoublyLinkedList(int goatAge, string goatName, string goatColor)
    : head(nullptr), tail(nullptr), age(goatAge),  {}

    void push_back(int value) {
        Node* newNode = new Node(value);
        if (!tail)  // if there's no tail, the list is empty
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void push_front(int value) {
        Node* newNode = new Node(value);
        if (!head)  // if there's no head, the list is empty
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    void insert_after(int value, int position) {
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }

        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
            return;
        }

        Node* temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;

        if (!temp) {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }

        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next)
            temp->next->prev = newNode;
        else
            tail = newNode; // Inserting at the end
        temp->next = newNode;
    }

    void delete_node(int value) {
        if (!head) return; // Empty list

        Node* temp = head;
        while (temp && temp->data != value)
            temp = temp->next;

        if (!temp) return; // Value not found

        if (temp->prev) {
            temp->prev->next = temp->next;
        } else {
            head = temp->next; // Deleting the head
        }

        if (temp->next) {
            temp->next->prev = temp->prev;
        } else {
            tail = temp->prev; // Deleting the tail
        }

        delete temp;
    }

    void print() {
        Node* current = head;
        if (!current) return;
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) return;
        while (current) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

// Driver program
int main() {
    srand(static_cast<unsigned int>(time(nullptr))); // Return current time as non-negative for srand
    DoublyLinkedList list;
    int size = rand() % (MAX_LS-MIN_LS+1) + MIN_LS;

    for (int i = 0; i < size; ++i)
        list.push_back(rand() % (MAX_NR-MIN_NR+1) + MIN_NR);
    cout << "List forward: ";
    list.print();

    cout << "List backward: ";
    list.print_reverse();

    cout << "Deleting list, then trying to print.\n";
    list.~DoublyLinkedList();
    cout << "List forward: ";
    list.print();

    return 0;
}
