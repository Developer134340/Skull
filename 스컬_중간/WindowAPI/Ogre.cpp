#include "stdafx.h"
#include "Ogre.h"
#include "player.h"

HRESULT Ogre::init()
{
	EnemyBase::init();

	Stat = ���;
	Direction = ����;	//����
	Hp = 300;			// ü��
	Attck = 15;		// ���ݷ�
	//rc = RectMakeCenter(x, y, 134, 105);		// ���� ��Ʈ
	//ATrc = RectMakeCenter(x, y, 134, 105); 		// ���� ���ݹ���
	//Arc = RectMakeCenter(x, y, 300, 300);		// ���� ��׷ι���
	name = "Ogre";
	Agro = true;
	Live = true;
	DeadE = false;
	Speed = 2.f;
	indexP = true;
	hitcount = 0;
	hitdel = 0;

	_BHP.Hpbar = (int)(Hp * 225 / 300);


	img = IMAGEMANAGER->findImage("OgreIdle");

	OgreDeadE = IMAGEMANAGER->findImage("OgreDF");
	

	return S_OK;
}

void Ogre::release()
{
}

void Ogre::update()
{
	EnemyBase::update();
	OgreRender(15);
	AI();
	HP();
	PlayerEnemyAttack();
	EnemyPlayerAttack(ATrc, Attck);
	_player->getPlayerClass()->DMGHead(rc);

	rc = RectMakeCenter(x + _player->getPlayerClass()->getImagePosition().x, y + _player->getPlayerClass()->getImagePosition().y, img->getFrameWidth(), img->getFrameHeight());		// ���� ��Ʈ
	ATrc = RectMakeCenter(x + _player->getPlayerClass()->getImagePosition().x, y + _player->getPlayerClass()->getImagePosition().y, img->getFrameWidth(), img->getFrameHeight());		// ���� ���ݹ���
}

void Ogre::render()
{
	EnemyBase::render();
	renderMonster(rc, Arc, ATrc);
	img->frameRender(getMemDC(), x - img->getFrameWidth() / 2 + _player->getPlayerClass()->getImagePosition().x, y - img->getFrameHeight() / 2 + _player->getPlayerClass()->getImagePosition().y);
	

	{
		if (KEYMANAGER->isToggleKey('Y'))
		{
			FrameRect(getMemDC(), _BHP.rc, RGB(255, 0, 0));
		}


		_BHP.HPbarBg->render(getMemDC(), _BHP.rc.left, _BHP.rc.top);

		for (int i = 0; i < _BHP.Hpbar; i++)
		{
			_BHP.HPbar->render(getMemDC(), (WINSIZEX/2-(_BHP.Frame->getWidth()/2)+46)+(i*2), _BHP.rc.top+12);
		}
		
		_BHP.Frame->render(getMemDC(), _BHP.rc.left, _BHP.rc.top);
		

	}


	if (DeadE)
	{
		FrameRect(getMemDC(), DeadRc, RGB(255, 0, 0));
		OgreDeadE->frameRender(getMemDC(), DeadRc.left + _player->getPlayerClass()->getImagePosition().x, DeadRc.top + _player->getPlayerClass()->getImagePosition().y);
	}
	//DeadE

}

void Ogre::OgreRender(int ImageSpeed)
{
	if (Live && (Stat == ��� || Stat == �̵�))
	{

		if (Stat == ���)
		{
			img = IMAGEMANAGER->findImage(name + "Idle");
			ICount++;
		}
		if (Stat == �̵�)
		{
			img = IMAGEMANAGER->findImage(name + "move");
			ICount++;
		}


		if (Direction == ������)
		{
			img->setFrameY(0);
		}
		else if (Direction == ����)
		{
			img->setFrameY(1);
		}

		if (Stat == �̵�)
		{
			if (ICount % ImageSpeed == 0)
			{
				IIndex++;
				if (IIndex > img->getMaxFrameX())
				{
					IIndex = 0;
					ICount = 0;
					Acion = false;
				}
				img->setFrameX(IIndex);
			}
		}

		if (Stat == ���)
		{
			delayCount++;
			if (ICount % ImageSpeed == 0)
			{
				IIndex++;
				if (IIndex > img->getMaxFrameX())
				{
					IIndex = 0;
					ICount = 0;
				}
				img->setFrameX(IIndex);
			}

			if (Agro)
			{
				if (delayCount % 200 == 0)
				{
					Acion = false;
					IIndex = 0;
					ICount = 0;
				}
			}
			else
			{
				Acion = false;

			}

		}
	}
	if (!Live)
	{
		img = IMAGEMANAGER->findImage(name + "Dead"); 
		if (Direction == ������)
		{
			img->setFrameY(0);
			OgreDeadE->setFrameY(0);
		}
		else if (Direction == ����)
		{
			img->setFrameY(1);
			OgreDeadE->setFrameY(1);
		}
		if (indexP)
		{
			ICount++;
			if (ICount % ImageSpeed == 0)
			{
				IIndex++;

				if (IIndex == 6)
				{
					DeadE = true;
					indexP = false;
				}
				if (IIndex > img->getMaxFrameX())
				{
					IIndex = img->getMaxFrameX();
				}
				img->setFrameX(IIndex);
			}
		}

		if (DeadE)
		{
			static int DeadCount=0;
			static int DeadIndex=0;

			DeadRc = RectMakeCenter(x+10, y-10, OgreDeadE->getFrameWidth(), OgreDeadE->getFrameHeight());
			DeadCount++;
			if (DeadCount % 5 == 0)
			{
				DeadIndex++;

				if (DeadIndex > OgreDeadE->getMaxFrameX())
				{
					DeadE = false;
					indexP = true;
				}
				OgreDeadE->setFrameX(DeadIndex);
			}
		}
	}
}

void Ogre::AI()
{
	float distance = getDistance(_player->getPlayerClass()->getPlayerPosition().x, _player->getPlayerClass()->getPlayerPosition().y, 
		x + _player->getPlayerClass()->getImagePosition().x, y + _player->getPlayerClass()->getImagePosition().y);

	if (Live)
	{
		if (!Acion)
		{
			if (_player->getPlayerClass()->getPlayerPosition().x > x + _player->getPlayerClass()->getImagePosition().x)
			{
				Direction = ������;
			}
			else if (_player->getPlayerClass()->getPlayerPosition().x < x + _player->getPlayerClass()->getImagePosition().x) { Direction = ����; }
		}
		if (distance > 150)
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

void Ogre::Attack()
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


		if (IIndex == 2)
		{
			if (ICount % 50 == 0)
			{
				IIndex++;
			}
		}
		else
		{
			if (IIndex == 3)
			{
				if (Direction == ����) { x -= 7; }
				else { x += 10; }
				enemyAttackColl = true;
			}
			if (ICount % 7 == 0)
			{
				IIndex++;
				if (IIndex > img->getMaxFrameX())
				{
					IIndex = 0;
					enemyAttackColl = false;
					Stat = ���;
				}
				img->setFrameX(IIndex);
			}
		}

	}
}

void Ogre::HP()
{
	RECT nullrc;
	_BHP.Hpbar = (int)(Hp * 225 / 300);
	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		if (IntersectRect(&nullrc, &rc, &_player->getPlayerClass()->getPlayerRc()))
		{
			Hp -= RND->range(10, 20);
			hitcount += 1;
			

			if (Stat != ����)
			{
				Stat = �ǰ�;
			}
		}
	}

	if (Stat == �ǰ�)
	{

		if (_player->getPlayerClass()->getPlayerPosition().x > x)
		{
			Direction = ������;
		}
		else if (_player->getPlayerClass()->getPlayerPosition().x < x) { Direction = ����; }
		if (Direction == ������) { img->setFrameY(0); }
		else { img->setFrameY(1); }


		float distance = getDistance(_player->getPlayerClass()->getPlayerPosition().x, _player->getPlayerClass()->getPlayerPosition().y, x, y);
		hitdel++;
		if (hitcount % 2 == 0)
		{
			img = IMAGEMANAGER->findImage("OgreHit");
			if (hitdel % 30 == 0)
			{
				hitcount = 0;
				hitdel = 0;
				if (distance > 150)
				{
					Stat = �̵�;
				}
				else { Stat = ����; }
			}
		}
		else if (hitcount % 2 == 1)
		{
			img = IMAGEMANAGER->findImage("OgreHit2");
			if (hitdel % 30 == 0)
			{
				hitcount = 0;
				hitdel = 0;
				if (distance > 150)
				{
					Stat = �̵�;
				}
				else { Stat = ����; }
			}
		}
		if (hitcount >= 10)
		{
			hitcount = 0;
			hitdel = 0;
			if (distance > 150)
			{
				Stat = �̵�;
			}
			else { Stat = ����; }
		}
	}

	if (Hp <= 0)
	{
		Live = false;
	}
}
