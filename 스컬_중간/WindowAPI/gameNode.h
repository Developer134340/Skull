#pragma once

#include "image.h"

//����� �̹����� �̹����Ŵ����� ��Ƶα�
static image* _backBuffer = IMAGEMANAGER->addImage("backBuffer", WINSIZEX, WINSIZEY);

class Player;

class gameNode
{
private:
	HDC _hdc;		//ȭ�� HDC

public:
	// Font ���� ����
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
	
	//����� �̹��� ���
	image* getBackBuffer() { return _backBuffer; }

	//ȭ�� HDC ���
	HDC getHDC() { return _hdc; }
	
	//�޸� DC ���
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

