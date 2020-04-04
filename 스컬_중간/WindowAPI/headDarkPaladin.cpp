#include "stdafx.h"
#include "headDarkPaladin.h"

HRESULT headDarkPaladin::init()
{
	_itemFon = false;
	_dropOn = false;
	_grade = "유니크";
	_name = "다크팔라딘";
	_imageOn = true;
	_introduction = "칼레온 병사들을 공포에 떨게하던 검은 갑옷의 성기사";

	_itemImg = IMAGEMANAGER->findImage("머리_다크팔라딘");
	_itemInvenImg = IMAGEMANAGER->findImage("인벤머리_다크팔라딘");
	_itemProfileImg = IMAGEMANAGER->findImage("다크팔라딘스컬프로필");
	_skulProfileImg = IMAGEMANAGER->findImage("다크팔라딘스컬");

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
