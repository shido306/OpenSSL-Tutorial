#include <iostream>
#include "../include/CommandLine.hpp"

byte_stream convert_hex_string(
    const std::string& hex_string
){
    if (hex_string.size() % 2 != 0) {
        throw std::invalid_argument("invalid hex string");
    }

    byte_stream byte_array(hex_string.size() / 2);
    for (std::size_t i = 0; i < hex_string.size(); i += 2) {
        auto&& byte_value = static_cast<uint8_t>(
            std::stoi(hex_string.substr(i, 2), nullptr, 16)
        );
        byte_array[i / 2] = byte_value;
    }

    return byte_array;
}

void usage(const std::filesystem::path& program_path){
  const auto program_name = program_path.filename().generic_string();

  std::cout
    << "OpenSSLライブラリの使用方法のサンプル"        << std::endl
    << "Usage:"                                       << std::endl
    << "  " << program_name << " enc"                 << std::endl
    << "  " << program_name << " dec"                 << std::endl
    << "  " << program_name << " help"                << std::endl
    << "  " << program_name << " -h"                  << std::endl
    << "Arguments:"                                   << std::endl
    << "  enc"                                        << std::endl
    << "    標準入力から受け取ったデータを暗号化し、" << std::endl
    << "    標準出力へ出力する"                       << std::endl
    << "  dec"                                        << std::endl
    << "    標準入力から受け取ったデータを復号化し、" << std::endl
    << "    標準出力へ出力する"                       << std::endl
    << "  help"                                       << std::endl
    << "    ヘルプを表示する"                         << std::endl
    << "Options:"                                     << std::endl
    << "  -h"                                         << std::endl
    << "    ヘルプを表示する"                         << std::endl
    << "  -i <iv>"                                    << std::endl
    << "    <iv>で指定された値でIVを作成する。"       << std::endl
    << "    <iv>はHex String形式(例: AB01DF93BC)で"   << std::endl
    << "    長さが128bitになるようにする必要がある"   << std::endl
    << "  -k <key>"                                   << std::endl
    << "    <key>で指定された値で鍵を作成する。"      << std::endl
    << "    <key>はhex String形式で長さが128 bit,"    << std::endl
    << "    192 bit, 256 bitのいずれかの"             << std::endl
    << "    長さになる必要がある。"                   << std::endl;
}