#pragma once


#include "Animation.h"
#include "EntityManager.h"
#include "PowerUps.h"
#include "Player.h"


class PowerUpSpeed : public PowerUps {
    public:
    Player *play;
    PowerUpSpeed(Player*);
    void activate();
};