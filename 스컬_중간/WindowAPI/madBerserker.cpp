#include "stdafx.h"
#include "madBerserker.h"

HRESULT madBerserker::init()
{
	_dropOn = false;
	_grade= "����";
	_name= "���������尩";
	_introduction= "���� ü�� 1%�� ���ݼӵ� 0.5%�� �ִ� 40%���� ����";
	_imageOn = true;

	_itemImg = IMAGEMANAGER->findImage("���������尩");
	_itemInvenImg = IMAGEMANAGER->findImage("���������尩");

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