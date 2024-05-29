#include "Object.hpp"

Object::Object() {
  id = 0;
  transform = std::make_unique<TransformationMatrix>();
}

Object::Object(std::unique_ptr<ObjectMemento> memento) {
  restoreMemento(std::move(memento));
}

Object::Object(const Object &origin) {
  id = origin.id;
  transform = std::make_unique<TransformationMatrix>(*origin.transform);
}

size_t Object::getId(void) const noexcept { return id; }

void Object::setId(size_t id) noexcept { this->id = id; };

void Object::accept(std::shared_ptr<BaseVisitor> vis) { vis->visit(*this); }

bool Object::isComposite(void) const noexcept { return false; }

bool Object::add(ObjectPtr &obj) { return false; }

bool Object::add(std::unique_ptr<Object> obj) { return false; }

bool Object::remove(const iterator &it) { return false; }

Object::iterator Object::begin() const noexcept { return Object::iterator(); }

Object::iterator Object::end() const noexcept { return Object::iterator(); }

std::unique_ptr<ObjectMemento> Object::createMemento(void) const {
  return std::make_unique<ObjectMemento>(*this);
}

void Object::restoreMemento(std::unique_ptr<ObjectMemento> memento) {
  transform.reset(memento->transform.release());
  id = memento->id;
}

std::unique_ptr<Object> Object::clone() const {
  return std::make_unique<Object>(*this);
}

ObjectMemento::ObjectMemento(const Object &o) { set(o); }

void ObjectMemento::set(const Object &o) {
  id = o.id;
  transform = std::make_unique<TransformationMatrix>(o.transform);
}

std::unique_ptr<Object> ObjectMemento::get() {
  return std::make_unique<Object>(*this);
}

std::unique_ptr<ObjectMemento> ObjectCaretaker::get() {
  if (!mementos.size())
    return nullptr;

  std::unique_ptr<ObjectMemento> last = std::move(mementos.back());
  mementos.pop_back();

  return last;
}

void ObjectCaretaker::set(std::unique_ptr<ObjectMemento> memento) {
  mementos.push_back(std::move(memento));
}
