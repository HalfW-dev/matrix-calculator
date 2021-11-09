#include <iostream>
#include <vector>
#include <cmath>

    int determinant(std::vector<std::vector<int>> matrix, int n) //Having the determinant function separated from the rest of the program
    {
        int det = 0;
        std::vector<std::vector<int>> submatrix(n, std::vector<int>(n, 0)); //Blank matrix so I don't have to deal with the push shenanigans

        if (n == 1) return (matrix[0][0]);
        if (n == 2) return ((matrix[0][0] * matrix[1][1]) - (matrix[1][0] * matrix[0][1]));

        else {
            for (int x = 0; x < n; x++)
            {
                int subi = 0;
                for (int i = 1; i < n; i++)
                {
                    int subj = 0;
                    for (int j = 0; j < n; j++)
                    {
                        if (j == x)
                            continue;
                        submatrix[subi][subj] = matrix[i][j];
                        subj++;
                    }
                    subi++;
                }
                det = det + (pow(-1, x) * matrix[0][x] * determinant(submatrix, n - 1));
            }
        }
        return det;
    }

    int minor_matrix_det_calculator(std::vector<std::vector<int>> matrix, int i, int j, int n) //Specifying the ij element for Laplace expansion for all elements in the argument matrix
    {
        std::vector<std::vector<int>> minor(n-1, std::vector<int>(n-1, 0));; //Placeholder for every minor matrix calculated, also blank matrix so I don't have to deal with the push shenanigans
        int i_minor = 0;
        int j_minor = 0;

        for (int a = 0; a < n; a++) //Looping through the rows of the argument matrix
        {
            if (a == i) continue; //Opting out all elements of the i-th row
            else
            {
                for (int b = 0; b < n; b++) //Looping through the columns of the argument matrix
                    if (b == j) continue; // Opting out all elements of the n-th column
                    else
                    {
                        if (j_minor >= n - 1) //Moving on to the next row at the end of row for the minor matrix
                        {
                            j_minor = 0;
                            i_minor = i_minor + 1;
                        }

                        minor[i_minor][j_minor] = matrix[a][b];
                        j_minor = j_minor + 1;
                        minor;
                    }
            }
        }

        int det_minor = determinant(minor, n - 1);
        return det_minor;
    }

    void cofactor_matrix_and_determinants(std::vector<std::vector<int>> matrix, int n)
    {
        std::vector<std::vector<int>> cofactor_matrix(n, std::vector<int>(n, 0));//Blank matrix so I don't have to deal with the push shenanigans
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if ((i + j) % 2 == 0) cofactor_matrix[i][j] = minor_matrix_det_calculator(matrix, i, j, n);
                else cofactor_matrix[i][j] = -minor_matrix_det_calculator(matrix, i, j, n);
            }
        }

        std::cout << "Your cofactor matrix is: " << std::endl;

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
                std::cout << cofactor_matrix[i][j] << " ";
            std::cout << std::endl;
        }

        std::cout << "Determinant of the matrix is: " << determinant(matrix, n) << std::endl;
        std::cout << "Determinant of the cofactor matrix is: " << determinant(cofactor_matrix, n);
    }

    int main()
    {
        int n;

        std::cout << "Enter dimension of square matrix (n x n): ";
        std::cin >> n;

        std::vector<std::vector<int>> matrix(n, std::vector<int>(n, 0));//Blank matrix so I don't have to deal with the push shenanigans

        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
            {
                std::cin >> matrix[i][j];
            }

       cofactor_matrix_and_determinants(matrix, n);
       return 0;
    }

//How to use:
//
//In the terminal:
//1. Specify the dimension of the square matrix
//2. Each input is a row of the matrix, each element is separated by space
//    For example:
//        1 2 3 (press Enter)
//        4 5 6 (press Enter)
//        7 8 9 (press Enter)
//3. Output will include the cofactor matrix of the provided matrix, and the determinant of both the provided matrix and the cofactor matrix.