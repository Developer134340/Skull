#include "stdafx.h"
#include "playerSkullBase.h"

HRESULT playerSkullBase::init()
{
	head = true;
	weapon = true;

	JpDhS = false;
	EFS = ����;
	//==================================
	//�̰͵��� ���� �ʱ�ȭ �� �ʿ� ���� ��
	Stat = ���;
	direction = ������;
	
	What = ��Ÿ;
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
	
	//���ڸ� 3���� �ٽ� �ʱ�ȭ ��
	dashCount = 2;
	//�� ���� �ִ� ���� ����Ƚ���� �ٽ� �ʱ�ȭ ��
	MaxAttackCount = 2;
	//�������� �ʱ�ȭ��==================================
	//Skill2Null ��ų �ϳ��ξֵ鸸 Ʈ��� �ٽ� �ʱ�ȭ
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
	if (Stat != ���� && Stat != ���)
	{
		int color;
		
		int r;
		int g;
		int b;
		
		switch (key)
		{
		case VK_LEFT:
			direction = ����;
			x -= Speed;

			color = GetPixel(_PixelMap->getMemDC(), rc.left - _imagePosition.x, rc.bottom - _imagePosition.y + (_PixelMap->getHeight() - WINSIZEY));

			r = GetRValue(color);
			g = GetGValue(color);
			b = GetBValue(color);

			if (r == 0 && g == 0 && b == 255)		x += Speed;
			if (x < 10)		x = 10;

			rc = RectMakeCenter(x, y + 35, 50, 70);

			if (Stat == �̵�)
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

			if (!Jumping) {Stat = �̵�;}
			break;
		case VK_RIGHT:
			direction = ������;
			x += Speed;

			color = GetPixel(_PixelMap->getMemDC(), rc.right - _imagePosition.x, rc.bottom - _imagePosition.y + (_PixelMap->getHeight() - WINSIZEY));

			r = GetRValue(color);
			g = GetGValue(color);
			b = GetBValue(color);

			if (r == 0 && g == 0 && b == 255)		x -= Speed;
			if (x > WINSIZEX - 10)		x = WINSIZEX - 10;

			rc = RectMakeCenter(x, y + 35, 50, 70);

			if (Stat == �̵�)
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

			if (!Jumping) { Stat = �̵�; }
			break;
		}
	}
}

void playerSkullBase::JumpStat()
{	
	if (JumpCountTrue)
	{
		if (Stat != �������� && Stat != ��� && Stat != ���� && Stat != ��ų1 && Stat != ��ų2)
		{
			jumpCount++;
			Jumping = true;
			Stat = ����;
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
		if (Attack && !Jumping && Stat != ��� && Stat != ��ų1)
		{
			Stat = ����;
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
			if (Stat != ��� && JumpAttack) { Stat = ��������; JumpAttack = false; }
		}
	}
	else {}
}


void playerSkullBase::FrameIRender(string name, string EffectName)
{
	if (Stat == ���) { img = IMAGEMANAGER->findImage(name + "Idle"); }
	else if (Stat == ���� && AttackCount == 1) { img = IMAGEMANAGER->findImage(name + "AttackA"); }
	else if (Stat == ���� && AttackCount == 3) { img = IMAGEMANAGER->findImage(name + "AttackB"); }
	else if (Stat == ���� && AttackCount == 5) { img = IMAGEMANAGER->findImage(name + "AttackC"); }
	else if (Stat == ���� && AttackCount == 7) { img = IMAGEMANAGER->findImage(name + "AttackD"); }
	else if (Stat == ����) { img = IMAGEMANAGER->findImage(name + "Jump"); }
	else if (Stat == ������) { img = IMAGEMANAGER->findImage(name + "Fall"); }
	else if (Stat == ��������) { img = IMAGEMANAGER->findImage(name + "JumpAttack"); }
	else if (Stat == ���) { img = IMAGEMANAGER->findImage(name + "Dash"); }
	else if (Stat == �̵�) { img = IMAGEMANAGER->findImage(name + "Walk"); }
	else if (Stat == ��ų1) { img = IMAGEMANAGER->findImage(name + "SkillA"); }
	else if (Stat == ��ų2) { img = IMAGEMANAGER->findImage(name + "SkillB"); }

	if (name == "Start" || name == "HNomal" || name == "NNomal")
	{
		if (Stat == ���� || Stat == ���) { img->frameRender(getMemDC(), x - img->getFrameWidth() / 2 + 2, y - img->getFrameHeight() / 2 + 30); }
		else if (Stat == ���) { img->frameRender(getMemDC(), x - img->getFrameWidth() / 2 + 2, y - img->getFrameHeight() / 2 + 30); }
		else if (Stat == ��ų1) { img->frameRender(getMemDC(), x - img->getFrameWidth() / 2 + 2, y - img->getFrameHeight() / 2 + 10); }
		else if (Stat != ����) { img->frameRender(getMemDC(), x - img->getFrameWidth() / 2, y - img->getFrameHeight() / 2 + 20); }
		else { img->frameRender(getMemDC(), x - img->getFrameWidth() / 2, y - img->getFrameHeight() / 2); }
	}
	else if (name == "ChiefGuard")
	{
		if (Stat == ���� && AttackCount == 1) { img->frameRender(getMemDC(), x - img->getFrameWidth() / 2 + 2, y - img->getFrameHeight() / 2 + 32); }
		else if (Stat == ���� && AttackCount == 2) { img->frameRender(getMemDC(), x - img->getFrameWidth() / 2 + 2, y - img->getFrameHeight() / 2 + 30); }
		else if (Stat == ���� && AttackCount == 3) { img->frameRender(getMemDC(), x - img->getFrameWidth() / 2 + 2, y - img->getFrameHeight() / 2 + 10); }
		else if (Stat == ���� && AttackCount == 4) { img->frameRender(getMemDC(), x - img->getFrameWidth() / 2 + 2, y - img->getFrameHeight() / 2 + 10); }
		else if (Stat == ���� && AttackCount == 5 && direction == ������) { img->frameRender(getMemDC(), x + 15 - img->getFrameWidth() / 2 + 2, y - img->getFrameHeight() / 2 + 30); }
		else if (Stat == ���� && AttackCount == 5 && direction == ����) { img->frameRender(getMemDC(), x - 15 - img->getFrameWidth() / 2 + 2, y - img->getFrameHeight() / 2 + 30); }
		else if (Stat == ���� && AttackCount == 7) { img->frameRender(getMemDC(), x - img->getFrameWidth() / 2 + 2, y - 10 - img->getFrameHeight() / 2 - 50); }

		//-----------------------------------------------�� �� �� ------------------------------------------------------------------

		else if (Stat == ���) { img->frameRender(getMemDC(), x - img->getFrameWidth() / 2 + 2, y - img->getFrameHeight() / 2 + 30); }
		else if (Stat == ��ų1 && direction == ������) { img->frameRender(getMemDC(), x + 26 - img->getFrameWidth() / 2 + 2, y - img->getFrameHeight() / 2 + 29); }
		else if (Stat == ��ų1 && direction == ����) { img->frameRender(getMemDC(), x - 27 - img->getFrameWidth() / 2 + 2, y - img->getFrameHeight() / 2 + 29); }
		else if (Stat == ��ų2) { img->frameRender(getMemDC(), x - img->getFrameWidth() / 2, y - img->getFrameHeight() / 2 + 17); }
		else if (Stat == ���) { img->frameRender(getMemDC(), x - img->getFrameWidth() / 2, y - img->getFrameHeight() / 2 + 20); }
		else { img->frameRender(getMemDC(), x - img->getFrameWidth() / 2, y - img->getFrameHeight() / 2 + 30); }
	}
	else if (name == "Hunter")
	{
		img->frameRender(getMemDC(), x - img->getFrameWidth() / 2 + 2, y - img->getFrameHeight() / 2 + 30);
		/*if (Stat == ���� || Stat == ���) { img->frameRender(getMemDC(), x - img->getFrameWidth() / 2 + 2, y - img->getFrameHeight() / 2 + 30); }
		else if (Stat == ���) { img->frameRender(getMemDC(), x - img->getFrameWidth() / 2 + 2, y - img->getFrameHeight() / 2 + 30); }
		else if (Stat == ��ų1) { img->frameRender(getMemDC(), x - img->getFrameWidth() / 2 + 2, y - img->getFrameHeight() / 2 + 10); }
		else if (Stat != ����) { img->frameRender(getMemDC(), x - img->getFrameWidth() / 2, y - img->getFrameHeight() / 2 + 20); }
		else { img->frameRender(getMemDC(), x - img->getFrameWidth() / 2, y - img->getFrameHeight() / 2); }*/
	}
	else
	{
		img->frameRender(getMemDC(), x - img->getFrameWidth() / 2 + 2, y - img->getFrameHeight() / 2);
	}

	if (EFS == ��������) { JuDhDust = IMAGEMANAGER->findImage("JumpEffect"), JpDhR = RectMakeCenter(EX + _imagePosition.x + 5, EY + _imagePosition.y, 100, 30); }
	else if (EFS == �������) { JuDhDust = IMAGEMANAGER->findImage("DashEffect"), JpDhR = RectMakeCenter(EX + _imagePosition.x + 5, EY + _imagePosition.y, 64, 60); }
	if (JpDhS) { JuDhDust->frameRender(getMemDC(), JpDhR.left, JpDhR.top); }
}

void playerSkullBase::FrameIUpdate(int ImageSpeed,int capeSpeed) //�̵��̳� ����Ҷ� ���
{
	if (Stat == ���)
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
	if (Stat == �̵�)
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
	if (Stat == ���� || Stat == ������)
	{
		ICount++;
		if (ICount % capeSpeed == 0)
		{
			IIndex++;	
			if (IIndex > img->getMaxFrameX())
			{
				if (Stat == ������)
				{
					IIndex = 2;
				}
				else if (Stat == ����)
				{
					IIndex = 2;
				}
			}
			img->setFrameX(IIndex);
		}
	}


	if (EFS == ������� || EFS == ��������)
	{
		static int count=0;
		static int index=0;

		count++;

		if (EFS == �������)
		{
			if (direction == ������) { JuDhDust->setFrameY(0); }
			else { JuDhDust->setFrameY(1); }
			if (count % 2 == 0)
			{
				index++;
			}
		}

		else if (EFS == ��������)
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
			EFS = ����;
		}
		JuDhDust->setFrameX(index);
		
	}
	
}

void playerSkullBase::DashAction(int ImageSpeed, int DashCount)
{
	if (Stat == ���)
	{
		if (direction == ������) { x += dashSpeed; }
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
			Stat = ���;
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
					Stat = ���;
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
			EFS = ��������;
			JpDhS = true;
		}
	}

	if (Jumping)
	{
		if (Stat != ���)
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
			if (Gravity >= Jump && Stat != ��������) { Stat = ������; }
		}
		else { Gravity = Jump; }

	}

	if (Stat == ������ || Stat == �������� )
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

			if (Stat != ��������)
			{
				Stat = ���;
			}

			if (!JpDhS)
			{
				EX = x - _imagePosition.x;
				EY = y + 60 - _imagePosition.y;
				EFS = ��������;
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

//�÷��̾� ���� �� ��Ʈ �׸��� �Լ�
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