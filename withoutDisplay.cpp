#include <string>
#include <iostream>
using namespace std;

//flagged is 11, unflagged is 10
//enum underStatus {ZERO = 0, ONE = 1, TWO = 2, THREE = 3, FOUR = 4, FIVE = 5, SIX = 6, SEVEN = 7, EIGHT = 8, BOMB = 9};
const int width = 30;
const int height = 15;
const int numBombs = (width*height)/8;
const int tileWidth = 20;

char shownGameboard [height][width]; // unflagged is -, flagged is !, shown is the number
int underGameboard [height][width];

bool gameOver = false; 
int boxesClicked = 0;

void endGame() {
    gameOver = true;
    if (boxesClicked >= (height*width)-numBombs) {
        cout << "Game is Over, you have won!";
    }
    else {
        cout << "Game is over, you have lost. :(";
    }
}

int checkBombs(int x, int y) {
    int count = 0;
    if (x > 0) {
        for (int i = 0; i < 3; i++) {
            if (y-1+i >= 0) { 
                if (underGameboard[x-1][y-1+i] == 9) {
                    count++;
                }
            }
        }
    }
    if (x < 9) {
        for (int i = 0; i < 3; i++) {
            if (y-1+i >= 0) { 
                if (underGameboard[x+1][y-1+i] == 9) {
                    count++;
                }
            }
        }
    }
    if (y >0) {
        if (underGameboard[x][y-1] == 9) {
            count++;
        }
    }
    if (y < 7) {
        if (underGameboard[x][y+1] == 9) {
            count++;
        }
    }
    return count;
}

void setupGame() {
    //setting board up to be blank
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            shownGameboard[i][j] = '-';
            underGameboard[i][j] = 0;
        }
    }

    //Placing bombs
    for (int i = 0; i < numBombs; i++) {
        //srand((unsigned int)time(NULL));
        int col = rand() % width;
        int row = rand() % height;
        while (underGameboard[row][col] == 9) {
            //srand((unsigned int)time(NULL));
            col = rand() % width;
            row = rand() % height;
        }
        underGameboard[row][col] = 9;
    }

    //placing appropriate numberical values
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (underGameboard[i][j] != 9) {
                underGameboard[i][j] = checkBombs(i, j);
            }
        }
    }

}

void printUnderBoard() {
    for (int i = 0; i< height; i++) {
        for (int j = 0; j < width; j++) {
            cout << underGameboard[i][j];
        }
        cout << "\n";
    }
}

void printShownBoard() {
    for (int i = 0; i< height; i++) {
        for (int j = 0; j < width; j++) {
            cout << shownGameboard[i][j];
        }
        cout << "\n";
    }
}

void flagBox(int col, int row) {
    shownGameboard[row][col] = '!';
    printShownBoard();
}

//clicks box. Ends game if its a bomb, if not it shows the number
void clickBox(int col, int row) {
    if (underGameboard[row][col] == 9) {
        endGame();
    }
    else {
        shownGameboard[row][col] = '0' + underGameboard[col][row];
        printShownBoard();
    }
    boxesClicked++;
    if(boxesClicked >= (height*width)-numBombs) {
        endGame();
    }

    
}

void promptSelection() {
    int choice;
    cout << "Would you like to Flag a box (Press 1) or click a box (Press 2)?";
    cin >> choice;
    int x;
    int y;
    
    while (choice != 1 && choice != 2) {
        cout << "Please enter either 1 for flagging a box or 2 for clicking a box";
        cin >> choice;
    }
    if (choice == 1) {
        cout << "Which box would you like to flag? \nInput a x-coordinate from 0-29 and press enter, then type an y coordinate from 0-14 and press enter.";
        cin >> x;
        cin >> y;
        while (x < 0 || x > width) {
            cout << "Enter a number from 0-29 for the x coordinate.";
            cin >> x;
        }
        while(y < 0 || y > height) {
            cout << "Enter a number from 0-14 for the y coordinate";
            cin >> y;
        }

        flagBox(x, y);
    }
    else if (choice == 2) {
        cout << "Which box would you like to click?\nInput an x-coordinate from 0-29 and press enter, then type a y coordinate from 0-14 and press enter.";
        cin >> x;
        cin >> y;
        while (x < 0 || x > width) {
            cout << "Enter a number from 0-29 for the x coordinate.";
            cin >> x;
        }
        while(y < 0 || y > height) {
            cout << "Enter a number from 0-14 for the y coordinate";
            cin >> y;
        }
        
        clickBox(x, y);
    }
    

}

int main() {
    setupGame();
    
    printUnderBoard();

    while (!gameOver) {
        promptSelection();
    }

    //printUnderBoard();

}