#include "ObjectComposite.hpp"

ObjectComposite::ObjectComposite(ObjectPtr first, ...) {
  for (std::shared_ptr<Object> *ptr = &first; *ptr; ++ptr)
    vec.push_back(*ptr);
}

void ObjectComposite::accept(std::shared_ptr<BaseVisitor> vis) {
  for (auto &obj : vec)
    obj->accept(vis);
}

bool constexpr ObjectComposite::isComposite(void) const noexcept {
  return true;
}

bool ObjectComposite::add(ObjectPtr &obj) {
  vec.push_back(obj);
  return true;
}

bool ObjectComposite::add(std::unique_ptr<Object> obj) {
  vec.push_back(std::shared_ptr<Object>(std::move(obj)));
  return true;
}

bool ObjectComposite::remove(const iterator &it) {
  vec.erase(it);
  return true;
}

Object::iterator ObjectComposite::begin() const noexcept { return vec.begin(); }

Object::iterator ObjectComposite::end() const noexcept { return vec.end(); }
