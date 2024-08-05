#ifndef WET2DS_UFNODE_H
#define WET2DS_UFNODE_H

#include <memory>

class UFnode{
public:
    int m_key;
    std::shared_ptr<Fleet> m_fleet;
    UFnode* m_parent;
    int m_extra;

    int getExtraPath();
    UFnode* findDad();

    UFnode(int key, std::shared_ptr<Fleet> fleet) : m_key(key), m_fleet(fleet),
                                         m_parent(nullptr),m_extra(0) {}
    ~UFnode() = default;
};
int UFnode::getExtraPath() {
    int sum = 0;
    UFnode* current = this;
    while (current){
        sum += current->m_extra;
        current = current->m_parent;
    }
    return sum;
}

UFnode* UFnode::findDad() {
    UFnode* current = this;
    while (current->m_parent){
        current = current->m_parent;
    }
    return current;
}
#endif //WET2DS_UFNODE_H
