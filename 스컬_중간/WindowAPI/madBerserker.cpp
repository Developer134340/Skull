#include "stdafx.h"
#include "madBerserker.h"

HRESULT madBerserker::init()
{
	_dropOn = false;
	_grade= "·¹¾î";
	_name= "±¤Àü»çÀÇÀå°©";
	_introduction= "ÀÒÀº Ã¼·Â 1%´ç °ø°Ý¼Óµµ 0.5%¾¿ ÃÖ´ë 40%±îÁö Áõ°¡";
	_imageOn = true;

	_itemImg = IMAGEMANAGER->findImage("±¤Àü»çÀÇÀå°©");
	_itemInvenImg = IMAGEMANAGER->findImage("±¤Àü»çÀÇÀå°©");

	return S_OK;
}

void madBerserker::release()
{
}

void madBerserker::update()
{
}

void madBerserker::render()
{
	if (_imageOn)
	{
		_itemImg->render(getMemDC(), _rc.left, _rc.top);
	}
	else {}
}