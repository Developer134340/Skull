#include "stdafx.h"
#include "Boss.h"
#include "player.h"

HRESULT Boss::init()
{

	EnemyBase::init();

	Stat = 보스등장;
	Hp = 500;			// 체력
	Attck = 10;		// 공격력
	Live = true;
	Acion = false;
	dis = 0;
	handdis = 0;
	firecount = 0;
	delayCount = 0;
	name = "boss";
	//=======================================================================
	_EF.ID = _EF.C = 0;

	Spark = false;
	Groggy = false;
	gether = false;
	dieEf = false;
	getherUp = false;
	rebound = false;
	reboundBody = false;
	bodydown = false;
	gethergo = false;


	reboundbool = false;
	//에너지볼 벡터=============================================
	En.I = IMAGEMANAGER->findImage("Bomb");

	En.crush = false;
	En.fire = false;
	En.alpha = 255;
	En.speed = 10.f;
	En.index = 0;
	En.count = 0;


	//보스 출현씬 변수들===========================================================================
	{
		appLh = false;
		appbody = false;
		appdown = false;
		appdowngo = false;
		appheadgo = false;
		appheadDis = 0;
		appjawgo = false;
		appjawDis = 0;
		headSH = false;
		appjawUP = false;
		handPush = false;
		handPull = false;
		handDis = 0;
		G = 0;
		ReadyCount = 0;
	}

	//바디========================================================================================
	{
		_body.I = IMAGEMANAGER->findImage("Body");
		_body.x = WINSIZEX / 2; //640; //
		_body.y = WINSIZEY + (_body.I->getFrameHeight() / 2);//407; //
		_body.rc = RectMakeCenter(_body.x, _body.y, _body.I->getFrameWidth(), _body.I->getFrameHeight());
		_body.C = _body.ID = 0;
	}
	//============================================================================================

	//핸드=========================================================================================
	{
		_hand[0].I = IMAGEMANAGER->findImage("DownHand");
		_hand[0].I->setFrameY(0);
		_hand[0].y = WINSIZEY + (_body.I->getFrameHeight() / 2 / 2); //507; //
		_hand[0].x = _body.x - _body.I->getFrameWidth() / 2; //376; //
		_hand[0].rc = RectMakeCenter(_hand[0].x, _hand[0].y, _hand[0].I->getFrameWidth(), _hand[0].I->getFrameHeight());
		_hand[0].FI = IMAGEMANAGER->findImage("DownHandEF");
	}
	{
		_hand[1].I = IMAGEMANAGER->findImage("DownLHand");
		_hand[1].I->setFrameY(1);
		_hand[1].y = WINSIZEY + (_body.I->getFrameHeight() / 2 / 2); //507; //
		_hand[1].x = _body.x + _body.I->getFrameWidth() / 2; //924; //
		_hand[1].rc = RectMakeCenter(_hand[1].x, _hand[1].y, _hand[1].I->getFrameWidth(), _hand[1].I->getFrameHeight());
		_hand[1].FI = IMAGEMANAGER->findImage("DownLHandEF");
	}

	for (int i = 0; i < 2; i++)
	{
		_hand[i].ID = _hand[i].C = 0;
		_hand[i].FC = _hand[i].FID = 0;
		_hand[i].EF = false;
		_hand[i].goEF = false;
	}

	_EF.I = IMAGEMANAGER->findImage("NULL");

	//==============================================================================================
	//head==========================================================================================
	_head.I = IMAGEMANAGER->findImage("BossHead");
	_head.x = WINSIZEX / 2;//640; //
	_head.y = _head.y = _body.y - _body.I->getFrameHeight() / 12;//359; //
	_head.rc = RectMakeCenter(_head.x, _head.y, _head.I->getFrameWidth(), _head.I->getFrameHeight());
	_head.ID = _head.C = 0;
	//==============================================================================================
	//Jaw===========================================================================================
	_jaw.I = IMAGEMANAGER->findImage("Jaw");
	_jaw.x = WINSIZEX / 2 + 25;//665; //
	_jaw.y = _head.y + _head.I->getFrameHeight() / 2 - 20;//484; //
	_jaw.rc = RectMakeCenter(_jaw.x, _jaw.y, _jaw.I->getFrameWidth(), _jaw.I->getFrameHeight());
	_jaw.ID = _jaw.C = 0;
	//==============================================================================================
	
	changeFont(30, RGB(255, 255, 255));

	return S_OK;
}

void Boss::release()
{
}

void Boss::update()
{
	AppBoss();//보스등장씬에서만 사용
//========================================
	findImage();
	AI();
	fireAction();
	PlayerBossAttack();
	
}

void Boss::render()
{
	renderBoss();
	hp();
}

void Boss::hp()
{
	if (Stat != 보스등장 && Live)
	{
		_BHP.nameBg->alphaRender(getMemDC(), _BHP.namerc.left, _BHP.namerc.top, 100);
		_BHP.HPbarBg->render(getMemDC(), _BHP.rc.left, _BHP.rc.top);

		wsprintf(Cname, "위그드라실");
		DrawText(getMemDC(), Cname, -1, &_BHP.namerc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		//FrameRect(getMemDC(), _BHP.namerc, RGB(255, 0, 0));

		for (int i = 0; i < _BHP.Hpbar; i++)
		{
			_BHP.HPbar->render(getMemDC(), (WINSIZEX / 2 - (_BHP.Frame->getWidth() / 2) + 46) + (i * 2), _BHP.rc.top + 12);
		}

		_BHP.Frame->render(getMemDC(), _BHP.rc.left, _BHP.rc.top);
	}
}
void Boss::AppBoss()
{
	if (Stat == 보스등장)
	{
		if (_hand[0].y <= WINSIZEY - (484 / 2 / 2) - 10)
		{
			if (!_hand[0].goEF)
			{
				appLh = true;
				_hand[0].I->setFrameX(1);
				_hand[0].fx = _hand[0].x;
				_hand[0].fy = _hand[0].y - _hand[0].FI->getFrameHeight() / 4;
				_hand[0].frc = RectMakeCenter(_hand[0].fx, _hand[0].fy, _hand[0].FI->getFrameWidth(), _hand[0].FI->getFrameHeight());
				_hand[0].EF = true;
				_hand[0].goEF = true;
			}

		}
		else
		{
			static int CO = 0;
			static int SH = 0;
			CO++;
			if (CO % 7 == 0)
			{
				SH++;
			}
			if (SH % 2 == 0)
			{
				_hand[0].x += 2;
			}
			else
			{
				_hand[0].x -= 2;
			}
			_hand[0].y -= 2;
		}
		if (appLh)
		{
			if (_hand[1].y <= WINSIZEY - (484 / 2 / 2) - 10)
			{
				if (!_hand[1].goEF)
				{
					_hand[1].I->setFrameX(1);
					_hand[1].fx = _hand[1].x;
					_hand[1].fy = _hand[1].y - _hand[1].FI->getFrameHeight() / 4;
					_hand[1].frc = RectMakeCenter(_hand[1].fx, _hand[1].fy, _hand[1].FI->getFrameWidth(), _hand[1].FI->getFrameHeight());
					_hand[1].EF = true;
					_hand[1].goEF = true;
				}
				if (!appbody)
				{
					static int body = 0;
					body++;
					if (body % 50 == 0)
					{
						appbody = true;
					}
				}
			}
			else
			{
				static int CO = 0;
				static int SH = 0;
				CO++;
				if (CO % 7 == 0)
				{
					SH++;
				}
				if (SH % 2 == 0)
				{
					_hand[1].x += 2;
				}
				else
				{
					_hand[1].x -= 2;
				}
				_hand[1].y -= 2;
			}
		}

		if (appbody)
		{

			if (_body.y - _body.I->getFrameHeight() / 5 > WINSIZEY - _body.I->getFrameHeight() / 2 - _body.I->getFrameHeight() / 4)
			{
				_body.y -= 30;
				_head.y -= 30;
				_jaw.y -= 30;
				if (!appdowngo)
				{
					appdown = true;
				}
			}
			if (appdown)
			{
				G += 0.5;
				_body.y += G;
				_head.y += G;
				_jaw.y += G;
				static int down;
				down++;
				if (down % 50 == 0)
				{
					appdowngo = true;
					appheadgo = true;
					appdown = false;
				}
			}
		}
		if (appheadgo)
		{
			if (appheadDis < 120)
			{
				_head.y += 20;
				_jaw.y += 20;
				appheadDis += 20;
				appjawgo = true;
				handPush = true;
			}
			else { appheadgo = false; }
		}
		if (handPush)
		{
			if (handDis < 90)
			{
				_hand[0].x -= 2;
				_hand[1].x += 2;
				handDis += 2;
			}
			else { handPush = false; }

		}
		if (appjawgo)
		{
			if (appjawDis < 40)
			{
				_jaw.y += 20;
				appjawDis += 20;
				headSH = true;
			}
			else { appjawgo = false; }
		}
		if (headSH)
		{
			static int headS = 0;
			static int headK = 0;
			headS++;
			if (headS % 2 == 0)
			{
				headK++;
				if (headK % 2 == 0)
				{
					_head.x += 5;
					_jaw.x += 5;
				}
				else
				{
					_head.x -= 5;
					_jaw.x -= 5;
				}
				if (headK >= 60)
				{
					appjawUP = true;
					headSH = false;
				}
			}
		}
		if (appjawUP)
		{
			if (appjawDis > 0)
			{
				_jaw.y -= 20;
				appjawDis -= 20;
				appheadUP = true;
				handPull = true;
			}
			else { appjawUP = false; }
		}
		if (appheadUP)
		{
			if (appheadDis > 0)
			{
				_head.y -= 20;
				_jaw.y -= 20;
				appheadDis -= 20;
			}
			else { appheadUP = false; }
		}
		if (handPull)
		{
			if (handDis > 0)
			{
				_hand[0].x += 3;
				_hand[1].x -= 3;
				_hand[0].y -= 2;
				_hand[1].y -= 2;
				handDis -= 2;
			}
			else { Stat = 보스대기; }
		}
	}
}

//==============================================================================================

void Boss::findImage()
{
	_BHP.Hpbar = (int)(Hp * 225 / 500);

	if (Stat == 보스대기) { _EF.I = IMAGEMANAGER->findImage("NULL"); }
	else if (Spark) { _EF.I = IMAGEMANAGER->findImage("Spark"); }
	else if (Groggy){ _EF.I = IMAGEMANAGER->findImage("GroggyEF"); }
	else if (gether) { _EF.I = IMAGEMANAGER->findImage("gether"); }


	if (Live)
	{
		
		if (Stat == 보스대기)
		{
			_hand[0].I = IMAGEMANAGER->findImage("PucnhReady");
			_hand[0].I->setFrameY(0);
			_hand[1].I = IMAGEMANAGER->findImage("PucnhLReady");
			_hand[1].I->setFrameY(1);
		}
		else if (Stat == 보스발사)
		{
			_hand[0].I = IMAGEMANAGER->findImage("DownHand");
			_hand[0].I->setFrameY(0);
			_hand[0].I->setFrameX(1);
			_hand[1].I = IMAGEMANAGER->findImage("DownLHand");
			_hand[1].I->setFrameY(1);
			_hand[1].I->setFrameX(1);
		}
	}

	else
	{
		_hand[0].I = IMAGEMANAGER->findImage("DownHand");
		_hand[0].I->setFrameY(0);
		_hand[1].I = IMAGEMANAGER->findImage("DownLHand");
		_hand[1].I->setFrameY(1);
		_EF.I = IMAGEMANAGER->findImage("DeadEF");
	}

	

	//프레임이미지====================================================
	for (int i = 0; i < 2; i++)
	{
		if (_hand[i].EF)
		{
			_hand[i].FC++;
			if (_hand[i].FC % 5 == 0)
			{
				_hand[i].FID++;
				if (_hand[i].FID > _hand[i].FI->getMaxFrameX())
				{
					_hand[i].FC = 0;
					_hand[i].FID = 0;
					_hand[i].EF = false;
				}
			}
			_hand[i].FI->setFrameX(_hand[i].FID);
		}

		if (Stat == 보스대기)
		{
			_hand[i].C++;
			if (_hand[i].C % 30 == 0)
			{
				_hand[i].ID++;
				if (_hand[i].ID > _hand[i].I->getMaxFrameX())
				{
					_hand[i].ID = 3;
				}
			}
			_hand[i].I->setFrameX(_hand[i].ID);
		}	
	}

	if (rebound)
	{
		_hand[0].C++;
		if (_hand[0].C % 5 == 0)
		{
			_hand[0].ID++;
			{
				if (_hand[0].ID > 3)
				{
					_hand[0].ID = 1;
					_hand[1].ID = 1;
					rebound = false;
				}
			}
		}
		_hand[0].I->setFrameX(_hand[0].ID);
		_hand[1].I->setFrameX(_hand[0].ID);
	}
	if (reboundBody)
	{
		static int iii,iic = 0;
		iic++;
		if (iic % 5 == 0)
		{
			iii++;
			if (iii > 2)
			{
				iii = 0;
				iic = 0;
				rebound = true;
				reboundBody = false;
			}
		}
		_body.I->setFrameX(iii);
	}
	
	if (Spark && !_vEn.empty())
	{
		static int ix, ic = 0;
		ic++;
		if (ic % 5 == 0)
		{
			ix++;
			if (ix > 2)
			{
				ix = 0;
			}
		}
		_head.I->setFrameX(ix);
		_jaw.I->setFrameX(ix);
	}
	else if(!Spark)
	{
		_head.I->setFrameX(0);
		_jaw.I->setFrameX(0);
	}


	for (int i = 0; i < _vEn.size(); i++)
	{
		if (_vEn[i].fire)
		{
			_vEn[i].count++;
			if (_vEn[i].count % 5 == 0)
			{
				_vEn[i].index++;
				if (_vEn[i].index > _vEn[i].I->getMaxFrameX())
				{
					_vEn[i].index = 0;
					_vEn[i].count = 0;
				}
			}
			_vEn[i].I->setFrameX(_vEn[i].index);
		}
	

		if (_vEn[i].crush)
		{ 		
			_vEn[i].count++;
			if (_vEn[i].count % 3 == 0)
			{
				_vEn[i].index++;
				if (_vEn[i].index > _vEn[i].I->getMaxFrameX())
				{
					_vEn[i].index = 0;
					_vEn.erase(_vEn.begin() + i);
					break;
				}
			}
			_vEn[i].I->setFrameX(_vEn[i].index);
		}
	}




	//렉트업데이트==============================================================
	_body.rc = RectMakeCenter(_body.x, _body.y, _body.I->getFrameWidth(), _body.I->getFrameHeight());
	_head.rc = RectMakeCenter(_head.x, _head.y, _head.I->getFrameWidth(), _head.I->getFrameHeight());
	_jaw.rc = RectMakeCenter(_jaw.x, _jaw.y, _jaw.I->getFrameWidth(), _jaw.I->getFrameHeight());
	for (int i = 0; i < _vEn.size(); i++)
	{
		if (_vEn[i].fire)
		{
			_vEn[i].rc = RectMakeCenter(_vEn[i].x, _vEn[i].y, _vEn[i].I->getFrameWidth(), _vEn[i].I->getFrameHeight());
		}
		else if (_vEn[i].crush)
		{
			_vEn[i].rc = RectMakeCenter(_vEn[i].x, _vEn[i].y - _vEn[i].I->getFrameHeight()/4 , _vEn[i].I->getFrameWidth(), _vEn[i].I->getFrameHeight());
		}
	}

	for (int i = 0; i < 2; i++)
	{
		_hand[i].rc = RectMakeCenter(_hand[i].x, _hand[i].y, _hand[i].I->getFrameWidth(), _hand[i].I->getFrameHeight());
	}

	if (gether || Spark)
	{
		_EF.x = _head.x;
		_EF.y = _head.y;
	}
	if (gether || Spark || Groggy || dieEf)
	{
		_EF.rc = RectMakeCenter(_EF.x, _EF.y, _EF.I->getFrameWidth(), _EF.I->getFrameHeight());
	}
}

void Boss::renderBoss()
{
	_body.I->frameRender(getMemDC(), _body.rc.left + _player->getPlayerClass()->getImagePosition().x, _body.rc.top + _player->getPlayerClass()->getImagePosition().y);
	_head.I->frameRender(getMemDC(), _head.rc.left + _player->getPlayerClass()->getImagePosition().x, _head.rc.top + _player->getPlayerClass()->getImagePosition().y);
	_jaw.I->frameRender(getMemDC(), _jaw.rc.left + _player->getPlayerClass()->getImagePosition().x, _jaw.rc.top + _player->getPlayerClass()->getImagePosition().y);
	for (int i = 0; i < 2; i++)
	{
		_hand[i].I->frameRender(getMemDC(), _hand[i].rc.left + _player->getPlayerClass()->getImagePosition().x, _hand[i].rc.top + _player->getPlayerClass()->getImagePosition().y);
		
		if (_hand[i].EF)
		{
			_hand[i].FI->frameRender(getMemDC(), _hand[i].frc.left + _player->getPlayerClass()->getImagePosition().x, _hand[i].frc.top + _player->getPlayerClass()->getImagePosition().y);
		}
	}

	if (gether || Spark || Groggy || dieEf)
	{
		_EF.I->frameRender(getMemDC(), _EF.rc.left + _player->getPlayerClass()->getImagePosition().x, _EF.rc.top + _player->getPlayerClass()->getImagePosition().y);
	}
	
	for (int i = 0; i < _vEn.size(); i++)
	{
		if (_vEn[i].fire)
		{
			_vEn[i].I = IMAGEMANAGER->findImage("Bomb");
			_vEn[i].I->frameRender(getMemDC(), _vEn[i].rc.left + _player->getPlayerClass()->getImagePosition().x, _vEn[i].rc.top + _player->getPlayerClass()->getImagePosition().y);
		}
		if (_vEn[i].crush)
		{
			_vEn[i].I = IMAGEMANAGER->findImage("Explorsion");

			_vEn[i].I->frameRender(getMemDC(), _vEn[i].rc.left + _player->getPlayerClass()->getImagePosition().x, _vEn[i].rc.top + _player->getPlayerClass()->getImagePosition().y);
		}
	}

	//프레임렉트============================================================
	if (KEYMANAGER->isToggleKey('Q'))
	{
		FrameRect(getMemDC(), _body.rc, RGB(255, 0, 255));
		for (int i = 0; i < 2; i++)
		{
			FrameRect(getMemDC(), _hand[i].rc, RGB(0, 0, 255));
			if (_hand[i].EF || _hand[i].goEF)
			{
				FrameRect(getMemDC(), _hand[i].frc, RGB(0, 0, 255));
			}
		}
		FrameRect(getMemDC(), _jaw.rc, RGB(255, 0, 0));
		FrameRect(getMemDC(), _head.rc, RGB(255, 0, 0));
		for (int i = 0; i < _vEn.size(); i++)
		{
			FrameRect(getMemDC(), _vEn[i].rc, RGB(255, 100, 255));
		}
	}
}



void Boss::HandDown()
{

}

void Boss::AI()
{
	if (Stat == 보스대기)
	{
		bodydown = false;
		static int ready = 0;
		ready++;
		delayCount++;
		if (ready % 40 == 0)
		{
			ReadyCount++;
			if (ReadyCount % 4 == 1 || ReadyCount % 4 == 2)
			{
				_body.y += 5;
				_head.y -= 5;
				_jaw.y += 7;
				_hand[0].y += 8;
				_hand[1].y += 8;
			}
			else
			{
				_body.y -= 5;
				_head.y += 5;
				_jaw.y -= 7;
				_hand[0].y -= 8;
				_hand[1].y -= 8;
			}
		}
		if (delayCount % 300 == 0)
		{
			_hand[0].ID = _hand[1].ID = 1;
			_hand[0].C = _hand[1].C = 0;
			delayCount = 0;
			handdis = 0;
			Stat = 보스발사;
		}
	}

	//에너지볼 발사=====================================================================================
	for (int i = 0; i < _vEn.size(); i++)
	{
		if (_vEn[i].fire)
		{
			_vEn[i].x += cos(_vEn[i].angle) * _vEn[i].speed;
			_vEn[i].y += -sin(_vEn[i].angle) * _vEn[i].speed;

			if (_vEn[i].y >= WINSIZEY - _vEn[i].I->getFrameHeight() / 2)
			{
				_vEn[i].index = 0; 
				_vEn[i].count = 0;
				_vEn[i].crush = true;
				_vEn[i].fire = false;
			}
		}
	}
}

void Boss::PlayerBossAttack()
{
	if (_player->getPlayerClass()->DMG(_head.rc))
	{
		setEnemyHp(Hp - _player->getPlayerClass()->DMG(_head.rc));
		_player->getPlayerClass()->setPlayerAttackColl(false);
	}
}

void Boss::fireAction()
{
	if (Stat == 보스발사) //내려감
	{
		if (!gether && !Spark)
		{
			if (handdis < 80)
			{
				handdis += 20;
				_hand[0].y += 20;
				_hand[1].y += 20;
			}
			else
			{
				if (dis <= 90)
				{
					dis += 10;
					_head.y += 15;
					_body.y += 10;
					_jaw.y += 12;
				}
				else
				{
					gethergo = true;
					handdis = 0;
					dis = 0;
				}
			}
		}

		if (gethergo)
		{
			gether = true;
		}
	}

	//기모으기===============================================================
	if (gether)
	{
		gethergo = false;
		_EF.C++;
		{
			if (_EF.C % 8 == 0)
			{
				_EF.ID++;
				if (_EF.ID > 22)
				{
					getherUp = true;
				}
				if (_EF.ID > _EF.I->getMaxFrameX())
				{
					_EF.ID = _EF.C = 0;
					gether = false;
				}
			}
			_EF.I->setFrameX(_EF.ID);
		}

		if (!getherUp && !Spark)
		{
			static int sk = 0;
			static int dly = 0;
			dly++;
			if (dly % 2 == 0)
			{
				sk++;
			}
			if (sk % 2 == 0)
			{
				_head.x += 2;
				_jaw.x += 2;
				_head.y -= 2;
				_jaw.y -= 2;
			}
			else
			{
				_head.x -= 2;
				_jaw.x -= 2;
				_head.y += 2;
				_jaw.y += 2;
			}
		}

	}

	if (getherUp && !Spark) // 올라감
	{
		if (dis < 90)
		{
			dis += 10;
			_head.y -= 22;
			_body.y -= 7;
			_jaw.y -= 20;
		}
		else
		{
			dis = 0;
			Spark = true;
			getherUp = false;
		}
	}

	if (Spark)
	{	
		_EF.C++;
		{
			if (_EF.C % 12 == 0)
			{
				_EF.ID++;

				if (_EF.ID > _EF.I->getMaxFrameX())
				{
					En.x = _EF.x;
					En.y = _EF.y;
					En.angle = getAngle(En.x, En.y, _player->getPlayerClass()->getPlayerPosition().x, _player->getPlayerClass()->getPlayerPosition().y);
					reboundBody = true;
					En.alpha = 0;
					En.I = IMAGEMANAGER->findImage("Bomb");
					En.fire = true;
					reboundbool = true;
					_vEn.push_back(En);
					_EF.ID = _EF.C = 0;

					firecount++;
					if (firecount >= boll)
					{
						firecount = 0;
						bodydown = true;
						Spark = false;
					}
				}
			}
			_EF.I->setFrameX(_EF.ID);
		}

		if (reboundbool)
		{
			static int reboundNum = 0;

			reboundNum++;
			if (reboundNum % 2 == 0)
			{
				_head.y += 10;
				_jaw.y -= 10;
				_body.y += 10;
			}
			else
			{
				_head.y -= 10;
				_body.y -= 10;
				_jaw.y += 10;
			}
			if (reboundNum % 8 == 0)
			{
				reboundbool = false;
			}
		}

	}

	if (bodydown)
	{
		_body.x = 640;
		_body.y = 407;
		_hand[0].y = 507;
		_hand[0].x = 376;
		_hand[1].y = 507;
		_hand[1].x = 924;
		_head.x = 640;
		_head.y = 359;
		_jaw.x = 665;
		_jaw.y = 484;
		handdis = 0;
		dis = 0;			
		Stat = 보스대기;		
	}

}