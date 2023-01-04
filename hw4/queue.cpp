#include <iostream>
#include <string>

class Cyclic_vector {
public:
    int capacity;
    int* elements;
    int begin;
    int size;

    Cyclic_vector () {
        begin = 0;
        size = 0;
        capacity = 2;
        elements = new int[2];
    }

    void change_cur_capacity(int new_capacity) {
        int* new_elements = new int[new_capacity];
        for (int i = 0; i < size; i++) {
            new_elements[i] = elements[(i + begin) % capacity];
        }
        delete[] elements;
        elements = new_elements;
        begin = 0;
    }

    void ensure_capacity() {
        int new_capacity = capacity * 2;
        change_cur_capacity(new_capacity);
        capacity *= 2;
    }

    void add(int x) {
        if (size >= capacity) {
            ensure_capacity();
        }
        elements[(size + begin) % capacity] = x;
        size++;
    }

    void decrease_capacity() {
        int new_capacity = capacity / 2;
        change_cur_capacity(new_capacity);
        capacity /= 2;
    }

    int erase() {
        int erase_value = elements[begin];
        if (size < capacity / 4) {
            decrease_capacity();
        }
        begin++;
        size--;
        begin %= capacity;
        return erase_value;
    }
};

class Queue{
    Cyclic_vector vector {};
public:
    void push(int x) {
        vector.add(x);
    }

    int pop() {
        return vector.erase();
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int m;
    std::string x;
    Queue queue;
    int erase_value;

    std::cin >> m;
    for(int i = 0; i < m; i++) {
        std::cin >> x;
        if (x == "+") {
            std::cin >> x;
            queue.push(stoi(x));
        }
        else {
            erase_value = queue.pop();
            std::cout << erase_value << '\n';
        }
    }

    return 0;
}
