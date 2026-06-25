#include <iostream>
#include <unistd.h>
#include <string>
#include "../include/OpenSSLData.hpp"
#include "../include/CommandLine.hpp"
#include "../include/Printer.hpp"
#include "../include/Crypto.hpp"

int main (int argc, char* argv[]){
    const auto program_path = argv[0];
    byte_stream iv(BLOCK_SIZE, 0);
    byte_stream key(128 / 8, 0);
    int opt;
    ///////////////
    // オプション処理
    ///////////////
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

    ///////////////
    // データの入力
    ///////////////
    byte_stream data;
    while (true) {
        auto byte_value = getc(stdin);
        if (byte_value == EOF) {
            break;
        }
        data.emplace_back(byte_value);
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
        if( subcommand == "enc" ){
            switch (key.size() * 8) {
                case 128:
                    print_data_while_encoding<128>(key, data, iv, encrypt<128>);
                    break;
                case 192:
                    print_data_while_encoding<192>(key, data, iv, encrypt<192>);
                    break;
                case 256:
                    print_data_while_encoding<256>(key, data, iv, encrypt<256>);
                    break;
                default:
                    std::cout << "invalid key type" << std::endl;
                    break;
            }
        }else if( subcommand == "dec" ){
            switch (key.size() * 8) {
                case 128:
                    print_data_while_encoding<128>(key, data, iv, decrypt<128>);
                    break;
                case 192:
                    print_data_while_encoding<192>(key, data, iv, decrypt<192>);
                    break;
                case 256:
                    print_data_while_encoding<256>(key, data, iv, decrypt<256>);
                    break;
                default:
                    std::cout << "invalid key type" << std::endl;
                    break;
            }
        }else{
            std::cerr << "unknown command: " << subcommand << std::endl;
            return 1;
        }
    }catch(const char* error) {
        std::cerr << error << std::endl;
        return 1;
    }
}