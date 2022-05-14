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
#include "PowerUpUltimate.h"

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
    if(found==true){
        for(Entity* powerUp: em->entities){
            if(dynamic_cast<PowerUps*> (powerUp) && found3==false){
                findMaze(x,y);
                found3=true;
        found=false;
    }
    }
    }
    if(found2==true){
        ofSetColor(255,153,51);
        for(int i=0; i<coordRecord.size(); i++){
            if(coordRecord[coordRecord.size()-2].first>=x && coordRecord[coordRecord.size()-2].second>=y){
                if(coordRecord[i].first>=x && coordRecord[i].second>=y){
                    ofDrawCircle(coordRecord[i].first+7, coordRecord[i].second+5,3);
        }
        }else if(coordRecord[coordRecord.size()-2].first>=x && coordRecord[coordRecord.size()-2].second<=y){
                if(coordRecord[i].first>=x && coordRecord[i].second<=y){
                    ofDrawCircle(coordRecord[i].first+7, coordRecord[i].second+5,3);
        }
        }else if(coordRecord[coordRecord.size()-2].first<=x && coordRecord[coordRecord.size()-2].second>=y){
                if(coordRecord[i].first<=x && coordRecord[i].second>=y){
                    ofDrawCircle(coordRecord[i].first+7, coordRecord[i].second+5,3);
        }
        }else if(coordRecord[coordRecord.size()-2].first<=x && coordRecord[coordRecord.size()-2].second<=y){
                if(coordRecord[i].first<=x && coordRecord[i].second<=y){
                    ofDrawCircle(coordRecord[i].first+7, coordRecord[i].second+5,3);
        }
        }
        }
        if(x==coordRecord[coordRecord.size()-1].first && y==coordRecord[coordRecord.size()-1].second){
            found2=false;
            found3=false;
            coordRecord.clear();
        }
    }

    if(current.size() > 0)
    {
        for(int i = 0; i<current.size();i++)
        {
                ofDrawBitmapString(to_string(current[i]->getRanking()), ofGetWidth()/2 + 40*i + 300, 50);
        }
    }
    if(score>=1000){
        int tempx = 504;
        int tempy = 400;
        tempR = 10;
        if(once5 == false){
            ultimatePower= new PowerUpUltimate(this->x,this->y,width,height, this,4);
            ofSetColor(120,81,169);
            ofDrawCircle(tempx+8,tempy-34,tempR);
        }

    }
}

string Player::findMaze(int x, int y)
{
        if (y < 80 || y > 672) {
            return "";
        }

        if (x < 216|| x > 792) {
            return "";
        }
        for(Entity* powerUp: em->entities) { 
            if(dynamic_cast<PowerUps*> (powerUp)){
            if(x==powerUp->getX() && y==powerUp->getY()){
            return to_string(x) + "," + to_string(y) + ",";
        }
        }
        }
        for(Entity* block: em->boundBlocks) {
            if(x==block->getX() && y==block->getY()){
                return ""; 
        }
        }
        for(pair<int,int> record: coordRecord) {
            if(x==record.first && y==record.second){
                return ""; 
        }
        }
        coordRecord.push_back(make_pair(x,y));
        string path = findMaze(x, y-16);

        if (!path.empty()) {
            return to_string(x) + "," + to_string(y) + "," + path;
        }
        path = findMaze(x+16, y);
        if (!path.empty()) {
            return to_string(x) + "," + to_string(y) + "," + path;
        }  
        path = findMaze(x, y+16);
        if (!path.empty()) {
            return to_string(x) + "," + to_string(y) + "," + path;
        }  
        path = findMaze(x-16, y);
        if (!path.empty()) {
            return to_string(x) + "," + to_string(y) + "," + path;
        } 
        return "";;
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
        case '1':
            found=true;
            found2= !found2;
            break;
            
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
            if(dynamic_cast<PowerUpUltimate*>(entity) && score>=1000){
                entity->remove = true;
                tempR=0;
                powerUpOn= true;
                if(once4 == false){
                    ultimatePower->activate();
                    once4 = true;
                    once5 = true;
                }

            }
        }
    }
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
