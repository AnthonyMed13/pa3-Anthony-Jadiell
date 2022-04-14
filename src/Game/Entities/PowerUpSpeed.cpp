#include "Animation.h"
#include "EntityManager.h"
#include "PowerUps.h"
#include "Player.h"
#include "PowerUpSpeed.h"

PowerUpSpeed::PowerUpSpeed(Player* played)
{
   this->play = played;
}

void PowerUpSpeed::activate() {
   play->setSpeed(10);
}
