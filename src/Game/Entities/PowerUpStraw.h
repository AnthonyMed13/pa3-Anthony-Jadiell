#pragma once

#include "PowerUps.h"
#include "Player.h"
#include "EntityManager.h"
#include "Map.h"

class PowerUpStraw : public PowerUps, public Entity{
    public:
        PowerUpStraw(int,int,int,int,Player*);
        EntityManager *em;
        void activate();
        Player *play;
};