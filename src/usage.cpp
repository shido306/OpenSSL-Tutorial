#include "../include/usage.hpp"
#include <iostream>

auto usage(const std::filesystem::path& program_path) -> void {
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
    << "    ヘルプを表示する"                         << std::endl;
}