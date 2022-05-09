#include "Player.h"
#include "EntityManager.h"
#include "Dot.h"
#include "BigDot.h"
#include "Ghost.h"
#include "PowerUpCherry.h"
#include "PowerUpStraw.h"
#include "PowerUpRandom.h"
#include "ChoosePlayerState.h"
#include "globalStatus.h"
#include "GhostEyes.h"
#include <algorithm>
#include "trackingmaze.h"

Player::Player(int x, int y, int width, int height, EntityManager* em) : Entity(x, y, width, height){
    spawnX = x;
    spawnY = y;
    switch(status){
        case false:
            sprite.load("images/mspacman.png");
            break;
        case true:
            sprite.load("images/pacman.png");
            break;
    }
    down.cropFrom(sprite, 0, 48, 16, 16);
    up.cropFrom(sprite, 0, 32, 16, 16);
    left.cropFrom(sprite, 0, 16, 16, 16);
    right.cropFrom(sprite, 0, 0, 16, 16);
    
    vector<ofImage> downAnimframes;
    vector<ofImage> upAnimframes;
    vector<ofImage> leftAnimframes;
    vector<ofImage> rightAnimframes;
    ofImage temp;
    for(int i=0; i<3; i++){
        temp.cropFrom(sprite, i*16, 48, 16, 16);
        downAnimframes.push_back(temp);
    }
    for(int i=0; i<3; i++){
        temp.cropFrom(sprite, i*16, 32, 16, 16);
        upAnimframes.push_back(temp);
    }
    for(int i=0; i<3; i++){
        temp.cropFrom(sprite, i*16, 16, 16, 16);
        leftAnimframes.push_back(temp);
    }
    for(int i=0; i<3; i++){
        temp.cropFrom(sprite, i*16, 0, 16, 16);
        rightAnimframes.push_back(temp);
    }
    walkDown = new Animation(1,downAnimframes);
    walkUp = new Animation(1,upAnimframes);
    walkLeft = new Animation(1,leftAnimframes);
    walkRight = new Animation(1,rightAnimframes);

    cherryPower = new PowerUpCherry(this->x,this->y,width,height, this,em,1);
    strawPower = new PowerUpStraw(this->x,this->y,width,height,this,2);
    randomPower = new PowerUpRandom(this->x,this->y,width,height,this,3);
    //track = new trackingmaze(nullptr,this);
    //current;
    this->em = em;

    moving = MLEFT;
    
}
void Player::setSkin(bool sk){
    skin = sk;
}

void Player::setX(int xs){
    x = xs;
}
void Player::setY(int ys){
    y = ys;
}

void Player::setW(int ws){
    width = ws;
}

void Player::setH(int hs){
    height = hs;
}

void Player::setInv(bool pO){
    Inv = pO;
}

void Player::tick(){
    if(Inv == true){
        powerCounter--;
        if (powerCounter == 0){
            Inv = false;
            width = 16;
            height = 16;
        }
    }

    checkCollisions();

    if (moving == MUP && canMoveUp) 
        facing = UP;
    else if (moving == MDOWN && canMoveDown) 
        facing = DOWN;
    else if (moving == MLEFT && canMoveLeft) 
        facing = LEFT;
    else if (moving == MRIGHT && canMoveRight)
        facing = RIGHT;

    if(facing == UP && canMoveUp){
        y-= speed;
        walkUp->tick();
    }else if(facing == DOWN && canMoveDown){
        y+=speed;
        walkDown->tick();
    }else if(facing == LEFT && canMoveLeft){
        x-=speed;
        walkLeft->tick();
    }else if(facing == RIGHT && canMoveRight){
        x+=speed;
        walkRight->tick();
    }
}

void Player::render(){
    ofSetColor(256,256,256);
    // ofDrawRectangle(getBounds());

    if(facing == UP)
        walkUp->getCurrentFrame().draw(x, y, width, height);
    else if(facing == DOWN)
        walkDown->getCurrentFrame().draw(x, y, width, height);
    else if(facing == LEFT)
        walkLeft->getCurrentFrame().draw(x, y, width, height);
    else if(facing == RIGHT)
        walkRight->getCurrentFrame().draw(x, y, width, height);
    
    ofSetColor(256, 0, 0);
    ofDrawBitmapString("Health: ", ofGetWidth()/2 + 100, 50);

    for(unsigned int i=0; i<health; i++){
        ofDrawCircle(ofGetWidth()/2 + 25*i +200, 50, 10);
    }
    ofDrawBitmapString("Score:"  + to_string(score), ofGetWidth()/2-200, 50);

    if(current.size() > 0)
    {
        for(int i = 0; i<current.size();i++)
        {
                ofDrawBitmapString(to_string(current[i]->getRanking()), ofGetWidth()/2 + 40*i + 300, 50);
        }
    }
}

void Player::keyPressed(int key){
    switch(key){
        case 'w':
            moving = MUP;
            break;
        case 's':
            moving = MDOWN;
            break;
        case 'a':
            moving = MLEFT;;
            break;
        case 'd':
            moving = MRIGHT;;
            break;
        case 'n':
            die();
            break;
        case 'm':
            if (health<3){health++;}
            else{}
            break;
        case ' ':
            if (current.size() > 0){
                current.front()->activate();
                current.erase(current.begin());
            }
            break;
        case 'i':
            sort(current.begin(),current.end(),[](PowerUps* p, PowerUps* p2) {return p->getRanking() > p2->getRanking();});
            break;
        case 'l':
            track->activate();
            
    }
}

void Player::keyReleased(int key){
    if(key == 'w' || key =='s' || key == 'a' || key == 'd'){
        walking = false;
    }
}
void Player::mousePressed(int x, int y, int button){

}

int Player::getHealth(){ return health; }
int Player::getScore(){ return score; }
FACING Player::getFacing(){ return facing; }
void Player::setHealth(int h){ health = h; }
void Player::setFacing(FACING facing){ this->facing = facing; }
void Player::setScore(int h){ score = h; }
int Player::getDotsConsumed(){return dotsConsumed;}
void Player::setDotsConsumed(int count){dotsConsumed= count;}

void Player::checkCollisions(){
    canMoveUp = true;
    canMoveDown = true;
    canMoveLeft = true;
    canMoveRight = true;

    for(BoundBlock* boundBlock: em->boundBlocks){
        if(this->getBounds(x, y-speed).intersects(boundBlock->getBounds()))
            canMoveUp = false;
        if(this->getBounds(x, y+speed).intersects(boundBlock->getBounds()))
            canMoveDown = false;
        if(this->getBounds(x-speed, y).intersects(boundBlock->getBounds()))
            canMoveLeft = false;
        if(this->getBounds(x+speed, y).intersects(boundBlock->getBounds()))
            canMoveRight = false;
    }
    for(Entity* entity:em->entities){
        if(collides(entity)){
            if(dynamic_cast<Dot*>(entity) || dynamic_cast<BigDot*>(entity)){
                entity->remove = true;
                score += 10;
                setDotsConsumed(getDotsConsumed()+1);
            }
            if(dynamic_cast<BigDot*>(entity)){
                score +=20;
                em->setKillable(true);
            }
            if(dynamic_cast<PowerUpCherry*>(entity)){
                entity->remove = true;
                powerUpOn = true;
                if(once1 == false)
                {
                    current.push_back(cherryPower);
                    once1 = true;
                }
            }
            if(dynamic_cast<PowerUpStraw*>(entity)){
                entity->remove = true;
                powerUpOn = true;
                if(once2 == false)
                {
                    current.push_back(strawPower);
                    once2 = true;
                }
                setDotsConsumed(getDotsConsumed()+1);
            }
            if(dynamic_cast<PowerUpRandom*>(entity)){
                entity->remove = true;
                powerUpOn = true;
                if(once3 == false)
                {
                    current.push_back(randomPower);
                    once3 = true;
                }
                setDotsConsumed(getDotsConsumed()+1);
            }
        }
    }
    //spriteG.load("images/Background");
    for(Entity* entity:em->ghosts){
        if(collides(entity)){
            Ghost* ghost = dynamic_cast<Ghost*>(entity);
            if(ghost->getKillable())
            {
                GhostEyes* test = new GhostEyes(x,y,width,height,ghost->moves,em);
                em->entities.push_back(test);
                ghost->remove = true;
            }
            else if(Inv == false)
                die();
        }
    }

}

void Player::die(){
    health--;
    x = spawnX;
    y = spawnY;

}

Player::~Player(){
    delete walkUp;
    delete walkDown;
    delete walkLeft;
    delete walkRight;
}
