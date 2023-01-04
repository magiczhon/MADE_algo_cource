#include <iostream>

struct Node {
    Node* left {nullptr};
    Node* right {nullptr};
    int32_t key {INT32_MIN};
    int32_t h {0};

    Node(int32_t k) {
        key = k;
        h = 1;
    }
};

void print_tree(Node* node) {
    if (node != nullptr) {
        print_tree(node->left);
        std::cout << node->key << " ";
        print_tree(node->right);
    }
}

Node* find_max_key (Node* node) {
    while (node->right != nullptr) {
        node = node->right;
    }
    return node;
}

Node* exists(Node* node, int32_t k) {
    if (node == nullptr) {
        return nullptr;
    }
    if (k == node->key) {
        return node;
    }
    if (k > node->key) {
        return exists(node->right, k);
    }
    else if (k < node->key) {
        return exists(node->left, k);
    }
}

Node* next_min(Node* node, int32_t k) {
    Node* target_node = nullptr;
    while (node != nullptr) {
        if (k < node->key) {
            target_node = node;
            node = node->left;
        }
        else {
            node = node->right;
        }
    }
    return target_node;
}

Node* prev_max(Node* node, int32_t k) {
    Node* target_node = nullptr;
    while (node != nullptr) {
        if (k > node->key) {
            target_node = node;
            node = node->right;
        }
        else {
            node = node->left;
        }
    }
    return target_node;
}

int32_t get_h(Node* node) {
    if (node == nullptr) {
        return 0;
    }
    return node->h;
}

int32_t get_balance(Node* node) {
    if (node == nullptr) {
        return 0;
    }
    return get_h(node->left) - get_h(node->right);
}

void fix_h (Node* node) {
    node->h = std::max(get_h(node->left), get_h(node->right)) + 1;
};

Node* small_rotate_left(Node* first_node) {
    Node* second_node = first_node->left;
    first_node->left = second_node->right;
    second_node->right = first_node;
    fix_h(first_node);
    fix_h(second_node);
    return second_node;
}

Node* small_rotate_right(Node* first_node) {
    Node* second_node = first_node->right;
    first_node->right = second_node->left;
    second_node->left = first_node;
    fix_h(first_node);
    fix_h(second_node);
    return second_node;
}

Node* balance(Node* node) {
    fix_h(node);
    if (get_balance(node) == 2) {
        if (get_balance(node->right) < 0) {
            node->right = small_rotate_right(node->right);
        }
        return small_rotate_left(node);
    }
    else if (get_balance(node) == -2) {
        if (get_balance(node->left) > 0) {
            node->left = small_rotate_left(node->left);
        }
        return small_rotate_right(node);
    }
    else {
        return node;
    }
}

Node* insert(Node* node, int32_t k) {
    if (node == nullptr) {
        return new Node(k);
    }
    if (k == node->key) {
        return node;
    }
    if (k > node->key) {
        node->right = insert(node->right, k);
    }
    else if (k < node->key) {
        node->left = insert(node->left, k);
    }
    return balance(node);
}

Node* drop(Node* node, int32_t k) {
    if (node == nullptr) {
        return nullptr;
    }
    if (k < node->key) {
        node->left = drop(node->left, k);
    }
    else if (k > node->key) {
        node->right = drop(node->right, k);
    }
    else if (node->left == nullptr and node->right == nullptr) {
        delete node;
        return nullptr;
    }
    else if (node->left == nullptr) {
        Node* cur_node = node;
        node = node->right;
        delete cur_node;
    }
    else if (node->right == nullptr) {
        Node* cur_node = node;
        node = node->left;
        delete cur_node;
    }
    else {
        Node* max_key_node = find_max_key(node->left);
        node->key = max_key_node->key;
        node->left = drop(node->left, node->key);
    }
    return balance(node);
}

int main() {
    int32_t x;
    Node* tmp_node;
    std::string command;
    std::string is_exists;
    Node* tree = nullptr;

    while(std::cin >> command >> x) {
        if (command == "insert") {
            tree = insert(tree, x);
        }
        if (command == "exists") {
            is_exists = "false";
            if (exists(tree, x) != nullptr) {
                is_exists = "true";
            }
            std::cout << is_exists << '\n';
        }
        if (command == "delete") {
            tree = drop(tree, x);
        }
        if (command == "prev") {
            tmp_node = prev_max(tree, x);
            if (tmp_node != nullptr) {
                std::cout << tmp_node->key << '\n';
            }
            else {
                std::cout << "none" << '\n';
            }
        }
        if (command == "next") {
            tmp_node = next_min(tree, x);
            if (tmp_node != nullptr) {
                std::cout << tmp_node->key << '\n';
            }
            else {
                std::cout << "none" << '\n';
            }
        }
    }
    return 0;
}