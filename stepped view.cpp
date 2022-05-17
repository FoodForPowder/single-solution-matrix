#include <fstream>
#include <iostream>
#include <cstdio>
#define ROW M
#define COLUMNS N
using namespace std;
void SolveMatrix(int numberOfRows, int numberOfColumns, double** matrix);
int main()
{
    ifstream fin;
    fin.open("input.txt");
    if (fin.is_open()) {
        int ROW, COLUMNS;
        fin >> ROW >> COLUMNS;
        COLUMNS++;
        double** expanded_matrix;
        expanded_matrix = new double* [ROW];
        for (int i = 0; i < ROW; i++) expanded_matrix[i] = new double[COLUMNS];
        for (int i = 0; i < ROW; i++) {
            for (int j = 0; j < COLUMNS; j++) fin >> expanded_matrix[i][j];
        }
        SolveMatrix(ROW, COLUMNS - 1, expanded_matrix);
        
    }
    return 0;
}
void SolveMatrix(int numberOfRows, int numberOfColumns, double** matrix) {
    for (int i = 0; i < numberOfRows - 1; i++)
    {
        int leadingElem = i;
        for (int j = i + 1; j < numberOfRows; j++)
        {
            if (std::abs(matrix[j][i]) > std::abs(matrix[leadingElem][i]))
            {
                leadingElem = j;
            }
        }
        if (leadingElem != i)
        {
            for (int j = i; j <= numberOfColumns; j++) //Смена мест двух строк
            {
                double supNum = matrix[i][j];
                matrix[i][j] = matrix[leadingElem][j];
                matrix[leadingElem][j] = supNum;
            }
        }
        for (int k = i + 1; k < numberOfRows; k++) // Умножение всех элементов строки на некоторое число, не равное нулю и прибавление к элементам одной строки соответствующих элементов другой строки
        {
            double coefficient = matrix[k][i] / matrix[i][i];
            for (int j = i; j <= numberOfColumns; j++)
            {
                matrix[k][j] -= coefficient * matrix[i][j];
            }
        }
    }
    for (int i = numberOfRows - 1; i >= 1; i--) // Умножение всех элементов строки на некоторое число, не равное нулю и прибавление к элементам одной строки соответствующих элементов другой строки
    {
        for (int k = 0; k <= i - 1; k++)
        {
            double coufficient = matrix[k][i] / matrix[i][i];
            matrix[k][numberOfColumns] -= coufficient * matrix[i][numberOfColumns];
            matrix[k][i] = 0;
        }
    }
    FILE* out;
    fopen_s(&out, "output.txt", "w");
    int numOfZero = 0;
    if (matrix[numberOfRows - 1][numberOfColumns] != 0) {
        for (int j = 0; j <= numberOfColumns; j++)
            if (matrix[numberOfRows - 1][j] == 0) numOfZero += 1;
    }
    if (numOfZero == numberOfColumns) {
        fprintf(out, "Inconsistent");
    }
    else {
       
        for (int i = 0; i < numberOfRows; i++) {
            double x = matrix[i][numberOfColumns] / matrix[i][i];
            fprintf(out,"x%d = %.2f; \n", i + 1, x);
        }
    }
}