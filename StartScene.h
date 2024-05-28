#ifndef StartScene_h
#define StartScene_h

#include "cocos2d.h"
using namespace cocos2d;

class StartScene : public Scene
{
public:
	static StartScene* create();
	bool init() override;
};

#endif