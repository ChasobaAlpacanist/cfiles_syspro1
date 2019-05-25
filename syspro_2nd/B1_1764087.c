#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>
#include <complex.h>
#include "A1_1764087.h"
#include "B1_1764087.h"

//
//正弦波または定常信号を作成する関数
double *gen_signal(double amp, double fre, int data_num, double sampling_rate, bool issin, double value_offset){
  assert(amp >= 0);
  double *signal_array = NULL;
  signal_array = (double *)calloc(data_num, sizeof(double));
  if(issin == true){
    for(int i = 0; i < data_num; i++){
      signal_array[i] = (amp * sin(2 * M_PI * fre * (i / sampling_rate))) + value_offset;
    }
  } else {
    for(int i = 0; i < data_num; i++){
      signal_array[i] = (amp * cos(2 * M_PI * fre * (i / sampling_rate))) + value_offset;
    }
  }
  return signal_array;
}

//矩形波信号を作成する関数
double *gen_square_signal(double amp, double fre, int data_num, double sampling_rate){
  double *signal_array = NULL;
  signal_array = (double *)calloc(data_num, sizeof(double));
  for(int i = 0; i < data_num; i++){
    if(sin(2 * M_PI * fre * (i / sampling_rate)) > 0){
      signal_array[i] = amp;
    } else {
      if(sin(2 * M_PI * fre * (i / sampling_rate)) < 0){
        signal_array[i] = (-1) * amp;
      } else {
        signal_array[i] = 0;
      }
    }
  }
  return signal_array;
}

//信号をサンプリングする関数
double *sampling_signal(double *input_signal, int signal_size, int sampling_num){
  assert(signal_size > sampling_num);
  double *sample_data = NULL;
  sample_data = (double *)calloc(sampling_num, sizeof(double));
  int sample_step = signal_size / sampling_num; //サンプル間隔

  for(int i = 0; i < sampling_num; i++){
    sample_data[i] = input_signal[i * sample_step];
  }
  return sample_data;
}

//信号を離散フーリエ変換する関数
double complex *dft_signal(double *input_signal, int signal_size, int sampling_num){
  double *sampled_signal = NULL; //サンプリングデータの作成
  sampled_signal = sampling_signal(input_signal, signal_size, sampling_num);

  double ang_fre = 0; //角周波数の定義

  double complex *ft_array = NULL;
  ft_array = (double complex *)calloc(sampling_num, sizeof(double complex));
  for(int i = 0; i < sampling_num; i++){
    ft_array[i] = 0 + 0 * I; //配列要素の初期化
    ang_fre = (2 * M_PI * i) / sampling_num;
    for(int j = 0; j < sampling_num; j++){ //フーリエ係数の計算
      ft_array[i] += sampled_signal[j] * (cos(ang_fre * j) - sin(ang_fre * j) * I);
    }
    ft_array[i] /= sampling_num;
  }
  return ft_array;
}

//複素周波数列を離散フーリエ逆変換する関数
double *inverse_dft_signal(double complex *ft_array, int array_size, int plot_num, double plot_step){
  double *signal_data = NULL;
  signal_data = (double *)calloc(plot_num, sizeof(double));
  double ang_fre = 0; //角周波数の定義
  double ft_real = 0; //フーリエ要素の実部
  double ft_imag = 0; //フーリエ要素の虚部

  for(int i = 0; i < plot_num; i++){ //フーリエ逆変換
    ang_fre = (2 * M_PI * plot_step * i) / array_size; //時刻plot_step * iでの角周波数
    for(int j = 0; j < array_size; j++){
      double ang = ang_fre * j; // 角度
      ft_real = creal(ft_array[j]); //実部
      ft_imag = cimag(ft_array[j]); //虚部

      signal_data[i] += ft_real * cos(ang) - ft_imag * sin(ang);
    }
  }
  return signal_data;
}

//信号のパワースペクトルを求める関数
double *p_s_signal(double *input_signal, int signal_size, int sampling_num){
  double complex *ft_array = NULL; //複素周波数列を格納する配列
  double *p_s_array = NULL; //パワースペクトルを格納する配列

  ft_array = dft_signal(input_signal, signal_size, sampling_num);
  p_s_array = (double *)calloc(sampling_num, sizeof(double));

  for(int i = 0; i < signal_size; i++){
    p_s_array[i] = pow(creal(ft_array[i]), 2) + pow(cimag(ft_array[i]), 2);
  }
  return p_s_array;
}

//3.信号出力関数
//ファイルへのデータ出力
FILE *export_signal(double *num_array, int array_size, FILE *export_file){
  for(int i = 0; i < array_size; i++){
    fprintf(export_file, "%d, %lf\n", i, num_array[i]);
  }
  return export_file;
}

//ファイルへの複素数データ出力
FILE *export_complex_signal(double complex *num_array, int array_size, FILE *export_file){
  for(int i = 0; i < array_size; i++){
    fprintf(export_file, "%d, %lf + %lf I\n", i, creal(num_array[i]), cimag(num_array[i]));
  }
  return export_file;
}
