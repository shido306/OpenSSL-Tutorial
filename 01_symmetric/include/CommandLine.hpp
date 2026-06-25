#include <string>
#include <filesystem>
#include "../include/OpenSSLData.hpp"

// インクルードガード
#ifndef _COMMAND_LINE_HPP_
#define _COMMAND_LINE_HPP_

// 文字列を16進数の羅列(byte_stream)に変換
byte_stream convert_hex_string(
    const std::string& hex_string
);

// helpコマンドの出力
void usage(
    const std::filesystem::path& program_path
);

#endif // _COMMAND_LINE_HPP_
