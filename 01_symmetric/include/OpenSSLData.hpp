#include <cstdint>
#include <vector>
#include <type_traits>
#include <array>
#include <cstddef>

// インクルードガード
#ifndef _OPEN_SSL_DATA_HPP_
#define _OPEN_SSL_DATA_HPP_

// 符号無し8bit整数を利用することを明確にするため
using byte = uint8_t;
// バイトストリーム用の型
using byte_stream = std::vector<byte>;

// AES-CBCにおける鍵を表す型
// key_sizeが128 bitか192 bitか256 bitなものしか鍵の型を生成できないように制限している
template <size_t N>
concept AESKeySize =
    N == 128 ||
    N == 192 ||
    N == 256;

template <size_t key_size>
requires AESKeySize<key_size>
using key = std::array<byte, key_size / 8>;

// AES-CBCにはIVが必要となるので、これを表現する型
// BLOCK_SIZE == 16なのはAESではブロック長が128 bit固定であり、
// IVもそのブロック長にする必要があるので、
// byte == uint8_tからその要素数が128 / 8 == 16となるため
constexpr auto BLOCK_SIZE = 16;
using iv = std::array<byte, BLOCK_SIZE>;

#endif // _OPEN_SSL_DATA_HPP_
