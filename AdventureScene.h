#ifndef AdventureScene_h
#define AdventureScene_h

#include "cocos2d.h"
using namespace cocos2d;

class AdventureScene : public Scene
{
public:
	CREATE_FUNC(AdventureScene);
	bool init() override;

	static int n;

};

#endif