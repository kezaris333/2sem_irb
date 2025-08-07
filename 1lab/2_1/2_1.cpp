//2. Реализовать класс logical_values_array. В классе определить и реализовать:
//● поле _value (типа unsigned int), которое хранит значение массива логических величин
//● accessor для поля _value
//● конструктор, принимающий значение типа unsigned int (равное по умолчанию 0) и инициализирующий
//переданным значением поле _value
//● методы, соответствующие всем стандартным логическим операциям, и (для бинарных операций)
//выполняющиеся между каждой парой битов полей _value объектов, над которыми выполняется
//преобразование: инверсия, конъюнкция, дизъюнкция, импликация, коимпликация, сложение по модулю 2,
//эквивалентность, стрелка Пирса, штрих Шеффера; в результате выполнения метода результат сохраняется
//в новый возвращаемый объект. При реализации необходимо использовать набор следующих базисных
//операций: конъюнкция, дизъюнкция, инверсия, сложение по модулю 2.
//● статический метод equals, сравнивающий два объекта по отношению эквивалентности
//● метод get_bit, который возвращает значение бита по его позиции (позиция является параметром типа
//size_t)
//● перегруженный оператор [], делегирующий выполнение на метод get_bit
//● метод, принимающий значение типа char *; по значению адреса в параметре должно быть записано
//двоичное представление поля _value в виде строки в стиле языка программирования C. Примечание:
//конвертация должна быть основана на использовании битовых операций.
//Продемонстрируйте работу реализованного функционала.

#include "beee.h"


//constructor
logical_values_array::logical_values_array(unsigned int x) {
    _value = x;
}

//тильда
logical_values_array logical_values_array::invert() {
    return (logical_values_array(~_value));
}

unsigned int logical_values_array::getval() const {
    return _value;
}

//конъюнкция * &
logical_values_array logical_values_array::con(const logical_values_array &arg1) const {
    return logical_values_array(_value & arg1._value);
}


//дизъюнкция + |
logical_values_array logical_values_array::disjunction(logical_values_array &arg1) const {
    return logical_values_array(_value | arg1._value);
}


//импликация - если... то...
logical_values_array logical_values_array::impl(logical_values_array &arg1) const {
    return logical_values_array(~_value | arg1._value);
}


//коимпликация - отрицание импликации
logical_values_array logical_values_array::coimpl(logical_values_array &arg1) const {
    return logical_values_array(~(~_value | arg1._value));//или (_value | ~arg1._value)
}

//eq
bool logical_values_array::equivalent(logical_values_array &arg1, logical_values_array &arg2) {
    return (arg1._value == arg2._value);
}


//стрелка пирса(функция вебба) - противоп дизъюнкции, истина ток тогда когда обе перпеменные ложные
logical_values_array logical_values_array::pirs(logical_values_array &arg1) const {
    return logical_values_array(~(_value | arg1._value));
}


//штрих шеффера- противоположно конъюнкции, ложна только тогда когда оба значения истинны
logical_values_array logical_values_array::shef(const logical_values_array &arg1) const {
    return logical_values_array(~(_value & arg1._value));
}


//get_bit
bool logical_values_array::get_bit(size_t pos) {  //sizeof байты
    if (pos >= sizeof(int) * 8) {//размер в битах
        throw std::invalid_argument("слишком большой номер позиции");
    }
    return ((_value >> pos) & 1);
}


//[]
bool logical_values_array::operator[](int i) {
    return (get_bit(i));
}


void logical_values_array::binary(char *bin) {// валуе в двоичке
    if (bin == nullptr)
        throw std::invalid_argument("пустая строка");
    int size_bit = (8 * sizeof(unsigned int));
    unsigned int temp = _value;
    for (int i = 0; i < size_bit; i++) {
        bin[size_bit - i - 1] =
                (temp & 1) + '0'; //temp&1 - младший бит числа, +'0' преобр в символ, size_bit-i запись с конца строки
        temp = temp >> 1;
    }
    bin[size_bit] = '\0';
}






//    //accessor for _value
//    //ba by be)
//    unsigned int getval() const {
//        return _value;
//    }





int main() {
    logical_values_array a(12);  //1100 в дв
    logical_values_array b(10);  //1010

    std::cout << "a = " << a.getval() << ", b = " << b.getval() << std::endl;


    std::cout << "AND: " << a.con(b).getval() << std::endl;
    std::cout << "OR: " << a.disjunction(b).getval() << std::endl;
    std::cout << "NOT a: " << a.invert().getval() << std::endl;

    std::cout << "бит 0 в a: " << a[0] << std::endl;
    std::cout << "бит 2 в a: " << a[2] << std::endl;


    char binary_a[33];
    a.binary(binary_a);
    std::cout << "a в двоичном виде: " << binary_a << std::endl;


    logical_values_array c(12);
    std::cout << "a == c: " << logical_values_array::equivalent(a, c) << std::endl;

    return 0;
}
