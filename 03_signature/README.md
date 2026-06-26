# 03 RSA電子署名

OpenSSLライブラリを使用したRSA電子署名のサンプルプログラムです。

## ソフトの内容

このプログラムは、OpenSSLライブラリのEVP APIを使用してRSA電子署名の生成と検証を実装しています。C++20で作成されており、コマンドラインから以下の機能を利用できます：

- **署名生成**: 標準入力から受け取ったメッセージを秘密鍵で署名してファイルに保存
- **署名検証**: 標準入力から受け取ったメッセージを公開鍵と署名ファイルで検証
- **鍵パス指定**: `-s`で秘密鍵ファイル、`-p`で公開鍵ファイルの入出力先を指定
- **署名ファイル指定**: `-S`で署名ファイルの入出力先を指定

署名時のハッシュ関数は **SHA-256**（`EVP_sha256()`）です。

使用する鍵ペアは **02_asymmetric** で生成したものを使用します。

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
./app [-p <公開鍵パス>] [-s <秘密鍵パス>] [-S <署名ファイル>] <help|sign|verify>
```

サブコマンド：

- `help`: ヘルプ表示
- `sign`: 署名生成（メッセージは標準入力から受け取る）
- `verify`: 署名検証（メッセージは標準入力から受け取る）

例：

```bash
# 1) 署名生成（デフォルト: generate/private.key, generate/signature.bin）
echo -n "Hello World" | ./app sign

# 秘密鍵パスと署名ファイルを指定して署名生成
echo -n "Hello World" | ./app -s generate/my_private.key -sig generate/my_signature.bin sign

# 2) 署名検証（デフォルト: generate/public.key, generate/signature.bin）
echo -n "Hello World" | ./app verify

# 公開鍵パスと署名ファイルを指定して署名検証
echo -n "Hello World" | ./app -p generate/my_public.key -sig generate/my_signature.bin verify
```

OpenSSLコマンドで署名、検証する方法

```bash
# 署名生成（OpenSSLコマンド）
echo -n "Hello World" | openssl dgst -sha256 -sign generate/private.key > generate/signature.bin

# 署名検証（OpenSSLコマンド）
echo -n "Hello World" | openssl dgst -sha256 -verify generate/public.key -signature generate/signature.bin
```