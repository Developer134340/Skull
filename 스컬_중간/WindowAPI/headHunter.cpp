#include "stdafx.h"
#include "headHunter.h"

HRESULT headHunter::init()
{
	_itemFon = false;
	_dropOn = false;
	_grade = "레어";
	_name = "헌터";
	_imageOn = true;

	_introduction = "활과 화살로 영웅이 되고자 했던 모험가";

	_itemImg = IMAGEMANAGER->findImage("머리_헌터");
	_itemInvenImg = IMAGEMANAGER->findImage("인벤머리_헌터");
	_itemProfileImg = IMAGEMANAGER->findImage("헌터스컬프로필");
	_skulProfileImg = IMAGEMANAGER->findImage("헌터스컬");

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
