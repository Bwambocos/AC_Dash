// include
#include <Siv3D.hpp>
#include "SceneMgr.h"
#include "Menu.h"

// define
#define DRAW_AC_WA_SPEED 3

// �O���[�o���ϐ�
static Texture ac, wa;
static Sound bgm;
static Font titleFont, choiceFont;
static int32 draw_ac_x, draw_wa_x;
static Circle SBoardCircle, playCircle, exitCircle;

// ���j���[ ������
void Menu_Init()
{
	// �w�i ������
	{
		if (!ac)
		{
			ac = Texture(L"data\\Menu\\ac.png");
			wa = Texture(L"data\\Menu\\wa.png");
			bgm = Sound(L"data\\Menu\\bgm.ogg");
		}
		draw_ac_x = -ac.width;
		draw_wa_x = Window::Width();
	}

	// �I���� ������
	{
		if (!titleFont)
		{
			titleFont = Font(64);
			choiceFont = Font(24);
			SBoardCircle = playCircle = exitCircle = Circle(128);
			SBoardCircle.x = Window::Center().x - SBoardCircle.r * 2 - 25;
			playCircle.x = Window::Center().x;
			exitCircle.x = Window::Center().x + exitCircle.r * 2 + 25;
			SBoardCircle.y = playCircle.y = exitCircle.y = 25 * 2 + titleFont.height + exitCircle.r;
		}
	}

	bgm.setLoop(true);
	bgm.play();
}

// ���j���[  �X�V
void Menu_Update()
{
	// �w�i �X�V
	{
		draw_ac_x = (draw_ac_x >= Window::Width() ? -ac.width : draw_ac_x + DRAW_AC_WA_SPEED);
		draw_wa_x = (draw_wa_x <= -wa.width ? Window::Width() : draw_wa_x - DRAW_AC_WA_SPEED);
	}

	// �I���� �X�V
	{
		if (SBoardCircle.leftClicked)
		{
			bgm.stop();
			SceneMgr_ChangeScene(Scene_SBoard);
		}
		if (playCircle.leftClicked)
		{
			bgm.stop();
			SceneMgr_ChangeScene(Scene_Game);
		}
		if (exitCircle.leftClicked) { System::Exit(); }
	}
}

// ���j���[  �`��
void Menu_Draw()
{
	// �w�i �`��
	{
		ac.draw(draw_ac_x, Window::Center().y - ac.height);
		wa.draw(draw_wa_x, Window::Center().y);
	}

	// �I���� �`��
	{
		titleFont(L"AC Dash v1.0").drawCenter(25);
		SBoardCircle.drawShadow({ 0, 8 }, 28, 6);
		SBoardCircle.draw(Palette::Gold);
		if (SBoardCircle.mouseOver) { SBoardCircle.drawFrame(5, 5, Palette::Red); }
		choiceFont(L"�X�R�A�{�[�h\n�@ ������").drawCenter(SBoardCircle.x, SBoardCircle.y, Palette::Black);
		playCircle.drawShadow({ 0, 8 }, 28, 6);
		playCircle.draw(Palette::Lightskyblue);
		if (playCircle.mouseOver) { playCircle.drawFrame(5, 5, Palette::Red); }
		choiceFont(L"�Q�[���J�n�I").drawCenter(playCircle.x, playCircle.y, Palette::Black);
		exitCircle.drawShadow({ 0, 8 }, 28, 6);
		exitCircle.draw(Palette::Orange);
		if (exitCircle.mouseOver) { exitCircle.drawFrame(5, 5, Palette::Red); }
		choiceFont(L"�I������").drawCenter(exitCircle.x, exitCircle.y, Palette::Black);
	}
}