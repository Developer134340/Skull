#include "stdafx.h"
#include "object.h"

HRESULT object::init(string key, POINT position)
{
	_position = position;

	_key = key;
	_damaging = false;
	_changing = false;

	_damageCount = _count = _index = 0;

	int rndInt = RND->range(100);

	if (rndInt > 80 && rndInt <= 100)
	{
		_potionDrop = false;
	}
	else
	{
		_potionDrop = true;
		if (rndInt > 0 && rndInt <= 50)
		{
			_potionKey = S;
		}
		else if (rndInt > 50 && rndInt <= 70)
		{
			_potionKey = M;
		}
		else if (rndInt > 30 && rndInt <= 80)
		{
			_potionKey = L;
		}
	}

	if (key == "TURRET")
	{
		_objectImg = IMAGEMANAGER->findImage("TURRET");
		_hp = 20;
		_state = NORMAL;
	}
	else if (key == "WOODEN_CART_A")
	{
		_objectImg = IMAGEMANAGER->findImage("WOODEN_CART_A");
		_hp = 6;
		_state = ATTACKED;
	}
	else if (key == "WOODEN_CART_B")
	{
		_objectImg = IMAGEMANAGER->findImage("WOODEN_CART_B");
		_hp = 6;
		_state = ATTACKED;
	}
	else if (key == "WOODEN_CART_C")
	{
		_objectImg = IMAGEMANAGER->findImage("WOODEN_CART_C");
		_hp = 18;
		_state = ATTACKED;
	}
	else if (key == "TENT_A")
	{
		_objectImg = IMAGEMANAGER->findImage("TENT_A");
		_hp = 8;
		_state = ATTACKED;
	}
	else if (key == "TENT_B")
	{
		_objectImg = IMAGEMANAGER->findImage("TENT_B");
		_hp = 18;
		_state = NORMAL;
	}
	else if (key == "TENT_C")
	{
		_objectImg = IMAGEMANAGER->findImage("TENT_C");
		_hp = 18;
		_state = NORMAL;
	}
	else if (key == "TENT_D")
	{
		_objectImg = IMAGEMANAGER->findImage("TENT_D");
		_hp = 18;
		_state = NORMAL;
	}
	else if (key == "WOODEN_BOX")
	{
		_objectImg = IMAGEMANAGER->findImage("WOODEN_BOX");
		_hp = 6;
		_state = ATTACKED;
	}
	else if (key == "FENCE_A")
	{
		_objectImg = IMAGEMANAGER->findImage("FENCE_A");
		_hp = 6;
		_state = ATTACKED;
	}
	else if (key == "FENCE_B")
	{
		_objectImg = IMAGEMANAGER->findImage("FENCE_B");
		_hp = 6;
		_state = ATTACKED;
	}
	else if (key == "FLAG_A")
	{
		_objectImg = IMAGEMANAGER->findImage("FLAG_A");
		_hp = 6;
		_state = ATTACKED;
	}
	else if (key == "FLAG_B")
	{
		_objectImg = IMAGEMANAGER->findImage("FLAG_B");
		_hp = 6;
		_state = ATTACKED;
	}
	else if (key == "CAULDRON")
	{
		_objectImg = IMAGEMANAGER->findImage("CAULDRON");
		_hp = 6;
		_state = ATTACKED;
	}
	else if (key == "CAGE_FRONT")
	{
		_objectImg = IMAGEMANAGER->findImage("CAGE_FRONT");
		_hp = 20;
		_state = ATTACKED;
	}
	else if (key == "CAGE_BACK")
	{
		_objectImg = IMAGEMANAGER->findImage("CAGE_BACK");
		_hp = 20;
		_state = ATTACKED;
	}


	return S_OK;
}

void object::release()
{
}

void object::update(POINT imagePosition)
{
	_imagePosition = imagePosition;

	_rc = RectMake(_position.x + imagePosition.x, _position.y + imagePosition.y - _objectImg->getFrameHeight(), _objectImg->getFrameWidth(), _objectImg->getFrameHeight());

	_count++;
	_objectImg->setFrameY(0);

	if (_state == CRUSHED)
	{
		_changing = false;
		_damaging = false;
	}

	if (_damaging == true)
	{
		if (_count - _damageCount < 15)
		{
			_changing = true;
		}
		else
		{
			_changing = false;
		}

		if (_count - _damageCount > 30)
		{
			_damaging = false;
		}
	}

	if (_key == "TURRET")
	{
		if (_changing == false && _hp < 10 && _hp > 0)
		{
			_state = ATTACKED;
		}
		else if (_changing == false && _hp <= 0)
		{
			_state = CRUSHED;
			_hp = 0;
		}
		else if (_changing == false && _hp >= 10)
		{
			_state = NORMAL;
		}
		else if (_changing == true && _hp >= 10)
		{
			_state = ATTACKING;
		}
		else if (_changing == true && _hp < 10 && _hp > 0)
		{
			_state = CRUSHING;
		}

		//-----------------------------------

		if (_state == ATTACKED)
		{
			_index = 7;
		}
		else if (_state == CRUSHED)
		{
			_index = 8;

		}
		else if (_state == ATTACKING)
		{
			_index = 9;
		}
		else if (_state == CRUSHING)
		{
			_index = 10;
		}
		else if (_state == NORMAL)
		{
			if (_count % 10 == 0)
			{
				_index++;
				if (_index > 6)
				{
					_index = 0;
				}
			}
		}
		_objectImg->setFrameX(_index);
	}

	else if (_key == "WOODEN_CART_A" || _key == "WOODEN_CART_B" || _key == "WOODEN_BOX" || _key == "CAULDRON" || _key == "FENCE_A" || _key == "FENCE_B" || _key == "TENT_A")
	{

		if (_changing == false && _hp > 0)
		{
			_state = ATTACKED;
		}
		else if (_changing == false && _hp <= 0)
		{
			_state = CRUSHED;
			_hp = 0;
		}
		else if (_changing == true)
		{
			_state = CRUSHING;
		}

		if (_state == ATTACKED)
		{
			_index = 0;
		}
		else if (_state == CRUSHING)
		{
			_index = 2;
		}
		else if (_state == CRUSHED)
		{
			_index = 1;
		}
		_objectImg->setFrameX(_index);
	}

	else if (_key == "CAGE_FRONT" || _key == "CAGE_BACK")
	{
		_potionDrop = false;

		if (_changing == false && _hp > 0)
		{
			_state = ATTACKED;
		}
		else if (_changing == false && _hp <= 0)
		{
			_state = CRUSHED;
			_hp = 0;
		}
		else if (_changing == true)
		{
			_state = CRUSHING;
		}

		if (_state == ATTACKED)
		{
			_index = 0;
		}
		else if (_state == CRUSHING)
		{
			_index = 2;
		}
		else if (_state == CRUSHED)
		{
			_index = 1;
		}
		_objectImg->setFrameX(_index);
	}


	else if (_key == "TENT_B" || _key == "TENT_C" || _key == "TENT_D" || _key == "WOODEN_CART_C")
	{
		if (_changing == false && _hp < 10 && _hp > 0)
		{
			_state = ATTACKED;
		}
		else if (_changing == false && _hp <= 0)
		{
			_state = CRUSHED;
			_hp = 0;
		}
		else if (_changing == false && _hp >= 10)
		{
			_state = NORMAL;
		}
		else if (_changing == true && _hp >= 10)
		{
			_state = ATTACKING;
		}
		else if (_changing == true && _hp < 10 && _hp > 0)
		{
			_state = CRUSHING;
		}

		//-----------------------------------

		if (_state == ATTACKED)
		{
			_index = 1;
		}
		else if (_state == CRUSHED)
		{
			_index = 2;

		}
		else if (_state == ATTACKING)
		{
			_index = 3;
		}
		else if (_state == CRUSHING)
		{
			_index = 4;
		}
		else if (_state == NORMAL)
		{
			_index = 0;
		}
		_objectImg->setFrameX(_index);
	}


	else if (_key == "FLAG_A")
	{

		if (_changing == false && _hp > 0)
		{
			_state = ATTACKED;
		}
		else if (_changing == false && _hp <= 0)
		{
			_state = CRUSHED;
			_hp = 0;
		}
		else if (_changing == true)
		{
			_state = CRUSHING;
		}

		if (_state == ATTACKED)
		{
			if (_count % 10 == 0)
			{
				_index++;
				if (_index > 5)
				{
					_index = 0;
				}
				_objectImg->setFrameX(_index);
			}
		}
		else if (_state == CRUSHING)
		{
			_index = 7;
		}
		else if (_state == CRUSHED)
		{
			_index = 6;
		}
		_objectImg->setFrameX(_index);
	}


	else if (_key == "FLAG_B")
	{

		if (_changing == false && _hp > 0)
		{
			_state = ATTACKED;
		}
		else if (_changing == false && _hp <= 0)
		{
			_state = CRUSHED;
			_hp = 0;
		}
		else if (_changing == true)
		{
			_state = CRUSHING;
		}

		if (_state == ATTACKED)
		{
			if (_count % 10 == 0)
			{
				_index++;
				if (_index > 6)
				{
					_index = 0;
				}
				_objectImg->setFrameX(_index);
			}
		}
		else if (_state == CRUSHING)
		{
			_index = 8;
		}
		else if (_state == CRUSHED)
		{
			_index = 7;
		}
		_objectImg->setFrameX(_index);

	}
}

void object::render()
{
	_objectImg->frameRender(getMemDC(), _rc.left, _rc.top);

	if (_damaging == true)
	{
		for (int i = 0; i < _vSplinter.size(); i++)
		{
			HPEN myPen = CreatePen(PS_NULL, 0, RGB(255, 255, 255));
			HGDIOBJ oldPen = SelectObject(getMemDC(), myPen);
			Rectangle(getMemDC(), _vSplinter[i].rc);
			SelectObject(getMemDC(), oldPen);
			DeleteObject(myPen);
		}
	}


}

void object::Scattering(int k)
{
	if (k == 0)
	{
		for (int i = 0; i < _vSplinter.size(); i++)
		{
			_vSplinter[i].gravity += 0.4;
		}

		for (int i = 0; i < _vSplinter.size(); i++)
		{
			_vSplinter[i].exRc.left += 7 * cosf(_vSplinter[i].angle);
			_vSplinter[i].exRc.top -= 7 * sinf(_vSplinter[i].angle);
			_vSplinter[i].exRc.top += _vSplinter[i].gravity;
//			_vSplinter[i].exRc.right = _vSplinter[i].exRc.left + 3;
//			_vSplinter[i].exRc.bottom = _vSplinter[i].exRc.top + 3;
		}
	}
	else   //플레이어가 오른쪽에 있을 때
	{
		for (int i = 0; i < _vSplinter.size(); i++)
		{
			_vSplinter[i].gravity += 0.4;
		}

		for (int i = 0; i < _vSplinter.size(); i++)
		{
			_vSplinter[i].exRc.left -= 7 * cosf(_vSplinter[i].angle);
			_vSplinter[i].exRc.top -= 7 * sinf(_vSplinter[i].angle);
			_vSplinter[i].exRc.top += _vSplinter[i].gravity;
//			_vSplinter[i].exRc.right = _vSplinter[i].exRc.left + 3;
//			_vSplinter[i].exRc.bottom = _vSplinter[i].exRc.top + 3;
		}
	}

	for (int i = 0; i < _vSplinter.size(); i++)
	{
		_vSplinter[i].rc.left = _vSplinter[i].exRc.left + _imagePosition.x - _exImagePosition.x;
		_vSplinter[i].rc.top = _vSplinter[i].exRc.top + _imagePosition.y - _exImagePosition.y;
		_vSplinter[i].rc.right = _vSplinter[i].rc.left + 3;
		_vSplinter[i].rc.bottom = _vSplinter[i].rc.top + 3;
	}
	
}

void object::crashObject(RECT playerRc, int playerAtk, int playerState)
{
	if (playerAtk != 0)
	{
		RECT temp;

		if (IntersectRect(&temp, &playerRc, &_rc))
		{
			if (_damaging == false)
			{
				if (_state != CRUSHED)
				{
					_damaging = true;
					_damageCount = _count;
					_hp -= playerAtk;
					_exImagePosition = _imagePosition;

					for (int j = 0; j < 30; j++)
					{
						tagSplinter temp;
						temp.angle = RND->range(39, 157) / 100.0f;
						temp.gravity = 0.1;
						temp.height = _rc.top + RND->range(0, (_rc.bottom - _rc.top) / 2);
						temp.rc = RectMake((_rc.left + (_rc.right - _rc.left) / 2), temp.height, 3, 3);
						temp.exRc = RectMake((_rc.left + (_rc.right - _rc.left) / 2), temp.height, 3, 3);
						_vSplinter.push_back(temp);
					}
				}
			}
		}

		if (_damaging == true)
		{
			this->Scattering(playerState);
		}
	}
}