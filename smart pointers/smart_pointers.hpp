#include <iostream>
#include <memory>
#include <new>
#include <utility>

class SharedCount {
 public:
  explicit SharedCount(size_t count = 0) noexcept : shared_owners_(count) {}

  size_t use_count() const noexcept { return shared_owners_; }

  void add_shared() noexcept { ++shared_owners_; }

  void release_shared() noexcept {
    if (--shared_owners_ == 0) {
      zero_shared();
    }
  }

  virtual ~SharedCount() = default;

  virtual void zero_shared() noexcept = 0;

 protected:
  size_t shared_owners_;
};

class SharedWeakCount : public SharedCount {
 public:
  explicit SharedWeakCount(size_t count = 0) noexcept
      : SharedCount(count), shared_weak_owners_(0) {}

  void add_weak() noexcept { ++shared_weak_owners_; }

  void release_weak() noexcept {
    if (--shared_weak_owners_ == 0 && shared_owners_ == 0) {
      zero_shared_and_weak();
    }
  }

  virtual void zero_shared_and_weak() noexcept = 0;

 protected:
  size_t shared_weak_owners_;
};

template <typename T, typename Deleter = std::default_delete<T>>
class SharedPtrPointer : public SharedWeakCount {
 public:
  explicit SharedPtrPointer(T* value, Deleter deleter = Deleter())
      : value_(value), deleter_(deleter) {}

  void zero_shared() noexcept override {
    deleter_(value_);
    value_ = nullptr;
    if (shared_weak_owners_ == 0) {
      delete this;
    }
  }

  void zero_shared_and_weak() noexcept override { delete this; }

 private:
  T* value_;
  Deleter deleter_;
};

template <typename T>
class ControlBlockBase : public SharedWeakCount {
 public:
  virtual T* get_value() noexcept = 0;
};

template <typename T>
class ControlBlock : public ControlBlockBase<T> {
 public:
  template <typename... Args>
  ControlBlock(Args&&... args) : value_(std::forward<Args>(args)...) {}

  void zero_shared() noexcept override {
    value_.~T();
    if (this->shared_weak_owners_ == 0) {
      delete this;
    }
  }

  void zero_shared_and_weak() noexcept override { delete this; }

  T* get_value() noexcept override { return &value_; }

 private:
  T value_;
};

template <typename T>
class SharedPtr {
 public:
  SharedPtr() noexcept : element_ptr_(nullptr), control_ptr_(nullptr) {}

  template <typename U>
  SharedPtr(U* ptr) : element_ptr_(ptr) {
    control_ptr_ = new SharedPtrPointer<U>(ptr);
    control_ptr_->add_shared();
  }

  SharedPtr(std::nullptr_t) noexcept
      : element_ptr_(nullptr), control_ptr_(nullptr) {}

  SharedPtr(const SharedPtr& other) noexcept
      : element_ptr_(other.element_ptr_), control_ptr_(other.control_ptr_) {
    if (control_ptr_ != nullptr) {
      control_ptr_->add_shared();
    }
  }

  SharedPtr(SharedPtr&& other) noexcept
      : element_ptr_(other.element_ptr_), control_ptr_(other.control_ptr_) {
    other.element_ptr_ = nullptr;
    other.control_ptr_ = nullptr;
  }

  SharedPtr& operator=(const SharedPtr& other) noexcept {
    SharedPtr(other).swap(*this);
    return *this;
  }

  SharedPtr& operator=(SharedPtr&& other) noexcept {
    SharedPtr(std::move(other)).swap(*this);
    return *this;
  }

  SharedPtr& operator=(std::nullptr_t) noexcept {
    SharedPtr().swap(*this);
    return *this;
  }

  template <typename U>
  SharedPtr(const SharedPtr<U>& other) noexcept
      : element_ptr_(other.element_ptr_), control_ptr_(other.control_ptr_) {
    if (control_ptr_) {
      control_ptr_->add_shared();
    }
  }

  template <typename U>
  SharedPtr<T>& operator=(const SharedPtr<U>& other) noexcept {
    SharedPtr(other).swap(*this);
    return *this;
  }

  ~SharedPtr() {
    if (control_ptr_ != nullptr) {
      control_ptr_->release_shared();
    }
  }

  size_t use_count() const noexcept {
    return (control_ptr_ != nullptr) ? control_ptr_->use_count() : 0;
  }

  T* get() const noexcept { return element_ptr_; }

  T& operator*() const noexcept { return *element_ptr_; }

  T* operator->() const noexcept { return element_ptr_; }

  void reset() noexcept { SharedPtr().swap(*this); }

  template <typename U, typename... Args>
  friend SharedPtr<U> MakeShared(Args&&... args);

 private:
  template <typename U>
  friend class WeakPtr;

  template <typename U>
  friend class SharedPtr;

  void swap(SharedPtr& other) noexcept {
    std::swap(element_ptr_, other.element_ptr_);
    std::swap(control_ptr_, other.control_ptr_);
  }

  T* element_ptr_;
  SharedWeakCount* control_ptr_;
};

template <typename T, typename... Args>
SharedPtr<T> MakeShared(Args&&... args) {
  auto control_block = new ControlBlock<T>(std::forward<Args>(args)...);
  SharedPtr<T> shared_ptr;
  shared_ptr.control_ptr_ = control_block;
  shared_ptr.element_ptr_ = control_block->get_value();
  control_block->add_shared();
  return shared_ptr;
}

template <typename T>
class WeakPtr {
 public:
  WeakPtr() noexcept : element_ptr_(nullptr), control_ptr_(nullptr) {}

  WeakPtr(const WeakPtr& other) noexcept
      : element_ptr_(other.element_ptr_), control_ptr_(other.control_ptr_) {
    if (control_ptr_ != nullptr) {
      control_ptr_->add_weak();
    }
  }

  WeakPtr(WeakPtr&& other) noexcept
      : element_ptr_(other.element_ptr_), control_ptr_(other.control_ptr_) {
    other.element_ptr_ = nullptr;
    other.control_ptr_ = nullptr;
  }

  template <typename U>
  WeakPtr(const WeakPtr<U>& other) noexcept
      : element_ptr_(other.element_ptr_), control_ptr_(other.control_ptr_) {
    if (control_ptr_) {
      control_ptr_->add_weak();
    }
  }

  WeakPtr(const SharedPtr<T>& other) noexcept
      : element_ptr_(other.element_ptr_), control_ptr_(other.control_ptr_) {
    if (control_ptr_ != nullptr) {
      control_ptr_->add_weak();
    }
  }

  WeakPtr<T>& operator=(const WeakPtr& other) noexcept {
    WeakPtr(other).swap(*this);
    return *this;
  }

  WeakPtr<T>& operator=(WeakPtr&& other) noexcept {
    WeakPtr(std::move(other)).swap(*this);
    return *this;
  }

  template <typename U>
  WeakPtr<T>& operator=(const WeakPtr<U>& other) noexcept {
    WeakPtr(other).swap(*this);
    return *this;
  }

  ~WeakPtr() {
    if (control_ptr_ != nullptr) {
      control_ptr_->release_weak();
    }
  }

  bool expired() const noexcept {
    return (control_ptr_ == nullptr) || control_ptr_->use_count() == 0;
  }

  SharedPtr<T> lock() const noexcept {
    SharedPtr<T> smart_ptr;
    if ((control_ptr_ != nullptr) && control_ptr_->use_count() > 0) {
      smart_ptr.element_ptr_ = element_ptr_;
      smart_ptr.control_ptr_ = control_ptr_;
      control_ptr_->add_shared();
    }
    return smart_ptr;
  }

 private:
  template <typename U>
  friend class SharedPtr;

  void swap(WeakPtr& other) noexcept {
    std::swap(element_ptr_, other.element_ptr_);
    std::swap(control_ptr_, other.control_ptr_);
  }

  T* element_ptr_;
  SharedWeakCount* control_ptr_;
};
