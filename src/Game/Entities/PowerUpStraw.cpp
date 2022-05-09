#include "PowerUps.h"
#include "Player.h"
#include "PowerUpStraw.h"
#include "EntityManager.h"

PowerUpStraw::PowerUpStraw(int x, int y, int width, int height, Player* played,int rank) : Entity(x, y, width, height){
    sprite.load("images/Strawberry.png");
    this->play = played;
    this->ranking = rank;
}

void PowerUpStraw::activate() {
    play->setInv(true);
    play->setW(1);
    play->setH(1);
}

void PowerUpStraw::render(){
    ofSetColor(256,256,256);
    sprite.draw(x, y, width, height);
}