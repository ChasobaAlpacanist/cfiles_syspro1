#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <assert.h>
#include "A1_1764087.h"
#include "B1_1764087.h"
#include "C1_1764087.h"

//Constant
#define MAX_ITERATION 1000 //繰り返し回数の上限
#define X 0 //データセットのxの値
#define Y 1 //データセットのyの値
#define D2 2 //2次元配列を表す

//functions

//1.勾配法による学習計算

//勾配法による2次関数-2x^2+5x+2の最大値を求める関数
double grad_quad_func(double learning_rate){
  double obj_value = 0;
  srand((unsigned)time(NULL));

  obj_value = rand() % 20001; //0 ~ 20000までの乱数を計算
  obj_value = (obj_value / 10000) - 1.0; //-1.0から1.0までの乱数
  double init_grad = (-2 * obj_value + 5); //初期値の勾配

  for(int i = 0; i < MAX_ITERATION; i++){
    double grad = (-4 * obj_value + 5); //2次関数-2x^2の勾配の計算
    obj_value += learning_rate * grad;
    if(fabs(grad) < pow(10, -6)){ //微分係数の絶対値が10e-6より小さい時
      printf("学習回数%dで勾配が小さくなったため収束としました\n", i + 1);
      return obj_value;
    }
    if((init_grad > 0 && grad < 0) || (init_grad < 0 && grad > 0)){ //初期値と現在の勾配が異符号
      printf("学習回数%dで勾配の正負が入れ替わったため収束としました\n", i + 1);
      return obj_value;
    }
  }
  printf("学習回数%dで繰り返し限界のため収束としました\n", MAX_ITERATION);
  return obj_value;
}

//勾配法を用いた一括更新学習法による線形システムの学習
double grad_bulk_linear_sys(double learning_rate, double **data_set, int array_size, int iteration_num){
  assert(learning_rate > 0);
  double linear_coeff = 0;
  srand((unsigned)time(NULL));

  linear_coeff = rand() % 20001; //0 ~ 20000までの乱数を計算
  linear_coeff = (linear_coeff / 10000) - 1; //-1.0から1.0までの乱数
  double grad = 0;

  for(int i = 0; i < iteration_num; i++){
    grad = 0;

    for(int j = 0; j < array_size; j++){ //二乗誤差の和の勾配の計算
      grad += (-2) * (data_set[j][Y] - linear_coeff * data_set[j][X]) * data_set[j][X];
    }
    linear_coeff -= learning_rate * grad;

    //収束確認
    if(fabs(grad) < pow(10, -6)){ //微分係数の絶対値が10e-6より小さい時
      printf("学習回数%dで勾配が小さくなったため収束としました\n", i + 1);
      printf("最終grad -> %lf\n", grad);
      return linear_coeff;
    }
  }
  //繰り返し回数が規定値を超えた時
  printf("学習回数%dで繰り返し限界のため収束としました\n", iteration_num);
  printf("最終grad -> %lf\n", grad);
  return linear_coeff;
}

//勾配法を用いた逐次更新学習法による線形システムの学習
double grad_inc_linear_sys(double learning_rate, double **data_set, int array_size, int iteration_num){
  assert(learning_rate > 0);
  double linear_coeff = 0;
  srand((unsigned)time(NULL));

  linear_coeff = rand() % 20001; //0 ~ 20000までの乱数を計算
  linear_coeff = (linear_coeff / 10000) - 1; //-1.0から1.0までの乱数
  double grad = 0;
  int counter = 0; //合計計算回数を数える変数

  for(int i = 0; i < array_size; i++){
    for(int j = 0; j < iteration_num; j++){
      grad = 0;

      for(int k = 0; k < i + 1; k++){ //二乗誤差の和の勾配の計算
        grad += (-2) * (data_set[k][Y] - linear_coeff * data_set[k][X]) * data_set[k][X];
      }
      linear_coeff -= learning_rate * grad;
      if(fabs(grad) < pow(10, -6)){
        counter += j;
        break;
      }

      if(j == iteration_num - 1){
        counter += iteration_num;
      }
    }
  }
  printf("合計学習回数%dで収束しました\n", counter);
  return linear_coeff;
}

//2.データセットの作成
//多次元データセットの作成
double **gen_multidim_detaset(int array_size, int dimention){

  double **deta_set = NULL;
  deta_set = (double **)calloc(array_size, sizeof(double *));
  for(int i = 0; i < array_size; i++){
    deta_set[i] = (double *)calloc(dimention, sizeof(double));
    printf("**********************************************************\n");
    for(int j = 0; j < dimention; j++){
      printf("%dつめのデータでの%d番目のデータ要素を指定してください:", i + 1, j + 1);
      scanf("%lf", &deta_set[i][j]);
    }
  }
  return deta_set;
}

//多次元データセットのメモリ解放
void free_detaset(double **deta_set, int array_size){
  assert(array_size > 0);
  for(int i = 0; i < array_size; i++){
    free(deta_set[i]);
  }
  free(deta_set);
}
