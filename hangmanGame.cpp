#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <locale>

using namespace std;


//computer picks a random word to guess.
int random_number(int difficulty_level)
{
    srand (time(NULL));
    int word_number;
    if (difficulty_level == 1) word_number = rand() % 347 + 1;
    else if (difficulty_level == 2) word_number = rand() % 308 + 1;
    else word_number = rand() % 189 + 1;
    return word_number;
}

string get_word(string file_name, int word_number)
{
    string word;
    ifstream inFile;
    if (file_name == "hangmanGameEasy.fil")
    {
        inFile.open("hangmanGameEasy.fil");
        if (!inFile)
        {   
            cout << "Unable to open file";
            exit(1); // terminate with error
        }
        else 
        {
            for (int i = 0; i < word_number; i++)
            {
                    string temp; 
                    getline(inFile, temp);
                     if (i == word_number -1) getline(inFile, word);
            }
        }
        inFile.close(); 
    }
    else if (file_name == "hangmanGameMedium.fil")
    {
        inFile.open("hangmanGameMedium.fil");
        if (!inFile)
        {   
            cout << "Unable to open file";
            exit(1); // terminate with error
        }
        else 
        {
            for (int i = 0; i < word_number; i++)
            {
                    string temp; 
                    getline(inFile, temp);
                     if (i == word_number -1) getline(inFile, word);
            }
        }
        inFile.close(); 
    }
    else
    {
        inFile.open("hangmanGameHard.txt");
        if (!inFile)
        {   
            cout << "Unable to open file";
            exit(1); // terminate with error
        }
        else 
        {
            for (int i = 0; i < word_number; i++)
            {
                    string temp; 
                    getline(inFile, temp);
                     if (i == word_number -1) getline(inFile, word);
            }
        }
        inFile.close(); 
    }
    return word;
}
string get_secret_word(int difficulty_level)
{
    int word_number;
    string secret_word;
    string file_name;
    if (difficulty_level == 1) 
    {
        word_number = random_number(1);
        file_name = "hangmanGameEasy.fil";
        secret_word = get_word(file_name, word_number);
    }
    else if (difficulty_level == 2) 
    {
        word_number = random_number(2);
        cout << "Random number :  " << word_number << endl;
        file_name = "hangmanGameMedium.fil";
        secret_word = get_word(file_name, word_number);
    }
    else
    {
        word_number = random_number(3);
        cout << "Random number :  " << word_number << endl;
        file_name = "hangmanGameHard.txt";
        secret_word = get_word(file_name, word_number);
    }
    return secret_word;
}
void print_word(string guess_so_far)
{
    cout << "guess_so_far: " << guess_so_far << endl;
}

bool right_or_not(string current_guess, string secret_word, string guess_so_far)
{
    bool correct = false;
    for (int i = 0; i < secret_word.length(); i++)
    {
        if (secret_word[i] == current_guess[0])
        {
            guess_so_far[i] = secret_word[i];
            correct = true;
            cout << guess_so_far[i];
            for (int n = 0; n < secret_word.length(); n++)
            {
                guess_so_far[i] += secret_word[i];
            }
        }
    }

    return correct;
}

bool check_endgame(int wrong_guess_count, int letter_count, string secret_word)
{
    bool finish = false;
    bool win = false;
    if (letter_count > secret_word.length()-1) 
    {
        finish = true;
        win = true;
        cout << "finish? " << finish << endl;
    }
    else if (wrong_guess_count >= 7)
    {
        finish = true;
        win = false;
        cout << "finish? " << finish << endl;
    }
    else 
    {
        finish = false;
        cout << "finish? " << finish << endl;
    }
    return finish;
}

bool win_or_not (int wrong_guess_count, int letter_count, string secret_word)
{
    bool win = false;
    if (letter_count > secret_word.length()-1) 
    {
        win = true;
    }
    else 
    {
        win = false;
    }
    return win;
}

void hangman_count(int wrong_guess_count)
{
     if (wrong_guess_count == 1)
     {
         cout << "o" << endl;
     }
     else if (wrong_guess_count == 2)
     {
         cout << "  o" << endl;
         cout << "  | " << endl;
     }
     else if (wrong_guess_count == 3)
     {
         cout << "  o " << endl;
         cout << " \\|" << endl;
     }
     else if (wrong_guess_count == 4)
     {
         cout << "  o " << endl;
         cout << " \\|/" << endl;
     }
     else if (wrong_guess_count == 5)
     {
         cout << " o " << endl;
         cout << "\\|/" << endl;
         cout << " | " << endl;
     }
     else if (wrong_guess_count == 6)
     {
         cout << " o " << endl;
         cout << "\\|/" << endl;
         cout << " | " << endl;
         cout << "/ " << endl;
     }
     else 
     {
         cout << "HANGMAN!" << endl;
         cout << " o " << endl;
         cout << "\\|/" << endl;
         cout << " | " << endl;
         cout << "/ \\" << endl; 
     }
}

int main()
  {
      int difficulty_level = 0;
      int word_number, letter_count = 0, wrong_guess_count = 0;
      string secret_word, current_guess, guess_so_far;
      bool true_or_not = false, finish = false; bool win = false;
      locale loc;

      // Difficulty Level.
      cout << "DIFFICULTY:  (1)EASY\n";
      cout << "             (2)MEDIUM\n";
      cout << "             (3)HARD\n";
      cout << "ENTER:  ";
      cin >> difficulty_level;
      while (difficulty_level > 3)
      {
        cout << "PLEASE ENTER A NUMBER FROM 1 - 3:  " << endl;
        cin >> difficulty_level;
      }

      // Get the Secret Word.
      secret_word = get_secret_word(difficulty_level);
      for (int i = 0; secret_word[i]!='\0'; i++)
      {
        secret_word[i] =toupper(secret_word[i]);
      }
      cout << "The secret word is :  " << secret_word << endl;
      //print_word(secret_word);
      cout << endl;

      for (int i = 0; i < secret_word.length(); i++)
      {
          guess_so_far = "- ";
          cout << guess_so_far;
      }
      cout << endl;

      // Start Guessing
      while (finish == false)
      {
        cout << "Enter a letter to guess:  " << endl;
        cin >> current_guess;
        for (int i = 0; current_guess[i]!='\0'; i++)
        {
            current_guess[i] =toupper(current_guess[i]);
        }
        true_or_not = right_or_not(current_guess, secret_word, guess_so_far);
        cout << endl;
        if (true_or_not)
        {
            cout << "Good guess!" << endl;
            letter_count++;
            cout << "letter_count = " << letter_count << endl;  
        }
        else
        {
            cout << "Try again." << endl;
            wrong_guess_count++;
            cout << "wrong_guess_count = " << wrong_guess_count << endl;
            hangman_count(wrong_guess_count);
        }
        finish = check_endgame(wrong_guess_count, letter_count, secret_word);
        win = win_or_not(wrong_guess_count, letter_count, secret_word);
        if (finish == true)
        {
            if (win == true)
            {
                cout << "CONGRATULATIONS! YOU WIN!" << endl;
            }
            else
            {
               cout << "SORRY, YOU LOSE." << endl;
            }
            
            cout << "THE SECRET WORD IS:  " << secret_word << endl;
        }
      }

      
      
}