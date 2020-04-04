#include "stdafx.h"
#include "GiantTree.h"
#include "player.h"

HRESULT GiantTree::init()
{
	EnemyBase::init();

	Stat = 대기;
	Direction = 오른쪽;	//방향
	x = WINSIZEX/2;
	y = WINSIZEY/2;		// 좌표
	Hp = 150;			// 체력
	maxhp = Hp;
	Attck = 20;		// 공격력
	name = "GiantTree"; 
	Live = true;
//	exImagePosition = _player->getPlayerClass()->getImagePosition();

	range = 2000;
	
	
	//=========
	GreenCount=0;
	GreenIndex=0;
	effetCount = 0;
	effectIndex = 0;
	Been.angle = PI_2;
	AttackCount = 0;
	stomp = false;
	stompDam = false;
	stompEffet = IMAGEMANAGER->findImage("GiantTreeEffect");
	GreenBeenI = IMAGEMANAGER->findImage("Light");
	
	stompRc = RectMakeCenter(x , y+25, stompEffet->getFrameWidth(), stompEffet->getFrameHeight());
	stompDagmeRC = RectMakeCenter(x , y+80 , stompEffet->getFrameWidth(), 20);
	GreenBeenDmg = 15;
	//=========

	img = IMAGEMANAGER->findImage("GiantTreeIdle");

	return S_OK;
}

void GiantTree::release()
{
	
}

void GiantTree::update()
{
	EnemyBase::update();
		//어그로판정
	if (Live)
	{
		AgroJudgment();
		AI();
		AttactRender(10);
		RangeAttack();
		PlayerEnemyAttack();
		Hpbar();
	}
	if (Hp <= 0)
	{
		Hp = 0;
		Live = false;
	}
	//Moving , Read Frame
	FrameMonsterI(10);


	//=====================
	rc = RectMakeCenter(x + _player->getPlayerClass()->getImagePosition().x, y + _player->getPlayerClass()->getImagePosition().y, img->getFrameWidth(), img->getFrameHeight());		// 몬스터 렉트
	Arc = RectMakeCenter(x + _player->getPlayerClass()->getImagePosition().x, y + _player->getPlayerClass()->getImagePosition().y+25, stompEffet->getFrameWidth()+500, stompEffet->getFrameHeight()+500);
	ATrc = RectMakeCenter(x + _player->getPlayerClass()->getImagePosition().x, y + _player->getPlayerClass()->getImagePosition().y + 25, stompEffet->getFrameWidth(), stompEffet->getFrameHeight());
	//=====================
	
	
}

void GiantTree::render()
{
	EnemyBase::render();
	//프레임렌더 출력=============
	renderMonster(rc,Arc,ATrc);
	//이미지 출력=============
	ImageRender();

	if (stomp)
	{
		stompEffet->frameRender(getMemDC(), stompRc.left, stompRc.top);
	}
	
	for (int i = 0; i < _vBeen.size(); i++)
	{
		GreenBeenI->frameRender(getMemDC(), _vBeen[i].rc.left, _vBeen[i].rc.top);
	}
	
	hpbarrender();
}


void GiantTree::AI()
{
	float distance = getDistance(_player->getPlayerClass()->getPlayerPosition().x, _player->getPlayerClass()->getPlayerPosition().y,
		x + _player->getPlayerClass()->getImagePosition().x, y + _player->getPlayerClass()->getImagePosition().y);
	if (Agro && !Acion)
	{
		if (distance > 300)
		{
			Stat = 원거리;
			Acion = true;
		}
		if (distance < 300)
		{
			if (AttackCount >= 1)
			{
				Stat = 공격;
				AttackCount = 0;
				Acion = true;
			}
			else
			{
				AttackCount++;
				Stat = 원거리;
				Acion = true;
			}
		}
	}

}

void GiantTree::AttactRender(int ImageSpeed)
{

	if (Stat == 원거리)
	{
		img = IMAGEMANAGER->findImage(name + "Range");
		ICount++;

		if (IIndex < 2)
		{
			if (ICount % 50 == 0)
			{
				IIndex++;
				img->setFrameX(IIndex);
			}
		}

		else
		{
			if (ICount % ImageSpeed == 0)
			{
				IIndex++;
				if (IIndex > img->getMaxFrameX())
				{
					IIndex = 0;
					Stat = 대기;
				}
				if (IIndex == 3)
				{
					Been.angle = PI_2;
					for (int i = 0; i < 6; i++)
					{
						Been.speed = 6.f;
						Been.exX = x + _player->getPlayerClass()->getImagePosition().x;
						Been.exY = Been.y = y + _player->getPlayerClass()->getImagePosition().y + 25;
						Been.x = x + _player->getPlayerClass()->getImagePosition().x;
						Been.y = y + _player->getPlayerClass()->getImagePosition().y + 25;
						Been.rc = RectMakeCenter(Been.x, Been.y, GreenBeenI->getFrameWidth(), GreenBeenI->getFrameHeight());
						Been.exImagePosition = _player->getPlayerClass()->getImagePosition();
						Been.angle += (PI2 / 6);
						_vBeen.push_back(Been);
					}
				}
				img->setFrameX(IIndex);
			}
		}
	}
	if (Stat == 공격)
	{
		img = IMAGEMANAGER->findImage(name + "Attack");
		ICount++;
		if (ICount % ImageSpeed == 0)
		{
			IIndex++;
			if (IIndex > img->getMaxFrameX())
			{
				IIndex = 0;
				Stat = 대기;			
			}
			if (IIndex == 5)
			{
				stomp = true;
				stompDam = true;
//				exImagePosition = _player->getPlayerClass()->getImagePosition();
			}
			img->setFrameX(IIndex);

		}
	}

	if (stomp)
	{
		effetCount++;
		if (effetCount % 3 == 0)
		{
			effectIndex++;
			if (effectIndex > 20)
			{
				effectIndex = 0;
				stompDam = false;
				stomp = false;
			}
			stompEffet->setFrameX(effectIndex);
		}
	}
}

void GiantTree::RangeAttack()
{
	GreenCount++;
	if (GreenCount % 10 == 0)
	{
		GreenIndex++;
		if (GreenIndex > GreenBeenI->getMaxFrameX())
		{
			GreenIndex = 0;
		}
		GreenBeenI->setFrameX(GreenIndex);
	}

	for (int i = 0; i < _vBeen.size(); i++)
	{
		_vBeen[i].exX += cosf(_vBeen[i].angle) * _vBeen[i].speed;
		_vBeen[i].exY += -sinf(_vBeen[i].angle) * _vBeen[i].speed;
		_vBeen[i].x = _vBeen[i].exX + _player->getPlayerClass()->getImagePosition().x-_vBeen[i].exImagePosition.x;
		_vBeen[i].y = _vBeen[i].exY + _player->getPlayerClass()->getImagePosition().y - _vBeen[i].exImagePosition.y;
		_vBeen[i].rc = RectMakeCenter(_vBeen[i].x, _vBeen[i].y, GreenBeenI->getFrameWidth(), GreenBeenI->getFrameHeight());
		_vBeen[i].distance = getDistance(x, y, _vBeen[i].x, _vBeen[i].y);

		if (range < _vBeen[i].distance)
		{
			_vBeen.erase(_vBeen.begin()+i);
		}
	}

}