#pragma once

#include <iostream>
#include <cstddef>
#include <algorithm>

class DynamicArray{
  public:
    DynamicArray():mPtrData(nullptr),mSize(0),mCapacity(0){}
    ~DynamicArray();
    inline size_t GetSize() const;
    inline size_t GetCapacity() const;
    bool Init(const size_t capacity = INITIAL_CAPACITY);
    bool Reserve(const size_t capacity);
    bool Resize(const size_t capactiy);
    bool PushBack(const int element);
    bool PopBack(int &element);
    const int &operator[](const size_t index) const;
    int &operator[](const size_t index);
    void Print();

  private:
    int *mPtrData;
    size_t mSize;
    size_t mCapacity;
    const static size_t INITIAL_CAPACITY = 10;
};
