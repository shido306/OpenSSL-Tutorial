#pragma once
#include <openssl/evp.h>


// 暗号化
template <size_t key_size>
requires AESKeySize<key_size>
byte_stream encrypt(
    const key<key_size>& key,
    const byte_stream& raw_data,
    const iv& iv
){
    //////////////////
    // 初期化コード
    //////////////////
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    if( ctx == nullptr ) {
        throw "cannot initialize OpenSSL cipher context";
    }
    // 暗号化スイート
    const EVP_CIPHER* cipher_suite;

    // EVP_aes_(key-size)_cbcという関数がAES-CBC暗号化スイートの設定を作成し、返してくれる。
    switch( key_size ){
        case 128:
            cipher_suite = EVP_aes_128_cbc();
            break;
        case 192:
            cipher_suite = EVP_aes_192_cbc();
            break;
        case 256:
            cipher_suite = EVP_aes_256_cbc();
            break;
    }
    if ( cipher_suite == nullptr ) {
        EVP_CIPHER_CTX_free(ctx);
        throw "cannot get cipher suite";
    }

    // スイートの設定を作成したら、その設定と鍵、IVをctxに設定する
    if(EVP_EncryptInit(ctx, cipher_suite, key.data(), iv.data()) == 0){
        EVP_CIPHER_CTX_free(ctx);
        throw "cannot construct OpenSSL cipher context";
    }

    //////////////////
    // 暗号化コード
    //////////////////
    
    // encrypted_dataのデータサイズの調整
    auto encrypted_data = byte_stream(
        raw_data.size() + (BLOCK_SIZE - raw_data.size() % BLOCK_SIZE)
    );
    int len = 0;
    if( EVP_EncryptUpdate(ctx, encrypted_data.data(), &len, raw_data.data(), raw_data.size()) == 0){
        EVP_CIPHER_CTX_free(ctx);
        throw "cannot encrypt data";
    }

    //////////////////
    // データの後処理
    //////////////////
    if( EVP_EncryptFinal(ctx, encrypted_data.data() + len, &len) == 0){
        EVP_CIPHER_CTX_free(ctx);
        throw "cannot padding";
    }
    EVP_CIPHER_CTX_free(ctx);
    return encrypted_data;
}

// 復号化
template <size_t key_size>
requires AESKeySize<key_size>
byte_stream decrypt(
    const key<key_size>& key,
    const byte_stream& encrypted_data,
    const iv& iv
){
    //////////////////
    // 初期化コード
    //////////////////
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    if( ctx == nullptr ) {
        throw "cannot initialize OpenSSL cipher context";
    }
    // 暗号化スイート
    const EVP_CIPHER* cipher_suite;

    // EVP_aes_(key-size)_cbcという関数がAES-CBC暗号化スイートの設定を作成し、返してくれる。
    switch( key_size ){
        case 128:
            cipher_suite = EVP_aes_128_cbc();
            break;
        case 192:
            cipher_suite = EVP_aes_192_cbc();
            break;
        case 256:
            cipher_suite = EVP_aes_256_cbc();
            break;
    }
    if( cipher_suite == nullptr ){
        EVP_CIPHER_CTX_free(ctx);
        throw "cannot get cipher suite";
    }
    // スイートの設定を作成したら、その設定と鍵、IVをctxに設定する
    if(EVP_DecryptInit(ctx, cipher_suite, key.data(), iv.data()) == 0){
        EVP_CIPHER_CTX_free(ctx);
        throw "cannot construct OpenSSL cipher context";
    }

    //////////////////
    // 復号化
    //////////////////
    auto plain_data = byte_stream(encrypted_data.size());
    // 暗号化時にははみだしていなかったデータの復号化後の長さ
    int plain_data_len = 0;
    
    if( EVP_DecryptUpdate(ctx, plain_data.data(), &plain_data_len, encrypted_data.data(), encrypted_data.size()) == 0 ){
        EVP_CIPHER_CTX_free(ctx);
        throw "cannot decrypt data";
    }

    // パデイングデータをのぞいた暗号化時にはみだしていたデータ分の長さ
    int remain_plain_data_len;
    if (EVP_DecryptFinal(ctx, plain_data.data() + plain_data_len, &remain_plain_data_len) == 0) {
        EVP_CIPHER_CTX_free(ctx);
        throw "cannot padding";
    }
    plain_data.resize(plain_data_len + remain_plain_data_len);
    EVP_CIPHER_CTX_free(ctx);
    return plain_data;
}