#include "PowerUps.h"
#include "Player.h"
#include "PowerUpStraw.h"
#include "EntityManager.h"
#include <time.h>

PowerUpStraw::PowerUpStraw(int x, int y, int width, int height, Player* played) : Entity(x, y, width, height){
    sprite.load("images/Strawberry.png");
    this->play = played;
}

void PowerUpStraw::activate() {
    play->setInv(true);
    play->setW(1);
    play->setH(1);
    
    //play->setW(8);
}