#ifndef GameScene_h
#define GameScene_h
#include "cocos2d.h"
#include "Monster.h"
#include "GameMap.h"
#include "GameEnd.h"
#include "Tower.h"
#include "ui\CocosGUI.h"
#include "SimpleAudioEngine.h"
#include "Bullet.h"

using namespace cocos2d;
using namespace cocos2d::ui;

class GameScene : public Scene
{
public:
	static GameScene* create(int i);
	bool init() override;
	void update(float dt);			
	int index;			//µØÍ¼¹Ø¿¨Êı
	int Wave_Number;	//²¨Êı
	GameEnd* gameEnd;		//ÓÎÏ·½áÊø½çÃæ

	Vector<Monster*> monster; //¹ÖÎïÈİÆ÷
	std::vector<Tower*> towers;	//ÅÚËşÈİÆ÷
	Vector<Bullet*> bullets;	//ÅÚËşÈİÆ÷
	void createBuildTool();
	TextAtlas* moneyT;
	

private:
	
	int money;			//Ç®
	GameMap* tiledMap;			//µØÍ¼
	
	std::vector<Vec2> wayPoints;
	int hp;				//ÑªÁ¿
	Sprite* ca;			//ÂÜ²·
	Sprite *select;
	void CarrotDead();		//ÂÜ²·ËÀÍöº¯Êı
	void SetTowerAnim(Tower* tower);
	
};

#endif