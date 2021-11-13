#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "TrainSet.h"

double* ForwardingPropagte (){}

int main (void) {
    
    int n = (sizeof(trainSet) / sizeof(double));
    int x_data_size = n / 2;
    int y_data_size = n / 2;
    int j = 0;
    int k = 0;
    int biasUnit = 1;
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

    double inputNode[2] = {1 , 0};

    double weightVal_0[3][2] = {
        0,
    };

    double line_1[4] = {
        0,
    };

    double weightVal_1[3][4] = {
        0,
    };

    double line_2[4] = {
        0,
    };

    double weightVal_2[2][4] = {
        0,
    };

    /* bias node and bias weight */
    inputNode[0] = 1;
    line_1[0] = 1;
    line_2[0] = 1;

    for(int i=0; i<3; i++){
        weightVal_0[i][0] = 1;
        weightVal_1[i][0] = 1;
        weightVal_2[j][0] = 1;
        j++;
        if(j >= 3)j = 0;
    }

}