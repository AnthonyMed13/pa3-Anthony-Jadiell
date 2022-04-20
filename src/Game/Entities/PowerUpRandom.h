#pragma once

#include "PowerUps.h"
#include "Player.h"
#include "EntityManager.h"

class PowerUpRandom : public PowerUps, public Entity{
    public:
        PowerUpRandom(int,int,int,int,Player*);
        EntityManager *em;
        void activate();
        Player *play;
};