#include "String.hpp"

void SwapNotString(size_t& a, size_t& b) {
  size_t c;
  c = a;
  a = b;
  b = c;
}

void SwapNotString(char*& a, char*& b) {
  char* c;
  c = a;
  a = b;
  b = c;
}

String::String() : size_(0), str_(nullptr), capacity_(size_) {}

String::String(size_t size, const char kCharacter = '\0')
    : size_(size), str_(new char[size]), capacity_(size) {
  memset(str_, kCharacter, size);
}

String::String(const String& string)
    : size_(string.size_), str_(new char[size_]), capacity_(size_) {
  memcpy(str_, string.str_, size_);
}

String::String(const char* string)
    : size_(strlen(string)), str_(new char[size_ + 1]), capacity_(size_ + 1) {
  memcpy(str_, string, capacity_);
}

String& String::operator+=(const String& string) {
  size_t old_size = size_;
  if (string.size_ + size_ > capacity_) {
    this->Resize(string.size_ + this->size_);
  }
  size_ = old_size + string.size_;
  memcpy(str_ + old_size, string.str_, string.size_);
  return *this;
}

String& String::operator*=(int n) {
  if (n == 0) {
    this->Clear();
  } else {
    String initial_string = *this;
    for (int i = 0; i < n - 1; ++i) {
      for (int j = 0; j < initial_string.size_; ++j) {
        this->PushBack(initial_string[j]);
      }
    }
  }
  return *this;
}

String& String::operator=(const String& string) {
  if (this != &string) {
    this->Clear();
    this->Resize(string.size_);
    memcpy(this->str_, string.str_, string.size_);
  }
  return *this;
}

String& String::operator=(const char* string) {
  String copy(string);
  *this = copy;
  return *this;
}

const char& String::operator[](size_t index) const { return str_[index]; }

char& String::operator[](size_t index) { return str_[index]; }

const char& String::Front() const { return str_[0]; }

char& String::Front() { return str_[0]; }

const char& String::Back() const { return str_[size_ - 1]; }

char& String::Back() { return str_[size_ - 1]; }

bool String::operator<(const String& string) const {
  size_t min_size;
  min_size = size_ < string.size_ ? size_ : string.size_;
  for (int i = 0; i < min_size; ++i) {
    if (str_[i] > string.str_[i]) {
      return false;
    }
  }
  return size_ <= string.size_;
}

bool String::operator>(const String& string) const {
  size_t min_size;
  min_size = size_ < string.size_ ? size_ : string.size_;
  for (int i = 0; i < min_size; ++i) {
    if (str_[i] < string.str_[i]) {
      return false;
    }
  }
  return size_ >= string.size_;
}

bool String::operator<=(const String& string) const {
  size_t min_size;
  min_size = size_ < string.size_ ? size_ : string.size_;
  for (int i = 0; i < min_size; ++i) {
    if (str_[i] > string.str_[i]) {
      return false;
    }
  }
  return size_ <= string.size_;
}

bool String::operator>=(const String& string) const {
  size_t min_size;
  min_size = size_ < string.size_ ? size_ : string.size_;
  for (int i = 0; i < min_size; ++i) {
    if (str_[i] < string.str_[i]) {
      return false;
    }
  }
  return size_ >= string.size_;
}

bool String::operator==(const String& string) const {
  if (size_ != string.size_) {
    return false;
  }
  for (int i = 0; i < size_; ++i) {
    if (str_[i] != string.str_[i]) {
      return false;
    }
  }
  return true;
}

bool String::operator!=(const String& string) const {
  return !(*this == string);
}

void String::Resize(size_t new_size, const char kCharacter) {
  if (capacity_ < new_size) {
    char* new_size_str = new char[new_size];
    memset(new_size_str, kCharacter, new_size);
    memcpy(new_size_str, str_, size_);
    delete[] str_;
    this->str_ = new_size_str;
    this->size_ = new_size;
    this->capacity_ = new_size;
  } else if (size_ > new_size) {
    size_ = new_size;
  }
}

void String::Resize(size_t new_size) {
  if (capacity_ < new_size) {
    char* new_size_str = new char[new_size];
    memcpy(new_size_str, str_, size_);
    delete[] str_;
    this->str_ = new_size_str;
    this->capacity_ = new_size;
  }
  size_ = new_size;
}

void String::Reserve(size_t new_cap) {
  if (new_cap > capacity_) {
    size_t old_size = size_;
    this->Resize(new_cap);
    size_ = old_size;
  }
}

void String::PushBack(const char kCharacter) {
  if (capacity_ == size_) {
    size_t push_index = size_;
    if (size_ == 0) {
      this->Resize(1);
    } else {
      this->Resize(2 * size_);
    }
    str_[push_index] = kCharacter;
    size_ = size_ / 2 + 1;
  } else if (capacity_ > size_) {
    str_[size_] = kCharacter;
    ++size_;
  }
}

void String::PopBack() {
  if (size_ > 0) {
    --size_;
  }
}

std::vector<String> String::Split(const String& delim) {
  std::vector<String> vect;
  String string_before_delim;
  bool is_delim = true;
  for (size_t i = 0; i < size_; ++i) {
    if (str_[i] == delim[0]) {
      for (size_t j = 0; j < delim.size_; j++) {
        if (i + j >= size_ || str_[i + j] != delim[j]) {
          is_delim = false;
          break;
        }
      }
      if (is_delim) {
        vect.push_back(string_before_delim);
        string_before_delim.Clear();
        i += delim.size_ - 1;
      } else {
        string_before_delim.PushBack(str_[i]);
        is_delim = true;
      }
    } else {
      string_before_delim.PushBack(str_[i]);
      is_delim = true;
    }
  }
  vect.push_back(string_before_delim);
  return vect;
}

String String::Join(const std::vector<String>& string) const {
  String empty_string;
  for (int i = 0; i < string.size(); ++i) {
    empty_string += string[i];
    if (i < string.size() - 1) {
      empty_string += *this;
    }
  }
  return empty_string;
}

size_t String::Capacity() const { return capacity_; }

size_t String::Size() const { return size_; }

const char* String::Data() const { return str_; }

bool String::Empty() const { return size_ == 0; }

void String::ShrinkToFit() {
  if (capacity_ > size_) {
    capacity_ = size_;
  }
}

void String::Clear() {
  size_ = 0;
  capacity_ = 0;
  delete[] str_;
  str_ = nullptr;
}

void String::Swap(String& string) {
  SwapNotString(size_, string.size_);
  SwapNotString(str_, string.str_);
  SwapNotString(capacity_, string.capacity_);
}

String::~String() { delete[] str_; }

std::ostream& operator<<(std::ostream& out, const String& string) {
  for (size_t i = 0; i < string.Size(); ++i) {
    out << string.Data()[i];
  }
  return out;
}

std::istream& operator>>(std::istream& in, String& string) {
  string.Clear();
  char character;
  while (in.get(character) && character != '\n') {
    string.PushBack(character);
  }
  return in;
}

String operator*(const String& string, int n) {
  String result = string;
  return result *= n;
}

String operator+(const String& string1, const String& string2) {
  String result = string1;
  return result += string2;
}
