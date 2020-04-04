#include "stdafx.h"
#include "userInt.h"

HRESULT userInt::init()
{
	_hp = 100;
	_tapOn = false;
	_f1On = false;
	_currentSkul = "����";
	_index = 0;

	tabSkul[0] = RectMake(340, 156, 52, 52);
	tabSkul[1] = RectMake(424, 156, 52, 52);
	tabEssence = RectMake(382, 270, 52, 52);
	tabItem[0] = RectMake(298, 384, 52, 52);
	tabItem[1] = RectMake(382, 384, 52, 52);
	tabItem[2] = RectMake(466, 384, 52, 52);
	tabItem[3] = RectMake(298, 448, 52, 52);
	tabItem[4] = RectMake(382, 448, 52, 52);
	tabItem[5] = RectMake(466, 448, 52, 52);

	textRc[0] = RectMake(897, 115, 100, 50);
	textRc[1] = RectMake(950, 155, 150, 30);
	textRc[2] = RectMake(795, 155, 100, 30);
	textRc[3] = RectMake(614, 295, 487, 50);
	

	return S_OK;
}

void userInt::release()
{
}

void userInt::update(string currentSkul, int hp, int maxHp, vector<itemBase*> vSkul, vector<itemBase*> vItem, vector<essenceBase*> vEssence)
{
	_currentSkul = currentSkul;
	_vSkul = vSkul;
	_vItem = vItem;
	_vEssence = vEssence;

	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		_index--;
		if (_index < 0)
		{
			_index = 0;
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		_index++;
		if (_index > 8)
		{
			_index = 8;
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		_index++;
		if (_index > 8)
		{
			_index = 8;
		}
	}

	

	if (KEYMANAGER->isOnceKeyDown(VK_TAB))
	{
		if (!_tapOn)
		{
			_tapOn = true;
		}
		else
		{
			_tapOn = false;
		}
		
	}

	_hp = (int)(143 * hp / maxHp);

	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		if (!_f1On)
		{
			_f1On = true;
		}
		else
		{
			_f1On = false;
		}

	}
}

void userInt::render()
{
	IMAGEMANAGER->findImage("����")->render(getMemDC(), 20, WINSIZEY - 130);

	for (int i = 0; i < _hp; i++)
	{
		IMAGEMANAGER->findImage("ü�¹�")->render(getMemDC(), 90+(i*2), WINSIZEY - 50);
	}
	IMAGEMANAGER->findImage("����������")->render(getMemDC(), 20, WINSIZEY - 130);


	//������ ���� �� ��ų
	if (_currentSkul== "����")
	{
		IMAGEMANAGER->findImage("�⺻����")->render(getMemDC(), 25, WINSIZEY - 125);
		IMAGEMANAGER->findImage("�⺻���ý�ų")->render(getMemDC(), 135, WINSIZEY - 112);	
	}
	else if (_currentSkul == "ġ��")
	{
		IMAGEMANAGER->findImage("ġ������")->render(getMemDC(), 25, WINSIZEY - 125);
		IMAGEMANAGER->findImage("ġ�����ý�ų1")->render(getMemDC(), 135, WINSIZEY - 112);
		IMAGEMANAGER->findImage("ġ�����ý�ų2")->render(getMemDC(), 195, WINSIZEY - 112);
	}
	else if (_currentSkul == "����")
	{
		IMAGEMANAGER->findImage("���ͽ���")->render(getMemDC(), 25, WINSIZEY - 125);
		IMAGEMANAGER->findImage("���ͽ��ý�ų2")->render(getMemDC(), 135, WINSIZEY - 112);
	}
	else if (_currentSkul == "��ũ�ȶ��")
	{
		IMAGEMANAGER->findImage("��ũ�ȶ����")->render(getMemDC(), 25, WINSIZEY - 125);
		IMAGEMANAGER->findImage("��ũ�ȶ���ý�ų1")->render(getMemDC(), 135, WINSIZEY - 112);
		IMAGEMANAGER->findImage("��ũ�ȶ���ý�ų2")->render(getMemDC(), 195, WINSIZEY - 112);
	}
	else if (_currentSkul == "�׸�����")
	{
		IMAGEMANAGER->findImage("���۽���")->render(getMemDC(), 25, WINSIZEY - 125);
		IMAGEMANAGER->findImage("���۽��ý�ų1")->render(getMemDC(), 135, WINSIZEY - 112);
		IMAGEMANAGER->findImage("���۽��ý�ų2")->render(getMemDC(), 195, WINSIZEY - 112);
	}

	if (_vSkul.size() == 2)
	{	
		if (_currentSkul == _vSkul[0]->getItemName())
		{
			_vSkul[1]->getSkulProfileImage()->scaleRender(getMemDC(),9, WINSIZEY - 70, 0.6f);
		}
		else if (_currentSkul == _vSkul[1]->getItemName())
		{
			_vSkul[0]->getSkulProfileImage()->scaleRender(getMemDC(),9, WINSIZEY - 70, 0.6f);
		}
		IMAGEMANAGER->findImage("SPACE")->render(getMemDC(), 6, WINSIZEY - 24);

	}

	//----------------������ ����
	if (_vEssence.size() == 0) {}
	else if (_vEssence[0]->getEssenceName() == "ȭ���� ����")
	{
		IMAGEMANAGER->findImage("ȭ����������ų")->render(getMemDC(), 268, WINSIZEY - 113);
	}
	else if (_vEssence[0]->getEssenceName() == "���̾ƽ��� ����")
	{
		IMAGEMANAGER->findImage("���̾ƽ���������ų")->render(getMemDC(), 268, WINSIZEY - 113);
	}
	

	if (_tapOn)
	{
		IMAGEMANAGER->findImage("�κ��丮â")->render(getMemDC(), 110, 50);

		if (KEYMANAGER->isToggleKey('T'))
		{
			Rectangle(getMemDC(), tabSkul[0]);
			Rectangle(getMemDC(), tabSkul[1]);
			Rectangle(getMemDC(), tabEssence);

			for (int i = 0; i < 6; i++)	
			{
				Rectangle(getMemDC(), tabItem[i]);
			}

			for (int i = 0; i < 4; i++)
			{
				Rectangle(getMemDC(), textRc[i]);
			}
		}

		switch (_index)
		{
		case 0:
			IMAGEMANAGER->findImage("�����ۼ���2")->render(getMemDC(), tabSkul[0].left - 2, tabSkul[0].top - 2);

			break;
		case 1:
			IMAGEMANAGER->findImage("�����ۼ���2")->render(getMemDC(), tabSkul[1].left - 2, tabSkul[0].top - 2);
			break;
		case 2:
			IMAGEMANAGER->findImage("�����ۼ���2")->render(getMemDC(), tabEssence.left - 2, tabEssence.top - 2);
			break;
		case 3:
			IMAGEMANAGER->findImage("�����ۼ���2")->render(getMemDC(), tabItem[0].left - 2, tabItem[0].top - 2);
			break;
		case 4:
			IMAGEMANAGER->findImage("�����ۼ���2")->render(getMemDC(), tabItem[1].left - 2, tabItem[1].top - 2);
			break;
		case 5:
			IMAGEMANAGER->findImage("�����ۼ���2")->render(getMemDC(), tabItem[2].left - 2, tabItem[2].top - 2);
			break;
		case 6:
			IMAGEMANAGER->findImage("�����ۼ���2")->render(getMemDC(), tabItem[3].left - 2, tabItem[3].top - 2);
			break;
		case 7:
			IMAGEMANAGER->findImage("�����ۼ���2")->render(getMemDC(), tabItem[4].left - 2, tabItem[4].top - 2);
			break;
		case 8:
			IMAGEMANAGER->findImage("�����ۼ���2")->render(getMemDC(), tabItem[5].left - 2, tabItem[5].top - 2);
			break;
		}

		//------------------------����--------------------

		if (_vEssence.size() == 0) {}
		else
		{
			_vEssence[0]->getEssenceImg()->scaleRender(getMemDC(), 386, 275, 0.8f);
		}
		
		//------------------������------------------------

		if (_vItem.size() == 0) {}
		else
		{
			for (int i = 0; i < _vItem.size(); i++)
			{
				_vItem[i]->getItemInvenImage()->render(getMemDC(), tabItem[i].left, tabItem[i].top);
			}

		}

		//------------------------����-------------------

		for (int i = 0; i < _vSkul.size(); i++)
		{
			_vSkul[i]->getItemInvenImage()->render(getMemDC(), tabSkul[i].left, tabSkul[i].top);
		}	


		this->changeFont(24, RGB(93, 73, 56));

		switch (_index)
		{
		case 0:
			IMAGEMANAGER->findImage("�����ۼ���")->render(getMemDC(), tabSkul[0].left - 7, tabSkul[0].top - 7);
			_vSkul[0]->getItemProfileImage()->render(getMemDC(), 609, 131);
			sprintf(str, "����");
			DrawText(getMemDC(), str, -1, &textRc[0], DT_CENTER | DT_SINGLELINE);
			DrawText(getMemDC(), _vSkul[0]->getItemName(), -1, &textRc[1], DT_RIGHT | DT_SINGLELINE);
			DrawText(getMemDC(), _vSkul[0]->getItemGrade(), -1, &textRc[2], DT_LEFT | DT_SINGLELINE);
			DrawText(getMemDC(), _vSkul[0]->getItemIntroduction(), -1, &textRc[3], DT_LEFT | DT_WORDBREAK);
			break;
		case 1:
			IMAGEMANAGER->findImage("�����ۼ���")->render(getMemDC(), tabSkul[1].left - 7, tabSkul[0].top - 7);
			if (_vSkul.size() == 1) {}
			else
			{
				_vSkul[1]->getItemProfileImage()->render(getMemDC(), 609, 131);
				sprintf(str, "����");
				DrawText(getMemDC(), str, -1, &textRc[0], DT_CENTER | DT_SINGLELINE);
				DrawText(getMemDC(), _vSkul[1]->getItemName(), -1, &textRc[1], DT_RIGHT | DT_SINGLELINE);
				DrawText(getMemDC(), _vSkul[1]->getItemGrade(), -1, &textRc[2], DT_LEFT | DT_SINGLELINE);
				DrawText(getMemDC(), _vSkul[1]->getItemIntroduction(), -1, &textRc[3], DT_LEFT | DT_WORDBREAK);
			}
			break;
		case 2:
			IMAGEMANAGER->findImage("�����ۼ���")->render(getMemDC(), tabEssence.left - 7, tabEssence.top - 7);
			if (_vEssence.size() == 0) {}
			else
			{
				_vEssence[0]->getEssenceProfileImage()->render(getMemDC(), 609, 131);
				sprintf(str, "����");
				DrawText(getMemDC(), str, -1, &textRc[0], DT_CENTER | DT_SINGLELINE);
				DrawText(getMemDC(), _vEssence[0]->getEssenceName(), -1, &textRc[1], DT_RIGHT | DT_SINGLELINE);
				DrawText(getMemDC(), _vEssence[0]->getEssenceGrade(), -1, &textRc[2], DT_LEFT | DT_SINGLELINE);
				DrawText(getMemDC(), _vEssence[0]->getEssenceIntroduction(), -1, &textRc[3], DT_LEFT | DT_WORDBREAK);
			}
			break;
		case 3:
			IMAGEMANAGER->findImage("�����ۼ���")->render(getMemDC(), tabItem[0].left - 7, tabItem[0].top - 7);
			if (_vItem.size() < 1) {}
			else
			{
				_vItem[0]->getItemImage()->scaleRender(getMemDC(), 642, 150, 2.0f);
				sprintf(str, "������");
				DrawText(getMemDC(), str, -1, &textRc[0], DT_CENTER | DT_SINGLELINE);
				DrawText(getMemDC(), _vItem[0]->getItemName(), -1, &textRc[1], DT_RIGHT | DT_SINGLELINE);
				DrawText(getMemDC(), _vItem[0]->getItemGrade(), -1, &textRc[2], DT_LEFT | DT_SINGLELINE);
				DrawText(getMemDC(), _vItem[0]->getItemIntroduction(), -1, &textRc[3], DT_LEFT | DT_WORDBREAK);
			}
			break;
		case 4:
			IMAGEMANAGER->findImage("�����ۼ���")->render(getMemDC(), tabItem[1].left - 7, tabItem[1].top - 7);
			if (_vItem.size() < 2) {}
			else
			{
				_vItem[1]->getItemImage()->scaleRender(getMemDC(), 642, 150, 2.0f);
				sprintf(str, "������");
				DrawText(getMemDC(), str, -1, &textRc[0], DT_CENTER | DT_SINGLELINE);
				DrawText(getMemDC(), _vItem[1]->getItemName(), -1, &textRc[1], DT_RIGHT | DT_SINGLELINE);
				DrawText(getMemDC(), _vItem[1]->getItemGrade(), -1, &textRc[2], DT_LEFT | DT_SINGLELINE);
				DrawText(getMemDC(), _vItem[1]->getItemIntroduction(), -1, &textRc[3], DT_LEFT | DT_WORDBREAK);
			}
			break;
		case 5:
			IMAGEMANAGER->findImage("�����ۼ���")->render(getMemDC(), tabItem[2].left - 7, tabItem[2].top - 7);
			if (_vItem.size() < 3) {}
			else
			{
				_vItem[2]->getItemImage()->scaleRender(getMemDC(), 642, 150, 2.0f);
				sprintf(str, "������");
				DrawText(getMemDC(), str, -1, &textRc[0], DT_CENTER | DT_SINGLELINE);
				DrawText(getMemDC(), _vItem[2]->getItemName(), -1, &textRc[1], DT_RIGHT | DT_SINGLELINE);
				DrawText(getMemDC(), _vItem[2]->getItemGrade(), -1, &textRc[2], DT_LEFT | DT_SINGLELINE);
				DrawText(getMemDC(), _vItem[2]->getItemIntroduction(), -1, &textRc[3], DT_LEFT | DT_WORDBREAK);
			}
			break;
		case 6:
			IMAGEMANAGER->findImage("�����ۼ���")->render(getMemDC(), tabItem[3].left - 7, tabItem[3].top - 7);
			if (_vItem.size() < 4) {}
			else
			{
				_vItem[3]->getItemImage()->scaleRender(getMemDC(), 642, 150, 2.0f);
				sprintf(str, "������");
				DrawText(getMemDC(), str, -1, &textRc[0], DT_CENTER | DT_SINGLELINE);
				DrawText(getMemDC(), _vItem[3]->getItemName(), -1, &textRc[1], DT_RIGHT | DT_SINGLELINE);
				DrawText(getMemDC(), _vItem[3]->getItemGrade(), -1, &textRc[2], DT_LEFT | DT_SINGLELINE);
				DrawText(getMemDC(), _vItem[3]->getItemIntroduction(), -1, &textRc[3], DT_LEFT | DT_WORDBREAK);
			}
			break;
		case 7:
			IMAGEMANAGER->findImage("�����ۼ���")->render(getMemDC(), tabItem[4].left - 7, tabItem[4].top - 7);
			if (_vItem.size() < 5) {}
			else
			{
				_vItem[4]->getItemImage()->scaleRender(getMemDC(), 642, 150, 2.0f);
				sprintf(str, "������");
				DrawText(getMemDC(), str, -1, &textRc[0], DT_CENTER | DT_SINGLELINE);
				DrawText(getMemDC(), _vItem[4]->getItemName(), -1, &textRc[1], DT_RIGHT | DT_SINGLELINE);
				DrawText(getMemDC(), _vItem[4]->getItemGrade(), -1, &textRc[2], DT_LEFT | DT_SINGLELINE);
				DrawText(getMemDC(), _vItem[4]->getItemIntroduction(), -1, &textRc[3], DT_LEFT | DT_WORDBREAK);
			}
			break;
		case 8:
			IMAGEMANAGER->findImage("�����ۼ���")->render(getMemDC(), tabItem[5].left - 7, tabItem[5].top - 7);
			if (_vItem.size() < 6) {}
			else
			{
				_vItem[5]->getItemImage()->scaleRender(getMemDC(), 642, 150, 2.0f);
				sprintf(str, "������");
				DrawText(getMemDC(), str, -1, &textRc[0], DT_CENTER | DT_SINGLELINE);
				DrawText(getMemDC(), _vItem[5]->getItemName(), -1, &textRc[1], DT_RIGHT | DT_SINGLELINE);
				DrawText(getMemDC(), _vItem[5]->getItemGrade(), -1, &textRc[2], DT_LEFT | DT_SINGLELINE);
				DrawText(getMemDC(), _vItem[5]->getItemIntroduction(), -1, &textRc[3], DT_LEFT | DT_WORDBREAK);
			}
			break;
		}
	}
}
