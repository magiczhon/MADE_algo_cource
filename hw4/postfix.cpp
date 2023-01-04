#include <iostream>

const char MAX_RANGE = '9';
const char MIN_RANGE = '0';

class Vector {
public:
    int size = 0;
    int capacity;
    int* elements;

    void ensure_capacity() {
        capacity *= 2;
        int* new_elements = new int[capacity];
        for (int i = 0; i < size; i++) {
            new_elements[i] = elements[i];
        }
        delete elements;
        elements = new_elements;
    }

    void add(int x) {
        if (size == 0) {
            capacity = 1;
            elements = new int[1];
            elements[0] = x;
            size++;
            return;
        }
        if (size + 1 > capacity) {
            ensure_capacity();
        }
        elements[size] = x;
        size++;
    }

    void decrease_capacity() {
        capacity /= 4;
        int* new_elements = new int[capacity];
        for (int i = 0; i < size; i++) {
            new_elements[i] = elements[i];
        }
        delete elements;
        elements = new_elements;
    }

    int erase() {
        int erase_el = elements[size - 1];
        if (size - 1 < capacity / 4) {
            decrease_capacity();
        }
        size--;
        return erase_el;
    }
};

class Stack {
    Vector stack;
public:
    void push(int x) {
        stack.add(x);
    }

    int pop() {
        return stack.erase();
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    char x;
    int first_operand;
    int second_operand;
    Stack stack;

    while(std::cin >> x) {
        if (x == '/')
            break;
        if (MIN_RANGE <= x and x <= MAX_RANGE) {
            stack.push(x - MIN_RANGE);
        }
        else {
            switch (x) {
                case '+': {
                    first_operand = stack.pop();
                    second_operand = stack.pop();
                    stack.push(second_operand + first_operand);
                    break;
                }
                case '-': {
                    first_operand = stack.pop();
                    second_operand = stack.pop();
                    stack.push(second_operand - first_operand);
                    break;
                }
                case '*': {
                    first_operand = stack.pop();
                    second_operand = stack.pop();
                    stack.push(second_operand * first_operand);
                    break;
                }
            }
        }
    }
    int res = stack.pop();
    std:: cout << res;
    return 0;
}
