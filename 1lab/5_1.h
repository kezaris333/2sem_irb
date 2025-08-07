#include <iostream>
#include <cstring>
#include <C:\Users\Миночка\Desktop\codes\binomial_priority\priority_queue.h>

class binary_heap : public priority_queue
{

public:

        class Node_binaryheap {
        public:
            int priority;
            char* value;
        };

    size_t size;
    Node_binaryheap *array = nullptr;
    size_t capacity;


public:

    binary_heap(size_t size_in);
    binary_heap(const binary_heap& other) ;
    binary_heap& operator= (const binary_heap& other);
    binary_heap(binary_heap&& other) noexcept;
    binary_heap& operator= (binary_heap&& other) noexcept;
    ~binary_heap() noexcept override;

public:


    void sifting_from_top_to_bottom (int current);
    void sifting_from_bottom_to_top (int current);

    void insert (int prior,  const char * val) override;
    void swap (Node_binaryheap& one, Node_binaryheap&two);
    void printer ();

    const char *remove_max() override;
    const char* obtain_max() override;

    priority_queue* merge(priority_queue* with) override;//слияние с уничтожением
    priority_queue* meld(priority_queue const* with) const override; //слияние без униточжения изначальных объектов

};
