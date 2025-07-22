#ifndef S21_AVLTREE_H
#define S21_AVLTREE_H

#include <iostream>
#include <memory>
#include <stack>
#include <limits>
#include <utility>
#include <stdexcept>
#include <initializer_list>

namespace s21 {
    template <typename K, typename V>
    struct AVLNode {
        using value_type = std::pair<const K, V>;

        value_type data;
        AVLNode* left;
        AVLNode* right;
        int height;
        size_t count;

        explicit AVLNode(const value_type& value) : data(value), left(nullptr), right(nullptr), height(1), count(1) {}
    };

    template <typename K, typename V>
    class AVLTree {
    public:
        using key_type = K;
        using mapped_type = V;
        using value_type = std::pair<const key_type, mapped_type>;
        using reference = value_type&;
        using const_reference = const value_type&;
        using size_type = size_t;
        using node_type = AVLNode<key_type, mapped_type>;

        class iterator {
        public:
            using value_type = std::pair<const K, V>;
            using reference = value_type&;
            using pointer = value_type*;

        public:
            node_type* current;
            const AVLTree* tree;
            size_t current_count;

        public:
            explicit iterator(node_type* node = nullptr, const AVLTree* tree = nullptr, size_t count = 0) : current(node), tree(tree), current_count(count) {}

            reference operator*() const {
                return current->data;
            }

            pointer operator->() const {
                return &(current->data);
            }

            iterator& operator++() {
                if (current_count < current->count - 1) {
                    ++current_count;
                } else {
                    if (current->right) {
                        current = current->right;
                        while (current->left)
                            current = current->left;
                    } else {
                        node_type* parent = tree->findParent(current);
                        while (parent && current == parent->right) {
                            current = parent;
                            parent = tree->findParent(parent);
                        }
                        current = parent;
                    }
                    current_count = 0;
                }
                return *this;
            }

            bool operator==(const iterator& other) const {
                return current == other.current && current_count == other.current_count;
            }

            bool operator!=(const iterator& other) const {
                return !(*this == other);
            }
        };

        class const_iterator {
        public:
            using value_type = const std::pair<const K, V>;
            using reference = const value_type&;
            using pointer = const value_type*;

        public:
            node_type* current;
            const AVLTree* tree;
            size_t current_count;

        public:
            explicit const_iterator(node_type* node = nullptr, const AVLTree* tree = nullptr, size_t count = 0) : current(node), tree(tree), current_count(count) {}

            reference operator*() const {
                return current->data;
            }

            pointer operator->() const {
                return &(current->data);
            }

            const_iterator& operator++() {
                if (current_count < current->count - 1) {
                    ++current_count;
                } else {
                    if (current->right) {
                        current = current->right;
                        while (current->left)
                            current = current->left;
                    } else {
                        node_type* parent = tree->findParent(current);
                        while (parent && current == parent->right) {
                            current = parent;
                            parent = tree->findParent(parent);
                        }
                        current = parent;
                    }
                    current_count = 0;
                }
                return *this;
            }

            bool operator==(const const_iterator& other) const {
                return current == other.current && current_count == other.current_count;
            }

            bool operator!=(const const_iterator& other) const {
                return !(*this == other);
            }
        };

    private:
        node_type* root;

        int height(node_type* node) const {
            return node ? node->height : 0;
        }

        int balanceFactor(node_type* node) const {
            return height(node->left) - height(node->right);
        }

        void updateHeight(node_type* node) {
            node->height = std::max(height(node->left), height(node->right)) + 1;
        }

        node_type* rotateRight(node_type* y) {
            node_type* x = y->left;
            node_type* T2 = x->right;

            x->right = y;
            y->left = T2;

            updateHeight(y);
            updateHeight(x);

            return x;
        }

        node_type* rotateLeft(node_type* x) {
            node_type* y = x->right;
            node_type* T2 = y->left;

            y->left = x;
            x->right = T2;

            updateHeight(x);
            updateHeight(y);

            return y;
        }

        node_type* balance(node_type* node) {
            updateHeight(node);

            if (balanceFactor(node) == 2) {
                if (balanceFactor(node->left) < 0)
                    node->left = rotateLeft(node->left);
                return rotateRight(node);
            }

            if (balanceFactor(node) == -2) {
                if (balanceFactor(node->right) > 0)
                    node->right = rotateRight(node->right);
                return rotateLeft(node);
            }

            return node;
        }

        node_type* insert(node_type* node, const value_type& value, iterator& it) {
            if (!node) {
                it = iterator(new node_type(value), this);
                return it.current;
            }

            if (value.first < node->data.first)
                node->left = insert(node->left, value, it);
            else if (value.first > node->data.first)
                node->right = insert(node->right, value, it);
            else {
                node->count++;
                it = iterator(node, this);
                return node;
            }

            return balance(node);
        }

        node_type* findMin(node_type* node) const {
            return node->left ? findMin(node->left) : node;
        }

        node_type* removeMin(node_type* node) {
            if (!node->left)
                return node->right;
            node->left = removeMin(node->left);
            return balance(node);
        }

        node_type* remove(node_type* node, const key_type& key, iterator& it) {
            if (!node)
                return nullptr;

            if (key < node->data.first)
                node->left = remove(node->left, key, it);
            else if (key > node->data.first)
                node->right = remove(node->right, key, it);
            else {
                if (node->count > 1) {
                    node->count--;
                    it = iterator(node, this);
                    return node;
                }

                node_type* left = node->left;
                node_type* right = node->right;
                delete node;

                if (!right) {
                    it = iterator(left, this);
                    return left;
                }

                node_type* min = findMin(right);
                min->right = removeMin(right);
                min->left = left;

                it = iterator(min, this);
                return balance(min);
            }

            it = iterator(node, this);
            return balance(node);
        }

        node_type* find(node_type* node, const key_type& key) const {
            if (!node)
                return nullptr;

            if (key < node->data.first)
                return find(node->left, key);
            else if (key > node->data.first)
                return find(node->right, key);
            else
                return node;
        }

        void clear(node_type* node) {
            if (node) {
                clear(node->left);
                clear(node->right);
                delete node;
            }
        }

        node_type* copyTree(node_type* node) {
            if (!node)
                return nullptr;

            auto* newNode = new node_type(node->data);
            newNode->left = copyTree(node->left);
            newNode->right = copyTree(node->right);
            newNode->height = node->height;
            newNode->count = node->count;

            return newNode;
        }

        node_type* findParent(node_type* node, node_type* child) const {
            if (!node || node == child)
                return nullptr;

            if ((node->left && node->left == child) || (node->right && node->right == child))
                return node;

            if (child->data.first < node->data.first)
                return findParent(node->left, child);
            else
                return findParent(node->right, child);
        }

    public:
        AVLTree() : root(nullptr) {}

        AVLTree(const AVLTree& other) : root(copyTree(other.root)) {}

        AVLTree(AVLTree&& other) noexcept : root(other.root) {
            other.root = nullptr;
        }

        ~AVLTree() {
            clear(root);
        }

        AVLTree& operator=(AVLTree&& other) noexcept {
            if (this != &other) {
                clear(root);
                root = other.root;
                other.root = nullptr;
            }
            return *this;
        }

        iterator insert(const value_type& value) {
            iterator it;
            root = insert(root, value, it);
            return it;
        }

        iterator erase(iterator pos) {
            if (pos == end())
                return end();

            iterator it;
            root = remove(root, pos->first, it);
            return it;
        }

        iterator find(const key_type& key) const {
            return iterator(find(root, key), this);
        }

        void clear() {
            clear(root);
            root = nullptr;
        }

        bool empty() const {
            return root == nullptr;
        }

        size_type size(node_type* node) const {
            if (!node)
                return 0;
            return node->count + size(node->left) + size(node->right);
        }

        size_type size() const {
            return size(root);
        }

        size_type max_size() const {
            return std::numeric_limits<size_type>::max();
        }

        node_type* findParent(node_type* node) const {
            return findParent(root, node);
        }

        node_type* findMin() const {
            return findMin(root);
        }

        iterator begin() const {
            return iterator(findMin(), this);
        }

        iterator end() const {
            return iterator(nullptr, this);
        }

        const_iterator cbegin() const {
            return const_iterator(findMin(), this);
        }

        const_iterator cend() const {
            return const_iterator(nullptr, this);
        }
    };
} // namespace s21

#endif // S21_AVLTREE_H