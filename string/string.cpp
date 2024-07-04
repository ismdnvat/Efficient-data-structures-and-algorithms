#include "string.hpp"

#include <cstring>

String::String(size_t size, char character)
    : size_(size), capacity_(size), str_(new char[size_ + 1]) {
  std::memset(str_, character, size_);
  str_[size_] = '\0';
}

String::String(const char* str) {
  size_ = std::strlen(str);
  capacity_ = size_;
  str_ = new char[size_ + 1];
  std::memcpy(str_, str, size_);
  str_[size_] = '\0';
}

String::String(const String& str) {
  size_ = str.size_;
  capacity_ = str.capacity_;
  str_ = new char[capacity_ + 1];
  if (size_ > 0) {
    std::memcpy(str_, str.str_, size_);
  }
  str_[size_] = '\0';
}

String& String::operator=(const String& str) {
  String copy(str);
  Swap(copy);
  return *this;
}

String::~String() { delete[] str_; }

void String::Clear() { Resize(0); }

void String::PushBack(const char character) { Resize(size_ + 1, character); }

void String::PopBack() {
  if (size_ != 0) {
    --size_;
    str_[size_] = '\0';
  }
}

void String::Resize(const size_t new_size) { Resize(new_size, '\0'); }

void String::Resize(const size_t new_size, const char character) {
  if (capacity_ <= new_size) {
    Reserve(2 * new_size);
  }
  if (capacity_ == 0) {
    return;
  }
  if (new_size < size_) {
    for (size_t i = new_size; i < size_; ++i) {
      str_[i] = '\0';
    }
  } else {
    for (size_t i = size_; i < new_size; ++i) {
      str_[i] = character;
    }
  }
  size_ = new_size;
  str_[size_] = '\0';
}

void String::Reserve(const size_t new_capacity) {
  if (new_capacity > capacity_) {
    char* new_str = new char[new_capacity + 1];
    if (str_ != nullptr) {
      std::memcpy(new_str, str_, size_);
    }
    delete[] str_;
    capacity_ = new_capacity;
    str_ = new_str;
  }
}

void String::ShrinkToFit() {
  if (capacity_ != size_) {
    char* new_str = new char[size_ + 1];
    std::memcpy(new_str, str_, size_ + 1);
    delete[] str_;
    str_ = new_str;
    capacity_ = size_;
  }
}

void String::Swap(String& other) {
  std::swap(this->size_, other.size_);
  std::swap(this->capacity_, other.capacity_);
  std::swap(this->str_, other.str_);
}

char& String::operator[](size_t index) { return str_[index]; }

char const& String::operator[](size_t index) const { return str_[index]; }

char& String::Front() { return str_[0]; }

char const& String::Front() const { return str_[0]; }

char& String::Back() { return str_[size_ - 1]; }

char const& String::Back() const { return str_[size_ - 1]; }

bool String::Empty() const { return size_ == 0; }

size_t String::Size() const { return size_; }

size_t String::Capacity() const { return capacity_; }

char const* String::Data() const { return str_; }

std::vector<String> String::Split(String delim) {
  std::vector<String> answer;
  String item;
  size_t step = delim.Size();
  size_t current_size = 0;
  bool split = true;
  for (size_t i = 0; i < size_; ++i) {
    if (str_[i] == delim[0]) {
      for (size_t j = 1; j < step; ++j) {
        if (str_[i + j] != delim[j]) {
          split = false;
          break;
        }
      }
      if (split) {
        if (current_size > 0) {
          item.Resize(current_size);
          strncpy(item.str_, str_ + i - current_size, current_size);
          current_size = 0;
        }
        answer.push_back(item);
        item.Clear();
        i += step - 1;
      } else {
        ++current_size;
      }
      split = true;
    } else {
      ++current_size;
    }
  }
  if (current_size > 0) {
    item.Resize(current_size);
    strncpy(item.str_, str_ + size_ - current_size, current_size);
  }
  answer.push_back(item);
  return answer;
}

String String::Join(const std::vector<String>& strings) {
  String empty;
  if (strings.empty()) {
    return empty;
  }
  size_t size = size_ * (strings.size() - 1);
  for (auto& item : strings) {
    size += item.Size();
  }
  String answer(strings[0]);
  answer.Reserve(size);
  for (size_t i = 1; i < strings.size(); ++i) {
    answer += *this;
    answer += strings[i];
  }
  return answer;
}

bool operator<(String const& first, String const& second) {
  for (size_t i = 0; i < std::min(first.Size(), second.Size()); ++i) {
    if (first[i] > second[i]) {
      return false;
    }
    if (first[i] < second[i]) {
      return true;
    }
  }
  return first.Size() < second.Size();
}

bool operator>(String const& first, String const& second) {
  return !(first < second);
}

bool operator<=(String const& first, String const& second) {
  return (first < second) || (first == second);
}

bool operator>=(String const& first, String const& second) {
  return (first > second) || (first == second);
}

bool operator==(String const& first, String const& second) {
  if (first.Size() != second.Size()) {
    return false;
  }

  for (size_t i = 0; i < first.Size(); ++i) {
    if (first[i] != second[i]) {
      return false;
    }
  }
  return true;
}

bool operator!=(String const& first, String const& second) {
  return !(first == second);
}

String& String::operator+=(String const& str) {
  size_t old_size = size_;
  Resize(size_ + str.size_);
  std::memcpy(str_ + old_size, str.str_, str.size_);
  return *this;
}

String operator+(String const& first, String const& second) {
  String new_str(first);
  new_str += second;
  return new_str;
}

String& String::operator*=(size_t number) {
  size_t old_size = size_;
  Resize(size_ * number);
  for (size_t i = 1; i < number; ++i) {
    std::memcpy(str_ + i * old_size, str_, old_size);
  }
  return *this;
}

String operator*(String const& str, size_t number) {
  String new_str(str);
  new_str *= number;
  return new_str;
}

std::ostream& operator<<(std::ostream& out, String const& str) {
  out << str.Data();
  return out;
}

std::istream& operator>>(std::istream& in, String& str) {
  const size_t kMaxSize = 4096;
  char str_[kMaxSize];
  in >> str_;
  String copy(str_);
  str.Swap(copy);
  return in;
}
