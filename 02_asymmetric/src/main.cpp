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
#include "../include/GenerateKey.hpp"

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

    try{
        if( subcommand == "keygen" ){
            std::string priv_path = "generate/private.key";     // 秘密鍵のパス：デフォルト
            std::string pub_path  = "generate/public.key";      // 公開鍵のパス：デフォルト
            int bits = 2048;                                    // 鍵のビット数：デフォルト

            // 鍵のペアを出力
            generateKeypair(priv_path, pub_path, bits);
        }
    }catch(const char* error) {
        std::cerr << error << std::endl;
        return 1;
    }

    return 0;
}