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
#define THRESHOLD_INPUT 1 //閾値の入力値
#define THRESHOLD_INDEX 0 //閾値の重み係数の要素番号

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

//勾配法を用いた逐次更新学習法によるニューロンの学習
double *grad_inc_neuron_coeff(double learning_rate, double **data_set, int data_size, int data_input_num ,int iteration_num){
  //初期化
  int offset_data_input_num = data_input_num + 1; //閾値を表す重みに対応する入力値を加える。
  double sum = 0; //総和の計算に必要な変数
  double sigmoid = 0; //シグモイド関数の値
  double error_grad = 0; //2乗誤差の勾配
  double error_sqsum = 0; //誤差の二乗平均

  double **offset_data_set = NULL; //閾値入力を含めたデータセット
  double *coeff_array = NULL; //重み係数数列

  offset_data_set = (double **)calloc(data_size, sizeof(double *));
  for(int i = 0; i < data_size; i++){ //閾値入力を含めたデータセットの作成
    offset_data_set[i] = copy_array(data_set[i], offset_data_set[i], data_input_num + 1);
    offset_data_set[i] = change_array_size(offset_data_set[i], offset_data_input_num + 1);
    for(int j = offset_data_input_num - 1; j > 0; j--){ //配列の右シフト
      offset_data_set[i][j] = offset_data_set[i][j - 1];
    }
    offset_data_set[i][0] = THRESHOLD_INPUT;
  }

  coeff_array = (double *)calloc(offset_data_input_num, sizeof(double));
  coeff_array = random_array_intialize(coeff_array, offset_data_input_num);

  //計算回数の制限
  for(int i_calc = 0; i_calc < iteration_num; i_calc++){

    //逐次更新学習
    for(int i = 0; i < data_size; i++){
      error_grad = 0;
      sigmoid = 0;
      sum = 0;

      //シグモイド関数の引数の計算
      for(int j = 0; j < offset_data_input_num; j++){
        sum += coeff_array[j] * data_set[i][j];
      }

      //誤差勾配の計算
      sigmoid = 1 / (1 + exp(-1 * sum));
      error_grad = -2 * (data_set[i][data_input_num] - sigmoid) * (sigmoid) * (1 - sigmoid);

      //重み係数の修正
      for(int j = 0; j < offset_data_input_num; j++){
        double part_grad = error_grad * data_set[i][j];//偏微分係数の計算
        coeff_array[j] -= learning_rate * part_grad;
      }
    }

    //収束の確認
    error_sqsum = 0;

    //二乗平均誤差の計算
    for(int i = 0; i < data_size; i++){
      sigmoid = 0;
      sum = 0;

      //シグモイド関数の引数の計算
      for(int j = 0; j < offset_data_input_num; j++){
        sum += coeff_array[j] * offset_data_set[i][j];
      }
      sigmoid = 1 / (1 + exp(-1 * sum));
      error_sqsum += pow(offset_data_set[i][offset_data_input_num] - sigmoid, 2);
    }
    error_sqsum /= data_size;

    //誤差の評価
    if(error_sqsum < pow(10, -6)){
      printf("計算回数%dで誤差が小さくなったため収束としました\n", i_calc);
      free_dataset(offset_data_set, offset_data_input_num + 1);
      return coeff_array;
    }
  }
  printf("計算回数%dとなったため収束としました\n", iteration_num);
  free_dataset(offset_data_set, offset_data_input_num + 1);
  return coeff_array;
}

//ニューロンモデルの重み係数配列を用いた計算
double neural_sigmoid(double *input_signal, double *coeff_array, double input_num){
  double sum = 0; //シグモイド計算のための合計値変数の定義
  double output = 0; //出力値変数

  sum += coeff_array[0]; //閾値の加算
  for(int i = 0; i < input_num; i++){
    sum += coeff_array[i + 1] * input_signal[i];
  }
  output = 1 / (1 + exp(-1 * sum));
  return output;
}


//2.データセットの作成
//多次元データセットの作成
double **gen_multidim_dataset(int array_size, int dimention){

  double **data_set = NULL;
  data_set = (double **)calloc(array_size, sizeof(double *));
  for(int i = 0; i < array_size; i++){
    data_set[i] = (double *)calloc(dimention, sizeof(double));
    printf("**********************************************************\n");
    for(int j = 0; j < dimention; j++){
      printf("%dつめのデータでの%d番目のデータ要素を指定してください:", i + 1, j + 1);
      scanf("%lf", &data_set[i][j]);
    }
  }
  return data_set;
}

//多次元データセットのメモリ解放
void free_dataset(double **data_set, int array_size){
  assert(array_size > 0);
  for(int i = 0; i < array_size; i++){
    free(data_set[i]);
  }
  free(data_set);
}
