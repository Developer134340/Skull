#include "stdafx.h"
#include "potion.h"

HRESULT potion::init(potionSize ps, POINT pos)
{
	_count = 0;
	_index = 0;
	_potionSize = ps;
	_position = pos;
	_gravity = 0;
	_initPosition = pos;
	_speed = 6;
	_dropOn = false;

	if (ps == S)
	{
		_percent = 0.1;
		_potionImg = IMAGEMANAGER->findImage("备浇S");
	}
	else if (ps == M)
	{
		_percent = 0.2;
		_potionImg = IMAGEMANAGER->findImage("备浇M");
	}
	else if (ps == L)
	{
		_percent = 0.3;
		_potionImg = IMAGEMANAGER->findImage("备浇L");
	}
	else if (ps == XL)
	{
		_percent = 0.5;
		_potionImg = IMAGEMANAGER->findImage("备浇XL");
	}

	_rc = RectMake(_position.x, _position.y - _potionImg->getFrameHeight(), _potionImg->getFrameWidth(),
		_potionImg->getHeight());

	return S_OK;
}

void potion::release()
{
	SAFE_DELETE(_potionImg);
}

void potion::update(POINT imagePosition)
{
	this->potionDrop(imagePosition);

	_rc = RectMake(_position.x, _position.y - _potionImg->getFrameHeight(), _potionImg->getFrameWidth(),
		_potionImg->getFrameHeight());

	_count++;
	if (_count % 10 == 0)
	{
		_index++;
		if (_index > 8)
		{
			_index = 0;
		}
		_potionImg->setFrameX(_index);
	}
}

void potion::render()
{
	_potionImg->frameRender(getMemDC(), _rc.left, _rc.top);
}

void potion::potionDrop(POINT imagePosition)
{
	if (_dropOn == false)
	{
	_exImagePosition = imagePosition;
	_dropOn = true;
	_exPosition = _initPosition;
	}

	if (_dropOn == true)
	{
		_exPosition.y -= _speed;
		_exPosition.y += _gravity;
		_position.y = _exPosition.y + imagePosition.y - _exImagePosition.y;
		_position.x = _exPosition.x + imagePosition.x - _exImagePosition.x;
		_gravity += 0.25;

		if (_position.y >= _initPosition.y + imagePosition.y - _exImagePosition.y)
		{
			_position.y = _initPosition.y + imagePosition.y - _exImagePosition.y;
			_position.x = _initPosition.x + imagePosition.x - _exImagePosition.x;
		}

	}

}