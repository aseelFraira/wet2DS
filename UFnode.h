#ifndef WET2DS_NODE_H
#define WET2DS_NODE_H
template<typename T>
class UFnode{
public:
    int m_key;
    T m_data;
    UFnode* m_parent;
    int m_extra;

    int getExtraPath();
    T findDad();

    UFnode(int key, T data, int extra) : m_key(key), m_data(data),
                                         m_parent(nullptr),m_extra(extra) {}
    ~UFnode() = default;
};
template<typename T>
int UFnode<T>::getExtraPath() {
    int sum = 0;
    UFnode<T>* current = this->m_parent;
    while (current){
        sum += current->m_extra;
    }
    return sum;
}

template<typename T>
T UFnode<T>::findDad() {
    UFnode<T>* current = this;
    while (current->m_parent){
        
    }
}
#endif //WET2DS_NODE_H
