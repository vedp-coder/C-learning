#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int number, guess, attempts = 0;
    int min = 1;
    int max = 100;
    char play_again;
    
    // Seed random number generator
    srand(time(0));
    
    printf("\n===== Number Guessing Game =====\n");
    
    do {
        // Generate random number between min and max
        number = (rand() % (max - min + 1)) + min;
        attempts = 0;
        
        printf("\nI'm thinking of a number between %d and %d.\n", min, max);
        
        do {
            printf("Enter your guess: ");
            scanf("%d", &guess);
            attempts++;
            
            if (guess < number) {
                printf("Too low! Try again.\n");
            } else if (guess > number) {
                printf("Too high! Try again.\n");
            } else {
                printf("\nCongratulations! You guessed the number %d in %d attempts!\n", number, attempts);
            }
        } while (guess != number);
        
        printf("\nWould you like to play again? (y/n): ");
        scanf(" %c", &play_again);
        
    } while (play_again == 'y' || play_again == 'Y');
    
    printf("\nThanks for playing! Goodbye!\n");
    
    return 0;
}
