#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "A1_1764087.h"

#define BUFFER_SIZE 256

//typedef Struct
typedef struct array{
  char name[BUFFER_SIZE]; //配列名
  int size; //配列サイズ
  double *array_content; //配列の中身
} array_st;

int main(void){




  free(array_1);
  free(array_2);

  return 0;
}

void array_io(void){
  int operation = 0;
  printf("**********************************************************\n");
  printf("処理を選択\n");
  printf("[1]キーボードによる配列入力\n");
  printf("[2]配列要素出力\n");
  printf("[3]ファイルから配列データ入力\n");
  printf("[4]ファイルへ配列データ出力\n");
  printf("[5]ファイルから読み取ったデータ数の取得\n");
  printf("[6]配列を指定数値に初期化\n");
  printf("[7]配列を乱数に初期化\n");
  printf("[8]配列の要素数指定および変更");
  printf("[0]戻る");
  scanf("%d", &operation);

  switch(operation){
      case 1:
        int operation_case1 = 0;
        printf("**********************************************************\n");
        printf("キーボードによる配列の入力を行います。\n");
        printf("array_1に入力する場合 -> 1、array_2に入力する場合 -> 2を入力");
        scanf("%d", operation_case1);
        assert(operation_case1 == 1 || operation_case1 == 2);

        int array_size = 0;


        if(operation_case1 == 1){
          printf("配列のサイズを入力してください");
          scanf("%d", array_1_size);
          array_1 = input_array(array_1_size);
        } else {
          printf("配列のサイズを入力してください");
          scanf("%d", array_2_size);
          array_2 = input_array(array_2_size);
        }
        break;

      case 2:
        int operation_case2 = 0;
        printf("**********************************************************\n");
        printf("配列の出力を行います。\n");
        printf("array_1を出力する場合 -> 1、array_2を出力する場合 -> 2を入力");
        scanf("%d", operation_case2);
        assert(operation_case2 == 1 || operation_case2 == 2);

        if(operation_case1 == 1){
          print_array(array_1);
        } else {
          print_array(array_2);
        }
        break;

      case 3:
        int operation_case3 = 0;
        FILE *fp = NULL;
        printf("**********************************************************\n");
        printf("ファイルからの配列データの入力を行います。\n");
        char file_name[BUFFER_SIZE] = {};
        printf("入力元のファイルを選択して下さい。")
        scanf("%c", file_name);

        fp = fopen(file_name, "w");
        printf("入力先を決定します。")
        printf("array_1に入力する場合 -> 1、array_2に入力する場合 -> 2を入力");
        scanf("%d", operation_case3);
        assert(operation_case3 == 1 || operation_case3 == 2);

        if(operation_case3 == 1){
          array_1 = input_array_from_file(fp);
        } else {
          array_2 = input_array_from_file(fp);
        }
        fclose(fp);
        break;

      case 4:
        int operation_case4 = 0;
        FILE *fp = NULL;
        printf("**********************************************************\n");
        printf("ファイルへの配列データの出力を行います。\n");
        char file_name[BUFFER_SIZE] = {};
        printf("出力先のファイルを選択して下さい。")
        scanf("%c", file_name);

        fp = fopen(file_name, "w");
        printf("出力元を決定します。")
        printf("array_1を出力する場合 -> 1、array_2に出力する場合 -> 2を入力");
        scanf("%d", operation_case4);
        assert(operation_case4 == 1 || operation_case4 == 2);

        if(operation_case4 = 1){
          fp = export_array(array_1, array_1_size, fp);
        } else {
          fp = export_array(array_2, array_2_size, fp);
        }
        fclose(fp);
        break;







  }

}

void array_operation(void){
  int operation = 0;
  printf("**********************************************************\n");
  printf("処理を選択\n");
  printf("[1]配列の最大値、最小値の探索\n");
  printf("[2]配列の最大値、最小値の要素番号の探索\n");
  printf("[3]指定数値をもつ要素番号の探索\n");
  printf("[4]配列の昇順、降順の並び替え\n");
  printf("[5]配列を逆順に並び替え\n");
  printf("[6]配列のコピー\n");
  printf("[0]戻る");
  scanf("%d", &operation);

  switch(operation):
}

void array_calculation(void){
  int operation = 0;
  printf("**********************************************************\n");
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
  printf("[0]戻る");
  scanf("%d", &operation);

  switch(operation):
}
