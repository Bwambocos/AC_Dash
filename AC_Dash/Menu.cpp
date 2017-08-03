// include
#include <Siv3D.hpp>
#include "SceneMgr.h"
#include "Menu.h"

// グローバル変数
static Texture ac, wa;
static int32 draw_ac_x, draw_wa_x;

// メニュー 初期化
void Menu_Init()
{
	// 背景 初期化
	{
		ac = Texture(L"data\\Menu\\ac.png");
		wa = Texture(L"data\\Menu\\wa.png");
		draw_ac_x = -ac.width;
		draw_wa_x = Window::Width() + wa.width;
	}
}

// メニュー  更新
void Menu_Update()
{
	// 背景 更新
	{
		draw_ac_x = (draw_ac_x >= Window::Width() ? -ac.width : draw_ac_x + 3);
		draw_wa_x = (draw_wa_x < -wa.width ? Window::Width() + wa.width : draw_wa_x - 2);
	}
}

// メニュー  描画
void Menu_Draw()
{
	// 背景 描画
	{
		ac.draw(draw_ac_x, Window::Center().y - ac.height);
		wa.draw(draw_wa_x, Window::Center().y);
	}
}