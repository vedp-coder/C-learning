#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define MAX_TRIES 6
#define WORD_COUNT 20
#define MAX_WORD_LENGTH 20

// Function to clear the screen (system-independent)
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Function to draw the hangman figure based on wrong attempts
void drawHangman(int wrongAttempts) {
    printf("  +---+\n");
    printf("  |   |\n");
    
    if (wrongAttempts >= 1) {
        printf("  O   |\n");
    } else {
        printf("      |\n");
    }
    
    if (wrongAttempts == 2) {
        printf("  |   |\n");
    } else if (wrongAttempts == 3) {
        printf(" /|   |\n");
    } else if (wrongAttempts >= 4) {
        printf(" /|\\  |\n");
    } else {
        printf("      |\n");
    }
    
    if (wrongAttempts == 5) {
        printf(" /    |\n");
    } else if (wrongAttempts >= 6) {
        printf(" / \\  |\n");
    } else {
        printf("      |\n");
    }
    
    printf("      |\n");
    printf("=========\n\n");
}

// Function to initialize the guessed word with underscores
void initializeGuessedWord(char* word, char* guessedWord) {
    int length = strlen(word);
    for (int i = 0; i < length; i++) {
        if (word[i] == ' ') {
            guessedWord[i] = ' ';
        } else {
            guessedWord[i] = '_';
        }
    }
    guessedWord[length] = '\0';
}

// Function to check if a letter is already guessed
int isAlreadyGuessed(char letter, char* guessedLetters, int letterCount) {
    for (int i = 0; i < letterCount; i++) {
        if (guessedLetters[i] == letter) {
            return 1;
        }
    }
    return 0;
}

// Function to update the guessed word with a correctly guessed letter
int updateGuessedWord(char* word, char* guessedWord, char letter) {
    int found = 0;
    int length = strlen(word);
    
    for (int i = 0; i < length; i++) {
        if (tolower(word[i]) == tolower(letter)) {
            guessedWord[i] = word[i];
            found = 1;
        }
    }
    
    return found;
}

// Function to check if the word is completely guessed
int isWordGuessed(char* guessedWord) {
    int length = strlen(guessedWord);
    for (int i = 0; i < length; i++) {
        if (guessedWord[i] == '_') {
            return 0;
        }
    }
    return 1;
}

int main() {
    // List of words for the game
    char words[WORD_COUNT][MAX_WORD_LENGTH] = {
        "apple", "banana", "orange", "strawberry", "pineapple",
        "computer", "keyboard", "monitor", "programming", "algorithm",
        "hangman", "software", "developer", "engineer", "language",
        "structure", "function", "variable", "integer", "character"
    };
    
    char word[MAX_WORD_LENGTH];
    char guessedWord[MAX_WORD_LENGTH];
    char guessedLetters[26]; // Store already guessed letters
    int guessedLetterCount = 0;
    char letter;
    int wrongAttempts;
    char playAgain;
    
    // Seed random number generator
    srand(time(0));
    
    do {
        // Select a random word
        strcpy(word, words[rand() % WORD_COUNT]);
        
        // Initialize game variables
        wrongAttempts = 0;
        guessedLetterCount = 0;
        initializeGuessedWord(word, guessedWord);
        
        // Game loop
        while (wrongAttempts < MAX_TRIES && !isWordGuessed(guessedWord)) {
            clearScreen();
            printf("===== HANGMAN GAME =====\n\n");
            drawHangman(wrongAttempts);
            
            printf("Word: %s\n", guessedWord);
            printf("Guessed letters: ");
            for (int i = 0; i < guessedLetterCount; i++) {
                printf("%c ", guessedLetters[i]);
            }
            printf("\n");
            printf("Wrong attempts: %d/%d\n", wrongAttempts, MAX_TRIES);
            
            printf("\nEnter a letter: ");
            scanf(" %c", &letter);
            letter = tolower(letter);
            
            // Check if letter is valid
            if (!isalpha(letter)) {
                printf("Please enter a valid letter.\n");
                continue;
            }
            
            // Check if letter is already guessed
            if (isAlreadyGuessed(letter, guessedLetters, guessedLetterCount)) {
                printf("You already guessed that letter! Try another.\n");
                continue;
            }
            
            // Add to guessed letters
            guessedLetters[guessedLetterCount++] = letter;
            
            // Update guessed word if letter is correct
            if (!updateGuessedWord(word, guessedWord, letter)) {
                wrongAttempts++;
                printf("Wrong guess!\n");
            } else {
                printf("Good guess!\n");
            }
        }
        
        clearScreen();
        drawHangman(wrongAttempts);
        printf("Word: %s\n", guessedWord);
        
        if (isWordGuessed(guessedWord)) {
            printf("\nCONGRATULATIONS! You guessed the word correctly!\n");
        } else {
            printf("\nGAME OVER! You ran out of attempts.\n");
            printf("The word was: %s\n", word);
        }
        
        printf("\nWould you like to play again? (y/n): ");
        scanf(" %c", &playAgain);
        
    } while (playAgain == 'y' || playAgain == 'Y');
    
    printf("\nThanks for playing! Goodbye!\n");
    
    return 0;
}
