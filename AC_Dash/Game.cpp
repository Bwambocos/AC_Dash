// include
#include <Siv3D.hpp>
#include "SceneMgr.h"
#include "Game.h"

// define
#define CHANGE_SPEED_DISTANCE 3000
#define ITEM_KIND_NUM 5
#define DRAW_STATS_CHANGED_LENGTH 1500

// �O���[�o���ϐ�
static Texture main, ground, item[ITEM_KIND_NUM];
static Font statsFont, font;
static Sound bgm, ok, ng;
static int64 startTime, nowTime;
static int64 score, life;
static int64 draw_stats_startTime, draw_stats_Time, draw_Message_startTime, draw_Message_Time;
static String statsChanged = L"", statsMessage = L"";
static double draw_ground_x1, draw_ground_x2, draw_item_x, draw_speed;
static int draw_item_num;
static bool draw_item_flag, first_flag = true;

// �Q�[�� ������
void Game_Init()
{
	// �w�i ������
	{
		if (!main)
		{
			main = Texture(L"data\\Game\\main.png");
			ground = Texture(L"data\\Game\\ground.png");
			bgm = Sound(L"data\\Game\\bgm.wav");
			ok = Sound(L"data\\Game\\ok.wav");
			ng = Sound(L"data\\Game\\ng.wav");
		}
		draw_ground_x1 = 0;
		draw_ground_x2 = Window::Width();
		draw_speed = 5;
	}

	// �A�C�e�� ������
	{
		if (!item[0])
		{
			item[0] = Texture(L"data\\Game\\ac.png");
			item[1] = Texture(L"data\\Game\\wa.png");
			item[2] = Texture(L"data\\Game\\wj.png");
			item[3] = Texture(L"data\\Game\\tle.png");
			item[4] = Texture(L"data\\Game\\re.png");
		}
		draw_item_flag = false;
	}

	// �X�e�[�^�X ������
	{
		FontManager::Register(L"data\\Game\\scoreboard.ttf");
		statsFont = Font(32, L"Score Board");
		score = 0; life = 5;
	}
	if (first_flag) { Game_Expl(); }
	nowTime = startTime = Time::GetMillisec64();
	bgm.setLoop(true);
	bgm.setVolume(0.9);
	bgm.play();
}

// �Q�[�� �X�V
void Game_Update()
{
	auto d = (double)(draw_speed * 60)*(Time::GetMillisec64() - nowTime) / 1000;

	// �w�i �X�V
	{
		if (nowTime - startTime > CHANGE_SPEED_DISTANCE)
		{
			startTime = nowTime;
			++draw_speed;
			statsMessage = L"SPEED UP!";
			draw_Message_Time = draw_Message_startTime = Time::GetMillisec64();
		}
		draw_ground_x1 = (draw_ground_x1 <= -Window::Width() ? Window::Width() : draw_ground_x1 - d);
		draw_ground_x2 = (draw_ground_x2 <= -Window::Width() ? Window::Width() : draw_ground_x2 - d);
	}

	// �A�C�e�� �X�V
	{
		if (draw_item_flag)
		{
			if (draw_item_x < -item[draw_item_num].width)
			{
				if (draw_item_num == 0)
				{
					score -= 100;
					--life;
					statsChanged = L"-100\n-1";
					ng.play();
					draw_stats_Time = draw_stats_startTime = Time::GetMillisec64();
				}
				draw_item_flag = false;
			}
			draw_item_x -= d;
		}
		if (!draw_item_flag)
		{
			if (RandomBool((double)1 / (double)3)) { draw_item_num = 0; }
			else { draw_item_num = Random(ITEM_KIND_NUM - 1); }
			draw_item_x = Window::Width();
			draw_item_flag = true;
		}
	}

	// �X�e�[�^�X �X�V
	{
		draw_stats_Time = draw_Message_Time = Time::GetMillisec64();
		if (draw_item_flag)
		{
			const Rect tmpRect((int)draw_item_x, 240, item[draw_item_num].width, item[draw_item_num].height);
			if (tmpRect.leftClicked)
			{
				switch (draw_item_num)
				{
				case 0:
					score += 250;
					++life;
					statsChanged = L"+250\n+1";
					ok.play();
					draw_stats_Time = draw_stats_startTime = Time::GetMillisec64();
					break;

				case 1:
					score -= 180;
					--life;
					statsChanged = L"-180\n-1";
					ng.play();
					draw_stats_Time = draw_stats_startTime = Time::GetMillisec64();
					break;

				case 2:
					--draw_speed;
					statsMessage = L"SPEED DOWN!";
					ok.play();
					draw_Message_Time = draw_Message_startTime = Time::GetMillisec64();
					break;

				case 3:
					++draw_speed;
					statsMessage = L"SPEED UP!";
					ng.play();
					draw_Message_Time = draw_Message_startTime = Time::GetMillisec64();
					break;

				case 4:
					score -= 100;
					--life;
					statsChanged = L"-100\n-1";
					ng.play();
					draw_stats_Time = draw_stats_startTime = Time::GetMillisec64();
					break;
				}
				draw_item_flag = false;
			}
		}
		score += (int64)d;
		if (life < 1)
		{
			bgm.setVolume(0.5);
			bgm.setLoop(false);
			Game_End();
			bgm.stop();
			SceneMgr_ChangeScene(Scene_SBoard);
		}
		if (score < 0) { score = 0; }
		if (life > 15)
		{
			life = 15;
			statsChanged[statsChanged.length - 2] = L'�}';
			statsChanged[statsChanged.length - 1] = L'0';
		}
	}
	nowTime = Time::GetMillisec64();
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
		if (draw_item_flag)
		{
			item[draw_item_num].draw(draw_item_x, 0);
			const Rect tmpRect((int)draw_item_x, 240, item[draw_item_num].width, 75);
			if (tmpRect.mouseOver) { tmpRect.drawFrame(2, 3, Palette::Yellow); }
		}
	}

	// �X�e�[�^�X �`��
	{
		const auto flag = draw_stats_Time - draw_stats_startTime <= DRAW_STATS_CHANGED_LENGTH;
		const auto display = Format(score, L"\n", life);
		int draw_x = (1 + (int)Log10(score)) * 30;
		statsFont(L"SCORE:\nLIFE :").draw(10, 10);
		statsFont(display).draw(192, 10, Palette::White);
		if (flag) { statsFont(statsChanged).draw(draw_x + 210, 10, Palette::Orange); }
		if (draw_Message_Time - draw_Message_startTime <= DRAW_STATS_CHANGED_LENGTH) { statsFont(statsMessage).drawCenter(10 + statsFont.height * 2, Palette::Orange); }
	}
}

// �Q�[������ �`��
void Game_Expl()
{
	Texture expl(L"data\\Game\\explain1.png");
	static RoundRect button1(Window::Width() / 2 - (font(L"���ɐi��").region().w + font.height) / 2, Window::Height() - font.height - 5, font(L"���ɐi��").region().w + font.height, font.height, 5);
	static RoundRect button2(Window::Width() - font(L"�Q�[���ɐi��").region().w - font.height - 5, Window::Height() - font.height - 5, font(L"�Q�[���ɐi��").region().w + font.height, font.height, 5);
	while (!button1.leftClicked && System::Update())
	{
		expl.draw();
		button1.draw(button1.mouseOver ? Palette::Orange : Palette::White);
		font(L"���ɐi��").drawCenter(Window::Height() - font.height - 5, Palette::Black);
	}
	expl = Texture(L"data\\Game\\explain2.png");
	while (!button2.leftClicked && System::Update())
	{
		expl.draw();
		button2.draw(button2.mouseOver ? Palette::Orange : Palette::White);
		font(L"�Q�[���ɐi��").draw(Window::Width() - font(L"�Q�[���ɐi��").region().w - font.height / 2 - 5, Window::Height() - font.height - 5, Palette::Black);
	}
	first_flag = false;
}

// �Q�[���I�� �`��
void Game_End()
{
	const Rect rect(0, 0, Window::Width(), Window::Height());
	const Font font1(48);
	const Font font2(36);
	const Font font3(24);
	const String text = Format(L"�X�R�A�� ", score, L" �ł��I");
	RoundRect button;
	button.w = font3(L"���ɐi��").region().w + font3.height;
	button.h = font3.height;
	button.x = Window::Width() / 2 - button.w / 2;
	button.y = 325;
	button.r = 5;

	while (!button.leftClicked)
	{
		System::Update();
		if(Input::KeyT.clicked)
		{
			auto tmp = Format(L"#AC_Dash v1.0 ���v���C���A�X�R�A ", score, L" �_���l�����܂����I�Ō�ɏo�������A�C�e���� ");
			switch (draw_item_num)
			{
			case 0:
				tmp += L"AC";
				break;
			case 1:
				tmp += L"WA";
				break;
			case 2:
				tmp += L"WJ";
				break;
			case 3:
				tmp += L"TLE";
				break;
			case 4:
				tmp += L"RE";
				break;
			}
			tmp += L" �ł����B";
			Twitter::OpenTweetWindow(tmp);
		}
		main.draw(); ground.draw();
		item[Random(ITEM_KIND_NUM - 1)].drawAt(RandomVec2(Window::Width(), Window::Height()));
		rect.draw(Color(64, 64, 64, 200));
		font1(L"�Q�[���I�[�o�[").drawCenter(25, Palette::Red);
		font2(text).drawCenter(150, Palette::Yellow);
		font3(L"�s�L�[�������ăX�R�A���c�C�[�g�I").drawCenter(250, Palette::Aqua);
		button.draw(button.mouseOver ? Palette::Orange : Palette::White);
		font3(L"���ɐi��").drawCenter(325, Palette::Black);
		item[1].drawAt(Window::Width() / 2, 330 + font3.height);
	}
}

// �Q�[�� �X�R�A�擾
int64 Game_getScore()
{
	return score;
}