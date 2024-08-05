//
// Created by Lana on 24/07/2024.
//

#ifndef WET2DS_PIRATE_H
#define WET2DS_PIRATE_H
class Pirate{
private:

    int m_pirateID;
    int m_argument;
    int m_savings;

public:

    Pirate(): m_argument(0),m_pirateID(0), m_savings(0) {}
    Pirate(int pirateID) : m_pirateID(pirateID), m_argument(0), m_savings(0){}

    int getPirateID(){
        return m_pirateID;
    }
    int getArgument(){
        return m_argument;
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
