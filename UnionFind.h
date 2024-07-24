#ifndef WET2DS_UNIONFIND_H
#define WET2DS_UNIONFIND_H

template<typename KEY,typename DATA>
class Node{
public:
    KEY m_key;
    DATA m_data;
    Node* m_parent;

    Node(): m_key(nullptr), m_data(nullptr), m_parent(nullptr){};
    Node(KEY key, DATA& data): m_key(key), m_data(data), m_parent(nullptr){}
    ~Node()=default;
};
Class UnionFind{

};
#endif //WET2DS_UNIONFIND_H
