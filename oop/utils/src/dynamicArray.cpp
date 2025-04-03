#include "dynamicArray.hpp"

DynamicArray::~DynamicArray() {
  delete[] this->mPtrData;
  this->mCapacity = 0;
  this->mSize = 0;
  this->mPtrData = nullptr;
  std::cout << "dynamic array destroyed" << std::endl;
}

inline size_t DynamicArray::GetSize() const { return this->mSize; }

inline size_t DynamicArray::GetCapacity() const { return this->mCapacity; }

bool DynamicArray::Init(const size_t capacity) {
  this->mPtrData = new int[capacity];
  this->mCapacity = capacity;
  this->mSize = 0;
  for (size_t i = 0; i < capacity; i++) {
    this->mPtrData[i] = 0;
  }
  return true;
}

bool DynamicArray::Reserve(const size_t capacity) {
  if (capacity <= this->mCapacity) {
    std::cout << "new capacity less or equal than current capacity"
              << std::endl;
    return true;
  }

  int *newMemBlock = new int[capacity];
  for (size_t i = 0; i < this->mSize; i++) {
    newMemBlock[i] = this->mPtrData[i];
  }

  delete[] this->mPtrData;
  this->mPtrData = newMemBlock;
  this->mCapacity = capacity;
  return true;
}

bool DynamicArray::Resize(const size_t capactiy) {
  if (capactiy > this->mCapacity) {
    this->Reserve(capactiy);
  }

  return true;
}

bool DynamicArray::PushBack(const int element) {
  if (this->mCapacity >= this->mSize) {
    Reserve(this->mCapacity == 0 ? 1 : this->mCapacity + 1);
  }

  this->mPtrData[this->mSize] = element;

  ++this->mSize;
  return true;
}

bool DynamicArray::PopBack(int &element) {
  if (this->mSize == 0) {
    std::cout << "nothing to pop" << std::endl;
    return true;
  }

  --this->mSize;
  element = this->mPtrData[this->mSize];
  return true;
}

const int &DynamicArray::operator[](const size_t index) const {
  return this->mPtrData[index];
}

int &DynamicArray::operator[](const size_t index) {
  return this->mPtrData[index];
}

void DynamicArray::Print() {
  for (size_t i = 0; i < this->mCapacity; i++) {
    std::cout << this->mPtrData[i] << " ";
  }
  std::cout << std::endl;
}
