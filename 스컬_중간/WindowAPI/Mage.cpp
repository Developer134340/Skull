#include "stdafx.h"
#include "Mage.h"
#include "player.h"



HRESULT Mage::init()
{
	EnemyBase::init();

	Stat = 순간이동;
	Direction = rand()%2;	//방향
	x = WINSIZEX / 2;
	y = WINSIZEY / 2;		// 좌표
	Hp = 80;			// 체력
	maxhp = Hp;
	Attck = 10;		// 공격력
	name = "Mage";
	Live = true;
	coll = true;
	fireCount = 0;
	Range = 700;
	Agro = true;
	AttackCount = 0;

	_fire.Index = 0;
	_fire.Count = 0;
	_fire.HitIndex = 0;
	_fire.HitCount = 0;
	_fire.Hit = false;
	_fire.fire = false;
	_fire.damageP = false;

	//==========

	
	
	TelIn = false;
	TelOut = false;
	alpa = 255;
	TIndex = 0;
	TCount = 0;
	TelGo = false;

	//==========



	img = IMAGEMANAGER->findImage("MageIdle"); 

	fireboll = IMAGEMANAGER->findImage("fire");
	fireHit = IMAGEMANAGER->findImage("fireHit");
	
	TelEin = IMAGEMANAGER->findImage("TelInEF");
	TelEOut = IMAGEMANAGER->findImage("TelOutEF");

	return S_OK;
}

void Mage::release()
{
}

void Mage::update()
{
	EnemyBase::update();
	if (Live)
	{
		PlayerEnemyAttack();
		AgroJudgment();
		AI();
		Hpbar();
	}
	if (Hp <= 0)
	{
		Hp = 0;
		Live = false;
	}
	FrameMonsterI(10);
	//================================================================

	rc = RectMakeCenter(x + _player->getPlayerClass()->getImagePosition().x, y + _player->getPlayerClass()->getImagePosition().y, img->getFrameWidth(), img->getFrameHeight());		// 몬스터 렉트
	ATrc = RectMakeCenter(x + _player->getPlayerClass()->getImagePosition().x, y + _player->getPlayerClass()->getImagePosition().y, img->getFrameWidth()+610, img->getFrameHeight()+610); 		// 몬스터 공격범위
	Arc = RectMakeCenter(x + _player->getPlayerClass()->getImagePosition().x, y + _player->getPlayerClass()->getImagePosition().y, img->getFrameWidth() + 610, img->getFrameHeight() + 610);		// 몬스터 어그로범위
	TelERc = RectMakeCenter(x + _player->getPlayerClass()->getImagePosition().x, y + _player->getPlayerClass()->getImagePosition().y,TelEin->getFrameWidth(), TelEin->getFrameHeight());

	
	//================================================================

}

void Mage::render()
{
	EnemyBase::render();
	renderMonster(rc, Arc, ATrc);
	mageRender();
	fireF();
	hpbarrender();
}

void Mage::mageRender()
{
	if (Stat != 순간이동)
	{
		if (Live)
		{
			img->frameRender(getMemDC(), x - img->getFrameWidth() / 2, y - img->getFrameHeight() / 2);
		}

		else
		{
			static int alpha = 255;
			alpha -= 2;
			if (alpha < 0)
			{
				alpha = 0;
			}
			img->alphaRender(getMemDC(), x - img->getWidth() / 2, y - img->getHeight() / 2 + 20, alpha);
		}
	}

	if (Stat ==순간이동)
	{

		if (img == IMAGEMANAGER->findImage("TelIn"))
		{
			img->frameRender(getMemDC(), x - img->getFrameWidth() / 2, y - img->getFrameHeight() / 2);	
		}

		if (img == IMAGEMANAGER->findImage("TelInA"))
		{
			alpa -= 6;
			if (alpa <= 0)
			{
				alpa = 0;
				TelOut = true;
				img = IMAGEMANAGER->findImage("telOutA");
			}
			img->alphaRender(getMemDC(), x - img->getWidth() / 2, y - img->getHeight() / 2, alpa);
		}
		if (img == IMAGEMANAGER->findImage("telOutA"))
		{
			alpa += 10;
			if (alpa >= 255)
			{
				alpa = 255;
				TelOut = false;
				coll = true;
				Stat = 공격;
			}
			img->alphaRender(getMemDC(), x - img->getWidth() / 2, y - img->getHeight() / 2, alpa);
		}

		if (TelIn)
		{
			TelEin->frameRender(getMemDC(), TelERc.left, TelERc.top);
		}
		if (TelOut)
		{
			TelEOut->frameRender(getMemDC(), TelERc.left, TelERc.top);
		}
	}
}

void Mage::AI()
{
	float distance = getDistance(_player->getPlayerClass()->getPlayerPosition().x, _player->getPlayerClass()->getPlayerPosition().y,
		x + _player->getPlayerClass()->getImagePosition().x, y + _player->getPlayerClass()->getImagePosition().y);
	if (Agro)
	{
		if (!Acion)
		{
			if (_player->getPlayerClass()->getPlayerPosition().x > x)
			{
				Direction = 오른쪽;
			}
			else if (_player->getPlayerClass()->getPlayerPosition().x < x) { Direction = 왼쪽; }

			if (distance < 700 && _vfire.empty())
			{
				Stat = 공격;
			}
			else { Stat = 대기; }
		}

		Attack();
	}
	Tel();
}

void Mage::Attack()
{
	if (Stat == 공격)
	{
		static int ICount = 0;
		static int IIndex = 0;
		img = IMAGEMANAGER->findImage(name + "Attack");
		Acion = true;
		if (Direction == 오른쪽)
		{
			img->setFrameY(0);
		}
		else { img->setFrameY(1); }

		if (IIndex != 5)
		{
			ICount++;

			if (ICount % 10 == 0)
			{
				IIndex++;
				img->setFrameX(IIndex);
			}
		}
		if (IIndex == 5)
		{
			if (_vfire.empty())
			{
				for (int i = 0; i < 3; i++)
				{
					_fire.x = x;
					_fire.y = y;
					_fire.speed = 5.f;
					_fire.rc = RectMakeCenter(_fire.x, _fire.y, fireboll->getFrameWidth(), fireboll->getFrameHeight());
					_fire.HitRc = RectMakeCenter(_fire.x, _fire.y, 5, 5);
					_vfire.push_back(_fire);

				}
			}

			fireCount++;

			if (fireCount % 25 == 0)
			{
				_vfire[AttackCount].angle = 

					_fire.angle = getAngle(

						_fire.x,
						_fire.y,
						_player->getPlayerClass()->getPlayerPosition().x,
						_player->getPlayerClass()->getPlayerPosition().y
					);

				_vfire[AttackCount].fire = true;
				AttackCount ++;
				if (AttackCount == 3)
				{
					ICount = 0;
					IIndex = 0;
					Stat = 대기;
					AttackCount = 0;
				}
			}
		}
	}


	
	for (int i = 0; i < _vfire.size(); i++)
	{
		if (_vfire[i].fire && !_vfire[i].Hit)
		{
			_vfire[i].distance = getDistance(_vfire[i].x, _vfire[i].y, x, y);
			_vfire[i].x += cosf(_vfire[i].angle)*_vfire[i].speed;
			_vfire[i].y += -sinf(_vfire[i].angle)*_vfire[i].speed;
			_vfire[i].rc = RectMakeCenter(_vfire[i].x, _vfire[i].y, fireboll->getFrameWidth(), fireboll->getFrameHeight());
			_vfire[i].HitRc = RectMakeCenter(_vfire[i].x, _vfire[i].y, 5, 5);

			if (Range < _vfire[i].distance)
			{
				_vfire[i].Hit = true;
			}
		}
	}
}

void Mage::fireF()
{
	for (int i = 0; i < _vfire.size(); i++)
	{
		RECT NullRc;
		if (!IntersectRect(&NullRc, &_vfire[i].HitRc, &_player->getPlayerClass()->getPlayerRc()))
		{
			if (!_vfire[i].Hit)
			{
				_vfire[i].Count++;
				if (_vfire[i].Count % 1 == 0)
				{
					_vfire[i].Index++;
					if (_vfire[i].Index > fireboll->getMaxFrameX())
					{
						_vfire[i].Index = 0;
					}
					fireboll->setFrameX(_vfire[i].Index);
				}


				FrameRect(getMemDC(), _vfire[i].rc, RGB(255, 0, 0));
				FrameRect(getMemDC(), _vfire[i].HitRc, RGB(0, 255, 0));
				fireboll->frameRender(getMemDC(), _vfire[i].rc.left, _vfire[i].rc.top);
			}
		}
		else
		{
			_vfire[i].Hit = true;
			if (!_vfire[i].damageP)
			{
				_player->getPlayerClass()->setPlayerHp(_player->getPlayerClass()->getPlayerHp() - Attck);
				_vfire[i].damageP = true;
			}
		}
		
		if (_vfire[i].Hit)
		{
			_vfire[i].HitCount++;
			{
				if (_vfire[i].HitCount % 2 == 0)
				{
					_vfire[i].HitIndex++;
					{
						if (_vfire[i].HitIndex > fireHit->getMaxFrameX())
						{
							_vfire.erase(_vfire.begin() + i);
							break;
						}
					}
					fireHit->setFrameX(_vfire[i].HitIndex);
				}
			}
			fireHit->frameRender(getMemDC(), _vfire[i].rc.left, _vfire[i].rc.top-30);
		}	
	}
	if (!Live)
	{

		_vfire.clear();

	}
}

void Mage::Tel()
{
	if (Stat == 순간이동)
	{
		static int IIndex = 0;
		static int ICount = 0;
		coll = false;
		Acion = true;

		ICount++;
		if (!TelGo)
		{
			img = IMAGEMANAGER->findImage("TelIn");
			if (Direction == 오른쪽)
			{
				img->setFrameY(0);
			}
			else { img->setFrameY(1); }

			{
				if (ICount % 20 == 0)
				{
					IIndex++;
					if (IIndex > img->getMaxFrameX())
					{
						img = IMAGEMANAGER->findImage("TelInA");
						TelIn = true;
						TelGo = true;
					}
					img->setFrameX(IIndex);
				}
			}
			
		}

		if (TelIn)
		{
			static int Count = 0;
			static int Index = 0;

			Count++;
			if (Count % 7 == 0)
			{
				Index++;
				if (Index > TelEin->getMaxFrameX())
				{
					TelIn = false;
				}
				TelEin->setFrameX(Index);
			}
		}
		if (TelOut)
		{
			static int Count = 0;
			static int Index = 0;

			Count++;
			if (Count % 7 == 0)
			{
				Index++;
				if (Index > TelEOut->getMaxFrameX())
				{				
					
				}
				TelEOut->setFrameX(Index);
			}
		}

	}

}



