#ifndef AdventureFirstScene_h
#define AdventureFirstScene_h

#include "cocos2d.h"
using namespace cocos2d;

class AdventureFirstScene : public Scene
{
public:
	CREATE_FUNC(AdventureFirstScene);
	bool init() override;
	static int a;
	const int MAX = 7;
private:
	
};

#endif