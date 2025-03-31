#include <iostream>

class logical_values_array {
    unsigned int _value; //хранит значение массива логических величин

public:


    //constructor
    logical_values_array(unsigned int x = 0) {
        _value = x;
    }

    //тильда
    logical_values_array invert() {
        return (logical_values_array(~_value));
    }


    //конъюнкция * &
    logical_values_array con(const logical_values_array &arg1) const {
        return logical_values_array(_value & arg1._value);
    }


    //дизъюнкция + |
    logical_values_array disjunction(logical_values_array &arg1) const {
        return logical_values_array(_value | arg1._value);
    }


    //импликация - если... то...
    logical_values_array impl(logical_values_array &arg1) const {
        return logical_values_array(~_value | arg1._value);
    }


    //коимпликация - отрицание импликации
    logical_values_array coimpl(logical_values_array &arg1) const {
        return logical_values_array(~(~_value | arg1._value));//или (_value | ~arg1._value)
    }

    //eq
    static bool equivalent(logical_values_array &arg1, logical_values_array &arg2) {
        return (arg1._value == arg2._value);
    }


    //стрелка пирса(функция вебба) - противоп дизъюнкции, истина ток тогда когда обе перпеменные ложные
    logical_values_array pirs(logical_values_array &arg1) const {
        return logical_values_array(~(_value | arg1._value));
    }



    //штрих шеффера- противоположно конъюнкции, ложна только тогда когда оба значения истинны
    logical_values_array shef(const logical_values_array &arg1) const {
        return logical_values_array(~(_value & arg1._value));
    }



    //get_bit
    bool get_bit(size_t pos) {  //sizeof байты
        if (pos >= sizeof(int) * 8) {//размер в битах
            throw std::invalid_argument("слишком большой номер позиции");
        }
        return ((_value >> pos) & 1);
    }


    //[]
    bool operator[](int i) {
        return (get_bit(i));
    }


    void binary(char *bin) {// валуе в двоичке
        if (bin == nullptr)
            throw std::invalid_argument("путая строка");
        int size_bit = (8 * sizeof(int));
        unsigned int temp = _value;
        for (int i = 0; i < size_bit; i++) {
            bin[size_bit - i - 1] =
                    (temp & 1) + '0'; //temp1 - младший бит числа, +0 преобр в символ,  sizebit-i запись с конца строки
            temp = temp >> 1;
        }
        bin[size_bit] = '\0';
    }


//    //accessor for _value
//    //ba by be)
//    unsigned int getval() const {
//        return _value;
//    }


};


int main() {
    logical_values_array a(5); // 5 в двоичном виде: 00000000000000000000000000000101
    logical_values_array b(3); // 3 в двоичном виде: 00000000000000000000000000000011

    
    auto c = a.con(b); 
    auto d = a.disjunction(b); 
    auto g = a.invert(); 

    char binaryA[33], binaryB[33];
    a.binary(binaryA);
    b.binary(binaryB);

    std::cout << "a (5): " << binaryA << std::endl;
    std::cout << "b (3): " << binaryB << std::endl;
    std::cout << "a AND b: " << c[0] << std::endl; // выводит 1 или 0
    std::cout << "a OR b: " << d[0] << std::endl; // выводит 1 или 0
    std::cout << "NOT a: " << g[0] << std::endl; // выводит 1 или 0

    return 0;
}
  
