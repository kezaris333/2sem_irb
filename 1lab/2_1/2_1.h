#include <iostream>
class logical_values_array {
    unsigned int _value; //хранит значение массива логических величин

public:
    logical_values_array(unsigned int x = 0);

    logical_values_array invert();

    logical_values_array con(const logical_values_array &arg1) const;

    logical_values_array disjunction(logical_values_array &arg1) const;

    logical_values_array impl(logical_values_array &arg1) const;

    logical_values_array coimpl(logical_values_array &arg1) const;

    static bool equivalent(logical_values_array &arg1, logical_values_array &arg2);

    unsigned int getval() const;

    logical_values_array pirs(logical_values_array &arg1) const;

    logical_values_array shef(const logical_values_array &arg1) const;

    bool get_bit(size_t pos);

    bool operator[](int i);

    void binary(char *bin) ;
};
