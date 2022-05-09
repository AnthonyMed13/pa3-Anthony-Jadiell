#pragma once

#include "PowerUps.h"
#include "Player.h"
#include "EntityManager.h"

class PowerUpRandom : public PowerUps, public Entity{
    public:
        PowerUpRandom(int,int,int,int,Player*,int);
        EntityManager *em;
        void activate();
        Player *play;
        int ranking;
        void render();
        int getRanking() {return ranking;}
        bool operator<(PowerUps&p){return this->ranking < p.getRanking();}
};