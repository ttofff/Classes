#ifndef HelpScene_h
#define HelpScene_h

#include "cocos2d.h"
using namespace cocos2d;

class HelpScene : public Scene
{
public:
	static HelpScene* create();
	bool init() override;
	static int a;
	const int MAX = 4;
};


#endif