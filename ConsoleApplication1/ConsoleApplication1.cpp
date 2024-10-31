#include <iostream>
#include <vector>
#include <string>
// i = y ET j = x !!!!!!!!!!!!!!!
// i = y ET j = x !!!!!!!!!!!!!!!
// i = y ET j = x !!!!!!!!!!!!!!!
// i = y ET j = x !!!!!!!!!!!!!!!
// i = y ET j = x !!!!!!!!!!!!!!!
// i = y ET j = x !!!!!!!!!!!!!!!
// i = y ET j = x !!!!!!!!!!!!!!!
// i = y ET j = x !!!!!!!!!!!!!!!
// i = y ET j = x !!!!!!!!!!!!!!!
// i = y ET j = x !!!!!!!!!!!!!!!
// i = y ET j = x !!!!!!!!!!!!!!!
// i = y ET j = x !!!!!!!!!!!!!!!
// i = y ET j = x !!!!!!!!!!!!!!!
// i = y ET j = x !!!!!!!!!!!!!!!
// i = y ET j = x !!!!!!!!!!!!!!!
// i = y ET j = x !!!!!!!!!!!!!!!
// i = y ET j = x !!!!!!!!!!!!!!!
// i = y ET j = x !!!!!!!!!!!!!!!
// i = y ET j = x !!!!!!!!!!!!!!!
// i = y ET j = x !!!!!!!!!!!!!!!
// i = y ET j = x !!!!!!!!!!!!!!!
// i = y ET j = x !!!!!!!!!!!!!!!
// i = y ET j = x !!!!!!!!!!!!!!!
// i = y ET j = x !!!!!!!!!!!!!!!
// i = y ET j = x !!!!!!!!!!!!!!!
using namespace std;

const int len = 30;
const int hei = 16;
int currentLen = 0;
int currentHei = 0;
bool isEnd = false;

struct Case {
    bool bomb = false;
    bool flag = false;
    bool hidden = true;
    int val = 0;
};
Case grille[hei][len];

void display() {
    //cout << currentHei;
    //cout << currentLen;

    cout << "      ";
    for (int i = 0; i < currentLen; i++)
        if (i < 9)
            cout << "|" << i << "|";
        else if (i == currentLen - 1)
            cout << "|" << i << "|";
        else
            cout << "|" << i;
    cout << endl;
    for (int i = 0; i < currentHei; i++) {
        if (i < 10)
            cout << " " << i << " -- ";
        else
            cout << i << " -- ";

        for (int j = 0; j < currentLen; j++)
        {
            if (grille[i][j].hidden) {      // j puis i pour avoir ligne - colonne
                if (grille[i][j].flag)
                    cout << "[F]";
                else
                    cout << "[ ]";
            }
            if (grille[i][j].hidden == false) {
                if (grille[i][j].bomb)
                    cout << "[X]";
                else if (grille[i][j].val == 0)
                    cout << "[-]";   
                else
                    cout << "[" << grille[i][j].val << "]";
            }
        }
        cout << endl;
    }
}
void generateGrid(int dif) {
    //vector<char>grid;     (useless)
    switch (dif) {
    case 1:

        currentLen = 9;
        currentHei = 9;
        break;

    case 2:

        currentLen = 16;
        currentHei = 16;
        break;

    case 3:

        currentLen = 30;
        currentHei = 16;
        break;
    }
    display();
}


void generateBomb(int dif,int startx,int starty) { //ne dépasse jamais la colonne 17 
    //la génération dépasse le nombre de ligne(génération ligne infinie?)
    int bombNumber = 0;
    switch (dif) {
    case 1:
        bombNumber = 10;
        break;
    case 2:
        bombNumber = 40;
        break;
    case 3:
        bombNumber = 99;
        break;
    default:
        bombNumber = 10;
        break;
    }

    for (int i = 0; i < bombNumber; i++)
    {
        int x = rand() % currentLen;
        int y = rand() % currentHei;
        {
            if (grille[y][x].bomb || (x == startx && y==starty) || (x == startx+1 && y == starty+1) || (x == startx + 1 && y == starty ) || (x == startx + 1 && y == starty - 1) || (x == startx -1 && y == starty - 1) || (x == startx - 1 && y == starty ) || (x == startx - 1 && y == starty + 1) || (x == startx && y == starty + 1) || (x == startx && y == starty - 1))
                i--;
            else
                grille[y][x].bomb = true;
        }
        
    }
}
void askCoordinates(int coord[]) {
    cout << "Veuillez rentrer des coordonnees : " << endl;
    cout << "j : ";
    cin >> coord[0];
    cout << endl << "i : ";
    cin >> coord[1];
}
void flag() {

    int coord[2];
    askCoordinates(coord);
    cout << grille[coord[0]][coord[1]].flag;
    grille[coord[0]][coord[1]].flag = true; // utile pour le DLC Auto-Clear
    cout << grille[coord[0]][coord[1]].flag << endl;

}
void reveal(int y,int x) {    
    if (x<0 || y<0 || y>currentHei - 1 || x>currentLen - 1 || grille[y][x].hidden == false)
        return;
    grille[y][x].hidden = false;
    if (grille[y][x].val == 0) {
        reveal(y - 1, x - 1);
        reveal(y - 1, x);
        reveal(y - 1, x + 1);
        reveal(y, x - 1);
        reveal(y, x + 1);
        reveal(y + 1, x - 1);
        reveal(y + 1, x);
        reveal(y + 1, x + 1);
    }
}
void dig() {
    
    int coord[2];
    askCoordinates(coord);
    int y = coord[0];
    int x = coord[1];    
    reveal(y,x);    
    if (grille[y][x].bomb)
        isEnd = true;    
}
int check(int y, int x) {
    //prendre les coordonnées du dig
    if (x<0 || y<0 || y>currentHei - 1 || x>currentLen - 1)
        return 0;
    if (grille[y][x].bomb)
        return 1;
    return 0;
}
void detection() {
    int val = 0;

    for (int i = 0; i < currentHei; i++)                
        for (int j = 0; j < currentLen; j++) {         
            val += check(i + 1, j + 1);
            val += check(i + 1, j);
            val += check(i + 1, j - 1);
            val += check(i - 1, j - 1);
            val += check(i - 1, j);
            val += check(i - 1, j + 1);
            val += check(i, j + 1);
            val += check(i, j - 1);
            grille[i][j].val = val;
            val = 0;
        }
    
    

}
void first(int dif) {
    int first;
    int coord[2];
    cout << endl;
    //display();
    cout << endl;
    cout << "1. Dig" << endl;    
    cout << "2. Leave" << endl;
    cout << "Veuillez effectuer une action." << endl << "> ";
    cin >> first;
    switch (first) {
    case 1:
        askCoordinates(coord);
        generateBomb(dif,coord[0],coord[1]);
        detection();
        reveal(coord[0], coord[1]);        
        break;    
    case 2:
        isEnd = true;
    }
    display();
}

void restart() {
    
    for (int i = 0; i < currentHei; i++) 
        

        for (int j = 0; j < currentLen; j++)

            grille[i][j].bomb=false;
            grille[i][j].flag=false;
            grille[i][j].hidden=true;

    }
}
    


int main()
{
    /*string seed;
    cout << "Veuillez enter votre graine : ";
    cin >> seed;
    int iseed = stoi(seed);
    srand(iseed);*/

    srand(time(0));
    int dif;
    cout << "1. Easy (9x9)" << endl;
    cout << "2. Medium (16x16)" << endl;
    cout << "3. Hard (30x16)" << endl;
    cout << endl << "Veuillez choisir une difficulte : ";
    // Choix de la difficulté
    cin >> dif;
    generateGrid(dif);
    first(dif);
    while (isEnd == false)
    {
        int choice;
        cout << endl;
        //display();
        cout << endl;
        cout << "1. Dig" << endl;
        cout << "2. Flag" << endl;
        cout << "3. Leave" << endl;
        cout << "Veuillez effectuer une action." << endl << "> ";
        cin >> choice;
        switch (choice) {
        case 1:
            dig();
            display();
            break;
        case 2:
            flag();            
            display();
            break;
        case 3:
            isEnd = true;
        }
    }
    if (isEnd = true) {
        for (int i = 0; i < currentLen; i++)
            for (int j = 0; j < currentHei; j++)
            {
                if ((grille[j][i].bomb))
                    (grille[j][i].hidden) = false;
            }
        isEnd=False;
        restart();
        cout << endl;
        display();
        int choix;
        cout << "rejouer ?" << endl;
        cout << "1. Oui" << endl;
        cout << "2. Non";
        cin >> choix;
        if (choix == 1)            
            main();
    }    
}