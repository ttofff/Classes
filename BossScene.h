#ifndef BossScene_h
#define BossScene_h
#include "cocos2d.h"
#include "Monster.h"
#include "GameMap.h"
#include "Gamepause.h"
#include "GameEnd.h"
#include "Tower.h"
#include "ui\CocosGUI.h"
#include "SimpleAudioEngine.h"
#include "Bullet.h"

using namespace cocos2d;
using namespace cocos2d::ui;

class BossScene : public Scene
{
public:
	static BossScene* create(int i, int size, int kind);

	bool init() override;
	void update(float dt);
	Sprite* menuBG;
	TextAtlas* curWaveText;
	TextAtlas* totalWaveText;
	int monsterNum;
	int index;			//��ͼ�ؿ���
	int Wave_Number;	//����
	Gamepause* gamepause;
	GameEnd* gameEnd;		//��Ϸ��������

	Vector<Monster*> monster; //��������
	Vector<Tower*> towers;	//��������
	Vector<Bullet*> bullets;	//�ӵ�����
	void createBuildTool();		//��������
	TextAtlas* moneyT;
	void create_UpTool(Tower* tower, int time);		//��������

	void sc(Tower* t, Vector<Tower*> towers);
	int blockSize; // ���ط����С
	int money;					//Ǯ
	GameMap* tiledMap;			//��ͼ
	
	std::vector<Vec2> wayPoints;
	int hp;				//Ѫ��
	Sprite* ca;			//�ܲ�
	Sprite *select;		//����ѡ����
	Sprite* Upselect;		//��������
	void CarrotWin();
	void CarrotDead();		//�ܲ���������
	void SetTowerAnim(Tower* tower);
	void SetHitAnim(Vec2 Position,Bullet* bullet);

	std::vector<std::vector<int>> TowerAllSelect;
	std::vector<int> TowerSelect;

	Monster* monsterselect; 
	bool isselect;
	void RemoveFanbullet(float dt);
	
	int monsterKind;

	float time;
	float lasttime;
};

#endif