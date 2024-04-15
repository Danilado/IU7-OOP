#ifndef BASE_CONTAINER_HPP
#define BASE_CONTAINER_HPP

#include <cstdlib>

class BaseContainer {
public:
  BaseContainer() noexcept;
  BaseContainer(size_t size) noexcept;
  virtual ~BaseContainer() = 0;

  size_t getSize() const noexcept;
  bool isEmpty() const noexcept;

protected:
  size_t size = 0;
};

#endif
