#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define LEARNING_RATE 0.1
#define EPOCHS 50000

typedef struct
{
    double bias;
    double w[4];
    double op;
} Perceptron;

double randN(){
    int N = 1000;
    double value = rand() % (N + 1);
    value = value / N * 2 -1;
    return value;
}

double sigmoid(double x)
{
    return (1 / (1 + exp(-x)));
}
double sigmoid_d(double x)
{
    return x * (1 - x);
}

int main()
{
    double inputs[4][2] = {
        {0.0, 0.0},
        {0.0, 1.0},
        {1.0, 0.0},
        {1.0, 1.0}};

    double targets[4] = {0.0, 0.0, 0.0, 1.0};
    
    Perceptron o,h[4];

    // double h_output[4];
    double output,error,op_grad,hd_grad;

    // initialize random weights
    o.bias = randN();
    for (int i=0;i<4;i++){
        o.w[i] = randN();
    }
    for(int i=0;i<4;i++){
        h[i].bias= randN();
        for(int j=0;j<2;j++){
            h[i].w[j] = randN();
        }
    }

    // train

    for(int epoch = 0;epoch<EPOCHS;epoch++){
        
        if(epoch%1000==0){
            printf("epoch %d\n",epoch);
        }
        for (int k =0;k<4;k++){
            
            // forward hidden
            for(int i=0;i<4;i++){
                h[i].op = h[i].bias;
                for(int j=0;j<2;j++){
                    h[i].op += inputs[k][j]*h[i].w[j]; 
                }
                h[i].op = sigmoid(h[i].op);
            }
            // forward output
            o.op = o.bias;
            for(int i=0;i<4;i++){
                o.op += h[i].op*o.w[i]; 
            }
            o.op = sigmoid(o.op);

            
            error = 0.5* ((targets[k]*targets[k]) - (o.op * o.op));

            // backward pass
            op_grad = sigmoid_d(o.op) * error;
            o.bias += op_grad * LEARNING_RATE;
            for(int i=0;i<4;i++){
                o.w[i] += h[i].op * op_grad * LEARNING_RATE;
            }

            for (int i=0;i<4;i++){
                hd_grad = op_grad * o.w[i] * sigmoid_d(h[i].op);
                h[i].bias += hd_grad * LEARNING_RATE;
                for(int j=0;j<2;j++){
                    h[i].w[j] += inputs[k][j] * hd_grad * LEARNING_RATE;
                }
            }
            
        if(epoch%1000==0){
            printf("Input: [%f, %f] Output: %f\n", inputs[k][0], inputs[k][1], o.op);
        }
        }
        if(epoch%1000==0){
            printf("\n\n\n");
        }
    }



    int outp;
    // test
    for (int k=0;k<4;k++){
        // forward
            // forward hidden
            for(int i=0;i<4;i++){
                h[i].op = h[i].bias;
                for(int j=0;j<2;j++){
                    h[i].op += inputs[k][j]*h[i].w[j]; 
                }
                h[i].op = sigmoid(h[i].op);
            }
            // forward output
            o.op = o.bias;
            for(int i=0;i<4;i++){
                o.op += h[i].op*o.w[i]; 
            }
            o.op = sigmoid(o.op);
            outp = o.op>0.5?1:0;
            printf("Input: [%f, %f] Output: %f ~ %d\n", inputs[k][0], inputs[k][1], o.op, outp);
    }

    return 0;
}
