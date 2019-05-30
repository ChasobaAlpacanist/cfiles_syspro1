#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <assert.h>
#include "A1_1764087.h"

//Constants
#define BUFFER_SIZE 256 //行を読むときのバッファサイズ

//配列基本入出力

//キーボードから配列データを入力
double *input_array(int array_size){
  double *array = NULL;
  array = (double *)calloc(array_size, sizeof(double));

  for(int i = 0; i < array_size; i++){
    printf("%d番目の値を入力してください:", i + 1);
    scanf("%lf", &array[i]);
  }
  return array;
}

//配列データをディスプレイに表示
void print_array(double *num_array, int array_size){
  for(int i = 0; i < array_size; i++){
    printf("%d番目の要素は%lf\n", i + 1, num_array[i]);
  }
}

//ファイルから配列データを入力
double *input_array_from_file(FILE *input_file){

  int file_lines = count_file_data(input_file);
  char buffer[BUFFER_SIZE] = {};

  double *array = NULL;
  array = (double *)calloc(file_lines, sizeof(double));

  for(int i = 0; i < file_lines; i++){
    fgets(buffer, BUFFER_SIZE, input_file);
    sscanf(buffer, "%lf", &array[i]);
  }
  rewind(input_file);

  return array;
}

//ファイルへの配列データ出力
FILE *export_array(double *num_array, int array_size, FILE *export_file){
  for(int i = 0; i < array_size; i++){
    fprintf(export_file, "%lf\n", num_array[i]);
  }
  return export_file;
}

//ファイルのデータ数のカウント
int count_file_data(FILE *file){
  //改行により別要素に移行すると仮定したときの要素数計算
  int file_lines = 0; //ファイルの要素数のカウント用の変数
  char buffer[BUFFER_SIZE];
  while(fgets(buffer, BUFFER_SIZE, file) != NULL){
    file_lines++;
  }
  rewind(file);
  return file_lines;
}

//任意のdouble型の数による配列の初期化
double *number_array_intialize(double *num_array, int array_size, double initial_num){
  assert(num_array != NULL); //num_arrayに配列が存在しているか確認
  for(int i = 0; i < array_size; i++){
    num_array[i] = initial_num;
  }
  return num_array;
}

//配列要素を(-1 ~ 1)で初期化
double *random_array_intialize(double *num_array, int array_size){
  assert(num_array != NULL); //num_arrayに配列が存在しているか確認
  srand((unsigned)time(NULL));
  for(int i = 0; i < array_size; i++){
    double rand_num = rand() % 20001; //0 ~ 20000までの乱数を計算
    rand_num = (rand_num / 10000) - 1.0; //-1.0から1.0までの乱数
    num_array[i] = rand_num;
  }
  return num_array;
}

//配列の要素数指定と変更
double *change_array_size(double *num_array, int array_size){
  assert(num_array != NULL);
  double *changed_num_array = NULL;
  changed_num_array = (double *)calloc(array_size, sizeof(array_size));
  changed_num_array = number_array_intialize(changed_num_array, array_size, 0);
  for(int i = 0; i < array_size; i++){
    changed_num_array[i] = num_array[i];
  }
  free(num_array); //変更前の配列を格納していたメモリを解放
  return changed_num_array;
}

//配列操作

//配列の最大最小を探索
double search_array_num_maxmin(double *num_array, int array_size){
  assert(num_array != NULL);
  int operation = 0;
  printf("最大 -> 1, 最小 -> -1を入力:");
  scanf("%d",&operation);

  assert(operation == 1 || operation == -1);
  double value = 0; //暫定的な目的の数字
  value = num_array[0];
  if(operation == 1){
    for(int i = 0; i < array_size - 1; i++){
      if(value < num_array[i + 1]){
        value = num_array[i + 1];
      }
    }
  } else {
    for(int i = 0; i < array_size - 1; i++){
      if(value > num_array[i + 1]){
        value = num_array[i + 1];
      }
    }
  }
  return value;
}

//配列の最大最小をもつ要素番号を探索
int search_array_index_maxmin(double *num_array, int array_size){
  assert(num_array != NULL);
  int operation = 0;
  printf("最大 -> 1, 最小 -> -1を選択:");
  scanf("%d",&operation);

  assert(operation == 1 || operation == -1);
  int index = 0; //暫定的な目的の要素番号
  if(operation == 1){
    for(int i = 0; i < array_size - 1; i++){
      if(num_array[i] < num_array[i + 1]){
        index = i + 1;
      }
    }
  } else {
    for(int i = 0; i < array_size - 1; i++){
      if(num_array[i] > num_array[i + 1]){
        index = i + 1;
      }
    }
  }
  return index;
}

//指定数値をもつ要素番号を探索
int search_array_index_num(double *num_array, int array_size, double num){
  assert(num_array != NULL);
  for(int i = 0; i < array_size; i++){
    if(num_array[i] == num){
      return i;
    }
  }
  return -1;
}

//配列を昇順、降順に並び替える
double *sort_array(double *num_array, double *sorted_num_array, int array_size){
  assert(num_array != NULL);
  sorted_num_array = copy_array(num_array, sorted_num_array, array_size);

  int operation = 0;
  printf("昇順 -> 1, 降順 -> -1を選択:");
  scanf("%d",&operation);
  assert(operation == 1 || operation == -1);

  if(operation == 1){
    for(int i = 0; i < array_size - 1; i++){
      for(int j = i + 1; j < array_size; j++){
        if(sorted_num_array[i] < sorted_num_array[j]){
          double tmp = sorted_num_array[j];
          sorted_num_array[j] = sorted_num_array[i];
          sorted_num_array[i] = tmp;
        }
      }
    }
  } else {
    for(int i = 0; i < array_size - 1; i++){
      for(int j = i + 1; j < array_size; j++){
        if(sorted_num_array[i] > sorted_num_array[j]){
          double tmp = sorted_num_array[j];
          sorted_num_array[j] = sorted_num_array[i];
          sorted_num_array[i] = tmp;
        }
      }
    }
  }
  return sorted_num_array;
}

//配列を昇順に並び替える
double *simple_sort_array(double *num_array, int array_size){
  for(int i = 0; i < array_size - 1; i++){
    for(int j = i + 1; j < array_size; j++){
      if(num_array[i] < num_array[j]){
        double tmp = num_array[j];
        num_array[j] = num_array[i];
        num_array[i] = tmp;
      }
    }
  }
  return num_array;
}

//配列の順序を逆にする
double *inverse_array(double *num_array, double *sorted_num_array, int array_size){
  free(sorted_num_array);
  sorted_num_array = (double *)calloc(array_size, sizeof(double));
  for(int i = 0; i < array_size; i++){
    sorted_num_array[(array_size - 1) - i] = num_array[i];
  }
  return sorted_num_array;
}

//配列のコピーを他の配列に出力
double *copy_array(double *num_array, double *copied_num_array, int array_size){
  free(copied_num_array);
  copied_num_array = (double *)calloc(array_size, sizeof(double));
  for(int i = 0; i < array_size; i++){
    copied_num_array[i] = num_array[i];
  }
  return copied_num_array;
}

//配列演算

//配列のシフト演算、ローテート演算
double *shift_array(double *num_array, int array_size, int shift_size){
  assert(shift_size <= array_size);
  int shift_operation = 0; //演算選択のための変数
  double *shifted_array = NULL;
  shifted_array = (double *)calloc(array_size, sizeof(double));
  printf("シフト操作 -> 1, ローテート操作 -> 2\n:");
  scanf("%d", &shift_operation);
  assert(shift_operation == 1 || shift_operation == 2);

  if(shift_operation == 1){ //シフト移動
    if(shift_size > 0){ //前進移動の時
      for(int i = 0; i < shift_size; i++){ //シフトサイズだけ要素番号の小さい方からを0を埋める
        shifted_array[i] = 0;
      }
      for(int i = shift_size; i < array_size; i++){
        shifted_array[i] = num_array[i - shift_size];
      }
    } else { //後退移動
      shift_size = abs(shift_size); //絶対値を取る
      for(int i = 0; i < shift_size; i++){ //シフトサイズだけ要素番号の大きい方から0を埋める
        shifted_array[(array_size - 1) - i] = 0;
      }
      for(int i = 0; i < array_size - shift_size; i++){
        shifted_array[i] = num_array[i + shift_size];
      }
    }
  } else { //ローテート移動
    if(shift_size > 0){ //前進移動
      for(int i = shift_size; i < array_size; i++){ //横にスライドする部分
        shifted_array[i] = num_array[i - shift_size];
      }
      for(int i = 0; i < shift_size; i++){
        shifted_array[i] = num_array[(array_size - 1) - shift_size + i]; //逆側にいく部分
      }
    } else { //後退移動
      shift_size = abs(shift_size);
      for(int i = 0; i < array_size - shift_size; i++){
        shifted_array[i] = num_array[i + shift_size];
      }
      for(int i = array_size - shift_size; i < array_size; i++){
        shifted_array[i] = num_array[i - (array_size - shift_size)];
      }
    }
  }
  return shifted_array;
}


//配列と配列の加算
double *sum_arrays(double *num_array1, double *num_array2, int array_size, double *res_array){
  free(res_array);
  res_array = (double *)calloc(array_size, sizeof(double));
  for(int i = 0; i < array_size; i++){
    res_array[i] = num_array1[i] + num_array2[i];
  }
  return res_array;
}

//配列と配列の減算
double *dif_arrays(double *num_array1, double *num_array2, int array_size, double *res_array){
  free(res_array);
  res_array = (double *)calloc(array_size, sizeof(double));
  for(int i = 0; i < array_size; i++){
    res_array[i] = num_array1[i] - num_array2[i];
  }
  return res_array;
}

//配列の絶対値計算
double *abs_array(double *num_array, int array_size){
  assert(num_array != NULL);
  double *array = NULL;
  array = (double *)calloc(array_size, sizeof(double));

  for(int i = 0; i < array_size; i++){
    array[i] = fabs(num_array[i]);
  }
  return array;
}

//配列の合計値計算
double sum_array(double *num_array, int array_size){
  assert(num_array != NULL);
  double sum = 0;
  for(int i = 0; i < array_size; i++){
    sum += num_array[i];
  }
  return sum;
}

//配列の平均値計算
double mean_array(double *num_array, int array_size){
  assert(num_array != NULL);
  return (sum_array(num_array, array_size) / array_size);
}

//配列の標準偏差計算
double sd_array(double *num_array, int array_size){
  assert(num_array != NULL);
  double variance = 0; //分散の定義
  double mean = mean_array(num_array, array_size); //平均算出

  for(int i = 0; i < array_size; i++){
    variance += pow((num_array[i] - mean), 2);
  }
  return sqrt(variance / (double)array_size);
}

//配列の変動係数計算
double cv_array(double *num_array, int array_size){
  assert(num_array != NULL);
  return (sd_array(num_array, array_size) / mean_array(num_array, array_size));
}

//配列の中央値算出
double search_median_array(double *num_array, int array_size){
  assert(num_array != NULL);
  double *array = NULL;
  int median_index = 0; //中央値のインデックス
  array = (double *)calloc(array_size, sizeof(double));

  array = copy_array(num_array, array, array_size);
  array = simple_sort_array(array, array_size);
  median_index = array_size / 2;

  if(array_size % 2 == 1){ //要素数が奇数の時
    return array[median_index];
  } else {                 //要素数が偶数の時
    return ((array[median_index - 1] + array[median_index]) / 2.0);
  }
}

//配列の条件の数字以上または以下の要素数の算出
double countif_array(double *num_array, int array_size, double number){
  assert(num_array != NULL);
  int operation = 0;
  printf("指定値以上 -> 1, 指定値以下 -> -1を選択:");
  scanf("%d",&operation);
  assert(operation == 1 || operation == -1);

  int counter = 0;
  if(operation == 1){
    for(int i = 0; i < array_size; i++){
      if(num_array[i] >= number){
        counter++;
      }
    }
  } else {
    for(int i = 0; i < array_size; i++){
      if(num_array[i] <= number){
        counter++;
      }
    }
  }
  return counter;
}

//配列の条件の数字以上または以下の要素の総和の算出
double sumif_array(double *num_array, int array_size, double number){
  assert(num_array != NULL);
  int operation = 0;
  printf("指定値以上 -> 1, 指定値以下 -> -1を選択:");
  scanf("%d",&operation);
  assert(operation == 1 || operation == -1);

  double sum = 0;
  if(operation == 1){
    for(int i = 0; i < array_size; i++){
      if(num_array[i] >= number){
        sum += num_array[i];
      }
    }
  } else {
    for(int i = 0; i < array_size; i++){
      if(num_array[i] <= number){
        sum += num_array[i];
      }
    }
  }
  return sum;
}
