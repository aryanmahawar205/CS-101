#include <arpa/inet.h>
#include <unistd.h>
#include <openssl/evp.h>
#include <cstring>
#include <iostream>

using namespace std;

string decryptAES(string ciphertext, string key, string iv)
{
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    unsigned char plaintext[1024];
    int len, plaintext_len;

    EVP_DecryptInit_ex(ctx, EVP_aes_128_cbc(), NULL,
                       (unsigned char*)key.c_str(),
                       (unsigned char*)iv.c_str());

    EVP_DecryptUpdate(ctx, plaintext, &len,
                      (unsigned char*)ciphertext.c_str(),
                      ciphertext.size());
    plaintext_len = len;

    EVP_DecryptFinal_ex(ctx, plaintext + len, &len);
    plaintext_len += len;

    EVP_CIPHER_CTX_free(ctx);
    return string((char*)plaintext, plaintext_len);
}

int main()
{
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    bind(server_fd,(struct sockaddr*)&address,sizeof(address));
    listen(server_fd,3);

    cout<<"AES Receiver waiting...\n";
    new_socket = accept(server_fd,(struct sockaddr*)&address,(socklen_t*)&addrlen);

    int msg_len;
    read(new_socket,&msg_len,sizeof(msg_len));

    char buffer[2048];
    read(new_socket,buffer,msg_len);
    string ciphertext(buffer,msg_len);

    string key, iv;
    cout<<"Enter same 16-char key: ";
    cin>>key;
    cout<<"Enter same 16-char IV: ";
    cin>>iv;

    string decrypted = decryptAES(ciphertext,key,iv);

    cout<<"\nDecrypted Message: "<<decrypted<<endl;
    close(new_socket);
}
