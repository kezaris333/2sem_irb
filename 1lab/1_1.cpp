#include <iostream>
#include <fstream>

class Encoder {
private:
    unsigned char* key; //массив ключа
    size_t keySize;     

    void swap(unsigned char& a, unsigned char& b) {
        unsigned char temp = a;
        a = b;
        b = temp;
    }

    //с блок 123456...
    void KSA(unsigned char* S) {
        for (int i = 0; i < 256; ++i) {
            S[i] = i;
        }

        int j = 0;
        for (int i = 0; i < 256; ++i) {
            j = (j + S[i] + key[i % keySize]) % 256; //смешиваем с бло
            swap(S[i], S[j]);
        }
    }

  //ксевдослуч массив к
    void PRGA(unsigned char* S, unsigned char* data, size_t dataSize) {
        int i = 0, j = 0;
        for (size_t n = 0; n < dataSize; ++n) {
            i = (i + 1) % 256;
            j = (j + S[i]) % 256;
            swap(S[i], S[j]); // Обмен значениями
            data[n] ^= S[(S[i] + S[j]) % 256]; // Применяем XOR к данным
        }
    }


public:
    Encoder(unsigned char const* key, size_t keySize) {
          this->keySize = keySize;
      
          this->key = new unsigned char[keySize]; //паямть для ключа
        for (size_t i = 0; i < keySize; ++i) {
            this->key[i] = key[i];
        }
    }

    // Деструктор для освобождения памяти
    ~Encoder() {
        delete[] key;
    }



    //метод для изменения ключа
    void setKey(unsigned char const* newKey, size_t newKeySize) {
        delete[] key; //осв паямть
        keySize = newKeySize;
        key = new unsigned char[keySize]; //пам под новый кл
        for (size_t i = 0; i < keySize; ++i) {
            key[i] = newKey[i]; 
        }
    }



    // шифров дешифровка
    void encode(char const* inputFile, char const* outputFile, bool encrypt) {
        std::ifstream inFile(inputFile, std::ios::binary); //открытие входногг
        std::ofstream outFile(outputFile, std::ios::binary); // выходного

        if (!inFile || !outFile) {
            std::cerr << "Error opening file!" << std::endl;
            return;
        }
//?? размер
        inFile.seekg(0, std::ios::end);
        size_t fileSize = inFile.tellg();
        inFile.seekg(0, std::ios::beg);

        //читаем данные из файла
        unsigned char* data = new unsigned char[fileSize];
        inFile.read(reinterpret_cast<char*>(data), fileSize);



      
    unsigned char S[256];
    KSA(S);

      
    PRGA(S, data, fileSize);

       
        outFile.write(reinterpret_cast<char*>(data), fileSize);

        delete[] data; 
    }
};





int main() {
    //ключ
    unsigned char key[] = { 0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF };
    size_t keySize = sizeof(key) / sizeof(key[0]);


    Encoder encoder(key, keySize);


  
    encoder.encode("input.txt", "encrypted.bin", true);
    std::cout << "File encrypted successfully!" << std::endl;

    

  
    encoder.encode("encrypted.bin", "decrypted.txt", false);
    std::cout << "File decrypted successfully!" << std::endl;

    return 0;
}
