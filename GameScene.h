#ifndef GameScene_h
#define GameScene_h

#include "cocos2d.h"
using namespace cocos2d;

class GameScene : public Scene
{
public:
	static GameScene* create(int i);
	bool init() override;
public:
	int money;

	int index;

	TMXTiledMap* tileMap;
};

#endif