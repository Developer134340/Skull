#include "stdafx.h"
#include "sylphid.h"


HRESULT sylphid::init()
{
	_dropOn = false;
	_grade= "레전더리";
	_name="실피드의 날개";
	_introduction= "맵 입장 시 10초간 공격속도와 이동속도 30% 증가";
	_imageOn = true;

	_itemImg = IMAGEMANAGER->findImage("실피드의날개");
	_itemInvenImg = IMAGEMANAGER->findImage("실피드의날개");

	return S_OK;
}

void sylphid::release()
{
}

void sylphid::update()
{
}

void sylphid::render()
{
	if (_imageOn)
	{
		_itemImg->render(getMemDC(), _rc.left, _rc.top);
	}
	else {}
}
