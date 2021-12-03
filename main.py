import os
import numpy as np

sudoku = np.zeros((9, 9))

fileSudokuCertificate = open("sudoku_certificate.out", "r")
contentFileSudokuCertificate = fileSudokuCertificate.read().split("\n")

indexCurrentRow = 0

for line in contentFileSudokuCertificate:
    line = line.replace(" ", "")
    sudoku[indexCurrentRow] = np.matrix([line[0], line[1], line[2], line[3], line[4], line[5], line[6], line[7], line[8]])
    indexCurrentRow = indexCurrentRow+1

commandTraceCBMC = os.popen('cbmc sudoku_solver.c --trace')
fullTraceCBMC = commandTraceCBMC.read()
compactTraceCBMC = fullTraceCBMC.split("sudokuGrid=sudokuGrid")[1]

fileTraceCBMC = open("sudoku_solution.out", "a")
fileTraceCBMC.write(compactTraceCBMC)
fileTraceCBMC.close()

fileTraceCBMC = open("sudoku_solution.out", "r")
contentFileTraceCBMC = fileTraceCBMC.read().split("\n")

for line in contentFileTraceCBMC:
    if "sudokuGrid[" in line:
        line = line.replace("l", "")
        line = line.replace(" ", "")
        line = line[:-8]

        x = int(line[11])
        y = int(line[14])
        z = int(line[17])
        sudoku[x][y] = z

print(np.array(sudoku))