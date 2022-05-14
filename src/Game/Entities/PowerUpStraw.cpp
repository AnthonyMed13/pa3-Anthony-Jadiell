#include "PowerUps.h"
#include "Player.h"
#include "PowerUpStraw.h"
#include "EntityManager.h"

PowerUpStraw::PowerUpStraw(int x, int y, int width, int height, Player* played,int rank) : Entity(x, y, width, height){
    name="Strawberry";
    sprite.load("images/Strawberry.png");
    this->play = played;
    this->ranking = rank;
}

void PowerUpStraw::activate() {
    play->setInv(true);
    play->setW(1);
    play->setH(1);
}