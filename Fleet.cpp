#include "Fleet.h"

Fleet(): m_fleetID(0), m_numOfShips(0), m_numOfPirates(0){}
Fleet(int ID): m_fleetID(ID), m_numOfShips(1), m_numOfPirates(0){}

int getShipsNum(){
return numOfShips;
}

void setShipsNum(int change){
    m_numOfShips += change;
}

int getPiratesNum(){
    return m_numOfPirates;
}

void setPiratesNum(int change){
    m_numOfPirates += change;
}


