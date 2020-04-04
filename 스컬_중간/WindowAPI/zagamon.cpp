#include "stdafx.h"
#include "zagamon.h"


HRESULT zagamon::init()
{
	_dropOn = false;
	_grade= "유니크";
	_name= "자가몬의 가시";
	_introduction= "공격시 3만큼의 추가 고정 데미지를 입힘";
	_imageOn = true;

	_itemImg = IMAGEMANAGER->findImage("자가몬의가시");
	_itemInvenImg = IMAGEMANAGER->findImage("자가몬의가시");

	return S_OK;
}

void zagamon::release()
{
}

void zagamon::update()
{
}

void zagamon::render()
{
	if (_imageOn)
	{
		_itemImg->render(getMemDC(), _rc.left, _rc.top);
	}
	else {}
}