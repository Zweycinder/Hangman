#include <iostream>
#include <windows.h>
#include <vector>//                                                                                     special type of array
#include <fstream>//                                                                                    to use the document that have HANGMAN WORDS                                                                                                                                                                                                                                                                                                                                                         svbe
#include <string>
#include <time.h>
#include <cstdlib>
#include <cctype>

using namespace std;

char GameNumber;

HANDLE ConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);


void HangmanMessage(string GameH1Message, bool GameH1top = true, bool GameH1Bottom = true);//          this is the main code to draw the game
void HangmanDrawTheGuy(int HangmanGuessCount = 0);
void HangmanLetters(string HangmanLetterInput, char from, char to);
void HangmanAvailableLetters(string Took);
bool HangmanWordsCheckWin(string HangmanTheWord, string HangmanGuessed);
string LoadHangmanRandomWords(string WordsPath);
int HangmanSaveChancesLeft(string HangmanWords, string HangmanGuesses);
void HANGMANTHEGAME();
void hangmanlists();


char PickGameMoodHS;
int PickRoom;

void resize(int X, int Y, int Z);

int HangmanLists;//                                                                                     to see what list we will choose

int main()
{
    HANGMANTHEGAME();
    return 0;
}

void HANGMANTHEGAME()
{
    resize(35, 35, 700);
    bool Hangmanagain;
    play:
    hangmanlists();
    cout << "1) play again 2) End\n>";
    cin >> Hangmanagain;
    if (Hangmanagain == true)
        goto play;
}
/* the MAIN HangmanGame function that use all the hangman functions and cout them in the sort
it is rn and also what make the user input the letter   */

void hangmanlists()
{
    srand(time(0));
    string text;
    char letter;
    string HangmanGuesses;
    string TheHangmanWord;
    int TRIES = 0;
    bool Win = false;
    switch (rand() % 5)
    {
    case 0: TheHangmanWord = LoadHangmanRandomWords("HangmanFruit.txt");
            text = "Guess The Fruit";
         break;
    case 1: TheHangmanWord = LoadHangmanRandomWords("HangmanAnimals.txt");
            text = "Guess The Animal";
         break;
    case 2: TheHangmanWord = LoadHangmanRandomWords("HangmanPartsOfBody.txt");
            text = "Guess The Part of Body";
         break;
    case 3: TheHangmanWord = LoadHangmanRandomWords("HangmanSuperhero.txt");
            text = "Guess The Super Hero";
         break;
    case 4: TheHangmanWord = LoadHangmanRandomWords("HangmanCars.txt");
            text = "Guess The Car Company";
         break;

    }


    do
    {
        system("cls");
        SetConsoleTextAttribute(ConsoleColor, 23);
        HangmanMessage("ZWEY'S HANGMAN");
        SetConsoleTextAttribute(ConsoleColor, 7);
        HangmanDrawTheGuy(TRIES);
        HangmanAvailableLetters(HangmanGuesses);
        HangmanMessage(text);
        Win = HangmanWordsCheckWin(TheHangmanWord, HangmanGuesses);

        if (Win || TRIES > 7) 
        {
            break;
        }

        cin >> letter;
        letter = toupper(letter);

        if (HangmanGuesses.find(letter) == string::npos) {
            HangmanGuesses += letter;
        }

        TRIES = HangmanSaveChancesLeft(TheHangmanWord, HangmanGuesses);

    } while (true);

    if (Win)
    {
        SetConsoleTextAttribute(ConsoleColor, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        HangmanMessage("YOU WON");
        SetConsoleTextAttribute(ConsoleColor, 7);
    }
    else
    {
        SetConsoleTextAttribute(ConsoleColor, FOREGROUND_RED);
        HangmanMessage("GAME OVER");
        SetConsoleTextAttribute(ConsoleColor, 7);
    }
}



void HangmanMessage(string GameH1Message, bool GameH1top, bool GameH1Bottom)//                         to draw the hangman border
{
    if (GameH1top)
    {
        cout << "+-----------------------------------+" << endl;
        cout << "|";
    }
    else
    {
        cout << "|";
    }
    /*     +-----------------------------------+
           |
    OR
           |
                                                     */
    bool GameH1front = true;
    for (int i = GameH1Message.length(); i < 35; i++)
    {
        if (GameH1front)
        {
            GameH1Message = " " + GameH1Message;
        }
        else
        {
            GameH1Message = GameH1Message + " ";
        }
        GameH1front = !GameH1front;
    }
    /*     +-----------------------------------+
           |             *SOMEWORD*                  */
    cout << GameH1Message.c_str();//                                                                    this is to delete the old cout and cout what he have

    if (GameH1Bottom)
    {
        cout << "|" << endl;
        cout << "+-----------------------------------+" << endl;
    }
    else
    {
        cout << "|" << endl;
    }
    /*     +-----------------------------------+
                                               |
    OR
                                               |
                                                    */
}

void HangmanDrawTheGuy(int HangmanGuessCount)//                                                         To Draw the hangman himself when the user get wrong guesses
{
    if (HangmanGuessCount >= 1)
    {
        SetConsoleTextAttribute(ConsoleColor, FOREGROUND_RED);
        HangmanMessage("|", false, false);
        SetConsoleTextAttribute(ConsoleColor, 7);
    }
    else
        HangmanMessage("", false, false);
    //One Mistake
    //                  |

    if (HangmanGuessCount >= 2)
    {
        SetConsoleTextAttribute(ConsoleColor, FOREGROUND_RED);
        HangmanMessage("|", false, false);
        SetConsoleTextAttribute(ConsoleColor, 7);
    }
    else
        HangmanMessage("", false, false);
    //Two Mistakes
    /*                  |
                        |
    */

    if (HangmanGuessCount >= 3)
    {
        SetConsoleTextAttribute(ConsoleColor, FOREGROUND_RED);
        HangmanMessage("O", false, false);
        SetConsoleTextAttribute(ConsoleColor, 7);

    }
    else
        HangmanMessage("", false, false);
    //Three Mistakes
    /*                  |
                        |
                        0
    */
    if (HangmanGuessCount == 4)//                                                                        we will need to put == this time because if we put >= the /|\ all in the seventh mistake
    {
        SetConsoleTextAttribute(ConsoleColor, FOREGROUND_RED);
        HangmanMessage("/ ", false, false);
        SetConsoleTextAttribute(ConsoleColor, 7);
    }
    //Four Mistakes
    /*                  |
                        |
                        0
                       /
    */
    if (HangmanGuessCount == 5)
    {
        SetConsoleTextAttribute(ConsoleColor, FOREGROUND_RED);
        HangmanMessage("/|", false, false);
        SetConsoleTextAttribute(ConsoleColor, 7);
    }
    //Five Mistakes
    /*                  |
                        |
                        0
                       /|
    */
    if (HangmanGuessCount >= 6)
    {
        SetConsoleTextAttribute(ConsoleColor, FOREGROUND_RED);
        HangmanMessage("/|\\", false, false);//                                                            we used double \ because one slash it will count as the ESC character but if we use \\ it will be like ESC and cout "\"
        SetConsoleTextAttribute(ConsoleColor, 7);
    }
    else
        HangmanMessage("", false, false);
    //Six Mistakes
    /*                  |
                        |
                        0
                       /|\
    */
    if (HangmanGuessCount == 7)//                                                                         we will need to put == this time because if we put >= the / \ all in the seventh mistake
    {
        SetConsoleTextAttribute(ConsoleColor, FOREGROUND_RED);
        HangmanMessage("/ ", false, false);
        SetConsoleTextAttribute(ConsoleColor, 7);
    }
    //Seven Mistakes
    /*                  |
                        |
                        0
                       /|\
                       /
    */
    if (HangmanGuessCount >= 8)
    {
        SetConsoleTextAttribute(ConsoleColor, FOREGROUND_RED);
        HangmanMessage("/ \\", false, false);//                                                            we used double \ because one slash it will count as the ESC character but if we use \\ it will be like ESC and cout "\"
        SetConsoleTextAttribute(ConsoleColor, 7);
    }
    else
        HangmanMessage("", false, false);
    //Eight Mistakes
    /*                  |
                        |
                        0
                       /|\
                       / \
    */
}

void HangmanLetters(string HangmanLetterInput, char from, char to)//                                        to show or hide latters
{
    string CharExistOrNot;
    for (char i = from; i <= to; i++)
    {
        if (HangmanLetterInput.find(i) == string::npos)
        {
            CharExistOrNot += i;
            CharExistOrNot += " ";
        }
        else
            CharExistOrNot += " ";
    }
    HangmanMessage(CharExistOrNot, false, false);
}
/*  this function is to hide the letters that are not in the guessed
    word, when its wrong it will delete that letter and add empty
    space in it                                           */

void HangmanAvailableLetters(string Took)
{
    HangmanMessage("Available Letters");
    HangmanLetters(Took, 'A', 'M');
    HangmanLetters(Took, 'N', 'Z');
}
/* this function is to show small box with message inside and to show
   all the letters as two rows from A to Z
       +-----------------------------------+
       |         Available Letters         |
       +-----------------------------------+
       |           ABCDEFGHIJKLM           |
       |           NOPQRSTUVWXYZ           |
       +-----------------------------------+              */

bool HangmanWordsCheckWin(string HangmanTheWord, string HangmanGuessed)
{
    bool won = true;
    string HangmanPlaceHolder;
    for (int i = 0; i < HangmanTheWord.length(); i++)
    {
        if (HangmanGuessed.find(HangmanTheWord[i]) == string::npos)
        {
            won = false;
            HangmanPlaceHolder += "_ ";
        }
        else
        {
            HangmanPlaceHolder += HangmanTheWord[i];
            HangmanPlaceHolder += " ";
        }
    }
    HangmanMessage(HangmanPlaceHolder, false);
    return won;
}
/* this function is used to check the how many letters in the guessed word
   and put few underscore inside a box with spaces between them with the box border
     +-----------------------------------+
     |            _ _ _ _ _ _            |
     +-----------------------------------+                 */

string LoadHangmanRandomWords(string WordsPath)
{
    int LineCount = 0;
    string HangmanWords;
    vector<string> v;
    ifstream reader(WordsPath);
    if (reader.is_open())
    {
        while (std::getline(reader, HangmanWords))
            v.push_back(HangmanWords);

        int RandomLine = rand() % v.size();

        HangmanWords = v.at(RandomLine);
        reader.close();
    }
    return HangmanWords;
}

int HangmanSaveChancesLeft(string HangmanWords, string HangmanGuesses)
{
    int HangmanMistake = 0;
    for (int i = 0; i < HangmanGuesses.length(); i++)
    {
        if (HangmanWords.find(HangmanGuesses[i]) == string::npos)
            HangmanMistake++;
    }
    return HangmanMistake;
}




void resize(int X, int Y, int Z)
{
    static CONSOLE_FONT_INFOEX  fontex;
    fontex.cbSize = sizeof(CONSOLE_FONT_INFOEX);
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    GetCurrentConsoleFontEx(hOut, 0, &fontex);
    fontex.FontWeight = Z;
    fontex.dwFontSize.X = X;
    fontex.dwFontSize.Y = Y;
    SetCurrentConsoleFontEx(hOut, NULL, &fontex);
}
