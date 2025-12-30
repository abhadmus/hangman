#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define MAXLINE 128  // Defines the maximum length for strings used in the program

/* Function to handle letter guesses. Compares the letter to the target word
   and updates the progress string with correct guesses. */
int l_checker(char string[], char given_l_or_w[], char guessword[], int gword_length, int *turns) {
    int i = 0, changes = 0;

    /* Loops through the length of the guess-word, the word that's the target of the guessing, and checks if the given letter matches any character in it*/
    for (i = 0; i < gword_length; i++) {
        if (guessword[i] == given_l_or_w[0]) {  // Checks if the letter matches going through the character's array one by one
            if (string[i] != guessword[i]) {   // Updates only if it hasn't been inputted already
                string[i] = given_l_or_w[0];
                changes++;
            } else {
                printf("\nAlready inputted!");  // Informs the user in the case of a re-inputted letter
            }
        }
    }

    /* Provides feedback*/
    if (changes > 0) {
        printf("\nGood choice!");
    } else if (changes == 0) {
        // Do nothing for neutral feedback, allowing stars_left to be unchanged in this case
    } else {
        printf("\nBad choice!");  // Deducts turns if no correct letters were found
        (*turns)--;
    }

    return changes;  // Returns the number of changes made to the progress string, which then affects stars_left. This then allows a count of the number of unknown letters to be kept
}

/* Function to handle word guesses. Compares the guessed word to the target word
   and updates the progress string if the guess is correct. */
int w_checker(char string[], char given_l_or_w[], char guessword[], int gword_length, int *turns) {
    int i = 0, changes = 0;

    /* Checks if the guessed word matches the target word */
    if (strcmp(guessword, given_l_or_w) == 0) {
        for (i = 0; i < gword_length; i++) {  // Updates the progress string to reveal the full word
            string[i] = guessword[i];
        }
        printf("\n\nGood choice!");
        changes = gword_length;  // Changes is set so that stars_left can end at or below zero, allowing the do-while to be terminated, ending the game
    } else {
        printf("\n\nBad choice!");
        (*turns)--;
    }
    return changes;
}

int main() {
    char repeat = 'y';  // Variable to track whether the user wants to play again
    int l_checker(), w_checker();  // Declares function prototypes

    do {
        /* Variables for the guessing setup */
        int gword_length, i, turns = 10, stars_left;
        char guessword[MAXLINE], guess_type, filename[MAXLINE];
        FILE *fpin;

        fpin = NULL;

        /* Loop to repeatedly prompt the user for a valid file until it is found */
        while (fpin == NULL) {
            printf("\nGive the filename with the unknown word: ");
            scanf("%s", &filename);
            fpin = fopen(filename, "r");

            if (fpin == NULL) {  // Handles invalid filenames
                printf("\nInvalid Filename. Try again.");
            }
        }

        /* Reads the guess-word from the file */
        fgets(guessword, MAXLINE, fpin);

        printf("\nReady to Start!");
        printf("\nThe word is: ");

        gword_length = strlen(guessword);  // Calculates the length of the target word

        /* Removes the newline character from the end of the word if it exists */
        if (guessword[gword_length - 1] == '\n') {
            guessword[gword_length - 1] = '\0';
            gword_length--;
        }

        /* Initializes the progress string, starting with every letter masked */
        char gword_progress[gword_length], given_l_or_w[gword_length];
        stars_left = gword_length;

        for (i = 0; i < gword_length; i++) {
            gword_progress[i] = '*';
            printf("%c", gword_progress[i]);  // Displays the masked word's current state, the initial state
        }
        gword_progress[i] = '\0';  // Null-terminate the progress string

        /* Main game loop: Runs until the user runs out of turns or guesses the word (there are no stars left to mask the word)*/
        do {
            printf("\n\nNumber of turns remaining: %d", turns);
            printf("\nWould you like to guess the word [w] or guess a letter [l]: ");
            scanf(" %c", &guess_type);

            if (guess_type == 'l') {
                /* Handles letter guessing */
                printf("\nWhat letter have you chosen?: ");
                scanf(" %c", given_l_or_w);

                stars_left = stars_left - l_checker(gword_progress, given_l_or_w, guessword, gword_length, &turns);
                printf("\nThe word is: %s", gword_progress);

            } else if (guess_type == 'w') {
                /* Handles word guessing */
                printf("\nWhat word have you chosen?: ");
                scanf("%s", given_l_or_w);

                stars_left = stars_left - w_checker(gword_progress, given_l_or_w, guessword, gword_length, &turns);
                printf("\nThe word is: %s", gword_progress);

            } else {
                /* Handles invalid inputs */
                printf("\nNeither l nor w indicated. Please enter one of l or w");
            }

        } while (turns > 0 && stars_left > 0);  // Exit when turns are exhausted or the word is guessed

        /* Provides feedback depending on the game outcome */
        if (turns == 0) {
            printf("\nYou have run out of turns! Better luck next time.");
        } else {
            printf("\nCongratulations! You have correctly guessed the word %s", guessword);
        }

        /* Asks the user if they want to play again */
        printf("\n\nDo you want to play again [y/n]: ");
        scanf(" %c", &repeat);

    } while (repeat == 'y');  // Repeat the game if the user chooses 'y'

    return 0;  // Exit the program
}
