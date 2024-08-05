//
// Created by aseel on 24/07/2024.
//

#ifndef WET2DS_LIST_H
#define WET2DS_LIST_H

#include <memory>
#include "Node.h"
template<typename T>
class NodeList{
public:
    int m_key;
    T m_data;
    NodeList* m_prev;
    NodeList* m_next;

    NodeList():m_data(nullptr),m_next(nullptr),m_prev(nullptr){}
    NodeList(int key,T data):m_key(key),m_data(data),m_next(nullptr),m_prev(nullptr){}
    ~NodeList() = default;

};
template<typename T>
class List{
public:
    int m_listSize;
    NodeList<T>* m_head;
    NodeList<T>* m_tail;

    List():m_head(nullptr),m_tail(nullptr),m_listSize(0){}
    ~List();
    void insertFront(int key,T data);

};
template<typename T>
List<T>::~List() {
    if (m_listSize == 0)
    {
        return;
    }
    NodeList<T>* prev = nullptr;
    while(m_head)
    {
        prev = m_head->m_prev;
        delete m_head;
        m_head = prev;
    }
}
template<typename T>
void List<T>::insertFront(int key,T data){
    NodeList<T>* NodeToAdd = new NodeList<T>(key,data);
    m_listSize++;
    if(m_tail == nullptr && m_head == nullptr)
    {
        m_head = NodeToAdd;
        m_tail = NodeToAdd;
        return;
    }
    m_head->m_next = NodeToAdd;
    NodeToAdd->m_prev = m_head;
    m_head=NodeToAdd;
}


#endif //WET2DS_LIST_H
