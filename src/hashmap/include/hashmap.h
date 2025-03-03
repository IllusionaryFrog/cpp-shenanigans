#pragma once

#include <cstdint>
#include <cstddef>
#include <memory>

namespace shenanigans {

template<typename K, typename V>
class hashmap {
public:
  hashmap() noexcept : _items(nullptr), _size(0), _capacity(0) {}

  hashmap(size_t capacity) : _items(std::make_unique<Item[]>(capacity * 2)), _size(0), _capacity(capacity * 2) {}

  size_t size() const noexcept {
    return _size;
  }

  size_t capacity() const noexcept {
    return _capacity / 2;
  }

  bool empty() const noexcept {
    return _size == 0;
  }

  void clear() noexcept {
    for (int i=0; i<_capacity; i++) _items[i].used = false;
    _size = 0;
  }

  void reserve(size_t capacity) {
    if (capacity > SIZE_MAX / 2) throw "TODO";
    if ((capacity *= 2) <= _capacity) return;

    std::unique_ptr<Item[]> items = std::make_unique<Item[]>(capacity);

    for (int i=0; i<_capacity; i++) {
      if (_items[i].used) {
        size_t index = _items[i].hash % capacity;
        while (items[index].used) index = (index + 1) % capacity;
        items[index] = _items[i];
      }
    }

    _capacity = capacity;
    _items = std::move(items);
  }

  void insert(const K& key, const V& value) {
    if(_capacity / 2 <= _size) reserve(_capacity == 0 ? 8 : _capacity);

    size_t hash = std::hash<K>{}(key);
    size_t index = hash % _capacity;
    while (_items[index].used) {
      if (_items[index].hash == hash) throw "TODO";
      index = (index + 1) % _capacity;
    }

    _size++;
    _items[index].key = key;
    _items[index].value = value;
    _items[index].hash = hash;
    _items[index].used = true;
  }

  void remove(const K& key) {
    if (_capacity != 0) {
      size_t hash = std::hash<K>{}(key);
      size_t index = hash % _capacity, curr = index;

      while (_items[curr].used) {
        size_t next = (curr + 1) % _capacity;

        if (_items[curr].hash == hash) {
          size_t prev = (index - 1) % _capacity;
          while (_items[prev].used) prev = ((index = prev) - 1) % _capacity;

          while (true) {
            size_t last = curr;

            while (_items[next].used) {
              size_t _index = _items[next].hash % _capacity;
              if ((index <= curr && _index >= index && _index <= curr)
                  || (index > curr && (_index >= index || _index <= curr)))
                last = next;
              next = (next + 1) % _capacity;
            }

            if (last != curr) {
              _items[curr] = _items[last];
              next = ((curr = last) + 1) % _capacity;
            } else {
              _items[curr].used = false;
              break;
            }
          }

          _size--;
          return;
        }

        curr = next;
      }
    }
    throw "TODO";
  }

  V& get(const K& key) const {
    if (_capacity != 0) {
      size_t hash = std::hash<K>{}(key);
      size_t index = hash % _capacity;
      while (_items[index].used) {
        if (_items[index].hash == hash) return _items[index].value;
        index = (index + 1) % _capacity;
      }
    }
    throw "TODO";
  }

private:
  struct Item {
    K key;
    V value;
    size_t hash;
    bool used;
  };

  size_t _size;
  size_t _capacity;
  std::unique_ptr<Item[]> _items;
};

}
