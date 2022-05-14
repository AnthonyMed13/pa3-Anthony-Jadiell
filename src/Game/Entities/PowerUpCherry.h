#pragma once

#include "PowerUps.h"
#include "Player.h"
#include "EntityManager.h"
#include "Map.h"



class PowerUpCherry : public PowerUps, public Entity {
    public:
        EntityManager *em;
        PowerUpCherry(int, int, int, int, Player*, EntityManager* em,int);
        void activate();
        Player *play;
        int xR;
        int ranking;
        string getName(){return name;}
        string name;
        int getRanking() {return ranking;}
        bool operator<(PowerUps&p){return this->ranking < p.getRanking();}
};