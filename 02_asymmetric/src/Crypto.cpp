//************************************************************************* 
//
// RSA 公開鍵暗号方式
//
// 暗号化/復号化 ソースファイル
//
// ************************************************************************/ 

/////////////////////////////
// インクルード
/////////////////////////////
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/rsa.h>
#include <iostream>
#include <vector>
#include "../include/Crypto.hpp"
#include "../include/io.hpp"

/////////////////////////////
// 関数定義
/////////////////////////////

// 公開鍵で暗号化
void encryptPubKey(
    const std::string& pub_path         // in: 公開鍵ファイルパス
){
    //==========================
    // 公開鍵ファイルの読み込み
    //==========================
    FILE* pub_file = fopen(pub_path.c_str(), "rb");
    if( pub_file == nullptr ){
        throw "cannot read public key file";
    }

    //==========================
    // 公開鍵の読み込み
    //==========================
    EVP_PKEY *pkey = PEM_read_PUBKEY(pub_file, nullptr, nullptr, nullptr);
    fclose(pub_file);

    if( pkey == nullptr ){
        throw "cannot read public key";
    }

    //==========================
    // 公開鍵から暗号化のコンテキストを作成
    //==========================
    // EVP_PKEY_CTX_new関数は、指定した暗号化方式の鍵生成コンテキストを作成して返す。
    // 第一引数は、公開鍵を指定する。
    // 第二引数のnullptrはプロバイダを指定する引数だが、nullptrを指定するとOpenSSLのデフォルトプロバイダが使用される。
    //==========================
    EVP_PKEY_CTX* ctx = EVP_PKEY_CTX_new(pkey, nullptr);
    EVP_PKEY_free(pkey);    // pkeyは不要になったので解放する
    if( ctx == nullptr ) {
        throw "cannot initialize OpenSSL cipher context";
    }

    //==========================
    // 暗号化のコンテキストを初期化
    //==========================
    // EVP_PKEY_encrypt_init関数は、暗号化のコンテキストを初期化する。
    //==========================
    if( EVP_PKEY_encrypt_init(ctx) <= 0 ){
        EVP_PKEY_CTX_free(ctx);
        throw "cannot initialize OpenSSL cipher context";
    }

    //==========================
    // パディングをOAEPに設定
    //==========================
    // EVP_PKEY_CTX_set_rsa_padding関数は、RSA暗号化のパディング方式を設定する。
    // OAEPパディングを推奨されているため、RSA_PKCS1_OAEP_PADDINGを指定する。
    //==========================
    if( EVP_PKEY_CTX_set_rsa_padding(ctx, RSA_PKCS1_OAEP_PADDING) <= 0 ){
        EVP_PKEY_CTX_free(ctx);
        throw "cannot set OAEP padding";
    }

    //==========================
    // stdinから平文を読み込み
    //==========================
    auto plaintext = read_stdin();
    if( plaintext.empty() ){
        EVP_PKEY_CTX_free(ctx);
        throw std::runtime_error("入力データが空です");
    }
    
    //==========================
    // 暗号化の出力サイズを取得
    //==========================
    size_t outlen;
    if( EVP_PKEY_encrypt(ctx, nullptr, &outlen, plaintext.data(), plaintext.size()) <= 0 ){
        EVP_PKEY_CTX_free(ctx);
        throw "cannot determine ciphertext length";
    }

    //==========================
    // 暗号化の実施
    //==========================
    std::vector<unsigned char> ciphertext(outlen);
    if( EVP_PKEY_encrypt(ctx, ciphertext.data(), &outlen, plaintext.data(), plaintext.size()) <= 0 ){
        EVP_PKEY_CTX_free(ctx);
        throw "cannot encrypt data";
    }

    EVP_PKEY_CTX_free(ctx);
 
    //==========================
    // stdoutへバイナリ出力
    //==========================
    ciphertext.resize(outlen);
    write_stdout(ciphertext);
}



// 秘密鍵で復号化
void decryptPrivKey(
    const std::string& priv_path    // in: 秘密鍵ファイルパス
){
    //==========================
    // 秘密鍵ファイルの読み込み
    //==========================
    FILE* priv_file = fopen(priv_path.c_str(), "rb");
    if( priv_file == nullptr ){
        throw "cannot read private key file";
    }

    //==========================
    // 秘密鍵の読み込み
    //==========================
    // PEM_read_PrivateKey関数は、PEM形式の秘密鍵を読み込む。
    // 第一引数のpriv_fileは、秘密鍵ファイルのFILEポインタ
    //==========================
    EVP_PKEY *pkey = PEM_read_PrivateKey(priv_file, nullptr, nullptr, nullptr);
    fclose(priv_file);

    if( pkey == nullptr ){
        throw "cannot read private key";
    }

    //==========================
    // 秘密鍵から復号化のコンテキストを作成
    //==========================
    EVP_PKEY_CTX* ctx = EVP_PKEY_CTX_new(pkey, nullptr);
    EVP_PKEY_free(pkey);    // pkeyは不要になったので解放する
    if( ctx == nullptr ) {
        throw "cannot initialize OpenSSL cipher context";
    }

    //==========================
    // 復号化のコンテキストを初期化
    //==========================
    if( EVP_PKEY_decrypt_init(ctx) <= 0 ){
        EVP_PKEY_CTX_free(ctx);
        throw "cannot initialize OpenSSL cipher context";
    }

    //==========================
    // パディングをOAEPに設定
    //==========================
    if( EVP_PKEY_CTX_set_rsa_padding(ctx, RSA_PKCS1_OAEP_PADDING) <= 0 ){
        EVP_PKEY_CTX_free(ctx);
        throw "cannot set OAEP padding";
    }

    //==========================
    // stdinから暗号文を読み込み
    //==========================
    auto ciphertext = read_stdin();
    if( ciphertext.empty() ){
        EVP_PKEY_CTX_free(ctx);
        throw std::runtime_error("入力データが空です");
    }

    //==========================
    // 暗号文サイズ分のバッファを確保
    //==========================
    size_t outlen = ciphertext.size();
    std::vector<unsigned char> plaintext(outlen);

    //==========================
    // 復号化の実施
    //==========================
    if( EVP_PKEY_decrypt(ctx, plaintext.data(), &outlen, ciphertext.data(), ciphertext.size()) <= 0 ){
        EVP_PKEY_CTX_free(ctx);
        throw "cannot decrypt data";
    }

    EVP_PKEY_CTX_free(ctx);

    //==========================
    // stdoutへバイナリ出力
    //==========================
    plaintext.resize(outlen);
    write_stdout(plaintext);
}