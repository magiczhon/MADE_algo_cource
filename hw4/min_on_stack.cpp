#include <iostream>

class Node {
public:
    Node(int x, Node* ptr) {
        data = x;
        next = ptr;
    }
    Node* next;
    int data;
    int min = INT32_MAX;
};

class Linked_list {
public:
    Node* head = nullptr;
    Node* tail = nullptr;
    int size = 0;

    void remove(int index) {
        if (size == 0 or index < 0 or index >= size) {
            return;
        }
        if (size == 1) {
            delete head;
            head = nullptr;
            tail = nullptr;
        }
        else {
            Node* prev = head;
            Node* cur = prev->next;
            int j = 1;
            while (j < index) {
                prev = cur;
                cur = prev->next;
                j++;
            }
            prev->next = cur->next;
            if (cur == tail) {
                tail = prev;
            }
            delete cur;
        }
        size--;
    };

    void print() {
        Node* cur = head;
        while (cur != nullptr) {
            std::cout << cur->data << " ";
            cur = cur->next;
        }
        std::cout << "\n";
    };

    void push_back(int x) {
        Node* new_node = new Node(x, nullptr);

        if (size == 0) {
            new_node->min = x;
            head = new_node;
            tail = new_node;
        }
        else {
            new_node->min = (x < tail->min) ? x : tail->min;
            tail->next = new_node;
            tail = new_node;
        }
        size++;
    }

    void push_front(int x) {
        Node* new_node = new Node(x, head);
        if (head != nullptr) {
            new_node->min = (x < head->min) ? x : head->min;
        }
        else {
            new_node->min = x;
        }
        head = new_node;
        size++;
    }

    void pop_front() {
        if (head == nullptr or head->next == nullptr) {
            head = nullptr;
        }
        else {
            Node* prev = head;
            head = head->next;
            delete prev;
        }
        size--;
    }
};

class Stack {
    Linked_list stack;
public:
    void push(int x) {
        stack.push_front(x);
    }

    void pop() {
        stack.pop_front();
    }

    int get_min() {
        return stack.head->min;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    Stack stack;

    std::cin >> n;
    int type_operation;
    int x;
    for(int _ = 0; _ < n; _++) {
        std::cin >> type_operation;
        switch (type_operation) {
            case 1: {
                std::cin >> x;
                stack.push(x);
                break;
            }
            case 2: {
                stack.pop();
                break;
            }
            case 3: {
                std::cout << stack.get_min() << '\n';
                break;
            }
        }
    }

    return 0;
}