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
	int index;			//��ͼ�ؿ���
	int Wave_Number;	//����
	GameEnd* gameEnd;

	std::vector<Monster*> monster; //��������

public:
	int money;			//Ǯ
	GameMap* tiledMap;			//��ͼ
	std::vector<Vec2> wayPoints;
	int hp;
	Sprite* ca;

	void CarrotDead();

};

#endif