#include "stdafx.h"
#include "gunpowderSword.h"


HRESULT gunpowderSword::init()
{
	_dropOn = false;
	_grade = "����";
	_name = "ȭ���";
	_imageOn = true;
	_introduction = "ġ��Ÿ �� �ֺ��� 20��ŭ�� �������� ������ ����";

	_itemImg = IMAGEMANAGER->findImage("ȭ���");
	_itemInvenImg = IMAGEMANAGER->findImage("ȭ���");

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