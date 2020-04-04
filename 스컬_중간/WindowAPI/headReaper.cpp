#include "stdafx.h"
#include "headReaper.h"

HRESULT headReaper::init()
{
	_itemFon = false;
	_dropOn = false;
	_grade = "레전더리";
	_name = "그림리퍼";
	_imageOn = true;
	_introduction = "죽음을 관장하는 명계의 신";
	_itemImg = IMAGEMANAGER->findImage("머리_리퍼");
	_itemInvenImg = IMAGEMANAGER->findImage("인벤머리_리퍼");
	_itemProfileImg = IMAGEMANAGER->findImage("리퍼스컬프로필");
	_skulProfileImg = IMAGEMANAGER->findImage("리퍼스컬");
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
