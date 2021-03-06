// include
#include "SceneMgr.h"
#include "Menu.h"
#include "Game.h"
#include "SBoard.h"

// グローバル変数
static Scene_S Scene, prevScene;

// 更新
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

// 描画
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

// シーン変更
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

// 前のシーンを得る
Scene_S getPrevScene()
{
	return prevScene;
}