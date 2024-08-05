#ifndef WET2DS_HASHTABLE_H
#define WET2DS_HASHTABLE_H
#include "List.h"
template<typename T>

class dynamicArray{
    List<T>** m_array;
    int m_size;
    int totalUsed;
    int initialSize;
    bool needToChange;

    explicit dynamicArray(int size);
    ~dynamicArray();
    void add(std::shared_ptr<T> toAdd,int index);
    List<std::shared_ptr<T>>* find(int index);


};
template<typename T>
class HashTable{
    dynamicArray* m_dynamicArray;
    int m_tableSize;
    explicit HashTable(int arraySize=10);
    ~HashTable()
    {
        delete array;
        array = nullptr;
    }
    void insert(std::shared_ptr<Player> toAdd);
    void enlargeArray();
    int hash(int index);
    std::shared_ptr<Player> find(int index);
};

#endif //WET2DS_HASHTABLE_H
