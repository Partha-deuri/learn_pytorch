#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define LEARNING_RATE 0.1
#define EPOCHS 1000

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

void initialize_weights(Perceptron *o, Perceptron h[4]){
     
    o->bias = randN();
    for (int i=0;i<4;i++){
        o->w[i] = randN();
    }
    for(int i=0;i<4;i++){
        h[i].bias= randN();
        for(int j=0;j<2;j++){
            h[i].w[j] = randN();
        }
    }
}

void forward_pass(Perceptron* o, Perceptron h[4],double inputs[2]){
     // forward hidden
    for(int i=0;i<4;i++){
        h[i].op = h[i].bias;
        for(int j=0;j<2;j++){
            h[i].op += inputs[j]*h[i].w[j]; 
        }
        h[i].op = sigmoid(h[i].op);
    }
    // forward output
    o->op = o->bias;
    for(int i=0;i<4;i++){
        o->op += h[i].op*o->w[i]; 
    }
    o->op = sigmoid(o->op);
}

void backward_pass(Perceptron *o, Perceptron h[4], double inputs[2] , double error, double op_grad, double hd_grad){

    op_grad = sigmoid_d(o->op) * error;
    o->bias += op_grad * LEARNING_RATE;
    for(int i=0;i<4;i++){
        o->w[i] += h[i].op * op_grad * LEARNING_RATE;
    for (int i=0;i<4;i++){
        hd_grad = op_grad * o->w[i] * sigmoid_d(h[i].op);
        h[i].bias += hd_grad * LEARNING_RATE;
        for(int j=0;j<2;j++){
            h[i].w[j] += inputs[j] * hd_grad * LEARNING_RATE;
        }
    }
}
}

int main()
{
    double inputs[4][2] = {
        {0.0, 0.0},
        {0.0, 1.0},
        {1.0, 0.0},
        {1.0, 1.0}};

    double targets[4] = {0.0, 1.0, 1.0, 0.0};
    
    double error,op_grad,hd_grad;
    int outp;

    Perceptron o,h[4];

    // initialize random weights
    initialize_weights(&o,h);



    // train
    for(int epoch = 0;epoch<EPOCHS;epoch++){

        for (int k =0;k<4;k++){
            // forward pass
            forward_pass(&o,h,inputs[k]);

            // error calculations
            error = (targets[k] - o.op) ;

            // backward pass
            backward_pass(&o,h,inputs[k],error,op_grad,hd_grad);  
        }
    }




    // test
    for (int k=0;k<4;k++){
        // forward
        forward_pass(&o,h,inputs[k]);
        outp = o.op>0.5?1:0;
        printf("Input: [%f, %f] Output: %f ~ %d\n", inputs[k][0], inputs[k][1], o.op, outp);
    }


    return 0;
}
