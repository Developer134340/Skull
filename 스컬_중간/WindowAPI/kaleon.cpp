#include "stdafx.h"
#include "kaleon.h"

HRESULT kaleon::init()
{
	_dropOn = false;
	_grade ="일반";
	_name ="보급형 칼레온 검";
	_introduction ="공격력 +10%";
	_imageOn = true;

	_itemImg = IMAGEMANAGER->findImage("보급형칼레온검");
	_itemInvenImg = IMAGEMANAGER->findImage("보급형칼레온검");

	return S_OK;
}

void kaleon::release()
{
}

void kaleon::update()
{
}

void kaleon::render()
{
	if (_imageOn)
	{
		_itemImg->render(getMemDC(), _rc.left, _rc.top);
	}
	else {}
}