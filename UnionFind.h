#ifndef WET2DS_UNIONFIND_H
#define WET2DS_UNIONFIND_H

#include "HashTable.h"

class Node {
public:
    int m_key;
    std::shared_ptr<Fleet> m_fleet;
    Node* m_parent;

    //Node() : m_key(nullptr), m_data(nullptr), m_parent(nullptr) {}
    Node(int key, std::shared_ptr<Fleet> data) : m_key(key), m_fleet(data), m_parent(nullptr) {}
    ~Node() = default;
};

template<typename T>
class UnionFind {
public:

    HashTable<List<Node>>* m_table;
    void compressPaths(Node* node);

    UnionFind(HashTable<T>* table = nullptr);
    ~UnionFind() { delete m_table; }

    void makeSet(int fleetID,std::shared_ptr<Fleet> fleet);
    Node* find(Node<T>* node);
    void unionSets(Node<T>* node1, Node<T>* node2);
};

template<typename T>
UnionFind<T>::UnionFind(HashTable<T>* table)
        : m_table(table) {}

template<typename T>
void UnionFind<T>::makeSet(int fleetID) {
    Node<T>* newNode = new Node<T>(fleetID, nullptr);
    m_table->insert(std::make_shared<Node<T>>(newNode));
}

template<typename T>
Node<T>* UnionFind<T>::find(Node<T>* node) {
    if (node->m_parent != node) {
        node->m_parent = find(node->m_parent);
    }
    return node->m_parent;
}

template<typename T>
void UnionFind<T>::unionSets(Node<T>* node1, Node<T>* node2) {
    Node<T>* root1 = find(node1);
    Node<T>* root2 = find(node2);

    if (root1 != root2) {
        root2->m_parent = root1;
    }
}

template<typename T>
void UnionFind<T>::compressPaths(Node<T>* node) {
    if (node->m_parent != node) {
        node->m_parent = find(node->m_parent);
    }
}

#endif //WET2DS_UNIONFIND_H
