#pragma once
#include <iostream>

template <size_t key_size, typename Encoder>
requires AESKeySize<key_size>
void print_data_while_encoding(
    const byte_stream& original_key,
    const byte_stream& data,
    const byte_stream& original_iv,
    const Encoder&& encoder
){
    iv iv;
    key<key_size> key;
    if (iv.size() != original_iv.size()) {
        throw std::invalid_argument("iv length must be 128 bit ");
    }
    if (original_key.size() != key.size()) {
        throw std::invalid_argument("invalid key size");
    }
    std::copy(original_iv.begin(), original_iv.end(), iv.begin());
    std::copy(original_key.begin(), original_key.end(), key.begin());

    auto encoded_data = encoder(key, data, iv);
    for (const auto byte_value : encoded_data) {
        std::cout << byte_value;
    }
}