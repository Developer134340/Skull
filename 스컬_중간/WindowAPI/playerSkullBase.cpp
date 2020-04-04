#include "stdafx.h"
#include "playerSkullBase.h"

HRESULT playerSkullBase::init()
{
	head = true;
	weapon = true;

	JpDhS = false;
	EFS = 없음;
	//==================================
	//이것들은 따로 초기화 할 필요 없음 ↓
	Stat = 대기;
	direction = 오른쪽;
	
	What = 평타;
	x = 100;
	y = WINSIZEY / 2 + 110;
	Gravity = 0;
	dashSpeed = 12.f;
	Speed = 4.f;
	dash = true;
	AttackDel = 0;
	AttackCount = 0;
	JumpAttack = true;
	Jumping = false;
	JumpCountTrue = true;
	Jump = 12.f;
	Skill2Null = false;

	jumpCount = 0;
	ICount=0;
	IIndex=0;
	Attack = true;
	AttackColl = false;
	dashDistance = 20;
	Combo = false;

	JuDhDust = IMAGEMANAGER->findImage("JumpEffecf");

	//==================================
	
	//닌자만 3으로 다시 초기화 ↓
	dashCount = 2;
	//각 직업 최대 연속 공격횟수로 다시 초기화 ↓
	MaxAttackCount = 2;
	//직업마다 초기화↓==================================
	//Skill2Null 스킬 하나인애들만 트루로 다시 초기화
	NowHp;
	MaxHp;
	name;
	img;
	Arc;

	//===============================================

	_imagePosition.x = 0;
	_imagePosition.y = 0;

	return S_OK;
}

void playerSkullBase::release()
{
}

void playerSkullBase::update()
{
}

void playerSkullBase::render()
{
	FrameRender();
}

POINT playerSkullBase::getPlayerPosition()
{
	POINT pos;

	pos.x = x;
	pos.y = y;

	return pos;
}

void playerSkullBase::Move(int key)
{
	if (Stat != 공격 && Stat != 대시)
	{
		int color;
		
		int r;
		int g;
		int b;
		
		switch (key)
		{
		case VK_LEFT:
			direction = 왼쪽;
			x -= Speed;

			color = GetPixel(_PixelMap->getMemDC(), rc.left - _imagePosition.x, rc.bottom - _imagePosition.y + (_PixelMap->getHeight() - WINSIZEY));

			r = GetRValue(color);
			g = GetGValue(color);
			b = GetBValue(color);

			if (r == 0 && g == 0 && b == 255)		x += Speed;
			if (x < 10)		x = 10;

			rc = RectMakeCenter(x, y + 35, 50, 70);

			if (Stat == 이동)
			{
				color = GetPixel(_PixelMap->getMemDC(), rc.right - _imagePosition.x, rc.bottom - _imagePosition.y + (_PixelMap->getHeight() - WINSIZEY + 3));

				r = GetRValue(color);
				g = GetGValue(color);
				b = GetBValue(color);

				if (!(r == 0 && g == 0 && b == 255))
				{
					Gravity = Jump;
					JumpStat();
				}

				rc = RectMakeCenter(x, y + 35, 50, 70);
			}

			if (!Jumping) {Stat = 이동;}
			break;
		case VK_RIGHT:
			direction = 오른쪽;
			x += Speed;

			color = GetPixel(_PixelMap->getMemDC(), rc.right - _imagePosition.x, rc.bottom - _imagePosition.y + (_PixelMap->getHeight() - WINSIZEY));

			r = GetRValue(color);
			g = GetGValue(color);
			b = GetBValue(color);

			if (r == 0 && g == 0 && b == 255)		x -= Speed;
			if (x > WINSIZEX - 10)		x = WINSIZEX - 10;

			rc = RectMakeCenter(x, y + 35, 50, 70);

			if (Stat == 이동)
			{
				color = GetPixel(_PixelMap->getMemDC(), rc.left - _imagePosition.x, rc.bottom - _imagePosition.y + (_PixelMap->getHeight() - WINSIZEY + 3));

				r = GetRValue(color);
				g = GetGValue(color);
				b = GetBValue(color);

				if (!(r == 0 && g == 0 && b == 255))
				{
					Gravity = Jump;
					JumpStat();
				}

				rc = RectMakeCenter(x, y + 35, 50, 70);
			}

			if (!Jumping) { Stat = 이동; }
			break;
		}
	}
}

void playerSkullBase::JumpStat()
{	
	if (JumpCountTrue)
	{
		if (Stat != 점프공격 && Stat != 대시 && Stat != 공격 && Stat != 스킬1 && Stat != 스킬2)
		{
			jumpCount++;
			Jumping = true;
			Stat = 점프;
			ICount = 0;
			IIndex = 0;

			if (jumpCount >= 2)
			{
				jumpCount = 2;
			}
			
		}
	}
}

void playerSkullBase::AttackStat()
{
	if (weapon)
	{
		if (Attack && !Jumping && Stat != 대시 && Stat != 스킬1)
		{
			Stat = 공격;
			if (AttackCount < 2 || (AttackCount >= 2 && AttackCount < 4))
			{
				AttackCount++;
			}
			if (AttackCount == 2 || AttackCount == 4 || AttackCount == 6)
			{
				Combo = true;
			}

			if (AttackCount > MaxAttackCount + 2)
			{
				AttackCount = 0;
			}
		}


		if (Jumping)
		{
			if (Stat != 대시 && JumpAttack) { Stat = 점프공격; JumpAttack = false; }
		}
	}
	else {}
}


void playerSkullBase::FrameIRender(string name, string EffectName)
{
	if (Stat == 대기) { img = IMAGEMANAGER->findImage(name + "Idle"); }
	else if (Stat == 공격 && AttackCount == 1) { img = IMAGEMANAGER->findImage(name + "AttackA"); }
	else if (Stat == 공격 && AttackCount == 3) { img = IMAGEMANAGER->findImage(name + "AttackB"); }
	else if (Stat == 공격 && AttackCount == 5) { img = IMAGEMANAGER->findImage(name + "AttackC"); }
	else if (Stat == 공격 && AttackCount == 7) { img = IMAGEMANAGER->findImage(name + "AttackD"); }
	else if (Stat == 점프) { img = IMAGEMANAGER->findImage(name + "Jump"); }
	else if (Stat == 떨어짐) { img = IMAGEMANAGER->findImage(name + "Fall"); }
	else if (Stat == 점프공격) { img = IMAGEMANAGER->findImage(name + "JumpAttack"); }
	else if (Stat == 대시) { img = IMAGEMANAGER->findImage(name + "Dash"); }
	else if (Stat == 이동) { img = IMAGEMANAGER->findImage(name + "Walk"); }
	else if (Stat == 스킬1) { img = IMAGEMANAGER->findImage(name + "SkillA"); }
	else if (Stat == 스킬2) { img = IMAGEMANAGER->findImage(name + "SkillB"); }

	if (name == "Start" || name == "HNomal" || name == "NNomal")
	{
		if (Stat == 공격 || Stat == 대시) { img->frameRender(getMemDC(), x - img->getFrameWidth() / 2 + 2, y - img->getFrameHeight() / 2 + 30); }
		else if (Stat == 대시) { img->frameRender(getMemDC(), x - img->getFrameWidth() / 2 + 2, y - img->getFrameHeight() / 2 + 30); }
		else if (Stat == 스킬1) { img->frameRender(getMemDC(), x - img->getFrameWidth() / 2 + 2, y - img->getFrameHeight() / 2 + 10); }
		else if (Stat != 공격) { img->frameRender(getMemDC(), x - img->getFrameWidth() / 2, y - img->getFrameHeight() / 2 + 20); }
		else { img->frameRender(getMemDC(), x - img->getFrameWidth() / 2, y - img->getFrameHeight() / 2); }
	}
	else if (name == "ChiefGuard")
	{
		if (Stat == 공격 && AttackCount == 1) { img->frameRender(getMemDC(), x - img->getFrameWidth() / 2 + 2, y - img->getFrameHeight() / 2 + 32); }
		else if (Stat == 공격 && AttackCount == 2) { img->frameRender(getMemDC(), x - img->getFrameWidth() / 2 + 2, y - img->getFrameHeight() / 2 + 30); }
		else if (Stat == 공격 && AttackCount == 3) { img->frameRender(getMemDC(), x - img->getFrameWidth() / 2 + 2, y - img->getFrameHeight() / 2 + 10); }
		else if (Stat == 공격 && AttackCount == 4) { img->frameRender(getMemDC(), x - img->getFrameWidth() / 2 + 2, y - img->getFrameHeight() / 2 + 10); }
		else if (Stat == 공격 && AttackCount == 5 && direction == 오른쪽) { img->frameRender(getMemDC(), x + 15 - img->getFrameWidth() / 2 + 2, y - img->getFrameHeight() / 2 + 30); }
		else if (Stat == 공격 && AttackCount == 5 && direction == 왼쪽) { img->frameRender(getMemDC(), x - 15 - img->getFrameWidth() / 2 + 2, y - img->getFrameHeight() / 2 + 30); }
		else if (Stat == 공격 && AttackCount == 7) { img->frameRender(getMemDC(), x - img->getFrameWidth() / 2 + 2, y - 10 - img->getFrameHeight() / 2 - 50); }

		//-----------------------------------------------공 격 끝 ------------------------------------------------------------------

		else if (Stat == 대시) { img->frameRender(getMemDC(), x - img->getFrameWidth() / 2 + 2, y - img->getFrameHeight() / 2 + 30); }
		else if (Stat == 스킬1 && direction == 오른쪽) { img->frameRender(getMemDC(), x + 26 - img->getFrameWidth() / 2 + 2, y - img->getFrameHeight() / 2 + 29); }
		else if (Stat == 스킬1 && direction == 왼쪽) { img->frameRender(getMemDC(), x - 27 - img->getFrameWidth() / 2 + 2, y - img->getFrameHeight() / 2 + 29); }
		else if (Stat == 스킬2) { img->frameRender(getMemDC(), x - img->getFrameWidth() / 2, y - img->getFrameHeight() / 2 + 17); }
		else if (Stat == 대기) { img->frameRender(getMemDC(), x - img->getFrameWidth() / 2, y - img->getFrameHeight() / 2 + 20); }
		else { img->frameRender(getMemDC(), x - img->getFrameWidth() / 2, y - img->getFrameHeight() / 2 + 30); }
	}
	else if (name == "Hunter")
	{
		img->frameRender(getMemDC(), x - img->getFrameWidth() / 2 + 2, y - img->getFrameHeight() / 2 + 30);
		/*if (Stat == 공격 || Stat == 대기) { img->frameRender(getMemDC(), x - img->getFrameWidth() / 2 + 2, y - img->getFrameHeight() / 2 + 30); }
		else if (Stat == 대시) { img->frameRender(getMemDC(), x - img->getFrameWidth() / 2 + 2, y - img->getFrameHeight() / 2 + 30); }
		else if (Stat == 스킬1) { img->frameRender(getMemDC(), x - img->getFrameWidth() / 2 + 2, y - img->getFrameHeight() / 2 + 10); }
		else if (Stat != 공격) { img->frameRender(getMemDC(), x - img->getFrameWidth() / 2, y - img->getFrameHeight() / 2 + 20); }
		else { img->frameRender(getMemDC(), x - img->getFrameWidth() / 2, y - img->getFrameHeight() / 2); }*/
	}
	else
	{
		img->frameRender(getMemDC(), x - img->getFrameWidth() / 2 + 2, y - img->getFrameHeight() / 2);
	}

	if (EFS == 점프이펙) { JuDhDust = IMAGEMANAGER->findImage("JumpEffect"), JpDhR = RectMakeCenter(EX + _imagePosition.x + 5, EY + _imagePosition.y, 100, 30); }
	else if (EFS == 대시이펙) { JuDhDust = IMAGEMANAGER->findImage("DashEffect"), JpDhR = RectMakeCenter(EX + _imagePosition.x + 5, EY + _imagePosition.y, 64, 60); }
	if (JpDhS) { JuDhDust->frameRender(getMemDC(), JpDhR.left, JpDhR.top); }
}

void playerSkullBase::FrameIUpdate(int ImageSpeed,int capeSpeed) //이동이나 대기할때 사용
{
	if (Stat == 대기)
	{
		static int ICount = 0;
		static int IIndex = 0;
		ICount++;
		if (ICount % ImageSpeed == 0)
		{
			IIndex++;
			
			if (IIndex > img->getMaxFrameX())
			{
				IIndex = 0;
			}
			img->setFrameX(IIndex);
		}
	}
	if (Stat == 이동)
	{
		static int ICount = 0;
		static int IIndex = 0;
		ICount++;
		if (ICount % capeSpeed == 0)
		{
			IIndex++;

			if (IIndex > img->getMaxFrameX())
			{
				IIndex = 0;
			}
			img->setFrameX(IIndex);
		}
	}
	if (Stat == 점프 || Stat == 떨어짐)
	{
		ICount++;
		if (ICount % capeSpeed == 0)
		{
			IIndex++;	
			if (IIndex > img->getMaxFrameX())
			{
				if (Stat == 떨어짐)
				{
					IIndex = 2;
				}
				else if (Stat == 점프)
				{
					IIndex = 2;
				}
			}
			img->setFrameX(IIndex);
		}
	}


	if (EFS == 대시이펙 || EFS == 점프이펙)
	{
		static int count=0;
		static int index=0;

		count++;

		if (EFS == 대시이펙)
		{
			if (direction == 오른쪽) { JuDhDust->setFrameY(0); }
			else { JuDhDust->setFrameY(1); }
			if (count % 2 == 0)
			{
				index++;
			}
		}

		else if (EFS == 점프이펙)
		{
			
			if (count % 1 == 0)
			{
				index++;
			}
		}

		if (index > JuDhDust->getMaxFrameX())
		{
			JpDhS = false;
			index = 0;
			EFS = 없음;
		}
		JuDhDust->setFrameX(index);
		
	}
	
}

void playerSkullBase::DashAction(int ImageSpeed, int DashCount)
{
	if (Stat == 대시)
	{
		if (direction == 오른쪽) { x += dashSpeed; }
		else { x -= dashSpeed; }

		static int DashD = 0; 
		DashD++;
		if (DashD % dashDistance == 0)
		{
			IIndex = 0;
			ICount = 0;
			dash = true;
			JpDhS = false;
			DashD = 0;
			Stat = 대기;
		}

		static int ICount = 0;
		static int IIndex = 0;
		ICount++;
		if (ICount % ImageSpeed == 0)
		{
			IIndex++;
			if (IIndex > img->getMaxFrameX())
			{
				IIndex = 0;
				if (name == "Hunter")
				{
					IIndex = 0;
					ICount = 0;
					dash = true;
					JpDhS = false;
					DashD = 0;
					Stat = 대기;
				}
			}
			img->setFrameX(IIndex);
		}
	}

	if (dashCount < DashCount)
	{
		static int cool = 0;
		cool++;
		if (cool % 150 == 0)
		{
			dashCount = DashCount;
		}
	}
}

void playerSkullBase::JumpAction(int ImageSpeed)
{
	if (jumpCount == 2)
	{
		if (!JpDhS)
		{
			EX = x - _imagePosition.x;
			EY = y + 30 - _imagePosition.y;
			EFS = 점프이펙;
			JpDhS = true;
		}
	}

	if (Jumping)
	{
		if (Stat != 대시)
		{
			if (Gravity < Jump * 2)		Gravity += 0.5f;

			if (jumpCount == 1)
			{
				if (Jumping && Stat)
				{
					y -= Jump - Gravity;
				}
			}
			if (jumpCount == 2)
			{
				Gravity = 0;
				jumpCount++;
			}
			if (jumpCount == 3)
			{
				y -= Jump - Gravity;
				JumpCountTrue = false;
			}
			if (Gravity >= Jump && Stat != 점프공격) { Stat = 떨어짐; }
		}
		else { Gravity = Jump; }

	}

	if (Stat == 떨어짐 || Stat == 점프공격 )
	{

		int color = GetPixel(_PixelMap->getMemDC(), rc.left + ((rc.right - rc.left) / 2) - _imagePosition.x, rc.bottom - _imagePosition.y + (_PixelMap->getHeight() - WINSIZEY));

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (r == 0 && g == 0 && b == 255)
		{
			while (true)
			{
				y--;
				rc = RectMakeCenter(x, y + 35, 50, 70);

				color = GetPixel(_PixelMap->getMemDC(), rc.left + ((rc.right - rc.left) / 2) - _imagePosition.x, rc.bottom - _imagePosition.y + (_PixelMap->getHeight() - WINSIZEY));

				r = GetRValue(color);
				g = GetGValue(color);
				b = GetBValue(color);

				if (!(r == 0 && g == 0 && b == 255))		break;
			}

			if (Stat != 점프공격)
			{
				Stat = 대기;
			}

			if (!JpDhS)
			{
				EX = x - _imagePosition.x;
				EY = y + 60 - _imagePosition.y;
				EFS = 점프이펙;
				JpDhS = true;
			}

			Gravity = 0;
			jumpCount = 0;
			Jumping = false;
			JumpCountTrue = true;
			JumpAttack = true;
		}

	}
}

//플레이어 상태 및 렉트 그리기 함수
void playerSkullBase::FrameRender()
{
	if (KEYMANAGER->isToggleKey('Y'))
	{
		FrameRect(getMemDC(), rc, RGB(0, 255, 0));
		FrameRect(getMemDC(), Arc, RGB(255, 0, 0));
		if (JpDhS)
		{
			FrameRect(getMemDC(), JpDhR, RGB(0, 26, 201));
		}
	}
}