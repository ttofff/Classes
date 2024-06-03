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
	int index;			//��ͼ�ؿ���
	int Wave_Number;	//����
	GameEnd* gameEnd;		//��Ϸ��������

	std::vector<Monster*> monster; //��������
	std::vector<Tower*> towers;	//��������
	void createBuildTool();
	TextAtlas* moneyT;
	

private:
	
	int money;			//Ǯ
	GameMap* tiledMap;			//��ͼ
	
	std::vector<Vec2> wayPoints;
	int hp;				//Ѫ��
	Sprite* ca;			//�ܲ�
	Sprite *select;
	void CarrotDead();		//�ܲ���������
	
};

#endif