#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstdlib>
#include <console.h>
using namespace std;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////GLOBAL VARIABLES;
vector<string> abc;
string table[26][26];
string undo[10000][26][26];
int a = -1;
string black, white;
int cblack, cwhite;
int x, y;
int turn = 1;
int countX, countO;
int ctr;
string liberity[26][26];
int quit = 0;
int c_undo = 0;
int deadX, cdeadX;
int deadO, cdeadO;
int remake, bmenu, result, backgr;
char gg, rm, bm, wp, eag, color;
int warn;
string player1, player2;
ofstream outfile;
ifstream infile;
string anything;
int game();
int printmenu();
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////GLOBAL VARIABLES;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////FUNCTIONS;
void buildVector(vector<string> &vect, int num){ //--------------------------------------------------------------build alphabets;
    string rd = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for(int u = 0; u < num; ++u){
        vect.push_back(rd.substr(u,1));
    }
}

void buildFirst(vector<string> &vect, int num){ //---------------------------------------------------------------build and show the first line;
    cout << "* ";
    for(int i = 0; i < num; ++i)
        cout << "| " << vect[i] << " ";
    cout << "| *" << endl;
}

void buildArray(string arr[][26], int num){ //-------------------------------------------------------------------build table array;
    for(int i = 0; i < num; ++i){
        for(int j = 0; j < num; ++j){
            arr[i][j] = "|   ";
        }
    }
}

void buildTable(vector<string> &vect, string arr[][26], int num){ //---------------------------------------------build and show the table;
    for(int i = 0; i < num; ++i){
        cout << "-----";
        for(int k = 0; k < num; ++k)
            cout << "----";
        cout << endl;
        cout << vect[i] << " ";
        for(int j = 0; j < num; ++j){
            cout << arr[i][j];
        }
        cout << "| " << vect[i] << endl;
    }
}

void buildLast(vector<string> &vect, int num){ //----------------------------------------------------------------build and show last line;
    cout << "-----";
    for(int k = 0; k < num; ++k)
        cout << "----";
    cout << endl;
    cout << "* ";
    for(int i = 0; i < num; ++i)
        cout << "| " << vect[i] << " ";
    cout << "| *" << endl;
}

void Liberity(int num){ //---------------------------------------------------------------------------------------find the liberality
    string z1, z2;
    z1 = "| ";
    z2 = 178;
    for(int i = 0; i < num; ++i){
        for(int j = 0; j < num; ++j){
            if (table[i][j] == "|   " || table[i][j] == z1 + " " + z2) liberity[i][j] = "  ";
            if (table[i][j] == "| X " || table[i][j] == z1 + "X" + z2) liberity[i][j] = "0X";
            if (table[i][j] == "| O " || table[i][j] == z1 + "O" + z2) liberity[i][j] = "0O";
        }
    }
}

void CheckLiberity(int num){ //----------------------------------------------------------------------------------check for the liberality;
    for(int r = 0; r < 2; ++r){
        for(int i = 0; i < num; ++i){
            for(int j = 0; j < num; ++j){
                if (liberity[i][j] == "0X"){
                    if (i==0){
                        if (j==0){
                            if (liberity[0][1] == "  " || liberity[0][1] == "1X" ||
                                liberity[1][0] == "  " || liberity[1][0] == "1X")
                                liberity[0][0] = "1X";
                        }
                        if (j==a-1){
                            if (liberity[0][a-2] == "  " || liberity[0][a-2] == "1X" ||
                                liberity[1][a-1] == "  " || liberity[1][a-1] == "1X")
                                liberity[0][a-1] = "1X";
                        }
                        if (j>0 && j<a-1) {
                            if (liberity[0][j-1] == "  " || liberity[0][j-1] == "1X" ||
                                liberity[0+1][j] == "  " || liberity[0+1][j] == "1X" ||
                                liberity[0][j+1] == "  " || liberity[0][j+1] == "1X")
                                liberity[0][j] = "1X";
                        }
                    }
                    if (j==0){
                        if (i==0){
                            if (liberity[0][1] == "  " || liberity[0][1] == "1X" ||
                                liberity[1][0] == "  " || liberity[1][0] == "1X")
                                liberity[0][0] = "1X";
                        }
                        if (i==a-1){
                            if (liberity[a-1][1] == "  " || liberity[a-1][1] == "1X" ||
                                liberity[a-2][0] == "  " || liberity[a-2][0] == "1X")
                                liberity[a-1][0] = "1X";
                        }
                        if (i>0 && i<a-1) {
                            if (liberity[i-1][0] == "  " || liberity[i-1][0] == "1X" ||
                                liberity[i+1][0] == "  " || liberity[i+1][0] == "1X" ||
                                liberity[i][0+1] == "  " || liberity[i][0+1] == "1X")
                                liberity[i][0] = "1X";
                        }
                    }
                    if (i!=0 && j!=0){
                        if (liberity[i-1][j] == "  " || liberity[i-1][j] == "1X" ||
                            liberity[i][j-1] == "  " || liberity[i][j-1] == "1X" ||
                            liberity[i+1][j] == "  " || liberity[i+1][j] == "1X" ||
                            liberity[i][j+1] == "  " || liberity[i][j+1] == "1X")
                            liberity[i][j] = "1X";
                    }
                }

                if (liberity[i][j] == "0O"){
                    if (i==0){
                        if (j==0){
                            if (liberity[0][1] == "  " || liberity[0][1] == "1O" ||
                                liberity[1][0] == "  " || liberity[1][0] == "1O")
                                liberity[0][0] = "1O";
                        }
                        if (j==a-1){
                            if (liberity[0][a-2] == "  " || liberity[0][a-2] == "1O" ||
                                liberity[1][a-1] == "  " || liberity[1][a-1] == "1O")
                                liberity[0][a-1] = "1O";
                        }
                        if (j>0 && j<a-1) {
                            if (liberity[0][j-1] == "  " || liberity[0][j-1] == "1O" ||
                                liberity[0+1][j] == "  " || liberity[0+1][j] == "1O" ||
                                liberity[0][j+1] == "  " || liberity[0][j+1] == "1O")
                                liberity[0][j] = "1O";
                        }
                    }
                    if (j==0){
                        if (i==0){
                            if (liberity[0][1] == "  " || liberity[0][1] == "1O" ||
                                liberity[1][0] == "  " || liberity[1][0] == "1O")
                                liberity[0][0] = "1O";
                        }
                        if (i==a-1){
                            if (liberity[a-1][1] == "  " || liberity[a-1][1] == "1O" ||
                                liberity[a-2][0] == "  " || liberity[a-2][0] == "1O")
                                liberity[a-1][0] = "1O";
                        }
                        if (i>0 && i<a-1) {
                            if (liberity[i-1][0] == "  " || liberity[i-1][0] == "1O" ||
                                liberity[i+1][0] == "  " || liberity[i+1][0] == "1O" ||
                                liberity[i][0+1] == "  " || liberity[i][0+1] == "1O")
                                liberity[i][0] = "1O";
                        }
                    }
                    if (i!=0 && j!=0){
                        if (liberity[i-1][j] == "  " || liberity[i-1][j] == "1O" ||
                            liberity[i][j-1] == "  " || liberity[i][j-1] == "1O" ||
                            liberity[i+1][j] == "  " || liberity[i+1][j] == "1O" ||
                            liberity[i][j+1] == "  " || liberity[i][j+1] == "1O")
                            liberity[i][j] = "1O";
                    }
                }
            }
        }
        for(int i = num-1; i >= 0; --i){
            for(int j = num-1; j >= 0; --j){
                if (liberity[i][j] == "0X"){
                    if (i==0){
                        if (j==0){
                            if (liberity[0][1] == "  " || liberity[0][1] == "1X" ||
                                liberity[1][0] == "  " || liberity[1][0] == "1X")
                                liberity[0][0] = "1X";
                        }
                        if (j==a-1){
                            if (liberity[0][a-2] == "  " || liberity[0][a-2] == "1X" ||
                                liberity[1][a-1] == "  " || liberity[1][a-1] == "1X")
                                liberity[0][a-1] = "1X";
                        }
                        if (j>0 && j<a-1) {
                            if (liberity[0][j-1] == "  " || liberity[0][j-1] == "1X" ||
                                liberity[0+1][j] == "  " || liberity[0+1][j] == "1X" ||
                                liberity[0][j+1] == "  " || liberity[0][j+1] == "1X")
                                liberity[0][j] = "1X";
                        }
                    }
                    if (j==0){
                        if (i==0){
                            if (liberity[0][1] == "  " || liberity[0][1] == "1X" ||
                                liberity[1][0] == "  " || liberity[1][0] == "1X")
                                liberity[0][0] = "1X";
                        }
                        if (i==a-1){
                            if (liberity[a-1][1] == "  " || liberity[a-1][1] == "1X" ||
                                liberity[a-2][0] == "  " || liberity[a-2][0] == "1X")
                                liberity[a-1][0] = "1X";
                        }
                        if (i>0 && i<a-1) {
                            if (liberity[i-1][0] == "  " || liberity[i-1][0] == "1X" ||
                                liberity[i+1][0] == "  " || liberity[i+1][0] == "1X" ||
                                liberity[i][0+1] == "  " || liberity[i][0+1] == "1X")
                                liberity[i][0] = "1X";
                        }
                    }
                    if (i!=0 && j!=0){
                        if (liberity[i-1][j] == "  " || liberity[i-1][j] == "1X" ||
                            liberity[i][j-1] == "  " || liberity[i][j-1] == "1X" ||
                            liberity[i+1][j] == "  " || liberity[i+1][j] == "1X" ||
                            liberity[i][j+1] == "  " || liberity[i][j+1] == "1X")
                            liberity[i][j] = "1X";
                    }
                }

                if (liberity[i][j] == "0O"){
                    if (i==0){
                        if (j==0){
                            if (liberity[0][1] == "  " || liberity[0][1] == "1O" ||
                                liberity[1][0] == "  " || liberity[1][0] == "1O")
                                liberity[0][0] = "1O";
                        }
                        if (j==a-1){
                            if (liberity[0][a-2] == "  " || liberity[0][a-2] == "1O" ||
                                liberity[1][a-1] == "  " || liberity[1][a-1] == "1O")
                                liberity[0][a-1] = "1O";
                        }
                        if (j>0 && j<a-1) {
                            if (liberity[0][j-1] == "  " || liberity[0][j-1] == "1O" ||
                                liberity[0+1][j] == "  " || liberity[0+1][j] == "1O" ||
                                liberity[0][j+1] == "  " || liberity[0][j+1] == "1O")
                                liberity[0][j] = "1O";
                        }
                    }
                    if (j==0){
                        if (i==0){
                            if (liberity[0][1] == "  " || liberity[0][1] == "1O" ||
                                liberity[1][0] == "  " || liberity[1][0] == "1O")
                                liberity[0][0] = "1O";
                        }
                        if (i==a-1){
                            if (liberity[a-1][1] == "  " || liberity[a-1][1] == "1O" ||
                                liberity[a-2][0] == "  " || liberity[a-2][0] == "1O")
                                liberity[a-1][0] = "1O";
                        }
                        if (i>0 && i<a-1) {
                            if (liberity[i-1][0] == "  " || liberity[i-1][0] == "1O" ||
                                liberity[i+1][0] == "  " || liberity[i+1][0] == "1O" ||
                                liberity[i][0+1] == "  " || liberity[i][0+1] == "1O")
                                liberity[i][0] = "1O";
                        }
                    }
                    if (i!=0 && j!=0){
                        if (liberity[i-1][j] == "  " || liberity[i-1][j] == "1O" ||
                            liberity[i][j-1] == "  " || liberity[i][j-1] == "1O" ||
                            liberity[i+1][j] == "  " || liberity[i+1][j] == "1O" ||
                            liberity[i][j+1] == "  " || liberity[i][j+1] == "1O")
                            liberity[i][j] = "1O";
                    }
                }
            }
        }
    }
    /*for(int i = 0; i < num; ++i){
        for(int j = 0; j < num; ++j){
            cout << liberity[i][j];
        }
        cout << endl;
    }*/
}

void NoLiberityX(int num){ //------------------------------------------------------------------------------------kill black[0];
    string z1, z2;
    z1 = "| ";
    z2 = 178;
    for(int i = 0; i < num; ++i){
        for(int j = 0; j < num; ++j){
            if (liberity[i][j] == "0X"){
                if (table[i][j] == "| X " || table[i][j] == z1 + "X" + z2){
                    table[i][j] = "|   ";
                    ++deadX;
                }
            }
        }
    }
}

void NoLiberityO(int num){ //------------------------------------------------------------------------------------kill white[O];
    string z1, z2;
    z1 = "| ";
    z2 = 178;
    for(int i = 0; i < num; ++i){
        for(int j = 0; j < num; ++j){
            if (liberity[i][j] == "0O"){
                if (table[i][j] == "| O " || table[i][j] == z1 + "O" + z2){
                    table[i][j] = "|   ";
                    ++deadO;
                }
            }
        }
    }
}

void point(int &i, int &j){ //-----------------------------------------------------------------------------------make the pointer of current position;
    string z1, z2;
    z1 = "| ";
    z2 = 178;
    if (table[i][j] == "|   ")
        table[i][j] = z1 + " " + z2;
    if (table[i][j] == "| X ")
        table[i][j] = z1 + "X" + z2;
    if (table[i][j] == "| O ")
        table[i][j] = z1 + "O" + z2;
}

int console(int &i, int &j){ //----------------------------------------------------------------------------------make the movement of the console;
    c_undo = 0;
	string z1, z2;
    z1 = "| ";
    z2 = 178;
    cblack = 1;
    cwhite = 1;
    remake = 0;
    bmenu = 0;
    result = 0;
	int key = inputKey();
	if (key == key_Up && i > 0){
        i -= 1; gotoXY(j, i);
        point(i, j);
        if (table[i+1][j] == z1 + " " + z2)
            table[i+1][j] = "|   ";
        if (table[i+1][j] == z1 + "X" + z2)
            table[i+1][j] = "| X ";
        if (table[i+1][j] == z1 + "O" + z2)
            table[i+1][j] = "| O ";
        return 1;
	}
	if (key == key_Down && i < a-1){
		i += 1; gotoXY(j, i);
		point(i, j);
		if (table[i-1][j] == z1 + " " + z2)
            table[i-1][j] = "|   ";
        if (table[i-1][j] == z1 + "X" + z2)
            table[i-1][j] = "| X ";
        if (table[i-1][j] == z1 + "O" + z2)
            table[i-1][j] = "| O ";
		return 1;
	}
	if (key == key_Left && j > 0){
		j -= 1; gotoXY(j, i);
		point(i, j);
		if (table[i][j+1] == z1 + " " + z2)
            table[i][j+1] = "|   ";
        if (table[i][j+1] == z1 + "X" + z2)
            table[i][j+1] = "| X ";
        if (table[i][j+1] == z1 + "O" + z2)
            table[i][j+1] = "| O ";
		return 1;
	}
	if (key == key_Right && j < a-1){
		j += 1; gotoXY(j, i);
		point(i, j);
		if (table[i][j-1] == z1 + " " + z2)
            table[i][j-1] = "|   ";
        if (table[i][j-1] == z1 + "X" + z2)
            table[i][j-1] = "| X ";
        if (table[i][j-1] == z1 + "O" + z2)
            table[i][j-1] = "| O ";
		return 1;
	}
	if (key == VK_RETURN || key == VK_SPACE){
        gotoXY(j, i);
        if (table[i][j] == z1 + " " + z2){
            if (turn % 2 != 0){
                table[i][j] = z1 + "X" + z2;
                cblack = 0;
                warn = 0;
            }
            else{
                table[i][j] = z1 + "O" + z2;
                cwhite = 0;
                warn = 0;
            }
        }
        else{
            if (turn % 2 != 0){
                cblack = 1;
                warn = 1;
            }
            else{
                cwhite = 1;
                warn = 1;
            }
        }
        return 1;
	}
	if (key == VK_ESCAPE){
        system("CLS");
        quit = 1;
        return 1;
	}
	if (key == VK_TAB){
        c_undo = 1;
        return 1;
	}
	if (key == 60){ //60: F2
        remake = 1;
        return 1;
	}
	if (key == 59){ //59: F1
        bmenu = 1;
        return 1;
	}
	if (key == 61){ //61: F3
        result = 1;
        return 1;
	}
	return 0;
}

void InsertMoveB(string arr[][26], string str){ //---------------------------------------------------------------insert black[X];
    char p1 = str[0];
    char p2 = str[1];
    int i = toupper(p1) - 'A';
    int j = toupper(p2) - 'A';
    if(arr[i][j] == "|   ")
        arr[i][j] = "| X ";
}

void CheckMoveB(string arr[][26], string str){ //----------------------------------------------------------------check black[X] valid or not;
    char p1 = str[0];
    char p2 = str[1];
    int i = toupper(p1) - 'A';
    int j = toupper(p2) - 'A';
    if (arr[i][j] != "|   "){ cblack = 1; warn = 1;}
    else{ cblack = 0; warn = 0;}
}

void InsertMoveW(string arr[][26], string str){ //---------------------------------------------------------------insert white[O];
    char p1 = str[0];
    char p2 = str[1];
    int i = toupper(p1) - 'A';
    int j = toupper(p2) - 'A';
    if(arr[i][j] == "|   ")
        arr[i][j] = "| O ";
}

void CheckMoveW(string arr[][26], string str){ //----------------------------------------------------------------check white[O] valid or not;
    char p1 = str[0];
    char p2 = str[1];
    int i = toupper(p1) - 'A';
    int j = toupper(p2) - 'A';
    if(arr[i][j] != "|   "){ cwhite = 1; warn = 1;}
    else{ cwhite = 0; warn = 0;}
}

void Table2Undo(string arr[][26], int num, int &t){ //-----------------------------------------------------------put table into undo at turn t;
    for(int i = 0; i < num; ++i){
        for(int j = 0; j < num; ++j){
            undo[t][i][j] = arr[i][j];
        }
    }
}

void Undo2Table(string arr[][26], int num, int &t){ //-----------------------------------------------------------put undo into table at turn t;
    for(int i = 0; i < num; ++i){
        for(int j = 0; j < num; ++j){
            arr[i][j] = undo[t][i][j];
        }
    }
}

void CountXO(string arr[][26], int num){ //----------------------------------------------------------------------count both black[X] and white[O];
    string z1, z2;
    z1 = "| ";
    z2 = 178;
    countX = 0;
    countO = 0;
    for(int i = 0; i < num; ++i){
        for(int j = 0; j < num; ++j){
            if (arr[i][j] == "| X " || arr[i][j] == z1 + "X" + z2) ++countX;
            if (arr[i][j] == "| O " || arr[i][j] == z1 + "O" + z2) ++countO;
        }
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////FUNCTIONS;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////OPERATIONS;
void TURN(int &t){ //==============================================================================================|DISPLAY TURN|;
    string tu;
    gotoXY(a * 5,a + 2);
    if (t % 2 != 0){
        cout << "  TURN:   " << t << "\t" << "(Turn of " << player1 << ")" << endl;
    }
    else{
        cout << "  TURN:   " << t << "\t" << "(Turn of " << player2 << ")" << endl;
    }
}

void SETUP(){ //===================================================================================================|SETUP GO GAME|;
    if (backgr == 0)
        system("color 0F");
    if (backgr == 1)
        system("color F0");
    do{
        system("CLS");
        cout << "***********************************************************************" << endl;
        cout << "** Please select the size of the board you want to play.             **" << endl
             << "** The standard sizes are 9 for small/ 13 for medium / 19 for large. **" << endl
             << "***********************************************************************" << endl
            << "                   Your choice: ";
        cin >> a;
    } while (a < 1 || a > 19);
    deadX = 0;
    deadO = 0;
    remake = 0;
    quit = 0;
    warn = 0;
    system("CLS");
    buildVector(abc,19);
    buildVector(abc,a);
    buildArray(table,a);
}

void GOG(){ //=====================================================================================================|START GO GAME|;
    buildFirst(abc,a);
    buildTable(abc,table,a);
    buildLast(abc,a);
}

string cinBlack(){ //==============================================================================================|BLACK[X]|;
    gotoXY(a * 5,a * 2 - 2);
    cout << "TYPE YOUR COMMAND: ";
    cin >> black;
    CheckMoveB(table,black);
    return black;
}

void moveBlack(){ //===============================================================================================|BLACK[X] MOVING|;
    InsertMoveB(table,black);
}

string cinWhite(){ //==============================================================================================|WHITE[O]|;
    gotoXY(a * 5,a * 2 - 2);
    cout << "TYPE YOUR COMMAND: ";
    cin >> white;
    CheckMoveW(table,white);
    return white;
}

void moveWhite(){ //===============================================================================================|WHITE[O] MOVING|;
    InsertMoveW(table,white);
}

void UNDO(){ //====================================================================================================|UNDO|;
    Undo2Table(table,a,turn);
}

void LETCOUNT(){ //================================================================================================|COUNT NUMBERS OF X AND O|;
    CountXO(table,a);
    gotoXY(a * 5,a + 4);
    cout << "  " << player1 << endl;
    gotoXY(a * 5,a + 5);
    cout << "  ALIVE X:   " << countX << endl;
    gotoXY(a * 5,a + 6);
    cout << "  DEAD X:    " << deadX;
    gotoXY(a * 5 + 18,a + 4);
    cout << "  " << player2 << endl;
    gotoXY(a * 5 + 18,a + 5);
    cout << "  ALIVE O:   " << countO << endl;
    gotoXY(a * 5 + 18,a + 6);
    cout << "  DEAD O:    " << deadO;
    Table2Undo(table,a,turn);
}

void CHOOSECTR(){ //===============================================================================================|CHOOSE TYPE OF CONTROL|;
    if (backgr == 0)
        system("color 0F");
    if (backgr == 1)
        system("color F0");
    cout << "*******************************************************************************" << endl;
    cout << "** Which type of control do you want to use:                                 **" << endl;
    cout << "** 1. Coordinate (The players must type exactly coordinates of the stones)   **" << endl
         << "** 2. Console (The players use keyboard to select coordinates of the stones) **" << endl
         << "*******************************************************************************" << endl << endl
         << "                      Your choice: ";
    cin >> ctr;
}

void GUIDE1(){ //==================================================================================================|SHOW GUIDE FOR COORDINATE|;
    gotoXY(a * 5, 0);
    cout << " ------------------GUIDE------------------ " << endl;
    gotoXY(a * 5, 1);
    cout << "| TYPE YOUR COMMAND:(Please use uppercase)|" << endl;
    gotoXY(a * 5, 2);
    cout << "| |X||Y|: Insert your stone to the board. |" << endl;
    gotoXY(a * 5, 3);
    cout << "|         (Example: AB)                   |" << endl;
    gotoXY(a * 5, 4);
    cout << "| UNDO: Undo the previous turn.           |" << endl;
    gotoXY(a * 5, 5);
    cout << "| END: End the game and go to the result. |" << endl;
    gotoXY(a * 5, 6);
    cout << "| REMAKE: Restart the new game.           |" << endl;
    gotoXY(a * 5, 7);
    cout << "| MENU: Go back to main menu.             |" << endl;
    gotoXY(a * 5, 8);
    cout << "| QUIT: Exit the whole game.              |" << endl;
    gotoXY(a * 5, 9);
    cout << " ----------------------------------------- " << endl;
}

void GUIDE2(){ //==================================================================================================|SHOW GUIDE FOR CONSOLE|;
    gotoXY(a * 5, 0);
    cout << " ------------------GUIDE------------------ " << endl;
    gotoXY(a * 5, 1);
    cout << "| PRESS YOUR HOTKEY:                      |" << endl;
    gotoXY(a * 5, 2);
    cout << "| Up/Down/Left/Right: Choose coordinates  |" << endl;
    gotoXY(a * 5, 3);
    cout << "| Enter/Space: Insert your stones         |" << endl;
    gotoXY(a * 5, 4);
    cout << "| TAB: Undo the previous turn.            |" << endl;
    gotoXY(a * 5, 5);
    cout << "| F3: End the game and go to the result.  |" << endl;
    gotoXY(a * 5, 6);
    cout << "| F2: Restart the new game.               |" << endl;
    gotoXY(a * 5, 7);
    cout << "| F1: Go back to main menu.               |" << endl;
    gotoXY(a * 5, 8);
    cout << "| ESC: Exit the whole game.               |" << endl;
    gotoXY(a * 5, 9);
    cout << " ----------------------------------------- " << endl;
}

void STATUS(){ //==================================================================================================|SHOW STATUS BAR|;
    gotoXY(a * 5, a);
    cout << " -----------------STATUS------------------ " << endl;
    TURN(turn);
}

void DEADORALIVE(int &t){ //===========================================================================================|CHECK DEAD OR ALIVE|;
    cdeadO = 0;
    cdeadX = 0;
    Liberity(a);
    if (t % 2 != 0){
        cdeadO = deadO;
        cdeadX = deadX;
        CheckLiberity(a);
        NoLiberityX(a);
        Liberity(a);
        CheckLiberity(a);
        NoLiberityO(a);
        CheckLiberity(a);
        if (deadO > cdeadO){
            t--;
            Undo2Table(table,a,t);
            deadO = cdeadO;
            warn = 1;
        }
    }
    if (t % 2 == 0){
        cdeadX = deadX;
        cdeadO = deadO;
        CheckLiberity(a);
        NoLiberityO(a);
        Liberity(a);
        CheckLiberity(a);
        NoLiberityX(a);
        CheckLiberity(a);
        if (deadX > cdeadX){
            t--;
            Undo2Table(table,a,t);
            deadX = cdeadX;
            warn = 1;
        }
    }
}

int logo();
void QUITGAME(){ //====================================================================================================|QUIT GAME FROM GAME|;
    system("CLS");
    if (backgr == 0)
        system("color 0F");
    if (backgr == 1)
        system("color F0");
    gg = ' ';
    cout << "******************************************" << endl;
    cout << "** This will quit your whole game!      **" << endl;
    cout << "** Are you sure to quit the game?       **" << endl;
    cout << "**       Yes(Y)    **      No(N)        **" << endl;
    cout << "******************************************" << endl;
    cout << endl;
	cout << "           Your Choice: ";
    cin >> gg;
    logo();
    system("CLS");
    cout << "******************************" << endl;
    cout << "**  GOOD GAME WELL PLAYED!  **" << endl;
    cout << "**      SEE YOU AGAIN!      **" << endl;
    cout << "******************************" << endl << endl << endl;
}

int QUITGAME0(){ //====================================================================================================|QUIT GAME FROM MENU|;
    system("CLS");
    if (backgr == 0)
        system("color 0B");
    if (backgr == 1)
        system("color F3");
    cout << "******************************" << endl;
    cout << "**  GOOD GAME WELL PLAYED!  **" << endl;
    cout << "**      SEE YOU AGAIN!      **" << endl;
    cout << "******************************" << endl << endl << endl;
    return 0;
}

void WARNING(){ //=====================================================================================================|SHOW WARNING|;
    gotoXY(a * 5, a * 2);
    if (warn == 1){
        gotoXY(a * 5, a * 2);
        cout << "**************************************" << endl;
        gotoXY(a * 5, a * 2 + 1);
        cout << "** Invalid move, please type again! **" << endl;
        gotoXY(a * 5, a * 2 + 2);
        cout << "**************************************" << endl;
    }
}

int FSETTING(){ //=====================================================================================================|FIRST WARNING|;
    anything = "";
    cout << "*****************************WARNING**********************************" << endl;
    cout << "** 1. Please follow exactly the guide in game.                      **" << endl;
    cout << "** 2. Choose your choices carefully.                                **" << endl;
    cout << "** 3. Spend much time on playing game will affect your health.      **" << endl;
    cout << "** 4. Using fullscreen(Alt+Enter) for the best quality of the game. **" << endl;
    cout << "** 5. Contact us for more information.                              **" << endl;
    cout << "**********************************************************************" << endl << endl;
    cout << "                       Press Any Things: ";
    cin >> anything;
    system("CLS");
    return 0;
}


void REMAKE(){ //======================================================================================================|REMAKE THE CURRENT GAME|;
    system("CLS");
    if (backgr == 0)
        system("color 0F");
    if (backgr == 1)
        system("color F0");
    rm = ' ';
    cout << "****************************************" << endl;
    cout << "** This will reset your current game! **" << endl;
    cout << "** Are you sure to continue?          **" << endl;
    cout << "**       Yes(Y)    **      No(N)      **" << endl;
    cout << "****************************************" << endl << endl;
    cout << "           Your Choice: ";
    cin >> rm;
}

int BACKMENU(){ //=====================================================================================================|BACK TO MENU|;
    system("CLS");
    if (backgr == 0)
        system("color 0F");
    if (backgr == 1)
        system("color F0");
    bm = ' ';
    cout << "****************************************" << endl;
    cout << "** This will go back to main menu!    **" << endl;
    cout << "** Are you sure to continue?          **" << endl;
    cout << "**       Yes(Y)    **      No(N)      **" << endl;
    cout << "****************************************" << endl << endl;
    cout << "           Your Choice: ";
    cin >> bm;
    return 0;
}

string PLER1(){ //=====================================================================================================|PLAYER1 INFO|;
    system("CLS");
    if (backgr == 0)
        system("color 0F");
    if (backgr == 1)
        system("color F0");
    cout << "********************************************" << endl;
    cout << "** Please enter your name:                **" << endl;
    cout << "********************************************" << endl;
    cout << endl;
    cout << "   PLAYER1:  " << player1 << " (current)" << endl;
    cout << "   Your Name:  ";
    cin >> player1;
    system("CLS");
    return player1;
}

string PLER2(){ //=====================================================================================================|PLAYER2 INFO|;
    system("CLS");
    if (backgr == 0)
        system("color 0F");
    if (backgr == 1)
        system("color F0");
    cout << "********************************************" << endl;
    cout << "** Please enter your name:                **" << endl;
    cout << "********************************************" << endl;
    cout << endl;
    cout << "   PLAYER2:  " << player2 << " (current)" << endl;
    cout << "   Your Name:  ";
    cin >> player2;
    system("CLS");
    return player2;
}

void PLAYER(){ //======================================================================================================|WELCOME PLAYER|;
    if (backgr == 0)
        system("color 0F");
    if (backgr == 1)
        system("color F0");
    int pl;
    do {
        cout << "*********************************************************" << endl;
        cout << "**                     WELCOME!                        **" << endl;
        cout << "**   1. Start new game                                 **" << endl;
        cout << "**   2. Edit player names                              **" << endl;
        cout << "**      (Please using fullscreen (Alt+Enter))          **" << endl;
        cout << "*********************************************************" << endl;
        cout << endl;
        cout << "               Your Choice:   ";
        cin >> pl;
        system("CLS");
    } while (pl < 1 || pl > 2);
    if (pl == 1);
    if (pl == 2){
        PLER1();
        PLER2();
        system("CLS");
    }
}

void SAVE(){ //========================================================================================================|SAVE DATA TO TXT|;
    outfile.open("savedata.txt", ios::app);
    outfile << endl << endl << player1 << "\t\t\t\t\t" << deadO << endl;
    outfile << player2 << "\t\t\t\t\t" << deadX;
    outfile.close();
}

void LOAD(){ //========================================================================================================|LOAD DATA FROM TXT|;
    string temp1, temp2;
    infile.open("savedata.txt", ios::in);
    while(!infile.eof()){
        infile >> player1;
        infile >> temp1;
        infile >> player2;
        infile >> temp2;
    }
    infile.close();
}

int ENDGAME(){ //======================================================================================================|END CURRENT GAME|;
    system("CLS");
    if (backgr == 0)
        system("color 0F");
    if (backgr == 1)
        system("color F0");
    wp = ' ';
    cout << "***********************************************************" << endl;
    cout << "** This will end your current game and go to the result! **" << endl;
    cout << "** Are you sure to continue?                             **" << endl;
    cout << "**                Yes(Y)    **      No(N)                **" << endl;
    cout << "***********************************************************" << endl << endl;
    cout << "           Your Choice: ";
    cin >> wp;
    return 0;
}

void RESULT(){ //======================================================================================================|RESULT BAR|;
    if (backgr == 0)
        system("color 0D");
    if (backgr == 1)
        system("color F5");
    anything = "";
    string winner, runner, cmt1, cmt2;
    double mul;
    if (a<=8) mul=0.5;
    if (a>8&&a<=12) mul=1;
    if (a>12&&a<17) mul=1.5;
    if (a>=17) mul=2;
    int score1, score2;
    if (deadO != deadX){
        if (deadO > deadX){
            winner = player1; runner = player2; score1 = deadO; score2 = deadX;
            if (score1<=2*mul) cmt1 = " (DO NOT play again!)";
            if (score1>2*mul&&score1<=8*mul) cmt1 = " (you're a beginner?)";
            if (score1>8*mul&&score1<=14*mul) cmt1 = " (nice-try!)";
            if (score1>14*mul&&score1<=20*mul) cmt1 = " (you're quite good!)";
            if (score1>20*mul&&score1<=28*mul) cmt1 = " (well-done!)";
            if (score1>28*mul&&score1<=36*mul) cmt1 = " (excellent!!)";
            if (score1>36*mul&&score1<=44*mul) cmt1 = " (perfect!!!)";
            if (score1>44*mul&&score1<=52*mul) cmt1 = " (genius!!!!)";
            if (score1>52*mul&&score1<=62*mul) cmt1 = " (godlike!!!!!)";
            if (score1>62*mul&&score1<=74*mul) cmt1 = " (may the force be with you!)";
            if (score1>74*mul&&score1<=86*mul) cmt1 = " (PlEASE don't play again!!)";
            if (score1>86*mul&&score1<=94*mul) cmt1 = " (you're such evil!!!)";
            if (score1>94*mul&&score1<=108*mul) cmt1 = " (Which planet are you from!!!!)";
            if (score1>108*mul) cmt1 = " (DO NOT KNOW WHAT TO SAY!!!!!)";
            if (score2<=2*mul) cmt2 = " (DO NOT play again!)";
            if (score2>2*mul&&score2<=8*mul) cmt2 = " (you're a beginner?)";
            if (score2>8*mul&&score2<=14*mul) cmt2 = " (nice-try!)";
            if (score2>14*mul&&score2<=20*mul) cmt2 = " (you're quite good!)";
            if (score2>20*mul&&score2<=28*mul) cmt2 = " (well-done!)";
            if (score2>28*mul&&score2<=36*mul) cmt2 = " (excellent!!)";
            if (score2>36*mul&&score2<=44*mul) cmt2 = " (perfect!!!)";
            if (score2>44*mul&&score2<=52*mul) cmt2 = " (genius!!!!)";
            if (score2>52*mul&&score2<=62*mul) cmt2 = " (godlike!!!!!)";
            if (score2>62*mul&&score2<=74*mul) cmt2 = " (may the force be with you!)";
            if (score2>74*mul&&score2<=86*mul) cmt2 = " (PlEASE don't play again!!)";
            if (score2>86*mul&&score2<=94*mul) cmt2 = " (you're such evil!!!)";
            if (score2>94*mul&&score2<=108*mul) cmt2 = " (Which planet are you from!!!!)";
            if (score2>108*mul) cmt2 = " (DO NOT KNOW WHAT TO SAY!!!!!)";
        }
        if (deadX > deadO){
            winner = player2; runner = player1; score1 = deadX; score2 = deadO;
            if (score1<=2*mul) cmt1 = " (DO NOT play again!)";
            if (score1>2*mul&&score1<=8*mul) cmt1 = " (you're a beginner?)";
            if (score1>8*mul&&score1<=14*mul) cmt1 = " (nice-try!)";
            if (score1>14*mul&&score1<=20*mul) cmt1 = " (you're quite good!)";
            if (score1>20*mul&&score1<=28*mul) cmt1 = " (well-done!)";
            if (score1>28*mul&&score1<=36*mul) cmt1 = " (excellent!!)";
            if (score1>36*mul&&score1<=44*mul) cmt1 = " (perfect!!!)";
            if (score1>44*mul&&score1<=52*mul) cmt1 = " (genius!!!!)";
            if (score1>52*mul&&score1<=62*mul) cmt1 = " (godlike!!!!!)";
            if (score1>62*mul&&score1<=74*mul) cmt1 = " (may the force be with you!)";
            if (score1>74*mul&&score1<=86*mul) cmt1 = " (PlEASE don't play again!!)";
            if (score1>86*mul&&score1<=94*mul) cmt1 = " (you're such evil!!!)";
            if (score1>94*mul&&score1<=108*mul) cmt1 = " (Which planet are you from!!!!)";
            if (score1>108*mul) cmt1 = " (DO NOT KNOW WHAT TO SAY!!!!!)";
            if (score2<=2*mul) cmt2 = " (DO NOT play again!)";
            if (score2>2*mul&&score2<=8*mul) cmt2 = " (you're a beginner?)";
            if (score2>8*mul&&score2<=14*mul) cmt2 = " (nice-try!)";
            if (score2>14*mul&&score2<=20*mul) cmt2 = " (you're quite good!)";
            if (score2>20*mul&&score2<=28*mul) cmt2 = " (well-done!)";
            if (score2>28*mul&&score2<=36*mul) cmt2 = " (excellent!!)";
            if (score2>36*mul&&score2<=44*mul) cmt2 = " (perfect!!!)";
            if (score2>44*mul&&score2<=52*mul) cmt2 = " (genius!!!!)";
            if (score2>52*mul&&score2<=62*mul) cmt2 = " (godlike!!!!!)";
            if (score2>62*mul&&score2<=74*mul) cmt2 = " (may the force be with you!)";
            if (score2>74*mul&&score2<=86*mul) cmt2 = " (PlEASE don't play again!!)";
            if (score2>86*mul&&score2<=94*mul) cmt2 = " (you're such evil!!!)";
            if (score2>94*mul&&score2<=108*mul) cmt2 = " (Which planet are you from!!!!)";
            if (score2>108*mul) cmt2 = " (DO NOT KNOW WHAT TO SAY!!!!!)";
        }
        system("CLS");
        cout << "************************************************************************************************" << endl;
        cout << "**                                       CONGRATULATION!                                      **" << endl;
        cout << "************************************************************************************************" << endl << endl;
        cout << "\t\t\t\t" << "Winner: " << winner << "\t\t" << score1 << cmt1 << endl << endl;
        cout << "\t\t\t\t" << "Loser:  " << runner << "\t\t" << score2 << cmt2 << endl << endl;
        cout << "************************************************************************************************" << endl;
        cout << "                                        Press Any Thing: ";
        cin >> anything;
        system("CLS");
    }
    if (deadO == deadX){
        system("CLS");
        cout << "***********************************************************************************************" << endl;
        cout << "**                                         DRAW MATCH!                                       **" << endl;
        cout << "***********************************************************************************************" << endl << endl;
        cout << "                PLAYER1:     " << player1 << "\t\t" << deadO << endl << endl;
        cout << "                PLAYER2:     " << player2 << "\t\t" << deadX << endl << endl;
        cout << "***********************************************************************************************" << endl;
        cout << "                                        Press Any Thing: ";
        cin >> anything;
    }
    system("CLS");
}

int ENDAGAIN(){ //=====================================================================================================|END INTERACT|;
    if (backgr == 0)
        system("color 0F");
    if (backgr == 1)
        system("color F0");
    do{
        system("CLS");
        eag = ' ';
        cout << "********************************************************" << endl;
        cout << "** Do you want to play again of go back to main menu  **" << endl;
        cout << "**         Again(A)         **        Menu(M)         **" << endl;
        cout << "********************************************************" << endl << endl;
        cout << "           Your Choice: ";
        cin >> eag;
        if (eag == 'A' || eag == 'a'){ game(); break;}
        if (eag == 'M' || eag == 'm'){ printmenu(); break;}
    }while(1);
    return 0;
}

int game();
int printmenu();
int rules();
int highscore();
int credit();
int setting();
int logo();

void PLAYCONSOLE(){ //===========================================================================================|PLAYING WITH CONSOLE|;
    int x = a / 2;
    int y = a / 2;
    gotoXY(y, x);
    point(x, y);
    int k;
    do {
        do {
            if (backgr == 0)
                system("color 09");
            if (backgr == 1)
                system("color F1");
            DEADORALIVE(turn);
            console(x, y);
            system("CLS");
            GOG();
            GUIDE2();
            STATUS();
            TURN(turn);
            LETCOUNT();
            WARNING();
        loop1:;
            k = console(x, y);
            if (k == 0)
                goto loop1;
            if (quit == 1){
                QUITGAME();
                if (gg == 'Y' || gg == 'y'){
                    break;
                }
                else{
                    quit = 0;
                    cblack = 1;
                    cwhite = 1;
                }
            }
            if (c_undo == 1){
                if (turn > 1) --turn;
                UNDO();
            }
            if (remake == 1){
                REMAKE();
                if (rm == 'Y' || rm == 'y'){
                    game(); break;
                }
                else{
                    remake = 0;
                    cblack = 1;
                    cwhite = 1;
                }
            }
            if (bmenu == 1){
                BACKMENU();
                if (bm == 'Y' || bm == 'y'){
                    printmenu(); break;
                }
                else{
                    bmenu = 0;
                    cblack = 1;
                    cwhite = 1;
                }
            }
            if (result == 1){
                ENDGAME();
                if (wp == 'Y' || wp == 'y'){
                    SAVE();
                    RESULT();
                    ENDAGAIN(); break;
                }
                else{
                    result = 0;
                    cblack = 1;
                    cwhite = 1;
                }
            }
        } while (cblack == 1 && cwhite == 1);
        ++turn;
        if (quit == 1) break;
    } while (1);
}

void PLAYCOORDINATE(){ //========================================================================================|PLAYING WITH COORDINATE|;
    do {
        do {
            if (backgr == 0)
                system("color 0D");
            if (backgr == 1)
                system("color F5");
            DEADORALIVE(turn);
			GOG();
			GUIDE1();
			STATUS();
			TURN(turn);
			LETCOUNT();
			WARNING();
			if(turn % 2 != 0){
                cinBlack();
                system("CLS");
                if (black == "REMAKE"){
                    REMAKE();
                    if (rm == 'Y' || rm == 'y'){
                        game(); break;
                    }
                    else{
                        cblack = 1;
                    }
                }
                if (black == "QUIT"){
                    QUITGAME();
                    if (gg == 'Y' || gg == 'y'){
                        quit = 1; break;
                    }
                    else{
                        cblack = 1;
                    }
                }
                if (black == "MENU"){
                    BACKMENU();
                    if (bm == 'Y' || bm == 'y'){
                        printmenu(); break;
                    }
                    else{
                        cblack = 1;
                    }
                }
                if (black == "END"){
                    ENDGAME();
                    if (wp == 'Y' || wp == 'y'){
                        SAVE();
                        RESULT();
                        ENDAGAIN(); break;
                    }
                    else{
                        cblack = 1;
                    }
                }
                else if (black == "UNDO"){
                    if (turn > 1) --turn;
                    UNDO();
                }
                else if (cblack == 0){
                    moveBlack();
                    ++turn;
                }
			}
            else{
                cinWhite();
                system("CLS");
                if (white == "REMAKE"){
                    REMAKE();
                    if (rm == 'Y' || rm == 'y'){
                        game(); break;
                    }
                    else{
                        cwhite = 1;
                    }
                }
                if (white == "QUIT"){
                    QUITGAME();
                    if (gg == 'Y' || gg == 'y'){
                        quit = 1; break;
                    }
                    else{
                        cwhite = 1;
                    }

                }
                if (white == "MENU"){
                    BACKMENU();
                    if (bm == 'Y' || bm == 'y'){
                        printmenu();
                        quit = 1; break;
                    }
                    else{
                        cwhite = 1;
                    }
                }
                if (white == "END"){
                    ENDGAME();
                    if (wp == 'Y' || wp == 'y'){
                        SAVE();
                        RESULT();
                        ENDAGAIN(); break;
                    }
                    else{
                        cwhite = 1;
                    }
                }
                else if (white == "UNDO"){
                    if (turn > 1) --turn;
                    UNDO();
                }
                else if (cwhite == 0){
                    moveWhite();
                    ++turn;
                }
            }
            if (remake == 1) break;
            if (quit == 1) break;
        } while (cwhite == 1 || cblack == 1);
        if (remake == 1) break;
        if (quit == 1) break;
    } while (1);
}

void BEHAVIOR(){ //==============================================================================================|PLAYING BEHAVIOR|;
    CHOOSECTR();
    turn = 1;
    system("CLS");
    switch (ctr){
        case 1: PLAYCOORDINATE(); break;
        case 2: PLAYCONSOLE(); break;
    }

}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////OPERATIONS;

int game(){ //////////////////////////////////////////////////////////////////////////////////////////////////////START NEW GAME;
    system("CLS");
	if (backgr == 0)
        system("color 09");
    if (backgr == 1)
        system("color F1");
	PLAYER();
    SETUP();
    BEHAVIOR();
    return 0;
}

int printmenu(){ ////////////////////////////////////////////////////////////////////////////////////////////////MAIN MENU;
    system("CLS");
    if (backgr == 0)
        system("color 0C");
    if (backgr == 1)
        system("color F4");
	cout << "* * * * * * * * * * * * * *" << endl;
	cout << "* * * * * * * * * * * * * *" << endl;
	cout << "* *                     * *" << endl;
	cout << "* *      MAIN MENU      * *" << endl;
	cout << "* *                     * *" << endl;
	cout << "* *   1. New Game       * *" << endl;
	cout << "* *   2. Instruction    * *" << endl;
	cout << "* *   3. Highscore      * *" << endl;
	cout << "* *   4. Setting        * *" << endl;
	cout << "* *   5. Credit         * *" << endl;
	cout << "* *   6. Quit           * *" << endl;
	cout << "* *                     * *" << endl;
	cout << "* * * * * * * * * * * * * *" << endl;
	cout << "* * * * * * * * * * * * * *" << endl;
	cout << endl;
	cout << "Your Choice: ";
	int numb;
	cin >> numb;
	switch (numb)
	{
	case 1:
	{
		game();
		break;
	}
	case 2:
	{
		rules();
		break;
	}
	case 3:
	{
	    highscore();
		break;
	}
	case 4:
	{
	    setting();
	    printmenu();
	    break;
	}
	case 5:
    {
        credit();
        break;
    }
	case 6:
	{
	    quit = 1;
	    logo();
		QUITGAME0();
		break;
	}
	default:
	{
        printmenu();
        break;
	}
	}
	return 0;
}

void printIns(){ ////////////////////////////////////////////////////////////////////////////////////////////////RULES;
    system("CLS");
    if (backgr == 0)
        system("color 0E");
    if (backgr == 1)
        system("color F6");
	cout << "*******************************************************THE RULE***********************************************************" << endl;
	cout << endl;
	cout << "A game of Go starts with an empty board. Each player has an effectively unlimited supply of pieces (called stones), one" << endl;
	cout << "taking the black stones, the other taking white. The main object of the game is to use your stones to form territories by" << endl;
	cout << "surrounding vacant areas of the board. It is also possible to capture your opponent's stones by completely surrounding" << endl;
	cout << "them." << endl;
	cout << endl;
	cout << "Players take turns, placing one of their stones on a vacant point at each turn, with Black playing first. Note that stones" << endl;
	cout << "are placed on the intersections of the lines rather than in the squares and once played stones are not moved. However they" << endl;
	cout << "may be captured, in which case they are removed from the board, and kept by the capturing player as prisoners." << endl;
	cout << endl;
	cout << "*************************************************THE END OF THE GAME*******************************************************" << endl;
	cout << endl;
	cout << "When you think you can't gain any more territory, reduce your opponent's territory or capture more strings, instead of" << endl;
	cout << "playing a stone on the board you pass and hand a stone to your opponent as a prisoner. A Black pass followed by a White" << endl;
	cout << "pass ends the game (since Black played first, White must play last)." << endl;
	cout << endl;
	cout << "Any hopeless strings are removed and become prisoners. If you cannot agree whether a string is dead or not, then continue" << endl;
	cout << "playing; you can then complete the capture of the disputed strings or confirm they are alive. (Playing after such a" << endl;
	cout << "continuation does not change the score as each pass gives up a prisoner.)" << endl;
	cout << endl;
	cout << "*************************************************************************************************************************" << endl;
	cout << endl;
}

int rules(){ ////////////////////////////////////////////////////////////////////////////////////////////////////RULES INTERACT;
	string MorQ;
	system("cls");
	printIns();
	cout << endl;
	cout << endl;
	cout << "**************************************" << endl;
	cout << "**           Back to menu?          **" << endl;
	cout << "**      Yes(Y)    **      No(N)     **" << endl;
	cout << "**************************************" << endl;
	cout << endl;
	cout << "Your Choice: ";
	cin >> MorQ;
	if (MorQ == "y" || MorQ == "Y" || MorQ == "yes" || MorQ == "YES")
	{
		system("cls");
		printmenu();
	}
	if (MorQ == "n" || MorQ == "N" || MorQ == "no" || MorQ == "NO")
    {
        system("cls");
        rules();
    }
	cout << endl;
	return 0;
}

int highscore(){ ////////////////////////////////////////////////////////////////////////////////////////////////HIGHSCORE/HISTORY;
    system("CLS");
    if (backgr == 0)
        system("color 0A");
    if (backgr == 1)
        system("color F2");
    string MorQ1;
    string user[30];
    int score[30];
    cout << "*****************************HISTORY**********************************" << endl;
    infile.open("savedata.txt", ios::in);
    for(int i = 0; !infile.eof(); ++i){
        infile >> user[i];
        infile >> score[i];
        cout << "\t" << i+1 << "\t" << user[i] << "\t\t\t\t\t" << score[i] << endl;
    }
    infile.close();
    cout << "**********************************************************************" << endl << endl << endl;
    cout << "**************************************" << endl;
	cout << "**           Back to menu?          **" << endl;
	cout << "**      Yes(Y)    **      No(N)     **" << endl;
	cout << "**************************************" << endl;
	cout << endl;
	cout << "Your Choice: ";
	cin >> MorQ1;
	if (MorQ1 == "y" || MorQ1 == "Y" || MorQ1 == "yes" || MorQ1 == "YES")
	{
		system("cls");
		printmenu();
	}
	if (MorQ1 == "n" || MorQ1 == "N" || MorQ1 == "no" || MorQ1 == "NO")
    {
        system("cls");
        highscore();
    }
	cout << endl;
	return 0;
}

int credit(){ ///////////////////////////////////////////////////////////////////////////////////////////////////CREDIT;
    if (backgr == 0)
        system("color 0F");
    if (backgr == 1)
        system("color F0");
    string MorQ2;
    anything = "";
    system("CLS");
    cout << "******************************************CREDIT************************************" << endl;
    cout << endl << endl << endl;
    cout << "                                    ---IO$TRE@M TE@M---" << endl << endl << endl;
    cout << "                                       ---Member---" << endl << endl;
    cout << "                    (Leader) Nguyen Song Hung Anh. CODE-1552025" << endl << endl;
    cout << "                                  Vu Dinh Anh Thu. CODE-1552372" << endl << endl;
    cout << "                                  Truong The Dinh. CODE-1552061" << endl << endl;
    cout << "                                       Vu Hai Nam. CODE-1550046" << endl << endl << endl;
    cout << "                             ---Fundamentals Of C++ Programming---" << endl << endl << endl;
    cout << "                                      ---Lecturers---" << endl << endl;
    cout << "                                      Nguyen Duc Dung" << endl << endl;
    cout << " " << endl << endl << endl;
    cout << "                       ---Ho Chi Minh City University Of Technology---" << endl << endl;
    cout << "                          ---Office For International Study Programs---" << endl << endl << endl;
    cout << "                                 ---THANK FOR SUPPORTING US---" << endl;
    cout << "                                      -------------------" << endl;
    cout << "                                           --------- " << endl << endl;;
    cout << "                                                       Contact: hnvipmh123@gmail.com" << endl;
    cout << "                                                               01636990493 (Mr. Nam)" << endl;
    cout << "                                                         anhhungsongnguyen@gmail.com" << endl;
    cout << "                                                               01686435274 (Mr. Anh)" << endl;
    cout << "************************************************************************************" << endl;
    cout << "                                  Press Any Thing: ";
    cin >> anything;
    cout << "**************************************" << endl;
	cout << "**           Back to menu?          **" << endl;
	cout << "**      Yes(Y)    **      No(N)     **" << endl;
	cout << "**************************************" << endl;
	cout << endl;
	cout << "Your Choice: ";
	cin >> MorQ2;
	if (MorQ2 == "y" || MorQ2 == "Y" || MorQ2 == "yes" || MorQ2 == "YES")
	{
		system("cls");
		printmenu();
	}
	if (MorQ2 == "n" || MorQ2 == "N" || MorQ2 == "no" || MorQ2 == "NO")
    {
        system("cls");
        credit();
    }
	cout << endl;
	return 0;
}

int logo(){
    system("CLS");
    if (backgr == 0)
        system("color 0E");
    if (backgr == 1)
        system("color F9");
    anything = "";
    cout << "oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo" << endl;
    cout << "oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo" << endl;
    cout << "oo                                                                                            oo" << endl;
    cout << "oo      oooooo       oooooo           oooooo         oooo       ooooo     ooooo  oooooooooo   oo" << endl;
    cout << "oo    oo      oo   oo      oo       oo      oo      oo ooo      ooo oo   oo ooo  ooo          oo" << endl;
    cout << "oo   ooo          ooo      ooo     ooo             oo   ooo     ooo  oo oo  ooo  ooo          oo" << endl;
    cout << "oo   ooo     oooo ooo      ooo     ooo     oooo   oo ooo ooo    ooo   ooo   ooo  ooooooo      oo" << endl;
    cout << "oo   ooo      ooo ooo      ooo     ooo      ooo  oo       ooo   ooo         ooo  ooo          oo" << endl;
    cout << "oo    oo      oo   oo      oo       oo      oo  oo         ooo  ooo         ooo  ooo          oo" << endl;
    cout << "oo      oooooo       oooooo           oooooo   oo           ooo ooo         ooo  oooooooooo   oo" << endl;
    cout << "oo                                                                                            oo" << endl;
    cout << "oo                                   ooooo ooooo   o   oo  oo                                 oo" << endl;
    cout << "oo  >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>     o   ooo    ooo  o oo o   <<<<<<<<<<<<<<<<<<<<<<<<<<<<  oo" << endl;
    cout << "oo                                     o   ooooo o   o o    o                                 oo" << endl;
    cout << "oo                                                                                            oo" << endl;
    cout << "oo   ooooooooo   oooooo      ooooo   ooooooooo oooooo    ooooooo     oooo     oooo     oooo   oo" << endl;
    cout << "oo      ooo    oo      oo  ooo          ooo    ooo   oo  ooo        oo ooo    ooo oo oo ooo   oo" << endl;
    cout << "oo      ooo   ooo      ooo   ooooo      ooo    ooo oo    ooooo     oo o ooo   ooo  ooo  ooo   oo" << endl;
    cout << "oo      ooo    oo      oo        ooo    ooo    ooo  ooo  ooo      oo     ooo  ooo       ooo   oo" << endl;
    cout << "oo   ooooooooo   oooooo      ooooo      ooo    ooo  ooo  ooooooo oo       ooo ooo       ooo   oo" << endl;
    cout << "oo                                                                                            oo" << endl;
    cout << "oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo" << endl;
    cout << "oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo" << endl;
    cout << endl << endl << endl << endl;
    cout << "                                         PRESS ANY THING: ";
    cin >> anything;
    system("CLS");
    return 0;
}

int setting(){ //////////////////////////////////////////////////////////////////////////////////////////////////SETTING;
    system("CLS");
    if (backgr == 0)
        system("color 0F");
    if (backgr == 1)
        system("color F0");
    cout << "****************************SETTING********************************" << endl;
    cout << "** This is the first time setting.                               **" << endl;
    cout << "** Which color of background do you prefer?                      **" << endl;
    cout << "**            Light(L)        ***        Dark(D)                 **" << endl;
    cout << "*******************************************************************" << endl << endl;
	do {
		cout << "               Your Choice:  ";
		cin >> color;
		if (color == 'L' || color == 'l') {
			backgr = 1;
			break;
		}
		if (color == 'D' || color == 'd') {
			backgr = 0;
			break;
		}
	}
	while (true);
    system("CLS");
    return 0;
}

int main(){ /////////////////////////////////////////////////////////////////////////////////////////////////////MAIN PROGRAM;
    system("Color 0F");
    FSETTING();
    setting();
    logo();
    LOAD();
	printmenu();
	system("pause");
	return 0;
}

