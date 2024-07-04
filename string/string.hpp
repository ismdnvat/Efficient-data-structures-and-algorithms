#pragma once

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <istream>
#include <ostream>
#include <vector>

class String {
 public:
  String() = default;
  String(size_t size, char character);
  String(const char* str);
  String(String const& str);
  String& operator=(const String& str);
  ~String();

  void Clear();
  void PushBack(char character);
  void PopBack();
  void Resize(size_t new_size);
  void Resize(size_t new_size, char character);
  void Reserve(size_t new_cap);
  void ShrinkToFit();
  void Swap(String& other);
  char& operator[](size_t index);
  char const& operator[](size_t index) const;
  char& Front();
  char const& Front() const;
  char& Back();
  char const& Back() const;
  bool Empty() const;
  size_t Size() const;
  size_t Capacity() const;
  char const* Data() const;
  std::vector<String> Split(String delim = String(" "));
  String& operator+=(String const& str);
  String& operator*=(size_t number);
  String Join(const std::vector<String>& strings);

 private:
  size_t capacity_ = 0;
  size_t size_ = 0;
  char* str_ = nullptr;
};

bool operator<(String const& first, String const& second);
bool operator>(String const& first, String const& second);
bool operator<=(String const& first, String const& second);
bool operator>=(String const& first, String const& second);
bool operator==(String const& first, String const& second);
bool operator!=(String const& first, String const& second);
String operator+(String const& first, String const& second);
String operator*(String const& str, size_t number);

std::ostream& operator<<(std::ostream& out, String const& str);
std::istream& operator>>(std::istream& in, String& str);
