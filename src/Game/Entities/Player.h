#pragma once

#include "Animation.h"
#include "EntityManager.h"
#include "PowerUps.h"


enum MOVING {
	MUP,
	MDOWN,
	MLEFT,
	MRIGHT,
};
class Player: public Entity{

    private:
        int spawnX, spawnY;
        unsigned int health=3;
        int score=0;
        bool canMoveUp, canMoveDown, canMoveRight, canMoveLeft;
        int speed = 4;
        bool Inv = false;
        bool walking = false;
        MOVING moving;
        FACING facing = DOWN;
        ofImage up, down, left, right;
        Animation *walkUp;
        Animation *walkDown;
        Animation *walkLeft;
        Animation *walkRight;
        EntityManager* em;
        int dotsConsumed=0;

    public:
        Player(int, int, int , int, EntityManager*);
        ~Player();
        int getHealth();
        int getScore();
        int getDotsConsumed();
        FACING getFacing();
        void setHealth(int);
        void setScore(int);
        void setFacing(FACING facing);
        void tick();
        void render();
        void keyPressed(int);
        void keyReleased(int);
        void damage(Entity* damageSource);
        void mousePressed(int, int, int);
        void reset();
        void checkCollisions();
        void die();
        void setDotsConsumed(int);
        void setSpeed(int s) {speed = s;}
        int getSpeed() {return speed;}
        void setX(int);
        void setY(int);
        void setW(int);
        void setH(int);
        void setInv(bool);
        bool getInv() {return Inv;}
        bool powerUpOn = false;
        PowerUps *current;
        PowerUps *speedPower;
        PowerUps *cherryPower;
        PowerUps *strawPower;
        PowerUps *randomPower;
        int powerCounter=2*10;


};