#include "PowerUps.h"
#include "Player.h"
#include "PowerUpUltimate.h"
#include "EntityManager.h"

PowerUpUltimate::PowerUpUltimate(int x, int y, int width, int height, Player* played,int rank) : Entity(x, y, width, height){
    name="ultimate";
    this->play = played;
    this->ranking = rank;
}

void PowerUpUltimate::activate() {
    sort(play->current.begin(),play->current.end(),[](PowerUps* p, PowerUps* p2){return p->getRanking()>p2->getRanking();});
}