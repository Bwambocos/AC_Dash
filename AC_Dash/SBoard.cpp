// include
#include <Siv3D.hpp>
#include "SceneMgr.h"
#include "SBoard.h"
#include "Game.h"

// define
#define MAX_CELL_NUM 5

struct cell_data
{
	String name;
	int64 score;
};

// �O���[�o���ϐ�
static std::vector<cell_data>data;
static Font titleFont, cellFont, textFont;
static Triangle goUp({ 480,101 }, { 510,111 }, { 450,111 });
static Triangle goDown({ 450,417 }, { 510,417 }, { 480,427 });
static String userName = L"";
static Font font1, font2;
static int drawCellBegin;

// �X�R�A�{�[�h ������
void SBoard_Init()
{
	if (data.size() == 0)
	{
		titleFont = Font(48);
		cellFont = Font(32);
		textFont = Font(24);
		font1 = Font(24);
		font2 = Font(18);
		const CSVReader csv(L"data\\Sboard\\saveData.csv");
		for (int i = 0; i < (signed)csv.rows; ++i)
		{
			data.push_back({ csv.get<String>(i,0),csv.get<int64>(i,1) });
		}
	}
	if (getPrevScene() == Scene_Game) { SceneMgr_ChangeScene(Scene_Record); }
	if (getPrevScene() == Scene_Record)
	{
		userName.erase(userName.length - 1);
		CSVWriter csv(L"data\\SBoard\\saveData.csv");
		bool isOverWrite = false;
		for (auto i : data)
		{
			if (i.name == userName)
			{
				i.score = Game_getScore();
				isOverWrite = true;
			}
		}
		if (!isOverWrite) { data.push_back({ userName,Game_getScore() }); }
		std::sort(data.begin(), data.end(), [](const auto&l, const auto&r) {return l.score > r.score; });
		for (auto i : data) { csv.writeRow(i.name, i.score); }
	}
	drawCellBegin = 0;
}

// �X�R�A�{�[�h �X�V
void SBoard_Update()
{
	if (Input::KeyB.clicked) { SceneMgr_ChangeScene(Scene_Menu); }
	if (goUp.leftClicked) { --drawCellBegin; }
	if (goDown.leftClicked) { ++drawCellBegin; }
	drawCellBegin += Mouse::Wheel();
	drawCellBegin = Min<int>(drawCellBegin, (int)data.size() - MAX_CELL_NUM);
	drawCellBegin = Max(drawCellBegin, 0);
}

// �X�R�A�{�[�h �`��
void SBoard_Draw()
{
	titleFont(L"�X�R�A�{�[�h").drawCenter(5);
	if (drawCellBegin > 0) { goUp.draw(goUp.mouseOver ? Palette::Orange : Palette::White); }
	if (drawCellBegin + MAX_CELL_NUM < (signed)data.size()) { goDown.draw(goDown.mouseOver ? Palette::Orange : Palette::White); }
	for (int i = 0; i < Min<int>(MAX_CELL_NUM, (int)data.size() - drawCellBegin); ++i)
	{
		auto num = i + drawCellBegin;
		auto text = Format(num + 1, L"�ʁ@", data[num].name, L"�@", data[num].score, L"�_");
		Color color;
		switch (num)
		{
		case 0:
			color = Palette::Gold;
			break;
		case 1:
			color = Palette::Silver;
			break;
		case 2:
			color = Palette::Brown;
			break;
		default:
			color = Palette::White;
			break;
		}
		if (data[num].name == userName) { color = Palette::Red; }
		cellFont(text).drawCenter(5 + titleFont.height + i * cellFont.height, color);
	}
	textFont(L"���j���[�ɖ߂�ɂ͂a�L�[�������Ă�������...").drawCenter(Window::Height() - textFont.height - 5);
}

// �X�R�A�{�[�h �L�^
void SBoard_Record()
{
	font1(L"�X�R�A�{�[�h�ɋL�^���閼�O����͂��Ă��������I").drawCenter(25);
	Input::GetCharsHelper(userName);
	if (userName.length > 10 && userName[userName.length - 1] != L'\n') { userName.erase(10, userName.length - 1); }
	font2(userName).draw(25, 25 + font1.height);
	if (userName.length > 0 && userName[userName.length - 1] == L'\n') { SceneMgr_ChangeScene(Scene_SBoard); }
}