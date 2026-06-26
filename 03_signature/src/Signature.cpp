//************************************************************************* 
//
// 署名・検証
//
// 署名/検証 ソースファイル
//
// ************************************************************************/ 

////////////////////////////
// インクルード
////////////////////////////
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "../include/Signature.hpp"
#include "../include/io.hpp"

////////////////////////////
// 関数定義
////////////////////////////

// 秘密鍵で署名を生成
void signData(
    const std::string& priv_path,   // in: 秘密鍵ファイルパス
    const std::string& sig_path     // in: 署名ファイル出力パス
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
    EVP_PKEY *pkey = PEM_read_PrivateKey(priv_file, nullptr, nullptr, nullptr);
    fclose(priv_file);

    if( pkey == nullptr ){
        throw "cannot read private key";
    }

    //==========================
    // 署名のコンテキストを作成
    //==========================
    EVP_MD_CTX* mdctx = EVP_MD_CTX_new();
    if( mdctx == nullptr ){
        EVP_PKEY_free(pkey);
        throw "cannot create message digest context";
    }

    //==========================
    // 署名の初期化
    //==========================
    // EVP_DigestSignInit関数は、署名操作を初期化する。
    // 第一引数のmdctxは署名のコンテキスト
    // 第三引数のEVP_sha256()はハッシュ関数にSHA-256を指定する。
    // 第四引数のnullptrはプロバイダを指定する引数だが、nullptrを指定するとOpenSSLのデフォルトプロバイダが使用される。
    // 第五引数のpkeyは署名に使用する秘密鍵を指定する。
    //==========================
    if( EVP_DigestSignInit(mdctx, nullptr, EVP_sha256(), nullptr, pkey) <= 0 ){
        EVP_MD_CTX_free(mdctx);
        EVP_PKEY_free(pkey);
        throw "cannot initialize signature context";
    }
    EVP_PKEY_free(pkey);    // 不要になったため、秘密鍵のコンテキストを解放する。

    //==========================
    // stdinからバイナリデータを読み込む
    //==========================
    auto msg = read_stdin();
    if( msg.empty() ){
        EVP_MD_CTX_free(mdctx);
        throw "input data is empty";
    }

    //==========================
    // メッセージを渡してハッシュ値を計算する
    //==========================
    // EVP_DigestSignUpdate関数は、署名するメッセージを渡してハッシュ値を計算する。
    // 第一引数のmdctxは署名のコンテキスト
    // 第二引数のmsg.data()は署名するメッセージのデータ
    // 第三引数のmsg.size()は署名するメッセージのサイズ
    // ※ EVP_DigestSignUpdate関数は、複数回呼び出すことができる。複数回呼び出すことで、メッセージを分割して渡すことができる。
    //==========================
    if( EVP_DigestSignUpdate(mdctx, msg.data(), msg.size()) <= 0 ){
        EVP_MD_CTX_free(mdctx);
        throw "cannot update DigestSign";
    }

    //==========================
    // 署名のサイズを取得
    //==========================
    // RSA鍵長によって変わるため、署名のサイズを取得する必要がある。
    //==========================
    size_t siglen;
    if( EVP_DigestSignFinal(mdctx, nullptr, &siglen) <= 0 ){
        EVP_MD_CTX_free(mdctx);
        throw "cannot determine signature length";
    }

    //==========================
    // 署名の生成
    //==========================
    // EVP_DigestSignFinal関数は、署名を生成する。
    // 第一引数のmdctxは署名のコンテキスト
    // 第二引数のsig.data()は署名の出力先のバッファ
    // 第三引数のsiglenは署名のサイズ
    //==========================
    std::vector<unsigned char> sig(siglen);
    if( EVP_DigestSignFinal(mdctx, sig.data(), &siglen) <= 0 ){
        EVP_MD_CTX_free(mdctx);
        throw "cannot generate signature";
    }

    EVP_MD_CTX_free(mdctx);     // 署名のコンテキストを解放する。

    //==========================
    // 署名をファイルに書き込む
    //==========================
    std::ofstream sig_file(sig_path, std::ios::binary);
    if( !sig_file ){
        throw "cannot open signature file for writing";
    }
    sig.resize(siglen);
    sig_file.write(reinterpret_cast<const char*>(sig.data()), sig.size());
 
    std::cerr << "[sign] 署名ファイル: " << sig_path << "\n";
}