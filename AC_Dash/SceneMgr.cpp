// include
#include "SceneMgr.h"
#include "Menu.h"
#include "Game.h"
#include "SBoard.h"

// �O���[�o���ϐ�
static Scene_S Scene, prevScene;

// �X�V
void SceneMgr_Update()
{
	switch (Scene)
	{
	case Scene_Menu:
		Menu_Update();
		break;

	case Scene_Game:
		Game_Update();
		break;

	case Scene_Result:
		Game_End();
		break;

	case Scene_Record:
		SBoard_Record();
		break;

	case Scene_SBoard:
		SBoard_Update();
		break;
	}
}

// �`��
void SceneMgr_Draw()
{
	switch (Scene)
	{
	case Scene_Menu:
		Menu_Draw();
		break;

	case Scene_Game:
		Game_Draw();
		break;

	case Scene_SBoard:
		SBoard_Draw();
		break;
	}
}

// �V�[���ύX
void SceneMgr_ChangeScene(Scene_S nextScene)
{
	prevScene = Scene;
	Scene = nextScene;
	switch (Scene)
	{
	case Scene_Menu:
		Menu_Init();
		break;

	case Scene_Game:
		Game_Init();
		break;

	case Scene_SBoard:
		SBoard_Init();
		break;
	}
}

// �O�̃V�[���𓾂�
Scene_S getPrevScene()
{
	return prevScene;
}