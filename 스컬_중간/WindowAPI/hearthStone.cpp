#include "stdafx.h"
#include "hearthStone.h"



HRESULT hearthStone::init()
{
	_dropOn = false;
	_grade = "�Ϲ�";
	_name = "�� �ٷ� ���� ����";
	_introduction = "��üü�� +10%";
	_imageOn = true;

	_itemImg = IMAGEMANAGER->findImage("���ٷ���������");
	_itemInvenImg = IMAGEMANAGER->findImage("���ٷ���������");

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

