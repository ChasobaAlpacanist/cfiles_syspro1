#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "A1_1764087.h"

#define BUFFER_SIZE 256

//Prototype Declaration
void array_io(void); //配列入出力系の関数群をまとめた関数
void array_operation(void); //配列操作系の関数群をまとめた関数
void array_calculation(void); //配列演算系の関数群をまとめた関数

//グローバル変数の定義
double *array_1_glo = NULL;
double *array_2_glo = NULL;
int array_1_size_glo = 0;
int array_2_size_glo = 0;

//mains
int main(void){
  int master_operation = 0; //操作決定のための変数

  printf("**********************************************************\n");
  printf("配列処理プログラム\n");
  do {
    printf("**********************************************************\n");
    printf("メインメニューです\n");
    printf("配列処理の選択\n");
    printf("[1]配列基本入出力\n");
    printf("[2]配列操作\n");
    printf("[3]配列演算\n");
    printf("[0]終了\n:");
    scanf("%d", &master_operation);
    assert(master_operation == 1 || master_operation == 2 ||
           master_operation == 3 || master_operation == 0);

    switch(master_operation){
      case 1:
        array_io();
        break;

      case 2:
        array_operation();
        break;

      case 3:
        array_calculation();
        break;

      case 0:
        break;
    }

  } while(master_operation != 0);
  free(array_1_glo);
  free(array_2_glo);
  return 0;
}

void array_io(void){ //配列基本入出力関数群
  int operation = 0; //操作用の変数の定義
  printf("**********************************************************\n");
  printf("配列の基本的な入出力を行います\n");
  printf("処理を選択\n");
  printf("[1]キーボードによる配列入力\n");
  printf("[2]配列要素出力\n");
  printf("[3]ファイルから配列データ入力\n");
  printf("[4]ファイルへ配列データ出力\n");
  printf("[5]ファイルから読み取ったデータ数の取得\n");
  printf("[6]配列を指定数値に初期化\n");
  printf("[7]配列を乱数に初期化\n");
  printf("[8]配列の要素数指定および変更\n");
  printf("[0]戻る\n:");
  scanf("%d", &operation);
  assert(operation == 1 || operation == 2 ||
         operation == 3 || operation == 4 ||
         operation == 5 || operation == 6 ||
         operation == 7 || operation == 8 || operation == 0);

  //switch分岐時に必要な変数の定義
  int operation_case = 0; //switch分岐のあとで処理選択が必要なときの変数
  FILE *fp = NULL; //switch分岐のあとでファイル操作が必要となった時の変数
  char file_name[BUFFER_SIZE] = {}; //ファイル名の変数
  double number = 0; //任意double型の数字変数

  switch(operation){
      case 1:
        printf("**********************************************************\n");
        printf("キーボードによる配列の入力を行います。\n");

        printf("array_1に入力する場合 -> 1、array_2に入力する場合 -> 2を入力:");
        scanf("%d", &operation_case);
        assert(operation_case == 1 || operation_case == 2);

        if(operation_case == 1){
          free(array_1_glo); //更新のため、配列を初期化する。
          printf("配列のサイズを入力してください:");
          scanf("%d", &array_1_size_glo);
          array_1_glo = input_array(array_1_size_glo);
        } else {
          free(array_2_glo); //更新のため、配列を初期化する。
          printf("配列のサイズを入力してください:");
          scanf("%d", &array_2_size_glo);
          array_2_glo = input_array(array_2_size_glo);
        }
        printf("入力を終了しました。\n");
        break;

      case 2:
        printf("**********************************************************\n");
        printf("配列の出力を行います。\n");
        printf("array_1を出力する場合 -> 1、array_2を出力する場合 -> 2を入力:");
        scanf("%d", &operation_case);
        assert(operation_case == 1 || operation_case == 2);

        if(operation_case == 1){
          if(array_1_glo != NULL){
            printf("配列は以下です。\n");
            print_array(array_1_glo, array_1_size_glo);
          } else {
            printf("配列が入力されておりません。\n");
          }
        } else {
          if(array_2_glo != NULL){
            printf("配列は以下です。\n");
            print_array(array_2_glo, array_2_size_glo);
          } else {
            printf("配列が入力されておりません。\n");
          }
          printf("出力を終了しました\n");
        }
        break;

      case 3:
        printf("**********************************************************\n");
        printf("ファイルからの配列データの入力を行います。\n");
        printf("入力元のファイルを選択して下さい:");
        scanf("%s", file_name);

        fp = fopen(file_name, "r");
        assert(fp != NULL); //入力元の存在確認

        printf("入力先を決定します。\n");
        printf("array_1に入力する場合 -> 1、array_2に入力する場合 -> 2を入力:");
        scanf("%d", &operation_case);
        assert(operation_case == 1 || operation_case == 2);

        if(operation_case == 1){
          free(array_1_glo); //更新のため、配列を初期化する。
          array_1_size_glo = count_file_data(fp);
          array_1_glo = input_array_from_file(fp);
        } else {
          free(array_2_glo); //更新のため、配列を初期化する。
          array_2_size_glo = count_file_data(fp);
          array_2_glo = input_array_from_file(fp);
        }
        printf("入力が終了しました\n");
        fclose(fp);
        break;

      case 4:
        printf("**********************************************************\n");
        printf("ファイルへの配列データの出力を行います。\n");
        printf("出力先のファイルを入力して下さい:");
        scanf("%s", file_name);

        fp = fopen(file_name, "w");
        printf("出力元を決定します。\n");
        printf("array_1を出力する場合 -> 1、array_2に出力する場合 -> 2を入力:");
        scanf("%d", &operation_case);
        assert(operation_case == 1 || operation_case == 2);

        if(operation_case == 1){
          fp = export_array(array_1_glo, array_1_size_glo, fp);
        } else {
          fp = export_array(array_2_glo, array_2_size_glo, fp);
        }

        printf("%sへのファイル出力が終了しました。\n", file_name);
        fclose(fp);
        break;

      case 5:
        printf("**********************************************************\n");
        printf("ファイル中の数値の数のカウントを行います。\n");
        printf("カウントするファイルを入力してください:");
        scanf("%s", file_name);

        fp = fopen(file_name, "r");
        assert(fp != NULL); //入力元の存在確認

        printf("%sのデータの数は%dです。\n", file_name, count_file_data(fp));
        break;

      case 6:
        printf("**********************************************************\n");
        printf("任意のdouble型の数による配列の初期化を行います。\n");
        printf("任意の数字を設定してください:");
        scanf("%lf", &number);

        printf("次に初期化する配列を選択します。\n");
        printf("配列はすでに存在していることを確認してください\n");
        printf("array_1を初期化する場合 -> 1、array_2に初期化する場合 -> 2を入力:");
        scanf("%d", &operation_case);
        assert(operation_case == 1 || operation_case == 2);

        if(operation_case == 1){
          array_1_glo = number_array_intialize(array_1_glo, array_1_size_glo, number);
          printf("array_1を%lfに初期化しました\n", number);
        } else {
          array_2_glo = number_array_intialize(array_2_glo, array_2_size_glo, number);
          printf("array_2を%lfに初期化しました\n", number);
        }
        break;

      case 7:
        printf("**********************************************************\n");
        printf("-1から1の乱数による配列の初期化を行います。\n");

        printf("配列はすでに存在していることを確認してください\n");
        printf("array_1を初期化する場合 -> 1、array_2に初期化する場合 -> 2を入力:");
        scanf("%d", &operation_case);
        assert(operation_case == 1 || operation_case == 2);

        if(operation_case == 1){
          array_1_glo = random_array_intialize(array_1_glo, array_1_size_glo);
          printf("array_1を乱数に初期化しました\n");
        } else {
          array_2_glo = random_array_intialize(array_2_glo, array_2_size_glo);
          printf("array_2を乱数に初期化しました\n");
        }
        break;

      case 8:
        printf("**********************************************************\n");
        printf("配列サイズの変更を行います。\n");
        printf("配列はすでに存在していることを確認してください\n");
        printf("array_1を変更する場合 -> 1、array_2に変更する場合 -> 2を入力:");
        scanf("%d", &operation_case);
        assert(operation_case == 1 || operation_case == 2);

        if(operation_case == 1){
          printf("変更前のarray_1の配列サイズは%dです\n", array_1_size_glo);
          printf("配列サイズを指定してください:");
          scanf("%d", &array_1_size_glo);
          array_1_glo = change_array_size(array_1_glo, array_1_size_glo);
          printf("array_1のサイズを%dに変更しました\n", array_1_size_glo);
        } else {
          printf("変更前のarray_2の配列サイズは%dです\n", array_1_size_glo);
          printf("配列サイズを指定してください:");
          scanf("%d", &array_2_size_glo);
          array_1_glo = change_array_size(array_2_glo, array_2_size_glo);
          printf("array_2のサイズを%dに変更しました\n", array_2_size_glo);
        }
        break;

      case 0:
        break;
  }

}

void array_operation(void){ //配列操作関数群
  int operation = 0;
  printf("**********************************************************\n");
  printf("配列の操作を行います\n");
  printf("処理を選択\n");
  printf("[1]配列の最大値、最小値の探索\n");
  printf("[2]配列の最大値、最小値の要素番号の探索\n");
  printf("[3]指定数値をもつ要素番号の探索\n");
  printf("[4]配列の昇順、降順の並び替え\n");
  printf("[5]配列を逆順に並び替え\n");
  printf("[6]配列のコピー\n");
  printf("[0]戻る\n:");
  scanf("%d", &operation);

  assert(operation == 1 || operation == 2 ||
         operation == 3 || operation == 4 ||
         operation == 5 || operation == 6 || operation == 0);

  //switch分岐時に必要な変数の定義
  int operation_case = 0; //switch分岐のあとで処理選択が必要なときの変数
  double value = 0; //目的地探索に必要な変数
  int index = 0; //目的値インデックス探索に必要な変数
  double search_value = 0; //探索する数字を格納する変数
  double *modified_array_1 = NULL; ////処理後の配列の定義
  double *modified_array_2 = NULL;




  switch(operation){
      case 1:
        printf("**********************************************************\n");
        printf("配列の最大、最小の探索を行います\n");
        printf("配列はすでに存在していることを確認してください\n");
        printf("array_1を探索する場合 -> 1、array_2に探索する場合 -> 2を入力:");
        scanf("%d", &operation_case);
        assert(operation_case == 1 || operation_case == 2);

        if(operation_case == 1){
          printf("**********************************************************\n");
          printf("array_1の探索を行います\n");

          value = search_array_num_maxmin(array_1_glo, array_1_size_glo);
          printf("探索値は%lfです\n", value);
        } else {
          printf("**********************************************************\n");
          printf("array_2の探索を行います\n");

          value = search_array_num_maxmin(array_2_glo, array_2_size_glo);
          printf("探索値は%lfです\n", value);
        }
        break;

      case 2:
        printf("**********************************************************\n");
        printf("配列の最大、最小のインデックス探索を行います\n");
        printf("配列はすでに存在していることを確認してください\n");
        printf("array_1を探索する場合 -> 1、array_2に探索する場合 -> 2を入力:");
        scanf("%d", &operation_case);
        assert(operation_case == 1 || operation_case == 2);

        if(operation_case == 1){
          printf("**********************************************************\n");
          printf("array_1のインデックス探索を行います\n");

          index = search_array_index_maxmin(array_1_glo, array_1_size_glo);
          printf("目的の要素番号はは%dです\n", index);
        } else {
          printf("**********************************************************\n");
          printf("array_2の探索を行います\n");

          index = search_array_index_maxmin(array_2_glo, array_2_size_glo);
          printf("目的の要素番号は%dです\n", index);
        }
        break;

      case 3:
        printf("**********************************************************\n");
        printf("配列中の指定数値のインデックス探索を行います\n");
        printf("配列はすでに存在していることを確認してください\n");
        printf("array_1を探索する場合 -> 1、array_2に探索する場合 -> 2を入力:");
        scanf("%d", &operation_case);
        assert(operation_case == 1 || operation_case == 2);

        printf("探索するdouble型数値を選択して下さい:");
        scanf("%lf", &search_value);

        if(operation_case == 1){
          printf("**********************************************************\n");
          printf("array_1の探索を行います\n");
          index = search_array_index_num(array_1_glo, array_1_size_glo, search_value);
          if(index == -1){
            printf("指定数値は見つかりませんでした\n");
          } else {
            printf("目的の要素番号は%dです\n", index);
          }
        } else {
          printf("**********************************************************\n");
          printf("array_2の探索を行います\n");
          index = search_array_index_num(array_2_glo, array_2_size_glo, search_value);
          if(index == -1){
            printf("指定数値は見つかりませんでした\n");
          } else {
            printf("目的の要素番号は%dです\n", index);
          }
        }
        break;

      case 4:
        printf("**********************************************************\n");
        printf("配列の並び替えを行います\n");
        printf("配列はすでに存在していることを確認してください\n");
        printf("array_1を整列する場合 -> 1、array_2に整列する場合 -> 2を入力:");
        scanf("%d", &operation_case);
        assert(operation_case == 1 || operation_case == 2);

        if(operation_case == 1){
          printf("**********************************************************\n");
          printf("array_1の整列を行います\n");
          modified_array_1 = sort_array(array_1_glo, modified_array_1, array_1_size_glo);
          printf("変更前:\n");
          print_array(array_1_glo, array_1_size_glo);
          printf("**********************************************************\n");
          printf("変更後:\n");
          print_array(modified_array_1, array_1_size_glo);
        } else {
          printf("**********************************************************\n");
          printf("array_2の整列を行います\n");
          modified_array_2 = sort_array(array_2_glo, modified_array_2, array_2_size_glo);
          printf("変更前:\n");
          print_array(array_2_glo, array_2_size_glo);
          printf("**********************************************************\n");
          printf("変更後:\n");
          print_array(modified_array_2, array_2_size_glo);
        }
        break;

      case 5:
        printf("**********************************************************\n");
        printf("配列の逆順に並び替えます\n");
        printf("配列はすでに存在していることを確認してください\n");
        printf("array_1を整列する場合 -> 1、array_2に整列する場合 -> 2を入力:");
        scanf("%d", &operation_case);
        assert(operation_case == 1 || operation_case == 2);

        if(operation_case == 1){
          printf("**********************************************************\n");
          printf("array_1の並び替えを行います\n");
          modified_array_1 = inverse_array(array_1_glo, modified_array_1, array_1_size_glo);
          printf("変更前:\n");
          print_array(array_1_glo, array_1_size_glo);
          printf("**********************************************************\n");
          printf("変更後:\n");
          print_array(modified_array_1, array_1_size_glo);
        } else {
          printf("**********************************************************\n");
          printf("array_2の整列を行います\n");
          modified_array_2 = inverse_array(array_2_glo, modified_array_2, array_2_size_glo);
          printf("変更前:\n");
          print_array(array_2_glo, array_2_size_glo);
          printf("**********************************************************\n");
          printf("変更後:\n");
          print_array(modified_array_2, array_2_size_glo);
        }
        break;

      case 6:
        printf("**********************************************************\n");
        printf("配列のコピーを作成します\n");
        printf("配列はすでに存在していることを確認してください\n");
        printf("array_1をコピーする場合 -> 1、array_2にコピーする場合 -> 2を入力:");
        scanf("%d", &operation_case);
        assert(operation_case == 1 || operation_case == 2);

        if(operation_case == 1){
          printf("**********************************************************\n");
          printf("array_1のコピーを行います\n");
          modified_array_1 = copy_array(array_1_glo, modified_array_1, array_1_size_glo);
          printf("コピーが終了しました\n");
          printf("コピーした配列は以下です\n");
          print_array(modified_array_1, array_1_size_glo);
        } else {
          printf("**********************************************************\n");
          printf("array_2のコピーを行います\n");
          modified_array_2 = copy_array(array_2_glo, modified_array_2, array_2_size_glo);
          printf("コピーが終了しました\n");
          printf("コピーした配列は以下です\n");
          print_array(modified_array_2, array_2_size_glo);
        }
        break;

      case 0:
        break;
  }
  free(modified_array_1);
  free(modified_array_2);
}

void array_calculation(void){ //配列演算関数群
  int operation = 0;
  printf("**********************************************************\n");
  printf("配列の演算を行います\n");
  printf("処理を選択\n");
  printf("[1]配列シフト\n");
  printf("[2]配列と配列の加算\n");
  printf("[3]配列と配列の減算\n");
  printf("[4]配列要素の絶対値変換\n");
  printf("[5]配列総和算出\n");
  printf("[6]配列平均値算出\n");
  printf("[7]配列標準偏差算出\n");
  printf("[8]配列変動係数算出\n");
  printf("[9]配列中央値算出\n");
  printf("[10]指定数以上の要素数算出\n");
  printf("[11]指定数以上の要素総和算出\n");
  printf("[0]戻る\n:");
  scanf("%d", &operation);

  //switch分岐時に必要な変数の定義
  int operation_case = 0; //switch分岐のあとで処理選択が必要なときの変数
  int counter = 0; //数を数える変数
  int shift_size = 0; //配列シフトにおけるシフト量
  double *res_array = NULL; //配列演算結果を格納する配列
  double value = 0; //配列の演算値を格納する変数
  double number = 0; //ユーザの指定した数値を格納する変数

  assert(operation == 1 || operation == 2 ||
         operation == 3 || operation == 4 ||
         operation == 5 || operation == 6 ||
         operation == 7 || operation == 8 ||
         operation == 9 || operation == 10 || operation == 11 ||
         operation == 0);

  switch(operation){
    case 1:
      printf("**********************************************************\n");
      printf("配列シフトを行います\n");
      printf("配列はすでに存在していることを確認してください\n");
      printf("array_1をシフトする場合 -> 1、array_2にシフトする場合 -> 2を入力:");
      scanf("%d", &operation_case);
      assert(operation_case == 1 || operation_case == 2);

      printf("シフトする大きさを選択してください\n");
      printf("右移動であれば正の数、左移動であれば負の数を選択\n");
      printf("シフト量は配列サイズ以下とします\n:");
      scanf("%d", &shift_size);

      if(operation_case == 1){
        printf("**********************************************************\n");
        printf("array_1の配列シフトを行います\n");
        res_array = shift_array(array_1_glo, array_1_size_glo, shift_size);
        printf("シフト前の配列:\n");
        print_array(array_1_glo, array_1_size_glo);
        printf("シフト後の配列:\n");
        print_array(res_array, array_1_size_glo);
      } else {
        printf("**********************************************************\n");
        printf("array_2の配列シフトを行います\n");
        res_array = shift_array(array_2_glo, array_2_size_glo, shift_size);
        printf("シフト前の配列:\n");
        print_array(array_2_glo, array_2_size_glo);
        printf("シフト後の配列:\n");
        print_array(res_array, array_1_size_glo);
      }
      free(res_array);
      break;

    case 2:
      printf("**********************************************************\n");
      printf("配列の加算を行います\n");
      printf("配列はすでに存在していることを確認してください\n");

      assert(array_1_glo != NULL && array_2_glo != NULL);
      assert(array_1_size_glo == array_2_size_glo); //配列の存在確認と配列サイズが等しいか確認
      free(res_array);
      res_array = (double *)calloc(array_1_size_glo, sizeof(double));

      printf("array_1は以下:\n");
      print_array(array_1_glo, array_1_size_glo);
      printf("array_2は以下:\n");
      print_array(array_2_glo, array_2_size_glo);

      printf("**********************************************************\n");
      res_array = sum_arrays(array_1_glo, array_2_glo, array_1_size_glo, res_array);
      printf("加算の結果は以下:\n");
      print_array(res_array, array_1_size_glo);
      free(res_array);
      break;

    case 3:
      printf("**********************************************************\n");
      printf("配列の減算を行います\n");

      assert(array_1_glo != NULL && array_2_glo != NULL);
      assert(array_1_size_glo == array_2_size_glo); //配列の存在確認と配列サイズが等しいか確認

      printf("array_1は以下:\n");
      print_array(array_1_glo, array_1_size_glo);
      printf("array_2は以下:\n");
      print_array(array_2_glo, array_2_size_glo);

      printf("**********************************************************\n");
      res_array = dif_arrays(array_1_glo, array_2_glo, array_1_size_glo, res_array);
      printf("減算の結果は以下:\n");
      print_array(res_array, array_1_size_glo);
      free(res_array);
      break;

    case 4:
      printf("**********************************************************\n");
      printf("配列要素の絶対値をを求めます\n");
      printf("array_1を計算する場合 -> 1、array_2を計算する場合 -> 2を入力:");
      scanf("%d", &operation_case);
      assert(operation_case == 1 || operation_case == 2);

      free(res_array);
      printf("**********************************************************\n");
      if(operation_case == 1){
        res_array = abs_array(array_1_glo, array_1_size_glo);
        printf("演算前は以下:\n");
        print_array(array_1_glo, array_1_size_glo);
        printf("演算後は以下:\n");
        print_array(res_array, array_1_size_glo);
      } else {
        res_array = abs_array(array_2_glo, array_2_size_glo);
        printf("演算前は以下:\n");
        print_array(array_2_glo, array_2_size_glo);
        printf("演算後は以下:\n");
        print_array(res_array, array_2_size_glo);
      }
      free(res_array);
      break;

    case 5:
      printf("**********************************************************\n");
      printf("配列の総和をを求めます\n");
      printf("array_1を計算する場合 -> 1、array_2を計算する場合 -> 2を入力:");
      scanf("%d", &operation_case);
      assert(operation_case == 1 || operation_case == 2);

      printf("**********************************************************\n");
      if(operation_case == 1){
        value = sum_array(array_1_glo, array_1_size_glo);
        printf("演算した配列は以下:\n");
        print_array(array_1_glo, array_1_size_glo);
      } else {
        value = sum_array(array_2_glo, array_2_size_glo);
        printf("演算した配列は以下:\n");
        print_array(array_2_glo, array_2_size_glo);
      }
      printf("総和は -> %lf\n", value);
      break;

    case 6:
      printf("**********************************************************\n");
      printf("配列の平均値をを求めます\n");
      printf("array_1を計算する場合 -> 1、array_2を計算する場合 -> 2を入力:");
      scanf("%d", &operation_case);
      assert(operation_case == 1 || operation_case == 2);

      printf("**********************************************************\n");
      if(operation_case == 1){
        value = mean_array(array_1_glo, array_1_size_glo);
        printf("演算した配列は以下:\n");
        print_array(array_1_glo, array_1_size_glo);
      } else {
        value = mean_array(array_2_glo, array_2_size_glo);
        printf("演算した配列は以下:\n");
        print_array(array_2_glo, array_2_size_glo);
      }
      printf("平均は -> %lf\n", value);
      break;

    case 7:
      printf("**********************************************************\n");
      printf("配列の標準偏差をを求めます\n");
      printf("array_1を計算する場合 -> 1、array_2を計算する場合 -> 2を入力:");
      scanf("%d", &operation_case);
      assert(operation_case == 1 || operation_case == 2);

      printf("**********************************************************\n");
      if(operation_case == 1){
        value = sd_array(array_1_glo, array_1_size_glo);
        printf("演算した配列は以下:\n");
        print_array(array_1_glo, array_1_size_glo);
      } else {
        value = sd_array(array_2_glo, array_2_size_glo);
        printf("演算した配列は以下:\n");
        print_array(array_2_glo, array_2_size_glo);
      }
      printf("標準偏差は -> %lf\n", value);
      break;

    case 8:
      printf("**********************************************************\n");
      printf("配列の変動係数を求めます\n");
      printf("array_1を計算する場合 -> 1、array_2を計算する場合 -> 2を入力:");
      scanf("%d", &operation_case);
      assert(operation_case == 1 || operation_case == 2);

      printf("**********************************************************\n");
      if(operation_case == 1){
        value = cv_array(array_1_glo, array_1_size_glo);
        printf("演算した配列は以下:\n");
        print_array(array_1_glo, array_1_size_glo);
      } else {
        value = cv_array(array_2_glo, array_2_size_glo);
        printf("演算した配列は以下:\n");
        print_array(array_2_glo, array_2_size_glo);
      }
      printf("変動係数は -> %lf\n", value);
      break;

    case 9:
      printf("**********************************************************\n");
      printf("配列の中央値を求めます\n");
      printf("array_1を計算する場合 -> 1、array_2を計算する場合 -> 2を入力:");
      scanf("%d", &operation_case);
      assert(operation_case == 1 || operation_case == 2);

      printf("**********************************************************\n");
      if(operation_case == 1){
        value = search_median_array(array_1_glo, array_1_size_glo);
        printf("演算した配列は以下:\n");
        print_array(array_1_glo, array_1_size_glo);
      } else {
        value = search_median_array(array_2_glo, array_2_size_glo);
        printf("演算した配列は以下:\n");
        print_array(array_2_glo, array_2_size_glo);
      }
      printf("中央値は -> %lf\n", value);
      break;

    case 10:
      printf("**********************************************************\n");
      printf("配列中の条件を満たす要素数を求めます\n");
      printf("array_1から求める場合 -> 1、array_2から求める場合 -> 2を入力:");
      scanf("%d", &operation_case);
      assert(operation_case == 1 || operation_case == 2);

      printf("基準となる数値を入力して下さい:");
      scanf("%lf", &number);

      if(operation_case == 1){
        printf("**********************************************************\n");
        counter = countif_array(array_1_glo, array_1_size_glo, number);
        printf("array_1の中身は以下:\n");
        print_array(array_1_glo, array_1_size_glo);
        printf("条件を満たす要素数は -> %d\n", counter);
      } else {
        printf("**********************************************************\n");
        counter = countif_array(array_2_glo, array_2_size_glo, number);
        printf("array_2の中身は以下:\n");
        print_array(array_2_glo, array_2_size_glo);
        printf("条件を満たす要素数は -> %d\n", counter);
      }
      break;

    case 11:
      printf("**********************************************************\n");
      printf("配列中の条件を満たす要素の総和を求めます\n");
      printf("array_1から求める場合 -> 1、array_2から求める場合 -> 2を入力:");
      scanf("%d", &operation_case);
      assert(operation_case == 1 || operation_case == 2);

      printf("基準となる数値を入力して下さい:");
      scanf("%lf", &number);

      if(operation_case == 1){
        printf("**********************************************************\n");
        value = sumif_array(array_1_glo, array_1_size_glo, number);
        printf("array_1の中身は以下:\n");
        print_array(array_1_glo, array_1_size_glo);
        printf("条件を満たす要素の総和は -> %lf\n", value);
      } else {
        printf("**********************************************************\n");
        value = countif_array(array_2_glo, array_2_size_glo, number);
        printf("array_2の中身は以下:\n");
        print_array(array_2_glo, array_2_size_glo);
        printf("条件を満たす要素の総和は -> %lf\n", value);
      }
      break;

    case 0:
      break;
  }
}
