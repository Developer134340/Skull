#include "stdafx.h"
#include "hearthStone.h"



HRESULT hearthStone::init()
{
	_dropOn = false;
	_grade = "일반";
	_name = "빛 바랜 마석 파편";
	_introduction = "전체체력 +10%";
	_imageOn = true;

	_itemImg = IMAGEMANAGER->findImage("빛바랜마석파편");
	_itemInvenImg = IMAGEMANAGER->findImage("빛바랜마석파편");

	return S_OK;
}

void hearthStone::release()
{
}

void hearthStone::update()
{
}

void hearthStone::render()
{
	if (_imageOn)
	{
		_itemImg->render(getMemDC(), _rc.left, _rc.top);
	}
	else {}
}

