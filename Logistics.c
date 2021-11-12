#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "ClassiData.h"
#include "Testset.h"

// 3 x 1 matrix
double sigmoid(double* theta, double* x_data)
{
    double power = 0;
    static double result = 0;

    for (int i = 0; i < 3; i++)
    {
        power += theta[i] * x_data[i];
    }

    result = 1 / (1 + (exp((-1 * power))));

    return result;
}

void main()
{
    printf("*********************************************\n\n");
    printf("Train start!\n");
    printf("Dataset loaded from ClassiData.h\n\n");
    printf("*********************************************\n\n");
    int n = (sizeof(x_data) / sizeof(double));
    int m = sizeof(y_data) / sizeof(int);
    int a = 0;
    int b = 0;

    //초기 theta 값(a, b, and c), learning rate = 0.01로 설정 
    double theta[3] = {1, 1, 1};
    double new_theta[3] = {0, };
    double lr = 0.01;

    double x_vector[2000][3] = {
        0,
    };

    double x_param[3] = {
        0,
    };

    // X0 값을 1로 설정
    for (int i = 0; i < 2000; i++)
    {
        x_vector[i][0] = 1;
    }

    // X1 과 X2 TRAIN DATA
    for (int i = 0; i < 2000; i++)
    {
        for (int j = 1; j < 3; j++)
        {
            x_vector[i][j] = x_data[a];
            a++;
        }
    }

    //theta = theta - derivative of Cost Funtion
    double _x0 = 0;
    double _x1 = 0;
    double _x2 = 0;
    double x0 = 0;
    double x1 = 0;
    double x2 = 0;

    //Train x1000 
    for(int k=0; k<10000; k++){
        for (int i =0 ; i < 2000; i++){
            for (int j =0 ; j < 3; j++){
                x_param[j] = x_vector[i][j];
            }
            _x0 += ( sigmoid(theta, x_param) - y_data[b] ) * x_param[0];
            _x1 += ( sigmoid(theta, x_param) - y_data[b] ) * x_param[1];
            _x2 += ( sigmoid(theta, x_param) - y_data[b] ) * x_param[2];
            b++;
        }
        
        x0 = _x0 / 2000;
        x1 = _x1 / 2000;
        x2 = _x2 / 2000;

        theta[0] -= (lr * x0);
        theta[1] -= (lr * x1);
        theta[2] -= (lr * x2);

        b = 0;
    }

    printf("Train completed! Enter x1,and x2 features here!\n\n");
    double x1_feature = 0;
    double x2_feature = 1;
    printf("What is x1?: ");
    scanf("%lf", &x1_feature);
    printf("What is x2?: ");
    scanf("%lf", &x2_feature);
    printf("\n");
    printf("*********************************************\n\n");
    
    // printf("train with dataset by 1000times: %lf + %lf x1 + %lf x2 ", theta[0], theta[1], theta[2]);

    // 알고리즘 테스트, 최적화된 Theta0, Theta1, Theta2 값을 통해 test!
    double x_test[3] = {
        1, x1_feature, x2_feature,
    };

   double power_test = 0;

    for (int i = 0; i < 3; i++)
    {
        power_test += theta[i] * x_test[i];
    }

    //결과 출력! 
    if ( power_test < 0 ){
        printf("Lower than the decision boundary! y = 0\n\n");
    }else {
        printf("Greater than the decision boundary! y = 1\n\n");
    }
    printf("*********************************************\n");


/*
    // Test Set을 통해 결과값 출력 !
    double x_test[200][3] = {0, };
    int c = 0;

    for (int i = 0; i < 200; i++)
    {
        x_test[i][0] = 1;
    }

    for (int i = 0; i < 200; i++)
    {
        for (int j = 1; j < 3; j++)
        {
            x_test[i][j] = test_set[c];
            c++;
        }
    }

    double x_param2[3] = {0, };
    int y_result[200] = {0, };
    double power_test = 0;

    for (int i = 0; i< 200; i++){
        for (int j = 0; j<3; j++){
            x_param2[j] = x_test[i][j];
        }
        for (int k =0; k< 3; k++){
            power_test += theta[k] * x_param2[k];
        }
        if (power_test < 0){
            printf("power_test is lower than 0\n");
            y_result[i] = 0;
        }
        else{
            printf("power_test is higher than 0\n");
            y_result[i] = 1;
        }
        power_test = 0;
    }

    for(int i=0; i<200; i++){
      printf("%d,\n", y_result[i]);
    }

    return 0;
    */
}