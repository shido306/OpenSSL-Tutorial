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
#include "../include/Crypto.hpp"

////////////////////////////
// 関数定義
////////////////////////////

// メイン関数
int main (int argc, char* argv[]){
    const auto program_path = argv[0];
    std::string priv_path = "generate/private.key";     // 秘密鍵のパス：デフォルト
    std::string pub_path  = "generate/public.key";      // 公開鍵のパス：デフォルト
    int bits = 2048;                                    // 鍵のビット数：デフォルト
    int opt;

    while((opt = getopt(argc, argv, "hp:s:b:")) != -1 ){
        switch( opt ){
            case 'h':   // ヘルプオプション
                usage(program_path);
                return 0;
            case 'p':   // 公開鍵のパス指定オプション
                pub_path = std::string(optarg);
                break;
            case 's':   // 秘密鍵のパス指定オプション
                priv_path = std::string(optarg);
                break;
            case 'b':   // 鍵のビット数指定オプション
                bits = std::stoi(optarg);
                break;
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
            // 鍵のペアを出力
            generateKeypair(priv_path, pub_path, bits);
        }else if( subcommand == "enc" ){
            // 公開鍵で暗号化
            encryptPubKey(pub_path);
        }
    }catch(const char* error) {
        std::cerr << error << std::endl;
        return 1;
    }

    return 0;
}