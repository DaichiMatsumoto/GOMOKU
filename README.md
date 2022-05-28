# C言語五目並べ競プロへようこそ
これは、C言語で記述される五目並べプログラムを対戦させる、有志競技プログラミングプロジェクトです。

早速今回の五目並べのルールとマスタープログラムの挙動を説明します。
本プログラムでは複数のCファイルのリンクコンパイルを行います。

### 【リンクコンパイルについて】
複数のCファイルをコンパイルする方法で、一つのCファイルをコンパイルする場合と手順は変わりません。

例えば、以下3つの。cファイルがあるとします。

- test.c

    関数 `example()` が記述されている。

- hoge.c

    関数 `noname()` が記述されている。

- main.c

    メイン関数が記述されている。メイン関数では、`test.c`に記述されている関数 `example()` と、`hoge.c`に記述されている関数 `noname()` を呼び出して使用している。
    
上記3ファイルは同一ディレクトリに存在しているが、main関数がその他のファイルに存在する関数を呼び出している以外に依存関係はない。
この場合、通常通り1ファイルずつコンパイルしても当然 `main.c` ファイルに存在しない関数(`example()`と`noname()`)を使用しているため、コンパイルエラーとなる。

そこで、リンクコンパイルを下記で行う。
```    
gcc -o test main.c test.c hoge.c
```
上記の様にコンパイルすることで、3ファイルがリンクされた状態でコンパイルが通り、この例では `test` という実行可能ファイルが生成される。

### 【ルール説明】
- 通常の五目並べと変わらないが、番目は10×10のミニチュアサイズである。
- 先攻は「O」後攻は「X」空欄は「-」で表示されている。
- 初期状態は、真ん中４マスにお互いの駒が交互に置かれた状態からスタート。
- 同じところに置いた場合はその旨の警告が出て、もう一度置き直しとなる。特にペナルティはない。
- 5こ並べたら勝ち。勝敗がつかずに全マスが埋まった場合は、引き分け。デスマッチのない平和な世界。
- 以下実際のゲーム盤面出力。初期状態。ご参考まで。

```
 ###  # 1  # 2  # 3  # 4  # 5  # 6  # 7  # 8  # 9  #10  ###
 # 1   -    -    -    -    -    -    -    -    -    -   # 1
 # 2   -    -    -    -    -    -    -    -    -    -   # 2
 # 3   -    -    -    -    -    -    -    -    -    -   # 3
 # 4   -    -    -    -    -    -    -    -    -    -   # 4
 # 5   -    -    -    -    O    X    -    -    -    -   # 5
 # 6   -    -    -    -    X    O    -    -    -    -   # 6
 # 7   -    -    -    -    -    -    -    -    -    -   # 7
 # 8   -    -    -    -    -    -    -    -    -    -   # 8
 # 9   -    -    -    -    -    -    -    -    -    -   # 9
 #10   -    -    -    -    -    -    -    -    -    -   #10
 ###  # 1  # 2  # 3  # 4  # 5  # 6  # 7  # 8  # 9  #10  ###
```
### 【同梱物内容】
- master.c
    
    ゲームを管理しているマスタープログラム。
    プレイヤーの順番の管理から勝敗の判定やら反則やらを管理している。
    
    対戦時も同様のものを使用する。ソースコードは見えるようにしてあるので、各自対戦プログラムを作成する際参照されたい。
    
- player1.o player2.o

    各自作成してもらう対戦プログラムの、動作チェック用リロケータブルファイル。
    oファイルは、cファイルをコンパイルしてできたもの。
    ただし実行ファイル(.exe等)とは異なり、単体で実行できない。

    .cファイル同様、以下のようにコンパイルすることで実行可能となる。
    ```
    gcc -o test player2.o
    ```
    
    このファイルには、著者が作成した対戦用プログラムがコンパイルされている。(１も２もどちらも一緒の内容)
    各自player.c player2.c を作成した後、
    ```        
    gcc -o test player1.c player2.o
    ```
    と、片方に.oファイルを含めてコンパイルすれば、動作確認用対戦プログラムと対戦できるようになる。

    動作確認ついでに、対戦してみてください。

- player1rand.c player2rand.c
    
    各自作成すべきプログラムの一例。
    空いてる所にランダムに駒を置く対戦プログラム。内容は両ファイル同様。
    
### 【作成プログラム内容説明】
まず、player1rand.c ファイルの中身を解説します。

```
void player1(int ground[12][12], int *strategy_x, int *strategy_y)
```

これが各自作るべき対戦プログラムの中のトップ呼び出し関数。

- 関数名

    `player1(int[12][12], *int, *int)` or `player2(int[12][12], *int, *int)`
    
    ファイル名は任意、関数名はこれを厳守のこと。

- 第一引数

    盤面の情報。毎ターン新しい現在の盤面情報が与えられる。12×12の二重配列であり、一番外回り一周は枠として使用され、フィールドではない。
    
    フィールドは、0−11の配列番号のうちの、1−10のみとなる。
    
    x、y座標は、
    ```
    ground[y座標][x座標]
    ```
    となる。
    
    player1が先攻、player2が後攻でプレイしたとすると、player1は `O` player2は `X` で表示されるが、これは実際のワールドの二重配列内では、整数処理されており、player1の駒は「１」player2の駒は「２」空きマスは「０」それ以外のフィールド外は「−１」で表示されている。
            
- 第二引数
    
    ポインタ。自分がそのターンに置く駒のx座標。これをを直接書き換えることで、マスタープログラムの中の実体も書き換えられる。

- 第三引数
  
    自分がそのターンに置く駒のy座標。

- 戻り値
    
    なし

player1とplayer2で二つ作成するが、これは先行後攻の入れ替えを行うためであり、戦略を二つ考えなければならない必要性はない。
中身は全く同じでOK。(確かに、先攻有利なゲームなため、勝つために先攻と後攻の戦略を少し変えることは得策かもしれない。但し今回はオセロのスタートのように、中心４マスをお互いの駒で交互に二つずつ埋めた状態から始めるため、あまり先攻後攻に有利不利はないかもしれない。)

### 【作成時のコーディングルール】
- フィールド変数(関数の外側で使う変数)には、各自ユニークな(一意の)単語を、接頭辞とし明示すること。
例えば、
    ```
    int gamecount
    ```
    をフィールドで宣言する場合、上記ではNG
    ```
    int Bakkarucorn_gamecount
    ```
    などとしてほしい。少々冗長になるが、コンフリクトを避けるためには止むを得ない。

- 乱数を使用する場合、rand関数とsrand関数を使うが、srand関数に関してはmaster側ですでに乱数シードを初期化しているため、自身のプログラムで使う場合はsrand関数を使用せずにrand関数使っても、乱数を得られる。むしろ、srandを自身のプログラムで再実行すると、予期せぬエラーを引き起こす原因となる。

### 【DEBUGモードについて】
`master.c`ファイルの18行目に、
```
//#define DEBUG
```
のコメントアウトがある。これは、コメントアウトしたまま対戦プログラムと一緒にリンクコンパイルすると、

```
>$ ./test
 ###  # 1  # 2  # 3  # 4  # 5  # 6  # 7  # 8  # 9  #10  ###
 # 1   -    -    -    -    -    -    -    -    -    -   # 1
 # 2   -    -    -    -    -    -    O    -    X    -   # 2
 # 3   -    -    -    -    -    -    -    X    -    -   # 3
 # 4   -    -    -    -    -    -    X    O    -    -   # 4
 # 5   -    -    -    -    O    X    -    -    -    -   # 5
 # 6   -    -    -    -    X    O    -    -    -    -   # 6
 # 7   -    -    -    -    -    -    -    -    -    -   # 7
 # 8   -    -    -    -    -    -    -    -    -    -   # 8
 # 9   -    -    -    -    -    -    O    -    -    -   # 9
 #10   -    -    -    -    -    -    -    -    -    -   #10
 ###  # 1  # 2  # 3  # 4  # 5  # 6  # 7  # 8  # 9  #10  ###
player2(X) WIN
```
上記のように、最終結果だけが表示されて終了する。
一方、コメントアウトをとるとDEBUGモードになり、一手一手の対戦状況がすべてコマンドラインに表示されるようになる。
実装中は、これを駆使するように。

### 【その他コーディング時における注意事項】
無限ループとセグメンテーションフォルトに留意しつつ、自由に楽しくコーディングするよう心がけてください。


### 【著作権について】
製作者の完全オリジナルであり、著作権は製作者にあるが、
これを受け取った者はこのプログラムを自由に配布、改変してもよいものとする。

以上
