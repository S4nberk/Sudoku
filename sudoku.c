#include <stdio.h> 
#include <stdbool.h>
#include "sudoku_puzzles.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define EASY_COUNT   (sizeof(easy_puzzles)   / sizeof(easy_puzzles[0]))
#define NORMAL_COUNT (sizeof(medium_puzzles) / sizeof(medium_puzzles[0]))
#define HARD_COUNT   (sizeof(hard_puzzles)   / sizeof(hard_puzzles[0]))

static void printSudoku(int source[9][9]) {
	for (int row = 0; row < 9; row++) {
		if (row % 3 == 0 && row != 0)
			printf("---------------------\n");

		for (int col = 0; col < 9; col++) {
			if (col % 3 == 0 && col != 0) {
				printf("|");
			}
			printf("%d ", source[row][col]);
		}
		printf("\n");
	}
}

static bool isValid(int source[9][9], int row, int col, int num) {
	for (int x = 0; x < 9; x++) {
		if (source[row][x] == num)
			return false;
	}
	for (int y = 0; y < 9; y++) {
		if (source[y][col] == num)
			return false;
	}

	int startCol = col - col % 3;
	int startRow = row - row % 3;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (source[startRow + i][startCol + j] == num)
				return false;
		}
	}
	return true;
}

static bool solveSudoku(int source[9][9]) {
	for (int row = 0; row < 9; row++) {
		for (int col = 0; col < 9; col++) {
			if (source[row][col] == 0) {
				for (int num = 1; num <= 9; num++) {
					if (isValid(source, row, col, num)) {
						source[row][col] = num;
						if (solveSudoku(source))
							return true;
						else source[row][col] = 0;
					}
				}
				return false;
			}
		}
	}
	return true;
}

int language = 1;//1 Turkish - 2 English
static const char* getText(const char* key) {
	if (language == 1) {
		if (strcmp(key, "welcome") == 0) return (const char*)"Sudoku'ya hosgeldiniz! ";
		if (strcmp(key, "play_or_solve") == 0) return (const char*)"Oynamak (1) mi istersiniz yoksa cozdurmek (2) mi?";
		if (strcmp(key, "invalid_input") == 0) return (const char*)"Gecersiz giris!";
		if (strcmp(key, "choose_difficulty") == 0) return (const char*)"Zorlugu seciniz: Kolay(1) - Normal(2) - Zor(3)";
		if (strcmp(key, "toSolve_or_solved") == 0) return (const char*)"Cozmek icin \"1\" cozumu gormek icin \"2\" yaziniz: \n> ";
		if (strcmp(key, "sol_found") == 0) return (const char*)"Cozum bulundu: \n";
		if (strcmp(key, "no_sol_found") == 0) return (const char*)"Cozum bulunamadi. \n";
		if (strcmp(key, "i_want_to_solve") == 0) return (const char*)"Yerlestirmek istediginiz sayinin satirini, sutununu ve sayiyi yaziniz: (Ornek kullanim: >1 3 5) (Cikis icin: >0 0 0)\n>";
		if (strcmp(key, "game_exit") == 0) return (const char*)"Sudokuyu simdilik terk ediyorsun... Ama geri donecegini biliyoruz :)";
		if (strcmp(key, "cannot_change") == 0) return (const char*)"Bu hucre degistirilemez. \n";
		if (strcmp(key, "num_true") == 0) return (const char*)"Dogru!\n";
		if (strcmp(key, "num_false") == 0) return (const char*)"Yanlis sayi! Tekrar deneyiniz. ";
		if (strcmp(key, "congratulations") == 0) return (const char*)"Tebrikler! Kazandiniz.\n";
		if (strcmp(key, "mistakes") == 0) return (const char*)"Hatalariniz";
		if (strcmp(key, "game_over") == 0) return (const char*)"3 hata yaptiniz. Oyun bitti.";
	}
	else if (language == 2) {
		if (strcmp(key, "welcome") == 0) return (const char*)"Welcome to Sudoku! ";
		if (strcmp(key, "play_or_solve") == 0) return (const char*)"Would you like to play (1) Sudoku or have it solved for you (2)?";
		if (strcmp(key, "invalid_input") == 0) return (const char*)"Invalid input!";
		if (strcmp(key, "choose_difficulty") == 0) return (const char*)"Select difficulty: Easy(1) - Normal(2) - Hard(3)";
		if (strcmp(key, "toSolve_or_solved") == 0) return (const char*)"Type \"1\" to solve, type \"2\" to see the solution: \n>";
		if (strcmp(key, "sol_found") == 0) return (const char*)"Solution found: \n";
		if (strcmp(key, "no_sol_found") == 0) return (const char*)"No solution found. \n";
		if (strcmp(key, "i_want_to_solve") == 0) return (const char*)"Enter the row, column, and number you want to place: (Example: >1 3 5) (To exit: >0 0 0)\n>";
		if (strcmp(key, "game_exit") == 0) return (const char*)"Leaving the Sudoku field... But we know you'll be back :)";
		if (strcmp(key, "cannot_change") == 0) return (const char*)"This cell can't be changed. \n";
		if (strcmp(key, "num_true") == 0) return (const char*)"Correct \n";
		if (strcmp(key, "num_false") == 0) return (const char*)"Wrong number! Try again. ";
		if (strcmp(key, "congratulations") == 0) return (const char*)"Congratulations! You won.\n";
		if (strcmp(key, "mistakes") == 0) return (const char*)"Your mistakes";
		if (strcmp(key, "game_over") == 0) return (const char*)"You made 3 mistakes. Game over";
	}
	return "Bilinmeyen anahtar!";
}

static void selectRandomSudoku(int difficulty, int source[9][9]);

static void copyBoard(int destination[9][9], int source[9][9]);

static void playSudoku(int board[9][9], int solution[9][9], int source[9][9]);
static int isBoardComplete(int source[9][9], int board[9][9]);
int board[9][9];
int solution[9][9];
int source[9][9];
int main() {
	int language_choice;
	printf("[DIL SECINIZ / SELECT LANGUAGE]\n");
	printf("1. Turkce\n");
	printf("2. English\n");
	printf("> ");
    scanf_s("%d", &language_choice);
	if (language_choice == 1 || language_choice == 2) {
		language = language_choice;
	}
	else {
		printf("%s\n", getText("invalid_input"));
		return -1;
	}

	int p_or_s = 0; //1 play - 2 solve
	printf("%s", getText("welcome"));
	printf("%s", getText("play_or_solve"));
	printf("\n> ");
	scanf_s("%d", &p_or_s);
	if (p_or_s != 1 && p_or_s != 2) {
		printf("%s\n", getText("invalid_input"));
		return -1;
	}
	
	if (p_or_s == 1) {
		int difficulty = 1; // 1 easy - 2 normal - 3 hard
		printf("%s", getText("choose_difficulty"));
		printf("\n> ");
		scanf_s("%d", &difficulty);
		if (difficulty != 1 && difficulty != 2 && difficulty != 3) {
			printf("%s\n", getText("invalid_input"));
			return -1;
		}
		selectRandomSudoku(difficulty, source);
		printSudoku(source);
		int ch_toSolve;
		printf("%s", getText("toSolve_or_solved"));
		scanf_s("%d", &ch_toSolve);
		if (ch_toSolve != 1 && ch_toSolve != 2) /* 1 to solve - 2 solved */ {
			printf("%s\n", getText("invalid_input"));
			return -1;
		}
		if (ch_toSolve == 1 /*user wants to solve*/) {
			copyBoard(solution, source);
			solveSudoku(solution);
			copyBoard(board, source);
			playSudoku(board, solution, source);
		}
		else {
			solveSudoku(source);
			if (solveSudoku(source)) {
				printf("%s",getText("sol_found"));
				printSudoku(source);
			}
			else {
				printf("%s",getText("no_sol_found"));
			}
		}
	}
	else {
		for (int i = 0; i < 9; i++) {
			printf("Satır %d için 9 sayı gir (0 boş): ", i + 1);
			for (int j = 0; j < 9; j++) {
				scanf("%d", &board[i][j]);
			}
		}

	}
	
	/*int source[9][9];

	if (solveSudoku(source)) {
		printf("Cozum bulundu:\n");
		printSudoku(source);
	}
	else {
		printf("Cozum bulunamadi.\n");
	} */
	return 0;
}

void selectRandomSudoku(int difficulty, int source[9][9]) {
	srand((unsigned int)time(NULL));
	int index;
	switch (difficulty) {
	case 1:
		index = rand() % EASY_COUNT;
			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 9; j++) {
					source[i][j] = easy_puzzles[index][i][j];
				}
			}
		break;
	case 2:
		index = rand() % NORMAL_COUNT;
			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 9; j++) {
					source[i][j] = medium_puzzles[index][i][j];
				}
			}
		break;
	case 3:
		index = rand() % HARD_COUNT;
			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 9; j++) {
					source[i][j] = hard_puzzles[index][i][j];
				}
			}
		break;
	default: printf("ERROR");
		break;
	}
}

void copyBoard(int destination[9][9], int source[9][9]) {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			destination[i][j] = source[i][j];
		}
	}
}

void playSudoku(int board[9][9], int solution[9][9], int source[9][9]) {
	int row, col, num;
	int mistakes = 0;
	while (1) {
		printf("%s", getText("i_want_to_solve"));
		scanf_s("%d %d %d", &row, &col, &num);
		if (row == 0 && col == 0 && num == 0) {
			printf("%s", getText("game_exit"));
			break;
		}
		row--; col--;
		if (row < 0 || row > 8 || col < 0 || col > 8 || num < 1 || num > 9) {
			printf("%s\n", getText("invalid_input"));
			continue;
		}
		if (source[row][col] != 0) {
			printf("%s\n", getText("cant_change"));
			continue;
		}
		if (solution[row][col] == num) {
			board[row][col] = num;
			printf("%s", getText("num_true"));
			if (isBoardComplete(solution, board)) {
				printf("%s", getText("congratulations"));
				break;
			}
		}
		else {
			printf("%s", getText("num_false"));
			mistakes++;
			printf("%s (%d/3)\n", getText("mistakes"),mistakes);
			if (mistakes >= 3) {
				printf("%s", getText("game_over"));
				break;
			}
		}
		printSudoku(board);
	}
}

int isBoardComplete(int solution[9][9], int board[9][9]) {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (board[i][j] != solution[i][j]) {
				return 0;
			}
		}
	}
	return 1;
}
