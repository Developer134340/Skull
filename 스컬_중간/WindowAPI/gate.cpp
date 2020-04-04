#include "stdafx.h"
#include "gate.h"

HRESULT gate::init(string gateKey, POINT position)
{
	_fOn = false;
	_count = _index = 0;
	_position = position;

	gateImg = new image;
	
	if (gateKey == "NOTING_GATE")
	{
		gateImg = IMAGEMANAGER->findImage("NOTING_GATE");
	}
	else if (gateKey == "NOMAL_GATE")
	{
		gateImg = IMAGEMANAGER->findImage("NOMAL_GATE");
	}
	else if (gateKey == "SKULL_GATE")
	{
		gateImg = IMAGEMANAGER->findImage("SKULL_GATE");
	}
	else if (gateKey == "ITEM_GATE")
	{
		gateImg = IMAGEMANAGER->findImage("ITEM_GATE");
	}
	else if (gateKey == "SHOP_GATE")
	{
		gateImg = IMAGEMANAGER->findImage("SHOP_GATE");
	}
	else if (gateKey == "CHAPTER_GATE")
	{
		gateImg = IMAGEMANAGER->findImage("CHAPTER_GATE");
	}
	else if (gateKey == "MIDBOSS_GATE")
	{
		gateImg = IMAGEMANAGER->findImage("MIDBOSS_GATE");
	}
	else if (gateKey == "LASTBOSS_GATE")
	{
		gateImg = IMAGEMANAGER->findImage("LASTBOSS_GATE");
	}
	_rc = RectMake(_position.x, _position.y - gateImg->getFrameHeight(), gateImg->getFrameWidth(), gateImg->getFrameHeight());

	return S_OK;
}

void gate::release()
{	
}

bool gate::update(POINT imagePosition, RECT playerRc)
{
	_rc = RectMake(_position.x + imagePosition.x, _position.y + imagePosition.y - gateImg->getFrameHeight(), gateImg->getFrameWidth(), gateImg->getFrameHeight());
	
	RECT temp;

	if (IntersectRect(&temp, &_rc, &playerRc))
	{
		_fOn  = true;
	}
	else
	{
		_fOn = false;
	}

	_count++;
	gateImg->setFrameY(0);
	if (_count % 8 == 0)
	{
		_index++;
		if (_index > 7)
		{
			_index = 0;
		}
		gateImg->setFrameX(_index);
	}

	return _fOn;
}

void gate::render()
{
	gateImg->frameRender(getMemDC(), _rc.left, _rc.top);
	if (_fOn == true)
	{
		IMAGEMANAGER->findImage("F_KEY")->render(getMemDC(), _rc.left + (_rc.right - _rc.left) / 2 - 15, _rc.top - 50);
	}
}