#include "stdafx.h"
#include "chiefGuard.h"

HRESULT chiefGuard::init()
{
	playerSkullBase::init();

	countslash = 0;
	MaxHp = 100;
	NowHp = MaxHp;
	dmg = 0;
	Stat = 대기;
	_firecount = 0;

	name = "ChiefGuard";
	EfName = "";
	MaxAttackCount = 3;
	Skill2Null = false;
	_Fireballskillon = true;
	_slashskillon = false;
	_slash._slashon = false;
	_slash.I = IMAGEMANAGER->findImage("ChiefGuardSkillB");

	{
		_fireball.speed = 7.f;
		_fireball.index = _fireball.count = 0;
		_fireball.I = IMAGEMANAGER->findImage("ChiefGuardFire");
		_fireball.IEF = IMAGEMANAGER->findImage("ChiefGuardSlash");
		_fireball.fire = false;
		_fireball.Irender = false;
	}

	weapon = true;

	return S_OK;

}

void chiefGuard::release()
{
	playerSkullBase::release();
}

void chiefGuard::update()
{
	YImageCheck();
	FrameIUpdate(13, 4);//이미지임 이미지를 빠르게 돌릴꺼면 숫자를 낮게 늦게돌릴꺼면 숫자를 빠르게할것
	DashAction(10, 2);//마찬가지
	JumpAction(7);
	Skill1(4);
	Skill2(3);
	AttackAction(7, 8);

	rc = RectMakeCenter(x, y, 44, 37);
	Arc = RectMakeCenter(x, y, 93, 57);
}

void chiefGuard::render()
{
	playerSkullBase::render();
	FrameIRender(name, EfName);//필수 


	if (_fireball.fire)
	{
		_fireball.I->frameRender(getMemDC(), _fireball.rc.left + _imagePosition.x, _fireball.rc.top + _imagePosition.y);
	}
	if (_fireball.Irender)
	{
		_fireball.IEF->frameRender(getMemDC(), x + _imagePosition.x - 150, y + _imagePosition.y - 40);
	}
	_slash.I->frameRender(getMemDC(), _slash._rc.left + _imagePosition.x, _slash._rc.top + _imagePosition.y);
}

void chiefGuard::AttackAction(int ImageSpeed, int JumpAttackSpeed)
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
				if (IIndex == 3)
				{
					RECT Temp;

					AttackColl = true;
					/////////////////////////
					//  에너미와 충돌 처리  //
					/////////////////////////
				}
				if (IIndex > img->getMaxFrameX())
				{
					if (AttackCount < 4)
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
		else if (img == IMAGEMANAGER->findImage(name + "AttackC"))
		{
			static int ICount = 0;
			static int IIndex = 0;
			ICount++;
			if (ICount % ImageSpeed == 0)
			{
				IIndex++;
				if (IIndex == 4)
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
		static int Count = 0;
		static int Index = 0;
		Count++;
		if (Count % JumpAttackSpeed == 0)
		{
			Index++;
			if (Index > img->getMaxFrameX())
			{
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


void chiefGuard::Skill1(int ImageSpeed)
{
	if (Stat == 스킬1)
	{
		static int count = 0;

		_fireball.Irender = true;

		count++;

		if (count == 3 * ImageSpeed)
		{
			_fireball.fire = true;
			_fireball.Direction = direction;
			_fireball.I->setFrameY(_fireball.Direction);
			_fireball.IEF->setFrameY(_fireball.Direction);
			_fireball.Sx = x + _imagePosition.x;
			_fireball.Sy = y + _imagePosition.y;
			_fireball.x = x + _imagePosition.x;
			_fireball.y = y + _imagePosition.y;
			_fireball.speed = 10.f;
			_fireball.count = 0;
		}
		else if (count == img->getMaxFrameX() * ImageSpeed)
		{
			Stat = 대기;
			count = 0;
		}
		img->setFrameX(count / ImageSpeed);
	}

	if (_fireball.Irender)
	{
		static int Ecount = 0;
		Ecount++;
		if (Ecount == _fireball.IEF->getMaxFrameX() * ImageSpeed)
		{
			_fireball.Irender = false;
			Ecount = 0;
		}
		_fireball.IEF->setFrameX(Ecount / ImageSpeed);
	}

	if (_fireball.fire)
	{
		int distance = getDistance(_fireball.Sx, _fireball.Sy, _fireball.x, _fireball.y);

		if (distance > 1500)
		{
			_fireball.fire = false;
		}

		if (_fireball.Direction == 오른쪽)
		{
			_fireball.x += _fireball.speed;
		}
		else
		{
			_fireball.x -= _fireball.speed;
		}
		_fireball.rc = RectMakeCenter(_fireball.x, _fireball.y + 30, _fireball.I->getFrameWidth(), _fireball.I->getFrameHeight());

		_fireball.count++;
		if (_fireball.count == _fireball.I->getMaxFrameX() * ImageSpeed)		_fireball.count = 0;
		_fireball.I->setFrameX(_fireball.count / ImageSpeed);
	}
}

void chiefGuard::Skill2(int ImageSpeed)
{
	if (Stat == 스킬2)
	{
		static int IINNN = 0;
		static int Icc = 0;
		Icc++;


		if (Icc % ImageSpeed == 0)
		{
			IINNN++;
			if (IINNN == 2)
			{
				_slash._slashon = true;
				_slash.x = x;
				_slash.y = y;
				_slash.Direction = direction;
				_slash._rc = RectMakeCenter(_slash.x, _slash.y, _slash.I->getFrameWidth(), _slash.I->getFrameHeight());
			}
			if (IINNN > img->getMaxFrameX())
			{
				IINNN = 0;
				Icc = 0;
				Stat = 대기;
			}
			img->setFrameX(IINNN);

		}

	}
	//
	if (_slash._slashon)
	{
		countslash++;
		RECT Temp;

		if(countslash % 5 == 0)
		{ 
			AttackColl = true;
		}

		static int cool = 0;
		cool++;

		if (_slash.Direction == 오른쪽) { _slash.I->setFrameY(0); }
		else _slash.I->setFrameY(1);

		static int count = 0;
		static int index = 0;

		count++;

		if (count % 5 == 0)
		{
			index++;
			if (index > _slash.I->getMaxFrameX())
			{
				index = 0;
			}
		}

		_slash.I->setFrameX(index);
		_slash._rc = RectMakeCenter(_slash.x, _slash.y, _slash.I->getFrameWidth(), _slash.I->getFrameHeight());
	}
}