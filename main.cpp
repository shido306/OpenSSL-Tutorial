#include <iostream>
#include <unistd.h>
#include <string>
#include "OpenSSLData.hpp"
#include "usage.hpp"

int main (int argc, char* argv[]){
    int opt;
    // -hオプションを追加するためにgetopt関数を使用
    while(( opt = getopt(argc, argv, "h")) != -1 ){
        switch( opt ){
            case 'h':
                usage(argv[0]);
                return 0;
            default:
                return 1;
        }
    }

    if( argc < 1 ){
        std::cerr << "no subcommand" << std::endl;
    }

    auto subcommand = std::string(argv[1]);
    if( subcommand == "help" ){
        usage(argv[0]);
        return 0;
    }
    if( subcommand == "enc" ){

    }else if( subcommand == "dec" ){

    }
}