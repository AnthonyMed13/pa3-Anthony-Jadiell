#pragma once

#include "BoundBlock.h"
#include "Grid.h"
#include "PowerUps.h"
class EntityManager {

public:
	~EntityManager();
	std::vector<Entity*> powerUp;
	std::vector<Entity*> entities;
	std::vector<BoundBlock*> boundBlocks;
	std::vector<Entity*> ghosts;
	std::vector<Grid*> grids;
	std::vector<Entity*> eyes;
	std::vector<std::string> gridText;
	void tick();
	void render();
	void setKillable(bool);

private:
	bool killable = false;
	int killableCounter;
};