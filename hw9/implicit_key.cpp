#include <iostream>
#include <ctime>

class Decart_tree {
public:
    struct Node {
        int32_t x;
        int32_t y;
        int32_t size;
        Node* left;
        Node* right;
        bool is_reversed;

        Node() {
            x = 0;
            y = 0;
            size = 1;
            left = nullptr;
            right = nullptr;
            is_reversed = false;
        }

        Node(int32_t cur_x, int32_t cur_y) {
            x = cur_x;
            y = cur_y;
            size = 1;
            left = nullptr;
            right = nullptr;
            is_reversed = false;
        }

        Node(const Node& copy) {
            x = copy.x;
            y = copy.y;
            size = copy.size;
            left = copy.left;
            right = copy.right;
            is_reversed = copy.is_reversed;
        }
    };

    Node* root;

    Decart_tree() {
        root = nullptr;
    }

    int32_t get_size(Node* p) {
        if (p == nullptr) {
            return 0;
        }
        else {
            return p->size;
        }
    }

    void fix_size(Node* p) {
        p->size = get_size(p->left) + get_size(p->right) + 1;
    }

    void print_tree(Node* vertice) {
        if (vertice != nullptr) {
            vertice = reverse(vertice);
            print_tree(vertice->left);
            std::cout << vertice->x << ' ';
            print_tree(vertice->right);
        }
    }

    std::pair<Node*, Node*> split(Node* vertice, int32_t x) {
        vertice = reverse(vertice);
        if (vertice == nullptr) {
            return std::make_pair(nullptr, nullptr);
        }
        else if (get_size(vertice->left) >= x) {
            auto t = split(vertice->left, x);
            vertice->left = t.second;
            fix_size(vertice);
            return std::make_pair(t.first, vertice);
        }
        else {
            auto t = split(vertice->right, x - get_size(vertice->left) - 1);
            vertice->right = t.first;
            fix_size(vertice);
            return std::make_pair(vertice, t.second);
        }
    }

    Node* merge(std::pair<Node*, Node*> t) {
        t.first = reverse(t.first);
        t.second = reverse(t.second);
        if (t.first == nullptr) {
            return t.second;
        }
        else if (t.second == nullptr) {
            return t.first;
        }
        else if (t.first->y > t.second->y) {
            t.first->right = merge(std::make_pair(t.first->right, t.second));
            fix_size(t.first);
            return t.first;
        }
        else {
            t.second->left = merge(std::make_pair(t.first, t.second->left));
            fix_size(t.second);
            return t.second;
        }
    }

    Node* insert(Node* vertice, int32_t i, int32_t x, int32_t y) {
        auto t = split(vertice, i);
        Node* new_node = new Node(x, y);
        Node* t1 = merge(std::make_pair(t.first, new_node));
        return merge(std::make_pair(t1, t.second));
    }

    Node* part_reverse(Node* vertice, int left, int right) {
        auto t2 = split(vertice, right);
        auto t1 = split(t2.first, left - 1);
        t1.second->is_reversed ^= true;
        auto t12 = merge(t1);
        return merge(std::make_pair(t12, t2.second));
    }

    Node* reverse(Node* vertice) {
        if (vertice == nullptr) {
            return nullptr;
        }
        else if (vertice->is_reversed) {
            vertice->is_reversed = false;
            std::swap(vertice->left, vertice->right);
            if (vertice->left != nullptr) {
                vertice->left->is_reversed ^= true;
            }
            if (vertice->right != nullptr) {
                vertice->right->is_reversed ^= true;
            }
        }
        return vertice;
    }
};

int32_t main()
{
    Decart_tree decart_tree;
    int32_t n, m, x;
    srand(time(nullptr));
    std::cin >> n >> m;
    for (int32_t i = 0; i < n; i++) {
        decart_tree.root = decart_tree.insert(decart_tree.root, i, i + 1, rand());
    }
    int32_t l, r;
    for (int32_t i = 0; i < m; i++) {
        std::cin >> l >> r;
        decart_tree.root = decart_tree.part_reverse(decart_tree.root, l, r);
    }
    decart_tree.print_tree(decart_tree.root);
}

