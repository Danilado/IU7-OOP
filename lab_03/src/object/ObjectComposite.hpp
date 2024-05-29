#ifndef OBJECT_COMPOSITE_HPP
#define OBJECT_COMPOSITE_HPP

#include "Object.hpp"

class ObjectComposite : public Object {
private:
  ObjectVector vec;

public:
  ObjectComposite() = default;
  ObjectComposite(ObjectPtr first, ...);

  void accept(std::shared_ptr<BaseVisitor> vis) override;

  bool constexpr isComposite(void) const noexcept override;
  bool add(ObjectPtr &obj) override;
  bool add(std::unique_ptr<Object> obj) override;
  bool remove(const iterator &it) override;
  iterator begin() const noexcept override;
  iterator end() const noexcept override;
};

#endif
