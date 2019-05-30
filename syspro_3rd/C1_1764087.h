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
    - 2018/05/29
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
    - 2018/05/29
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
    - 2018/05/29
      基本的な機能の実装(by 1764087 木村慶豪)

*/
double grad_inc_linear_sys(double learning_rate, double **data_set, int array_size, int iteration_num);

/******************2.データセットの作成******************/
/*
  @brief 多次元データセットの作成

  データセットの大きさを指定し、double型の多次元配列を作成し、入力する関数
  @param [in] array_size(int) データセットの大きさ
  @param [in] dimention(int) 次元の大きさ
  @param [out] **deta_set(double) 出力するデータセット
  @return (double **) ユーザによって入力された多次元データセットを出力する。
  @attention array_sizeは正数,dimentionも正数
  @per 更新履歴
    - 2018/05/29
      基本的な機能の実装(by 1764087 木村慶豪)
*/
double **gen_multidim_detaset(int array_size, int dimention);

/*
  @brief 多次元データセットのメモリ解放

  多次元データセットで使用したメモリを全て解放する関数
  @param [in] **deta_set(double) メモリ解法するデータセット
  @param [in] array_size(int) データセットの大きさ
  @param [out] void
  @return (void)。
  @attention array_sizeは正数でデータセットのサイズと等しくなければならない。
  @per 更新履歴
    - 2018/05/29
      基本的な機能の実装(by 1764087 木村慶豪)
*/
void free_detaset(double **deta_set, int array_size);
