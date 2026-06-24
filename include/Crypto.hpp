#include "../include/OpenSSLData.hpp"

// インクルードガード
#ifndef _CRYPTO_HPP_
#define _CRYPTO_HPP_

// 暗号化
template <size_t key_size, enable_if_valid_key<key_size> = nullptr>
byte_stream encrypt(
    const key<key_size>& key,
    const byte_stream& data,
    const iv& iv
);

// 復号化
template <size_t key_size, enable_if_valid_key<key_size> = nullptr>
byte_stream decrypt(
    const key<key_size>& key,
    const byte_stream& data,
    const iv& iv
);

#endif // _CRYPTO_HPP_
