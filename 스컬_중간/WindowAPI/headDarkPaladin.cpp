#include "stdafx.h"
#include "headDarkPaladin.h"

HRESULT headDarkPaladin::init()
{
	_itemFon = false;
	_dropOn = false;
	_grade = "����ũ";
	_name = "��ũ�ȶ��";
	_imageOn = true;
	_introduction = "Į���� ������� ������ �����ϴ� ���� ������ �����";

	_itemImg = IMAGEMANAGER->findImage("�Ӹ�_��ũ�ȶ��");
	_itemInvenImg = IMAGEMANAGER->findImage("�κ��Ӹ�_��ũ�ȶ��");
	_itemProfileImg = IMAGEMANAGER->findImage("��ũ�ȶ����������");
	_skulProfileImg = IMAGEMANAGER->findImage("��ũ�ȶ����");

	return S_OK;
}

void headDarkPaladin::release()
{
}

void headDarkPaladin::update()
{
}

void headDarkPaladin::render()
{
}
