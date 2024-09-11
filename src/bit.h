#ifndef HK_CHIP8_BIT_H
#define HK_CHIP8_BIT_H

namespace chip8 {
template <typename T>
class integer_iterator {
 public:
  static constexpr auto SIZE = sizeof(T) * 8;

  explicit integer_iterator(T& item, std::size_t idx = SIZE)
      : m_item(&item), m_idx(idx) {}

  auto operator==(const integer_iterator&) const -> bool = default;

  auto operator++() -> integer_iterator& {
    m_idx++;
    return *this;
  }

  auto operator++(int) -> integer_iterator {
    auto old = *this;
    operator++();
    return old;
  }

  auto operator--() -> integer_iterator& {
    m_idx--;

    if (m_idx > SIZE) {
      m_idx = SIZE;
    }

    return *this;
  }

  auto operator--(int) -> integer_iterator {
    auto old = *this;
    operator--();
    return old;
  }

  auto operator*() const -> bool {
    return static_cast<bool>(*m_item & (1 << m_idx));
  }

 private:
  T* m_item;
  std::size_t m_idx;
};

using byte_iterator = integer_iterator<byte>;

template <typename T>
auto begin(T& value) -> integer_iterator<T> {
  return integer_iterator<byte>(value, 0);
}

template <typename T>
auto end(T& value) -> integer_iterator<T> {
  return integer_iterator<byte>(value);
}
}  // namespace chip8

#endif
