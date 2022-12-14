#pragma once

#include "PowerUps.h"
#include "Player.h"
#include "EntityManager.h"
#include "Map.h"

class PowerUpStraw : public PowerUps, public Entity{
    public:
        PowerUpStraw(int,int,int,int,Player*,int);
        void activate();
        Player *play;
        string getName(){return name;}
        string name;
        int ranking;
        int getRanking() {return ranking;}
         bool operator<(PowerUps&p){return this->ranking < p.getRanking();}
};