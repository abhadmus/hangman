# Word Guessing Game in C

This C program is a terminal-based word guessing game, based on Hangman. The user attempts to guess a hidden word—either one letter at a time or the full word—within a limited number of turns.

---

## Objective

Guess the word selected from a file:
- You can **guess a letter** or **guess the entire word**.
- You have **10 turns**.
- Correct guesses reveal characters of the word.
- Incorrect guesses reduce the number of turns.
- You win if you guess the full word before running out of turns.

---

## Features

- Reads the hidden word from a text file
- Supports guessing by **letter** or **full word**
- Tracks and displays progress using `*` symbols
- Prevents repeated guesses
- Handles invalid input gracefully
- Offers replayability by prompting to play again

---

## How to Use

### 1. Create a word file

Prepare a simple `.txt` file with a **single word** on the first line. Example:

`secretword.txt`:
```
engineer
```

### 2. Compile the program

Using `gcc` (Linux/macOS/WSL):

```bash
gcc hangman.c -o hangman
./hangman
```

On Windows (MinGW):

```bash
gcc hangman.c -o hangman.exe
hangman.exe
```

---

## Gameplay Example

```
Give the filename with the unknown word: secretword.txt

Ready to Start!
The word is: *********

Number of turns remaining: 10
Would you like to guess the word [w] or guess a letter [l]: l
What letter have you chosen?: e
Good choice!
The word is: *e****e**

...

Congratulations! You have correctly guessed the word engineer

Do you want to play again [y/n]:
```

---

## How It Works

### Input
- The word to guess is read from a file provided by the user.
- The player inputs one character or one word at a time.

### Logic
- If a guessed letter exists in the word and hasn't been guessed before, it's revealed.
- If the full word is guessed correctly, the game ends in victory.
- Each incorrect word guess or unhelpful letter guess reduces the turn count.
- The game ends in defeat when turns reach 0.

---

## Code Overview

- `l_checker()` handles letter guesses
- `w_checker()` handles full word guesses
- The main loop manages game flow, input, display, and feedback
- Error checks ensure valid file input and user interaction

---

## Dependencies

- Standard C libraries:
  - `stdio.h`
  - `stdlib.h`
  - `string.h`
  - `math.h`

---

## Notes

- The guessed word must be on the **first line** of the input file.
- Only lowercase alphabetic characters are assumed (no input sanitization for symbols).
- Word is case-sensitive.