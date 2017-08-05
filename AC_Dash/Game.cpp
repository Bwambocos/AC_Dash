// include
#include <Siv3D.hpp>
#include "SceneMgr.h"
#include "Game.h"

// �O���[�o���ϐ�
static Texture main, ground, ac, wa;
static Font statsFont;
static int draw_ground_x1, draw_ground_x2, draw_speed;
static int64 score, life;

// �Q�[�� ������
void Game_Init()
{
	// �w�i ������
	{
		if (!main)
		{
			main = Texture(L"data\\Game\\main.png");
			ground = Texture(L"data\\Game\\ground.png");
		}
		draw_ground_x1 = 0;
		draw_ground_x2 = Window::Width();
		draw_speed = 5;
	}

	// �X�e�[�^�X������
	{
		if (!ac)
		{
			ac = Texture(L"data\\Game\\ac.png");
			wa = Texture(L"data\\Game\\wa.png");
			FontManager::Register(L"data\\Game\\scoreboard.ttf");
			statsFont = Font(32, L"Score Board");
			score = 0; life = 5;
		}
	}
}

// �Q�[�� �X�V
void Game_Update()
{
	// �w�i �X�V
	{
		draw_ground_x1 = (draw_ground_x1 <= -Window::Width() ? Window::Width() : draw_ground_x1 - draw_speed);
		draw_ground_x2 = (draw_ground_x2 <= -Window::Width() ? Window::Width() : draw_ground_x2 - draw_speed);
	}

	// �X�e�[�^�X �X�V
	{
		++score;
	}
}

// �Q�[�� �`��
void Game_Draw()
{
	// �w�i �`��
	{
		main.draw();
		ground.draw(draw_ground_x1, 0);
		ground.draw(draw_ground_x2, 0);
	}

	// �X�e�[�^�X �`��
	{
		auto display = Format(L"SCORE:", score, L"\nLIFE :", life);
		statsFont(display).draw(10, 10);
	}
}