#include "stdafx.h"
#include "zagamon.h"


HRESULT zagamon::init()
{
	_dropOn = false;
	_grade= "����ũ";
	_name= "�ڰ����� ����";
	_introduction= "���ݽ� 3��ŭ�� �߰� ���� �������� ����";
	_imageOn = true;

	_itemImg = IMAGEMANAGER->findImage("�ڰ����ǰ���");
	_itemInvenImg = IMAGEMANAGER->findImage("�ڰ����ǰ���");

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