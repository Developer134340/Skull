#include "stdafx.h"
#include "hunter.h"


HRESULT hunter::init()
{

	playerSkullBase::init();

	name = "Hunter"; 
	EfName = "";

	MaxHp = 100;
	NowHp = MaxHp;
	dmg = 0;
	Stat = 대기;
	MaxAttackCount = 3;
	Skill2Null = true;
	rc = RectMakeCenter(x, y, 44, 37);

	dashSpeed = 10.f;
	dashDistance = 30;

	img = IMAGEMANAGER->findImage("HunterIdle");

	{
		sk.rc;
		sk.index= sk.count = 0;
		sk.I = IMAGEMANAGER->findImage("HunterSkillBEffect");
		sk.EF = false;
		sk.ii= sk.ic = 0;
	}

	ZeroMemory(&bu, sizeof(bu));

	bu.speed = 10.0f;
	bu.I = IMAGEMANAGER->findImage("HunterArrowA");
	bu.fire = false;

	IMAGEMANAGER->findImage("HunterArrowB");

	return S_OK;
}

void hunter::release()
{
}

void hunter::update()
{
	if (head) { name = "Hunter"; }

	YImageCheck();
	FrameIUpdate(13, 4);
	DashAction(4, 1);
	JumpAction(7);
	Skill1(6);
	AttackAction(7, 8);

	rc = RectMakeCenter(x, y + 35, 50, 70);

	for (int i = 0; i < _vBullet.size(); i++)
	{
		if (_vBullet[i].fire)
		{
			_vBullet[i].rc = RectMakeCenter(_vBullet[i].x, _vBullet[i].y, _vBullet[i].I->getFrameWidth(), _vBullet[i].I->getFrameHeight());
			_vBullet[i].I->frameRender(getMemDC(), _vBullet[i].rc.left, _vBullet[i].rc.top);
			
			if (_vBullet[i].Direction == 오른쪽) { _vBullet[i].x += _vBullet[i].speed; }
			else { _vBullet[i].x -= _vBullet[i].speed; }
			
			RECT Mop;
			RECT Null;
			if (IntersectRect(&Null, &_vBullet[i].rc, &Mop))
			{
				//hp -= dmg
				_vBullet.erase(_vBullet.begin() + i);
			}
		}
	}
}

void hunter::render()
{
	FrameIRender("Hunter", "");
	FrameRender();
	for (int i = 0; i < _vBullet.size(); i++)
	{
		if (_vBullet[i].Direction == 오른쪽)
		{
			_vBullet[i].I->setFrameY(0);
		}
		else { _vBullet[i].I->setFrameY(1); }

		if (_vBullet[i].fire)
		{
			_vBullet[i].I->frameRender(getMemDC(), _vBullet[i].rc.left, _vBullet[i].rc.top);
			FrameRect(getMemDC(), _vBullet[i].rc, RGB(255, 0, 0));
		}
	}

	if (sk.EF)
	{
		if (sk.direction == 오른쪽)
		{
			sk.I->setFrameX(0);
		}
		else
		{
			sk.I->setFrameX(1);
		}
		sk.I->frameRender(getMemDC(), sk.rc.left, sk.rc.top);
		sk.rc = RectMake(sk.x, sk.y + 20, sk.I->getFrameWidth(), sk.I->getFrameHeight());

		sk.ic++;
		if (sk.ic % 1 == 0)
		{
			AttackColl = true;
			sk.ii++;
		}
		sk.I->setFrameY(sk.ii);
	}


	if (sk.ii > sk.I->getMaxFrameY())
	{
		sk.count = sk.index = 0;
		sk.ii = sk.ic = 0;
		AttackColl = false;
		sk.EF = false;
		Stat = 대기;
	}
	
}



void hunter::AttackAction(int ImageSpeed, int JumpAttackSpeed)
{
	if (Stat == 공격)//공격상태일때
	{
		What = 평타;//평타상태일떄

		if (img == IMAGEMANAGER->findImage(name + "AttackA"))//첫번째공격일때?
		{
			static int Q = 0;
			static int W = 0;
			Q++;
			if (Q % ImageSpeed == 0)
			{
				W++;
				if (W > img->getMaxFrameX())//프레임이 끝나면? 
				{
					if (direction == 오른쪽) { bu.Direction = 오른쪽; }
					else { bu.Direction = 왼쪽; }

					bu.x = x;
					bu.y = y;
					bu.rc = RectMakeCenter(bu.x, bu.y, bu.I->getFrameWidth(), bu.I->getFrameWidth());
					bu.I = IMAGEMANAGER->findImage("HunterArrowA");
					bu.fire = true;
					_vBullet.push_back(bu);

					if (AttackCount < 2)//1
					{
						AttackCount = 0;
						W = 0;
						Stat = 대기;
						AttackColl = false;
					}
					if (Combo)
					{
						AttackCount++;
						Combo = false;
					}
					W = 0;
					AttackDel++;
				}
				img->setFrameX(W);
			}	
		}
		else if (img == IMAGEMANAGER->findImage(name + "AttackB"))//2번쨰 공격일때? 
		{
			static int ICount = 0;
			static int IIndex = 0;
			ICount++;
			if (ICount % ImageSpeed == 0)
			{
				IIndex++;
				if (IIndex > img->getMaxFrameX())
				{
					if (direction == 오른쪽) { bu.Direction = 오른쪽; }
					else { bu.Direction = 왼쪽; }
					bu.x = x;
					bu.y = y;
					bu.rc = RectMakeCenter(bu.x, bu.y, bu.I->getFrameWidth(), bu.I->getFrameWidth());
					bu.fire = true;
					_vBullet.push_back(bu);

					if (AttackCount < 4)//1
					{
						AttackCount = 0;
						IIndex = 0;
						Stat = 대기;
						AttackColl = false;
					}
					if (Combo)
					{
						AttackCount++;
						Combo = false;
					}
					AttackColl = false;
					IIndex = 0;
					AttackDel++;
				}
				img->setFrameX(IIndex);
			}
		}
		else if (img == IMAGEMANAGER->findImage(name + "AttackC"))//3번째 공격일때? 
		{
			static int C = 0;
			static int I = 0;
			C++;
			if (C % ImageSpeed == 0)
			{
				I++;
				if (I > img->getMaxFrameX())
				{
					if (direction == 오른쪽) { bu.Direction = 오른쪽; }
					else { bu.Direction = 왼쪽; }
					bu.x = x;
					bu.y = y;
					bu.rc = RectMakeCenter(bu.x, bu.y, bu.I->getFrameWidth(), bu.I->getFrameWidth());
					bu.fire = true;
					bu.I = IMAGEMANAGER->findImage("HunterArrowB");
					_vBullet.push_back(bu);

					Combo = false;
					AttackColl = false;
					AttackDel++;
					I = 0;
					C = 0;
					AttackCount = 0;
					Stat = 대기;
				}
				img->setFrameX(I);
			}
		}
	}


	if (Stat == 점프공격)
	{
		static int Count = 0;
		static int Index = 0;
		Count++;
		if (Count % 5 == 0)
		{
			Index++;
			if (Index > img->getMaxFrameX())
			{
				if (direction == 오른쪽) { bu.Direction = 오른쪽; }
				else { bu.Direction = 왼쪽; }
				Index = 0;
				bu.x = x;
				bu.y = y;
				bu.rc = RectMakeCenter(bu.x, bu.y, bu.I->getFrameWidth(), bu.I->getFrameWidth());
				bu.I = IMAGEMANAGER->findImage("HunterArrowA");
				bu.fire = true;
				_vBullet.push_back(bu);

				Stat = 대기;
			}
			img->setFrameX(Index);
		}
	}

}

void hunter::Skill1(int ImageSpeed)
{
	if (Stat == 스킬1)
	{
		sk.direction = direction;
		sk.count++;
		if (sk.count % ImageSpeed == 0)
		{
			sk.index++;
			if (sk.index > img->getMaxFrameX())
			{
				if (sk.direction == 오른쪽)
				{
					sk.x = x+10;
				}
				else
				{
					sk.x = x - sk.I->getFrameWidth()-10;
				}
				sk.y = y-10;
				sk.EF = true;
			}
		}
		img->setFrameX(sk.index);
	}
}
