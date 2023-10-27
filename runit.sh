gcc -o sudoku -lpthread -lm src/*.c

./sudoku puzzles/puzzle9-valid.txt
./sudoku puzzles/puzzle2-invalid.txt
./sudoku puzzles/puzzle2-difficult.txt
