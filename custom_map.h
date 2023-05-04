//
// Created by jeremiah on 5/4/23.
//

#pragma once

#include <memory>
#include <vector>

template<typename T, typename U>
struct CustomMap {

    //swap
    //contains
    //find

    [[nodiscard]] size_t size() const {
        return map_size;
    }

    [[nodiscard]] size_t empty() const {
        return map_size == 0;
    }

    bool insert(const T& key, const U& value) {
        if (root == nullptr) {
            root = createNode(key, value);
            return true;
        } else {
            Node* current_node = root;

            while (true) {
                if (*current_node->key == key) {
                    return false;
                } else if (*current_node->key > key) {
                    if (current_node->left == nullptr) {
                        current_node->left = createNode(key, value);
                        return true;
                    } else {
                        current_node = current_node->left;
                    }
                } else {
                    if (current_node->right == nullptr) {
                        current_node->right = createNode(key, value);
                        return true;
                    } else {
                        current_node = current_node->right;
                    }
                }
            }
        }
    }

    //TODO: allows for nullptr if no found I guess.
    std::unique_ptr<U> erase(const T& key) {
        if (empty()) {
            return nullptr;
        }

        Node** parent_node_field = nullptr;
        Node* current_node = root;

        while (*current_node->key != key) {
            if (current_node == nullptr) {
                return nullptr;
            } else if (*current_node->key < key) {
                parent_node_field = current_node->left;
                current_node = current_node->left;
            } else { // > (== was checked at start of loop)
                parent_node_field = current_node->right;
                current_node = current_node->right;
            }
        }

//        root = nullptr;

        std::unique_ptr<U> extracted_value = std::move(current_node->value);
        map_size--;
//        delete current_node;

        Node* new_node = nullptr;
        if (current_node->right && current_node->left) {
            //TODO: need to, refactor the tree maybe?
        } else if (current_node->right) {
            new_node = current_node->right;
        } else if (current_node->left) {
            new_node = current_node->left;
        }

        *parent_node_field = new_node;

        //TODO: delete current_node
        //TODO: lower size b
        //TODO: refactor tree to remove node
        // root; if right exists, move right node to take root; if left exists, move left; else null it
        // middle; if right exists, move right node to take root; if left exists, move left; else null it
        // leaf

        return extracted_value;

    }

    void print() {
        std::vector<std::vector<Node*>> v{std::vector<Node*>{root}};

        for (int i = 0; i < v.size(); ++i) {
            std::vector<Node*>& prev = v[i];
            std::vector<Node*> next;

            for (Node* node: prev) {
                if (node != nullptr) {
                    next.emplace_back(node->left);
                    next.emplace_back(node->right);
                }
            }

            if (!next.empty()) {
                v.emplace_back(next);
            }
        }

        for (const auto& node_level: v) {
            for (Node* node: node_level) {
                if (node == nullptr) {
                    std::cout << " null  ";
                } else {
                    std::cout << '(' << *node->key << ',' << *node->value << ")  ";
                }
            }
            std::cout << '\n';
        }
    }

private:
    struct Node {
        Node() = delete;

        explicit Node(
                std::unique_ptr<T>&& _key,
                std::unique_ptr<U>&& _value
        ) : key(std::move(_key)),
            value(std::move(_value)) {}

        std::unique_ptr<T> key = nullptr;
        std::unique_ptr<U> value = nullptr;

        Node* left = nullptr;
        Node* right = nullptr;
    };

    Node* createNode(const T& key, const U& value) {
        map_size++;
        std::unique_ptr<T> key_copy = std::make_unique<T>(key);
        std::unique_ptr<U> value_copy = std::make_unique<U>(value);
        return new Node{
                std::move(key_copy),
                std::move(value_copy)
        };
    }

    Node* root = nullptr;
    size_t map_size = 0;
};