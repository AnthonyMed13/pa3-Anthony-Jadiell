#pragma once

#include "EntityManager.h"
#include "Animation.h"
#include "Ghost.h"
#include "GhostSpawner.h"

class GhostEyes: public Entity{
    public:
        GhostEyes(int, int, int, int, vector<pair<int,int>>,EntityManager*);
        void tick();
        string colors = "red";
        int counter = 1;
        vector<pair<int,int>> move;
       Ghost* spawn;
       size_t size = 1;
       ofImage sprite2;
       bool once = false;
       
    private:
        bool justSpawned=true;
        int speed=2;
        EntityManager* em;
};