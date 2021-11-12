#include <stdio.h>
#include <string.h>
#include <DataSet.h>
#include <stdlib.h>

double *matrix_multiplication(double x_data[][3], double xt_data[][1800], int x_row, int x_column, int xt_row, int xt_column)
{

    // printf("%d, %d,  %d, %d\n", x_row, x_column, xt_row, xt_column);
    static double output[3][3] = {
        0,
    };

    for (int i = 0; i < xt_row; i++)
    {
        for (int j = 0; j < x_column; j++)
        {
            for (int k = 0; k < xt_column; k++)
            {
                output[i][j] += (xt_data[i][k] * x_data[k][j]);
            }
        }
    }
    /*
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("[%d][%d]%lf\t", i, j, output[i][j]);
        }
    }
    */
    return output;
}

double *matrix_transpose(double x_data[][3], int x_row, int x_column)
{
    static double output[3][1800] = {
        0,
    };

    int output_row = x_column;
    int output_column = x_row;

    // Transpose of X matrix is stored into "Output" matrix
    for (int i = 0; i < x_column; i++)
    {
        for (int j = 0; j < x_row; j++)
        {
            output[i][j] = x_data[j][i];
        }
    }

    for (int i = 0; i < output_row; i++)
    {
        for (int j = 0; j < output_column; j++)
        {
            //            printf("[%d][%d] %lf\t", i, j, output[i][j]);
        }
    }

    return output;
}

double *matrix_inversion(double data[][3], int data_row, int data_column)
{
    static double output[3][3] = {
        0,
    };
    double a10 = data[0][0];
    double a11 = data[0][1];
    double a12 = data[0][2];
    double b10 = data[1][0];
    double b11 = data[1][1];
    double b12 = data[1][2];
    double c10 = data[2][0];
    double c11 = data[2][1];
    double c12 = data[2][2];

    //printf("| %lf\t%lf\t%lf |\n| %lf\t%lf\t%lf |\n| %lf\t%lf\t%lf |\n", a10, a11, a12, b10, b11, b12, c10, c11, c12);

    double det = 0;
    det = (a10 * b11 * c12) - (a10 * b12 * c11) - (a11 * b10 * c12) - (a11 * b12 * c10) - (a12 * b10 * c11) - (a12 * b11 * c10);
    if (!det)
    {
        printf(" No inverse Matrix: %lf \n", det);
        return 0;
    }

    //printf("%lf\n", det);
    output[0][0] = ((b11 * c12) - (b12 * c11)) / det;
    output[0][1] = ((a12 * c11) - (a11 * c12)) / det;
    output[0][2] = ((a11 * b12) - (a12 * b11)) / det;
    output[1][0] = ((b12 * c10) - (b10 * c12)) / det;
    output[1][1] = ((a10 * c12) - (a12 * c10)) / det;
    output[1][2] = ((a12 * b10) - (a10 * b12)) / det;
    output[2][0] = ((b10 * c11) - (b11 * c10)) / det;
    output[2][1] = ((a11 * c10) - (a10 * c11)) / det;
    output[2][2] = ((a10 * b11) - (a11 * b10)) / det;
    /*
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("[%d][%d]: %lf", i, j, output[i][j]);
        }
    }
    */
    return output;
}

double *matrix_inverse_multiplication(double inverse_data[][3], double xt_data[][1800], int inverse_row, int xt_row, int xt_column)
{

    static double output[3][1800] = {
        0,
    };

    for (int i = 0; i < inverse_row; i++)
    {
        for (int j = 0; j < xt_column; j++)
        {
            for (int k = 0; k < xt_row; k++)
            {
                output[i][j] += (inverse_data[i][k] * xt_data[k][j]);
            }
        }
    }
    /*
    for (int i = 0; i < inverse_row; i++)
    {
        for (int j = 0; j < xt_column; j++)
        {
            printf("[%d][%d]%lf\t", i, j, output[i][j]);
        }
    }
    */
    return output;
}

double *matrix_multiplication_3(double xt_x_inverse_multiple_result[][1800], double y_data[][1], int xt_x_row, int y_row, int y_column)
{
    static double output[3][1] = {
        0,
    };

    for (int i = 0; i < xt_x_row; i++)
    {
        for (int j = 0; j < y_column; j++)
        {
            for (int k = 0; k < y_row; k++)
            {
                output[i][j] += (xt_x_inverse_multiple_result[i][k] * y_data[k][j]);
            }
        }
    }
    /*
    for (int i = 0; i < xt_x_row; i++)
    {
        for (int j = 0; j < y_column; j++)
        {
            printf("[%d][%d]%lf\t", i, j, output[i][j]);
        }
    }
    */
    return output;
}

int main(void)
{
    int n = (sizeof(total_data) / sizeof(double));

    printf("Total number of data is: %d \n", n);

    double x_data[1800][3] = {
        0,
    };

    int x_row = sizeof(x_data) / sizeof(x_data[0]);
    int x_column = sizeof(x_data[0]) / sizeof(double);
    //double *x_transpose = 0;

    // printf("%d, %d", x_row, x_column)
    double y_data[1800] = {
        0,
    };

    int j = 0;
    int k = 0;

    //Extract Data from Dataset.h Here

    // for X^0 data for all '1'
    for (int i = 0; i < 1800; i++)
    {
        x_data[i][0] = 1;
    }

    for (int i = 0; i < n; i++)
    {
        if ((i % 2) == 2 || (i % 2) == 0)
        {
            // For X_1 value to be set X
            x_data[j][1] = total_data[i];
            // For X_2 value to be set X^2
            x_data[j][2] = total_data[i] * total_data[i];
            j++;
        }
        else
        {
            // For Y value to be set Y
            y_data[k] = total_data[i];
            k++;
        }
    }

    // original X vector
    /*
    for (int i = 0; i < x_row; i++)
    {
        for (int j = 0; j < x_column; j++)
            printf("[%d][%d]: %lf\t", i, j, x_data[i][j]);
    }

    for (int i = 0; i < (n / 2); i++)
    {
        printf("[%d][0]: %lf \t", i, y_data[i]);
    }
*/
    //    printf("\n");

    // X^T 계산을 위해 Matrix_Transpose 함수 선언
    double(*x_transpose)[1800] = matrix_transpose(x_data, x_row, x_column);

    int xt_row = x_column;
    int xt_column = x_row;
    /*
    for (int i = 0; i < xt_row; i++)
    {
        for (int j = 0; j < xt_column; j++)
            printf("[%d][%d] %lf\t", i, j, x_transpose[i][j]);
        printf("\n");
    }
    */
    // X^t * X
    double(*xt_x_multiple_result)[3] = matrix_multiplication(x_data, x_transpose, x_row, x_column, xt_row, xt_column);
    /*
    for (int i = 0; i < x_row; i++)
    {
        for (int j = 0; j < xt_column; j++)
            printf("[%d][%d] %lf\t", i, j, xt_x_multiple_result[i][j]);
        printf("\n");
    }*/
    //double(*xt_x_inverse_result)

    // (X^t * X)^-1 inverse 구현
    double(*xt_x_inverse_result)[3] = matrix_inversion(xt_x_multiple_result, xt_row, x_column);
    /*
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("[%d][%d]: %lf", i, j, xt_x_inverse_result[i][j]);
        }
    }
    */
    int xt_x_row = xt_row;

    double(*xt_x_inverse_multiple_result)[1800] = matrix_inverse_multiplication(xt_x_inverse_result, x_transpose, xt_x_row, xt_row, xt_column);
    /*
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 1800; j++)
        {
            printf("[%d][%d]: %lf", i, j, xt_x_inverse_multiple_result[i][j]);
        }
    }
    */
    int y_row = sizeof(y_data) / sizeof(y_data[0]);
    int y_column = sizeof(y_data[0]) / sizeof(double);

    double(*final_result)[1] = matrix_multiplication_3(xt_x_inverse_multiple_result, y_data, xt_x_row, y_row, y_column);
    /*
    for (int i = 0; i < 3; i++)
    {
        printf("%lf\n", final_result[i][0]);
    }

    printf("\n");
    */
    printf(" 'a' value is: %lf\n 'b' value is: %lf\n 'c' value is: %lf\n", final_result[0][0], final_result[1][0], final_result[2][0]);

    double res1 = (final_result[0][0] * x_data[0][2]) + (final_result[1][0] * x_data[0][1]) + final_result[2][0];
    double res2 = (final_result[0][0] * x_data[1][2]) + (final_result[1][0] * x_data[1][1]) + final_result[2][0];

    printf(" y_data : %lf, and with the optimal value: %lf\n", y_data[0], res1);
    printf(" y_data : %lf, and with the optimal value: %lf", y_data[1], res2);

    return 0;
}