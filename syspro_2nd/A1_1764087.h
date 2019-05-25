#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


/********************1. 配列基本入力**********************/

/*
  @brief キーボードから配列データを入力

  配列数に応じてキーボードからdouble型の値を入力し,配列に格納する関数
  @param [in] array_size(int) 配列サイズ
  @return (double *) 入力された配列のポインタを返す。
  @attention array_sizeは非零自然数
  @per 更新履歴
    - 2018/05/15
      基本的な機能の実装(by 1764087 木村慶豪)
*/
 double *input_array(int array_size);

/*
  @brief 配列データをディスプレイに表示

  配列数に応じてディスプレイ上に配列の中のdouble型の値を出力する関数
  @param [in] *num_array(double[]) 出力するデータ配列
  @param [in] array_size(int) 配列サイズ
  @return void
  @attention array_sizeはnum_array[]の配列数と同じでなければならない。
  @per 更新履歴
    - 2018/05/15
      基本的な機能の実装(by 1764087 木村慶豪)
*/
void print_array(double *num_array, int array_size);

/*
  @brief ファイルから配列データを入力

  ファイル中のデータ数に応じてファイルからdouble型の値を配列に入力する関数
  @param [in] input_file(FILE *) 配列に入力するためのファイル
  @param [out] array(double *) 入力された配列
  @return (double *) 入力された配列を返す
  @attention ファイルは改行ごとに異なる要素とする
  @per 更新履歴
    - 2018/05/15
      基本的な機能の実装(by 1764087 木村慶豪)
*/
double *input_array_from_file(FILE *input_file);

/*
  @brief ファイルへの配列データ出力

  double型の配列データをファイルに出力する関数
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
FILE *export_array(double *num_array, int array_size, FILE *export_file);

/*
  @brief ファイルのデータ数のカウント

  ファイルから読み取ったデータ数を取得
  @param [in] file(FILE *) 配列データを出力するためのファイル
  @return (int) カウント数を返す
  @attention ファイル内データは改行により別の要素とする。
  @per 更新履歴
    - 2018/05/15
      基本的な機能の実装(by 1764087 木村慶豪)
*/
int count_file_data(FILE *file);

/*
  @brief 任意のdouble型の数による配列の初期化

  double型の数字を引数にとり配列をその数字で初期化する
  @param [in][out] *num_array(double) 初期化する配列
  @param [in] array_size(int) 配列サイズ
  @param [in] initial_num(double) 初期化する数字
  @return (double *) 初期化後の配列を返す。
  @attention 配列数とarray_sizeは等しくなければならない
  @per 更新履歴
    - 2018/05/15
      基本的な機能の実装(by 1764087 木村慶豪)
*/
double *number_array_intialize(double *num_array, int array_size, double initial_num);

/*
  @brief 配列要素を(-1 ~ 1)で初期化

  配列を-1 ~ 1の乱数で初期化する
  @param [in][out] *num_array(double) 初期化する配列
  @param [in] array_size(int) 配列サイズ
  @return (double *) 初期化後の配列を返す。
  @attention 配列数とarray_sizeは等しくなければならない
  @per 更新履歴
    - 2018/05/15
      基本的な機能の実装(by 1764087 木村慶豪)
*/
double *random_array_intialize(double *num_array, int array_size);

/*
  @brief 配列の要素数指定と変更

  入力に配列のアドレスを指定し、要素数を指定し変更する。変更した際の要素を超える配列要素は削除され、
  要素数を増やした場合は0を埋める。
  @param [in] *num_array(double) 配列
  @param [in] array_size(int) 指定する配列サイズ
  @param [out] *changed_num_array(double)配列
  @return (double *) 変更後の配列を返す。
  @attention
  @per 更新履歴
    - 2018/05/15
      基本的な機能の実装(by 1764087 木村慶豪)
*/
double *change_array_size(double *num_array, int array_size);

/********************2. 配列操作**********************/

/*
  @brief 配列の最大最小を探索

  double型配列の最大値、最小値を求める
  @param [in] *num_array(double) 最大値、最小値を求める配列
  @param [in] array_size(int) 配列サイズ
  @param [out] value(double) 求めた最大値または最小値を表す
  @return (double) 求めた最大値または最小値を返す。
  @attention array_sizeは配列の要素数と等しくならなければならない
             関数中に最大または最小を選ぶ。最大 -> 1, 最小 -> -1
             それ以外の値を入力するとエラーが発生する。
  @per 更新履歴
    - 2018/05/15
      基本的な機能の実装(by 1764087 木村慶豪)
*/
double search_array_num_maxmin(double *num_array, int array_size);

/*
  @brief 配列の最大最小をもつ要素番号を探索

  double型配列の最大値、最小値の要素番号を調べる
  @param [in] *num_array(double) 最大値、最小値の要素番号を求める配列
  @param [in] array_size(int) 配列サイズ
  @param [out] index(int) 最大、または最小の数字を表す要素番号
  @return (int) 求めた最大値または最小値の配列番号を返す。
  @attention array_sizeは配列の要素数と等しくならなければならない
             関数中で入力により最大または最小を選ぶ。最大 -> 1, 最小 -> -1
             それ以外の値を入力するとエラーが発生する。
  @per 更新履歴
    - 2018/05/15
      基本的な機能の実装(by 1764087 木村慶豪)
*/
int search_array_index_maxmin(double *num_array, int array_size);

/*
  @brief 指定数値をもつ要素番号を探索

  任意の数値を入力し、その数値をもつ要素のインデックスを探索する
  @param [in] *num_array(double) 任意数値をもつ要素のインデックスを求める配列
  @param [in] array_size(int) 配列サイズ
  @param [in] num(double) 指定する数値
  @return (int) 求めたインデックスを返す。
  @attention array_sizeは配列の要素数と等しくならなければならない
             目的の要素が存在しなかった時は-1を返す。
  @per 更新履歴
    - 2018/05/15
      基本的な機能の実装(by 1764087 木村慶豪)
*/
int search_array_index_num(double *num_array, int array_size, double num);

/*
  @brief 配列を昇順、降順に並び替える

  バブルソートを使用し、配列を昇順または降順に並び替え、他の配列に出力する
  @param [in] *num_array(double) 並び替え前の配列
  @param [in][out] *sorted_num_array(double) 並び替え後の配列
  @param [in] array_size(int) 配列サイズ
  @return 並び替え後の配列を返す。
  @attention array_sizeは配列の要素数と等しくならなければならない
             num_arrayとsorted_num_arrayのサイズは等しくなければならない。
             関数中で昇順か降順かを入力する。 昇順 -> 1, 降順 -> -1
  @per 更新履歴
    - 2018/05/15
      基本的な機能の実装(by 1764087 木村慶豪)
*/
double *sort_array(double *num_array, double *sorted_num_array, int array_size);

/*
  @brief 配列の順序を逆にする

  入力された配列の逆順を他の配列に出力する
  @param [in] *num_array(double) 並び替え前の配列
  @param [in][out] *sorted_num_array(double) 並び替え後の配列
  @param [in] array_size(int) 配列サイズ
  @return (double *) 並び替え後の配列のポインタを返す
  @attention array_sizeは配列の要素数と等しくならなければならない
             num_arrayとsorted_num_arrayのサイズは等しくなければならない。
  @per 更新履歴
    - 2018/05/15
      基本的な機能の実装(by 1764087 木村慶豪)
*/
double *inverse_array(double *num_array, double *sorted_num_array, int array_size);

/*
  @brief 配列のコピーを他の配列に出力

  入力された配列のコピーを他の配列に出力する
  @param [in] *num_array(double) コピー元の配列
  @param [in][out] *copied_num_array(double) コピー先の配列
  @param [in] array_size(int) 配列サイズ
  @return (double *) コピー先の配列のポインタを返す
  @attention array_sizeは配列の要素数と等しくならなければならない
             sorted_num_arrayのサイズがnum_arrayのサイズより大きくならなければならない。
  @per 更新履歴
    - 2018/05/15
      基本的な機能の実装(by 1764087 木村慶豪)
*/
double *copy_array(double *num_array, double *sorted_num_array, int array_size);

/********************2. 配列演算**********************/

/*
  @brief 配列のシフト演算、ローテート演算

  配列の各要素をシフト演算、ローテート演算を行う, シフトして空いた部分には0を入れる
  @param [in] *num_array(double) 演算対象の配列
  @param [in] array_size(int) 配列サイズ
  @param [in] shift_size(int) 移動するシフト量
  @param [out] *shifted_array(double) シフトまたはローテートされた配列
  @return (double *) シフト演算後の配列
  @attention array_sizeは配列の要素数と等しくならなければならない, shift_size <= array_size
  @per 更新履歴
    - 2018/05/22
      基本的な機能の実装(by 1764087 木村慶豪)
*/
double *shift_array(double *num_array, int array_size, int shift_size);

/*
  @brief 配列と配列の加算

  配列の各インデックスに対し、加算を行い、他の配列に出力する。
  @param [in] *num_array1(double) 演算対象の配列の1つめ
  @param [in] *num_array2(double) 演算対象の配列の2つめ
  @param [in] array_size(int) 配列サイズ
  @param [in][out] *res_array(double) 加算結果を格納するための配列
  @return (double *) 加算結果を格納した配列のポインタを返す
  @attention num_array1とnum_array2のサイズはarray_sizeと等しくなければならない
  @per 更新履歴
    - 2018/05/15 作成
      基本的な機能の実装(by 1764087 木村慶豪)
*/
double *sum_arrays(double *num_array1, double *num_array2, int array_size, double *res_array);

/*
  @brief 配列と配列の減算

  配列の各インデックスに対し、減算を行い、他の配列に出力する。
  @param [in] *num_array1(double) 演算対象の配列の1つめ
  @param [in] *num_array2(double) 演算対象の配列の2つめ
  @param [in] array_size(int) 配列サイズ
  @param [in][out] *res_array(double) 減算結果を格納するための配列
  @return (double *) 減算結果を格納した配列のポインタを返す
  @attention num_array1とnum_array2のサイズはarray_sizeと等しくなければならない
  @per 更新履歴
    - 2018/05/15
      基本的な機能の実装(by 1764087 木村慶豪)
*/
double *dif_arrays(double *num_array1, double *num_array2, int array_size, double *res_array);

/*
  @brief 配列の絶対値計算

  配列の各要素に対し絶対値を計算する
  @param [in][out] *num_array(double) 演算対象の配列
  @param [in] array_size(int) 配列サイズ
  @param [out] *array(double) 演算後の配列
  @return (double *) 絶対値演算後の配列
  @attention array_sizeは配列の要素数と等しくならなければならない
  @per 更新履歴
    - 2018/05/15
      基本的な機能の実装(by 1764087 木村慶豪)
*/
double *abs_array(double *num_array, int array_size);

/*
  @brief 配列の総和計算

  配列の各要素を足し合わせた結果を返す
  @param [in] *num_array(double) 演算対象の配列
  @param [in] array_size(int) 配列サイズ
  @param [out] sum(double) 合計値
  @return (double) 総和計算結果を返す。
  @attention array_sizeは配列の要素数と等しくならなければならない
  @per 更新履歴
    - 2018/05/15
      基本的な機能の実装(by 1764087 木村慶豪)
*/
double sum_array(double *num_array, int array_size);

/*
  @brief 配列の平均値計算

  配列の各要素の平均を返す
  @param [in] *num_array(double) 演算対象の配列
  @param [in] array_size(int) 配列サイズ
  @return (double) 平均の計算結果を返す。
  @attention array_sizeは配列の要素数と等しくならなければならない
  @per 更新履歴
    - 2018/05/15
      基本的な機能の実装(by 1764087 木村慶豪)
*/
double mean_array(double *num_array, int array_size);

/*
  @brief 配列の標準偏差計算

  配列の全要素に対する標準偏差を返す
  @param [in] *num_array(double) 演算対象の配列
  @param [in] array_size(int) 配列サイズ
  @return (double) 標準偏差の計算結果を返す。
  @attention array_sizeは配列の要素数と等しくならなければならない
  @per 更新履歴
    - 2018/05/15
      基本的な機能の実装(by 1764087 木村慶豪)
*/
double sd_array(double *num_array, int array_size);

/*
  @brief 配列の変動係数計算

  配列の全要素に対する変動係数を返す
  @param [in] *num_array(double) 演算対象の配列
  @param [in] array_size(int) 配列サイズ
  @return (double) 標準偏差の計算結果を返す。
  @attention array_sizeは配列の要素数と等しくならなければならない
  @per 更新履歴
    - 2018/05/15
      基本的な機能の実装(by 1764087 木村慶豪)
*/
double cv_array(double *num_array, int array_size);

/*
  @brief 配列の中央値算出

  配列の全要素に対する中央値を返す。ソートを行い、真ん中のインデックスの数字を返す。
  @param [in] *num_array(double) 演算対象の配列
  @param [in] array_size(int) 配列サイズ
  @return (double) 配列の中央値を返す。
  @attention array_sizeは配列の要素数と等しくならなければならない
  @per 更新履歴
    - 2018/05/15
      基本的な機能の実装(by 1764087 木村慶豪)
*/
double search_median_array(double *num_array, int array_size);

/*
  @brief 配列の条件の数字以上または以下の要素数の算出

  特定の数値number以上または以下の数値をもつ要素の数を数える。
  @param [in] *num_array(double) 演算対象の配列
  @param [in] array_size(int) 配列サイズ
  @param [in] num(double) 条件となる数字
  @param [out] counter 条件を満たす要素数をカウントする。
  @return (int) 条件を満たす要素数を返す。
  @attention array_sizeは配列の要素数と等しくならなければならない
  @per 更新履歴
    - 2018/05/15
      基本的な機能の実装(by 1764087 木村慶豪)
*/
double countif_array(double *num_array, int array_size, double number);

/*
  @brief 配列の条件の数字以上または以下の要素の総和の算出

  特定の数値以上または以下の数値をもつ要素の総和を計算する
  @param [in] *num_array(double) 演算対象の配列
  @param [in] array_size(int) 配列サイズ
  @param [in] num(double) 条件となる数字
  @param [out] sum(double) 条件を満たす要素の総和を計算する。
  @return (double) 条件を満たす要素の総和を返す。
  @attention array_sizeは配列の要素数と等しくならなければならない
  @per 更新履歴
    - 2018/05/15
      基本的な機能の実装(by 1764087 木村慶豪)
*/
double sumif_array(double *num_array, int array_size, double number);
