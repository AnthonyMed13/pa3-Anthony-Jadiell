#pragma once

#include "Player.h"
#include "EntityManager.h"
#include "tracking.h"
#include "Grid.h"

class trackingmaze : public tracking{
    public:
    void activate();
    void tick();
    string findCheese(int,int);
    Player* played;
    EntityManager* em;
    std::vector<std::vector<int>> maze;
    trackingmaze(std::vector<std::vector<int>>,Player*);
};