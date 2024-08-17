#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define X 'X'
#define O 'O'
#define EMPTY ' '

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
    if ((x_count == 0 && o_count == 0) || o_count > x_count || o_count == x_count)
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

        printf("%c move (row, col) : ", current);
        scanf("%d %d", &row, &col);

        if (row < 1 || row > 3 || col < 1 || col > 3 || board[row - 1][col - 1] != EMPTY)
        {
            continue;
        }
        board[row - 1][col - 1] = current;

        if (checkWinning(board) != EMPTY)
        {
            drawBoard(board);
            printf("Player %c wins!\n", current);
            break;
        }

        current = determineTurn(board);
    }
}