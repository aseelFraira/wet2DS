#ifndef WET2DS_HASHTABLE_H
#define WET2DS_HASHTABLE_H

#include <memory> // For std::shared_ptr
#include "List.h" // Assuming List.h is available


template<typename T>
class dynamicArray {
public:
    List<T>** m_array;
    int m_size;
    int totalUsed;
    int initialSize;
    bool needToChange;

public:
    explicit dynamicArray(int size);
    ~dynamicArray();
    void add(T toAdd, int index, int id, UFnode* ptr = nullptr);
    List<T>* find(int index) const;
};


template<typename T>
class HashTable {
    dynamicArray<T>* m_dynamicArray;
    int m_tableSize;
public:
    explicit HashTable(int arraySize = 10);
    ~HashTable();
    void insert(T data,int id, UFnode* ptr = nullptr);
    void enlargeArray();
    int hash(int index);
    NodeList<T>* find(int id);
};

template<typename T>
dynamicArray<T>::dynamicArray(int size)
        : m_size(size), totalUsed(0), initialSize(size), needToChange(false) {
    m_array = new List<T>*[m_size];
    for (int i = 0; i < m_size; ++i) {
        m_array[i] = new List<T>();
    }
}

template<typename T>
dynamicArray<T>::~dynamicArray() {
    for (int i = 0; i < m_size; ++i) {
        delete m_array[i];
        m_array[i]= nullptr;
    }
    m_size=0;
    delete[] m_array;
}

template<typename T>
void dynamicArray<T>::add(T toAdd, int index, int id, UFnode* ptr) {
    if (index >= m_size) return; // Out of bounds
    if (m_array[index] == nullptr) {
        m_array[index] = new List<T>;
    }
    m_array[index]->insertFront(toAdd,id,ptr);
    ++totalUsed;
    if(totalUsed == m_size){
        needToChange = true;
    }
}
template<typename T>
List<T> *dynamicArray<T>::find(int index) const {
    if (index >= m_size) return nullptr;// Out of bounds
    return m_array[index];
}

template<typename T>
HashTable<T>::HashTable(int arraySize)
        : m_tableSize(arraySize) {
    m_dynamicArray = new dynamicArray<T>(arraySize);
}

template<typename T>
HashTable<T>::~HashTable() {
    delete m_dynamicArray;
    m_dynamicArray = nullptr;
}

template<typename T>
void HashTable<T>::insert(T data, int id, UFnode* ptr) {
    int index = hash(id); // Assuming T has a getKey() method
    m_dynamicArray->add(data,index,id,ptr);
    if (m_dynamicArray->needToChange) {
        enlargeArray();
        m_dynamicArray->needToChange = false;
    }
}

template<typename T>
void HashTable<T>::enlargeArray() {
    int OldSize = m_tableSize;
    m_tableSize *= 2;
    dynamicArray<T>* newArray = new dynamicArray<T>(m_tableSize);
    for (int i = 0; i < OldSize; ++i) {
        List<T>* list = m_dynamicArray->m_array[i];
        if (list != nullptr) {
            NodeList<T>* current = list->m_head;
            while(current) {
                UFnode* ptr = current->ptr;
                newArray->add(current->m_data, hash(current->m_key),current->m_key,ptr);
                current = current->m_prev;
            }
        }
    }
    delete m_dynamicArray;
    m_dynamicArray = newArray;
}

template<typename T>
int HashTable<T>::hash(int index) {

    return index % m_tableSize; // Example hash function
}

template<typename T>
NodeList<T>* HashTable<T>::find(int id) {
    List<T>* list = m_dynamicArray->m_array[hash(id)];
    if(!list){
        return nullptr;
    }
    NodeList<T>* curr = list->m_head;
    while(curr){
        if(curr->m_key == id){
            return curr;
        }
        curr = curr->m_prev;
    }
    return nullptr; // Not found
}



#endif // WET2DS_HASHTABLE_H
