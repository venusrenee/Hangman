#include <iostream>
#include <string.h>
#include <fstream>
#include <sstream>
#include <random>
#include <string>
#include <vector>
#include <time.h>

using namespace std;

string word;
int score = 0;
char char_guess;
string str_guess;
char difficulty = 'n';
string debug = "off";
bool gameover = false;
string hintword = word;
//These are just variables initializing the score, the letters the player guesses, the number of guesses the player has used,
//the difficulty level, and the boolean setting gameover to false, as gameover = true is what is used to end the game
//when the player is ready to quit-HR


//This class functioncontains data members and and member functions for the entire game.
//Inside of this class it has the "Public", which specifies that those members are accessible from any function
class word_manipulate {

public:

    string line, word_pull;
    vector<string> wordbank;
    int hint_count = 3;
    string hintword;


    void set_word() {

        ifstream file("hangmanwordbank.csv");

        while (getline(file, line)) {

            istringstream sstream(line);

            while (getline(sstream, word_pull, ',')) {
                wordbank.push_back(word_pull);
            }

        }


        srand(time(0));
        int r = rand() % wordbank.size();

        string randomword = wordbank[r];
        word = randomword;
        hintword = word;


        // This function chooses a random word from a word bank in the .csv file by using a double while loop to read a line from
        // the file using getline/istringstream/sstream, and then pull words from the file (word_pull) separated by commas.
        // These words are added to a vector wordbank, and then srand and rand are used to pull a random word from the wordbank by
        // generating a random number between 0 and the size of wordbank, and then using that random number to pull a random word from
        // the vector and set it as the word which will need to be guessed for the game -HR
    }

    //This function will display a random hint letter from the randomly selected word
    void hint() {

        char hint;

        srand(time(0));
        
        int r = rand() % hintword.size();
        hint = hintword[r];
        hintword.erase(remove(hintword.begin(),hintword.end(),hint));
        hint_count--;

        if (hint_count >= 0) {
            cout << "Your hint letter is: " << hint << endl << "You have " << hint_count << " hints remaining." << endl;
        }
        else {
            cout << "You have no hints remaining" << endl;
        }

    }
};
// This is the main gameplay function, when a new game is started
void play()
{
    float num_guess = 0;
    vector<char> let;
    word_manipulate wordpick;
    wordpick.set_word();
    string display(word.length(), '*');

    float num_guess_increase = 1;

    if (difficulty == 'e') {
        num_guess_increase = .5;
    }
    else if (difficulty == 'n') {
        num_guess_increase = 1;
    }
    else {
        num_guess_increase = 1.5;
    }
    // Depending on how many wrong guesses this prints the correlated hangman
    do
    {
        system("cls");
        cout << "Type ? for a hint, Type ~ to exit." << endl;
        //Checks if '?' is input and displays a hint letter
        if (num_guess == 0)
        {
            cout << "---------- \n";
            cout << "[]      V  \n";
            cout << "[]         \n";
            cout << "[]         \n";
            cout << "[]         \n";
            cout << "[]         \n";
            cout << "[]         \n";
        }

        if (num_guess <= 1 && num_guess > 0)
        {
            cout << "---------- \n";
            cout << "[]      V  \n";
            cout << "[]      O  \n";
            cout << "[]         \n";
            cout << "[]         \n";
            cout << "[]         \n";
            cout << "[]         \n";
        }
        if (num_guess <= 2 && num_guess > 1)
        {
            cout << "---------- \n";
            cout << "[]      V  \n";
            cout << "[]      O  \n";
            cout << "[]      Y  \n";
            cout << "[]      I  \n";
            cout << "[]         \n";
            std::cout << "[]         \n";
        }
        if (num_guess <= 3 && num_guess > 2)
        {
            cout << "---------- \n";
            cout << "[]      V  \n";
            cout << "[]      O  \n";
            cout << "[]    I-Y \n";
            cout << "[]      I \n";
            cout << "[]         \n";
            cout << "[]         \n";
        }
        if (num_guess <= 4 && num_guess > 3)
        {
            cout << "---------- \n";
            cout << "[]      V  \n";
            cout << "[]      O  \n";
            cout << "[]    I-Y-I \n";
            cout << "[]      I  \n";
            cout << "[]         \n";
            cout << "[]         \n";
        }
        if (debug == "on") {
            cout << word << endl;
            cout << "You have " << num_guess << " strikes" << endl;
        }
        cout << "You have guessed: ";
        for (int i = 0; i < let.size(); i++) {
            cout << let[i] << " ";
        }
        cout << endl;
        //print the current display word which changes as characters are guessed
        cout << display;
        cout << "\n";
        if (char_guess == '?') {
            //for (int i = 0; i < display.size(); i++) {
            wordpick.hint();
            //}
        }
        cout << "Type a letter\n";
        cin >> str_guess;
        char_guess = str_guess.front();
        let.push_back(char_guess);
        if (char_guess == '~') {
            break;
        }
        //Searches the word for the guessed character if the letter is correct change the char of display to 
        //the correct character
        for (int i = 0; i < word.length(); i++)
        {
            if (char_guess == word[i])
            {
                display[i] = char_guess;
            }

        }

        //string::npos is a constant for the string function when this is returned true by find it means
        //the character was not found
        //If the character is not found in the word increase the number of wrong guesses by a number decided 
        //by the selected difficulty
        if (word.find(char_guess) == string::npos) {
            if (char_guess == '?') {
                num_guess = num_guess;
            }
            else {
                num_guess += num_guess_increase;
            }

        }

        //If the number of wrong guesses is over 4.5 the game is over. 4.5 is used because of the difficulty setting
        //being able to be changed
        if (num_guess >= 4.5) {
            gameover = true;
        }
        //The game is also over if the display word which actively changes with the guesses is equal to the buffer word
        //decided at the beginning of each new game
        else if (word == display) {
            gameover = true;
        }
    } while (!gameover);

    char yn;

    if (gameover == true) {

        if (num_guess >= 4.5) {
            system("cls");
            cout << "---------- \n";
            cout << "[]      V  \n";
            cout << "[]      O  \n";
            cout << "[]    I-Y-I \n";
            cout << "[]      I  \n";
            cout << "[]      A  \n";
            cout << "[]         \n";
            cout << "You lose\n";
            cout << "The word was " << word << endl;
            cout << "Score: " << score << endl;
            cout << "Play again? type y or n: ";
            cin >> yn;

            if (yn == 'y') {
                gameover = false;
                num_guess = 0;
                play();
            }
            else {
                gameover = false;
                //menu
            }
        }
        else
        {
            system("cls");
            cout << "You win!\n";
            cout << "---------- \n";
            cout << "[]           \n";
            cout << "[]           \n";
            cout << "[]     _A_      \n";
            cout << "[]      O   \n";
            cout << "[]      Y    \n";
            cout << "[]      A   \n";
            score++;
            cout << "Score: " << score << endl;
            cout << "Play again? type y or n: ";
            cin >> yn;

            if (yn == 'y') {
                gameover = false;
                num_guess = 0;
                play();
            }
            else {
                gameover = false;
                //menu
            }
        }
    }
}

//main menu this is what is ran when the program is first executed. If 'n' no is selected after a game is over it 
//will return here as well.
void menu() {

    char option;
    char difinput;

    while (1) {

        cout << "Lets play Hangman!" << endl;
        cout << "Type s to start, o for options, h for help and instructions, d for debug,or q to quit" << endl;
        cin >> option;

        if (option == 's') {
            play();
        }
        else if (option == 'o') {
            cout << "Select a difficulty: e for easy, n for normal, h for hard. ";
            cin >> difinput;
            //difficulty input sets a difficulty variable which affects how many
            //misses you aqcquire from 1 wrong letter
            while (1) {
                if (difinput == 'e') {
                    difficulty = 'e';
                    break;
                }
                if (difinput == 'n') {
                    difficulty = 'n';
                    break;
                }
                if (difinput == 'h') {
                    difficulty = 'h';
                    break;
                }
            }
        }
        else if (option == 'd') {
            while (1) {
                cout << "Debug mode is " << debug << endl;
                cout << "Input on to turn debug on, input off to turn debug off. " << endl;
                cin >> debug;
                if (debug != "on" && debug != "off") {
                    cout << "Please try again. Input on to turn debug on, input off to turn debug off." << endl;
                }
                else {
                    break;
                }

            }
        }
        else if (option == 'h') {
            cout << "The game is simple. You get guess the word one letter at a time. If you fail, the man dies." << endl;
            cout << "If you need help, enter ? to recieve a hint, but be careful, you only have 3." << endl;
        }
        else if (option == 'q') {
            exit(0);
        }
        else {
            cout << "Not an option please choose again." << endl;
            cin >> option;
        }
    }

    //changed main function to play(), play calls itself recursively to enable the play of multiple games.

}


int main() {

    menu();
    return 0;
    //calling the function that display the game main menu
}