## CLDIAを用いた行列演算(C++用)

1. 実行列・複素行列の計算が可能. 
2. 現在はまだ外部インターフェースがまだ不十分であるが, 基本機能は利用してよい. 
3. 対角和, 行列式, 階数, 一般逆行列の移植を早急に進める. 

### 実行列関連のサンプルプログラム

#### 1. 行列の初期化
<details>
<summary>1.1 行数・列数を指定した行列の0による初期化</summary>

```C++
#include<iostream>
#include"CLDIA.h"

using namespace std;

int main(void){
	RMatrix A(4,6);     //4行6列の実行列を作成する. 全ての要素は0で初期化される. 
	cout << A << endl;  //行列の情報(行数, 列数, 行列成分)を表示する. 
	return 0;
}
```
</details>



<details>
<summary>1.2 1x1行列(スカラー)の0による初期化</summary>

```C++
#include<iostream>
#include"CLDIA.h"

using namespace std;

int main(void){
	RMatrix A;          //1行1列の実行列を作成する. 要素は0で初期化される. 
	cout << A << endl;  //行列の情報を表示する. 
	return 0;
}

```
</details>

<details>
<summary>1.3 1x1行列(スカラー)の値を指定した初期化</summary>

```C++
#include<iostream>
#include"CLDIA.h"

using namespace std;

int main(void){
	RMatrix A = 3.0;    //1行1列の実行列を作成する. 要素は3.0で初期化される. 
	cout << A << endl;  //行列の情報を表示する. 
	return 0;
}

```
</details>

<details>
<summary>1.4 row行col列の単位行列(対角成分:1, 非対角成分:0)を作成</summary>

```C++
#include<iostream>
#include"CLDIA.h"

using namespace std;

int main(void){
	RMatrix A = RMatrix::identity(4,6); //4行6列の単位行列を作成する. 
	cout << A << endl;                  //行列の情報を表示する. 
	return 0;
}

```
</details>

<details>
<summary>1.4 row行col列のランダム行列(各成分は標準正規分布に従う乱数)を作成</summary>

```C++
#include<iostream>
#include"CLDIA.h"

using namespace std;

int main(void){
	RMatrix A = RMatrix::random(4,6);   //4行6列の単位行列を作成する. 
	cout << A << endl;                  //行列の情報を表示する. 
	return 0;
}

```
</details>

#### 2. 行列の情報(行数と列数)の取得
<details>
<summary>2.1 行列の行数, 列数を取得</summary>

```C++
#include<iostream>
#include"CLDIA.h"

using namespace std;

int main(void){
	RMatrix A(4,6);
	cout << A.get_row() << endl; //行列の行数を表示する. 
	cout << A.get_col() << endl; //行列の列数を表示する. 
	return 0;
}

```
</details>

<details>
<summary>2.2 行列のi行j列の要素を取得(0行0列からカウント)</summary>

```C++
#include<iostream>
#include"CLDIA.h"

using namespace std;

int main(void){
	RMatrix A(4,6);
	cout << A[2][3] << endl; //行列の2行3列の要素を表示する. 
	return 0;
}

```
</details>

<details>
<summary>2.3 行列のi行j列の要素を設定(0行0列からカウント)</summary>

```C++
#include<iostream>
#include"CLDIA.h"

using namespace std;

int main(void){
	RMatrix A(4,6);
	
	A[2][3] = 5.0;     //行列の2行3列の要素を5.0に設定する. 
	cout << A << endl; //行列の情報を表示する. 
	return 0;
}

```
</details>

#### 3. 行列の基本処理
<details>
<summary>3.01 代入処理</summary>

```C++
#include<iostream>
#include"CLDIA.h"

using namespace std;

int main(void){
	RMatrix A = RMatrix::random(4,6);
	RMatrix B;
	
	B = A;             //行列AをBにコピーする.  
	cout << A << endl; //行列Aの情報を表示する. 
	cout << B << endl; //行列Bの情報を表示する. 
	return 0;
}

```
</details>

<details>
<summary>3.02 加算処理(行列同士の加算)</summary>

```C++
#include<iostream>
#include"CLDIA.h"

using namespace std;

int main(void){
	RMatrix A = RMatrix::random(4,6);
	RMatrix B = RMatrix::random(4,6);
	cout << (A + B) << endl; //AとBの加算結果を表示する. 
	// C  = A + B
	// A  = A + B 
	// A += B     なども同様に扱える. 
	return 0;
}

```
</details>

<details>
<summary>3.03 減算処理(行列同士の減算)</summary>

```C++
#include<iostream>
#include"CLDIA.h"

using namespace std;

int main(void){
	RMatrix A = RMatrix::random(4,6);
	RMatrix B = RMatrix::random(4,6);
	cout << (A - B) << endl; //AとBの減算結果を表示する. 
	// C  = A - B
	// A  = A - B 
	// A -= B     なども同様に扱える. 
	return 0;
}

```
</details>

<details>
<summary>3.04 乗算処理(行列同士の乗算)</summary>

```C++
#include<iostream>
#include"CLDIA.h"

using namespace std;

int main(void){
	RMatrix A = RMatrix::random(4,6);
	RMatrix B = RMatrix::random(6,8);
	cout << (A * B) << endl; //AとBの乗算結果を表示する. 
	// C  = A * B
	// A  = A * B 
	// A *= B     なども同様に扱える. 
	return 0;
}

```
</details>

<details>
<summary>3.05 加算処理(行列と数の加算)</summary>

```C++
#include<iostream>
#include"CLDIA.h"

using namespace std;

int main(void){
	RMatrix A = RMatrix::random(4,6);
	RMatrix b = 3.0;
	cout << (A + b) << endl; //各成分について(Aij = Aij + b)を実行し, 結果を表示する. 
	cout << (b + A) << endl; //各成分について(Aij = b + Aij)を実行し, 結果を表示する.  
	return 0;
}

```
</details>

<details>
<summary>3.06 減算処理(行列と数の減算)</summary>

```C++
#include<iostream>
#include"CLDIA.h"

using namespace std;

int main(void){
	RMatrix A = RMatrix::random(4,6);
	RMatrix b = 3.0;
	cout << (A - b) << endl; //各成分について(Aij = Aij - b)を実行し, 結果を表示する. 
	cout << (b - A) << endl; //各成分について(Aij = b - Aij)を実行し, 結果を表示する. 
	return 0;
}

```
</details>

<details>
<summary>3.07 乗算処理(行列と数の乗算)</summary>

```C++
#include<iostream>
#include"CLDIA.h"

using namespace std;

int main(void){
	RMatrix A = RMatrix::random(4,6);
	RMatrix b = 3.0;
	cout << (A * b) << endl; //各成分について(Aij = Aij * b)を実行し, 結果を表示する. 
	cout << (b * A) << endl; //各成分について(Aij = b * Aij)を実行し, 結果を表示する. 
	return 0;
}

```
</details>

<details>
<summary>3.08 除算処理(行列と数の除算)</summary>

```C++
#include<iostream>
#include"CLDIA.h"

using namespace std;

int main(void){
	RMatrix A = RMatrix::random(4,6);
	RMatrix b = 3.0;
	cout << (A / b) << endl; //各成分について(Aij = Aij / b)を実行し, 結果を表示する. 
	return 0;
}

```
</details>

<details>
<summary>3.09 乗算処理(行列の成分同士の乗算)</summary>

```C++
#include<iostream>
#include"CLDIA.h"

using namespace std;

int main(void){
	RMatrix A = RMatrix::random(4,6);
	RMatrix B = RMatrix::random(4,6);
	cout << (A % B) << endl; //各成分について(Aij * Bij)を実行し, 結果を表示する. 
	return 0;
}

```
</details>

<details>
<summary>3.10 除算処理(行列の成分同士の除算)</summary>

```C++
#include<iostream>
#include"CLDIA.h"

using namespace std;

int main(void){
	RMatrix A = RMatrix::random(4,6);
	RMatrix B = RMatrix::random(4,6);
	cout << (A / B) << endl; //各成分について(Aij / Bij)を実行し, 結果を表示する. 
	return 0;
}

```
</details>

<details>
<summary>3.11 行列の縦結合</summary>

```C++
#include<iostream>
#include"CLDIA.h"

using namespace std;

int main(void){
	RMatrix A = RMatrix::random(4,6);
	RMatrix B = RMatrix::random(7,6);
	cout << (A & B) << endl; //AとBを縦に結合し, 結果を表示する. 
	return 0;
}

```
</details>

<details>
<summary>3.12 行列のi行目の横ベクトルの抽出</summary>

```C++
#include<iostream>
#include"CLDIA.h"

using namespace std;

int main(void){
	RMatrix A = RMatrix::random(4,6);
	cout << (A & 2) << endl; //Aの2行目の横ベクトルを取り出し, 結果を表示する. 
	cout << (2 & A) << endl; //Aの2行目の横ベクトルを取り出し, 結果を表示する(上と同じ). 
	return 0;
}

```
</details>

<details>
<summary>3.13 行列の横結合</summary>

```C++
#include<iostream>
#include"CLDIA.h"

using namespace std;

int main(void){
	RMatrix A = RMatrix::random(4,6);
	RMatrix B = RMatrix::random(4,8);
	cout << (A | B) << endl; //AとBを横に結合し, 結果を表示する. 
	return 0;
}

```
</details>

<details>
<summary>3.14 行列のj列目の縦ベクトルの抽出</summary>

```C++
#include<iostream>
#include"CLDIA.h"

using namespace std;

int main(void){
	RMatrix A = RMatrix::random(4,6);
	cout << (A | 2) << endl; //Aの2列目の縦ベクトルを取り出し, 結果を表示する. 
	cout << (2 | A) << endl; //Aの2列目の縦ベクトルを取り出し, 結果を表示する. 
	return 0;
}

```
</details>

<details>
<summary>3.15 転置行列の取得</summary>

```C++
#include<iostream>
#include"CLDIA.h"

using namespace std;

int main(void){
	RMatrix A = RMatrix::random(4,6);
	cout << ~A << endl; //Aの転置行列を作成し, 結果を表示する. 
	return 0;
}

```
</details>

<details>
<summary>3.16 逆行列の取得</summary>

```C++
#include<iostream>
#include"CLDIA.h"

using namespace std;

int main(void){
	RMatrix A = RMatrix::random(5,5);
	cout << !A      << endl; //Aの逆行列を作成し, 結果を表示する. 
	cout << !A *  A << endl; //逆行列の定義より, 単位行列となる. 
	cout <<  A * !A << endl; //逆行列の定義より, 単位行列となる. 
	return 0;
}

```
</details>

<details>
<summary>3.17 縦ベクトルからその要素を対角成分とする対角行列を取得</summary>

```C++
#include<iostream>
#include"CLDIA.h"

using namespace std;

int main(void){
	RMatrix v = RMatrix::random(5,1);
	cout << v.diag() << endl; //vの要素をもつ対角行列を作成し, 結果を表示する. 
	return 0;
}

```
</details>

<details>
<summary>3.18 非対角成分を0にした行列を作成</summary>

```C++
#include<iostream>
#include"CLDIA.h"

using namespace std;

int main(void){
	RMatrix A = RMatrix::random(5,5);
	cout << A.diag() << endl; //Aの非対角要素を0とした行列を作成し, 表示する. 
	return 0;
}

```
</details>

#### 4. 行列の発展的な演算
<details>
<summary>4.01 行列の特異値分解</summary>

```C++
#include<iostream>
#include"CLDIA.h"

using namespace std;

int main(void){
	RMatrix A = RMatrix::random(5,7);
	RMatrix s;//特異値を格納する縦ベクトル
	RMatrix U;//右特異ベクトル群
	RMatrix V;//左特異ベクトル群
	cout << A << endl; //Aを表示する. 
	cout << U * s.diag() * ~V << endl; //特異値分解の定義より, これはAに一致する. 
	cout << ~U * U << endl;            //特異ベクトルの直交性より, 単位行列となる. 
	cout << ~V * V << endl;            //特異ベクトルの直交性より, 単位行列となる. 
	return 0;
}

```
</details>

<details>
<summary>4.02 連立方程式の解(正方行列, ランク落ちがない場合)</summary>

```C++
#include<iostream>
#include"CLDIA.h"

using namespace std;

int main(void){
	RMatrix A = RMatrix::random(5,5); 
	RMatrix b = RMatrix::random(5,1); 
	RMatrix x = !A * b;               // Ax = bとなるxを求める. 
	cout << x << endl;                // xを表示する. 
	cout << ((A * x) | b) << endl;    // 等式を満たしているかを確認するために表示する. 
	return 0;
}

```
</details>

<details>
<summary>4.02 連立方程式の最小二乗解(非対称行列, ランク落ちがない場合)</summary>

```C++
#include<iostream>
#include"CLDIA.h"

using namespace std;

int main(void){
	RMatrix A = RMatrix::random(8,5); 
	RMatrix b = RMatrix::random(8,1); 
	RMatrix x = !(~A * A) * (~A * b); // |Ax - b|を最小とするxを求める. 
	cout << x << endl;                // xを表示する. 
	cout << ((A * x) | b) << endl;    // Ax = bに近い状況になっているかを確認するために表示する. 
	return 0;
}

```
</details>

<details>
<summary>4.03 重み付き最小二乗解(非対称行列, ランク落ちがない場合)</summary>

```C++
#include<iostream>
#include"CLDIA.h"

using namespace std;

int main(void){
	RMatrix A = RMatrix::random(8,5); 
	RMatrix b = RMatrix::random(8,1);
	RMatrix w(8,1);                   // 方程式の重み
	w      += 1.0;                    // 全ての重みを1.0に設定
	w[0][0] = 0.001;
	w[1][0] = 0.001;                  // 始めの3方程式の重みを小さくなるように設定
	w[2][0] = 0.002;
	RMatrix x = !(~A * w.diag() * A) * (~A * w.diag() * b); // (Ax - b)^{T} diag(w) (Ax - b)を最小とするxを求める. 
	cout << x << endl;                                      // xを表示する. 
	cout << ((A * x) | b) << endl;                          // Ax = bに近い状況になっているかを確認するために表示する. 
	// おそらく重みが相対的に大きな最後の5式で良い一致が見られるはずである. 
	return 0;
}

```
</details>



