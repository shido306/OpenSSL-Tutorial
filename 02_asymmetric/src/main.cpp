//************************************************************************* 
//
// RSA 公開鍵暗号方式
//
// メイン関数 ソースファイル
//
// ************************************************************************/ 

////////////////////////////
// インクルード
////////////////////////////
#include <iostream>
#include <unistd.h>
#include "../include/CommandLine.hpp"

////////////////////////////
// 関数定義
////////////////////////////

// メイン関数
int main (int argc, char* argv[]){
    const auto program_path = argv[0];
    int opt;

    while((opt = getopt(argc, argv, "h")) != -1 ){
        switch( opt ){
            case 'h':   // ヘルプオプション
                usage(program_path);
                return 0;
            default:
                return 1;
        }
    }    

    if( argc - optind < 1 ){
        std::cerr << "no subcommand" << std::endl;
        return 1;
    }
        auto subcommand = std::string(argv[optind]);
    if( subcommand == "help" ){
        usage(program_path);
        return 0;
    }

    return 0;
}