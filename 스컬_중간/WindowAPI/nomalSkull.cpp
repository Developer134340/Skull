#include "stdafx.h"
#include "nomalSkull.h"

HRESULT nomalSkull::init()
{
	playerSkullBase::init();

	MaxHp = 100;
	NowHp = MaxHp;///////////////////////////////
	dmg = 0;

	Stat = 대기;
	
	head = true;
	name = "Start";
	EfName = "";
	MaxAttackCount = 2;
	Skill2Null = true;
	weapon = false;

	{
		_Head.loop = false;
		_Head.speed = 7.f;
		_Head.I = IMAGEMANAGER->findImage("Head");
		_Head.fire = false;
		_Head.Irender = false;
		_Head.Drop = false;
		_Head.Gravity = 0.0f;
		_Head.count,_Head.index = 0;
	}


	return S_OK;
}

void nomalSkull::release()
{
	playerSkullBase::release();

}

void nomalSkull::update()
{
	playerSkullBase::update();

	if (head && weapon) { name = "HNomal"; }
	else if(!head && weapon){ name = "NNomal"; }
	else if (!weapon) { name = "Start"; }

	YImageCheck();
	FrameIUpdate(10, 6);
	DashAction(10,2);
	JumpAction(7);
	Skill1(10);
	AttackAction(7,8);

	rc = RectMakeCenter(x, y + 35, 50, 70); 
	if (direction == 오른쪽)			Arc = RectMakeCenter(x + 15, y + 35, 110, 70);
	else							Arc = RectMakeCenter(x - 15, y + 35, 110, 70);
	_Head.rc = RectMakeCenter(_Head.x, _Head.y, 19, 17);
}

void nomalSkull::render()
{
	playerSkullBase::render();
	FrameIRender(name,EfName);

	if (_Head.Irender)
	{
		if (_Head.Direction == 오른쪽) { _Head.I->setFrameY(1); }	else { _Head.I->setFrameY(0);}
		_Head.I->frameRender(getMemDC(), _Head.rc.left, _Head.rc.top);
	}

}

void nomalSkull::AttackAction(int ImageSpeed, int JumpAttackSpeed)
{
	if (Stat == 공격)
	{
		What = 평타;
		if (img == IMAGEMANAGER->findImage(name + "AttackA"))
		{
			static int ICount = 0;
			static int IIndex = 0;
			ICount++;
			if (ICount % ImageSpeed == 0)
			{
				IIndex++;
				if (IIndex == 3)
				{
					AttackColl = true;
					/////////////////////////
					//  에너미와 충돌 처리  //
					/////////////////////////
				}
				if (IIndex > img->getMaxFrameX())
				{
					if (AttackCount < 2)
					{
						AttackCount = 0;
						Stat = 대기;
						AttackColl = false;
					}
					if (Combo)
					{
						AttackCount++;
						Combo = false;
					}
					IIndex = 0;
					AttackDel++;
				}
				img->setFrameX(IIndex);
			}
		}
		else if (img == IMAGEMANAGER->findImage(name + "AttackB"))
		{
			static int ICount = 0;
			static int IIndex = 0;
			ICount++;
			if (ICount % ImageSpeed == 0)
			{
				IIndex++;
				if (IIndex == 2)
				{
					RECT Temp;

					AttackColl = true;
					/////////////////////////
					//  에너미와 충돌 처리  //
					/////////////////////////
				}
				if (IIndex > img->getMaxFrameX())
				{
					Combo = false;
					AttackColl = false;
					AttackCount = 0;
					IIndex = 0;
					AttackDel++;
					Stat = 대기;
				}
				img->setFrameX(IIndex);
			}
		}
	}

	if (Stat == 점프공격)
	{
		What = 평타;
		static int Count = 0;
		static int Index = 0;
		Count++;
		if (Count % JumpAttackSpeed == 0)
		{
			Index++;
			if (Index == 2)
			{
				AttackColl = true;
				/////////////////////////
				//  에너미와 충돌 처리  //
				/////////////////////////
			}
			if (Index > img->getMaxFrameX())
			{
				Count = 0;
				Index = 0;
				AttackColl = false;
				Stat = 대기;
			}
			img->setFrameX(Index);
		}
	}

	if (AttackDel >= 15)
	{
		static int Cool = 0;
		Cool++;
		Attack = false;
		if (Cool % 60 == 0)
		{
			AttackDel = 0;
			Attack = true;
		}
	}
}

void nomalSkull::Skill1(int ImageSpeed)
{
	if (weapon)
	{
		static int Icount = 0;
		static int Iindex = 0;

		if (!head)
		{
			float distance = getDistance(_Head.Sx, _Head.Sy, _Head.x, _Head.y);
			int Range = 450;


			static int Colldow = 0;
			Colldow++;
			if (Colldow % 300 == 0)
			{
				Iindex = 0;
				Icount = 0;
				_Head.Irender = false;
				head = true;
			}

			if (_Head.fire)
			{
				AttackColl = true;
				if (_Head.Direction == 오른쪽) (_Head.x += _Head.speed); else { _Head.x -= _Head.speed; }
			}

			if (distance > Range) { _Head.fire = false; _Head.Irender = false; }
			else
			{
				if (_Head.fire)
				{
					/////////////////////////
					//  에너미와 충돌 처리  //
					/////////////////////////
				}
			}

			if (_Head.Drop)
			{

				_Head.Gravity += 0.2f;

				if (_Head.y + 9 < WINSIZEY / 2 + 25)
				{
					_Head.x += -cosf(_Head.angle) * 2;
					_Head.y -= sinf(_Head.angle) * 5;
					_Head.y += _Head.Gravity;
				}
				else
				{
					static int loopCount = 0;
					loopCount++;
					_Head.Gravity = 0.0f;
					if (loopCount % 20 == 0)
					{
						_Head.loop = true;
						_Head.Drop = false;
					}
				}
			}
			if (_Head.loop)
			{
				RECT TempRC;
				if (IntersectRect(&TempRC, &_Head.rc, &rc))
				{
					_Head.Irender = false;
					head = true;
					_Head.loop = false;
				}
			}

		}
		else
		{
			_Head.x = x;
			_Head.y = y;
			_Head.Direction = direction;
			_Head.rc = RectMakeCenter(_Head.x, _Head.y, 19, 17);
		}


		if (Stat == 스킬1)
		{
			static int count = 0;
			static int index = 0;

			if (index < img->getMaxFrameX())
			{
				count++;
			}
			if (count % ImageSpeed == 0)
			{
				index++;
				if (index == 2)
				{
					head = false;
					_Head.fire = true;
					_Head.Irender = true;
					_Head.Sx = x;
					_Head.Sy = y;
					_Head.x = x;
					_Head.y = y;
				}
				if (index > img->getMaxFrameX())
				{
					index = 0;
					count = 0;
					Stat = 대기;
				}
			}
			img->setFrameX(index);
		}
	}
}