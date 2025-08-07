/*1. Реализовать класс encoder. В классе определить и реализовать:
● конструктор, принимающий ключ шифрования в виде массив байтов типа unsigned char const * и размер
этого массива
● mutator для значения ключа
● метод encode, который принимает путь ко входному файлу (типа char const *), выходному файлу (типа
char const *) и флаг, отвечающий за то, выполнять шифрование или дешифрование (типа bool) и
выполняет процесс шифрования/дешифрования файла
Шифрование/дешифрование файлов выполняется алгоритмом RC4. Структура содержимого файлов произвольна.
Продемонстрировать работу класса, произведя шифрование/дешифрование различных файлов: текстовых,
графических, аудио, видео, исполняемых*/


//
// #include <iostream>
// #include <fstream>
//
// using namespace std;
//
//
// class encoder  {
//     unsigned char* key;
//     size_t keylen;
//     unsigned char S[256];
//     unsigned char i, j;
//
//  void ksa () {
//      for (int i = 0; i < 256; i++) { //иниц блока S 1234567
//          S[i] = i;
//      }
//
//      //ksa
//      i = 0, j = 0;
//      while (i < 256) {
//          j = (j + S[i] + K[i] /*%keylen*/) % 256;
//          unsigned char temp = S[i];
//          S[i] = S[j];
//          S[j] = temp;
//          i++;
//      }
//      i = j = 0;
//  }
//
//  void PRGA(unsigned  char *data, size_t datalen, unsigned char *output ) {
//
//             for (size_t k = 0; k < datalen; k++) {
//                 i = (i + 1) % 256;
//                 j = (j + S[i]) % 256;
//
//                 unsigned char temp = S[i];
//                 S[i] = S[j];
//                 S[j] = temp;
//
//                 unsigned char t = (S[i] + S[j]) % 256;
//
//                 //xor
//                 output[k] = data[k] ^ S[t];
//             }
//         }
//
// public:
//
// };
//
//
// int main() {
//     std::cout << "Hello, World!" << std::endl;
//     return 0;
// }
//

#include <iostream>
#include <fstream>

using namespace std;

class encoder {
    unsigned char* key;
    size_t keylen;
    unsigned char S[256];
    unsigned char i, j;

    void ksa() {
        for (int i = 0; i < 256; i++) {
            S[i] = i;
        }

        i = 0, j = 0;
        while (i < 256) {
            j = (j + S[i] + key[i % keylen]) % 256;  // Исправлено: K[i] на key[i % keylen]
            unsigned char temp = S[i];
            S[i] = S[j];
            S[j] = temp;
            i++;
        }
        i = j = 0;
    }

    void PRGA(unsigned char* data, size_t datalen, unsigned char* output) {
        for (size_t k = 0; k < datalen; k++) {
            i = (i + 1) % 256;
            j = (j + S[i]) % 256;

            unsigned char temp = S[i];
            S[i] = S[j];
            S[j] = temp;

            unsigned char t = (S[i] + S[j]) % 256;

            output[k] = data[k] ^ S[t];
        }
    }

public:
    encoder(unsigned char const* key, size_t key_size) {
        this->key = nullptr;
        set_key(key, key_size);
    }

    //mutator для ключа
    void set_key(unsigned char const* new_key, size_t new_keylen) {
        if (key) delete[] key;
        keylen = new_keylen;
        key = new unsigned char[keylen];
        for (size_t i = 0; i < keylen; i++) {
            key[i] = new_key[i];
        }
        ksa();
    }

    //метод encode
    bool encode(char const* input_file, char const* output_file, bool encrypt) {
        ifstream in(input_file, ios::binary);
        if (!in) return false;

        ofstream out(output_file, ios::binary);
        if (!out) return false;

        //определяем размер файла
        in.seekg(0, ios::end);
        size_t file_size = in.tellg();
        in.seekg(0, ios::beg);


        unsigned char* buffer = new unsigned char[file_size];
        in.read((char*)buffer, file_size);

        unsigned char* result = new unsigned char[file_size];
        PRGA(buffer, file_size, result);

        out.write((char*)result, file_size);

        delete[] buffer;
        delete[] result;

        return true;
    }

    ~encoder() {
        if (key) delete[] key;
    }
};

int main() {

    unsigned char key[] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};
    encoder rc4(key, sizeof(key));

    rc4.encode("input.txt", "encrypted.bin", true);

    encoder rc4_decryptor(key, sizeof(key));
    rc4_decryptor.encode("encrypted.bin", "decrypted.txt", false);

    return 0;
}}
