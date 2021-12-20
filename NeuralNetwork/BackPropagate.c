#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "TrainSet.h"

#define INPUT_NODE 2
#define L1_NODE 4
#define L2_NODE 4
#define L3_NODE 1
double biasUnit = 1;
double lr = 0.01;

double random()
{
    double a[6] = {
        0.1, 0.2, 0.3, -0.1, -0.2, -0.3};
    int b = rand() % 6;

    double c = a[b];

    return c;
}

double *sumOfWeight_0(double *a_val, double weight_0[][3])
{
    static double result[4] = {
        0,
    };
    result[0] = biasUnit;
    for (int i = 1; i < 4; i++)
    {
        result[i] = (a_val[0] * weight_0[0][(i - 1)]) + (a_val[1] * weight_0[1][(i - 1)]);
    }
    return result;
}

double *sumOfWeight_1(double *a_val, double weight_1[][3])
{
    static double result[4] = {
        0,
    };
    result[0] = biasUnit;
    for (int i = 1; i < 4; i++)
    {
        result[i] = (a_val[0] * weight_1[0][i - 1]) + (a_val[1] * weight_1[1][i - 1]) + (a_val[2] * weight_1[2][i - 1]) + (a_val[3] * weight_1[3][i - 1]);
    }
    return result;
}

double sumOfWeight_2(double *a_val, double weight_2[][1])
{
    static double result = 0;

    result = (a_val[0] * weight_2[0][0]) + (a_val[1] * weight_2[1][0]) + (a_val[2] * weight_2[2][0]) + (a_val[3] * weight_2[3][0]);

    return result;
}

double DELTA_3(double z_3, double actual_y)
{
    static double result = 0;
    result = z_3 - actual_y;

    return result;
}

double DELTA_2(double DELTA_3, double WEIGHT_LINE_2[][1], int target_node)
{
    static double result = 0;
    if (target_node == 0) // a(1)
    {
        // Delta_0 for liine = 2
        result = WEIGHT_LINE_2[1][0] * DELTA_3;
    }
    else if (target_node == 1) // a(2)
    {
        // Delta_1 for liine = 2
        result = WEIGHT_LINE_2[2][0] * DELTA_3;
    }
    else if (target_node == 2) // a(3)
    {
        // Delta_2 for liine = 2
        result = WEIGHT_LINE_2[3][0] * DELTA_3;
    }

    return result;
}

double DELTA_1(double DELTA_2_0, double DELTA_2_1, double DELTA_2_2, double WEIGHT_LINE_1[][3], int target_node)
{
    static double result = 0;
    if (target_node == 0) // a(1)
    {
        result = (WEIGHT_LINE_1[1][0] * DELTA_2_0) + (WEIGHT_LINE_1[1][1] * DELTA_2_1) + (WEIGHT_LINE_1[1][2] * DELTA_2_2);
    }
    else if (target_node == 1) // a(1)
    {
        result = (WEIGHT_LINE_1[2][0] * DELTA_2_0) + (WEIGHT_LINE_1[2][1] * DELTA_2_1) + (WEIGHT_LINE_1[2][2] * DELTA_2_2);
    }
    else if (target_node == 2) // a(1)
    {
        result = (WEIGHT_LINE_1[2][0] * DELTA_2_0) + (WEIGHT_LINE_1[2][1] * DELTA_2_1) + (WEIGHT_LINE_1[2][2] * DELTA_2_2);
    }

    return result;
}

int main(void)
{
    int n = (sizeof(trainSet) / sizeof(double));
    int x_data_size = n / 2;
    int y_data_size = n / 2;
    int j = 0;
    int k = 0;
    double x_data[5000] = {
        0,
    };
    double y_data[5000] = {
        0,
    };
    /* Training set of "x value" and "x value(y = f(x))" */
    for (int i = 0; i < n; i++)
    {
        if ((i % 2) == 2 || (i % 2) == 0)
        {
            x_data[j] = trainSet[i];
            j++;
        }
        else
        {
            y_data[k] = trainSet[i];
            k++;
        }
    }
    j = 0;
    k = 0;
    /****************************/ // Line = 0
    double inputNode[2] = {
        0,
    };
    double weightVal_0[2][3] = {
        0,
    };
    /****************************/ // Line = 1
    double line_1[4] = {
        0,
    };
    double weightVal_1[4][3] = {
        0,
    };
    /****************************/ // Line = 2
    double line_2[4] = {
        0,
    };
    double weightVal_2[4][1] = {
        0,
    };
    /****************************/ // Line = 3
    double outputNode = 0;
    /* bias node and bias weight */
    inputNode[0] = biasUnit;
    line_1[0] = biasUnit;
    line_2[0] = biasUnit;

    for (int i = 0; i < 3; i++)
    {
        weightVal_0[0][i] = biasUnit;
        weightVal_1[0][i] = biasUnit;
    }

    weightVal_2[0][0] = biasUnit;

    /* Initiazlie Weight value with random number 1 ~ 3 */
    /* Weight line = 0 */
    for (int i = 0; i < 3; i++)
    {
        weightVal_0[1][i] = random();
        printf("[l=0] [1][%d] : %lf\n", i, weightVal_0[1][i]);
    }
    printf("**********************************************\n");
    /* Weight Line = 1 */
    for (int i = 1; i < 4; i++)
    {
        for (int a = 0; a < 3; a++)
        {
            weightVal_1[i][a] = random();
            printf("[l=1] [%d][%d] : %lf\n", i, a, weightVal_1[i][a]);
        }
    }
    printf("**********************************************\n");
    /* Weight Line = 2 */
    for (int i = 1; i < 4; i++)
    {
        weightVal_2[i][0] = random();
        printf("[l=2] [%d][0] : %lf\n", i, weightVal_2[i][0]);
    }
    printf("**********************************************\n");

    // Updated weighted value
    double updated_weightVal_2[4][1] = {
        0,
    };

    double updated_weightVal_1[4][3] = {
        0,
    };

    double updated_weightVal_0[2][3] = {
        0,
    };
    for (int i = 0; i < 3; i++)
    {
        updated_weightVal_0[0][i] = biasUnit;
        updated_weightVal_1[0][i] = biasUnit;
    }

    updated_weightVal_2[0][0] = biasUnit;

    double MSE_result_test_0[10000] = {
        0,
    };

    double MSE_result_test_1[5000] = {
        0,
    };

    printf("Train with data set (# of x = 5000)\n");
    printf("Print out the updated weight value and MSE value for each epoch\n");
    printf("**********************************************\n");

    for (int a = 0; a < 1000; a++)
    {
        //Overall Algorithm
        // Line = 3, delta value
        double _delta_3 = 0;
        // Line = 2, delta value = 0, 1, 2
        double _delta_2_0 = 0;
        double _delta_2_1 = 0;
        double _delta_2_2 = 0;
        // Line = 1, delta value = 0, 1, 2
        double _delta_1_0 = 0;
        double _delta_1_1 = 0;
        double _delta_1_2 = 0;
        // Weighted sum for line = 1, 2, 3
        // wegiht value of line 2 to 3, 10, 20, 30
        double change_weightVal_2_10 = 0;
        double change_weightVal_2_20 = 0;
        double change_weightVal_2_30 = 0;

        /* weight value of line 1 to 2, 10,11,12
                                        20,21,22
                                        30,31,32*/
        double change_weightVal_1_10 = 0;
        double change_weightVal_1_11 = 0;
        double change_weightVal_1_12 = 0;

        double change_weightVal_1_20 = 0;
        double change_weightVal_1_21 = 0;
        double change_weightVal_1_22 = 0;

        double change_weightVal_1_30 = 0;
        double change_weightVal_1_31 = 0;
        double change_weightVal_1_32 = 0;

        // weight value of line 0 to 1, 10,11,12
        double change_weightVal_0_10 = 0;
        double change_weightVal_0_11 = 0;
        double change_weightVal_0_12 = 0;

        for (int i = 0; i < 5000; i++)
        {
            double *z_1 = 0;
            double *z_2 = 0;
            double z_3 = 0;

            inputNode[0] = biasUnit;
            inputNode[1] = x_data[i];

            z_1 = sumOfWeight_0(inputNode, weightVal_0);
            z_2 = sumOfWeight_1(z_1, weightVal_1);
            z_3 = sumOfWeight_2(z_2, weightVal_2);

            // Backpropagation here...
            _delta_3 = DELTA_3(z_3, y_data[i]);
            change_weightVal_2_10 += z_2[1] * _delta_3;
            //printf("%lf\n", change_weightVal_2_10);
            change_weightVal_2_20 += z_2[2] * _delta_3;
            change_weightVal_2_30 += z_2[3] * _delta_3;

            _delta_2_0 = DELTA_2(_delta_3, weightVal_2, 0);
            change_weightVal_1_10 += z_1[1] * _delta_2_0;
            change_weightVal_1_20 += z_1[2] * _delta_2_0;
            change_weightVal_1_30 += z_1[3] * _delta_2_0;

            _delta_2_1 = DELTA_2(_delta_3, weightVal_2, 1);
            change_weightVal_1_11 += z_1[1] * _delta_2_1;
            change_weightVal_1_21 += z_1[2] * _delta_2_1;
            change_weightVal_1_31 += z_1[3] * _delta_2_1;

            _delta_2_2 = DELTA_2(_delta_3, weightVal_2, 2);
            change_weightVal_1_12 += z_1[1] * _delta_2_2;
            change_weightVal_1_22 += z_1[2] * _delta_2_2;
            change_weightVal_1_32 += z_1[3] * _delta_2_2;

            _delta_1_0 = DELTA_1(_delta_2_0, _delta_2_1, _delta_2_2, weightVal_1, 0);
            change_weightVal_0_10 += inputNode[1] * _delta_1_0;

            _delta_1_1 = DELTA_1(_delta_2_0, _delta_2_1, _delta_2_2, weightVal_1, 1);
            change_weightVal_0_11 += inputNode[1] * _delta_1_1;

            _delta_1_2 = DELTA_1(_delta_2_0, _delta_2_1, _delta_2_2, weightVal_1, 2);
            change_weightVal_0_12 += inputNode[1] * _delta_1_2;
        }

        weightVal_2[1][0] -= (lr * (0.0002 * change_weightVal_2_10));
        //printf("[%d]: %lf\n", a, weightVal_2[1][0]);
        weightVal_2[2][0] -= (lr * (0.0002 * change_weightVal_2_20));
        //printf("[%d]: %lf\n", a, weightVal_2[2][0]);

        weightVal_2[3][0] -= (lr * (0.0002 * change_weightVal_2_30));

        weightVal_1[1][0] -= (lr * (0.0002 * change_weightVal_1_10));
        weightVal_1[1][1] -= (lr * (0.0002 * change_weightVal_1_11));
        weightVal_1[1][2] -= (lr * (0.0002 * change_weightVal_1_12));

        weightVal_1[2][0] -= (lr * (0.0002 * change_weightVal_1_20));
        weightVal_1[2][1] -= (lr * (0.0002 * change_weightVal_1_21));
        weightVal_1[2][2] -= (lr * (0.0002 * change_weightVal_1_22));

        weightVal_1[3][0] -= (lr * (0.0002 * change_weightVal_1_30));
        weightVal_1[3][1] -= (lr * (0.0002 * change_weightVal_1_31));
        weightVal_1[3][2] -= (lr * (0.0002 * change_weightVal_1_32));

        weightVal_0[1][0] -= (lr * (0.0002 * change_weightVal_0_10));
        weightVal_0[1][1] -= (lr * (0.0002 * change_weightVal_0_11));
        weightVal_0[1][2] -= (lr * (0.0002 * change_weightVal_0_12));

        double MSE_result = 0;
        double MSE_result_2 = 0;
        for (int i = 0; i < 5000; i++)
        {
            inputNode[1] = x_data[i];
            double(*a_1) = sumOfWeight_0(inputNode, weightVal_0);
            double(*a_2) = sumOfWeight_1(a_1, weightVal_1);
            double a_3 = sumOfWeight_2(a_2, weightVal_2);

            MSE_result += (0.5 * (a_3 - y_data[i]) * (a_3 - y_data[i]));
            MSE_result_2 += (a_3 - y_data[i]);
        }
        if ((a % 10) == 0)
        {
            printf("[%d]: MSE for now: %lf \n", a, (MSE_result / 5000));
            //printf("[%d] 1/2*(y' - y)^2 : %lf \n", a, (MSE_result / 5000));
            //printf("[%d] (y' - y): %lf \n", a, (MSE_result_2 / 5000));
        }
    }

    printf("Updated Weight Value for each layer!\n");
    printf("**********************************************\n");

    for (int i = 0; i < 3; i++)
    {
        printf("[l=0] [1][%d] : %lf\n", i, weightVal_0[1][i]);
    }
    printf("**********************************************\n");

    for (int i = 1; i < 4; i++)
    {
        for (int a = 0; a < 3; a++)
        {
            printf("[l=1] [%d][%d] : %lf\n", i, a, weightVal_1[i][a]);
        }
    }
    printf("**********************************************\n");

    for (int i = 1; i < 4; i++)
    {
        printf("[l=2] [%d][0] : %lf\n", i, weightVal_2[i][0]);
    }
}