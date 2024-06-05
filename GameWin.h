#ifndef GameWin_h
#define GameWin_h

#include "cocos2d.h"
using namespace cocos2d;

class GameWin : public Scene
{
public:
	CREATE_FUNC(GameWin);
	bool init() override;
	void SetWave(int SWaveNumber);
	void SetTotalWave();
	void SetMapIndex(int index);

	void SetBlockSize(int size);
private:
	int blockSize; // ÏñËØ·½¿é´óÐ¡

};

#endif