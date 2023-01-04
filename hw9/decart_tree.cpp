#include <iostream>
#include <ctime>

struct Node {
    Node* left {nullptr};
    Node* right {nullptr};
    int32_t x {INT32_MIN};
    int32_t y {INT32_MIN};

    Node(int32_t cur_x, int32_t cur_y) {
        x = cur_x;
        y = cur_y;
    }
};

void print_tree(Node* node) {
    if (node != nullptr) {
        print_tree(node->left);
        std::cout << node->x << " ";
        print_tree(node->right);
    }
}

Node* exists(Node* node, int32_t cur_x) {
    if (node == nullptr) {
        return nullptr;
    }
    if (cur_x == node->x) {
        return node;
    }
    if (cur_x > node->x) {
        return exists(node->right, cur_x);
    }
    else if (cur_x < node->x) {
        return exists(node->left, cur_x);
    }
}

Node* next_min(Node* node, int32_t cur_x) {
    Node* target_node = nullptr;
    while (node != nullptr) {
        if (cur_x < node->x) {
            target_node = node;
            node = node->left;
        }
        else {
            node = node->right;
        }
    }
    return target_node;
}

Node* prev_max(Node* node, int32_t cur_x) {
    Node* target_node = nullptr;
    while (node != nullptr) {
        if (cur_x > node->x) {
            target_node = node;
            node = node->right;
        }
        else {
            node = node->left;
        }
    }
    return target_node;
}

std::pair<Node*, Node*> split(Node* node, int32_t cur_x) {
    if (node == nullptr) {
        return std::make_pair(nullptr, nullptr);
    }
    if (node->x > cur_x) {
        auto subtrees = split(node->left, cur_x);
        node->left = subtrees.second;
        return std::make_pair(subtrees.first, node);
    }
    else {
        auto subtrees = split(node->right, cur_x);
        node->right = subtrees.first;
        return std::make_pair(node, subtrees.second);
    }
}

Node* merge(Node* subtree1, Node* subtree2) {
    if (subtree1 == nullptr) {
        return subtree2;
    }
    if (subtree2 == nullptr) {
        return subtree1;
    }
    if (subtree1->y > subtree2->y) {
        subtree1->right = merge(subtree1->right, subtree2);
        return subtree1;
    }
    else {
        subtree2->left = merge(subtree1, subtree2->left);
        return subtree2;
    }
}

Node* insert(Node* node, int32_t cur_x, int32_t cur_y) {
    auto subtrees = split(node, cur_x);
    Node* new_node = new Node(cur_x, cur_y);
    subtrees.first = merge(subtrees.first, new_node);
    node = merge(subtrees.first, subtrees.second);
    return node;
}

Node* drop(Node* node, int32_t cur_x) {
    auto subtrees = split(node, cur_x);
    auto temp_split = split(subtrees.first, cur_x - 1);
    node = merge(temp_split.first, subtrees.second);
    delete temp_split.second;
    return node;
}

int main() {
    int32_t x;
    Node* tmp_node;
    std::string command;
    std::string is_exists;
    Node* decart_tree = nullptr;
    srand(time(nullptr));

    while(std::cin >> command >> x) {
        if (command == "qwe") { break; }
        if (command == "insert") {
            decart_tree = insert(decart_tree, x, rand() + 1);
        }
        if (command == "exists") {
            is_exists = "false";
            if (exists(decart_tree, x) != nullptr) {
                is_exists = "true";
            }
            std::cout << is_exists << '\n';
        }
        if (command == "delete") {
            decart_tree = drop(decart_tree, x);
        }
        if (command == "prev") {
            tmp_node = prev_max(decart_tree, x);
            if (tmp_node != nullptr) {
                std::cout << tmp_node->x << '\n';
            }
            else {
                std::cout << "none" << '\n';
            }
        }
        if (command == "next") {
            tmp_node = next_min(decart_tree, x);
            if (tmp_node != nullptr) {
                std::cout << tmp_node->x << '\n';
            }
            else {
                std::cout << "none" << '\n';
            }
        }
    }
    return 0;
}

