#ifndef SINGLETON_TEMPLATE_HPP
#define SINGLETON_TEMPLATE_HPP

#include "my_concepts.hpp"
#include <memory>

template <OnlyObject Type> class Singleton {
private:
  static std::unique_ptr<Type> inst;

public:
  template <typename... Args> static Type &instance(Args &&...args) {
    struct Proxy : public Type {
      Proxy(Args &&...args) : Type(forward<Args>(args)...) {}
    };

    if (!inst)
      inst = make_unique<Proxy>(forward<Args>(args)...);

    return *inst;
  }

  Singleton() = delete;
  Singleton(const Singleton &) = delete;
  Singleton<Type> &operator=(const Singleton &) = delete;
};

template <OnlyObject Type> std::unique_ptr<Type> Singleton<Type>::inst{};

#endif
