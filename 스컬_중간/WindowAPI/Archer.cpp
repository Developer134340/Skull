#include "stdafx.h"
#include "Archer.h"
#include "player.h"

HRESULT Archer::init()
{
	EnemyBase::init();

	Stat = ���;
	Direction = rand() % 2;;//rand() % 2;	//����
	//x = WINSIZEX / 2;
	//y = WINSIZEY / 2;		// ��ǥ
	Hp = 80;			// ü��
	maxhp = Hp;
	Attck = 10;		// ���ݷ�
	name = "Archar";
	Live = true;
	Speed = 1.f;

	Agro = false;

	fire = false;
	AimOn = false;
	alp = 0;

	img = IMAGEMANAGER->findImage("ArcharIdle");
	Aim = IMAGEMANAGER->findImage("ArcharAim");
	Arrow = IMAGEMANAGER->findImage("Arrow");

	_Shot.speed = 14.f;

	

	return S_OK;
}

void Archer::release()
{
}

void Archer::update()
{
	EnemyBase::update();
	RECT temp;
	if (Live)
	{
		for (int i = 0; i < _vShot.size(); i++)
		{
			if (IntersectRect(&temp, &_player->getPlayerClass()->getPlayerRc(), &_vShot[i].arrowrc))
			{
				_vShot.erase(_vShot.begin() + i);
				_player->getPlayerClass()->setPlayerHp(_player->getPlayerClass()->getPlayerHp() - Attck);
				fire = false;
			}
		}
		PlayerEnemyAttack();
		AgroJudgment();
		AI();
	}
	if (Hp <= 0)
	{
		Hp = 0;
		Live = false;
	}
	FrameMonsterI(10);
	//================================================================
	rc = RectMakeCenter(x + _player->getPlayerClass()->getImagePosition().x, y + _player->getPlayerClass()->getImagePosition().y, img->getFrameWidth(), img->getFrameHeight());		// ���� ��Ʈ
	ATrc = RectMakeCenter(x + _player->getPlayerClass()->getImagePosition().x, y + _player->getPlayerClass()->getImagePosition().y, img->getFrameWidth()+900, img->getFrameHeight()+900); 		// ���� ���ݹ���
	Arc = RectMakeCenter(x + _player->getPlayerClass()->getImagePosition().x, y + _player->getPlayerClass()->getImagePosition().y, img->getFrameWidth() + 900, img->getFrameHeight() + 900);
	
	//================================================================


}

void Archer::render()
{
	EnemyBase::render();
	renderMonster(rc, Arc, ATrc);
	ImageRender();

	if (Stat != �ǰ� && Live)
	{
		if (AimOn)
		{
			Aim->alphaRender(getMemDC(), AimRc.left, AimRc.top, alp);
		}

		if (fire)
		{
			if (Direction == ������)
			{
				Arrow->setFrameY(0);
				Arrow->frameRender(getMemDC(), _vShot[0].arrowrc.left, _vShot[0].arrowrc.top);
			}
			else
			{
				Arrow->setFrameY(1);
				Arrow->frameRender(getMemDC(), _vShot[0].arrowrc.left, _vShot[0].arrowrc.top);
			}
		}
	}
	hpbarrender();
}


void Archer::AI()
{
	float distance = getDistance(_player->getPlayerClass()->getPlayerPosition().x, _player->getPlayerClass()->getPlayerPosition().y,
		x + _player->getPlayerClass()->getImagePosition().x, y + _player->getPlayerClass()->getImagePosition().y);

	if (Agro)
	{
		
		if (!Acion)
		{
			if (_player->getPlayerClass()->getPlayerPosition().x > x + _player->getPlayerClass()->getImagePosition().x)
			{
				Direction = ������;
			}
			else if (_player->getPlayerClass()->getPlayerPosition().x < x + _player->getPlayerClass()->getImagePosition().x) { Direction = ����; }
		}
		if (distance > 480)
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
		
		if (Stat == �̵� && Direction == ������)
		{
			x += Speed;
		}
		else if (Stat == �̵� && Direction == ����)
		{
			x -= Speed;
		}
		
		Attack();

	}
}

void Archer::Attack()
{
	if (Stat == ����)
	{
		static int ICount = 0;
		static int IIndex = 0;
		img = IMAGEMANAGER->findImage(name + "Attack");
		Acion = true;
		if (Direction == ������)
		{
			img->setFrameY(0);
		}
		else { img->setFrameY(1); }
		
		if (IIndex != 3)
		{
			ICount++;
			if (ICount % 10 == 0)
			{
				IIndex++;
			}
		}
		if (IIndex == 3)
		{
			AimOn = true;
		}
			img->setFrameX(IIndex);
	}

	if (AimOn)
	{
		if (Direction == ������)
		{
			AimRc = RectMake(x + 30 + _player->getPlayerClass()->getImagePosition().x, y - 6 + _player->getPlayerClass()->getImagePosition().y, Aim->getFrameWidth(), Aim->getFrameHeight());
			_Shot.x = x + 30, _Shot.y = y - 4;
			_Shot.arrowrc = RectMake(_Shot.x + _player->getPlayerClass()->getImagePosition().x, _Shot.y + _player->getPlayerClass()->getImagePosition().y, Arrow->getFrameWidth(), Arrow->getFrameHeight());
		}
		else { AimRc = RectMake(x - 910 + _player->getPlayerClass()->getImagePosition().x, y - 6 + _player->getPlayerClass()->getImagePosition().y, Aim->getFrameWidth(), Aim->getFrameHeight());
				_Shot.x = x - 55, _Shot.y = y - 4; 
				_Shot.arrowrc = RectMake(_Shot.x + _player->getPlayerClass()->getImagePosition().x, _Shot.y + _player->getPlayerClass()->getImagePosition().y, Arrow->getFrameWidth(), Arrow->getFrameHeight());}

		alp += 2;
		if (alp > 255)
		{
			alp = 0;
			fire = true;			
			AimOn = false;
			Stat = ���;
		}
	}

	if (fire)
	{

		if (_vShot.empty())
		{
			_vShot.push_back(_Shot);
		}

		float distance = getDistance(_vShot[0].x, _vShot[0].y, x, y);

		if (Direction == ������) { _vShot[0].x += _vShot[0].speed; }
		else{ _vShot[0].x -= _vShot[0].speed;  }

		_vShot[0].arrowrc = RectMake(_vShot[0].x + _player->getPlayerClass()->getImagePosition().x, _vShot[0].y + _player->getPlayerClass()->getImagePosition().y, Arrow->getFrameWidth(), Arrow->getFrameHeight());
		
		if (distance > 460)
		{
			_vShot.erase(_vShot.begin());
			IIndex = 0;
			ICount = 0;
			fire = false;
		}
	}
}
