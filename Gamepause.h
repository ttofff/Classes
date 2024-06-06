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

	void SetBlockSize(int size);

	void SetMonsterKind(int kind);

public:
	int index;
	int blockSize; // ÏñËØ·½¿é´óĞ¡

	int monsterKind;

};

#endif // __Gamepause_H__