#include "PowerUpRandom.h"

PowerUpRandom::PowerUpRandom(int x, int y, int width, int height, Player* played) : Entity(x, y, width, height){
    sprite.load("images/Points.png");
    this->play = played;
}

void PowerUpRandom::activate(){
    play->setScore(ofRandom(1000,5000));
}