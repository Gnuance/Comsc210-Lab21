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
        7. Update both of the print() methods that are in the class. Both should display the text "List is empty" if the list is empty;
                otherwise, output the list as shown in the sample output below.

    Design decisions:

*/

#include <iostream>
#include <ctime> // For time needed by srand
#include <array> // For an array that actually has bounds checking
using namespace std;

// Class represents individual goats
class Goat
{
private:
    string name;
    string color;
    int age;

public:
    // Public constant variables
    static const int NUM_ELEMENTS = 15;
    static const int AGE_MIN = 1;
    static const int AGE_MAX = 20;
    static const array<string, NUM_ELEMENTS> NAMES;
    static const array<string, NUM_ELEMENTS> COLORS;
    Goat *prev;
    Goat *next;
    Goat();
    Goat(string, string, int);
    string getName() { return name; };
    string getColor() { return color; };
    int getAge() { return age; };
    string &setRandomName()
    {
        name = NAMES.at(rand() % NAMES.size());
        return name;
    };
    string &setRandomColor()
    {
        color = COLORS.at(rand() % COLORS.size());
        return color;
    };
    int &setRandomAge()
    {
        age = rand() % (AGE_MAX - AGE_MIN + 1) + AGE_MIN;
        return age;
    };
    ~Goat();
};

// Initialize array variables for names and colors. Apparently must be done outside of class... Ugh, really c++???
const array<string, Goat::NUM_ELEMENTS> Goat::NAMES = {"Nibbles", "Billy", "Clover", "Pogo", "Gigi", "Biscuit", "Snickers", "Waffle", "Tater Tot", "Daisy", "Pippin", "Chomper", "Marshmallow", "Goaty McGoatface", "Pebbles"};
const array<string, Goat::NUM_ELEMENTS> Goat::COLORS = {"Red", "Blue", "Green", "Yellow", "Purple", "Orange", "Pink", "Cyan", "Magenta", "Teal", "Lime", "Brown", "Gray", "Lavender", "Coral"};

Goat::Goat()
    : prev(nullptr), next(nullptr)
{
    setRandomName();
    setRandomColor();
    setRandomAge();
}

Goat::Goat(string goatName, string goatColor, int goatAge)
    : prev(nullptr), next(nullptr), name(goatName), color(goatColor), age(goatAge)
{
}

Goat::~Goat()
{
}

// Class represents a goat herd with pointers to the head and tail of the herd
class Herd
{
private:
    Goat *head;
    Goat *tail;
    static const string EMPTY_HERD_MESSAGE;

public:
    // constructor
    Herd()
    {
        head = nullptr;
        tail = nullptr;
    }
    Herd(int goatAge, string goatName, string goatColor)
        : head(nullptr), tail(nullptr) {}

    void push_back(const Goat &g)
    {
        Goat *newGoat = new Goat(g);
        if (!tail) // if there's no tail, the list is empty
            head = tail = newGoat;
        else
        {
            tail->next = newGoat;
            newGoat->prev = tail;
            tail = newGoat;
        }
    }

    void push_front(const Goat &g)
    {
        Goat *newGoat = new Goat(g);
        if (!head) // if there's no head, the list is empty
            head = tail = newGoat;
        else
        {
            newGoat->next = head;
            head->prev = newGoat;
            head = newGoat;
        }
    }

    void insert_after(const Goat &g, int position)
    {
        if (position < 0)
        {
            cout << "Position must be >= 0." << endl;
            return;
        }

        Goat *newGoat = new Goat(g);
        if (!head)
        {
            head = tail = newGoat;
            return;
        }

        Goat *temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;

        if (!temp)
        {
            cout << "Position exceeds list size. Goat not inserted.\n";
            delete newGoat;
            return;
        }

        newGoat->next = temp->next;
        newGoat->prev = temp;
        if (temp->next)
            temp->next->prev = newGoat;
        else
            tail = newGoat; // Inserting at the end
        temp->next = newGoat;
    }

    void delete_Goat(const Goat &g)
    {
        if (!head)
            return; // Empty list

        Goat *temp = head;
        while (temp && temp != &g)
            temp = temp->next;

        if (!temp)
            return; // Value not found

        if (temp->prev)
        {
            temp->prev->next = temp->next;
        }
        else
        {
            head = temp->next; // Deleting the head
        }

        if (temp->next)
        {
            temp->next->prev = temp->prev;
        }
        else
        {
            tail = temp->prev; // Deleting the tail
        }

        delete temp;
    }

    void print()
    {
        Goat *current = head;
        int count = 0; // Counter for formatting

        if (!current)
        {
            cout << EMPTY_HERD_MESSAGE << endl;
            return;
        }
        while (current)
        {
            if (count > 0)
                cout << ", "; // Add ',' and space for any additional items
            cout << current->getName();
            current = current->next;
            count++;
        }
        cout << endl;
    }

    void print_reverse()
    {
        Goat *current = tail;
        int count = 0; // Counter for formatting

        if (!current)
        {
            cout << EMPTY_HERD_MESSAGE << endl;
            return;
        }
        while (current)
        {
            if (count > 0)
                cout << ", "; // Add ',' and space for any additional items
            cout << current->getName() << " ";
            current = current->prev;
            count++;
        }
        cout << endl;
    }

    ~Herd()
    {
        while (head)
        {
            Goat *temp = head;
            head = head->next;
            delete temp;
        }
    }
};

const string Herd::EMPTY_HERD_MESSAGE = "Herd list is empty. Your flock is gone. Time for a career change.";

// Driver program
int main()
{
    const int MIN_LS = 5, MAX_LS = 20;                        // Constants for list size and records
    srand(static_cast<unsigned int>(time(nullptr)));          // Return current time as non-negative for srand
    Goat goatimusPrime;                                       // Represents a goat, but not just any goat. The epitome of the goats. What every goat stives to be
    Goat *goatPtr;                                            // Pointer to create goat objects with parameters
    Herd herdList;                                            // Represents entire herd of goats
    int numOfGoats = rand() % (MAX_LS - MIN_LS + 1) + MIN_LS; // Size of goat herd

    // For rand() num, create goat with all attributes, and push into herd
    for (int i = 0; i < numOfGoats / 2; ++i)
    {
        goatimusPrime.setRandomName();
        goatimusPrime.setRandomColor();
        goatimusPrime.setRandomAge();
        herdList.push_back(goatimusPrime);
        goatPtr = new Goat(goatPtr->setRandomName(), goatPtr->setRandomColor(), goatPtr->setRandomAge());
        herdList.push_back(*goatPtr);
    }

    // Print goat herd list forward
    cout << endl
         << "List forward: ";
    herdList.print();

    // Print goat herd list backwards
    cout << endl
         << "List backward: ";
    herdList.print_reverse();

    cout << endl
         << "Deleting list, then trying to print.";
    herdList.~Herd();
    cout << endl
         << "List forward: ";
    herdList.print();

    return 0;
}