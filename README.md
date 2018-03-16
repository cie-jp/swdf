develop branch

git clone github.com:Shiina-tnct/CLDIA

## CLDIA (Common Library for Data Integration and Analysis)

### ライブラリ概要

1. データ統合・解析に用いられる処理群をまとめたパッケージ

### インストール方法

1. CDFライブラリをインストールする. 
2. ~/.profileに以下を記述し環境変数を設定する. 
~~~
export   CDF_LIBRARY_PATH=$HOME/usr/local/cdf36_4 #  CDFライブラリのインストールパス
export CLDIA_LIBRARY_PATH=$HOME/usr/local/cldia   #CLDIAライブラリのインストールパス
~~~
3. `make`        を実行する. 
4. `make test`   を実行する. [正常動作を検証するものであるのでスキップしても構わない. ]
5. `make install`を実行する. 
