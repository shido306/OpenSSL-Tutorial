//************************************************************************* 
//
// RSA 公開鍵暗号方式
//
// キー生成 ソースファイル
//
// ************************************************************************/ 

////////////////////////////
// インクルード
////////////////////////////
#include <openssl/evp.h>
#include <openssl/pem.h>
#include "../include/GenerateKey.hpp"

////////////////////////////
// 関数定義
////////////////////////////

// 秘密鍵、公開鍵生成して出力
void generateKeypair(
    const std::string& priv_path,   // in: 秘密鍵ファイルパス
    const std::string& pub_path,    // in: 公開鍵ファイルパス
    int bits                        // in: 鍵のビット数
){
    //==========================
    // 鍵生成のコンテキストを作成
    //==========================
    // EVP_PKEY_CTX_new_from_name関数は、指定した暗号化方式の鍵生成コンテキストを作成して返す。
    // 第一引数のnullptrはプロバイダを指定する引数だが、nullptrを指定するとOpenSSLのデフォルトプロバイダが使用される。
    // 第二引数の"RSA"はRSA暗号化方式を指定する文字列
    // 第三引数は「プロパティクエリ文字列」を指定する引数だが、nullptrを指定するとデフォルトのプロパティが使用される。
    //==========================
    EVP_PKEY_CTX *ctx = EVP_PKEY_CTX_new_from_name(nullptr, "RSA", nullptr);
    if( ctx == nullptr ) {
        throw "cannot initialize OpenSSL cipher context";
    }

    //==========================
    // 鍵生成のコンテキストを初期化
    //==========================
    // EVP_PKEY_keygen_init関数は、鍵生成のコンテキストを初期化する。
    //==========================
    if( EVP_PKEY_keygen_init(ctx) <= 0 ) {
        EVP_PKEY_CTX_free(ctx);
        throw "cannot initialize OpenSSL keygen context";
    }

    //==========================
    // 鍵のビット数を設定
    //==========================
    // EVP_PKEY_CTX_set_rsa_keygen_bits関数は、鍵生成のコンテキストに鍵のビット数を設定する。
    //==========================
    if( EVP_PKEY_CTX_set_rsa_keygen_bits(ctx, bits) <= 0 ) {
        EVP_PKEY_CTX_free(ctx);
        throw "cannot set key size";
    }

    //==========================
    // 鍵のペアを生成
    //==========================
    EVP_PKEY *pkey = nullptr;
    if( EVP_PKEY_generate(ctx, &pkey) <= 0 ) {
        EVP_PKEY_CTX_free(ctx);
        throw "cannot generate key pair";
    }
    EVP_PKEY_CTX_free(ctx);

    //==========================
    // 秘密鍵をPEM形式で出力
    //==========================
    FILE *priv_file = fopen(priv_path.c_str(), "wb");
    if( priv_file == nullptr ) {
        EVP_PKEY_free(pkey);
        throw "cannot open private key file";
    }

    PEM_write_PrivateKey(priv_file, pkey, nullptr, nullptr, 0, nullptr, nullptr);
    fclose(priv_file);

    //==========================
    // 公開鍵をPEM形式で出力
    //==========================
    FILE *pub_file = fopen(pub_path.c_str(), "wb");
    if( pub_file == nullptr ) {
        EVP_PKEY_free(pkey);
        throw "cannot open public key file";
    }

    PEM_write_PUBKEY(pub_file, pkey);
    fclose(pub_file);

    EVP_PKEY_free(pkey);
}