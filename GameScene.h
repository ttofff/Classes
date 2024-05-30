#ifndef GameScene_h
#define GameScene_h

#include "cocos2d.h"
#include "Monster.h"
using namespace cocos2d;

class GameScene : public Scene
{
public:
	static GameScene* create(int i);
	bool init() override;
	void getWayPoints();
	void update(float dt);
public:
	int money;			//Ǯ
	TMXTiledMap* tiledMap;			//��ͼ
	std::vector<Vec2> wayPoints;
	Monster* monster;


};

#endif