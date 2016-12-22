#include <iostream>     // display inputs and outputs to the screen
#include <string>       // use strings
#include <ctime>        // use random numbers
#include <cstdlib>      // use random numbers
#include <fstream>      // to read and write files
#include <vector>       // dynamic tables

using namespace std;

// mix the letters in mysteryWord and return the mixed word
string mixLetters(string mysteryWord)
{
    string mixedWord;
    int len(mysteryWord.length());

    for (int compteur(1); compteur <= len; compteur++)
    {
        // pick a letter randomly
        srand(time(0));
        int position = rand() % mysteryWord.size();

        // add it to mixedWord
        mixedWord += mysteryWord[position];

        // Erase the letter from the mysteryWord
        mysteryWord.erase(position, 1);
    }
    return mixedWord;
}

// returns a random word in the file "dico.txt"
string wordDict(vector<string> &words)
{
    string pickedWord;
    ifstream file("dico.txt");

    if(file)
    {
        string line;

        while (file >> line)
        {
            words.push_back(line);
        }

        srand(time(0));
        pickedWord = words[rand() % words.size()];
    }
    else
    {
        cout << "ERROR: Cannot open the file." << endl;
    }

    return pickedWord;
}

// clear console screen
void clearScreen()
{
    cout << string( 100, '\n' );
}

int main()
{
    // declare variables
    string word, mixedWord, answer, party_answer("d");
    bool party(true);
    int nbGuess(5), nbPlayers(0);
    vector<string> words;

    do
    {
        while (nbPlayers != 1 && nbPlayers != 2)
        {
            cout << "RULES: You have 5 guesses to find a word whose letters have been mixed up randomly." << endl;
            cout << "You can play alone or with a friend. Good luck!" << endl;
            cout << "How many players (1 or 2)?" << endl;
            cin >> nbPlayers;

            switch (nbPlayers)
            {
                case 1:
                    // pick a word from the dictionary
                    word = wordDict(words);
                    cout << "A word from the dictionary has been picked randomly." << endl;
                    break;

                case 2:
                    cout << "Player 1, please enter a word." << endl;
                    cin >> word;
                    clearScreen();
                    break;

                default:
                    cout << "Please enter a valid number of players (1 or 2)!" << endl;
                    break;
            }
        }

        // mix the letters
        mixedWord = mixLetters(word);
        cout << "The letters have been mixed up!" << endl;

        do
        {
            cout << endl << "You have " << nbGuess << " remaining guess(es)." << endl;
            cout << "What is this word? : " << mixedWord << endl;
            cin >> answer;

            if (word == answer)
            {
                cout << "Well done !" << endl;
            }
            else
            {
                cout << "That's not the word !" << endl;
                nbGuess--;
            }

        }
        while ((word != answer) && (nbGuess > 0));

        if (nbGuess == 0)
        {
            cout << "GAME OVER!" << endl;
            cout << "The word was: " << word << endl;
        }

        while ((party_answer != "Y") && (party_answer != "N"))
        {
            cout << endl << "Do you want to play again ? (Y/N)" << endl;
            cin >> party_answer;
        }

        if (party_answer == "Y")
        {
            party = true;
        }
        else if (party_answer == "N")
        {
            party = false;
        }

        // reinitialise party_answer and nbGuess
        party_answer = "d";
        nbGuess = 5;
        nbPlayers = 0;

    }
    while (party);

    return 0;
}
