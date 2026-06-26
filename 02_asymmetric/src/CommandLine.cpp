//************************************************************************* 
//
// RSA 公開鍵暗号方式
//
// コマンドライン引数の処理 ソースファイル
//
// ************************************************************************/ 

////////////////////////////
// インクルード
////////////////////////////
#include <iostream>
#include "../include/CommandLine.hpp"

////////////////////////////
// 関数定義
////////////////////////////

// ヘルプ表示
void usage(
    const std::filesystem::path& program_path
){
    const auto program_name = program_path.filename().generic_string();

    std::cout
        << "OpenSSLライブラリのRSA公開鍵暗号方式の使用方法のサンプル"        << std::endl
        << "Usage:"                                       << std::endl
        << "  " << program_name << " help"                << std::endl
        << "  " << program_name << " keygen"              << std::endl
        << "  " << program_name << " -h"                  << std::endl
        << "Arguments:"                                   << std::endl
        << "  help"                                       << std::endl
        << "    ヘルプを表示する"                         << std::endl
        << "  keygen"                                     << std::endl
        << "    キーを生成する"                           << std::endl
        << "  enc"                                     << std::endl
        << "    公開鍵で暗号化する"                         << std::endl
        << "  dec"                                     << std::endl
        << "    秘密鍵で復号化する"                         << std::endl
        << "Options:"                                     << std::endl
        << "  -h"                                         << std::endl
        << "    ヘルプを表示する"                         << std::endl
        << "  -p"                                         << std::endl
        << "    公開鍵ファイルのパスを指定する"           << std::endl
        << "  -s"                                         << std::endl
        << "    秘密鍵ファイルのパスを指定する"              << std::endl
        << "  -b"                                         << std::endl
        << "    鍵のビット数を指定する"                       << std::endl;
}