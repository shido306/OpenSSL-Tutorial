#include <functional>
#include <stdexcept>
#include <algorithm>
#include "../include/OpenSSLData.hpp"

// インクルードガード
#ifndef _PRINTER_HPP_
#define _PRINTER_HPP_

// データの出力
template <size_t key_size, typename Encoder>
requires AESKeySize<key_size>
void print_data_while_encoding(
    const byte_stream& original_key,
    const byte_stream& data,
    const byte_stream& original_iv,
    const Encoder&& encoder
);

#include "../include/Printer.tpp"

#endif // _PRINTER_HPP_
