#include "stdafx.h"
#include "icarus.h"

HRESULT icarus::init()
{
	_dropOn = false;
	_grade = "유니크";
	_name = "이카루스의 단검";
	_introduction = "공중에서 공격 시 데미지 +50%, 지상에서 -20%";
	_imageOn = true;

	_itemImg = IMAGEMANAGER->findImage("이카루스의단검");
	_itemInvenImg = IMAGEMANAGER->findImage("이카루스의단검");

	return S_OK;
}

void icarus::release()
{
}

void icarus::update()
{
}

void icarus::render()
{
	if (_imageOn)
	{
		_itemImg->render(getMemDC(), _rc.left, _rc.top);
	}
	else {}
}
