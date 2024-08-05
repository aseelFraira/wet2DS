//
// Created by Lana on 24/07/2024.
//
#include "Fleet.h"
#include "UFnode.h"
#include <memory>
#ifndef WET2DS_PIRATE_H
#define WET2DS_PIRATE_H
class Pirate{
private:

    int m_pirateID;
    int m_argument;
    int m_savings;

public:
    UFnode* motherFleet; //TODO UNIONFIND NODEEEEEEEE
    Pirate(): m_argument(0),m_pirateID(0), m_savings(0), motherFleet(nullptr) {}
    Pirate(int pirateID) : m_pirateID(pirateID), m_argument(0), m_savings(0),motherFleet(
            nullptr){}

    int getPirateID(){
        return m_pirateID;
    }
    int getArgument(){
        return m_argument + motherFleet->getExtraPath();
    }
    void setArgument(int change){
        m_argument = change;
    }

    int getSavings(){
        return m_savings;
    }

    void setSavings(int change){
        m_savings += change;
    }

};
#endif //WET2DS_PIRATE_H
