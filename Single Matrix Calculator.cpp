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
    std::vector<std::vector<int>> minor(n - 1, std::vector<int>(n - 1, 0));; //Blank minor matrix
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

std::vector<std::vector<int>> cofactor_matrix(std::vector<std::vector<int>> &mat, int n)
{
    std::vector<std::vector<int>> cft_mat(n, std::vector<int>(n, 0));//Blank cofactor matrix 
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if ((i + j) % 2 == 0) cft_mat[i][j] = minor_matrix_det_calculator(mat, i, j, n);
            else cft_mat[i][j] = -minor_matrix_det_calculator(mat, i, j, n);
        }
    }
    return cft_mat;
}

std::vector<std::vector<int>> inverse_matrix(std::vector<std::vector<int>>& mat, int n)
{
    std::vector<std::vector<int>> cft_mat = cofactor_matrix(mat, n);
    std::vector<std::vector<int>> inv_mat(n, std::vector<int>(n, 0)); //Blank inverse matrix
    int det_mat = det(mat, n);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            inv_mat[i][j] = cft_mat[i][j] / det_mat;
        }

    return inv_mat;
}

void swap(std::vector<std::vector<int>> &mat, int row1, int row2, int col)
{
    for (int i = 0; i < col; i++)
    {
        int temp = mat[row1][i];
        mat[row1][i] = mat[row2][i];
        mat[row2][i] = temp;
    }
}

int rankOfMatrix(std::vector<std::vector<int>> &mat, int n)
{
    int rank = n;

    for (int row = 0; row < rank; row++)
    {
        if (mat[row][row])
        {
            for (int col = 0; col < n; col++)
            {
                if (col != row)
                {
                    double mult = (double)mat[col][row] /
                        mat[row][row];
                    for (int i = 0; i < rank; i++)
                        mat[col][i] -= mult * mat[row][i];
                }
            }
        }
        else
        {
            bool reduce = true;

            for (int i = row + 1; i < n; i++)
            {
                if (mat[i][row])
                {
                    swap(mat, row, i, rank);
                    reduce = false;
                    break;
                }
            }

            if (reduce)
            {
                rank--;
                for (int i = 0; i < n; i++)
                    mat[i][row] = mat[i][rank];
            }

            row--;
        }
    }
    return rank;
}

int main()
{
    int n;
    int m;

    std::cout << "Enter dimension of matrix (rows): ";
    std::cin >> n;
    std::cout << "Enter dimension of matrix (columns): ";
    std::cin >> m;

    std::vector<std::vector<int>> mat(n, std::vector<int>(m, 0));//Blank mat so I don't have to deal with the push shenanigans

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
        {
            std::cin >> mat[i][j];
        }

    if (n == m)
    {
        std::vector<std::vector<int>> cft_mat = cofactor_matrix(mat, n);
        std::cout << "Your cofactor matrix is: " << std::endl;

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
                std::cout << cft_mat[i][j] << " ";
            std::cout << std::endl;
        }

        if (det(mat, n))
        {
            std::vector<std::vector<int>> inv_mat = inverse_matrix(mat, n);

            std::cout << "Your inverse matrix is: " << std::endl;

            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                    std::cout << inv_mat[i][j] << " ";
                std::cout << std::endl;
            }
        }
        else
        {
            std::cout << "There's no inverse matrix for the provided matrix as its determinant is equal to 0." << std::endl;
        }
    }
    
    int rank = rankOfMatrix(mat, n);
    std::cout << "The rank of your matrix is: " << rank << std::endl;

    return 0;
}
