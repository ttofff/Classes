#ifndef GameScene_h
#define GameScene_h

#include "cocos2d.h"
#include "Monster.h"
#include "GameMap.h"
using namespace cocos2d;

class GameScene : public Scene
{
public:
	static GameScene* create(int i);
	bool init() override;
	void update(float dt);	
	int index;			//地图关卡数

	std::vector<Monster*> monster; //怪物容器

public:
	int money;			//钱
	GameMap* tiledMap;			//地图
	std::vector<Vec2> wayPoints;
	int hp;
	Sprite* ca;

};

#endif