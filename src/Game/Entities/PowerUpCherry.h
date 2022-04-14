#pragma once

#include "PowerUps.h"
#include "Player.h"
#include "EntityManager.h"
#include "Map.h"



class PowerUpCherry : public PowerUps, public Entity {
    public:
        int xs;
        int ys;
        Map *test;
        bool canTeleport = false;
        EntityManager *em;
        PowerUpCherry(int, int, int, int, Player*, EntityManager* em);
        void activate();
        Player *play;
        int xR;
        int yR;
};