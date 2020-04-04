#include "stdafx.h"
#include "headNormalSkul.h"

HRESULT headNormalSkul::init()
{
	_itemFon = false;
	_dropOn = false;
	_grade = "일반";
	_name = "스컬";
	_imageOn = true;

	_introduction = "마왕성 경비대의 막내 스켈레톤. 다른 스켈레톤에 비해 체구가 작아 리틀본이라 불린다.";

	_itemImg = IMAGEMANAGER->findImage("머리_스컬");
	_itemInvenImg = IMAGEMANAGER->findImage("인벤머리_스컬");
	_itemProfileImg = IMAGEMANAGER->findImage("기본스컬프로필");
	_skulProfileImg = IMAGEMANAGER->findImage("기본스컬");

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
