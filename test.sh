#!/bin/bash

# /dev/urandomから16 byte(128 bit)とってhex stringにしてIVにする
iv="$(head -c 16 /dev/urandom | od -x -A n | tr -d ' \n')"
# /dev/urandomから32 byte(256 bit)とってhex stringにして鍵にする
key="$(head -c 32 /dev/urandom | od -x -A n | tr -d ' \n')"

echo "/dev/urandomから1000バイトとってbase64エンコードしたものを表示"
# /dev/urandomから1000バイトとってbase64エンコードしたものを表示
data="$(head -c 1000 /dev/urandom | base64 | tr -d '\n' | xargs echo | tee /dev/stderr)"

echo "作成した暗号化・復号化コマンドで暗号化してopensslコマンドで復号化して表示"
# 作成した暗号化・復号化コマンドで暗号化してopensslコマンドで復号化して表示
echo $data  | ./app -i "$iv" -k "$key" enc | openssl aes-256-cbc -nosalt -d -iv "$iv" -K "$key" | xargs echo

echo "opensslコマンドで暗号化して作成した暗号化・復号化コマンドで復号化して表示"
# opensslコマンドで暗号化して作成した暗号化・復号化コマンドで復号化して表示
echo $data | openssl aes-256-cbc -nosalt -e -iv "$iv" -K "$key" | ./app -i "$iv" -k "$key" dec | xargs echo


echo "作成した暗号化・復号化コマンドで暗号化して作成した暗号化・復号化コマンドで復号化して表示"
# 作成した暗号化・復号化コマンドで暗号化して作成した暗号化・復号化コマンドで復号化して表示
echo $data | ./app -i "$iv" -k "$key" enc | ./app -i "$iv" -k "$key" dec | xargs echo
