#include "PowerUpRandom.h"

PowerUpRandom::PowerUpRandom(int x, int y, int width, int height, Player* played,int rank) : Entity(x, y, width, height){
    name="Random";
    sprite.load("images/Points.png");
    this->ranking = rank;
    this->play = played;
}

void PowerUpRandom::activate(){
    play->setScore(ofRandom(1000,5000));
}
