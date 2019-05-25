#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <complex.h>
#include "A1_1764087.h"

/********************1. 信号作成**********************/

/*
  @brief 信号を作成する関数

  入力から振幅、周波数、サンプリング数、サンプリング時間およびオフセットをつけた1周期分の正弦波信号を作成する
  @param [in] amp(double) 正弦波の振幅
  @param [in] fre(double) 正弦波の周波数
  @param [in] sampling_num(int) サンプリング数
  @param [in] sampling_rate(double) サンプリング周波数
  @param [in] issin(bool) sinの信号を取り出すか
  @param [in] value_offset(double) 正弦波の縦方向オフセット
  @param [out] *signal_array(double) 生成した数列を格納する
  @return (double *) 入力に対する正弦波や定常信号を返す。
  @attention ampが0であれば信号はv_offset定常信号となる。
             amp >= 0
             iscosがtrue -> cos信号
             false -> sin信号

  @per 更新履歴
    - 2018/05/22
      基本的な機能の実装(by 1764087 木村慶豪)
*/
 double *gen_signal(double amp, double fre, int data_num, double sampling_rate, bool issin, double value_offset);

 /*
   @brief 信号を作成する関数

   入力から振幅、周波数、サンプリング数、サンプリング時間をつけた矩形波信号を作成する
   @param [in] amp(double) 矩形波の振幅
   @param [in] fre(double) 矩形波の周波数
   @param [in] data_num(int) データ数
   @param [in] sampling_rate(double) サンプリング周波数
   @param [out] *signal_array(double) 生成した数列を格納する
   @return (double *) 入力に対する矩形波信号を返す。
   @attention サンプリングした時間に周波数をかけた値のsinが正の時、正の振幅を返す。
              負の時に負の振幅を返す。
              0の時に0を返す。

   @per 更新履歴
     - 2018/05/22
       基本的な機能の実装(by 1764087 木村慶豪)
 */
 double *gen_square_signal(double amp, double fre, int data_num, double sampling_rate);


 /********************2. 信号処理**********************/
 /*
   @brief 信号をサンプリングする関数

   信号から指定の数だけ値をサンプリングする
   @param [in] *input_signal(double) 入力信号の配列
   @param [in] signal_size(int) 入力信号配列のサイズ
   @param [in] sampling_num(int) サンプリング数
   @param [out] *sample_data(double) サンプリングした値を格納する配列
   @return (double *) 入力信号をサンプリングしたものの配列を返す
   @attention sampling_numはsignal_sizeより小さくなければならない。
              sampling_numを小さい値にすると正しくサンプリングできない
              sampling_num / サンプル秒 * 2 > 2 * M_PI * 原信号周波数を確認

   @per 更新履歴
     - 2018/05/22
       基本的な機能の実装(by 1764087 木村慶豪)
 */
 double *sampling_signal(double *input_signal, int signal_size, int sampling_num);

 /*
   @brief 信号を離散フーリエ変換する関数

   信号をサンプリングし、サンプリングしたデータを元に離散フーリエ変換を行い、複素周波数列を作成する
   @param [in] *input_signal(double) 入力信号の配列
   @param [in] signal_size(int) 入力信号配列のサイズ
   @param [in] sampling_num(int) サンプリング数
   @param [out] *ft_array(double complex) フーリエ変換された値を格納する配列
   @return (double complex *) 入力信号をフーリエ変換した複素周波数の配列を返す
   @attention sample_numはsignal_sizeより小さくなければならない。

   @per 更新履歴
     - 2018/05/23
       基本的な機能の実装(by 1764087 木村慶豪)
 */
 double complex *dft_signal(double *input_signal, int signal_size, int sampling_num);

 /*
   @brief 複素周波数列を離散フーリエ逆変換する関数

   複素周波数列をフーリエ逆変換し、時間信号を復元する
   @param [in] *ft_array(double complex) 複素周波数列が格納された配列
   @param [in] array_size(int) 複素周波数列配列のサイズ
   @param [in] plot_num(int) 時間信号の数
   @param [in] plot_step(double) 時間信号の間隔
   @param [out] *signal_data(double) フーリエ逆変換された時間信号を格納する配列
   @return (double *) 入力信号をフーリエ逆変換した時間信号の配列を返す
   @attention プロット数はフーリエ変換したサンプリング数と同じにする

   @per 更新履歴
     - 2018/05/23
      　要修正
       基本的な機能の実装(by 1764087 木村慶豪)
 */
 double *inverse_dft_signal(double complex *ft_array, int array_size, int plot_num, double plot_step);

 /*
   @brief 信号のパワースペクトルを求める関数

   信号をサンプリングし、サンプリングしたデータを元に離散フーリエ変換を行い、
   複素周波数列からパワースペクトル列を作成する。
   @param [in] *input_signal(double) 入力信号の配列
   @param [in] signal_size(int) 入力信号配列のサイズ
   @param [in] sample_num(int) サンプリングの際のサンプリング数
   @param [out] *power_spectrum(double) パワースペクトルを格納する配列
   @return (double *) 入力信号のパワースペクトルを格納した配列を返す
   @attention sample_numはsignal_sizeより小さくなければならない。

   @per 更新履歴
     - 2018/05/23
       基本的な機能の実装(by 1764087 木村慶豪)
 */
 double *p_s_signal(double *input_signal, int signal_size, int sampling_num);

 /********************3. 信号出力**********************/
 /*
   @brief ファイルへのデータ出力

   //信号(複素周波数列)を時間(周波数)と信号(パワー)の形式でファイルに出力する関数
   @param [in] *num_array(double) データを出力する配列
   @param [in] array_size(int) 配列サイズ
   @param [in][out] export_file(FILE *) 配列データを出力するためのファイル
   @return FILE 出力されたファイルのポインタを返す。
   @attention
   @per 更新履歴　array_sizeはnum_arrayのサイズと等しくなければならない。
                export_fileは書き込み状態で開いている必要がある。
     - 2018/05/15
       基本的な機能の実装(by 1764087 木村慶豪)
 */
 FILE *export_signal(double *num_array, int array_size, FILE *export_file);

 /*
   @brief ファイルへのデータ出力

   //信号(複素周波数列)を時間(周波数)と信号(パワー)の形式でファイルに出力する関数
   @param [in] *num_array(double) データを出力する配列
   @param [in] array_size(int) 配列サイズ
   @param [in][out] export_file(FILE *) 配列データを出力するためのファイル
   @return FILE 出力されたファイルのポインタを返す。
   @attention
   @per 更新履歴　array_sizeはnum_arrayのサイズと等しくなければならない。
                export_fileは書き込み状態で開いている必要がある。
     - 2018/05/15
       基本的な機能の実装(by 1764087 木村慶豪)
 */
 FILE *export_complex_signal(double complex *num_array, int array_size, FILE *export_file);
