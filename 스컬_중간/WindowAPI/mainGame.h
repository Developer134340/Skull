#pragma once

#include "gameNode.h"
#include "LoadingScene.h"
#include "TitleScene.h"
#include "OpeningScene.h"
#include "StartMapScene.h"
#include "TutorialScene_1.h"
#include "TutorialScene_2.h"
#include "TutorialScene_3.h"
#include "TutorialScene_4.h"
#include "TutorialScene_5.h"
#include "ShopScene.h"
#include "ItemScene.h"
#include "SkullScene.h"
#include "FieldScene_1.h"
#include "FieldScene_2.h"
#include "BossReadyScene.h"
#include "BossScene.h"

class mainGame : public gameNode
{
private:

public:
	HRESULT init();
	void release();
	void update();
	void render();

	mainGame() {}
	~mainGame() {}
};

