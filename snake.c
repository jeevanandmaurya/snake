#include <stdio.h>
#include <conio.h>
#include <Windows.h>

// 30*30 Blocks
// BLOCK-0 or N
// 0-Empty
// N-Filled(1-SnakeBlock/2-FoodBlock/3-Explosive)

int gameover = 0;
int snakeLen = 1;
int row[30], col[30];
int velX = 0, velY = 0;
int score = 0;
int time = 0;
int block[900];
// O++++++++++

void keyinput(char input)
{
    // printf("Press a key (W = Up, A = Left, S = Down, D = Right, Q = Quit):\n");
    // Reads a character without Enter

    switch (input)
    {
    case 'w':
        // case 'W':
        velY = -1;
        velX = 0;
        break;
    case 'a':
        // case 'A':
        velX = -1;
        velY = 0;
        break;
    case 's':
        // case 'S':
        velY = 1;
        velX = 0;
        break;
    case 'd':
        // case 'D':
        velX = 1;
        velY = 0;
        break;
    case 'q':
        //  case 'Q':
        //  gameover = 1;

    default:
        printf("Invalid key! Use W/A/S/D to move, Q to quit.\n");
    }
}

void GameLoop()
{
    system("cls");
    printf("SCORE-> %d\n", score);
    // KeyControll
    if (_kbhit())
    {

        char input = _getch();
        keyinput(input);
    }

    // move
    // Resenting old block

    // b3->b2 b2->b1 b1->b1new

    block[(row[snakeLen - 1] - 1) * (30) + col[snakeLen - 1] - 1] = 0;

    for (int i = snakeLen - 1; i > 0; i--)
    {
        row[i] = row[i - 1];
        col[i] = col[i - 1];
        if (block[(row[i] - 1) * (30) + col[i] - 1] == 2)
        {
            score++;
            snakeLen++;
        }
        else
        {
            block[(row[i] - 1) * (30) + col[i] - 1] = 1;
        }

       // printf("<%d> %d\n", i, block[(row[i] - 1) * (30) + col[i] - 1]);
    }

    block[(row[0] - 1) * (30) + col[0] - 1] = 0;

    // Updating new Block`s Instance
    col[0] += velX;
    if (col[0] > 30 || col[0] < 1)
    {
        col[0] = col[0] - velX * 30;
    }

    row[0] += velY;
    if (row[0] > 30 || row[0] < 1)
    {
        row[0] = row[0] - velY * 30;
    }
    // Updating new Block
    if (block[(row[0] - 1) * (30) + col[0] - 1] == 2)
    {
        score++;
        snakeLen++;
    }
    else
    {

        block[(row[0] - 1) * (30) + col[0] - 1] = 1;
    }

    // Printing
    for (int i = 0; i < 30; i++)
    {
        printf(" # ");
    }

    // printing blocks
    for (int i = 0; i < 900; i++)
    {

        if (i % 30 == 0)
        {
            printf("\n # ");
        }

        switch (block[i])
        {

        case 1:
            printf(" O ");
            break;
        case 2:
            printf(" o ");
            break;
        case 3:
            printf("x");
            break;

        default:
            printf("   ");
            break;
        }
        if ((i + 1) % 30 == 0)
        {
            printf("#");
        }
    }

    printf("\n");
    for (int i = 0; i < 30; i++)
    {
        printf(" # ");
    }
    printf("\n VelX<%d> VelY<%d> row[0]<%d> col[0]<%d>", velX, velY, row[0], col[0]);
    for (int i = 0; i < snakeLen; i++)
    {
        printf("\nrow[%d]<%d> col[%d]<%d> block<%d>", i, row[i], i, col[i], block[(row[i] - 1) * (30) + col[i] - 1]);
    }

    printf("\n time<%d>", time);
    // system("cls");

    if (block[35]==1)
    {
        block[800]=2;
    }
    if (block[800]==1)
    {
        block[35]=2;
    }
    
}

int main()
{

    // system("cls");
    for (int i = 0; i < snakeLen; i++)
    {
        row[i] = 15;
    }
    for (int i = 0; i < snakeLen; i++)
    {
        col[i] = 15 - i;
    }

    velX = 1;
    velY = 0;

    for (int i = 0; i < 900; i++)
    {
        block[i] = 0;
    }

    // Food
    block[35] = 2;
    block[800] = 2;

    while (gameover == 0)
    {

        GameLoop();
        Sleep(10);
        time++;
    }

    return 0;
}