#ifndef WET2DS_UNIONFIND_H
#define WET2DS_UNIONFIND_H

#include "HashTable.h"
#include "UFnode.h"

class UnionFind {
public:
    HashTable<std::shared_ptr<Fleet>>* m_table;

    UnionFind(HashTable<std::shared_ptr<Fleet>>* table = nullptr){m_table = table;}
    ~UnionFind() { delete m_table; }

     ////functions/////////////////
    void makeSet(std::shared_ptr<Fleet> fleet){
        UFnode* newNode = new UFnode(fleet->getID(),fleet);
        m_table->insert(fleet,fleet->getID(),newNode);
    }

    UFnode *find(int id){
        if(!m_table->find(id)){
            return nullptr;
        }
        UFnode* curr = m_table->find(id)->ptr;
        UFnode* root = curr->findDad();
        int extra = curr->getExtraPath();

        while(curr->m_parent){
            int tempExtra = extra;
            extra -= curr->m_extra;
            if(curr->m_parent->m_key != root->m_key){
                curr->m_parent = root;
                curr->m_extra = tempExtra;
            }
            curr = curr->m_parent;
        }
        return curr;
    }

    void unite(int id1, int id2){
        UFnode* root1 = find(id1);
        UFnode* root2 = find(id2);
        if (root1 != root2){
            if(root1->m_fleet->getPiratesNum() >= root2->m_fleet->getPiratesNum()) {

                if (root1->m_fleet->getShipsNum() < root2->m_fleet->getShipsNum()) {
                    root1->m_parent = root2;
                    root2->m_extra += root1->m_fleet->getPiratesNum();
                    root1->m_extra -= root2->m_extra;
                    root2->m_fleet->setShipsNum(root1->m_fleet->getShipsNum());
                    root2->m_fleet->setPiratesNum(root1->m_fleet->getPiratesNum());
                    m_table->remove(id2);

                } else {
                    root2->m_parent = root1;
                    root2->m_extra += (root1->m_fleet->getPiratesNum() - root1->m_extra);
                    root1->m_fleet->setShipsNum(root2->m_fleet->getShipsNum());
                    root1->m_fleet->setPiratesNum(root2->m_fleet->getPiratesNum());
                    m_table->remove(id2);

                }
            } else {
                if (root1->m_fleet->getShipsNum() <= root2->m_fleet->getShipsNum()){

                    root1->m_parent = root2;
                    root1->m_extra += (root2->m_fleet->getPiratesNum() - root2->m_extra);
                    root2->m_fleet->setShipsNum(root1->m_fleet->getShipsNum());
                    root2->m_fleet->setPiratesNum(root1->m_fleet->getPiratesNum());
                    m_table->remove(id1);

                } else {

                    root2->m_parent = root1;
                    root1->m_extra += root2->m_fleet->getPiratesNum();
                    root2->m_extra -= root1->m_extra;
                    root1->m_fleet->setShipsNum(root2->m_fleet->getShipsNum());
                    root1->m_fleet->setPiratesNum(root2->m_fleet->getPiratesNum());
                    m_table->remove(id1);

                }
            }
        }
    }
};





#endif //WET2DS_UNIONFIND_H