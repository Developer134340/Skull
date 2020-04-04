#include "stdafx.h"
#include "GreenTree.h"
#include "player.h"

HRESULT GreenTree::init()
{
	EnemyBase::init();

	Stat = ���;
	Direction = rand() % 2;	//����
	x = WINSIZEX / 2;
	y = WINSIZEY / 2;		// ��ǥ
	Hp = 100;			// ü��
	maxhp = Hp;
	Attck = 20;		// ���ݷ�
	TmpX = 0;
	

	name = "GreenTree";
	Live = true;
	RageAttck = false;
	AimOn = false;
	Speed = 1.f;
	alp = 0;

	img = IMAGEMANAGER->findImage("GreenTreeIdle");
	Effect = IMAGEMANAGER->findImage("GreenTreeAttackEffet");


	return S_OK;
}

void GreenTree::release()
{
}

void GreenTree::update()
{
	EnemyBase::update();
	if (Live)
	{
		AgroJudgment();
		AI();
		Hpbar();
		if (RageAttck &&enemyAttackColl)
		{
			RECT Temp;
			if (IntersectRect(&Temp, &RangeRc, &_player->getPlayerClass()->getPlayerRc()));
			{
				_player->getPlayerClass()->setPlayerHp(_player->getPlayerClass()->getPlayerHp() - Attck);
				enemyAttackColl = false;
			}
		}
	}
	if (Hp <= 0)
	{
		Hp = 0;
		Live = false;
	}
	
	FrameMonsterI(12);
	//================================================================
	rc = RectMakeCenter(x + _player->getPlayerClass()->getImagePosition().x, y + _player->getPlayerClass()->getImagePosition().y, img->getFrameWidth(), img->getFrameHeight());		// ���� ��Ʈ
	Arc = RectMakeCenter(x + _player->getPlayerClass()->getImagePosition().x, y + _player->getPlayerClass()->getImagePosition().y, img->getFrameWidth() + 1000, img->getFrameHeight() + 1000);		// ���� ��׷ι���
	RangeRc = RectMakeCenter(TmpX + _player->getPlayerClass()->getImagePosition().x, _player->getPlayerClass()->getPlayerPosition().y + _player->getPlayerClass()->getImagePosition().y, Effect->getFrameWidth()+1000, Effect->getFrameHeight()+1000);
	//================================================================
}

void GreenTree::render()
{
	EnemyBase::render();
	renderMonster(rc, Arc, ATrc);
	
	if (AimOn)
	{
		Aim->alphaRender(getMemDC(), RangeRc.left, RangeRc.bottom, alp);
	}
	if (RageAttck)
	{
		Effect->frameRender(getMemDC(), RangeRc.left, RangeRc.top);
	}
	ImageRender();
	hpbarrender();
}

void GreenTree::AI()
{
	float distance = getDistance(_player->getPlayerClass()->getPlayerPosition().x, _player->getPlayerClass()->getPlayerPosition().y,
		x + _player->getPlayerClass()->getImagePosition().x, y + _player->getPlayerClass()->getImagePosition().y);
	if (Agro)
	{
		{
			if (!Acion)
			{
				if (_player->getPlayerClass()->getPlayerPosition().x > x)
				{
					Direction = ������;
				}
				else if (_player->getPlayerClass()->getPlayerPosition().x < x) { Direction = ����; }
			}
			if (distance > 1000)
			{
				if (!Acion)
				{
					Stat = �̵�;
				}
			}
			else
			{
				if (!Acion)
				{
					Stat = ����;
				}
			}
			Attack();
		}

		if (Stat == �̵� && Direction == ������)
		{
			x += Speed;
		}
		else if (Stat == �̵� && Direction == ����)
		{
			x -= Speed;
		}
	}
	else
	{
		if (Stat == ���)
		{
			static int redyCount = 0;
			redyCount++;


			if (redyCount % 70 == 0)
			{
				Direction = rand() % 2;
				Stat = �̵�;
			}

		}
		if (Stat == �̵�)
		{
			static int moveCount = 0;
			moveCount++;
			if (Direction == ������) { x += Speed; }
			else { x -= Speed; }

			if (moveCount % RND->range(120, 170) == 0)
			{
				Stat = ���;
			}
		}

	}
}

void GreenTree::Attack()
{
	if (Stat == ����)
	{
		static int ICount = 0;
		static int IIndex = 0;
		img = IMAGEMANAGER->findImage(name + "Attack");
		Acion = true;
		if (Direction == ������)
		{
			img->setFrameY(0);
		}
		else { img->setFrameY(1); }


		if (IIndex != 2)
		{
			ICount++;

			if (ICount % 10 == 0)
			{
				IIndex++;
				if (IIndex > img->getMaxFrameX())
				{
					IIndex = 0;
					Stat = ���;
				}
			}
		}
		if (IIndex == 1){TmpX = _player->getPlayerClass()->getPlayerPosition().x;}
		if (IIndex == 2)
		{
			AimOn = true;
			if (AimOn) { IIndex = 2; }
		}
	
		if (AimOn)
		{
			alp += 4;
			if (alp >= 255)
			{
				alp = 0;
				IIndex += 1;
				RageAttck = true;
				AimOn = false;
			}
		}

		img->setFrameX(IIndex);
	}

	if (RageAttck)
	{
		static int EffectCount = 0;
		static int EffectIndex = 0;

		EffectCount++;
		if (EffectCount % 7 == 0)
		{
			EffectIndex++;
			if (EffectIndex > Effect->getMaxFrameX())
			{
				EffectIndex = 0;
				RageAttck = false;
			}
		}
		Effect->setFrameX(EffectIndex);
	}

}
