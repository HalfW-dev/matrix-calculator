#include <iostream>
#include <vector>
#include <cmath>

    int det(std::vector<std::vector<int>> mat, int n) //Determinant function
    {
        int d = 0;
        std::vector<std::vector<int>> submat(n, std::vector<int>(n, 0)); //Blank matrix so no push shenanigans

        if (n == 1) return (mat[0][0]);
        if (n == 2) return ((mat[0][0] * mat[1][1]) - (mat[1][0] * mat[0][1]));

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
                        submat[subi][subj] = mat[i][j];
                        subj++;
                    }
                    subi++;
                }
                d = d + (pow(-1, x) * mat[0][x] * det(submat, n - 1));
            }
        }
        return d;
    }

    int minor_matrix_det_calculator(std::vector<std::vector<int>> mat, int i, int j, int n) //Specifies the ij element for Laplace expansion for all elements in the argument matrix
    {
        std::vector<std::vector<int>> minor(n-1, std::vector<int>(n-1, 0));; //Placeholder for minor matrix , also blank mat so no shenanigans
        int i_minor = 0;
        int j_minor = 0;

        for (int a = 0; a < n; a++) //Loops through row of matrix
        {
            if (a == i) continue; //Opts out all elements of the i-th row
            else
            {
                for (int b = 0; b < n; b++) //Loops through the column of matrix
                    if (b == j) continue; // Opts out all elements of the n-th column
                    else
                    {
                        if (j_minor >= n - 1) //Moves to next row at the end of row 
                        {
                            j_minor = 0;
                            i_minor = i_minor + 1;
                        }

                        minor[i_minor][j_minor] = mat[a][b];
                        j_minor = j_minor + 1;
                    }
            }
        }

        int det_minor = det(minor, n - 1);
        return det_minor;
    }

    void cofactor_matrix_and_determinants(std::vector<std::vector<int>> mat, int n)
    {
        std::vector<std::vector<int>> cft_mat(n, std::vector<int>(n, 0));//Blank mat so I don't have to deal with the push shenanigans
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if ((i + j) % 2 == 0) cft_mat[i][j] = minor_matrix_det_calculator(mat, i, j, n);
                else cft_mat[i][j] = -minor_matrix_det_calculator(mat, i, j, n);
            }
        }

        std::cout << "Your cofactor matrix is: " << std::endl;

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
                std::cout << cft_mat[i][j] << " ";
            std::cout << std::endl;
        }

        std::cout << "Determinant of the matrix is: " << det(mat, n) << std::endl;
        std::cout << "Determinant of the cofactor matrix is: " << det(cft_mat, n);
    }

    int main()
    {
        int n;

        std::cout << "Enter dimension of square matrix (n x n): ";
        std::cin >> n;

        std::vector<std::vector<int>> mat(n, std::vector<int>(n, 0));//Blank mat so I don't have to deal with the push shenanigans

        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
            {
                std::cin >> mat[i][j];
            }

       cofactor_matrix_and_determinants(mat, n);
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
//3. Output will include the cofactor mat of the provided matrix, and the determinant of both the provided matrix and the cofactor matrix.
