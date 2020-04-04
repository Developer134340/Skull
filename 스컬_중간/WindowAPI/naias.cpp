#include "stdafx.h"
#include "naias.h"

HRESULT naias::init()
{
	_dropOn = false;
	_gravity = 0;
	_fireOn = false;
	_count = 0;
	_imageOn = true;

	_grade = "일반";
	_name = "나이아스의 정수";
	_introduction = "물과 얼음의 권속";
	_skillIntroduction = "아이시클: 4방향으로 얼음조각을 날림";

	_essenceImg = IMAGEMANAGER->findImage("나이아스의정수");
	_essenceProfileImg = IMAGEMANAGER->findImage("나이아스의정수프로필");

	return S_OK;
}

void naias::release()
{
}

void naias::update()
{
	_rc = RectMake(_position.x, _position.y - 38, 40, 38);
	_count++;
}

void naias::render()
{
	if (_fireOn == true)
	{
		if (_vAttack[0].on == true)
		{
			IMAGEMANAGER->findImage("나이아스의정수공격")->render(getMemDC(), _vAttack[0].rc.left, _vAttack[0].rc.top);
		}
		else {}
		if (_vAttack[1].on == true)
		{
			IMAGEMANAGER->findImage("나이아스의정수공격2")->render(getMemDC(), _vAttack[1].rc.left, _vAttack[1].rc.top);
		}
		else {}
		if (_vAttack[2].on == true)
		{
			IMAGEMANAGER->findImage("나이아스의정수공격3")->render(getMemDC(), _vAttack[2].rc.left, _vAttack[2].rc.top);
		}
		else {}
		if (_vAttack[3].on == true)
		{
			IMAGEMANAGER->findImage("나이아스의정수공격4")->render(getMemDC(), _vAttack[3].rc.left, _vAttack[3].rc.top);
		}
		else {}
	}
}

void naias::fire(RECT playerRc, int playerDirection, POINT imagePosition)
{
	if (KEYMANAGER->isOnceKeyDown('D'))
	{
		if (_fireOn == false)
		{
			for (int i = 0; i < 4; i++)
			{
				_skillCount = _count;
				tagAttack temp;
				temp.position = PointMake(playerRc.left + (playerRc.right - playerRc.left) / 2, playerRc.top + (playerRc.bottom - playerRc.top) / 2);
				temp.rc = RectMake(temp.position.x + imagePosition.x, temp.position.y - 17 + imagePosition.y, 33, 17);
				temp.angle = i * 1.046f;
				temp.speed = 5;
				temp.on = true;
				_vAttack.push_back(temp);
			}
			_fireOn = true;
		}
	}

	if (_fireOn == true)
	{
		for (int i = 0; i < _vAttack.size(); i++)
		{
			_vAttack[i].position.x += _vAttack[i].speed * cosf(_vAttack[i].angle);
			_vAttack[i].position.y -= _vAttack[i].speed * sinf(_vAttack[i].angle);
			_vAttack[i].rc = RectMake(_vAttack[i].position.x, _vAttack[i].position.y - 17, 33, 17);
			_vAttack[i].speed++;

			if (_vAttack[i].position.x > WINSIZEX || _vAttack[i].position.y < 0 || _vAttack[i].position.x < 0)
			{
				_vAttack[i].on = false;
				_vAttack[i].rc = { -10000, -10000, -10000, -10000 };
			}

			if (_count - _skillCount > 400)		//쿨타임확인
			{
				_vAttack.clear();
				_fireOn = false;
			}
		}
	}
}