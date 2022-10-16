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

//�ԈႦ�����L�����Z���O�̏�Ԃɖ߂�����

/***** �O���[�o���ϐ� *****/

// �Ղ̃}�X�ڂ̐�
int board[BOARD_HEIGHT][BOARD_WIDTH];

// �W�����̃x�N�g��(�J�[�\�����W����ォ�玞�v���) 
int x[STONE_MAX] = { -1, -1, 0, 1, 1, 1, 0, -1 };
int y[STONE_MAX] = { 0, 1, 1, 1, 0, -1, -1, -1 };

// �^�[����؂�ւ��邽�߂̃t���O
bool change_turn = false;

// �Ђ�����Ԃ������̃t���O
bool end_reverse_ = false;

/*************************/


//�Տ������֐�
void init_board()
{
	for (int x = 0; x < BOARD_HEIGHT; x++)
	{
		for (int y = 0; y < BOARD_WIDTH; y++)
		{
			board[x][y] = EMPTY;

			//�Ղ̊O
			//board[x][y];
			board[0][y] = BOARD_OUT;
			board[x][0] = BOARD_OUT;
			board[BOARD_HEIGHT - 1][y] = BOARD_OUT;
			board[x][BOARD_WIDTH - 1] = BOARD_OUT;
		}
		printf("\n");
	}

	//���ۂ̃Q�[��������
	board[4][5] = WHITE;
	board[5][4] = WHITE;
	board[4][4] = BLACK;
	board[5][5] = BLACK;

}

//�΂��Ђ�����Ԃ��֐�
void reverse_stone(int reverseX_, int reverseY_, int& turn_color_, int vec)
{

	while (1)
	{

		reverseX_ += x[vec];
		reverseY_ += y[vec];

		/*************************************���F�̃^�[���̏ꍇ******************************************/
		if (turn_color_ == BLACK_TURN && board[reverseX_][reverseY_] == WHITE)
		{
			//printf("���F�ɂЂ�����Ԃ��܂�.\n");
			board[reverseX_][reverseY_] = BLACK;
			continue;

		}
		else if (turn_color_ == BLACK_TURN && board[reverseX_][reverseY_] == BLACK)
		{
			//printf("���ɂЂ�����Ԃ����I�����܂��B\n");
			end_reverse_ = true;
			break;
		}
		/*************************************************************************************************/

		/*************************************���F�̃^�[���̏ꍇ******************************************/
		if (turn_color_ == WHITE_TURN && board[reverseX_][reverseY_] == BLACK)
		{
			//printf("���F�ɂЂ�����Ԃ��܂�.\n");
			board[reverseX_][reverseY_] = WHITE;
			continue;
		}
		else if (turn_color_ == WHITE_TURN && board[reverseX_][reverseY_] == WHITE)
		{
			//printf("���ɂЂ�����Ԃ����I�����܂��B\n");
			end_reverse_ = true;
			break;
		}
		/*************************************************************************************************/
	}

}

// �΂��m�F����֐� 
void check_stone(int cursorX_, int cursorY_, int vector, int& turn_color)
{

	// �Ђ�����Ԃ��p�̃t���O
	bool reverse_ = false;

	//�m�F����΂̍��W
	int checkX_, checkY_ = 0;

	checkX_ = cursorX_;
	checkY_ = cursorY_;

	while (1)
	{
		checkX_ += x[vector];
		checkY_ += y[vector];

		/****************************************�G���[����************************************************/
		// �󂾂����ꍇ
		if (board[checkX_][checkY_] == EMPTY)
		{
			//printf("��ł��B\n");
			break;
		}
		// �Ղ����O�������ꍇ
		else if (checkX_ < 1 || checkX_ >= STONE_MAX || checkY_ < 1 || checkY_ >= STONE_MAX)
		{
			//printf("�Ղ����O�ł��B\n");
			break;
		}
		/*************************************************************************************************/


		/*************************************���F�̃^�[���̏ꍇ******************************************/
		if (turn_color == BLACK_TURN && board[checkX_][checkY_] == WHITE)
		{
			//printf("���F������܂����B\n");
			reverse_ = true;
			continue;
		}
		else if (reverse_ && turn_color == BLACK_TURN && board[checkX_][checkY_] == BLACK)
		{
			reverse_ = false;

			// �u���Ƃ��̃G���[����
			// ���ɒu���Ă���΂̏�͒u���Ȃ�
			if (board[cursorX_][cursorY_] == BLACK || board[cursorX_][cursorY_] == WHITE)
				break;
			else if (board[cursorX_][cursorY_] == EMPTY)
				board[cursorX_][cursorY_] = BLACK;

			// 0.5�b�ԑҋ@
			Sleep(0.5 * 1000);

			reverse_stone(cursorX_, cursorY_, turn_color, vector);
			break;
		}
		/*************************************************************************************************/

		/*************************************���F�̃^�[���̏ꍇ******************************************/
		if (turn_color == WHITE_TURN && board[checkX_][checkY_] == BLACK)
		{
			//printf("���F������܂����B\n");
			reverse_ = true;
			continue;
		}
		else if (reverse_ && turn_color == WHITE_TURN && board[checkX_][checkY_] == WHITE)
		{
			reverse_ = false;

			// �u���Ƃ��̃G���[����
			// ���ɒu���Ă���΂̏�͒u���Ȃ�
			if (board[cursorX_][cursorY_] == BLACK || board[cursorX_][cursorY_] == WHITE)
				break;
			else if (board[cursorX_][cursorY_] == EMPTY)
				board[cursorX_][cursorY_] = WHITE;

			// 0.5�b�ԑҋ@
			Sleep(0.5 * 1000);
			reverse_stone(cursorX_, cursorY_, turn_color, vector);
			break;
		}
		/************************************************************************************************/

		// �Ȃ������ꍇ(���F�̎�)
		else
		{
			//printf("�΂�u���ꏊ������܂���B\n");
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


	// �����̐΂̍��v
	sum_stone = black_stone + white_stone;

	if (sum_stone == STONE_MAX * STONE_MAX)
	{
		printf("���������܂����I!!\n");
		printf("�����̌���...\n");

		// 3�b�ԑҋ@
		Sleep(3 * 1000);


		if (black_stone > white_stone)
			printf("���F�̏����ł��I ���߂łƂ��������܂��I\n");
		else if (black_stone < white_stone)
			printf("���F�̏����ł��I ���߂łƂ��������܂��I\n");
		else
			printf("���_�ł���! �����l�ł����I\n");

		printf("����        ���F�Z:%d�@���F��:%d��\n", black_stone, white_stone);

		printf("�I�Z���Q�[�����I�����܂�.\n");

		// 7�b�ԑҋ@
		Sleep(7 * 1000);

		return true;
	}
	else
		return false;
}

// ���C���֐�
int main(int argc, char* argv[])
{
	printf("\n");
	printf("�I�Z���Q�[�����J�n���܂�!\n");
	printf("�v���C���[1�͍��A�v���C���[�Q�͔��ł��B\n");
	printf("1 or 2����͂��Ă��������B(���Z:1, ����:2)\n");

	// �^�[���𐔒l�Ŏ������ϐ� ��:3 ��:4
	int turn_;

	// �^�[���̐F��\�����邽�߂̕ϐ�
	std::string  turn_names;

	while (1)
	{
		char num = getchar();

		if (num == '1')
		{
			turn_names = "��";
			turn_ = BLACK_TURN;
			break;
		}
		else if (num == '2')
		{
			turn_names = "��";
			turn_ = WHITE_TURN;
			break;
		}
		else
			printf("�ǂ��炩�I��ł��������B\n");
	}

	std::cout << "���Ȃ���" << turn_names << "�F�ł�." << std::endl;
	printf("\n");
	printf("����ł̓I�Z���X�^�[�g�I\n");

	// 2�b�ԑҋ@
	Sleep(2 * 1000);

	//�Տ�����
	init_board();

	//���삳����ۂ̃J�[�\���ϐ�
	int cursorX = 1;
	int cursorY = 1;

	while (1)
	{
		//��ʃ��Z�b�g�R�}���h
		system("cls");

		// �Օ\��
		for (int x = 0; x < BOARD_WIDTH; x++)
		{
			for (int y = 0; y < BOARD_HEIGHT; y++)
			{
				if (x == cursorX && y == cursorY)
					printf("��");
				else
					switch (board[x][y])
					{
					case BOARD_OUT:
						printf("�O");
						break;
					case EMPTY:
						printf("�E");
						break;
					case BLACK:
						printf("�Z");
						break;
					case WHITE:
						printf("��");
						break;
					}
			}
			printf("\n");
		}

		printf("\n");

		std::cout << "����" << turn_names << "�̃^�[���ł�." << std::endl;

		printf("\n");
		printf("\n");

		printf("i:���, l:�E��, j:����, ,:���� �ړ����܂��B\n");
		printf("�΂�u���Ƃ��� �hk �h�������Ă��������B\n");
		printf("�΂��u���Ȃ��ꍇ�� �hn �h�������Ă��������B\n");

		//���[�U�ɂ��J�[�\������
		char word = getchar();

		if (word == 'i')
			cursorX--;
		else if (word == ',')
			cursorX++;
		else if (word == 'l')
			cursorY++;
		else if (word == 'j')
			cursorY--;
		else if (word == 'k') // �΂�u���@�{�@�^�[�����؂�ւ��
		{
			// 8�ӏ��`�F�b�N����
			for (int k = 0; k < STONE_MAX; k++)
			{
				// �u�����Ƃ��ł��邩�m�F����֐�
				check_stone(cursorX, cursorY, k, turn_);

				// 8�ӏ��ڃ`�F�b�N�I��������
				if (k == STONE_MAX - 1)
					change_turn = true;
			}

			// 0.5�b�ԑҋ@
			Sleep(0.5 * 1000);

			// ���^�[���ŐF��؂�ւ���
			if (turn_ == BLACK_TURN && change_turn && end_reverse_)
			{
				// �^�[���𔒐F�؂�ւ���
				turn_ = WHITE_TURN;
				turn_names = "��";
				change_turn = false;
				end_reverse_ = false;
			}
			else if (turn_ == WHITE_TURN && change_turn && end_reverse_)
			{
				turn_ = BLACK_TURN;
				turn_names = "��";
				change_turn = false;
				end_reverse_ = false;
			}

		}
		// �u���ꏊ���Ȃ������ꍇ
		else if (word == 'n')
		{

			// ���^�[���ŐF��؂�ւ���
			if (turn_ == BLACK_TURN)
			{
				// �^�[���𔒐F�؂�ւ���
				turn_ = WHITE_TURN;
				turn_names = "��";
				change_turn = false;
				end_reverse_ = false;
			}
			else if (turn_ == WHITE_TURN)
			{
				turn_ = BLACK_TURN;
				turn_names = "��";
				change_turn = false;
				end_reverse_ = false;
			}
		}

		// 8�~8���ɃJ�[�\������ɂ��邽�߂ɂ��邽�߂̏���
		if (cursorX < 1 || cursorX > BOARD_HEIGHT - 2)
			cursorX = 1;
		else if (cursorY < 1 || cursorY > BOARD_WIDTH - 2)
			cursorY = 1;

		// ���肷��֐�
		if (play_end())
			break;

	}

	return 0;
}
