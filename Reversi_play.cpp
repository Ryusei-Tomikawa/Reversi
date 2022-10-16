#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string>
#include <iostream>
#include <Windows.h>

#define BOARD_WIDTH 10
#define BOARD_HEIGHT 10
#define STONE_MAX 8

#define BOARD_OUT -1
#define EMPTY 0
#define WHITE 1
#define BLACK 2

#define BLACK_TURN 3
#define WHITE_TURN 4

//間違えた時キャンセル前の状態に戻すこと

/***** グローバル変数 *****/

// 盤のマス目の数
int board[BOARD_HEIGHT][BOARD_WIDTH];

// ８か所のベクトル(カーソル座標から上から時計回り) 
int x[STONE_MAX] = { -1, -1, 0, 1, 1, 1, 0, -1 };
int y[STONE_MAX] = { 0, 1, 1, 1, 0, -1, -1, -1 };

// ターンを切り替えるためのフラグ
bool change_turn = false;

// ひっくり返した時のフラグ
bool end_reverse_ = false;

/*************************/


//盤初期化関数
void init_board()
{
	for (int x = 0; x < BOARD_HEIGHT; x++)
	{
		for (int y = 0; y < BOARD_WIDTH; y++)
		{
			board[x][y] = EMPTY;

			//盤の外
			//board[x][y];
			board[0][y] = BOARD_OUT;
			board[x][0] = BOARD_OUT;
			board[BOARD_HEIGHT - 1][y] = BOARD_OUT;
			board[x][BOARD_WIDTH - 1] = BOARD_OUT;
		}
		printf("\n");
	}

	//実際のゲーム初期化
	board[4][5] = WHITE;
	board[5][4] = WHITE;
	board[4][4] = BLACK;
	board[5][5] = BLACK;

}

//石をひっくり返す関数
void reverse_stone(int reverseX_, int reverseY_, int& turn_color_, int vec)
{

	while (1)
	{

		reverseX_ += x[vec];
		reverseY_ += y[vec];

		/*************************************黒色のターンの場合******************************************/
		if (turn_color_ == BLACK_TURN && board[reverseX_][reverseY_] == WHITE)
		{
			//printf("黒色にひっくり返します.\n");
			board[reverseX_][reverseY_] = BLACK;
			continue;

		}
		else if (turn_color_ == BLACK_TURN && board[reverseX_][reverseY_] == BLACK)
		{
			//printf("黒にひっくり返しを終了します。\n");
			end_reverse_ = true;
			break;
		}
		/*************************************************************************************************/

		/*************************************白色のターンの場合******************************************/
		if (turn_color_ == WHITE_TURN && board[reverseX_][reverseY_] == BLACK)
		{
			//printf("白色にひっくり返します.\n");
			board[reverseX_][reverseY_] = WHITE;
			continue;
		}
		else if (turn_color_ == WHITE_TURN && board[reverseX_][reverseY_] == WHITE)
		{
			//printf("白にひっくり返しを終了します。\n");
			end_reverse_ = true;
			break;
		}
		/*************************************************************************************************/
	}

}

// 石を確認する関数 
void check_stone(int cursorX_, int cursorY_, int vector, int& turn_color)
{

	// ひっくり返す用のフラグ
	bool reverse_ = false;

	//確認する石の座標
	int checkX_, checkY_ = 0;

	checkX_ = cursorX_;
	checkY_ = cursorY_;

	while (1)
	{
		checkX_ += x[vector];
		checkY_ += y[vector];

		/****************************************エラー処理************************************************/
		// 空だった場合
		if (board[checkX_][checkY_] == EMPTY)
		{
			//printf("空です。\n");
			break;
		}
		// 盤よりも外だった場合
		else if (checkX_ < 1 || checkX_ >= STONE_MAX || checkY_ < 1 || checkY_ >= STONE_MAX)
		{
			//printf("盤よりも外です。\n");
			break;
		}
		/*************************************************************************************************/


		/*************************************黒色のターンの場合******************************************/
		if (turn_color == BLACK_TURN && board[checkX_][checkY_] == WHITE)
		{
			//printf("白色がありました。\n");
			reverse_ = true;
			continue;
		}
		else if (reverse_ && turn_color == BLACK_TURN && board[checkX_][checkY_] == BLACK)
		{
			reverse_ = false;

			// 置くときのエラー処理
			// 既に置いてある石の上は置けない
			if (board[cursorX_][cursorY_] == BLACK || board[cursorX_][cursorY_] == WHITE)
				break;
			else if (board[cursorX_][cursorY_] == EMPTY)
				board[cursorX_][cursorY_] = BLACK;

			// 0.5秒間待機
			Sleep(0.5 * 1000);

			reverse_stone(cursorX_, cursorY_, turn_color, vector);
			break;
		}
		/*************************************************************************************************/

		/*************************************白色のターンの場合******************************************/
		if (turn_color == WHITE_TURN && board[checkX_][checkY_] == BLACK)
		{
			//printf("黒色がありました。\n");
			reverse_ = true;
			continue;
		}
		else if (reverse_ && turn_color == WHITE_TURN && board[checkX_][checkY_] == WHITE)
		{
			reverse_ = false;

			// 置くときのエラー処理
			// 既に置いてある石の上は置けない
			if (board[cursorX_][cursorY_] == BLACK || board[cursorX_][cursorY_] == WHITE)
				break;
			else if (board[cursorX_][cursorY_] == EMPTY)
				board[cursorX_][cursorY_] = WHITE;

			// 0.5秒間待機
			Sleep(0.5 * 1000);
			reverse_stone(cursorX_, cursorY_, turn_color, vector);
			break;
		}
		/************************************************************************************************/

		// なかった場合(同色の時)
		else
		{
			//printf("石を置く場所がありません。\n");
			break;
		}
	}
}

bool play_end()
{
	int black_stone = 0;
	int white_stone = 0;
	int sum_stone = 0;

	for (int x = 1; x < BOARD_HEIGHT - 1; x++)
	{
		for (int y = 1; y < BOARD_WIDTH - 1; y++)
		{
			if (board[x][y] == BLACK)
				black_stone++;
			else if (board[x][y] == WHITE)
				white_stone++;
		}
	}


	// 黒白の石の合計
	sum_stone = black_stone + white_stone;

	if (sum_stone == STONE_MAX * STONE_MAX)
	{
		printf("決着がつきました！!!\n");
		printf("勝負の結果...\n");

		// 3秒間待機
		Sleep(3 * 1000);


		if (black_stone > white_stone)
			printf("黒色の勝利です！ おめでとうございます！\n");
		else if (black_stone < white_stone)
			printf("白色の勝利です！ おめでとうございます！\n");
		else
			printf("同点でした! お疲れ様でした！\n");

		printf("結果        黒色〇:%d個　白色●:%d個\n", black_stone, white_stone);

		printf("オセロゲームを終了します.\n");

		// 7秒間待機
		Sleep(7 * 1000);

		return true;
	}
	else
		return false;
}

// メイン関数
int main(int argc, char* argv[])
{
	printf("\n");
	printf("オセロゲームを開始します!\n");
	printf("プレイヤー1は黒、プレイヤー２は白です。\n");
	printf("1 or 2を入力してください。(黒〇:1, 白●:2)\n");

	// ターンを数値で示した変数 黒:3 白:4
	int turn_;

	// ターンの色を表示するための変数
	std::string  turn_names;

	while (1)
	{
		char num = getchar();

		if (num == '1')
		{
			turn_names = "黒";
			turn_ = BLACK_TURN;
			break;
		}
		else if (num == '2')
		{
			turn_names = "白";
			turn_ = WHITE_TURN;
			break;
		}
		else
			printf("どちらか選んでください。\n");
	}

	std::cout << "あなたは" << turn_names << "色です." << std::endl;
	printf("\n");
	printf("それではオセロスタート！\n");

	// 2秒間待機
	Sleep(2 * 1000);

	//盤初期化
	init_board();

	//動作させる際のカーソル変数
	int cursorX = 1;
	int cursorY = 1;

	while (1)
	{
		//画面リセットコマンド
		system("cls");

		// 盤表示
		for (int x = 0; x < BOARD_WIDTH; x++)
		{
			for (int y = 0; y < BOARD_HEIGHT; y++)
			{
				if (x == cursorX && y == cursorY)
					printf("◎");
				else
					switch (board[x][y])
					{
					case BOARD_OUT:
						printf("外");
						break;
					case EMPTY:
						printf("・");
						break;
					case BLACK:
						printf("〇");
						break;
					case WHITE:
						printf("●");
						break;
					}
			}
			printf("\n");
		}

		printf("\n");

		std::cout << "次は" << turn_names << "のターンです." << std::endl;

		printf("\n");
		printf("\n");

		printf("i:上へ, l:右へ, j:左へ, ,:下へ 移動します。\n");
		printf("石を置くときは ”k ”を押してください。\n");
		printf("石が置けない場合は ”n ”を押してください。\n");

		//ユーザによるカーソル動作
		char word = getchar();

		if (word == 'i')
			cursorX--;
		else if (word == ',')
			cursorX++;
		else if (word == 'l')
			cursorY++;
		else if (word == 'j')
			cursorY--;
		else if (word == 'k') // 石を置く　＋　ターンが切り替わる
		{
			// 8箇所チェックする
			for (int k = 0; k < STONE_MAX; k++)
			{
				// 置くことができるか確認する関数
				check_stone(cursorX, cursorY, k, turn_);

				// 8箇所目チェック終了した時
				if (k == STONE_MAX - 1)
					change_turn = true;
			}

			// 0.5秒間待機
			Sleep(0.5 * 1000);

			// 次ターンで色を切り替える
			if (turn_ == BLACK_TURN && change_turn && end_reverse_)
			{
				// ターンを白色切り替える
				turn_ = WHITE_TURN;
				turn_names = "白";
				change_turn = false;
				end_reverse_ = false;
			}
			else if (turn_ == WHITE_TURN && change_turn && end_reverse_)
			{
				turn_ = BLACK_TURN;
				turn_names = "黒";
				change_turn = false;
				end_reverse_ = false;
			}

		}
		// 置く場所がなかった場合
		else if (word == 'n')
		{

			// 次ターンで色を切り替える
			if (turn_ == BLACK_TURN)
			{
				// ターンを白色切り替える
				turn_ = WHITE_TURN;
				turn_names = "白";
				change_turn = false;
				end_reverse_ = false;
			}
			else if (turn_ == WHITE_TURN)
			{
				turn_ = BLACK_TURN;
				turn_names = "黒";
				change_turn = false;
				end_reverse_ = false;
			}
		}

		// 8×8内にカーソルが常にあるためにするための処理
		if (cursorX < 1 || cursorX > BOARD_HEIGHT - 2)
			cursorX = 1;
		else if (cursorY < 1 || cursorY > BOARD_WIDTH - 2)
			cursorY = 1;

		// 判定する関数
		if (play_end())
			break;

	}

	return 0;
}
