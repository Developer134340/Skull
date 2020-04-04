#include "stdafx.h"
#include "itemBase.h"

HRESULT itemBase::init()
{

	return S_OK;
}

void itemBase::release()
{
}

void itemBase::update()
{
}

void itemBase::render()
{
}

void itemBase::dropItem(POINT pos)
{
	if (_dropOn == false)
	{
		_dropOn = true;
		_position = pos;
		_gravity = 0;
	}
	_rc = RectMake(_position.x, _position.y, 84, 81);
	_position.y -= 7;
	_position.y += _gravity;
	_gravity += 0.25;
	_position.x = pos.x;

	if (_position.y > pos.y + 20)
	{
		_position.y = pos.y + 20;
	}
}

void itemBase::getItem(RECT playerRect)	//renderÇÔ¼ö
{
	RECT temp;

	if (_imageOn == false) {}
	else
	{
		_itemImg->render(getMemDC(), _rc.left, _rc.top);

		if (IntersectRect(&temp, &playerRect, &_rc))
		{
			_itemFon = true;
		}
	}

	if (_itemFon && _imageOn)
	{
		IMAGEMANAGER->render("F_KEY", getMemDC(), _position.x + 25, _position.y - 150);
		IMAGEMANAGER->render("ITEM_NAME", getMemDC(), _position.x - 45, _position.y - 80);
		RECT textRc = RectMake(_position.x - 45, _position.y - 80, 170, 50);
		SetTextColor(getMemDC(), RGB(255, 255, 255));
		SetBkMode(getMemDC(), TRANSPARENT);
		DrawText(getMemDC(), _name, -1, &textRc, DT_VCENTER | DT_CENTER | DT_SINGLELINE);
	}

}

void itemBase::showItem(RECT itemPosition)
{
	_rc = itemPosition;
	_position = PointMake( itemPosition.left, itemPosition.top );
}