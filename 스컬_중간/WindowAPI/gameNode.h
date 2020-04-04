#pragma once

#include "image.h"

//백버퍼 이미지를 이미지매니져에 담아두기
static image* _backBuffer = IMAGEMANAGER->addImage("backBuffer", WINSIZEX, WINSIZEY);

class Player;

class gameNode
{
private:
	HDC _hdc;		//화면 HDC

public:
	// Font 관련 변수
	LOGFONT _lf;
	HFONT _font;
	HFONT _oldFont;
	char _dir[256];

protected:
	Player* _player;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	
	//백버퍼 이미지 얻기
	image* getBackBuffer() { return _backBuffer; }

	//화면 HDC 얻기
	HDC getHDC() { return _hdc; }
	
	//메모리 DC 얻기
	HDC getMemDC() { return _backBuffer->getMemDC(); }

	void setPlayer(Player* pl) { _player = pl; }


	LRESULT CALLBACK MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
	inline void changeFont(int Height, COLORREF color)
	{
		memset(&_lf, 0, sizeof(_lf));
		_lf.lfHeight = Height;
		_lf.lfWeight = 1000;
		_lf.lfOutPrecision = OUT_TT_ONLY_PRECIS;
		strcpy(_lf.lfFaceName, "Oswald-Bold");

		_font = CreateFontIndirect(&_lf);

		_oldFont = (HFONT)SelectObject(getMemDC(), _font);

		SetBkMode(getMemDC(), TRANSPARENT);
		SetTextColor(getMemDC(), color);
	}

	gameNode() {}
	virtual ~gameNode() {}
};

