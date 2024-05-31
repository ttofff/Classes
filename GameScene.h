#ifndef GameScene_h
#define GameScene_h

#include "cocos2d.h"
#include "Monster.h"
#include "GameMap.h"
#include "GameEnd.h"
using namespace cocos2d;

class GameScene : public Scene
{
public:
	static GameScene* create(int i);
	bool init() override;
	void update(float dt);	
	int index;			//地图关卡数
	int Wave_Number;	//波数
	GameEnd* gameEnd;

	std::vector<Monster*> monster; //怪物容器

public:
	int money;			//钱
	GameMap* tiledMap;			//地图
	std::vector<Vec2> wayPoints;
	int hp;
	Sprite* ca;

	void CarrotDead();

};

#endif