#include "stdafx.h"
#include "EnemyBase.h"
#include "player.h"


HRESULT EnemyBase::init()
{ 
	ICount = 0;			//이미지 카운트
	IIndex = 0;			//이미지 인덱스
	HitCount = 0;		//경직 시간
	Stat = 대기;		//상태
	Agro = false;		// 몬스터 어그로
	Acion = true;		//프레임 끝난후 동작가능
	alpha = 0;
	delayCount = 0;
	
	{
		_BHP.Dmgbar = IMAGEMANAGER->findImage("dmgbar");
		_BHP.Frame = IMAGEMANAGER->findImage("Frame");
		_BHP.HPbar = IMAGEMANAGER->findImage("HPbar");
		_BHP.HPbarBg = IMAGEMANAGER->findImage("HPbarBg");
		_BHP.nameBg = IMAGEMANAGER->findImage("nameBg");
		_BHP.x = WINSIZEX / 2;
		_BHP.y = 100;
		_BHP.rc = RectMakeCenter(_BHP.x, _BHP.y, 542, 46);
		_BHP.namerc = RectMakeCenter(WINSIZEX / 2, 50, _BHP.nameBg->getWidth(), _BHP.nameBg->getHeight());
	}

	enemyAttackColl = false;
	enemyCantAttack = false;

	Hpframe = IMAGEMANAGER->findImage("hpfr");
	Hpbg = IMAGEMANAGER->findImage("hpbg");
	hpbar = IMAGEMANAGER->findImage("hpbar");
	hpframe = (int)(Hp * 51 / maxhp);

	return S_OK;
}

void EnemyBase::release()
{
}

void EnemyBase::update()
{
}

void EnemyBase::render()
{

}

void EnemyBase::renderMonster(RECT rc,RECT Arc,RECT ATrc)
{
	if (Live)
	{
		if (KEYMANAGER->isToggleKey('Y'))
		{
			FrameRect(getMemDC(), rc, RGB(153, 0, 204));
			FrameRect(getMemDC(), Arc, RGB(255, 102, 0));
			FrameRect(getMemDC(), ATrc, RGB(255, 0, 0));
		}
	}
}


void EnemyBase::FrameMonsterI(int ImageSpeed)
{

	if (Live && (Stat == 대기 || Stat == 이동))
	{
		if (Stat == 대기)
		{
			img = IMAGEMANAGER->findImage(name + "Idle");
			ICount++;
		}
		if (Stat == 이동)
		{
			img = IMAGEMANAGER->findImage(name + "move");
			ICount++;
		}

		if (Direction == 오른쪽)
		{
			img->setFrameY(0);
		}
		else if (Direction == 왼쪽)
		{
			img->setFrameY(1);
		}

		if (Stat == 이동)
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

		if (Stat == 대기)
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
	else
	{
		if (Stat == 피격)
		{
			img = IMAGEMANAGER->findImage(name + "Hit");
			if (_player->getPlayerClass()->getDirection() == 오른쪽)
			{
				img->setFrameY(1);
			}
			else
			{
				img->setFrameY(0);
			}
			img->setFrameX(0);
		}	
		if (!Live)img = IMAGEMANAGER->findImage(name + "Dead");
	}
}

void EnemyBase::ImageRender()
{
	if (Live)
	{
		if (name == "Knight")
		{
			if (Stat == 피격)
			{
				img->frameRender(getMemDC(), x - img->getFrameWidth() / 2 + _player->getPlayerClass()->getImagePosition().x, y - img->getFrameHeight() / 2 + _player->getPlayerClass()->getImagePosition().y + 20);
			}
			else
			{
				img->frameRender(getMemDC(), x - img->getFrameWidth() / 2 + _player->getPlayerClass()->getImagePosition().x, y - img->getFrameHeight() / 2 + _player->getPlayerClass()->getImagePosition().y - 6);
			}
		}
		else if (name == "Archar")
		{
			if (Stat == 피격)
			{
				img->frameRender(getMemDC(), x - img->getFrameWidth() / 2 + _player->getPlayerClass()->getImagePosition().x, y - img->getFrameHeight() / 2 + _player->getPlayerClass()->getImagePosition().y + 20);
			}
			else if (Stat == 대기)
			{
				img->frameRender(getMemDC(), x - img->getFrameWidth() / 2 + _player->getPlayerClass()->getImagePosition().x, y - img->getFrameHeight() / 2 + _player->getPlayerClass()->getImagePosition().y + 7);
			}
			else if (Stat == 공격)
			{
				img->frameRender(getMemDC(), x - img->getFrameWidth() / 2 + _player->getPlayerClass()->getImagePosition().x, y - img->getFrameHeight() / 2 + _player->getPlayerClass()->getImagePosition().y + 12);
			}
			else
			{
				img->frameRender(getMemDC(), x - img->getFrameWidth() / 2 + _player->getPlayerClass()->getImagePosition().x, y - img->getFrameHeight() / 2 + _player->getPlayerClass()->getImagePosition().y - 6);
			}
		}
		else if (name == "Tree")
		{
			if (Stat == 피격)
			{
				img->frameRender(getMemDC(), x - img->getFrameWidth() / 2 + _player->getPlayerClass()->getImagePosition().x, y - img->getFrameHeight() / 2 + _player->getPlayerClass()->getImagePosition().y + 20);
			}
			else if (Stat == 대기)
			{
				img->frameRender(getMemDC(), x - img->getFrameWidth() / 2 + _player->getPlayerClass()->getImagePosition().x, y - img->getFrameHeight() / 2 + _player->getPlayerClass()->getImagePosition().y - 5);
			}
			else if (Stat == 공격)
			{
				img->frameRender(getMemDC(), x - img->getFrameWidth() / 2 + _player->getPlayerClass()->getImagePosition().x, y - img->getFrameHeight() / 2 + _player->getPlayerClass()->getImagePosition().y - 5);
			}
			else
			{
				img->frameRender(getMemDC(), x - img->getFrameWidth() / 2 + _player->getPlayerClass()->getImagePosition().x, y - img->getFrameHeight() / 2 + _player->getPlayerClass()->getImagePosition().y - 6);
			}
		}
		else if (name == "Gard")
		{
			if (Stat == 피격)
			{
				img->frameRender(getMemDC(), x - img->getFrameWidth() / 2 + _player->getPlayerClass()->getImagePosition().x, y - img->getFrameHeight() / 2 + _player->getPlayerClass()->getImagePosition().y + 32);
			}
			else if (Stat == 대기)
			{
				img->frameRender(getMemDC(), x - img->getFrameWidth() / 2 + _player->getPlayerClass()->getImagePosition().x, y - img->getFrameHeight() / 2 + _player->getPlayerClass()->getImagePosition().y - 37);
			}
			else if (Stat == 공격)
			{
				img->frameRender(getMemDC(), x - img->getFrameWidth() / 2 + _player->getPlayerClass()->getImagePosition().x, y - img->getFrameHeight() / 2 + _player->getPlayerClass()->getImagePosition().y - 48);
			}
			else if (Stat == 스킬1)
			{
				img->frameRender(getMemDC(), x - img->getFrameWidth() / 2 + _player->getPlayerClass()->getImagePosition().x, y - img->getFrameHeight() / 2 + _player->getPlayerClass()->getImagePosition().y - 50);
			}
			else if (Stat == 이동)
			{
				img->frameRender(getMemDC(), x - img->getFrameWidth() / 2 + _player->getPlayerClass()->getImagePosition().x, y - img->getFrameHeight() / 2 + _player->getPlayerClass()->getImagePosition().y - 40);
			}
			else
			{
				img->frameRender(getMemDC(), x - img->getFrameWidth() / 2 + _player->getPlayerClass()->getImagePosition().x, y - img->getFrameHeight() / 2 + _player->getPlayerClass()->getImagePosition().y - 6);
			}
		}
		else if (name == "Mage")
		{
			if (Stat == 피격)
			{
				img->frameRender(getMemDC(), x - img->getFrameWidth() / 2 + _player->getPlayerClass()->getImagePosition().x, y - img->getFrameHeight() / 2 + _player->getPlayerClass()->getImagePosition().y + 32);
			}
			else if (Stat == 대기)
			{
				img->frameRender(getMemDC(), x - img->getFrameWidth() / 2 + _player->getPlayerClass()->getImagePosition().x, y - img->getFrameHeight() / 2 + _player->getPlayerClass()->getImagePosition().y - 37);
			}
			else if (Stat == 공격)
			{
				img->frameRender(getMemDC(), x - img->getFrameWidth() / 2 + _player->getPlayerClass()->getImagePosition().x, y - img->getFrameHeight() / 2 + _player->getPlayerClass()->getImagePosition().y - 48);
			}
			else if (Stat == 스킬1)
			{
				img->frameRender(getMemDC(), x - img->getFrameWidth() / 2 + _player->getPlayerClass()->getImagePosition().x, y - img->getFrameHeight() / 2 + _player->getPlayerClass()->getImagePosition().y - 50);
			}
			else if (Stat == 이동)
			{
				img->frameRender(getMemDC(), x - img->getFrameWidth() / 2 + _player->getPlayerClass()->getImagePosition().x, y - img->getFrameHeight() / 2 + _player->getPlayerClass()->getImagePosition().y - 40);
			}
			else
			{
				img->frameRender(getMemDC(), x - img->getFrameWidth() / 2 + _player->getPlayerClass()->getImagePosition().x, y - img->getFrameHeight() / 2 + _player->getPlayerClass()->getImagePosition().y - 6);
			}
		}
		else
		{
			if (Stat == 피격)
			{
				img->frameRender(getMemDC(), x - img->getFrameWidth() / 2 + _player->getPlayerClass()->getImagePosition().x, y - img->getFrameHeight() / 2 + _player->getPlayerClass()->getImagePosition().y + 20);
			}
			else
			{
				img->frameRender(getMemDC(), x - img->getFrameWidth() / 2 + _player->getPlayerClass()->getImagePosition().x, y - img->getFrameHeight() / 2 + _player->getPlayerClass()->getImagePosition().y - 6);
			}
		}
	}
	else
	{
		alpha = 0;
		alpha += 2;
		if (alpha > 255)
		{
			alpha = 255;
		}
		img->alphaFrameRender(getMemDC(), x - img->getWidth() / 2 + _player->getPlayerClass()->getImagePosition().x, y - img->getHeight() / 2 + 50 + _player->getPlayerClass()->getImagePosition().y, alpha);
	}
}

void EnemyBase::AgroJudgment()
{
	RECT Nullrc;
	if (IntersectRect(&Nullrc, &_player->getPlayerClass()->getPlayerRc(), &Arc))
	{
		Agro = true;
	}
}


void EnemyBase::PlayerEnemyAttack()
{
	RECT temp;

	if (_player->getPlayerClass()->DMG(rc) && Stat != 피격)//플레이어가 한번 때렸을때 적용됨 
	{
		if (name != "Gard" && name != "boss" && name !="GiantTree")
		{
			Stat = 피격;
		}
		ICount = 0;
		setEnemyHp(Hp - _player->getPlayerClass()->DMG(rc));

		_player->getPlayerClass()->setPlayerAttackColl(false);
	}
	if (name != "Gard" && name != "boss" && name != "GiantTree")
	{
		if (Stat == 피격 && ICount >= 20)
		{
			Stat = 대기;
		}
		//ICount = 넉백시 이동하는 시간 
		else if (Stat == 피격 && ICount < 20 && _player->getPlayerClass()->getDirection() == 오른쪽)
		{
			ICount++;
			x++;//이동량
		}
		else if (Stat == 피격 && ICount < 20 && _player->getPlayerClass()->getDirection() == 왼쪽)
		{
			ICount++;
			x--;//이동량
		}
	}
}

void EnemyBase::EnemyPlayerAttack(RECT rc, int attack)
{
	RECT temp;
	if (IntersectRect(&temp, &ATrc, &_player->getPlayerClass()->getPlayerRc()) && enemyAttackColl && enemyCantAttack == false)
	{
		_player->getPlayerClass()->setPlayerHp(_player->getPlayerClass()->getPlayerHp() - Attck);
		enemyCantAttack = true;
	}

	if (!enemyAttackColl)
	{
		enemyCantAttack = false;
	}
}

void EnemyBase::Hpbar()
{
	hpframe = (int)(Hp * 51 / maxhp);
	if (Agro)
	{
		hpx = x;
		hpy = y + img->getFrameHeight() / 2 + 10;
		hprc = RectMakeCenter(hpx + _player->getPlayerClass()->getImagePosition().x, hpy + _player->getPlayerClass()->getImagePosition().y, 63, 10);
	}
}
void EnemyBase::hpbarrender()
{
	if (Live)
	{
		Hpbg->render(getMemDC(), hprc.left, hprc.top);
		for (int i = 0; i < hpframe; i++)
		{
			hpbar->render(getMemDC(), hprc.left + 6 + (i * 1), hprc.top);
		}
		Hpframe->render(getMemDC(), hprc.left, hprc.top);
	}
}