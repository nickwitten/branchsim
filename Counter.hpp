#ifndef COUNTER_H
#define COUNTER_H

#include <cstdint>


class Counter {

    private:

    /* TODO: Create any private variables you need here */
    char m_Val;

    public:
    Counter() : Counter(2) {}
    /* This constructor should initialize the counter (which is width bits) to
       weakly not taken! */
    Counter(uint64_t width);

    /* Transition in the Saturating Counter state diagram according to this branch
       being taken or not taken */
    void update(bool taken);

    /* Return current counter value */
    uint64_t get();

    /* Return true if the current counter is weakly taken or greater */
    bool isTaken();

    /* Set counter value */
    void setCount(uint64_t count);

    /* Return true if the current counter is in the weakly taken or weakly
       not-taken states */
    bool isWeak();

    /* Set this counter to either weakly taken (if taken==true) or weakly not
       taken (if taken==false).*/
    void reset(bool taken);
};




#endif
