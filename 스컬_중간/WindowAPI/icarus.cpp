#include "stdafx.h"
#include "icarus.h"

HRESULT icarus::init()
{
	_dropOn = false;
	_grade = "����ũ";
	_name = "��ī�罺�� �ܰ�";
	_introduction = "���߿��� ���� �� ������ +50%, ���󿡼� -20%";
	_imageOn = true;

	_itemImg = IMAGEMANAGER->findImage("��ī�罺�Ǵܰ�");
	_itemInvenImg = IMAGEMANAGER->findImage("��ī�罺�Ǵܰ�");

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
