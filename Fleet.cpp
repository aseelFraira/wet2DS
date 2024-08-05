#include "Fleet.h"

Fleet::Fleet(): m_fleetID(0), m_numOfShips(0), m_numOfPirates(0){}
Fleet::Fleet(int ID) : m_fleetID(ID), m_numOfShips(1), m_numOfPirates(0){}

int Fleet::getShipsNum() {
return m_numOfShips;
}

void Fleet::setShipsNum(int change) {
    m_numOfShips += change;
}

int Fleet::getPiratesNum() {
    return m_numOfPirates;
}

void Fleet::setPiratesNum(int change) {
    m_numOfPirates += change;
}


