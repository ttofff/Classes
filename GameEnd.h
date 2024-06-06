#ifndef GameEnd_h
#define GameEnd_h

#include "cocos2d.h"
using namespace cocos2d;

class GameEnd : public Scene
{
public:
	CREATE_FUNC(GameEnd);
	bool init() override;
	void SetLoseInterface();
	void SetWinInterface();
	void SetWave(int SWaveNumber);
	void SetTotalWave();
	void SetCurrIndex(int index);
	void SetMapIndex(int index);
	void SetNextIndex(int index);

	void SetBlockSize(int size);

	void SetMonsterKind(int kind);
private:
	int blockSize; // ÏñËØ·½¿é´óÐ¡

	int monsterKind;

};

#endif