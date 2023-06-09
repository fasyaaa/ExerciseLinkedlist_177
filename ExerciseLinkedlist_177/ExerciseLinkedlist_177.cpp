#include <iostream>
#include <string>
using namespace std;
class Node {
public:
    int rollNumber;
    string name;
    Node* next;
};
class CircularLinkedList {
private:
    Node* LAST;
public:
    CircularLinkedList() {
        LAST = NULL;
    }
    void addNode();
    bool search(int rollno, Node** previous, Node** current);
    bool listEmpty();
    bool delNode();
    void traverse();
};

void CircularLinkedList::addNode() {
    int rollNomer;
    string name;

    //Beginning of the list
    cout << "Enter the roll number : ";
    cin >> rollNomer;                  //a2 Assign value to the data field of the new node
    cout << "Enter name : ";
    cin >> name;

    Node* newNode = new Node();         //a1 Allocate memory for the new node.
    newNode->rollNumber = rollNomer;         
    newNode->name = name;

    if (LAST == NULL) {
        newNode->next = newNode;        
        LAST = newNode;                 
    }
    else {
        Node* MUHAMMAD = LAST->next;            //b1 Make current point to the first node (current diganti nama depan)
        Node* FIRMANSYAH = NULL;                //b2 Make previous point to NULL (previous diganti nama belakanng)

        if (rollNomer < MUHAMMAD->rollNumber) { 
            newNode->next = MUHAMMAD;
            LAST->next = newNode;               //a4 Make the next field of LAST point to the new node
        }
        else {  
            while (MUHAMMAD->rollNumber < rollNomer && MUHAMMAD != LAST) {      //b3 Repeat steps 4 and 5 until current.info > newnode.info or previous = LAST
                FIRMANSYAH = MUHAMMAD;       //b4 Make previous point to current.
                MUHAMMAD = MUHAMMAD->next;  //b5 Make current point to the next node in sequence.
            }

            if (MUHAMMAD == LAST && MUHAMMAD->rollNumber < rollNomer) {  
                newNode->next = LAST->next; //c3 Make the next field of the new node point to the successor of LAST
                LAST->next = newNode;   //c4 Make the next field of LAST point to the new node.
                LAST = newNode;  //c5 Mark LAST point to the new node
            }
            else {  
                newNode->next = MUHAMMAD;          
                FIRMANSYAH->next = newNode;
            }
        }
    }
}
bool CircularLinkedList::search(int rollno, Node** FIRMANSYAH, Node** MUHAMMAD) {
    *FIRMANSYAH = LAST->next;           //previous
    *MUHAMMAD = LAST->next;             //current
    while (*MUHAMMAD != LAST) {
        if (rollno == (*MUHAMMAD)->rollNumber) {
            return true;
        }
        *FIRMANSYAH = *MUHAMMAD;
        *MUHAMMAD = (*MUHAMMAD)->next;
    }
    if (rollno == LAST->rollNumber) {
        return true;
    }
    else {
        return false;
    }
}
bool CircularLinkedList::listEmpty() {
    return LAST == NULL;
}
bool CircularLinkedList::delNode() { 
    int rollNumber;

    cout << "Enter roll number of the node to be deleted: ";
    cin >> rollNumber;

    if (listEmpty()) {
        cout << "List is empty. Cannot delete node." << endl;
        return false;
    }

    Node* FIRMANSYAH = LAST;       //b1 Make previous point to the successor of LAST.
    Node* MUHAMMAD = LAST->next;    //b2 Make current point to the successor of LAST.

    if (MUHAMMAD->rollNumber == rollNumber && MUHAMMAD == LAST) {  //a1 If the node to be deleted is the only node in the list
        delete MUHAMMAD;
        LAST = NULL;  // Mark LAST as NULL
        return true; // exit
    }

    while (MUHAMMAD->rollNumber != rollNumber && MUHAMMAD != LAST) { //b3 Repeat steps 4 and 5 until either the node is found, or previous = LAST
        FIRMANSYAH = MUHAMMAD; //b4 Make previous point to current.
        MUHAMMAD = MUHAMMAD->next; //b5 Make current point to the next node in sequence.
    }

    if (MUHAMMAD->rollNumber != rollNumber) {  
        cout << "Node with roll number " << rollNumber << " not found." << endl;
        return false;
    }


    FIRMANSYAH->next = MUHAMMAD->next; //c1 Make previous point to the successor of LAST.
                                       

    if (MUHAMMAD == LAST)        //c2 Make current point to LAST.
        LAST = FIRMANSYAH;      //c3 Make the next field of previous point to the successor of LAST. c4 Mark previous as LAST.

    delete MUHAMMAD;        //c5 Release the memory for the node marked as current.
    return true;
}
void CircularLinkedList::traverse() {
        if (listEmpty()) {

            cout << "\nList is empty\n";
        }
        else {
            cout << "\nRecords in the list are:\n";
            Node* currentNode = LAST->next;

            while (currentNode != LAST) {
                cout << currentNode->rollNumber << " " << currentNode->name << endl;
                    currentNode = currentNode->next;
            }
                cout << LAST->rollNumber << " " << LAST->name << endl;
        }
    }
    int main() {
        CircularLinkedList obj;
        while (true) {
            try {
                cout << "\nMenu" << endl;
                cout << "1. Add a record to the list" << endl;
                cout << "2. Delete a record from the list" << endl; 
                cout << "3. View all the records in the list" << endl; 
                cout << "4. Exit" << endl;
                cout << "\nEnter your choice (1-5): ";
                char ch;
                cin >> ch;
                switch (ch) {
                case '1': {
                    obj.addNode();
                    break;
                }
                case '2': {
                    obj.delNode();
                    break;
                }
                case '3': {
                    obj.traverse();
                    break; }
                case '4': {
                    return 0;
                }
                default: {
                    cout << "Invalid option" << endl;
                    break; }
                }
            }
            catch (exception& e) {

                cout << e.what() << endl;
            }
        }
        return 0;
    }