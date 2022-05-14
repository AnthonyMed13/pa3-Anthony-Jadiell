#pragma once

#include "PowerUps.h"
#include "Player.h"
#include "EntityManager.h"

class PowerUpRandom : public PowerUps, public Entity{
    public:
        PowerUpRandom(int,int,int,int,Player*,int);
        void activate();
        Player *play;
        int ranking;
        string getName(){return name;}
        string name;
        int getRanking() {return ranking;}
        bool operator<(PowerUps&p){return this->ranking < p.getRanking();}
};