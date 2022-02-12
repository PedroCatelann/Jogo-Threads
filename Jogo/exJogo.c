#include <stdio.h>
#include <windows.h>
#include <process.h>
#include<stdlib.h>
#include<time.h>

HANDLE mutex; ///mutual exclusion
int coluna;
int cont = 0;
char mat[100][100];


void gotoxy(int x, int y)
{
    COORD coord;
    coord.X=(short)x;
    coord.Y=(short)y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

void tiro(int lin)
{
    int col= coluna + 1;
    while(col<80)
    {
        mat[lin][col]='X';
        WaitForSingleObject(mutex,INFINITE);
        gotoxy(col,lin);
        printf("*");
        ReleaseMutex(mutex);


        _sleep(50);

        WaitForSingleObject(mutex,INFINITE);
        gotoxy(col,lin);
        printf(" ");
        col++;
        ReleaseMutex(mutex);
    }
}

void nave(int x) {

    int col=80, lin = x;
    while(col != 0) {

        Sleep(100);

        if(mat[lin][col] == 'X') {

            cont++;
            break;
        }
        WaitForSingleObject(mutex, INFINITE);
        gotoxy(col,lin);
        printf(" ");
        col--;
        gotoxy(col,lin);
        printf("X");
        ReleaseMutex(mutex);
        if(col==0) {

            WaitForSingleObject(mutex, INFINITE);
            gotoxy(col,lin);
            printf(" ");
        }
    }


}

void criar() {

    int aleat=0;

    while(1) {

        aleat = rand()%30;
        _beginthread(nave,NULL,aleat);
        Sleep(1000);
    }
}

void estrela(int x) {

    int col=80, lin = x;
    while(col != 0) {

        Sleep(10);

        WaitForSingleObject(mutex, INFINITE);
        gotoxy(col,lin);
        printf(" ");
        col--;
        gotoxy(col,lin);
        printf(".");
        ReleaseMutex(mutex);
    }

    WaitForSingleObject(mutex, INFINITE);
    gotoxy(col,lin);
    printf(" ");
}

void pontuacao() {

    while(1) {

        WaitForSingleObject(mutex, INFINITE);
        gotoxy(0,0);
        printf("Pontuacao: %d", cont);
        ReleaseMutex(mutex);
    }
}



void criar_estrela() {

    int aleat=0;

    while(1) {

        aleat = rand()%28;
        _beginthread(estrela,NULL,aleat);
        Sleep(80);
    }
}

int main(void)
{
    srand(time(NULL));
    int linNave=12,colNave=0;
    char tecla;
    mutex=CreateMutex(NULL,FALSE,NULL);
    _beginthread(criar, NULL, NULL);
    _beginthread(criar_estrela, NULL, NULL);
    _beginthread(pontuacao, NULL, NULL);
    while(1)
    {
        WaitForSingleObject(mutex,INFINITE);
        gotoxy(colNave,linNave);
        printf(">");
        ReleaseMutex(mutex);
        tecla=getch();
        switch(tecla)
        {
        case 32: //barra de espaço
            _beginthread(tiro,NULL,linNave);
            break;
        case -32: //caracter especial
            tecla=getch();
            if (tecla==72)
            {
                WaitForSingleObject(mutex,INFINITE);
                gotoxy(colNave,linNave);
                printf(" ");
                linNave--;
                gotoxy(colNave,linNave);
                printf(">");
                ReleaseMutex(mutex);
            }
            else if(tecla==80)
            {
                WaitForSingleObject(mutex,INFINITE);
                gotoxy(colNave,linNave);
                printf(" ");
                linNave++;
                gotoxy(colNave,linNave);
                printf(">");
                ReleaseMutex(mutex);
            }
            else if(tecla==77) {

                WaitForSingleObject(mutex, INFINITE);
                gotoxy(colNave, linNave);
                printf(" ");
                colNave++;
                coluna = colNave;
                gotoxy(colNave,linNave);
                printf(">");
                ReleaseMutex(mutex);
            }
            else if(tecla==75) {

                WaitForSingleObject(mutex, INFINITE);
                gotoxy(colNave, linNave);
                printf(" ");
                colNave--;
                coluna = colNave;
                gotoxy(colNave,linNave);
                printf(">");
                ReleaseMutex(mutex);
            }
        }
    }
}
