#include "stdafx.h"
#include "headHunter.h"

HRESULT headHunter::init()
{
	_itemFon = false;
	_dropOn = false;
	_grade = "����";
	_name = "����";
	_imageOn = true;

	_introduction = "Ȱ�� ȭ��� ������ �ǰ��� �ߴ� ���谡";

	_itemImg = IMAGEMANAGER->findImage("�Ӹ�_����");
	_itemInvenImg = IMAGEMANAGER->findImage("�κ��Ӹ�_����");
	_itemProfileImg = IMAGEMANAGER->findImage("���ͽ���������");
	_skulProfileImg = IMAGEMANAGER->findImage("���ͽ���");

	return S_OK;
}

void headHunter::release()
{
}

void headHunter::update()
{
}

void headHunter::render()
{
}
