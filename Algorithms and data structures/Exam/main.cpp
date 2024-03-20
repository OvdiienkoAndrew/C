#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;

    Node(int val) : data(val), next(nullptr) {}
};

void displayCircularList(Node* head) {
    if (head == nullptr) {
        cout << "Список порожній." << endl;
        return;
    }

    Node* current = head;
    do {
        cout << current->data << " ";
        current = current->next;
    } while (current != head);
    cout << endl;
}

Node* createCircularList(int n) {
    if (n <= 0)
        return nullptr;

    Node* head = new Node(1);
    Node* current = head;

    for (int i = 2; i <= n; i++) {
        current->next = new Node(i);
        current = current->next;
    }

    current->next = head;

    return head;
}

void deleteCircularList(Node*& head) {
    if (head == nullptr)
        return;

    Node* current = head;
    Node* nextNode;

    do {
        nextNode = current->next;
        delete current;
        current = nextNode;
    } while (current != head);

    head = nullptr;
}

int main() {
    int numberOfElements = 10;

    cout << "Kільцевий список: ";
    Node* circularList = createCircularList(numberOfElements);
    displayCircularList(circularList);
    deleteCircularList(circularList);
    cout << "Після видалення: ";
    displayCircularList(circularList);
    circularList = createCircularList(20);
    displayCircularList(circularList);
    return 0;
}
