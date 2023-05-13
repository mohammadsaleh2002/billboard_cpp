/*

	BillBoard	:	This program receives the text from the user and moves it in 8 directions.

*/

#include <iostream>
#include <windows.h>
#include <time.h>

using namespace std;

static int width, height;

/* Variable to check for hitting the console wall */

static bool hit;

/*  move Up or Down */

void move_UpDown(string text, int& x, int& y, int& dirY) {
    y += dirY;   
/* check for hit up and down wall */
    if(y < 1 || y > height) {
        dirY *= -1;     
        hit = true;
        return;
    }

    COORD pos = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    cout << text;

    Sleep(50);
}

/*  move Left or Right */

void move_LeftRight(string text, int& x, int& y, int& dirX) {
    x += dirX;  
    /* check for hit right and left wall */    
    if(x < 1 || x+text.length() > width - 1 ) {
        dirX *= -1;   
        hit = true;
        return;
    }

    COORD pos = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    cout << text;

    Sleep(50);
}

	/*  move Diagonally */

void move_Diagonally(string text, int& x, int& y, int& dirX, int& dirY) {
    x += dirX;
    y += dirY;
	/* check for hit corners */
	if((x < 1 || x + text.length() > width - 1 ) && (y < 1 || y > height - 1)) {
		dirY *= -1;
        dirX *= -1;
        hit = true;
        return;
    }
    /* check for hit right and left wall */
    if(x < 1 || x + text.length() > width - 1) {
        dirX *= -1;
        hit = true;
        return;
    }
    /* check for hit up and down wall */
    if(y < 1 || y > height ){
    	dirY *= -1;
    	hit = true;
    	return;
	}
	
    COORD pos = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    cout << text;

    Sleep(50);
}

int main(){

    string input ;
    int x = 1, y = 1;
    int dirX = 1, dirY = 1;
 	cout << "Enter Somthing : "<<endl;
 	getline(cin , input);

    /* Adjust console size */
    
	CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    
    /* The width of the console */
    
    width = csbi.srWindow.Right - csbi.srWindow.Left ;
    
    /* The height of the console */
    
    height = csbi.srWindow.Bottom - csbi.srWindow.Top ;


	srand(time(0));
    while(true) {
		int r = rand() % 3;
    	while(!hit){
	    	switch(r){
	    		case 0:
	    			move_UpDown(input, x, y, dirY);
	    			break;
	    		case 1:
					move_Diagonally(input, x, y, dirX, dirY);
					break;
	    		case 2:
	    			move_LeftRight(input, x, y, dirX);
	    			break;	    	
			}
			system("cls");
		}
		if(hit){
			hit = false;
		}
			
    }
    return 0;
}
