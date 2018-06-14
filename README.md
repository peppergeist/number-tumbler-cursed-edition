# number-tumbler-cursed-edition
a remake of number tumbler, not written in a joke language, implementing using the curses library

## Usage
Run the program numbertumblerce in your terminal.

## Rules
1. First, choose a difficulty. This determines which numbers appear in the code. A difficulty of 1 means that only the digits 0 through 5 can appear. A difficulty of 5, the maximum, means all digits between 0 and 9 can appear.

2. Then, the computer will think of a four-digit code number. This number can contain leading zeroes. You have ten guesses to find out what this number is.

3. Enter a four-digit guess. The computer will display a series of pluses, minuses, and dots representing how close your guess was to the actual code. A plus means your guess contained a correct number in the correct location. A minus means that your guess contained a correct number, but it was in the wrong location. A dot means that your guess contained an incorrect number that does not appear in the code at all. The number of each of these symbols corresponds to each number in your guess matching their rules, so a guess with two completely correct digits, an almost correct digit, and an incorrect digit would garner a response of "++-.". The order of the symbols is unrelated to the order of your guess.

4. You will get points based on how many numbers of your guess was correct. Additionally, you will get bonus points for each guess you have remaining if you guess the code in less than ten turns.

## Scoring

* For each guess, you receive 25 points for each plus, 10 points for each minus, and 0 points for each dot.

* For each remaining guess after guessing the correct answer, you receive 100 points.

* The maximum score is 1000 points, from guessing the correct answer on the first try.

**Happy tumbling!**
