#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>
#include <complex.h>
#include "A1_1764087.h"
#include "B1_1764087.h"

//Constant
#define NO_OFFSET 0 //オフセットなしを表す
#define BUFFER_SIZE 256 //行を読むときのバッファサイズ
#define UNIT_STEP 1 //単位ステップ間隔

//Prototype
double *signal_gen(double *signal_array, int data_num);

int main(void){
  double *raw_signal = NULL; //原信号
  int data_num; //原信号のデータ数
  double complex *ft_array;

  //フーリエ変換用変数
  double complex *dft_array = NULL;
  int dft_num = 0; //DFTの点数

  //フーリエ逆変換用変数
  double *inv_dft_array = NULL;

  //パワースペクトル変換用変数
  double *p_s_array = NULL;

  //ファイル出力用変数
  FILE *fp = NULL;
  char file_name[BUFFER_SIZE] = {};

  printf("**********************************************************\n");
  printf("原信号を入力します\n");
  printf("原信号のデータ数を指定してください(正の数):");
  scanf("%d", &data_num);
  assert(data_num > 0);

  raw_signal = signal_gen(raw_signal, data_num);

  printf("**********************************************************\n");
  printf("入力したデータをcsvで出力します\n");
  printf("エクスポートするファイル名を選択\n");
  scanf("%s", file_name);

  fp = fopen(file_name, "w");
  fp = export_signal(raw_signal, data_num, fp);
  fclose(fp);

  printf("**********************************************************\n");
  printf("入力した信号の離散フーリエ変換を行います。\n");
  printf("DFTの点数を指定してください:");
  scanf("%d", &dft_num);

  dft_array = dft_signal(raw_signal, data_num, dft_num);
  printf("**********************************************************\n");
  printf("フーリエ変換が終了しました\n");
  printf("変換データを出力します\n");
  printf("エクスポートするファイル名を選択\n");
  scanf("%s", file_name);

  fp = fopen(file_name, "w");
  fp = export_complex_signal(dft_array, dft_num, fp);
  fclose(fp);
  printf("出力が終了しました\n");

  printf("**********************************************************\n");
  printf("フーリエ変換した複素周波数列の離散フーリエ逆変換を行います。\n");

  inv_dft_array = inverse_dft_signal(dft_array, dft_num, dft_num, UNIT_STEP);
  printf("**********************************************************\n");
  printf("フーリエ逆変換が終了しました\n");
  printf("変換データを出力します\n");
  printf("エクスポートするファイル名を選択\n");
  scanf("%s", file_name);

  fp = fopen(file_name, "w");
  fp = export_signal(inv_dft_array, dft_num, fp);
  fclose(fp);
  printf("出力が終了しました\n");

  printf("**********************************************************\n");
  printf("入力した信号のパワースペクトルの測定を行います。\n");

  p_s_array = p_s_signal(raw_signal, data_num, dft_num);
  printf("**********************************************************\n");
  printf("パワースペクトル変換が終了しました\n");
  printf("変換データを出力します\n");
  printf("エクスポートするファイル名を選択\n");
  scanf("%s", file_name);

  fp = fopen(file_name, "w");
  fp = export_signal(p_s_array, dft_num, fp);
  fclose(fp);
  printf("出力が終了しました\n");

  free(raw_signal);
  free(dft_array);
  free(inv_dft_array);
  free(p_s_array);

  return 1;
}

double *signal_gen(double *signal_array, int data_num){
  //波形の定数の定義
  double a_amp = 0; //1の波の振幅
  double a_fre = 0; //1の波の周波数
  double b_amp = 0; //2の波の振幅
  double b_fre = 0; //2の波の周波数
  double offset = 0; //信号のオフセット

  //合成前の信号を入れる配列の定義
  double *signal_1 = NULL;
  double *signal_2 = NULL;

  //サンプル定数の定義
  double sampling_rate = 0; //サンプリング周波数

  int operation_case = 0; //switch分岐のための変数

  printf("**********************************************************\n");
  printf("信号の作成を行います\n");
  printf("現在格納されている波形データは失われます\n");
  printf("作成する波形を選択してください\n");
  printf("[1]単一正弦波\n");
  printf("[2]オフセットなし合成波\n");
  printf("[3]オフセット付き合成波\n");
  printf("[4]矩形波\n");
  printf("[0]戻る\n:");
  scanf("%d", &operation_case);
  assert(operation_case == 1 || operation_case == 2 || operation_case == 3 ||
         operation_case == 4 || operation_case == 0);

  switch(operation_case){
    case 1:
      free(signal_array); //残っている信号配列の消去

      printf("**********************************************************\n");
      printf("単一正弦波の作成を行います\n");
      printf("振幅(a)を入力(正の値):");
      scanf("%lf", &a_amp);
      assert(a_amp > 0);

      printf("周波数(α)を入力:");
      scanf("%lf", &a_fre);

      /*printf("サンプリング回数を入力(正の値):");
      scanf("%d", &sampling_num);
      assert(sampling_num > 0);*/

      printf("サンプリング周波数を入力(正の値):");
      scanf("%lf", &sampling_rate);
      assert(sampling_rate > 0);
      signal_array = gen_signal(a_amp, a_fre, data_num, sampling_rate, true, NO_OFFSET);
      break;

    case 2:
      free(signal_array); //残っている信号配列の消去

      printf("**********************************************************\n");
      printf("オフセットなし合成波の作成を行います\n");
      printf("1つめの波の振幅(a)を入力(正の値):");
      scanf("%lf", &a_amp);
      assert(a_amp > 0);

      printf("1つめの波の周波数(α)を入力:");
      scanf("%lf", &a_fre);

      printf("2つめの波の振幅(b)を入力(正の値):");
      scanf("%lf", &b_amp);
      assert(b_amp > 0);

      printf("2つめの波の周波数(β)を入力:");
      scanf("%lf", &b_fre);

      printf("サンプリング周波数を入力(正の値):");
      scanf("%lf", &sampling_rate);
      assert(sampling_rate > 0);

      signal_1 = gen_signal(a_amp, a_fre, data_num, sampling_rate, true, NO_OFFSET);
      signal_2 = gen_signal(b_amp, b_fre, data_num, sampling_rate, false, NO_OFFSET);
      signal_array = sum_arrays(signal_1, signal_2, data_num, signal_array);
      break;

    case 3:
      free(signal_array); //残っている信号配列の消去

      printf("**********************************************************\n");
      printf("オフセット付き合成波の作成を行います\n");
      printf("1つめの波の振幅(a)を入力(正の値):");
      scanf("%lf", &a_amp);
      assert(a_amp > 0);

      printf("1つめの波の周波数(α)を入力:");
      scanf("%lf", &a_fre);

      printf("2つめの波の振幅(b)を入力(正の値):");
      scanf("%lf", &b_amp);
      assert(b_amp > 0);

      printf("2つめの波の周波数(β)を入力:");
      scanf("%lf", &b_fre);

      printf("オフセット(c)を入力:");
      scanf("%lf", &offset);

      /*printf("サンプリング回数を入力(正の値):");
      scanf("%d", &sampling_num);
      assert(sampling_num > 0);*/

      printf("サンプリング周波数を入力(正の値):");
      scanf("%lf", &sampling_rate);
      assert(sampling_rate > 0);

      signal_1 = gen_signal(a_amp, a_fre, data_num, sampling_rate, true, offset);
      signal_2 = gen_signal(b_amp, b_fre, data_num, sampling_rate, false, NO_OFFSET);
      signal_array = sum_arrays(signal_1, signal_2, data_num, signal_array);
      break;

    case 4:
      free(signal_array); //残っている信号配列の消去

      printf("**********************************************************\n");
      printf("矩形波の作成を行います\n");
      printf("矩形波の振幅(a)を入力(正の値):");
      scanf("%lf", &a_amp);
      assert(a_amp > 0);

      printf("矩形波の周波数(1 / 2*γ)を入力:");
      scanf("%lf", &a_fre);

      printf("サンプリング周波数を入力(正の値):");
      scanf("%lf", &sampling_rate);
      assert(sampling_rate > 0);

      signal_array = gen_square_signal(a_amp, a_fre, data_num, sampling_rate);
      break;

    case 0:
      break;
  }
  free(signal_1);
  free(signal_2);
  return signal_array;
}
