#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <assert.h>
#include "A1_1764087.h"
#include "B1_1764087.h"


/******************1.勾配法による学習計算******************/
/*
  @brief 勾配法による2次関数-2x^2+5x+2の最大値を求める関数

  学習率を用いて関数の最大点を求める関数
  @param [in] learning_rate(double) 学習率
  @param [out] obj_value(double) 最大点でのx座標
  @return (double) 勾配法により求められた最大値のx座標を返す。
  @attention 収束条件は勾配法の繰り返し回数が1000回を超える
             または、勾配の大きさgが g < 10e-6を下回った時
             または、勾配の符号が初期値での勾配の符号と異なった時とする。
             obj_valueの初期値は-1~1の乱数とする
             学習率は正数
  @per 更新履歴
    - 2019/05/29
      基本的な機能の実装(by 1764087 木村慶豪)
*/
double grad_quad_func(double learning_rate);

/*
  @brief 勾配法を用いた一括更新学習法による線形システムの学習

  全ての学習データを一度に受け取り、それぞれに対する目標の線形システムとの二乗誤差を測定、和を求めて勾配を求める。
  得られた勾配を用いて勾配法によりデータセットにもっとも適した線形係数を求める関数
  @param [in] learning_rate(double) 学習率
  @param [in] data_set(double **) データセット
  @param [in] array_size(int) データセットの総数
  @param [in] iteration_num(int) 学習の繰り返し回数
  @param [out] linear_coeff(double) 目標の線形システムの係数
  @return (double) 一括更新勾配法による線形システムの係数を返す
  @attention 収束条件は勾配法の繰り返し回数がiteration_numを超える
             または勾配の大きさgがg < 10e-6を下回った時とする
             linear_coeffの初期値は-1~1の範囲とする
             学習率は正数
  @per 更新履歴
    - 2019/05/29
      基本的な機能の実装(by 1764087 木村慶豪)
*/
double grad_bulk_linear_sys(double learning_rate, double **data_set, int array_size, int iteration_num);

/*
  @brief 勾配法を用いた逐次更新学習法による線形システムの学習

  学習データを受け取り、学習データごとに目標の線形システムとの二乗誤差を測定し、勾配を求める。
  得られた勾配から勾配法によりもっとも適した線形システムの係数を求め、データの入力ごとに更新を繰り返す関数
  @param [in] learning_rate(double) 学習率
  @param [in] data_set(double **) データセット
  @param [in] array_size(int) データセットの総数
  @param [in] iteration_num(int) 学習の繰り返し回数
  @param [out] linear_coeff(double) 目標の線形システムの係数
  @return (double) 逐次更新勾配法により求めた線形システムの係数を返す
  @attention 収束条件は勾配法の繰り返し回数がiteration_numを超える
             または勾配の大きさgがg < 10e-6を下回った時とする
             linear_coeffの初期値は-1~1の範囲とする
             学習率は正数
  @per 更新履歴
    - 2019/05/29
      基本的な機能の実装(by 1764087 木村慶豪)

*/
double grad_inc_linear_sys(double learning_rate, double **data_set, int array_size, int iteration_num);

/*
  @brief 勾配法を用いた逐次更新学習法によるニューロンの学習

  教師信号を受け取り、教師信号ごとに目標のニューロンとの二乗誤差を測定する。
  その後、各入力の重みごとに偏微分を行い勾配を得る。
  得られた勾配から勾配法により入力の重み求め、データの入力ごとに更新を繰り返す関数
  @param [in] learning_rate(double) 学習率
  @param [in] data_set(double **) データセット
  @param [in] data_size(int) データセットの総数
  @param [in] data_input_num(int) データの入力数
  @param [in] iteration_num(int) 学習の繰り返し回数
  @param [out] coeff_array(double *) 目標のニューロンの重み配列
  @return (double) 逐次更新勾配法により求めたニューロンの重み配列を返す
  @attention 収束条件は勾配法の繰り返し回数がiteration_numを超える
             または誤差の大きさの二乗平均error_sqsumが10e-6を下回った時とする。

             coeff_arrayの各要素の初期値は-1~1の範囲とする
             学習率は正数
             data_sizeはデータセットの1次要素数に等しい
             data_input_numはデータセットの2次要素数から1引いた値に等しい

  @per 更新履歴
    - 2019/06/04
      基本的な機能の実装(by 1764087 木村慶豪)

*/
double *grad_inc_neuron_coeff(double learning_rate, double **data_set, int data_size, int data_input_num ,int iteration_num);

/*
  @brief ニューロンモデルの重み係数配列を用いた計算
  任意の入力から重み係数配列を用いてニューロンモデルの計算を行う
  @param [in] input_signal(double *) 入力信号
  @param [in] coeff_array(double *)  ニューロンモデルの重み係数配列
  @param [in] input_num(int) 入力信号の数
  @param [out] output(double) 出力信号
  @return (double) 入力信号および重み係数配列から計算したシグモイド関数の結果を返す
  @attention input_numはinput_signalの配列サイズと等しく、coeff_arrayの配列サイズより1小さい。

  @per 更新履歴
    - 2019/06/05
       基本的な機能の実装(by 1764087 木村慶豪)

*/
double neural_sigmoid(double *input_signal, double *coeff_array, double input_num);

/******************2.データセットの作成******************/
/*
  @brief 多次元データセットの作成

  データセットの大きさを指定し、double型の多次元配列を作成し、入力する関数
  @param [in] array_size(int) データセットの大きさ
  @param [in] dimention(int) 次元の大きさ
  @param [out] data_set(double **) 出力するデータセット
  @return (double **) ユーザによって入力された多次元データセットを出力する。
  @attention array_sizeは正数,dimentionも正数
  @per 更新履歴
    - 2019/05/29
      基本的な機能の実装(by 1764087 木村慶豪)
    - 2019/06/02
      表記揺れの統一(by 1764087 木村慶豪)
*/
double **gen_multidim_dataset(int array_size, int dimention);

/*
  @brief 多次元データセットのメモリ解放

  多次元データセットで使用したメモリを全て解放する関数
  @param [in] data_set(double **) メモリ解法するデータセット
  @param [in] array_size(int) データセットの大きさ
  @param [out] void
  @return (void)
  @attention array_sizeは正数でデータセットのサイズと等しくなければならない。
  @per 更新履歴
    - 2019/05/29
      基本的な機能の実装(by 1764087 木村慶豪)
    - 2019/06/02
      表記揺れの統一(by 1764087 木村慶豪)
*/
void free_dataset(double **data_set, int array_size);
