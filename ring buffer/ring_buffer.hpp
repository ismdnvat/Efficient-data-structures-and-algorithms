#include <cstddef>
#include <vector>

class RingBuffer {
 public:
  RingBuffer() = default;

  explicit RingBuffer(size_t capacity) : buffer_(capacity){};

  size_t Size() const { return size_; }

  bool Empty() const { return size_ == 0; }

  bool TryPush(int element) {
    if (size_ >= buffer_.size()) {
      return false;
    }
    if (tail_ == buffer_.size()) {
      tail_ = 0;
    }
    buffer_[tail_] = element;
    ++tail_;
    ++size_;
    return true;
  }

  bool TryPop(int* element) {
    if (Empty()) {
      return false;
    }
    *element = buffer_[head_];
    buffer_[head_] = 0;
    ++head_;
    --size_;
    if (head_ == buffer_.size() && size_ < buffer_.size()) {
      head_ = 0;
    }
    return true;
  }

 private:
  size_t size_ = 0;
  size_t head_ = 0;
  size_t tail_ = 0;
  std::vector<int> buffer_;
};
