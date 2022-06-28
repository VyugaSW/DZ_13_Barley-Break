#include <iostream>
#include <Windows.h>

using namespace std;
char term;
int board[4][4];
void FillingBoard(int(*arr)[4]);
void DrawingBoard(int(*arr)[4]);
void PlayerStep(int(*arr)[4], int numb, char step);
void WrongStep(int(*arr)[4]);
void WinCheck(int(*arr)[4]);
// "0" - пустое место

int main()
{
    FillingBoard(board);
    char step;
    int numb;
    cout << "Do you want to star? (y/n):\n";
    cin >> term;
    while (term == 'y') {
        system("cls");
        DrawingBoard(board);
        cout << "Enter number - "; cin >> numb;
        cout << "Enter route (u - up/ d - down/ r - right/ l - left) - "; cin >> step;
        PlayerStep(board, numb, step);
        DrawingBoard(board); 
        WinCheck(board);
    }
}
void WinCheck(int(*arr)[4]) {
    int WinCheckArr[4][4] = { {1,2,3,4 }, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 0} };
    int count = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (arr[i][j] == WinCheckArr[i][j]) count++;
        }
    }
    if (count == 16) {
        cout << "You WIN!\n";
        term = 'n';
    }
}
void FillingBoard(int(*arr)[4]) {
    srand(time(NULL));
    //Список для контроля повторений
    int board_numbers[16] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
    int RandNumb;
    int count = 0;
    //Происходит заполнение поля с учётом и скрупулёзной проверкой повторений
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            RandNumb = rand() % 16;
            while (board_numbers[RandNumb] == 1) {
                RandNumb = rand() % 16;
            }
            board_numbers[RandNumb] = 1;
            arr[i][j] = RandNumb;
        }
    }
}
void DrawingBoard(int(*arr)[4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cout << "|" << arr[i][j] << "|";
        }
        cout << endl;
    }
}
void WrongStep(int(*arr)[4]) {
    int numb;
    char step;

    cout << "Wrong, try one more time:\n ";
    cout << "Enter number - "; cin >> numb;
    cout << "Enter route (u - up/ d - down/ r - right/ l - left) - "; cin >> step;
    PlayerStep(arr, numb, step);
}
void PlayerStep(int(*arr)[4], int numb, char step) {
    int t1, t2;
    int temp;
    // Определяем местоположение числа
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (arr[i][j] == numb) {
                t1 = i;
                t2 = j;
            }
        }
    }
   
    if (step == 'u') {
        if (t1 == 0) WrongStep(arr);
        else {
            temp = arr[t1 - 1][t2];
            arr[t1 - 1][t2] = numb;
            arr[t1][t2] = temp;
        }
    }
    else if (step == 'd') {
        if (t1 == 3) WrongStep(arr);
        else {
            temp = arr[t1 + 1][t2];
            arr[t1 + 1][t2] = numb;
            arr[t1][t2] = temp;
        }
    }
    else if (step == 'r') {
        if (t2 == 3) WrongStep(arr);
        else {
            temp = arr[t1][t2+1];
            arr[t1][t2+1] = numb;
            arr[t1][t2] = temp;
        }
    }
    else if (step == 'l') {
        if (t2 == 0) WrongStep(arr);
        else {
            temp = arr[t1][t2 - 1];
            arr[t1][t2 - 1] = numb;
            arr[t1][t2] = temp;
        }
    }
    else {
        WrongStep(arr);
    }
}