#include "stdafx.h"
#include "sylphid.h"


HRESULT sylphid::init()
{
	_dropOn = false;
	_grade= "��������";
	_name="���ǵ��� ����";
	_introduction= "�� ���� �� 10�ʰ� ���ݼӵ��� �̵��ӵ� 30% ����";
	_imageOn = true;

	_itemImg = IMAGEMANAGER->findImage("���ǵ��ǳ���");
	_itemInvenImg = IMAGEMANAGER->findImage("���ǵ��ǳ���");

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
