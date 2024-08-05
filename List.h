//
// Created by aseel on 24/07/2024.
//

#ifndef WET2DS_LIST_H
#define WET2DS_LIST_H
template<typename T>
class NodeList{
    T m_data;
    NodeList* m_prev;
    NodeList* m_next;

    NodeList():m_data(nullptr),m_next(nullptr),m_prev(nullptr){}
    NodeList(T data):m_data(data),m_next(nullptr),m_prev(nullptr){}
    ~NodeList() = default;

};
template<typename T>
class List{
public:
    int m_size;
    NodeList<T>* m_head;
    NodeList<T>* m_tail;

    List():m_head(nullptr),m_tail(nullptr),m_size(0){}
    ~List();
    void insertFront(T data);

};
template<typename T>
List<T>::~List() {
    if (m_size == 0)
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
List<T>::addFront(T data){
    ListNode<T>* NodeToAdd = new ListNode<T>(data);
    listSize++;
    if(tail == nullptr && head == nullptr)
    {
        head=NodeToAdd;
        tail=NodeToAdd;
        return;
    }
    head->next=ListNodeToAdd;
    ListNodeToAdd->prev=head;
    head=ListNodeToAdd;
}


#endif //WET2DS_LIST_H
