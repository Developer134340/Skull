#include "stdafx.h"
#include "kaleon.h"

HRESULT kaleon::init()
{
	_dropOn = false;
	_grade ="�Ϲ�";
	_name ="������ Į���� ��";
	_introduction ="���ݷ� +10%";
	_imageOn = true;

	_itemImg = IMAGEMANAGER->findImage("������Į���°�");
	_itemInvenImg = IMAGEMANAGER->findImage("������Į���°�");

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