#include "stdafx.h"
#include "Player.h"

HRESULT Player::init()
{
	_MainSkul = new nomalSkull;
	_MainSkul->init();

	_positionBefore = _MainSkul->getPlayerPosition();
	_vectorX = 0.0f;
	_vectorY = 0.0f;

	_ui = new userInt;
	_ui->init();

	itemBase* temp;
	temp = new headNormalSkul;
	temp->init();
	_vSkul.push_back(temp);

	_currentSkul = "스컬";

	essenceBase* temp2;
	temp2 = new flameDragon;
	temp2->init();
	_vEssence.push_back(temp2);

	return S_OK;
}

void Player::release()
{
	_ui->release();
}

void Player::update()
{
	_MainSkul->update();
	_ui->update(_currentSkul, _MainSkul->getNowHP(), _MainSkul->getMaxHP(), _vSkul, _vItem, _vEssence);

	if (!_ui->getTabOn())
	{
		KeyAction();
	}

	this->changeSkul();


	if (_vEssence.size() != 0)
	{
		_vEssence[0]->update();
		_vEssence[0]->fire(_MainSkul->getPlayerRc(), _MainSkul->getDirection(), getPlayerClass()->getImagePosition());
	}

}

void Player::render()
{
	_MainSkul->render();

	if (_vEssence.size() != 0)
	{
		_vEssence[0]->render();
	}

	_ui->render();
}

void Player::KeyAction()
{//===============================================
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_MainSkul->Move(VK_LEFT);
	}

	if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
	{
		_MainSkul->KeyUp();
	}
//===============================================
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_MainSkul->Move(VK_RIGHT);
	}

	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		_MainSkul->KeyUp();
	}
//===============================================
	if (KEYMANAGER->isOnceKeyDown('Z'))//대시
	{
		_MainSkul->DashStat();
	}
	if (KEYMANAGER->isOnceKeyDown('X'))//공격
	{
		_MainSkul->AttackStat();
	}
	if (KEYMANAGER->isOnceKeyDown('C'))//점프
	{
		_MainSkul->JumpStat();
	}
	if (KEYMANAGER->isOnceKeyDown('A'))//스킬1
	{
		_MainSkul->setStat(스킬1);
	}
	if (KEYMANAGER->isOnceKeyDown('S'))//스킬2
	{
		_MainSkul->setStat(스킬2);
	}
	//if (KEYMANAGER->isOnceKeyDown('D'))//정수
	//{
	//	;
	//}
	//if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	//{
	//	;
	//}
}

void Player::camMove(image * bgImg) //플레이어의 위치에 따라 cam 을 움직이는 함수
{
	if (_positionBefore.x == _MainSkul->getPlayerPosition().x) {}
	else if (_MainSkul->getPlayerPosition().x < _MainSkul->getImagePosition().x + (WINSIZEX / 2)) { _MainSkul->setImagePositionX(0); }
	else if (_MainSkul->getPlayerPosition().x > _MainSkul->getImagePosition().x + bgImg->getWidth() - (WINSIZEX / 2)) { _MainSkul->setImagePositionX(WINSIZEX - bgImg->getWidth()); }
	else
	{
		_vectorX = _positionBefore.x - _MainSkul->getPlayerPosition().x;
		_MainSkul->setImagePositionX(_MainSkul->getImagePosition().x + _vectorX);
		_MainSkul->setPlayerPositionX(_positionBefore.x);

	}

	if (_positionBefore.y == _MainSkul->getPlayerPosition().y) {}
	else if (_MainSkul->getPlayerPosition().y > _MainSkul->getImagePosition().y + (WINSIZEY / 2)) { _MainSkul->setImagePositionY(0); }
	else if (_MainSkul->getPlayerPosition().y < _MainSkul->getImagePosition().y - bgImg->getHeight() + (3 * (WINSIZEY / 2))) { _MainSkul->setImagePositionY(bgImg->getHeight() - WINSIZEY); }
	else
	{
		_vectorY = _positionBefore.y - _MainSkul->getPlayerPosition().y;
		_MainSkul->setImagePositionY(_MainSkul->getImagePosition().y + _vectorY);
		_MainSkul->setPlayerPositionY(_positionBefore.y);

	}
}

void Player::changeSkul()
{
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		if (_vSkul.size() <= 1) {}
		else
		{
			if (_currentSkul == _vSkul[0]->getItemName())
			{
				_currentSkul = _vSkul[1]->getItemName();

			}
			else if (_currentSkul == _vSkul[1]->getItemName())
			{
				_currentSkul = _vSkul[0]->getItemName();
				
			}
		}

		_MainSkul = new hunter;
		_MainSkul->init();
	}
}