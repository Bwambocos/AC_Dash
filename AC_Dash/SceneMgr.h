#pragma once

// �V�[���\����
typedef enum
{
	Scene_Menu,
	Scene_Game,
	Scene_SBoard,
}Scene_S;

// �X�V
void SceneMgr_Update();

// �`��
void SceneMgr_Draw();

// �V�[���ύX
void SceneMgr_ChangeScene(Scene_S);

// �O�̃V�[���𓾂�
Scene_S getPrevScene();