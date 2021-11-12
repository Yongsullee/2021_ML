#include <stdio.h>
#include <string.h>
#include <DataSet.h>
#include <stdlib.h>

// theota0 value and thoeta1 value return
double *derivative_reuslt(double *First_partial_result, double *Second_partial_result)
{
    //I/O process
    printf("First partial derivatvie respect to thoeta_0: %lf, %lf, %lf\n", First_partial_result[0], First_partial_result[1], First_partial_result[2]);
    printf("Second partial derivatvie respect to thoeta_1: %lf, %lf, %lf\n", Second_partial_result[0], Second_partial_result[1], Second_partial_result[2]);

    double common_multiple = (Second_partial_result[0] / 1800) / (First_partial_result[0] / 1800);
    double second_res_1 = 0;
    double second_res_2 = 0;
    double third_res_1 = 0;
    double third_res_2 = 0;

    static double fin_res[2] = {
        0,
    };
    // To proceed to the simultaneous equation with common multiple produced by Theota_0's constant
    second_res_1 = First_partial_result[1] * common_multiple;
    second_res_2 = Second_partial_result[1] * common_multiple;

    // To proceed to the simultaneous equation with common multiple produced by Theota_0's constant
    third_res_1 = First_partial_result[2] * common_multiple;
    third_res_2 = Second_partial_result[2] * common_multiple;
    // fin_res[1] for optimal theota_1 value
    fin_res[1] = (third_res_1 - third_res_2) / (second_res_1 - second_res_2);
    // fin_res[0] for optimal theota_0 value
    fin_res[0] = First_partial_result[2] - (First_partial_result[1] * fin_res[1]);

    return fin_res;
};

// theota0 value, theota1 value, and constant value
double *First_partial(double *x_data, double *y_data, int size)
{
    //size is 1800 in decimal value
    int n = size;
    //initialization here!
    static double result[3] = {
        0,
    };
    double first_res = 0;
    double second_res = 0;
    double third_res = 0;

    first_res = (double)n;

    for (int i = 0; i < n; i++)
    {
        second_res += x_data[i];
        third_res += (-1 * y_data[i]);
    }

    result[0] = first_res / (double)n;
    result[1] = second_res / (double)n;
    result[2] = third_res / (double)n;
    printf("** First partial derivative result is as below! **\n");
    printf("Result 1 is : %lf theta0\t", result[0]);
    printf("Result 2 is : %lf theta1\t", result[1]);
    printf("Result 3 is : %lf\n", result[2]);

    return result;
};

// theota0 value, theota1 value, and constant value
double *Second_partial(double *x_data, double *y_data, int size)
{
    //size is 1800 in decimal value
    int n = size;
    //initialization here!
    static double result_1[3] = {
        0,
    };
    double first_res = 0;
    double second_res = 0;
    double third_res = 0;

    for (int i = 0; i < n; i++)
    {
        first_res += (n * x_data[i]);
        second_res += (x_data[i] * x_data[i]);
        third_res += ((-1 * y_data[i]) * x_data[i]);
    }

    result_1[0] = first_res / (double)n;
    result_1[1] = second_res / (double)n;
    result_1[2] = third_res / (double)n;
    printf("** Second partial derivative result is as below! **\n");
    printf("Result 1 is : %lf theta0\t", result_1[0]);
    printf("Result 2 is : %lf theta1\t", result_1[1]);
    printf("Result 3 is : %lf\n", result_1[2]);

    return result_1;
};

int main(void)
{
    // Number of data from dataset.h file
    int n = (sizeof(total_data) / sizeof(double));
    int x_data_size = n / 2;
    int y_data_size = n / 2;
    int j = 0;
    int k = 0;

    //printf("Total number of dataset: %d\n", n);

    // Initialization
    double x_data[1800] = {
        0,
    };
    double y_data[1800] = {
        0,
    };

    // To devide the dataSet into x_data, and y_data
    for (int i = 0; i < n; i++)
    {
        if ((i % 2) == 2 || (i % 2) == 0)
        {
            x_data[j] = total_data[i];
            j++;
        }
        else
        {
            y_data[k] = total_data[i];
            k++;
        }
    }

    double theota_0 = 0;
    double theota_1 = 0;
    double *First_partial_result = 0;
    double *Second_partial_result = 0;
    double *MSE_pair = 0;

    // thoeta_0과 theota_1의 partial derivative 식 반환 [theota_1 vlaue, theota_2 value, and constant value]
    //First_partial_result = First_partial(x_data, y_data, x_data_size);
    First_partial_result = First_partial(x_data, y_data, x_data_size);
    //Second_partial_result = Second_partial(x_data, y_data, x_data_size);
    Second_partial_result = Second_partial(x_data, y_data, x_data_size);

    MSE_pair = derivative_reuslt(First_partial_result, Second_partial_result);

    printf("Finally Optimal Theota_0: %lf, Optimal Theota_1: %lf !\n", MSE_pair[0], MSE_pair[1]);

    double res1 = (MSE_pair[1] * x_data[0]) + MSE_pair[0];
    double res2 = (MSE_pair[1] * x_data[1]) + MSE_pair[0];
    double res3 = (MSE_pair[1] * x_data[2]) + MSE_pair[0];

    printf(" y-data: [%lf], optimal value: [%lf] ", y_data[0], res1);
    printf(" y-data: [%lf], optimal value: [%lf] ", y_data[1], res2);
    printf(" y-data: [%lf], optimal value: [%lf] ", y_data[2], res3);

    return 0;
}