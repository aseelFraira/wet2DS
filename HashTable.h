#ifndef WET2DS_HASHTABLE_H
#define WET2DS_HASHTABLE_H

#include <memory> // For std::shared_ptr
#include "List.h" // Assuming List.h is available

class dynamicArray {
    List<>** m_array;
    int m_size;
    int totalUsed;
    int initialSize;
    bool needToChange;

public:
    explicit dynamicArray(int size);
    ~dynamicArray();
    void add(std::shared_ptr<T> toAdd, int index);
    List<std::shared_ptr<T>>* find(int index);
};

template<typename T>
class HashTable {
    dynamicArray<T>* m_dynamicArray;
    int m_tableSize;

public:
    explicit HashTable(int arraySize = 10);
    ~HashTable();
    void insert(std::shared_ptr<T> toAdd);
    void enlargeArray();
    int hash(int index);
    std::shared_ptr<T> find(int index);
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
void dynamicArray<T>::add(std::shared_ptr<T> toAdd, int index) {
    if (index >= m_size) return; // Out of bounds
    if (m_array[index] == nullptr) {
        m_array[index] = new List<std::shared_ptr<T>>;
    }
    m_array[index]->add(toAdd);
    ++totalUsed;
    needToChange = (totalUsed > m_size / 2); // Example condition
}

template<typename T>
List<std::shared_ptr<T>>* dynamicArray<T>::find(int index) {
    if (index >= m_size) return nullptr; // Out of bounds
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
void HashTable<T>::insert(std::shared_ptr<T> toAdd) {
    int index = hash(toAdd->getKey()); // Assuming T has a getKey() method
    m_dynamicArray->add(toAdd, index);
    if (m_dynamicArray->needToChange) {
        enlargeArray();
    }
}

template<typename T>
void HashTable<T>::enlargeArray() {
    int newSize = m_tableSize * 2;
    dynamicArray<T>* newArray = new dynamicArray<T>(newSize);
    for (int i = 0; i < m_tableSize; ++i) {
        List<std::shared_ptr<T>>* list = m_dynamicArray->find(i);
        if (list != nullptr) {
            // Assuming List has an iterator or way to traverse elements
            for (auto& item : *list) {
                int newIndex = hash(item->getKey()) % newSize;
                newArray->add(item, newIndex);
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
std::shared_ptr<T> HashTable<T>::find(int index) {
    List<std::shared_ptr<T>>* list = m_dynamicArray->find(hash(index));
    if (list != nullptr) {
        for (auto& item : *list) {
            if (item->getKey() == index) { // Assuming T has a getKey() method
                return item;
            }
        }
    }
    return nullptr; // Not found
}

#endif // WET2DS_HASHTABLE_H
