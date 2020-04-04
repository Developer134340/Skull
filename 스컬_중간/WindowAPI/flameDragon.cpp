#include "stdafx.h"
#include "flameDragon.h"


HRESULT flameDragon::init()
{
	_dropOn = false;
	_gravity = 0;
	_fireOn = false;
	_count = _attackCount = 0;
	_imageOn = true;

	_grade = "����ũ";
	_name = "ȭ���� ����";
	_introduction = "��� ����� ����";
	_skillIntroduction = "�÷��� �극�� : ȭ���� ��ȯ�Ͽ� �극���� ������ ������ �����ʿ� ���� ū ���ظ� ����, ���ݷ� +10%";

	_essenceImg = IMAGEMANAGER->findImage("ȭ��������");
	_essenceProfileImg = IMAGEMANAGER->findImage("ȭ��������������");

	IMAGEMANAGER->findImage("�巡����")->setFrameY(0);
	IMAGEMANAGER->findImage("�巡�����")->setFrameY(0);
	IMAGEMANAGER->findImage("�巡���")->setFrameY(0);
	IMAGEMANAGER->findImage("�巡�����")->setFrameY(0);

	return S_OK;
}

void flameDragon::release()
{
}

void flameDragon::update()
{
	_rc = RectMake(_position.x, _position.y - 38, 40, 38);
	_count++;
}

void flameDragon::render()
{
	if (_fireOn == true)
	{
		if (_count - _attackCount > 10 && _count - _attackCount <= 80)
		{
			IMAGEMANAGER->findImage("�巡����")->frameRender(getMemDC(), _vDragonAttack[0].position.x - 53, _vDragonAttack[0].position.y);
		}
		else if (_count - _attackCount > 80 && _count - _attackCount <= 320)
		{
			//Rectangle(getMemDC(), _vDragonAttack[0].attackRc);
			IMAGEMANAGER->findImage("�巡�����")->frameRender(getMemDC(), _vDragonAttack[0].position.x - 40, _vDragonAttack[0].position.y);
		}
		else if (_count - _attackCount > 320)
		{
			IMAGEMANAGER->findImage("�巡����")->alphaFrameRender(getMemDC(), _vDragonAttack[0].position.x - 53, _vDragonAttack[0].position.y, _vDragonAttack[0].alpha);
		}

		if (_count - _attackCount > 80 && _count - _attackCount < 400)
		{
			IMAGEMANAGER->findImage("�巡���")->frameRender(getMemDC(), _vDragonAttack[0].attackRc.left, _vDragonAttack[0].attackRc.top);
		}
		IMAGEMANAGER->findImage("�巡�����")->frameRender(getMemDC(), _vDragonAttack[0].position.x - 20, _vDragonAttack[0].position.y + 50);

	}
}

void flameDragon::fire(RECT playerRc, int playerDirection, POINT imagePosition)
{
	if (KEYMANAGER->isOnceKeyDown('D'))
	{
		if (_fireOn == false)
		{
			_attackCount = _count;
			tagDragon temp;
			for (int i = 0; i < 4; i++)
			{
				temp.index[i] = 0;
			}
			temp.position = PointMake(playerRc.left, playerRc.top - 300);
			temp.exPosition = PointMake(playerRc.left, playerRc.top - 300);
			temp.exImagePosition = imagePosition;
			temp.direction = playerDirection;
			temp.alpha = 0;
			if (playerDirection == 1)//����
			{
				temp.attackRc = RectMake(temp.position.x - 250,  temp.position.y + 150, 220, 180);
			}
			else
			{
				temp.attackRc = RectMake(temp.position.x + 122, temp.position.y + 147, 230, 180);
			}
			_vDragonAttack.push_back(temp);
			_fireOn = true;
		}
	}

	if (_fireOn == true)
	{
		_vDragonAttack[0].position.x = _vDragonAttack[0].exPosition.x + imagePosition.x - _vDragonAttack[0].exImagePosition.x;
		_vDragonAttack[0].position.y = _vDragonAttack[0].exPosition.y + imagePosition.y - _vDragonAttack[0].exImagePosition.y;
		
		if (_vDragonAttack[0].direction == 1)//����
		{
			_vDragonAttack[0].attackRc = RectMake(_vDragonAttack[0].position.x - 250, _vDragonAttack[0].position.y + 150, 220, 180);
		}
		else
		{
			_vDragonAttack[0].attackRc = RectMake(_vDragonAttack[0].position.x + 122, _vDragonAttack[0].position.y + 147, 230, 180);
		}

		//-------------------------�� ��ġ------------------------

		if (_vDragonAttack[0].direction == 1) //����
		{
			IMAGEMANAGER->findImage("�巡����")->setFrameY(1);
			IMAGEMANAGER->findImage("�巡�����")->setFrameY(1);
			IMAGEMANAGER->findImage("�巡���")->setFrameY(1);
		}
		else
		{
			IMAGEMANAGER->findImage("�巡����")->setFrameY(0);
			IMAGEMANAGER->findImage("�巡�����")->setFrameY(0);
			IMAGEMANAGER->findImage("�巡���")->setFrameY(0);
		}

		if (_count % 4 == 0)
		{
			_vDragonAttack[0].index[0]++;
			if (_vDragonAttack[0].index[0] > 18)
			{
				_vDragonAttack[0].index[0] = 18;
			}
			IMAGEMANAGER->findImage("�巡�����")->setFrameX(_vDragonAttack[0].index[0]);
		}

		if (_count % 5 == 0)
		{
			_vDragonAttack[0].index[1]++;
			if (_vDragonAttack[0].index[1] > 10)
			{
				_vDragonAttack[0].index[1] = 0;
			}
			IMAGEMANAGER->findImage("�巡����")->setFrameX(_vDragonAttack[0].index[1]);
		}

		if (_count % 5 == 0)
		{
			_vDragonAttack[0].index[2]++;
			if (_vDragonAttack[0].index[2] > 4)
			{
				_vDragonAttack[0].index[2] = 0;
			}
			IMAGEMANAGER->findImage("�巡�����")->setFrameX(_vDragonAttack[0].index[2]);
		}

		if (_count - _attackCount > 80)
		{
			if (_count % 4 == 0)
			{
				_vDragonAttack[0].index[3]++;
				if (_vDragonAttack[0].index[3] > 63)
				{
					_vDragonAttack[0].index[3] = 63;
				}
				IMAGEMANAGER->findImage("�巡���")->setFrameX(_vDragonAttack[0].index[3]);
			}
		}

		if (_count - _attackCount > 320)
		{
			_vDragonAttack[0].alpha += 5;
			if (_vDragonAttack[0].alpha > 255)
			{
				_vDragonAttack[0].alpha = 255;
			}
		}

	}
	if (_count - _attackCount > 1000)
	{
		_vDragonAttack.clear();
		_fireOn = false;
	}

}
