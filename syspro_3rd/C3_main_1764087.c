#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <assert.h>
#include "A1_1764087.h"
#include "B1_1764087.h"
#include "C1_1764087.h"

//Constants
#define D2 2 //2次元配列
#define D3 3 //3次元配列
#define DATA_SIZE 6 //教師信号のサイズ
#define INPUT_NUM 2 //入力信号の数
#define X1 0 //教師信号の入力x1の値
#define X2 1 //教師信号の入力x2の値
#define Y 2  //教師信号の出力yの値

int main(void){
  //変数定義
  double learning_rate = 0; //学習率
  double **train_dataset = NULL; //訓練データセット
  double *coeff_array = NULL; //重み係数配列
  int iteration_times = 0; //繰り返し計算の回数

  train_dataset = (double **)calloc(DATA_SIZE, sizeof(double *));
  for(int i = 0; i < DATA_SIZE; i++){
    train_dataset[i] = (double *)calloc(D3, sizeof(double));
  }
  train_dataset[0][X1] = 0;
  train_dataset[0][X2] = 1;
  train_dataset[0][Y] = 0;

  train_dataset[1][X1] = 1;
  train_dataset[1][X2] = 0;
  train_dataset[1][Y] = 0;

  train_dataset[2][X1] = 0;
  train_dataset[2][X2] = 0;
  train_dataset[2][Y] = 0;

  train_dataset[3][X1] = 1;
  train_dataset[3][X2] = 3;
  train_dataset[3][Y] = 1;

  train_dataset[4][X1] = 2;
  train_dataset[4][X2] = 1;
  train_dataset[4][Y] = 1;

  train_dataset[5][X1] = 1.5;
  train_dataset[5][X2] = 2;
  train_dataset[5][Y] = 1;

  printf("**********************************************************\n");
  printf("逐次更新学習法によるニューロンモデルの重み係数決定を行います\n");
  printf("**********************************************************\n");
  printf("学習率を指定してください:");
  scanf("%lf", &learning_rate);
  printf("学習の繰り返し計算の最大回数を指定してください:");
  scanf("%d", &iteration_times);
  coeff_array = grad_inc_neuron_coeff(learning_rate, train_dataset, DATA_SIZE, INPUT_NUM, iteration_times);
  printf("学習率%lf, 最大繰り返し回数%dでの重み係数配列は以下\n", learning_rate, iteration_times);
  for(int i = 0; i < INPUT_NUM + 1; i++){
    printf("omega%d -> %lf\n", i, coeff_array[i]);
  }

  //入力信号の定義
  double input_data_1[D2] = {0, 2};
  double input_data_2[D2] = {3, 2};
  double input_data_3[D2] = {0, 0};

  printf("**********************************************************\n");
  printf("学習後のニューロンに(0,2), (3,2)の信号を与えます。\n");
  printf("(0,2)を与えた時の出力は -> %lf\n", neural_sigmoid(input_data_1, coeff_array, D2));
  printf("(3,2)を与えた時の出力は -> %lf\n", neural_sigmoid(input_data_2, coeff_array, D2));
  printf("(0,0)を与えた時の出力は -> %lf\n", neural_sigmoid(input_data_3, coeff_array, D2));

  free(coeff_array);
  free_dataset(train_dataset, DATA_SIZE);
  return 1;
}
