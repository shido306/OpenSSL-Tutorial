//************************************************************************* 
//
// 署名・検証
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
        << "OpenSSLライブラリの署名・検証の使用方法のサンプル"        << std::endl
        << "Usage:"                                       << std::endl
        << "  " << program_name << " help"                << std::endl
        << "  " << program_name << " keygen"              << std::endl
        << "  " << program_name << " -h"                  << std::endl
        << "Arguments:"                                   << std::endl
        << "  help"                                       << std::endl
        << "    ヘルプを表示する"                         << std::endl
        << "  sign"                                       << std::endl
        << "    データに署名を生成する"                   << std::endl
        << "  verify"                                     << std::endl
        << "    データの署名を検証する"                   << std::endl
        << "Options:"                                     << std::endl
        << "  -h"                                         << std::endl
        << "    ヘルプを表示する"                         << std::endl
        << "  -p"                                         << std::endl
        << "    公開鍵ファイルのパスを指定する"           << std::endl
        << "  -s"                                         << std::endl
        << "    秘密鍵ファイルのパスを指定する"              << std::endl
        << "  -S"                                         << std::endl
        << "    署名ファイルのパスを指定する"              << std::endl;
}