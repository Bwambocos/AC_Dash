// include
#include <Siv3D.hpp>
#include "SceneMgr.h"
#include "Menu.h"

// �O���[�o���ϐ�
static Texture ac, wa;
static int32 draw_ac_x, draw_wa_x;

// ���j���[ ������
void Menu_Init()
{
	// �w�i ������
	{
		ac = Texture(L"data\\Menu\\ac.png");
		wa = Texture(L"data\\Menu\\wa.png");
		draw_ac_x = -ac.width;
		draw_wa_x = Window::Width() + wa.width;
	}
}

// ���j���[  �X�V
void Menu_Update()
{
	// �w�i �X�V
	{
		draw_ac_x = (draw_ac_x >= Window::Width() ? -ac.width : draw_ac_x + 3);
		draw_wa_x = (draw_wa_x < -wa.width ? Window::Width() + wa.width : draw_wa_x - 2);
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
}