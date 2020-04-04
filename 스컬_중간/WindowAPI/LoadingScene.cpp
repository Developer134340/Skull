#include "stdafx.h"
#include "LoadingScene.h"

HRESULT LoadingScene::init()
{
	_loading = new loading;
	_loading->init();

	IMAGEMANAGER->addFrameImage("LoadingSkull", "IMAGE/Loading/LoadingSkull.bmp", 720, 80, 8, 1);

	_frameCount = 0;

	this->loadingImage();
	this->loadingSound();

	return S_OK;
}

void LoadingScene::release()
{
	_loading->release();
	SAFE_DELETE(_loading);
}

void LoadingScene::update()
{
	_loading->update();

	_frameCount++;
	if (_frameCount == 48)		_frameCount = 0;
	IMAGEMANAGER->findImage("LoadingSkull")->setFrameX(_frameCount / 6);

	if (_loading->loadingDone())
	{
		SCENEMANAGER->loadScene("Title");
	}
}

void LoadingScene::render()
{
	_loading->render();

	IMAGEMANAGER->findImage("LoadingSkull")->frameRender(getMemDC(), WINSIZEX - 150, WINSIZEY - 150);
	TextOut(getMemDC(), WINSIZEX - 155, WINSIZEY - 70, "�ҷ����� ��", sizeof("�ҷ����� ��"));
}

void LoadingScene::loadingImage()
{
	_loading->loadImage("BLACK", WINSIZEX, WINSIZEY);

	_loading->loadImage("TITLE_BG", "IMAGE/Title/Background.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("TITLE_BACK_CASTLE", "IMAGE/Title/BackCastle.bmp", -(WINSIZEX / 2), WINSIZEY - 267, WINSIZEX, 267, true, RGB(255, 0, 255));
	_loading->loadImage("TITLE_CLOUD", "IMAGE/Title/Cloud.bmp", 2560, 720, true, RGB(255, 0, 255));
	_loading->loadImage("TITLE_FRONT_CASTLE", "IMAGE/Title/Castle.bmp", -(WINSIZEX / 2), 0, WINSIZEY, WINSIZEY, true, RGB(255, 0, 255));
	_loading->loadImage("TITLE_LOGO", "IMAGE/Title/TitleLogo.bmp", 320, 160, true, RGB(255, 0, 255));
	_loading->loadImage("TITLE_GROUND", "IMAGE/Title/Ground.bmp", -(WINSIZEX / 4), WINSIZEY - 173, 1280, 200, true, RGB(255, 0, 255));
	_loading->loadFrameImage("TITLE_SKUL", "IMAGE/Title/Skul.bmp", 642, 100, 6, 1, true, RGB(255, 0, 255));

	_loading->loadImage("OPENING_CASTLE_BACK", "IMAGE/Opening/Background_Castle_back.bmp", 3840, 700);
	_loading->loadImage("OPENING_CASTLE_MIDDLE", "IMAGE/Opening/Background_Castle_middle.bmp", 3840, 720, true, RGB(255, 0, 255));
	_loading->loadImage("OPENING_CASTLE_FRONT", "IMAGE/Opening/Background_Castle_front.bmp", 3840, 720, true, RGB(255, 0, 255));
	_loading->loadImage("OPENING_BROKEN_CASTLE_BACK", "IMAGE/Opening/Background_Broken_Castle_back.bmp", 3840, 700);
	_loading->loadImage("OPENING_BROKEN_CASTLE_MIDDLE", "IMAGE/Opening/Background_Broken_Castle_middle.bmp", 3840, 720, true, RGB(255, 0, 255));
	_loading->loadImage("OPENING_BROKEN_CASTLE_FRONT", "IMAGE/Opening/Background_Broken_Castle_front.bmp", 3840, 720, true, RGB(255, 0, 255));
	_loading->loadFrameImage("OPENING_OGRE", "IMAGE/Opening/Ogre.bmp", 1060, 375, 1200, 240, 5, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("OPENING_DRUID", "IMAGE/Opening/Druid.bmp", 950, 375, 800, 240, 5, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("OPENING_FOX", "IMAGE/Opening/Fox.bmp", 820, 415, 1000, 200, 5, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("OPENING_WITCH", "IMAGE/Opening/Witch.bmp", 600, 435, 840, 180, 6, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("OPENING_SKUL", "IMAGE/Opening/Skul.bmp", 720, 535, 400, 80, 4, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("OPENING_WARRIOR", "IMAGE/Opening/Warrior.bmp", 832, 100, 8, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("OPENING_GAURD", "IMAGE/Opening/Gaurd.bmp", 1760, 200, 8, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("OPENING_ARCHER", "IMAGE/Opening/Archer.bmp", 480, 100, 6, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("OPENING_EXPLOSION", "IMAGE/Opening/Explosion.bmp", 12320, 500, 22, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("OPENING_HERO", "IMAGE/Opening/Hero.bmp", WINSIZEX + 1500, 200, 1400, 200, 7, 1, true, RGB(255, 0, 255));

	_loading->loadFrameImage("FINGER_SKULL", "IMAGE/Tutorial/FingerSkull.bmp", 360, 90, 4, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("WEAPON_SKULL", "IMAGE/Tutorial/WeaponSkull.bmp", 720, 60, 6, 1, true, RGB(255, 0, 255));
	_loading->loadImage("NO_WEAPON_SKULL", "IMAGE/Tutorial/NoWeaponSkull.bmp", 120, 60, true, RGB(255, 0, 255));
	_loading->loadFrameImage("WEAPON_GET", "IMAGE/Tutorial/WeaponGet.bmp", 900, 70, 10, 1, true, RGB(255, 0, 255));

	_loading->loadImage("TUTORIAL_BG_BACK", "IMAGE/Tutorial/Background_Back.bmp", 1920, 1600, true, RGB(255, 0, 255));
	_loading->loadImage("TUTORIAL_BG_MIDDLE", "IMAGE/Tutorial/Background_Middle.bmp", 1920, 1600, true, RGB(255, 0, 255));
	_loading->loadImage("TUTORIAL_BG_FRONT", "IMAGE/Tutorial/Background_Front.bmp", 1920, 1600, true, RGB(255, 0, 255));
	_loading->loadImage("TUTORIAL_1_MAP", "IMAGE/Tutorial/Map_0-1.bmp", 3392, 1280, true, RGB(255, 0, 255));
	_loading->loadImage("TUTORIAL_1_MAP_PIXEL", "IMAGE/Tutorial/Map_0-1_Pixel.bmp", 3392, 1280);
	_loading->loadImage("TUTORIAL_2_MAP", "IMAGE/Tutorial/Map_0-2.bmp", 2752, 1280, true, RGB(255, 0, 255));
	_loading->loadImage("TUTORIAL_2_MAP_PIXEL", "IMAGE/Tutorial/Map_0-2_Pixel.bmp", 2752, 1280);
	_loading->loadImage("TUTORIAL_3_MAP", "IMAGE/Tutorial/Map_0-3.bmp", 2240, 1280, true, RGB(255, 0, 255));
	_loading->loadImage("TUTORIAL_3_MAP_PIXEL", "IMAGE/Tutorial/Map_0-3_Pixel.bmp", 2240, 1280);
	_loading->loadImage("TUTORIAL_4_MAP", "IMAGE/Tutorial/Map_0-4.bmp", 2752, 1280, true, RGB(255, 0, 255));
	_loading->loadImage("TUTORIAL_4_MAP_PIXEL", "IMAGE/Tutorial/Map_0-4_Pixel.bmp", 2752, 1280);
	_loading->loadImage("TUTORIAL_5_MAP", "IMAGE/Tutorial/Map_0-5.bmp", 2048, 1280, true, RGB(255, 0, 255));
	_loading->loadImage("TUTORIAL_5_MAP_PIXEL", "IMAGE/Tutorial/Map_0-5_Pixel.bmp", 2048, 1280);

	_loading->loadImage("START_BG_BACK", "IMAGE/Tutorial/Background_Back_2.bmp", 1920, 1280);
	_loading->loadImage("START_MAP", "IMAGE/Tutorial/Map_1-0.bmp", 1920, 1280, true, RGB(255, 0, 255));
	_loading->loadImage("START_MAP_PIXEL", "IMAGE/Tutorial/Map_1-0_Pixel.bmp", 1920, 1280, true, RGB(255, 0, 255));

	_loading->loadImage("FIELD_BG_BACK", "IMAGE/FieldMap/Background_Back.bmp", 1920, 1600, true, RGB(255, 0, 255));
	_loading->loadImage("FIELD_BG_MIDDLE", "IMAGE/FieldMap/Background_Middle.bmp", 1920, 1600, true, RGB(255, 0, 255));
	_loading->loadImage("FIELD_BG_FRONT", "IMAGE/FieldMap/Background_Front.bmp", 1920, 1600, true, RGB(255, 0, 255));
	_loading->loadImage("FIELD_1_MAP", "IMAGE/FieldMap/Map_1-1.bmp", 2496, 2368, true, RGB(255, 0, 255));
	_loading->loadImage("FIELD_1_MAP_PIXEL", "IMAGE/FieldMap/Map_1-1_Pixel.bmp", 2496, 2368);
	_loading->loadImage("FIELD_2_MAP", "IMAGE/FieldMap/Map_2-1.bmp", 3840, 1920, true, RGB(255, 0, 255));
	_loading->loadImage("FIELD_2_MAP_PIXEL", "IMAGE/FieldMap/Map_2-1_Pixel.bmp", 3840, 1920);

	_loading->loadImage("SHOP_MAP", "IMAGE/Shop/ShopMap.bmp", 1920, 1280, true, RGB(255, 0, 255));
	_loading->loadImage("SHOP_MAP_PIXEL", "IMAGE/Shop/ShopMapPixel.bmp", 1920, 1280);
	_loading->loadFrameImage("SHOP_NPC", "IMAGE/Shop/ShopNPC.bmp", 1350, 190, 5, 1, true, RGB(255, 0, 255));
	_loading->loadImage("ITEM_MAP", "IMAGE/ItemMap/ItemMap.bmp", 1856, 1280, true, RGB(255, 0, 255));
	_loading->loadImage("ITEM_MAP_PIXEL", "IMAGE/ItemMap/ItemMapPixel.bmp", 1856, 1280, true, RGB(255, 0, 255));
	_loading->loadImage("SKULL_MAP", "IMAGE/SkullMap/SkullMap.bmp", 1856, 1280, true, RGB(255, 0, 255));
	_loading->loadImage("SKULL_MAP_PIXEL", "IMAGE/SkullMap/SkullMapPixel.bmp", 1856, 1280, true, RGB(255, 0, 255));

	_loading->loadImage("BOSS_BG_BACK", "IMAGE/BossMap/BossBackground_Back.bmp", 1800, 800, true, RGB(255, 0, 255));
	_loading->loadImage("BOSS_BG_FRONT", "IMAGE/BossMap/BossBackground_Front.bmp", 1800, 800, true, RGB(255, 0, 255));
	_loading->loadImage("BOSS_1_MAP", "IMAGE/BossMap/BossMap_1.bmp", 1600, 1280, true, RGB(255, 0, 255));
	_loading->loadImage("BOSS_1_MAP_PIXEL", "IMAGE/BossMap/BossMap_1_Pixel.bmp", 1600, 1280);
	_loading->loadImage("BOSS_2_MAP", "IMAGE/BossMap/BossMap_2.bmp", 1280, 720, true, RGB(255, 0, 255));
	_loading->loadImage("BOSS_2_MAP_PIXEL", "IMAGE/BossMap/BossMap_2_Pixel.bmp", 1280, 720);

	_loading->loadFrameImage("�Ϲݻ���", "IMAGE/Object/����_�Ϲ�.bmp", 1080, 84, 9, 1);
	_loading->loadFrameImage("�������", "IMAGE/Object/����_����.bmp", 1431, 81, 9, 1);
	_loading->loadFrameImage("����ũ����", "IMAGE/Object/����_����ũ.bmp", 1647, 96, 9, 1);
	_loading->loadFrameImage("������������", "IMAGE/Object/����_��������.bmp", 1881, 120, 9, 1);

	_loading->loadImage("ITEM_NAME", "IMAGE/Item/ItemName.bmp", 170, 50, true, RGB(255, 0, 255));
	_loading->loadImage("ȭ���", "IMAGE/Item/ȭ���.bmp", 54, 54, true, RGB(255, 0, 255));
	_loading->loadImage("���ٷ���������", "IMAGE/Item/���ٷ���������.bmp", 54, 54, true, RGB(255, 0, 255));
	_loading->loadImage("��ī�罺�Ǵܰ�", "IMAGE/Item/��ī�罺�Ǵܰ�.bmp", 54, 54, true, RGB(255, 0, 255));
	_loading->loadImage("������Į���°�", "IMAGE/Item/������Į���°�.bmp", 54, 54, true, RGB(255, 0, 255));
	_loading->loadImage("���������尩", "IMAGE/Item/���������尩.bmp", 54, 54, true, RGB(255, 0, 255));
	_loading->loadImage("���ǵ��ǳ���", "IMAGE/Item/���ǵ��ǳ���.bmp", 54, 54, true, RGB(255, 0, 255));
	_loading->loadImage("�ڰ����ǰ���", "IMAGE/Item/�ڰ����ǰ���.bmp", 54, 54, true, RGB(255, 0, 255));

	_loading->loadFrameImage("�����", "IMAGE/Object/�����ذ񹫴�.bmp", 1300, 80, 10, 1);
	_loading->loadFrameImage("����ũ����", "IMAGE/Object/����ũ�ذ񹫴�.bmp", 2520, 90, 10, 1);
	_loading->loadFrameImage("������������", "IMAGE/Object/���������ذ񹫴�.bmp", 3620, 222, 10, 1);

	_loading->loadImage("ȭ��������", "IMAGE/Essence/ȭ��������.bmp", 54, 54, true, RGB(255, 0, 255));
	_loading->loadImage("ȭ����������ų", "IMAGE/Essence/ȭ����������ų.bmp", 52, 52, true, RGB(255, 0, 255));
	_loading->loadFrameImage("�巡����", "IMAGE/Essence/�巡����.bmp", 3300, 540, 11, 2);
	_loading->loadFrameImage("�巡�����", "IMAGE/Essence/�����.bmp", 1395, 540, 5, 2);
	_loading->loadFrameImage("�巡���", "IMAGE/Essence/���.bmp", 21120, 540, 64, 2);
	_loading->loadFrameImage("�巡�����", "IMAGE/Essence/�����.bmp", 4066, 217, 19, 1);
	_loading->loadImage("���̾ƽ�������", "IMAGE/Essence/���̾ƽ�������.bmp", 54, 54, true, RGB(255, 0, 255));
	_loading->loadImage("���̾ƽ���������ų", "IMAGE/Essence/���̾ƽ���������ų.bmp", 52, 52, true, RGB(255, 0, 255));
	_loading->loadImage("���̾ƽ�����������", "IMAGE/Essence/���̾ƽ�����������.bmp", 33, 17, true, RGB(255, 0, 255));
	_loading->loadImage("���̾ƽ�����������2", "IMAGE/Essence/���̾ƽ�����������2.bmp", 33, 33, true, RGB(255, 0, 255));
	_loading->loadImage("���̾ƽ�����������3", "IMAGE/Essence/���̾ƽ�����������3.bmp", 33, 33, true, RGB(255, 0, 255));
	_loading->loadImage("���̾ƽ�����������4", "IMAGE/Essence/���̾ƽ�����������4.bmp", 33, 17, true, RGB(255, 0, 255));

	_loading->loadImage("�κ��丮â", "IMAGE/Item/�κ��丮.bmp", 1058, 626, true, RGB(255, 0, 255));
	_loading->loadImage("����", "IMAGE/Item/Player_Frame.bmp", 360, 112, true, RGB(255, 0, 255));
	_loading->loadImage("����������", "IMAGE/Item/Player_Frame_.bmp", 360, 112, true, RGB(255, 0, 255));
	_loading->loadImage("ü�¹�", "IMAGE/Item/healthBar.bmp", 2, 20);
	_loading->loadImage("�̴ϸ�������", "IMAGE/MiniMap/�̴ϸ�������.bmp", 214, 118, true, RGB(255, 0, 255));
	_loading->loadImage("�̴ϸʹ��", "IMAGE/MiniMap/�̴ϸʹ��.bmp", 214, 118, true, RGB(255, 0, 255));
	_loading->loadImage("MINI_TUTORIAL_1", "IMAGE/MiniMap/�̴ϸ�_Ʃ�丮�� 0 - 1.bmp", 206, 78, true, RGB(255, 0, 255));
	_loading->loadImage("MINI_TUTORIAL_2", "IMAGE/MiniMap/�̴ϸ�_Ʃ�丮�� 0 - 2.bmp", 206, 96, true, RGB(255, 0, 255));
	_loading->loadImage("MINI_TUTORIAL_3", "IMAGE/MiniMap/�̴ϸ�_Ʃ�丮�� 0 - 3.bmp", 193, 110, true, RGB(255, 0, 255));
	_loading->loadImage("MINI_TUTORIAL_4", "IMAGE/MiniMap/�̴ϸ�_Ʃ�丮�� 0 - 4.bmp", 206, 96, true, RGB(255, 0, 255));
	_loading->loadImage("MINI_TUTORIAL_5", "IMAGE/MiniMap/�̴ϸ�_Ʃ�丮�� 0 - 5.bmp", 176, 110, true, RGB(255, 0, 255));
	_loading->loadImage("MINI_FIELD_1", "IMAGE/MiniMap/�̴ϸ�_�����ʵ� 1 - 1.bmp", 116, 110, true, RGB(255, 0, 255));
	_loading->loadImage("MINI_FIELD_2", "IMAGE/MiniMap/�̴ϸ�_�����ʵ� 2 - 1.bmp", 206, 103, true, RGB(255, 0, 255));
	_loading->loadImage("MINI_SHOP", "IMAGE/MiniMap/�̴ϸ�_�����ʵ�.bmp", 165, 110, true, RGB(255, 0, 255));
	_loading->loadImage("MINI_ITEM", "IMAGE/MiniMap/�̴ϸ�_�������ʵ�.bmp", 160, 110, true, RGB(255, 0, 255));

	_loading->loadImage("�⺻����", "IMAGE/Item/Skul #6532.bmp", 90, 90, true, RGB(255, 0, 255));
	_loading->loadImage("�⺻���ý�ų", "IMAGE/Item/SkullThrowing.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->loadImage("�⺻����������", "IMAGE/Item/Skul #6402.bmp", 161, 145, true, RGB(255, 0, 255));
	_loading->loadImage("�κ��Ӹ�_����", "IMAGE/Item/�κ��Ӹ�_����.bmp", 52, 52, true, RGB(255, 0, 255));

	_loading->loadImage("ġ������", "IMAGE/Item/ChiefGuard #6319.bmp", 90, 90, true, RGB(255, 0, 255));
	_loading->loadImage("ġ�����ý�ų1", "IMAGE/Item/ġ��1.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->loadImage("ġ�����ý�ų2", "IMAGE/Item/ġ��2.bmp", 48, 48, true, RGB(255, 0, 255));

	_loading->loadImage("���ͽ���", "IMAGE/Item/Hunter #6347.bmp", 90, 90, true, RGB(255, 0, 255));
	_loading->loadImage("���ͽ��ý�ų1", "IMAGE/Item/����1.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->loadImage("���ͽ��ý�ų2", "IMAGE/Item/����2.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->loadImage("���ͽ���������", "IMAGE/Item/Hunter.bmp", 161, 145, true, RGB(255, 0, 255));
	_loading->loadImage("�κ��Ӹ�_����", "IMAGE/Item/�κ��Ӹ�_����.bmp", 52, 52, true, RGB(255, 0, 255));
	_loading->loadImage("�Ӹ�_����", "IMAGE/Item/�Ӹ�_����.bmp", 72, 64, true, RGB(255, 0, 255));

	_loading->loadImage("��ũ�ȶ����", "IMAGE/Item/DarkPaladin #6784.bmp", 90, 90, true, RGB(255, 0, 255));
	_loading->loadImage("��ũ�ȶ���ý�ų1", "IMAGE/Item/��ũ1.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->loadImage("��ũ�ȶ���ý�ų2", "IMAGE/Item/��ũ2.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->loadImage("��ũ�ȶ����������", "IMAGE/Item/DarkPaladin #6388.bmp", 161, 145, true, RGB(255, 0, 255));
	_loading->loadImage("�κ��Ӹ�_��ũ�ȶ��", "IMAGE/Item/�κ��Ӹ�_��ũ�ȶ��.bmp", 52, 52, true, RGB(255, 0, 255));
	_loading->loadImage("�Ӹ�_��ũ�ȶ��", "IMAGE/Item/�Ӹ�_��ũ�ȶ��.bmp", 72, 64, true, RGB(255, 0, 255));

	_loading->loadImage("���۽���", "IMAGE/Item/GrimReaper #6502.bmp", 90, 90, true, RGB(255, 0, 255));
	_loading->loadImage("���۽��ý�ų1", "IMAGE/Item/����1.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->loadImage("���۽��ý�ų2", "IMAGE/Item/����2.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->loadImage("���۽���������", "IMAGE/Item/GrimReaper #6396.bmp", 161, 145, true, RGB(255, 0, 255));
	_loading->loadImage("�κ��Ӹ�_����", "IMAGE/Item/�κ��Ӹ�_����.bmp", 52, 52, true, RGB(255, 0, 255));
	_loading->loadImage("�Ӹ�_����", "IMAGE/Item/�Ӹ�_����.bmp", 72, 64, true, RGB(255, 0, 255));

	_loading->loadImage("ȭ��������������", "IMAGE/Essence/ȭ��������.bmp", 161, 145, true, RGB(255, 0, 255));
	_loading->loadImage("���̾ƽ�������������", "IMAGE/Essence/���̾ƽ�������.bmp", 161, 145, true, RGB(255, 0, 255));

	_loading->loadImage("�����ۼ���", "IMAGE/Item/�����ۼ���.bmp", 66, 66, true, RGB(255, 0, 255));
	_loading->loadImage("�����ۼ���2", "IMAGE/Item/�����ۼ���2.bmp", 56, 56, true, RGB(255, 0, 255));

	_loading->loadFrameImage("����S", "IMAGE/Object/ü��ȸ��S.bmp", 252, 28, 9, 1);
	_loading->loadFrameImage("����M", "IMAGE/Object/ü��ȸ��M.bmp", 396, 44, 9, 1);
	_loading->loadFrameImage("����L", "IMAGE/Object/ü��ȸ��L.bmp", 576, 64, 9, 1);
	_loading->loadFrameImage("����XL", "IMAGE/Object/ü��ȸ��XL.bmp", 1080, 120, 9, 1);

	_loading->loadImage("F_KEY", "IMAGE/Object/F_Key.bmp", 30, 28, true, RGB(255, 0, 255));
	_loading->loadImage("SPACE", "IMAGE/Object/SPACE.bmp", 60, 22, true, RGB(255, 0, 255));
	_loading->loadFrameImage("NOTING_GATE", "IMAGE/Object/NotingGate.bmp", 1120, 300, 8, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("NOMAL_GATE", "IMAGE/Object/NomalGate.bmp", 2800, 256, 8, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("SKULL_GATE", "IMAGE/Object/SkullGate.bmp", 2800, 256, 8, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("ITEM_GATE", "IMAGE/Object/ItemGate.bmp", 3200, 256, 8, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("SHOP_GATE", "IMAGE/Object/ShopGate.bmp", 2960, 270, 8, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("CHAPTER_GATE", "IMAGE/Object/ChapterGate.bmp", 3440, 320, 8, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("MIDBOSS_GATE", "IMAGE/Object/MidBossGate.bmp", 3680, 350, 8, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("LASTBOSS_GATE", "IMAGE/Object/LastBossGate.bmp", 5040, 370, 8, 1, true, RGB(255, 0, 255));
	_loading->loadImage("NOMAL_GATE_LOCK", "IMAGE/Object/NomalGate_Lock.bmp", 350, 256, true, RGB(255, 0, 255));

	_loading->loadFrameImage("TURRET", "IMAGE/Object/Turret.bmp", 3080, 440, 11, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("WOODEN_CART_A", "IMAGE/Object/WoodenCartA.bmp", 336, 62, 3, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("WOODEN_CART_B", "IMAGE/Object/WoodenCartB.bmp", 570, 76, 3, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("WOODEN_CART_C", "IMAGE/Object/WoodenCartC.bmp", 890, 132, 5, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("TENT_A", "IMAGE/Object/TentA.bmp", 576, 108, 3, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("TENT_B", "IMAGE/Object/TentB.bmp", 1280, 100, 5, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("TENT_C", "IMAGE/Object/TentC.bmp", 1300, 164, 5, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("TENT_D", "IMAGE/Object/TentD.bmp", 1740, 180, 5, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("WOODEN_BOX", "IMAGE/Object/WoodenBox.bmp", 342, 70, 3, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("FENCE_A", "IMAGE/Object/FenceA.bmp", 246, 68, 3, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("FENCE_B", "IMAGE/Object/FenceB.bmp", 384, 76, 3, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("FLAG_A", "IMAGE/Object/FlagA.bmp", 496, 266, 8, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("FLAG_B", "IMAGE/Object/FlagB.bmp", 702, 198, 9, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("CAULDRON", "IMAGE/Object/Cauldron.bmp", 426, 86, 3, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("CAGE_FRONT", "IMAGE/Tutorial/CageFront.bmp", 1128, 270, 3, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("CAGE_BACK", "IMAGE/Tutorial/CageBack.bmp", 930, 270, 3, 1, true, RGB(255, 0, 255));
	_loading->loadImage("CAGE_WITCH", "IMAGE/Tutorial/CageWitch.bmp", 130, 120, true, RGB(255, 0, 255));
	_loading->loadFrameImage("CAGE_WITCH_IDLE", "IMAGE/Tutorial/CageWitchIdle.bmp", 780, 360, 6, 2, true, RGB(255, 0, 255));

	_loading->loadFrameImage("JumpEffect", "IMAGE/Player/Effect/JumpEffect.bmp", 1700, 30, 17, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("DashEffect", "IMAGE/Player/Effect/DashEffect.bmp", 704, 120, 11, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("AttackEffect", "IMAGE/Player/Effect/AttackEffect2.bmp", 1800, 480, 10, 2, true, RGB(255, 0, 255));

	_loading->loadFrameImage("StartIdle", "IMAGE/Player/Start/StartIdle.bmp", 400, 200, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("StartWalk", "IMAGE/Player/Start/StartWalk.bmp", 800, 200, 8, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("StartDash", "IMAGE/Player/Start/StartDash.bmp", 100, 120, 1, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("StartJump", "IMAGE/Player/Start/StartJump.bmp", 300, 200, 3, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("StartFall", "IMAGE/Player/Start/StartFall.bmp", 400, 200, 4, 2, true, RGB(255, 0, 255));

	_loading->loadFrameImage("Head", "IMAGE/Player/Nomal/Head.bmp", 30, 60, 1, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("HNomalIdle", "IMAGE/Player/Nomal/HNomalIdle.bmp", 400, 200, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("HNomalAttackA", "IMAGE/Player/Nomal/HNomalAttackA.bmp", 800, 240, 5, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("HNomalAttackB", "IMAGE/Player/Nomal/HNomalAttackB.bmp", 640, 240, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("HNomalJumpAttack", "IMAGE/Player/Nomal/HNomalJumpAttack.bmp", 640, 240, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("HNomalWalk", "IMAGE/Player/Nomal/HNomalWalk.bmp", 800, 200, 8, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("HNomalSkillA", "IMAGE/Player/Nomal/HNomalSkillA.bmp", 640, 240, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("HNomalDash", "IMAGE/Player/Nomal/HNomalDash.bmp", 100, 120, 1, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("HNomalJump", "IMAGE/Player/Nomal/HNomalJump.bmp", 300, 200, 3, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("HNomalFall", "IMAGE/Player/Nomal/HNomalFall.bmp", 400, 200, 4, 2, true, RGB(255, 0, 255));

	_loading->loadFrameImage("NNomalIdle", "IMAGE/Player/Nomal/NNomalIdle.bmp", 400, 200, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("NNomalAttackA", "IMAGE/Player/Nomal/NNomalAttackA.bmp", 800, 240, 5, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("NNomalAttackB", "IMAGE/Player/Nomal/NNomalAttackB.bmp", 640, 240, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("NNomalJumpAttack", "IMAGE/Player/Nomal/NNomalJumpAttack.bmp", 640, 240, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("NNomalWalk", "IMAGE/Player/Nomal/NNomalWalk.bmp", 800, 200, 8, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("NNomalSkillA", "IMAGE/Player/Nomal/NNomalSkillA.bmp", 640, 240, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("NNomalDash", "IMAGE/Player/Nomal/NNomalDash.bmp", 100, 120, 1, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("NNomalJump", "IMAGE/Player/Nomal/NNomalJump.bmp", 300, 200, 3, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("NNomalFall", "IMAGE/Player/Nomal/NNomalFall.bmp", 400, 200, 4, 2, true, RGB(255, 0, 255));

	_loading->loadFrameImage("ChiefGuardIdle", "IMAGE/Player/ChiefGuard/ChiefGuardIdle.bmp", 840, 200, 6, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("ChiefGuardAttackA", "IMAGE/Player/ChiefGuard/ChiefGuardAttackA.bmp", 1000, 240, 5, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("ChiefGuardAttackB", "IMAGE/Player/ChiefGuard/ChiefGuardAttackB.bmp", 1040, 320, 5, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("ChiefGuardAttackC", "IMAGE/Player/ChiefGuard/ChiefGuardAttackC.bmp", 1248, 208, 6, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("ChiefGuardJumpAttack", "IMAGE/Player/ChiefGuard/ChiefGuardJumpAttack.bmp", 850, 288, 5, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("ChiefGuardWalk", "IMAGE/Player/ChiefGuard/ChiefGuardWalk.bmp", 768, 164, 6, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("ChiefGuardSkillA", "IMAGE/Player/ChiefGuard/ChiefGuardSkillA.bmp", 1248, 208, 6, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("ChiefGuardSkillB", "IMAGE/Player/ChiefGuard/ChiefGuardSkillB.bmp", 4664, 360, 22, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("ChiefGuardDash", "IMAGE/Player/ChiefGuard/ChiefGuardDash.bmp", 710, 148, 5, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("ChiefGuardJump", "IMAGE/Player/ChiefGuard/ChiefGuardJump.bmp", 408, 168, 3, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("ChiefGuardFall", "IMAGE/Player/ChiefGuard/ChiefGuardFall.bmp", 308, 168, 2, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("ChiefGuardFire", "IMAGE/Player/ChiefGuard/Fire.bmp", 2808, 264, 12, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("ChiefGuardSlash", "IMAGE/Player/ChiefGuard/FireSlash.bmp", 6468, 328, 22, 2, true, RGB(255, 0, 255));

	_loading->loadFrameImage("HunterIdle", "IMAGE/Player/Hunter/HunterIdle.bmp", 320, 160, 4, 2);
	_loading->loadFrameImage("HunterAttackA", "IMAGE/Player/Hunter/HunterAttackA.bmp", 400, 160, 5, 2);
	_loading->loadFrameImage("HunterAttackB", "IMAGE/Player/Hunter/HunterAttackB.bmp", 320, 160, 4, 2);
	_loading->loadFrameImage("HunterAttackC", "IMAGE/Player/Hunter/HunterAttackC.bmp", 700, 160, 7, 2);
	_loading->loadFrameImage("HunterDash", "IMAGE/Player/Hunter/HunterDash.bmp", 560, 160, 7, 2);
	_loading->loadFrameImage("HunterJump", "IMAGE/Player/Hunter/HunterJump.bmp", 240, 160, 3, 2);
	_loading->loadFrameImage("HunterFall", "IMAGE/Player/Hunter/HunterFall.bmp", 240, 160, 3, 2);
	_loading->loadFrameImage("HunterWalk", "IMAGE/Player/Hunter/HunterWalk.bmp", 560, 160, 7, 2);
	_loading->loadFrameImage("HunterJumpAttack", "IMAGE/Player/Hunter/HunterJumpAttack.bmp", 300, 160, 3, 2);
	_loading->loadFrameImage("HunterSkillA", "IMAGE/Player/Hunter/HunterSkillA.bmp", 700, 160, 7, 2);
	_loading->loadFrameImage("HunterSkillBEffect", "IMAGE/Player/Hunter/HunterSkillBEffect.bmp", 1280, 600, 2, 10);
	_loading->loadFrameImage("HunterArrowA", "IMAGE/Player/Hunter/HunterArrowA.bmp", 42, 20, 1, 2);
	_loading->loadFrameImage("HunterArrowB", "IMAGE/Player/Hunter/HunterArrowB.bmp", 50, 44, 1, 2);

	_loading->loadImage("dmgbar", "IMAGE/Enemy/HP/BossHp/Dmgbar.bmp", 2, 22);
	_loading->loadImage("Frame", "IMAGE/Enemy/HP/BossHp/Frame.bmp", 542, 46, true, RGB(255, 0, 255));
	_loading->loadImage("HPbar", "IMAGE/Enemy/HP/BossHp/HPbar.bmp", 2, 22);
	_loading->loadImage("HPbarBg", "IMAGE/Enemy/HP/BossHp/HPbarBg.bmp", 542, 46, true, RGB(255, 0, 255));
	_loading->loadImage("nameBg", "IMAGE/Enemy/HP/BossHp/nameBg.bmp", 300, 30);

	_loading->loadImage("hpfr", "IMAGE/Enemy/HP/Minion/hpfr.bmp", 63, 10, true, RGB(255, 0, 255));
	_loading->loadImage("hpbg", "IMAGE/Enemy/HP/Minion/hpbg.bmp", 59, 10);
	_loading->loadImage("hpbar", "IMAGE/Enemy/HP/Minion/hpbar.bmp", 1, 6);



	_loading->loadFrameImage("ArcharIdle", "IMAGE/Enemy/Archer/ArcharIdle.bmp", 380, 220, 5, 2);
	_loading->loadFrameImage("ArcharAttack", "IMAGE/Enemy/Archer/ArcharAttack.bmp", 456, 196, 4, 2);
	_loading->loadFrameImage("Archarmove", "IMAGE/Enemy/Archer/Archarmove.bmp", 456, 196, 6, 2);
	_loading->loadImage("ArcharAim", "IMAGE/Enemy/Archer/ArcharAim.bmp", 880, 20, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Arrow", "IMAGE/Enemy/Archer/Arrow.bmp", 50, 24, 1, 2);
	_loading->loadFrameImage("ArcharDead", "IMAGE/Enemy/Archer/ArcharDead.bmp", 144, 36, 1, 1);
	_loading->loadFrameImage("ArcharHit", "IMAGE/Enemy/Archer/ArcharHit.bmp", 102, 180, 1, 2);

	_loading->loadFrameImage("GardIdle", "IMAGE/Enemy/Gard/GardIdle.bmp", 1090, 400, 5, 2);
	_loading->loadFrameImage("GardAttack", "IMAGE/Enemy/Gard/GardAttack.bmp", 2048, 436, 8, 2);
	_loading->loadFrameImage("Gardmove", "IMAGE/Enemy/Gard/Gardmove.bmp", 1792, 400, 8, 2);
	_loading->loadImage("GardDead", "IMAGE/Enemy/Gard/GardDead.bmp", 268, 70, true, RGB(255, 0, 255));
	_loading->loadFrameImage("GardTakle", "IMAGE/Enemy/Gard/GardTakle.bmp", 618, 452, 3, 2);
	_loading->loadFrameImage("TackleEffect", "IMAGE/Enemy/Gard/TackleEffect.bmp", 7304, 536, 22, 2);
	


	_loading->loadFrameImage("GiantTreeIdle", "IMAGE/Enemy/GiantTree/GiantTreeIdle.bmp", 1150, 230, 5, 1);
	_loading->loadFrameImage("GiantTreeAttack", "IMAGE/Enemy/GiantTree/GiantTreeMele.bmp", 1960, 224, 7, 1);
	_loading->loadFrameImage("GiantTreeRange", "IMAGE/Enemy/GiantTree/GiantTreeRange.bmp", 1072, 230, 4, 1);
	_loading->loadFrameImage("GiantTreeDead", "IMAGE/Enemy/GiantTree/GiantTreeDead.bmp", 200, 154, 1, 1);
	_loading->loadFrameImage("GiantTreeEffect", "IMAGE/Enemy/GiantTree/GiantTreeEffect.bmp", 11760, 140, 21, 1);
	_loading->loadFrameImage("Light", "IMAGE/Enemy/GiantTree/Light.bmp", 112, 50, 2, 1);


	_loading->loadFrameImage("GreenTreeIdle", "IMAGE/Enemy/GreenTree/GreenTreeIdle.bmp", 570, 264, 5, 2);
	_loading->loadFrameImage("GreenTreeAttack", "IMAGE/Enemy/GreenTree/GreenTreeAttack.bmp", 1312, 308, 8, 2);
	_loading->loadFrameImage("GreenTreemove", "IMAGE/Enemy/GreenTree/GreenTreemove.bmp", 648, 260, 6, 2);
	_loading->loadFrameImage("GreenTreeHit", "IMAGE/Enemy/GreenTree/GreenTreeHit.bmp", 88, 252, 1, 2);
	_loading->loadFrameImage("GreenTreeDead", "IMAGE/Enemy/GreenTree/GreenTreeDead.bmp", 44, 63, 1, 1);
	_loading->loadFrameImage("GreenTreeAttackEffet", "IMAGE/Enemy/GreenTree/GreenTreeAttackEffet.bmp", 2232, 116, 9, 1);
	_loading->loadImage("GreenTreeAim", "IMAGE/Enemy/GreenTree/GreenTreeAim.bmp", 254, 14, true, RGB(255, 0, 255));



	_loading->loadFrameImage("HammerIdle", "IMAGE/Enemy/Hammer/HammerIdle.bmp", 1176, 296, 6, 2);
	_loading->loadFrameImage("Hammermove", "IMAGE/Enemy/Hammer/HammerJump.bmp", 1540, 360, 7, 2);
	_loading->loadFrameImage("HammerAttack", "IMAGE/Enemy/Hammer/HammerAttack.bmp", 1952, 500, 8, 2);
	_loading->loadFrameImage("HammerSkill1", "IMAGE/Enemy/Hammer/HammerSkill1.bmp", 2744, 680, 7, 2);
	_loading->loadFrameImage("HammerReady", "IMAGE/Enemy/Hammer/HammerReady.bmp", 1484, 340, 7, 2);	
	_loading->loadFrameImage("HammerDead", "IMAGE/Enemy/Hammer/HammerDead.bmp", 820, 260, 5, 2);	
	_loading->loadFrameImage("AttackEf", "IMAGE/Enemy/Hammer/AttackEf.bmp", 18798, 270, 39, 1);
	_loading->loadFrameImage("HammerSkill1EF", "IMAGE/Enemy/Hammer/HammerSkill1EF.bmp", 2430, 112, 5, 1);
	//========================================================================================================
	_loading->loadFrameImage("KnightIdle", "IMAGE/Enemy/Knight/KnightIdle.bmp", 408, 256, 6, 2);
	_loading->loadFrameImage("KnightAttack", "IMAGE/Enemy/Knight/KnightAttack.bmp", 580, 256, 5, 2);
	_loading->loadFrameImage("Knightmove", "IMAGE/Enemy/Knight/Knightmove.bmp", 832, 256, 8, 2);
	_loading->loadFrameImage("KnightHit", "IMAGE/Enemy/Knight/KnightHit.bmp", 92, 188, 1, 2);
	_loading->loadFrameImage("KnightDead", "IMAGE/Enemy/Knight/KnightDead.bmp", 144, 32, 1, 1);

	_loading->loadFrameImage("Knight1Idle", "IMAGE/Enemy/Knight/KnightIdle.bmp", 408, 256, 6, 2);
	_loading->loadFrameImage("Knight1Attack", "IMAGE/Enemy/Knight/KnightAttack.bmp", 580, 256, 5, 2);
	_loading->loadFrameImage("Knight1move", "IMAGE/Enemy/Knight/Knightmove.bmp", 832, 256, 8, 2);
	_loading->loadFrameImage("Knight1Hit", "IMAGE/Enemy/Knight/KnightHit.bmp", 92, 188, 1, 2);
	_loading->loadFrameImage("Knight1Dead", "IMAGE/Enemy/Knight/KnightDead.bmp", 144, 32, 1, 1);

	_loading->loadFrameImage("Knight2Idle", "IMAGE/Enemy/Knight/KnightIdle.bmp", 408, 256, 6, 2);
	_loading->loadFrameImage("Knight2Attack", "IMAGE/Enemy/Knight/KnightAttack.bmp", 580, 256, 5, 2);
	_loading->loadFrameImage("Knight2move", "IMAGE/Enemy/Knight/Knightmove.bmp", 832, 256, 8, 2);
	_loading->loadFrameImage("Knight2Hit", "IMAGE/Enemy/Knight/KnightHit.bmp", 92, 188, 1, 2);
	_loading->loadFrameImage("Knight2Dead", "IMAGE/Enemy/Knight/KnightDead.bmp", 144, 32, 1, 1);


	_loading->loadFrameImage("Knight3Idle", "IMAGE/Enemy/Knight/KnightIdle.bmp", 408, 256, 6, 2);
	_loading->loadFrameImage("Knight3Attack", "IMAGE/Enemy/Knight/KnightAttack.bmp", 580, 256, 5, 2);
	_loading->loadFrameImage("Knight3move", "IMAGE/Enemy/Knight/Knightmove.bmp", 832, 256, 8, 2);
	_loading->loadFrameImage("Knight3Hit", "IMAGE/Enemy/Knight/KnightHit.bmp", 92, 188, 1, 2);
	_loading->loadFrameImage("Knight3Dead", "IMAGE/Enemy/Knight/KnightDead.bmp", 144, 32, 1, 1);
	//========================================================================================================

	_loading->loadFrameImage("MageIdle", "IMAGE/Enemy/Mage/MageIdle.bmp", 430, 224, 5, 2);
	_loading->loadFrameImage("MageAttack", "IMAGE/Enemy/Mage/MageAttack.bmp", 516, 284, 6, 2);
	_loading->loadFrameImage("TelIn", "IMAGE/Enemy/Mage/TelIn.bmp", 258, 126, 3, 1);
	_loading->loadFrameImage("fire", "IMAGE/Enemy/Mage/fire.bmp", 1056, 44, 22, 1);
	_loading->loadFrameImage("fireHit", "IMAGE/Enemy/Mage/fireHit.bmp", 962, 80, 13, 1);
	_loading->loadFrameImage("TelInEF", "IMAGE/Enemy/Mage/TelInEF.bmp", 564, 266, 3, 1);
	_loading->loadFrameImage("TelOutEF", "IMAGE/Enemy/Mage/TelOutEF.bmp", 990, 266, 5, 1);
	_loading->loadImage("telOutA", "IMAGE/Enemy/Mage/telOutA.bmp", 86, 110, true, RGB(255, 0, 255));
	_loading->loadImage("TelInA", "IMAGE/Enemy/Mage/TelInA.bmp", 86, 126, true, RGB(255, 0, 255));
	_loading->loadFrameImage("MageDead", "IMAGE/Enemy/Mage/MageDead.bmp", 142, 40, 1, 1);
	_loading->loadFrameImage("MageHit", "IMAGE/Enemy/Mage/MageHit.bmp", 116, 176, 1, 2);


	_loading->loadFrameImage("OgreIdle", "IMAGE/Enemy/Ogre/OgreIdle.bmp", 1104, 360, 6, 2);
	_loading->loadFrameImage("OgreAttack", "IMAGE/Enemy/Ogre/OgreAttack.bmp", 1876, 420, 7, 2);
	_loading->loadFrameImage("Ogremove", "IMAGE/Enemy/Ogre/Ogremove.bmp", 1760, 360, 8, 2);
	_loading->loadFrameImage("OgreDead", "IMAGE/Enemy/Ogre/OgreDead.bmp", 3136, 320, 14, 2);
	_loading->loadFrameImage("OgreHit", "IMAGE/Enemy/Ogre/OgreHit.bmp", 242, 340, 1, 2);
	_loading->loadFrameImage("OgreHit2", "IMAGE/Enemy/Ogre/OgreHit2.bmp", 222, 308, 1, 2);
	_loading->loadFrameImage("OgreDF", "IMAGE/Enemy/Ogre/OgreDF.bmp", 9752, 452, 23, 2);


	_loading->loadFrameImage("TreeIdle", "IMAGE/Enemy/Tree/TreeIdle.bmp", 560, 264, 5, 2);
	_loading->loadFrameImage("TreeAttack", "IMAGE/Enemy/Tree/TreeAttack.bmp", 472, 256, 4, 2);
	_loading->loadFrameImage("Treemove", "IMAGE/Enemy/Tree/Treemove.bmp", 636, 260, 6, 2);
	_loading->loadFrameImage("TreeHit", "IMAGE/Enemy/Tree/TreeHit.bmp", 92, 256, 1, 2);
	_loading->loadFrameImage("TreeDead", "IMAGE/Enemy/Tree/TreeDead.bmp", 152, 66, 1, 1);

	_loading->loadFrameImage("Bomb", "IMAGE/Enemy/Boss/Bomb.bmp", 2800, 204, 14, 1);
	_loading->loadFrameImage("Explorsion", "IMAGE/Enemy/Boss/Explorsion.bmp", 17622, 332, 33, 1);
	_loading->loadFrameImage("Body", "IMAGE/Enemy/Boss/Body.bmp", 3195, 525, 5, 1);
	_loading->loadFrameImage("DownHand", "IMAGE/Enemy/Boss/DownHand.bmp", 2280, 363, 6, 2);
	_loading->loadFrameImage("DownLHand", "IMAGE/Enemy/Boss/DownHand.bmp", 2280, 363, 6, 2);
	_loading->loadFrameImage("DownHandEF", "IMAGE/Enemy/Boss/DownHandEF.bmp", 9078, 255, 17, 1);
	_loading->loadFrameImage("DownLHandEF", "IMAGE/Enemy/Boss/DownHandEF.bmp", 9078, 255, 17, 1);
	_loading->loadFrameImage("NULL", "IMAGE/Enemy/Boss/NULL.bmp", 12, 12, 1, 1);
	_loading->loadFrameImage("BossHead", "IMAGE/Enemy/Boss/Head.bmp", 1845, 261, 5, 1);
	_loading->loadFrameImage("Jaw", "IMAGE/Enemy/Boss/Jaw.bmp", 672, 147, 4, 1);
	_loading->loadFrameImage("PucnhReady", "IMAGE/Enemy/Boss/PucnhReady.bmp", 2160, 450, 8, 2);
	_loading->loadFrameImage("PucnhLReady", "IMAGE/Enemy/Boss/PucnhReady.bmp", 2160, 450, 8, 2);
	_loading->loadFrameImage("DeadEF", "IMAGE/Enemy/Boss/DeadEF.bmp", 28308, 618, 30, 1);
	_loading->loadFrameImage("gether", "IMAGE/Enemy/Boss/gether.bmp", 11200, 400, 28, 1);
	_loading->loadFrameImage("Spark", "IMAGE/Enemy/Boss/Spark.bmp", 4720, 208, 20, 1);
	_loading->loadFrameImage("GroggyEF", "IMAGE/Enemy/Boss/GroggyEF.bmp", 5876, 440, 13, 1);
}

void LoadingScene::loadingSound()
{
	_loading->loadSound("TITLE_BGM", "SOUND/Title/BGM_Title.wav", true, true);
	_loading->loadSound("OPENING_PEACE", "SOUND/Opening/BGM_Peace.wav", true, false);
	_loading->loadSound("OPENING_VIBRATION", "SOUND/Opening/SFX_Vibration.wav", false, false);
	_loading->loadSound("OPENING_CRASH", "SOUND/Opening/SFX_Crash.wav", false, false);
	_loading->loadSound("OPENING_INVADE", "SOUND/Opening/BGM_Invade.wav", true, false);
	_loading->loadSound("TUTORIAL_BGM", "SOUND/Tutorial/BGM_Tutorial.wav", true, true);
	_loading->loadSound("FIELD_BGM", "SOUND/Field/BGM_Field.wav", true, true);
	_loading->loadSound("BOSS_BGM", "SOUND/Boss/BGM_Boss.wav", true, true);
}