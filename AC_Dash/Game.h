#pragma once
#include <Siv3D.hpp>

// ゲーム 初期化
void Game_Init();

// ゲーム 更新
void Game_Update();

// ゲーム 描画
void Game_Draw();

// ゲーム説明 描画
void Game_Expl();

// ゲーム終了 描画
void Game_End();

// ゲーム スコア取得
int64 Game_getScore();