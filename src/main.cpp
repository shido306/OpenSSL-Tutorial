#include <iostream>
#include <unistd.h>
#include <string>
#include "../include/OpenSSLData.hpp"
#include "../include/CommandLine.hpp"

int main (int argc, char* argv[]){
    const auto program_path = argv[0];
    byte_stream iv(BLOCK_SIZE, 0);
    byte_stream key(128 / 8, 0);
    int opt;
    // -hオプションを追加するためにgetopt関数を使用
    while((opt = getopt(argc, argv, "hi:k:V")) != -1 ){
        switch( opt ){
            case 'h':   // ヘルプオプション
                usage(program_path);
                return 0;
            case 'i':   // IV作成オプション
                try{
                    // 16進数の羅列に変換
                    iv = convert_hex_string(optarg);
                }catch(const std::invalid_argument& error) {
                  std::cerr << "invalid iv format" << std::endl;
                    return 1;
                }catch(const std::out_of_range& error) {
                    std::cerr << error.what() << std::endl;
                    return 1;
                }
                // 128 bitか確認
                if( iv.size() != BLOCK_SIZE ) {
                    std::cerr << "iv must be 128 bit" << std::endl;
                }
                break;
            case 'k':   // 鍵作成オプション
                try{
                    // 16進数の羅列に変換
                    key = convert_hex_string(optarg);
                }catch(const std::invalid_argument& error) {
                    std::cout << "invalid key format" << std::endl;
                    return 1;
                }catch(const std::out_of_range& error) {
                    std::cerr << error.what() << std::endl;
                    return 1;
                }
                // 128/192/256 bitか確認
                if(!(key.size() == 128 / 8 || key.size() == 192 / 8 || key.size() == 256 / 8)) {
                    std::cerr << "key size must be 128, 192 or 256 bit" << std::endl;
                }
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
    if( subcommand == "enc" ){

    }else if( subcommand == "dec" ){

    }else{
        std::cerr << "unknown command: " << subcommand << std::endl;
        return 1;
    }
}