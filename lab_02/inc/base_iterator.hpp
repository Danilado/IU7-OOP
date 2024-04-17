#ifndef BASE_ITERATOR_HPP
#define BASE_ITERATOR_HPP

#include <cstdlib>

// abstract
class BaseIterator {
public:
  BaseIterator();
  explicit BaseIterator(const BaseIterator &iter);
  virtual ~BaseIterator() = 0;

protected:
  size_t index;
  size_t size;
};

#endif
