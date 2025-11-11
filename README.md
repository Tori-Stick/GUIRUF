# GUIRUF
GUIRUF (GUI library of Removed Unneeded Functions)
読み方はジラフです。必要最低限の機能しか存在しない、GUIアプリケーション制作のためのツールです。

---
[![License](https://img.shields.io/badge/License-Boost_1.0-lightblue.svg)](https://www.boost.org/LICENSE_1_0.txt)
<img src="https://img.shields.io/badge/-Ubuntu-E95420.svg?logo=ubuntu&style=plastic"> <img src="https://img.shields.io/badge/-C++-00599C.svg?logo=cplusplus&style=plastic"> <img src="https://img.shields.io/badge/-Cmake-064F8C.svg?logo=cmake&style=plastic">

## インストール

1. GitHubのURL、または以下のコマンドからライブラリのtar.gzファイルをダウンロードする。
```
wget https://github.com/Tori-Stick/GUIRUF/raw/refs/heads/main/GUIRUF-1.0.1.tar.gz
```

2. tar.gzファイルを解凍する
```
tar zxvf GUIRUF-*
```

3. インストールする
```
cd GUIRUF
make
sudo make install
```

## 実行方法

コマンドラインで実行したいとき
```
g++ main.cpp -o main -lGUIRUF -lX11 
./main
```

CMakeLists.txtを使って実行したいとき
```
include_directories(/usr/local/include)
link_directories(/usr/local/lib)

add_executable(main main.cpp)
target_link_libraries(main GUIRUF X11)
```

## 使用方法

以下のコマンドで**ウィンドウを作成します**。
引数にはウィンドウサイズが入りますが、
何も入れられていない場合は全画面で表示されます。
```
#include <GUIRUF/guiruf.hpp>

int main(){
    GUIRUF guiruf(500,500);
}
```

<br>

**ウィンドウ上に描画したいとき**は以下のコードが使えます。
eraseの既定値はfalseです。
eraseがfalseだと、黒、
eraseがtrueだと、白で描画します。

- `FillWindow(bool erase)`
- `DrawPoint(int x, int y, bool erase)`
- `DrawLine(int x1, int y1, int x2, int y2, bool erase)`

`FillWindow`はウィンドウを一色で塗りつぶします。
`DrawPoint`は、ウィンドウ上の(x,y)の位置に1pxの点を描画します。
`DrawLine`は、始点を(x1,y1)、終点を(x2,y2)とする幅1pxの線を
ウィンドウ上に描画します。

<br>

**ウィンドウ上での操作を取得したいとき**は、以下のコードが使えます。
ただし、これらのコードは**ループ内で使用することを推奨しています**。

- `UpdateEvents()`
- `IsMouseClicked()`
- `IsMouseReleased()`
- `LocateMouse()`
- `IsKeyPressed()`
- `IsKeyPressed(int *keycode)`
- `IsKeyReleased()`
- `IsKeyReleased(int *keycode)`

`UpdateEvents`はマウス操作やキーボード操作の情報を取得するための
コマンドです。基本的にはこのコードはループ処理の開始時に記入しておきます。
`IsMouseClicked`,`IsMouseReleased`はマウスがクリックされたとき、
そしてマウスクリック状態から離したときに`true`を返します。
`LocateMouse()`はマウスの位置を返します。戻り値は
`std::vector<int> {x,y}`です。
`IsKeyPressed`,`IsKeyReleased`はキーボードが押されたとき、そして
キーボードが離されたときに`true`を返します。引数`keycode`を入れておくと、
押したキーボードの情報がその変数内に入ります。

## 更新履歴

* 2025/11/12 README.md, makafileを更新、NOTICEを追加

## License

GUIRUF is licensed under the [Boost Software License 1.0](./LICENSE).

This project uses the X11 libraries, which are licensed under the MIT/X11-style license.
See [NOTICE](./NOTICE) for details.
