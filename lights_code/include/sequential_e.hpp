#ifndef SEQUENTIAL_EFFECTS_HPP
#define SEQUENTIAL_EFFECTS_HPP

#include "lighting_defs.hpp"
#include <queue>

class BaseSequential: public AnimatedLightingEffect{
public:
    BaseSequential(CRGB* data, uint32_t nLeds, CRGB color, uint32_t delay, uint8_t fade_amt, uint trail_size, uint start_pos=0, int8_t dir=1);

    virtual void draw_frame();
    virtual void reset();

protected:
    virtual void update_status();
    virtual void update_frame();

    uint8_t fade_amt;
    uint trail_size;
    uint start_pos;
    uint pos;
    int8_t dir;     // 1 for increasing array, -1 for decreasing
};

class SequentialBounce: public BaseSequential{
public:
    SequentialBounce(CRGB* data, uint32_t nLeds, CRGB color, uint32_t delay, uint8_t fade_amt, uint trail_size, uint start_pos=0, int8_t start_dir=1);
    void draw_frame();
    void reset();

protected:
    void update_status();
    void update_frame();

    int8_t start_dir;   // keep track of set direction for resetting
};

// Circular queue/array that is currently only used for this effect
class CircularQueue{
public:
    CircularQueue(uint32_t size){
        size = size;
        array = new uint8_t[size];
        front = 0;
        back = 0;
        len = 0;
        memset(array, 0, size * sizeof(uint8_t));
    }
    ~CircularQueue(){
        delete[] array;
    }

    bool isFull(){
        return front == back && len != 0;
    }

    bool isEmpty(){
        return len == 0;
    }

    uint8_t& operator[](uint32_t i){
        return array[(front + i) % size];
    }

    void queue(uint32_t val){
        if (isFull()){
            printf("q die\n");
            //raise;
            return;
        }
        array[back] = val;
        back = (back + 1) % size;
        len++;
    }

    uint8_t dequeue(){
        if (isEmpty()){
            printf("dq die\n");
            //raise;
            return 0;
        }
        uint32_t ret = array[front];
        front = (front + 1) % size;
        len--;
        return ret;
    }

    void clear(){
        len = 0;
        front = 0;
        back = 0;
        // memset(array, 0, size * sizeof(uint8_t));
    }

    uint32_t len;

private:
    uint8_t* array;
    uint32_t size;
    uint32_t front;
    uint32_t back;
};

// Sequential fade but the fade amt is random
class SequentialComet: public BaseSequential{
public:
    SequentialComet(CRGB* data, uint32_t nLeds, CRGB color, uint32_t delay, uint8_t fade_amt, uint trail_size, uint start_pos=0, int8_t dir=1);
    ~SequentialComet();

    void draw_frame();
    void reset();

protected:
    void update_frame();
    void draw_trail(uint32_t index);

    //CircularQueue trail_brightness_queue;
    std::queue<uint8_t> trail_brightness_queue;

};

#endif
