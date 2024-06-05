#ifndef GameScene_h
#define GameScene_h
#include "cocos2d.h"
#include "Monster.h"
#include "GameMap.h"
#include "Gamepause.h"
#include "GameWin.h"
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
	static GameScene* create(int i, int size);
	bool init() override;
	void update(float dt);
	Sprite* menuBG;
	TextAtlas* curWaveText;
	int index;			//地图关卡数
	int Wave_Number;	//波数
	int monsterNum; // 怪物数量
	Gamepause* gamepause;
	GameWin* gameWin;
	GameEnd* gameEnd;		//游戏结束界面

	Vector<Monster*> monster; //怪物容器
	Vector<Tower*> towers;	//炮塔容器
	Vector<Bullet*> bullets;	//子弹容器
	void createBuildTool();		//建塔工具
	TextAtlas* moneyT;
	void create_UpTool(Tower* tower, int time);		//升级工具

	void sc(Tower* t, Vector<Tower*> towers);
	int blockSize; // 像素方块大小
	int money;					//钱
	GameMap* tiledMap;			//地图
	
	std::vector<Vec2> wayPoints;
	int hp;				//血量
	Sprite* ca;			//萝卜
	Sprite *select;		//建塔选择精灵
	Sprite* Upselect;		//升级精灵
	void CarrotWin();
	void CarrotDead();		//萝卜死亡函数
	void SetTowerAnim(Tower* tower);


	Monster* monsterselect; 
	bool isselect;
};

#endif