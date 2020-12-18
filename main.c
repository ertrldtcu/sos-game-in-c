#include <stdio.h>
#include <stdlib.h>
#define boyut 12

void getNames(); // wants players names when game started
void drawScoreboard(); // draw scoreboard
void drawGameboard(); // draw gameboard
int takeInput(); // return 1 if did valid input, otherwise 0
int controlSOS(); // return 1 if scored, otherwise 0

char sos[boyut][boyut]; // save S and O
int scores[2] = { 0,0 }; // save players scores
int counter = 1; // round counter
int sRow, sCol; // save selected row and column
int currentPlayer = 0; // save current player, can be 0 or 1
char name[2][20]; // save player nicks

void main() {

	for (int i = 0; i < boyut; i++)
		for (int j = 0; j < boyut; j++)
			sos[i][j] = ' ';

	getNames();
	while (counter <= boyut * boyut) {
		system("cls");
		sRow = 0; sCol = 0;
		drawScoreboard();
		drawGameboard();
		int input = takeInput();
		if (input) {
			int point = controlSOS();
			if (!point) {
				printf("\xaf\xaf\xaf Sorry, you didn't get point! The turn passed to the other player!");
				getch();
				currentPlayer = (currentPlayer + 1) % 2;
			}
			else {
				scores[currentPlayer] = scores[currentPlayer] + 1;
				printf("\xaf\xaf\xaf Congratulations, you take point! Play again!");
				getch();
			}
			counter++;
		}
	}

	system("cls");
	printf("\xaf\xaf Game is over!! \xae\xae\n\n");
	if (scores[0] > scores[1]) printf("\xaf\xaf %s won with %d score!! \xae\xae\n\n", name[0], scores[0]);
	else if (scores[0] < scores[1]) printf("\xaf\xaf %s won with %d score!! \xae\xae\n\n", name[1], scores[1]);
	else printf("\xaf\xaf Game draw!! \xae\xae\n\n");
}

void getNames() {
	printf("Player 1: ");
	scanf("%s", &name[0][0]);
	printf("Player 2: ");
	scanf("%s", &name[1][0]);
}

void drawScoreboard() {
	printf("%s %d : %d %s\n\n", name[0], scores[0], scores[1], name[1]);
}

void drawGameboard() {
	int i, j;
	// top line
	for (i = 1; i < (boyut + 2) * 6 + 2; i++) {
		printf("\xdb");
	}
	printf("\n\xdb\xdb ");
	for (i = 0; i <= boyut; i++) {
		if (!i) printf("\xda\xc4\xc4\xc4\xc4\xc4\xc2");
		else if (i == boyut) printf("\xc4\xc4\xc4\xc4\xc4\xbf");
		else printf("\xc4\xc4\xc4\xc4\xc4\xc2");
	}
	// gameboard
	printf(" \xdb\xdb");
	for (i = 0; i <= boyut; i++) {
		printf("\n\xdb\xdb ");
		for (j = 0; j <= boyut; j++) {
			if (!i && !j) printf("\xb3     ");
			else if (!i && j == boyut) printf("\xb3 %2d  \xb3", j);
			else if (!i) printf("\xb3 %2d  ", j);
			else if (!j) printf("\xb3 %2d  \xb3", i);
			else if (sRow && sCol && sRow == i && sCol == j) printf(" \xdb\xdb\xdb \xb3");
			else printf("  %c  \xb3", sos[i - 1][j - 1]);
		}
		printf(" \xdb\xdb\n\xdb\xdb ");
		for (j = 0; j <= boyut; j++) {
			if (i == boyut && !j) printf("\xc0\xc4\xc4\xc4\xc4\xc4");
			else if (i == boyut) printf("\xc1\xc4\xc4\xc4\xc4\xc4");
			else if (!j) printf("\xc3\xc4\xc4\xc4\xc4\xc4");
			else printf("\xc5\xc4\xc4\xc4\xc4\xc4");
			if (i == boyut && j == boyut) printf("\xd9");
			else if (j == boyut) printf("\xb4");
		}
		printf(" \xdb\xdb");
	}
	// bottom line
	printf("\n");
	for (i = 1; i < (boyut + 2) * 6 + 2; i++) {
		printf("\xdb");
	}
}

int takeInput() {
	printf("\n\n\xaf Player turn: %s\n", name[currentPlayer]);
	printf("\xaf Row: ");
	scanf("%d", &sRow);
	printf("\xaf Column: ");
	scanf("%d", &sCol);
	if (!(sRow > 0 && sRow <= boyut && sCol > 0 && sCol <= boyut)) {
		printf("\xaf\xaf Invalid position!!\n\xaf\xaf Press any key to continue!!");
		getch();
		return 0;
	}
	switch (sos[sRow - 1][sCol - 1]) {

	case 'S':
	case 'O':   printf("\xaf\xaf Invalid position!!\n\xaf\xaf Press any key to continue!!");
		getch();
		return 0;

	default:    system("cls");
		drawScoreboard();
		drawGameboard();
		printf("\n\n\xaf Player turn: %s\n\xaf Row: %d\n\xaf Column: %d\n\xaf\xaf S/O? ", name[currentPlayer], sRow, sCol);
		char ch;
		scanf(" %c", &ch);
		switch (ch) {
		case 's':
		case 'S': sos[sRow - 1][sCol - 1] = 'S'; return 1;
		case 'o':
		case 'O': sos[sRow - 1][sCol - 1] = 'O'; return 1;
		}

		printf("\xaf\xaf Invalid letter!!\n\xaf\xaf Press any key to continue!!");
		getch();
		return 0;
	}
}

int controlSOS() {
	if (sos[sRow - 1][sCol - 1] == 'S') {
		if (sos[sRow - 3][sCol - 3] == 'S' && sos[sRow - 2][sCol - 2] == 'O') return 1;
		if (sos[sRow - 3][sCol - 1] == 'S' && sos[sRow - 2][sCol - 1] == 'O') return 1;
		if (sos[sRow - 3][sCol + 1] == 'S' && sos[sRow - 2][sCol] == 'O') return 1;
		if (sos[sRow - 1][sCol - 3] == 'S' && sos[sRow - 1][sCol - 2] == 'O') return 1;
		if (sos[sRow - 1][sCol + 1] == 'S' && sos[sRow - 1][sCol] == 'O') return 1;
		if (sos[sRow + 1][sCol - 3] == 'S' && sos[sRow][sCol - 2] == 'O') return 1;
		if (sos[sRow + 1][sCol - 1] == 'S' && sos[sRow][sCol - 1] == 'O') return 1;
		if (sos[sRow + 1][sCol + 1] == 'S' && sos[sRow][sCol] == 'O') return 1;
	}
	else {
		if (sos[sRow - 2][sCol - 2] == 'S' && sos[sRow][sCol] == 'S') return 1;
		if (sos[sRow - 2][sCol - 1] == 'S' && sos[sRow][sCol - 1] == 'S') return 1;
		if (sos[sRow - 2][sCol] == 'S' && sos[sRow][sCol - 2] == 'S') return 1;
		if (sos[sRow - 1][sCol - 2] == 'S' && sos[sRow - 1][sCol] == 'S') return 1;
	}
	return 0;
}
