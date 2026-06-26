# OpenSSL-Tutorial

OpenSSLライブラリを使用したRSA公開鍵暗号方式のサンプルプログラムです。

## ソフトの内容

このプログラムは、OpenSSLライブラリのEVP APIを使用してRSA鍵生成と公開鍵暗号化を実装しています。C++20で作成されており、コマンドラインから以下の機能を利用できます：

- **鍵生成**: RSA秘密鍵・公開鍵ペアをPEM形式で生成
- **公開鍵暗号化**: 標準入力から受け取った平文を公開鍵で暗号化して標準出力へ出力
- **鍵パス指定**: `-s`で秘密鍵ファイル、`-p`で公開鍵ファイルの入出力先を指定
- **鍵長指定**: `-b`でRSA鍵長（ビット数）を指定

暗号化時のパディング方式は **OAEP**（`RSA_PKCS1_OAEP_PADDING`）です。

## 開発環境

| 項目 | バージョン |
|--------|--------|
| OS | Ubuntu 26.04 LTS |
| OpenSSL | 3.5.5 |
| Compiler | g++ 15.2.0 |
| C++ Standard | C++20 |

本プロジェクトは OpenSSL 3.5.5 で開発・動作確認を行っています。
他のバージョンでは追加修正が必要になる可能性があります。

## コンパイル方法

### 必要なもの

- g++（C++20対応版）
- OpenSSLライブラリと開発ヘッダ
- make

### Ubuntu/Debianの場合

```bash
sudo apt update
sudo apt install build-essential libssl-dev
```

### コンパイル手順

```bash
make
```

このコマンドで`app`という実行ファイルが生成されます。

その他のmakeコマンド：

```bash
make clean   # ビルド成果物を削除
make re      # クリーンしてから再ビルド
```

## 使用方法

```bash
./app [-p <公開鍵パス>] [-s <秘密鍵パス>] [-b <鍵長>] <help|keygen|enc|dec>
```

サブコマンド：

- `help`: ヘルプ表示
- `keygen`: 鍵ペア生成
- `enc`: 公開鍵暗号化（平文は標準入力から受け取る）
- `dec`: 秘密鍵復号化（暗号文は標準入力から受け取る）

例：

```bash
# 1) 鍵生成（デフォルト: 2048bit, generate/private.key, generate/public.key）
./app keygen

# 2) 平文を公開鍵で暗号化してbase64化
echo -n "hogehoge" | ./app enc | base64 > enc.dat

# 公開鍵のパスを指定して暗号化
echo -n "hogehoge" | ./app -p generate/my_public.key enc | base64 > enc.dat

# 3) 暗号文を秘密鍵で復号化
cat enc.dat | base64 -d | ./app dec
```

鍵パスや鍵長を指定する例：

```bash
# 3072bit鍵を別パスに生成
./app -b 3072 -s generate/my_private.key -p generate/my_public.key keygen

# 指定した公開鍵で暗号化
echo -n "test" | ./app -p generate/my_public.key enc | base64 > enc.dat

# 秘密鍵パスを指定して復号化
cat enc.dat | base64 -d | ./app -s generate/my_private.key dec
```

OpenSSLコマンドで暗号化、復号化する方法

```bash
# 暗号化（OpenSSLコマンド）
echo -n "hogehoge" | openssl pkeyutl -encrypt -pubin -inkey generate/public.key -pkeyopt rsa_padding_mode:oaep | base64

# 復号（OpenSSLコマンド）
cat enc.dat | base64 -d | openssl pkeyutl -decrypt -inkey generate/private.key -pkeyopt rsa_padding_mode:oaep
```
