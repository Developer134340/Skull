#include "stdafx.h"
#include "essenceBase.h"


HRESULT essenceBase::init()
{
	
	return S_OK;
}

void essenceBase::release()
{
}

void essenceBase::update()
{
}

void essenceBase::render()
{
}


void essenceBase::fire(RECT playerRc, int playerDirection, POINT imagePosition)
{
}

void essenceBase::dropEssence(POINT pos)
{
	if (_dropOn == false)
	{
		_dropOn = true;
		_position = pos;
	}

	if (_dropOn == true)
	{
		_rc = RectMake(_position.x, _position.y, 40, 38);
		_position.y -= 6;
		_position.y += _gravity;
		_gravity += 0.25;
		_position.x = pos.x;

		if (_position.y >= pos.y)
		{
			_position.y = pos.y;
		}
	}
}

void essenceBase::getEssence(RECT playerRect)	//renderÇÔ¼ö
{
	RECT temp;

	if (_imageOn == false) {}
	else
	{
		_essenceImg->render(getMemDC(), _rc.left, _rc.top);

		if (IntersectRect(&temp, &playerRect, &_rc))
		{
			_essenceFon = true;
		}
	}

	if (_essenceFon && _imageOn)
	{
		IMAGEMANAGER->render("F_KEY", getMemDC(), _position.x + 25, _position.y - 150);
		IMAGEMANAGER->render("ITEM_NAME", getMemDC(), _position.x - 60, _position.y - 115);
		RECT textRc = RectMake(_position.x - 60, _position.y - 115, 170, 50);
		SetTextColor(getMemDC(), RGB(255, 255, 255));
		SetBkMode(getMemDC(), TRANSPARENT);
		DrawText(getMemDC(), _name, -1, &textRc, DT_VCENTER | DT_CENTER | DT_SINGLELINE);

	}
}

void essenceBase::showEssence(RECT essencePosition)
{
	_rc = essencePosition;
	_position = { essencePosition.left, essencePosition.top };
}
