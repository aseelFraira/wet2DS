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

    void remove(int id);
};

template<typename T>
dynamicArray<T>::dynamicArray(int size)
        : m_size(size), totalUsed(0), initialSize(size), needToChange(false) {
    m_array = new List<T>*[m_size];
    for (int i = 0; i < m_size; ++i) {
        m_array[i] = nullptr;
    }
}

template<typename T>
dynamicArray<T>::~dynamicArray() {
    for (int i = 0; i < m_size; ++i) {
        delete m_array[i];
    }
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
    needToChange = (totalUsed > m_size / 2); // Example condition
}
template<typename T>
List<T> *dynamicArray<T>::find(int index) const {
    if (index >= m_size) return nullptr; // Out of bounds
    return m_array[index];
}

template<typename T>
HashTable<T>::HashTable(int arraySize)
        : m_tableSize(0) {
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
    m_dynamicArray->add(data,index,id);
    if (m_dynamicArray->needToChange) {
        enlargeArray();
    }
    m_tableSize++;
}

template<typename T>
void HashTable<T>::enlargeArray() {
    int newSize = m_tableSize * 2;
    dynamicArray<T>* newArray = new dynamicArray<T>(newSize);
    for (int i = 0; i < m_tableSize; ++i) {
        List<T>* list = m_dynamicArray->find(i);
        if (list != nullptr) {
            // Assuming List has an iterator or way to traverse elements
            NodeList<T>* current = list->m_head;
            while(current) {
                int newIndex = hash(current->m_key) % newSize;
                UFnode* ptr = current->ptr;
                newArray->add(current->m_data, newIndex,current->m_key,ptr);
                current = current->m_next;
            }
        }
    }
    delete m_dynamicArray;
    m_dynamicArray = newArray;
    m_tableSize = newSize;
}

template<typename T>
int HashTable<T>::hash(int index) {
    return index % m_tableSize; // Example hash function
}

template<typename T>
NodeList<T>* HashTable<T>::find(int id) {
    List<T>* list = m_dynamicArray->find(hash(id));
    if(!list){
        return nullptr;
    }
    NodeList<T>* curr = list->m_head;
    while(curr){
        if(curr->m_key == id){
            return curr;
        }
        curr = curr->m_next;
    }
    return nullptr; // Not found
}

template<typename T>
void HashTable<T>::remove(int id) {
    int index = hash(id);
    List<T> *list = m_dynamicArray->find(index);

    if (list == nullptr) {
        return; // The list doesn't exist, nothing to remove
    }

    NodeList<T> *current = list->m_head;
    NodeList<T> *previous = nullptr;

    while (current != nullptr) {
        if (current->m_key == id) {
            if (previous == nullptr) {
                list->m_head = current->m_next;
            } else {
                previous->m_next = current->m_next;
            }

            if (current == list->m_tail) {
                list->m_tail = previous;
            }

            delete current;
            m_tableSize--;
            return;
        }
        previous = current;
        current = current->m_next;
    }
}


#endif // WET2DS_HASHTABLE_H
