#pragma once

#include "PowerUps.h"
#include "Player.h"
#include "EntityManager.h"

class PowerUpUltimate : public PowerUps, public Entity{
    public:
        PowerUpUltimate(int,int,int,int,Player*,int);
        void activate();
        Player *play;
        string name;
        string getName(){return name;}
        int ranking;
        int getRanking() {return ranking;}
         bool operator<(PowerUps&p){return this->ranking < p.getRanking();}
};