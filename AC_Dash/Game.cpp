// include
#include <Siv3D.hpp>
#include "SceneMgr.h"
#include "Game.h"

// define
#define MAKE_ITEM_DISTANCE 3250
#define ITEM_KIND_NUM 2

// �O���[�o���ϐ�
static Texture main, ground, item[ITEM_KIND_NUM];
static Font statsFont;
static int64 score, life;
static int draw_ground_x1, draw_ground_x2, draw_speed;
static int draw_item_num, draw_item_x;
static bool draw_item_flag;

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

	// �A�C�e�� ������
	{
		draw_item_flag = false;
	}

	// �X�e�[�^�X ������
	{
		if (!item[0])
		{
			item[0] = Texture(L"data\\Game\\ac.png");
			item[1] = Texture(L"data\\Game\\wa.png");
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

	// �A�C�e�� �X�V
	{
		if (draw_item_flag)
		{
			if (draw_item_x < -item[draw_item_num].width)
			{
				if (draw_item_num == 0)
				{
					score -= 1800;
					--life;
				}
				draw_item_flag = false;
			}
			draw_item_x -= draw_speed;
		}
		if (!draw_item_flag)
		{
			draw_item_num = Random(ITEM_KIND_NUM - 1);
			draw_item_x = Window::Width();
			draw_item_flag = true;
		}
	}

	// �X�e�[�^�X �X�V
	{
		if (draw_item_flag)
		{
			const Rect tmpRect(draw_item_x, 240, item[draw_item_num].width, item[draw_item_num].height);
			if (tmpRect.leftClicked)
			{
				switch (draw_item_num)
				{
				case 0:
					score += 2500;
					++life;
					break;

				case 1:
					score -= 1800;
					--life;
					break;
				}
				draw_item_flag = false;
			}
		}
		++score;
		if (life < 1) { SceneMgr_ChangeScene(Scene_Result); }
		if (score < 0) { score = 0; }
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

	// �A�C�e�� �`��
	{
		if (draw_item_flag) { item[draw_item_num].draw(draw_item_x, 0); }
	}

	// �X�e�[�^�X �`��
	{
		auto display = Format(L"SCORE:", score, L"\nLIFE :", life);
		statsFont(display).draw(10, 10);
	}
}