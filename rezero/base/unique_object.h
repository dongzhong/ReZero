// Created by Dong Zhong on 2021/09/15.

#ifndef REZERO_BASE_UNIQUE_OBJECT_H_
#define REZERO_BASE_UNIQUE_OBJECT_H_

#include <utility>

#include "rezero/base/logging.h"
#include "rezero/base/macros.h"

namespace rezero {

// struct UniqueFooTraits {
//   static int InvalidValue() { return 0; }
//   static boo IsValid(const T& value) { return value != InvalidValue(); }
//   static void Free(int f) { ::FreeFoo(f); }
// };
template <typename T, typename Traits>
class UniqueObject {
 private:
  struct Data : public Traits {
    explicit Data(const T& in) : generic(in) {}
    Data(const T& in, const Traits& other) : Traits(other), generic(in) {}

    T generic;
  };

 public:
  using element_type = T;
  using traits_type = Traits;

  UniqueObject() : data_(Traits::InvalidValue()) {}
  explicit UniqueObject(const T& value) : data_(value) {}

  UniqueObject(const T& value, const Traits& traits) : data_(value, traits) {}

  UniqueObject(UniqueObject&& other)
      : data_(other.release(), other.get_traits) {}

  ~UniqueObject() { FreeIfNecessary(); }

  UniqueObject& operator=(UniqueObject&& other) {
    reset(other.release());
    return *this;
  }

  void reset(const T& value = Traits::InvalidValue()) {
    REZERO_CHECK(data_.generic == Traits::InvalidValue() ||
                 data_.generic != value);
    FreeIfNecessary();
    data_.generic = value;
  }

  void swap(UniqueObject& other) {
    using std::swap;
    swap(static_cast<Traits&>(data_), static_cast<Traits&>(other.data_));
    swap(data_.generic, other.data_.generic);
  }

  [[nodiscard]] T release() {
    T old_generic = data_.generic;
    data_.generic = Traits::InvalidValue();
    return old_generic;
  }

  const T& get() const { return data_.generic; }

  bool is_valid() const { return Traits::IsValid(data_.generic); }

  bool operator==(const T& value) const { return data_.generic == value; }

  bool operator!=(const T& value) const { return data_.generic != value; }

  Traits& get_traits() { return data_; }
  const Traits& get_traits() const { return data_; }

 private:
  void FreeIfNecessary() {
    if (data_.generic != Traits::InvalidValue()) {
      data_.Free(data_.generic);
      data_.generic = Traits::InvalidValue();
    }
  }

  template <typename T2, typename Traits2>
  bool operator==(const UniqueObject<T2, Traits2>& p2) const = delete;

  template <typename T2, typename Traits2>
  bool operator!=(const UniqueObject<T2, Traits2>& p2) const = delete;

  Data data_;

  REZERO_DISALLOW_COPY_AND_ASSIGN(UniqueObject);
};

template <typename T, typename Traits>
void swap(const UniqueObject<T, Traits>& a, const UniqueObject<T, Traits>& b) {
  a.swap(b);
}

template <typename T, typename Traits>
bool operator==(const T& value, const UniqueObject<T, Traits>& object) {
  return value == object.get();
}

template <typename T, typename Traits>
bool operator!=(const T& value, const UniqueObject<T, Traits>& object) {
  return !(value == object.get());
}

} // namespace rezero

#endif // REZERO_BASE_UNIQUE_OBJECT_H_