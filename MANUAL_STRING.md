## CLDIA::STRINGクラス

std::stringよりも各種データ型との変換処理を容易に行うために利用する

### 利用方法

```C++
#include"CLDIA.h"
using namespace CLDIA
```
を記述することで利用できる. 

### 関数一覧

#### 1. 初期化
```C++
STRING str1         ;//空文字列で初期化
STRING str2(10,' ') ;//10個の半角スペース' 'の文字列で初期化
STRING str3 = "hoge";//CHAR 配列"hoge"で初期化
STRING str4 =    'a';//CHAR 型     'a'で初期化
STRING str5 =     5 ;//INT4 型      5 で初期化
STRING str6 =   3.0 ;//REAL8型    3.0 で初期化
STRING str7 = epoch ;//TIME_TT2000型  で初期化
STRING str8("%04d-%02d-%02d",2017,01,15);//sprintfのフォーマットで初期化
```
</details>

#### 2. 出力
```C++
cout << str3 << endl;//stdoutに出力
cerr << str7 << endl;//stderrに出力
str8.show();         //stdoutに出力
str8.show(fp);       //ファイルポインタを指定して出力
```

#### 3. 文字列操作
```C++
//STRING str3 = str1 + str2;//str1とstr2を結合した文字列を得る. 
//str3 += str4;             //str3の末尾にstr4を付け加える. 
INT4   YYYY = 2017;
INT4   MM   =   01;
INT4   DD   =   15;
STRING date = STRING("%04d",YYYY) + "-" + STRING("%02d",MM) + "-" + STRING("%02d",DD);
cout << date << endl;
```

#### 4. 各種データ型へのキャスト
```C++
STRING      str   = "2017";
INT4        YYYY  = str;
REAL8       val   = str;
TIME_TT2000 epoch = str;
cout << YYYY  << endl;
cout << val   << endl;
cout << epoch << endl;
cout << STRING(epoch) << endl;
```
`TIME_TT2000`型へのキャストは
`"2000-01-01 00:00:00.000000000"`に対応する値を返す. 
`(TIME_TT2000)STRING("2017-05")`を指定すると, 先頭から指定項目が反映され
`"2017-05-01 00:00:00.000000000"`に相当する`TIME_TT2000`型の値が返される. 

#### 5. 文字列へのアクセス
```C++
STRING str = "hoge";

str[2] = 'G'; //通常の文字列配列と同様にアクセス可能

cout << str << endl;
cout << strlen(&str[0]) << endl;//文字列の長さを表示
//(注) 文字列の先頭ポインタを得るときは'str'ではなく必ず'&str[0]'と書くこと(演算子[]のオーバーロードにより簡易アクセスを実現しているため). 
// 以下, エラーになるコード     
// cout << strlen( str   ) << endl;
```
