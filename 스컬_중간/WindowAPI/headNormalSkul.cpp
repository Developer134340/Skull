#include "stdafx.h"
#include "headNormalSkul.h"

HRESULT headNormalSkul::init()
{
	_itemFon = false;
	_dropOn = false;
	_grade = "�Ϲ�";
	_name = "����";
	_imageOn = true;

	_introduction = "���ռ� ������ ���� ���̷���. �ٸ� ���̷��濡 ���� ü���� �۾� ��Ʋ���̶� �Ҹ���.";

	_itemImg = IMAGEMANAGER->findImage("�Ӹ�_����");
	_itemInvenImg = IMAGEMANAGER->findImage("�κ��Ӹ�_����");
	_itemProfileImg = IMAGEMANAGER->findImage("�⺻����������");
	_skulProfileImg = IMAGEMANAGER->findImage("�⺻����");

	return S_OK;
}

void headNormalSkul::release()
{
}

void headNormalSkul::update()
{
}

void headNormalSkul::render()
{
}
