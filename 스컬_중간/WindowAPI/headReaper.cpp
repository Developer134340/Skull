#include "stdafx.h"
#include "headReaper.h"

HRESULT headReaper::init()
{
	_itemFon = false;
	_dropOn = false;
	_grade = "��������";
	_name = "�׸�����";
	_imageOn = true;
	_introduction = "������ �����ϴ� ����� ��";
	_itemImg = IMAGEMANAGER->findImage("�Ӹ�_����");
	_itemInvenImg = IMAGEMANAGER->findImage("�κ��Ӹ�_����");
	_itemProfileImg = IMAGEMANAGER->findImage("���۽���������");
	_skulProfileImg = IMAGEMANAGER->findImage("���۽���");
	return S_OK;
}

void headReaper::release()
{
}

void headReaper::update()
{
}

void headReaper::render()
{
}
