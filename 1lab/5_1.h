class priority_queue
{

public:

    virtual ~priority_queue() noexcept = default;

    virtual void insert (int priority, char const *value) = 0;

    virtual char const *remove_max() = 0;

    virtual char const *obtain_max() = 0; //const char * - нельзя модифицировать значение под укзаателем

    virtual priority_queue *merge(priority_queue *with) = 0; //слияние с уничтожением

    virtual priority_queue *meld (priority_queue const *with)  = 0; //слияние без униточжения изначальных объектов

};
