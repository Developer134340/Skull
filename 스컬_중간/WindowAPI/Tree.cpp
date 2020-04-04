#include "stdafx.h"
#include "Tree.h"
#include "player.h"

HRESULT Tree::init()
{
	EnemyBase::init();

	Stat = ���;
	Direction = rand() % 2;	//����
	x = WINSIZEX / 2;
	y = WINSIZEY / 2;		// ��ǥ
	Hp = 50;			// ü��
	maxhp = Hp;
	Attck = 15;		// ���ݷ�
	name = "Tree";
	Live = true;
	Speed = 1.f;
	damageP = false;

	img = IMAGEMANAGER->findImage("TreeIdle");

	return S_OK;
}

void Tree::release()
{
}

void Tree::update()
{
	EnemyBase::update();
	if (Live)
	{
		RECT temp;
		AgroJudgment();
		AI();
		Hpbar();

		if (IntersectRect(&temp, &_player->getPlayerClass()->getPlayerRc(), &ATrc) && !damageP && Stat == ���� && img->getFrameX() >= 1)
		{
			_player->getPlayerClass()->setPlayerHp(_player->getPlayerClass()->getPlayerHp() - Attck);
			damageP = true;
		}
	}


	if (Hp <= 0)
	{
		Hp = 0;
		Live = false;
	}

	FrameMonsterI(15);
	//================================================================
	rc = RectMakeCenter(x + _player->getPlayerClass()->getImagePosition().x, y + _player->getPlayerClass()->getImagePosition().y, img->getFrameWidth(), img->getFrameHeight());		// ���� ��Ʈ
	ATrc = RectMakeCenter(x + _player->getPlayerClass()->getImagePosition().x, y + _player->getPlayerClass()->getImagePosition().y, img->getFrameWidth(), img->getFrameHeight()); 		// ���� ���ݹ���
	Arc = RectMakeCenter(x + _player->getPlayerClass()->getImagePosition().x, y + _player->getPlayerClass()->getImagePosition().y, img->getFrameWidth() + 400, img->getFrameHeight() + 400);		// ��
	//================================================================
}

void Tree::render()
{
	EnemyBase::render();
	renderMonster(rc, Arc, ATrc);
	ImageRender();
	hpbarrender();
}

void Tree::AI()
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
			if (distance > 60)
			{
				if (!Acion)
				{
					Stat = �̵�;
				}
			}
			else
			{
				if (!Acion )
				{
					Stat = ����;
				}
			Attack();
			}
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
			
			if (moveCount % RND->range(120,170) == 0)
			{
				Stat = ���;
			}
		}

	}

}

void Tree::Attack()
{
	if (Stat == ����)
	{
		static int ICount = 0;
		static int IIndex = 0;
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
			if (ICount % 40 == 0)
			{
				IIndex++;
			}
		}
		else
		{
			if (ICount % 20 == 0)
			{
				IIndex++;
				if (IIndex > img->getMaxFrameX())
				{
					IIndex = 0;
					Stat = ���;
					damageP = false;
				}
				img->setFrameX(IIndex);
			}
		}
	}
}
