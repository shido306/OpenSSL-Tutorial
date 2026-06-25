//************************************************************************* 
//
// RSA 公開鍵暗号方式
//
// 入出力 ソースファイル
//
// ************************************************************************/ 

/////////////////////////////
// インクルード
/////////////////////////////
#include <unistd.h>
#include <iostream>
#include <vector>
#include "../include/io.hpp"

/////////////////////////////
// 関数定義
/////////////////////////////

// stdinからバイナリデータを読み込む
std::vector<unsigned char> read_stdin( void ){
    std::vector<unsigned char> buf;
    unsigned char tmp[4096];
    ssize_t n;

    while ((n = read(STDIN_FILENO, tmp, sizeof(tmp))) > 0) {
        buf.insert(buf.end(), tmp, tmp + n);
    }

    if (n < 0) {
        throw "Error reading from stdin";
    }

    return buf;
}
 
// stdoutへバイナリデータを書き出す
void write_stdout(
    const std::vector<unsigned char>& data    // in: 出力するバイナリデータ
){
    for (const auto byte_value : data) {
        std::cout << byte_value;
    }
}
