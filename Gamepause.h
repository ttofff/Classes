#ifndef __Gamepause__h
#define __Gamepause__h

#include "cocos2d.h"
USING_NS_CC;
class Gamepause : public cocos2d::Scene
{
public:
	virtual bool init();
	CREATE_FUNC(Gamepause);
	void RestartMap(int index);
	
public:
	int index;

};

#endif // __Gamepause_H__