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
#define DATA_SIZE 5 //訓練データのサイズ
#define X 0 //データセットのxの値
#define Y 1 //データセットのyの値

//Prototype

int main(void){
  //変数定義
  //2次関数の最大値特定に必要な変数
  double learning_rate = 0; //学習率
  double max_x = 0; //勾配法により求めた2次関数の最大値のx
  double max_y = 0; //勾配法により求めた2次関数の最大値のy

  //線形システムのパラメータ特定に必要な変数
  double **train_dataset = NULL; //訓練データセット
  int iteration_times = 0; //繰り返し計算の回数
  double coeff = 0; //線形システムのパラメータ

  train_dataset = (double **)calloc(DATA_SIZE, sizeof(double *));
  for(int i = 0; i < DATA_SIZE; i++){
    train_dataset[i] = (double *)calloc(D2, sizeof(double));
  }
  train_dataset[0][X] = 1;
  train_dataset[0][Y] = 1;

  train_dataset[1][X] = 2;
  train_dataset[1][Y] = 2.5;

  train_dataset[2][X] = 3;
  train_dataset[2][Y] = 2.5;

  train_dataset[3][X] = 4;
  train_dataset[3][Y] = 4.5;

  train_dataset[4][X] = 5;
  train_dataset[4][Y] = 4.5;

  printf("**********************************************************\n");
  printf("2次関数-2x^2 + 5x + 2の最大点を勾配法を用いて求めます\n");
  printf("学習率を指定してください:");
  scanf("%lf", &learning_rate);
  max_x = grad_quad_func(learning_rate);
  max_y = -2 * max_x * max_x + 5 * max_x + 2;
  printf("学習率%lf -> xは%lf, yは%lf\n", learning_rate, max_x, max_y);

  printf("**********************************************************\n");
  printf("一括更新学習法による線形システムの係数決定を行います\n");
  printf("**********************************************************\n");
  /*printf("訓練データセットの作成を行います");
  train_dataset = gen_multidim_dataset(DATA_SIZE, D2);*/
  printf("学習率を指定してください:");
  scanf("%lf", &learning_rate);
  printf("学習の繰り返し計算の最大回数を指定してください:");
  scanf("%d", &iteration_times);
  coeff = grad_bulk_linear_sys(learning_rate, train_dataset, DATA_SIZE, iteration_times);
  printf("学習率%lf, 最大繰り返し回数%d -> パラメータaは%lf\n", learning_rate, iteration_times, coeff);

  printf("**********************************************************\n");
  printf("逐次更新学習法による線形システムの係数決定を行います\n");
  printf("**********************************************************\n");
  /*printf("訓練データセットの作成を行います");
  train_dataset = gen_multidim_dataset(DATA_SIZE, D2);*/
  printf("学習率を指定してください:");
  scanf("%lf", &learning_rate);
  printf("学習の繰り返し計算の最大回数を指定してください:");
  scanf("%d", &iteration_times);
  coeff = grad_inc_linear_sys(learning_rate, train_dataset, DATA_SIZE, iteration_times);
  printf("学習率%lf, 逐次最大繰り返し回数%d -> パラメータaは%lf\n", learning_rate, iteration_times, coeff);

  free_dataset(train_dataset, DATA_SIZE);
  return 1;
}
