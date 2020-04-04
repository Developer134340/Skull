#pragma once

#include "gameNode.h"
#include "loading.h"

class LoadingScene : public gameNode
{
private:
	loading* _loading;
	int		 _frameCount;
;
public:
	HRESULT init();
	void release();
	void update();
	void render();

	void loadingImage();
	void loadingSound();

	LoadingScene() {}
	~LoadingScene() {}
};

