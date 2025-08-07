#include "123.h"

//конструктор
binary_heap::binary_heap(size_t size_in) : size(0), capacity(size_in) {
    array = size_in > 0 ? new Node_binaryheap[size_in] : nullptr;
}

//конструктор копирования
binary_heap::binary_heap(const binary_heap& other) : size(other.size), capacity(other.capacity) {
    if (capacity > 0) {
        array = new Node_binaryheap[capacity];

        for (size_t i = 0; i < size; i++) {
            array[i].priority = other.array[i].priority;
            if (other.array[i].value) {
                array[i].value = new char[strlen(other.array[i].value) + 1];
                strcpy(array[i].value, other.array[i].value);
            } else {
                array[i].value = nullptr;
            }
        }
    } else {
        array = nullptr;
    }
}

//оператор присваивания копированием
binary_heap& binary_heap::operator= (const binary_heap& other) {

    if (this == &other) {
        return *this;
    }

    for (size_t i = 0; i < size; i++) {
        delete[] array[i].value;  // освобождаем строки
    }

    delete[] array;
    size = other.size;
    capacity = other.capacity;

    if (capacity > 0) {
        array = new Node_binaryheap[capacity];

        for (size_t i = 0; i < size; i++) {
            array[i].priority = other.array[i].priority;
            if (other.array[i].value) {
                array[i].value = new char[strlen(other.array[i].value) + 1];
                strcpy(array[i].value, other.array[i].value);
            } else {
                array[i].value = nullptr;
            }
        }
    } else {
        array = nullptr;
    }

    return *this;
}

//конструктор перемещения
binary_heap::binary_heap(binary_heap&& other) noexcept : size(other.size), capacity(other.capacity), array(other.array) {
    other.array = nullptr;
    other.size = 0;
    other.capacity = 0;
}

//оператор присваивания перемещением
binary_heap& binary_heap::operator= (binary_heap&& other) noexcept {
    if (this == &other) {
        return *this;
    }

    for (size_t i = 0; i < size; i++) {
        delete[] array[i].value;
    }
    delete[] array;

    array = other.array;
    size = other.size;
    capacity = other.capacity;

    other.size = 0;
    other.capacity = 0;
    other.array = nullptr;

    return *this;
}

binary_heap::~binary_heap() noexcept {
    for (size_t i = 0; i < size; i++) {
        delete[] array[i].value;
    }
    delete[] array;
}

void binary_heap::swap (Node_binaryheap&one, Node_binaryheap&two) {
    Node_binaryheap temp = one;
    one = two;
    two = temp;
}

void binary_heap::sifting_from_top_to_bottom (int current) { //хз нужен ли параметр
    //передать верхний элемент, сравнить детей, если их приоритет больше, то меняем местами с наибольшим

    int size_ = static_cast<int>(size);

    while (true) {
        int left_c = current * 2 + 1;
        int right_c = current * 2 + 2;
        int largest_c = current;

        if (left_c < size_ &&
            array[largest_c].priority < array[left_c].priority) {
            largest_c = left_c;
        }

        if (right_c < size_ &&
            array[largest_c].priority < array[right_c].priority) {
            largest_c = right_c;
        }

        if (largest_c == current) {
            break;
        }

        swap(array[current], array[largest_c]);
        current = largest_c;
    }
}

void binary_heap::sifting_from_bottom_to_top (int current) {
    while (current > 0) {
        int parent = (current - 1) / 2;

        if (array[current].priority > array[parent].priority) {
            swap(array[current], array[parent]);
            current = parent;
        } else {
            break;
        }
    }
}

void binary_heap::insert(int prior, char const* val) {
    if (size >= capacity) {
        size_t new_capacity = (capacity == 0) ? 1 : capacity * 2;
        auto* new_array = new Node_binaryheap[new_capacity];

        for (size_t i = 0; i < size; i++) {
            new_array[i].priority = array[i].priority;
            if (array[i].value) {
                new_array[i].value = new char[strlen(array[i].value) + 1];
                strcpy(new_array[i].value, array[i].value);
            } else {
                new_array[i].value = nullptr;
            }
        }

        for (size_t i = 0; i < size; i++) {
            delete[] array[i].value;
        }
        delete[] array;

        array = new_array;
        capacity = new_capacity;
    }

    array[size].priority = prior;
    array[size].value = new char[strlen(val) + 1];
    strcpy(array[size].value, val);

    sifting_from_bottom_to_top(static_cast<int>(size));
    size++;
}

char const* binary_heap::remove_max() {
    if (size == 0 || array == nullptr)
        throw std::out_of_range("массив пуст");

    char* max_value = new char[strlen(array[0].value) + 1];
    strcpy(max_value, array[0].value);

    delete[] array[0].value;

    if (size > 1) {
        array[0] = array[size - 1];
    }
    size--;
    if (size > 0) {
        sifting_from_top_to_bottom(0);
    }
    return max_value;
}

char const* binary_heap::obtain_max() {
    if (size == 0)
        throw std::out_of_range("массив пуст");
    return array[0].value;
}

priority_queue* binary_heap::meld(priority_queue const* with)  {
    const binary_heap* other = static_cast<const binary_heap*>(with);
    size_t max_size = size + other->size;
    auto* new_heap = new binary_heap(max_size);
    new_heap->size = max_size;

    for (size_t i = 0; i < size; i++) { //элементы из первой кучи
        new_heap->array[i].priority = array[i].priority;
        if (array[i].value) {
            new_heap->array[i].value = new char[strlen(array[i].value) + 1];
            strcpy(new_heap->array[i].value, array[i].value);
        } else {
            new_heap->array[i].value = nullptr;
        }
    }

    for (size_t j = 0; j < other->size; j++) { //из второй кучи
        size_t temp = j + size;
        new_heap->array[temp].priority = other->array[j].priority;
        if (other->array[j].value) {
            new_heap->array[temp].value = new char[strlen(other->array[j].value) + 1];
            strcpy(new_heap->array[temp].value, other->array[j].value);
        } else {
            new_heap->array[temp].value = nullptr;
        }
    }

    for (int i = static_cast<int>(max_size / 2) - 1; i >= 0; --i) { //просеивание сверху вниз
        new_heap->sifting_from_top_to_bottom(i);
    }
    return new_heap;
}

priority_queue* binary_heap::merge(priority_queue* with) {
    binary_heap* other = static_cast<binary_heap*>(with);

    if (this == other) {
        return this;
    }

    size_t max_size = size + other->size;

    auto* new_array = new Node_binaryheap[max_size]; //делаем новый массив

    for (size_t i = 0; i < size; i++) { //копируем элементы из первой кучи
        new_array[i].priority = array[i].priority;
        if (array[i].value) {
            new_array[i].value = new char[strlen(array[i].value) + 1];
            strcpy(new_array[i].value, array[i].value);
        } else {
            new_array[i].value = nullptr;
        }
    }

    for (size_t j = 0; j < other->size; j++) { //из второй кучи
        new_array[size + j].priority = other->array[j].priority;
        if (other->array[j].value) {
            new_array[size + j].value = new char[strlen(other->array[j].value) + 1];
            strcpy(new_array[size + j].value, other->array[j].value);
        } else {
            new_array[size + j].value = nullptr;
        }
    }

    for (size_t i = 0; i < size; i++) {
        delete[] array[i].value;
    }
    delete[] array;

    for (size_t j = 0; j < other->size; j++) {
        delete[] other->array[j].value;
    }
    delete[] other->array;

    array = new_array;
    size = max_size;
    capacity = max_size;
    other->array = nullptr;
    other->size = 0;
    other->capacity = 0;

    for (int i = static_cast<int>(max_size / 2) - 1; i >= 0; --i) { //просеивание сверху вниз
        this->sifting_from_top_to_bottom(i);
    }

    return this;
}

void binary_heap::printer() {
    for (size_t i = 0; i < size; i++) {
        std::cout << array[i].priority << std::endl;
    }
}

int main() {
    binary_heap pupu(3);
    pupu.insert(12, "ff");
    pupu.insert(52, "dgh");
    pupu.insert(22, "fg");
    pupu.printer();

    return 0;
}
