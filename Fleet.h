//
// Created by Lana on 24/07/2024.
//

#ifndef WET2DS_FLEET_H
#define WET2DS_FLEET_H
class Fleet{
private:
    int m_fleetID;
    int m_numOfShips;
    int m_numOfPirates;
public:
    Fleet();
    Fleet(int ID);
    int getShipsNum();
    void setShipsNum(int change);
    int getPiratesNum();
    void setPiratesNum(int change);
    int getID(){
        return m_fleetID;
    }
};
#endif //WET2DS_FLEET_H
