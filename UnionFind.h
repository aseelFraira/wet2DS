#ifndef WET2DS_UNIONFIND_H
#define WET2DS_UNIONFIND_H

#include "HashTable.h"
template<typename T>
class UFnode{
public:
    int m_key;
    T m_data;
    UFnode* m_parent;
    int m_extra;

    UFnode(int key, T data, int extra) : m_key(key), m_data(data),
                                         m_parent(nullptr),m_extra(extra) {}
    ~UFnode() = default;
};
template<typename T>
class UnionFind {
public:

    HashTable<List<NodeList<UFnode<T>>>>* m_table;
    void compressPaths(Node* node);

    UnionFind(HashTable<T>* table = nullptr);
    ~UnionFind() { delete m_table; }

    void makeSet(int fleetID,std::shared_ptr<Fleet> fleet);
    UFnode<T>* find(int id);
    void unionSets(int id1, int id2);
};

template<typename T>
UnionFind<T>::UnionFind(HashTable<T>* table)
        : m_table(table) {}

template<typename T>
void UnionFind<T>::makeSet(int id,T data) {
    UFnode<T>* newNode = new UFnode<T>(id,data,0);
    m_table->insert(id);
}

template<typename T>
UFnode<T>* UnionFind<T>::find(int id) {
    T data = m_table->find(id);
    while (no)
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