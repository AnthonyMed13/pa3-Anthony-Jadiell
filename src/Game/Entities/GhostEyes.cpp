#include "GhostEyes.h"

GhostEyes::GhostEyes(int x, int y, int width, int height, vector<pair<int,int>> moving, EntityManager* em) : Entity(x,y,width,height)
{   
    this->em = em;
    this->x = x;
    this->y = y;
    move = moving;
    sprite.load("images/GhostEyesL.png");
}

void GhostEyes::tick()
{
    if(once == false)
    {
        x = move[move.size()-size].first;
        y = move[move.size()-size].second;
    }
    if(size != move.size()) size++;
    else {
        if(once == false)
        {
            sprite.clear();
            sprite2.load("images/Background.png");
            spawn = new Ghost(x,y,width,height,sprite2,em,colors);
            em->ghosts.push_back(spawn);
            once = true;
        }
        //Ghost* test = new Ghost(x,y,width,height,sprite,em,colors);
       // em->entities.push_back(test);
         //for(Entity* entity:em->eyes){
             //   GhostEyes* eyes = dynamic_cast<GhostEyes*>(entity);
             //   eyes->remove = true;
           // }
        }
}


