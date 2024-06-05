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
	int index;			//��ͼ�ؿ���
	int Wave_Number;	//����
	GameEnd* gameEnd;		//��Ϸ��������

	Vector<Monster*> monster; //��������
	Vector<Tower*> towers;	//��������
	Vector<Bullet*> bullets;	//�ӵ�����
	void createBuildTool();		//��������
	TextAtlas* moneyT;
	void create_UpTool(Tower* tower, int time);		//��������

	void sc(Tower* t, Vector<Tower*> towers);
private:
	
	int money;					//Ǯ
	GameMap* tiledMap;			//��ͼ
	
	std::vector<Vec2> wayPoints;
	int hp;				//Ѫ��
	Sprite* ca;			//�ܲ�
	Sprite *select;		//����ѡ����
	Sprite* Upselect;		//��������
	void CarrotDead();		//�ܲ���������
	void SetTowerAnim(Tower* tower);
};

#endif