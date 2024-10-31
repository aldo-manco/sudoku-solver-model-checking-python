#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>

#define SIZE 9
#define MINUS_INFINITE -2147483648

unsigned __CPROVER_bitvector[6] generateNonDeterministicNumbers();

__CPROVER_bitvector[1] sudokuSolver(unsigned __CPROVER_bitvector[6] sudokuGrid[][SIZE]);

__CPROVER_bitvector[1] radixSudokuSolver(unsigned __CPROVER_bitvector[6] sudokuGrid[][SIZE]);

__CPROVER_bitvector[1] thereAreDuplicatesInRows(unsigned __CPROVER_bitvector[6] *sudokuArray);

__CPROVER_bitvector[1] thereAreDuplicatesInCols(unsigned __CPROVER_bitvector[6] *sudokuArray);

void fillSudokuGrid(unsigned __CPROVER_bitvector[6] sudokuGrid[][SIZE]);

void printSudoku(unsigned __CPROVER_bitvector[6] sudokuGrid[][SIZE]);

__CPROVER_bitvector[1] readSudokuCertificate(unsigned __CPROVER_bitvector[6] rows, unsigned __CPROVER_bitvector[6] cols, unsigned __CPROVER_bitvector[6] (*a)[cols], const char *filename);

unsigned __CPROVER_bitvector[4] main() {

    // SUDOKU WHICH NEEDS TO BE SOLVED

    unsigned __CPROVER_bitvector[6] sudokuGrid[SIZE][SIZE] =
            {{0, 0, 0, 0, 6, 0, 2, 0, 7},
             {6, 7, 8, 0, 0, 0, 0, 0, 5},
             {2, 0, 5, 0, 0, 0, 0, 0, 0},
             {0, 9, 0, 0, 0, 0, 0, 0, 0},
             {0, 2, 0, 7, 3, 0, 0, 5, 0},
             {0, 0, 0, 2, 0, 9, 0, 7, 0},
             {0, 0, 0, 9, 0, 6, 0, 0, 0},
             {0, 0, 0, 0, 5, 0, 4, 3, 0},
             {8, 0, 0, 4, 0, 0, 5, 2, 0}};

    //unsigned __CPROVER_bitvector[6] sudokuGrid[SIZE][SIZE];

    //readSudokuCertificate(SIZE, SIZE, sudokuGrid, "sudoku_certificate.dat");

    fillSudokuGrid(sudokuGrid);

    /*while (!sudokuSolver(sudokuGrid)){

        unsigned __CPROVER_bitvector[6] sudokuGrid[SIZE][SIZE] =
                {{0, 0, 0, 0, 6, 0, 2, 0, 7},
                 {6, 7, 8, 0, 0, 0, 0, 0, 5},
                 {2, 0, 5, 0, 0, 0, 0, 0, 0},
                 {0, 9, 0, 0, 0, 0, 0, 0, 0},
                 {0, 2, 0, 7, 3, 0, 0, 5, 0},
                 {0, 0, 0, 2, 0, 9, 0, 7, 0},
                 {0, 0, 0, 9, 0, 6, 0, 0, 0},
                 {0, 0, 0, 0, 5, 0, 4, 3, 0},
                 {8, 0, 0, 4, 0, 0, 5, 2, 0}};

        fillSudokuGrid(sudokuGrid);
    }*/

    //assert(!sudokuSolver(sudokuGrid));
    assert(!radixSudokuSolver(sudokuGrid));

    // SUDOKU SOLVED

    unsigned __CPROVER_bitvector[6] sudokuGridSolved[SIZE][SIZE] =
            {{5, 3, 4, 6, 7, 8, 9, 1, 2},
             {6, 7, 2, 1, 9, 5, 3, 4, 8},
             {1, 9, 8, 3, 4, 2, 5, 6, 7},
             {8, 5, 9, 7, 6, 1, 4, 2, 3},
             {4, 2, 6, 8, 5, 3, 7, 9, 1},
             {7, 1, 3, 9, 2, 4, 8, 5, 6},
             {9, 6, 1, 5, 3, 7, 2, 8, 4},
             {2, 8, 7, 4, 1, 9, 6, 3, 5},
             {3, 4, 5, 2, 8, 6, 1, 7, 9}};

    //printSudoku(sudokuGridSolved);

    //assert(!sudokuSolver(sudokuGridSolved));
    //assert(!radixSudokuSolver(sudokuGridSolved));

    return 0;
}

__CPROVER_bitvector[1] sudokuSolver(unsigned __CPROVER_bitvector[6] sudokuGrid[][SIZE]) {

    for (unsigned __CPROVER_bitvector[4] i = 0; i < SIZE; ++i) {
        for (unsigned __CPROVER_bitvector[4] j = 0; j < SIZE - 1; ++j) {
            for (unsigned __CPROVER_bitvector[4] k = j + 1; k < SIZE; ++k) {

                if (sudokuGrid[i][j] == sudokuGrid[i][k]) {

                    printf("Two elements on the same row:\n"
                           "#1 Element: (%i , %i)\n"
                           "#2 Element: (%i, %i)",
                           i + 1, j + 1, i + 1, k + 1);

                    return false;
                }

                if (sudokuGrid[j][i] == sudokuGrid[k][i]) {

                    printf("Two elements on the same column:\n"
                           "#1 Element: (%i, %i)\n"
                           "#2 Element: (%i, %i)",
                           j + 1, i + 1, k + 1, i + 1);

                    return false;
                }
            }
        }
    }

    unsigned __CPROVER_bitvector[4] tmp, counter = 0;

    for (unsigned __CPROVER_bitvector[4] w = 0, x = 2; w <= 6 && x <= 8; w += 3, x += 3) {
        for (unsigned __CPROVER_bitvector[4] y = 0, z = 2; y <= 6 && z <= 8; y += 3, z += 3) {
            for (unsigned __CPROVER_bitvector[4] k = 0; k < 9; ++k) {
                for (unsigned __CPROVER_bitvector[4] i = w; i <= x; ++i) {
                    for (unsigned __CPROVER_bitvector[4] j = y; j <= z; ++j) {

                        if (counter == k) {
                            tmp = sudokuGrid[i][j];
                            counter++;
                            continue;
                        }

                        if (sudokuGrid[i][j] == tmp) {

                            printf("Two elements on the same submatrix\n\n"
                                   "Corners of Submatrix:\n"
                                   "- First Element: (%i, %i);\n"
                                   "- Last Element: (%i, %i)\n\n"
                                   "Elements in conflict: %i, %i",
                                   w + 1, x + 1, y + 1, z + 1, tmp, sudokuGrid[i][j]);

                            return false;
                        }
                        counter++;
                    }
                }
                counter = 0;
                tmp = MINUS_INFINITE;
            }
        }
    }
    return true;
}

__CPROVER_bitvector[1] radixSudokuSolver(unsigned __CPROVER_bitvector[6] sudokuGrid[][SIZE]) {

    for (unsigned __CPROVER_bitvector[4] i = 0; i < SIZE; ++i) {
        if (thereAreDuplicatesInRows(sudokuGrid[i])) {
            return false;
        }
    }

    for (unsigned __CPROVER_bitvector[4] i = 0; i < SIZE; ++i) {
        if (thereAreDuplicatesInCols(&sudokuGrid[0][i])) {
            return false;
        }
    }

    // TRANSPOSE METHOD TO CHECK COLS IN SUDOKU INSTANCE

    /*unsigned __CPROVER_bitvector[4] sudokuGridTransposed[SIZE][SIZE]={0};

    for (unsigned __CPROVER_bitvector[4] i = 0; i < SIZE; ++i) {
        for (unsigned __CPROVER_bitvector[4] j = 0; j < SIZE; ++j) {
            sudokuGridTransposed[i][j] = sudokuGrid[j][i];
        }
    }

    for (unsigned __CPROVER_bitvector[4] i = 0; i < SIZE; ++i) {
        if (thereAreDuplicatesInRows(sudokuGridTransposed[i])){
            return false;
        }
    }*/

    unsigned __CPROVER_bitvector[4] counter[SIZE + 1] = {0};

    for (unsigned __CPROVER_bitvector[4] w = 0, x = 2; w <= 6 && x <= 8; w += 3, x += 3) {
        for (unsigned __CPROVER_bitvector[4] y = 0, z = 2; y <= 6 && z <= 8; y += 3, z += 3) {

            for (unsigned __CPROVER_bitvector[4] i = w; i <= x; ++i) {
                for (unsigned __CPROVER_bitvector[4] j = y; j <= z; ++j) {
                    counter[sudokuGrid[i][j]]++;
                }
            }

            for (unsigned __CPROVER_bitvector[4] k = 0; k <= SIZE; ++k) {

                if (counter[k] > 1) {
                    return false;
                }

                counter[k] = 0;
            }
        }
    }
    return true;
}

__CPROVER_bitvector[1] thereAreDuplicatesInRows(unsigned __CPROVER_bitvector[6] *sudokuArray) {

    unsigned __CPROVER_bitvector[4] counter[SIZE + 2] = {0};

    for (unsigned __CPROVER_bitvector[4] i = 0; i < SIZE; ++i) {
        counter[sudokuArray[i]]++;
    }

    for (unsigned __CPROVER_bitvector[4] i = 0; i < SIZE + 1; ++i) {
        if (counter[i] > 1) {
            return true;
        }
    }

    return false;
}

__CPROVER_bitvector[1] thereAreDuplicatesInCols(unsigned __CPROVER_bitvector[6] *firstElementPointer) {

    unsigned __CPROVER_bitvector[6] counter[SIZE + 2] = {0};

    for (unsigned __CPROVER_bitvector[7] i = 0; i < SIZE * SIZE; i += 9) {
        counter[*(firstElementPointer + i)]++;
    }

    for (unsigned __CPROVER_bitvector[4] i = 0; i < SIZE + 1; ++i) {
        if (counter[i] > 1) {
            return true;
        }
    }

    return false;
}

void fillSudokuGrid(unsigned __CPROVER_bitvector[6] sudokuGrid[][SIZE]) {

    for (unsigned __CPROVER_bitvector[4] i = 0; i < SIZE; ++i) {
        for (unsigned __CPROVER_bitvector[4] j = 0; j < SIZE; ++j) {

            if (sudokuGrid[i][j] == 0) {
                sudokuGrid[i][j] = generateNonDeterministicNumbers();
                __VERIFIER_assume(sudokuGrid[i][j]>=1 && sudokuGrid[i][j]<=9);
            }
        }
    }
}

void printSudoku(unsigned __CPROVER_bitvector[6] sudokuGrid[][SIZE]) {
    printf("     1   2   3   4   5   6   7   8   9");
    printf("\n   -------------------------------------\n");

    for (unsigned __CPROVER_bitvector[4] i = 0; i < SIZE; ++i) {
        printf("%i  |", i + 1);
        for (unsigned __CPROVER_bitvector[4] j = 0; j < SIZE; ++j) {
            printf(" %i |", sudokuGrid[i][j]);
        }
        printf("\n   -------------------------------------\n");
    }
}

__CPROVER_bitvector[1] readSudokuCertificate(unsigned __CPROVER_bitvector[6] rows, unsigned __CPROVER_bitvector[6] cols, unsigned __CPROVER_bitvector[6] (*a)[cols], const char *filename) {

    FILE *fileSudokuCertificate;
    fileSudokuCertificate = fopen(filename, "r");

    if (fileSudokuCertificate == NULL) {
        return false;
    }

    for (unsigned __CPROVER_bitvector[6] i = 0; i < rows; ++i) {
        for (unsigned __CPROVER_bitvector[6] j = 0; j < cols; ++j) {
            fscanf(fileSudokuCertificate, "%d", a[i] + j);
            fseek(fileSudokuCertificate, 1, SEEK_CUR);
        }
    }

    fclose(fileSudokuCertificate);
    return true;
}