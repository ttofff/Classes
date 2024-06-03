#ifndef GameScene_h
#define GameScene_h
#include "cocos2d.h"
#include "Monster.h"
#include "GameMap.h"
#include "GameEnd.h"
#include "Tower.h"
#include "ui\CocosGUI.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace cocos2d::ui;

class GameScene : public Scene
{
public:
	static GameScene* create(int i);
	bool init() override;
	void update(float dt);			
	int index;			//地图关卡数
	int Wave_Number;	//波数
	GameEnd* gameEnd;		//游戏结束界面

	std::vector<Monster*> monster; //怪物容器
	std::vector<Tower*> towers;	//炮塔容器
	void createBuildTool();
	TextAtlas* moneyT;
	

private:
	
	int money;			//钱
	GameMap* tiledMap;			//地图
	
	std::vector<Vec2> wayPoints;
	int hp;				//血量
	Sprite* ca;			//萝卜
	Sprite *select;
	void CarrotDead();		//萝卜死亡函数
	
};

#endif