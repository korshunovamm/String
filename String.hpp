#pragma once

#include <cstring>
#include <iostream>
#include <vector>

void SwapNotString(size_t& a, size_t& b);

void SwapNotString(char*& a, char*& b);

class String {
 private:
  size_t size_;
  char* str_;
  size_t capacity_;

 public:
  String();

  String(size_t, char);

  String(const String&);

  String(const char*);

  String& operator+=(const String&);

  String& operator*=(int);

  String& operator=(const String&);

  String& operator=(const char*);

  const char& operator[](size_t) const;

  char& operator[](size_t);

  std::vector<String> Split(const String& delim = " ");

  [[nodiscard]] String Join(const std::vector<String>&) const;

  [[nodiscard]] const char& Front() const;

  char& Front();

  [[nodiscard]] const char& Back() const;

  char& Back();

  bool operator<(const String&) const;

  bool operator>(const String&) const;

  bool operator<=(const String&) const;

  bool operator>=(const String&) const;

  bool operator==(const String&) const;

  bool operator!=(const String&) const;

  void Resize(size_t);

  void Resize(size_t, char);

  void Reserve(size_t);

  void PushBack(char);

  void PopBack();

  [[nodiscard]] size_t Capacity() const;

  [[nodiscard]] size_t Size() const;

  [[nodiscard]] const char* Data() const;

  [[nodiscard]] bool Empty() const;

  void ShrinkToFit();

  void Clear();

  void Swap(String&);

  ~String();
};

String operator*(const String&, int);

String operator+(const String&, const String&);

std::ostream& operator<<(std::ostream&, const String&);

std::istream& operator>>(std::istream&, String&);
