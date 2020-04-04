#include "stdafx.h"
#include "Knight.h"
#include "player.h"

HRESULT Knight::init()
{
	EnemyBase::init();

	Stat = ���;
	Direction = rand() % 2;	//����
	Hp = 80;			// ü��
	maxhp = Hp;
	Attck = 10;		// ���ݷ�
	name = "Knight";
	Live = true;
	Speed = 2.f;

	img = IMAGEMANAGER->findImage("KnightIdle");

	return S_OK;
}

void Knight::release()
{
}

void Knight::update()
{
	EnemyBase::update();
	if (Live)
	{
		AgroJudgment();
		AI();
		PlayerEnemyAttack();
		EnemyPlayerAttack(ATrc, Attck);
		Hpbar();
	}
	FrameMonsterI(6);

	if (Hp <= 0)
	{
		Hp = 0;
		Live = false;
	}

	//================================================================
	rc = RectMakeCenter(x + _player->getPlayerClass()->getImagePosition().x, y + _player->getPlayerClass()->getImagePosition().y, img->getFrameWidth(), img->getFrameHeight());		// ���� ��Ʈ
	ATrc = RectMakeCenter(x + _player->getPlayerClass()->getImagePosition().x, y + _player->getPlayerClass()->getImagePosition().y, img->getFrameWidth(), img->getFrameHeight()); 		// ���� ���ݹ���
	Arc = RectMakeCenter(x + _player->getPlayerClass()->getImagePosition().x, y + _player->getPlayerClass()->getImagePosition().y, img->getFrameWidth() + 460, img->getFrameHeight() + 460);		// ���� ��׷ι���
	//================================================================
}

void Knight::render()
{
	EnemyBase::render();
	ImageRender();
	renderMonster(rc, Arc, ATrc);
	hpbarrender();
}

void Knight::AI()
{
	if (Agro)
	{
		float distance = getDistance(_player->getPlayerClass()->getPlayerPosition().x, _player->getPlayerClass()->getPlayerPosition().y, 
			x + _player->getPlayerClass()->getImagePosition().x, y + _player->getPlayerClass()->getImagePosition().y);

		{
			if (!Acion)
			{
				if (_player->getPlayerClass()->getPlayerPosition().x > x + _player->getPlayerClass()->getImagePosition().x)
				{
					Direction = ������;
				}
				else if (_player->getPlayerClass()->getPlayerPosition().x < x + _player->getPlayerClass()->getImagePosition().x) { Direction = ����; }
			}
			if (distance > 50)
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

}

void Knight::Attack()
{	
	if (Stat == ����)
	{
		img = IMAGEMANAGER->findImage(name + "Attack");
		ICount++;
		Acion = true;
		if (Direction == ������)
		{
			img->setFrameY(0);
		}
		else { img->setFrameY(1); }

		
		if (IIndex == 0)
		{
			if (ICount % 80 == 0)
			{
				IIndex++;
			}
		}
		else if (IIndex == 4)
		{
			if (ICount % 50 == 0)
			{
				IIndex++;
			}
		}
		else
		{
			if (IIndex < 4)
			{
				if (Direction == ����) { x -= 3; }
				else { x += 3; }
			}
			if (ICount % 8 == 0)
			{
				IIndex++;
				if (IIndex > img->getMaxFrameX())
				{
					IIndex = 0;
					Stat = ���;
					enemyAttackColl = false;
				}
				img->setFrameX(IIndex);
			}
		}
		if (IIndex == 2)
		{
			enemyAttackColl = true;

		}
	}	
}
