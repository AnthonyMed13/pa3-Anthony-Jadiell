#include "PowerUps.h"
#include "Player.h"
#include "PowerUpCherry.h"
#include "EntityManager.h"
#include "Map.h"
#include "BigDot.h"

PowerUpCherry::PowerUpCherry(int x, int y, int width, int height, Player* played, EntityManager* em,int rank): Entity(x, y, width, height){
    sprite.load("images/Cherry.png");
    name="Cherry";
    this->play = played;
    this->em = em;
    this->ranking = rank;
    xR = ofRandom(1,5);
}

void PowerUpCherry::activate(){
    for(Entity* position: em->entities){
        if (dynamic_cast<BigDot*>(position))
        {
            if (xR == 0)
            {
                play->setX(position->getX());
                play->setY(position->getY());
            }
            xR--;
        }
    }
}