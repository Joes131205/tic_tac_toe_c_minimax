#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define X 'X'
#define O 'O'
#define EMPTY ' '

void drawBoard(char board[3][3]);
char determineTurn(char board[3][3]);
char determineWinner(char set[]);
char checkWinning(char board[3][3]);
bool isTied(char board[3][3]);
void getBestMove(char board[3][3], int *row, int *col);
int utility(char board[3][3]);
int minimax(char board[3][3], bool isMaximizing);

int main()
{
    char board[3][3] = {{EMPTY, EMPTY, EMPTY},
                        {EMPTY, EMPTY, EMPTY},
                        {EMPTY, EMPTY, EMPTY}};

    char player[10];
    do
    {
        printf("Choose your player (X or O): ");
        scanf("%s", player);
    } while ((player[0] != X && player[0] != O) || strlen(player) != 1);

    char current = determineTurn(board);
    int row, col;

    while (true)
    {
        drawBoard(board);
        if (current == player[0])
        {
            // Player move
            printf("%c move (row, col) : ", current);
            scanf("%d %d", &row, &col);

            if (row < 1 || row > 3 || col < 1 || col > 3 || board[row - 1][col - 1] != EMPTY)
            {
                printf("Invalid move. Try again.\n");
                continue;
            }
            board[row - 1][col - 1] = current;
        }
        else
        {
            // AI MOVE
            getBestMove(board, &row, &col);
            board[row][col] = current;
        }

        if (checkWinning(board) != EMPTY)
        {
            drawBoard(board);
            printf("Player %c wins!\n", current);
            break;
        }
        else if (isTied(board))
        {
            drawBoard(board);
            printf("Draw!\n");
            break;
        }

        current = determineTurn(board);
    }

    return 0;
}

// Tic Tac Toe Mechanic
void drawBoard(char board[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf(" %c ", board[i][j]);
            if (j < 2)
            {
                printf("|");
            }
        }
        printf("\n");
        if (i < 2)
        {
            printf("---+---+---\n");
        }
    }
}

char determineTurn(char board[3][3])
{
    int x_count = 0;
    int o_count = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == X)
            {
                x_count++;
            }
            else if (board[i][j] == O)
            {
                o_count++;
            }
        }
    }
    if (x_count <= o_count)
    {
        return X;
    }
    else
    {
        return O;
    }
}

char determineWinner(char set[])
{
    if (set[0] != EMPTY && set[0] == set[1] && set[1] == set[2])
    {
        return set[0];
    }
    return EMPTY;
}

char checkWinning(char board[3][3])
{
    char winner;

    // Check rows
    for (int i = 0; i < 3; i++)
    {
        winner = determineWinner(board[i]);
        if (winner != EMPTY)
        {
            return winner;
        }
    }

    // Check columns
    for (int i = 0; i < 3; i++)
    {
        char column[3] = {board[0][i], board[1][i], board[2][i]};
        winner = determineWinner(column);
        if (winner != EMPTY)
        {
            return winner;
        }
    }

    // Check diagonals
    char diag1[3] = {board[0][0], board[1][1], board[2][2]};
    winner = determineWinner(diag1);
    if (winner != EMPTY)
    {
        return winner;
    }

    char diag2[3] = {board[0][2], board[1][1], board[2][0]};
    winner = determineWinner(diag2);
    if (winner != EMPTY)
    {
        return winner;
    }

    // No winner
    return EMPTY;
}

bool isTied(char board[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == EMPTY)
            {
                return false;
            }
        }
    }
    return true;
}

// AI Mechanic

void getBestMove(char board[3][3], int *row, int *col)
{
    int bestScore = -1000;
    *row = -1;
    *col = -1;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == EMPTY)
            {
                board[i][j] = determineTurn(board); // Assume AI is playing as X
                int score = minimax(board, false);
                board[i][j] = EMPTY;
                if (score > bestScore)
                {
                    bestScore = score;
                    *row = i;
                    *col = j;
                }
            }
        }
    }
}

int utility(char board[3][3])
{
    char winner = checkWinning(board);
    if (winner == X)
    {
        return 1;
    }
    else if (winner == O)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

int minimax(char board[3][3], bool isMaximizing)
{
    char winner = checkWinning(board);
    if (winner == X)
        return 1;
    if (winner == O)
        return -1;
    if (isTied(board))
        return 0;

    if (isMaximizing)
    {
        int bestScore = -1000;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board[i][j] == EMPTY)
                {
                    board[i][j] = X;
                    int score = minimax(board, false);
                    board[i][j] = EMPTY;
                    bestScore = (score > bestScore) ? score : bestScore;
                }
            }
        }
        return bestScore;
    }
    else
    {
        int bestScore = 1000;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board[i][j] == EMPTY)
                {
                    board[i][j] = O;
                    int score = minimax(board, true);
                    board[i][j] = EMPTY;
                    bestScore = (score < bestScore) ? score : bestScore;
                }
            }
        }
        return bestScore;
    }
}
