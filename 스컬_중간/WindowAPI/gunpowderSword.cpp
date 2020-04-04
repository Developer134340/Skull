#include "stdafx.h"
#include "gunpowderSword.h"


HRESULT gunpowderSword::init()
{
	_dropOn = false;
	_grade = "레어";
	_name = "화약검";
	_imageOn = true;
	_introduction = "치명타 시 주변에 20만큼의 데미지를 입히는 폭발";

	_itemImg = IMAGEMANAGER->findImage("화약검");
	_itemInvenImg = IMAGEMANAGER->findImage("화약검");

	return S_OK;
}

void gunpowderSword::release()
{
}

void gunpowderSword::update()
{
}

void gunpowderSword::render()
{ 
	if (_imageOn)
	{
		_itemImg->render(getMemDC(), _rc.left, _rc.top);
	}
	else {}
}