// Enter 16-char key: 1234567890123456
// Enter 16-char IV: 6543210987654321
// Enter message: Hello AES socket
// g++ receiver.cpp -lssl -lcrypto -o receiver
// ./receiver
// g++ sender.cpp -lssl -lcrypto -o sender
// ./sender
#include <arpa/inet.h>
#include <unistd.h>
#include <openssl/evp.h>
#include <cstring>
#include <iostream>

using namespace std;

string encryptAES(string plaintext, string key, string iv)
{
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    unsigned char ciphertext[1024];
    int len, ciphertext_len;

    EVP_EncryptInit_ex(ctx, EVP_aes_128_cbc(), NULL,
                       (unsigned char*)key.c_str(),
                       (unsigned char*)iv.c_str());

    EVP_EncryptUpdate(ctx, ciphertext, &len,
                      (unsigned char*)plaintext.c_str(),
                      plaintext.size());
    ciphertext_len = len;

    EVP_EncryptFinal_ex(ctx, ciphertext + len, &len);
    ciphertext_len += len;

    EVP_CIPHER_CTX_free(ctx);
    return string((char*)ciphertext, ciphertext_len);
}

int main()
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serv_addr;

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8080);
    inet_pton(AF_INET,"127.0.0.1",&serv_addr.sin_addr);
    connect(sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr));

    string key, iv, message;
    cout<<"Enter 16-char key: ";
    cin>>key;
    cout<<"Enter 16-char IV: ";
    cin>>iv;
    cin.ignore();

    cout<<"Enter message: ";
    getline(cin,message);

    string ciphertext = encryptAES(message,key,iv);

    int len = ciphertext.size();
    send(sock,&len,sizeof(len),0);
    send(sock,ciphertext.c_str(),len,0);

    cout<<"Encrypted message sent!\n";
    close(sock);
}