#include "Object.hpp"

Object::Object() { transform = std::make_unique<TransformationMatrix>(); }

Object::Object(std::unique_ptr<ObjectMemento> memento) {
  restoreMemento(std::move(memento));
}

Object::Object(const Object &origin) {
  transform = std::make_unique<TransformationMatrix>(*origin.transform);
}

void Object::accept(BaseVisitor &vis) {}

bool Object::isComposite() const noexcept { return false; }

bool Object::add(ObjectPtr &obj) { return false; }

bool Object::add(std::unique_ptr<Object> obj) { return false; }

bool Object::remove(const iterator &it) { return false; }

Object::iterator Object::begin() const noexcept { return Object::iterator(); }

Object::iterator Object::end() const noexcept { return Object::iterator(); }

std::unique_ptr<ObjectMemento> Object::createMemento(void) const {
  return std::make_unique<ObjectMemento>(*this);
}

void Object::restoreMemento(std::unique_ptr<ObjectMemento> memento) {
  transform = std::move(memento->get());
}

std::shared_ptr<TransformationMatrix> Object::getTransformation() {
  return transform;
}

ObjectMemento::ObjectMemento(const Object &o) { set(o); }

void ObjectMemento::set(const Object &o) {
  transform = std::make_unique<TransformationMatrix>(*o.transform);
}

std::unique_ptr<TransformationMatrix> ObjectMemento::get() {
  return std::move(transform);
}

ObjectCaretaker::MemPtr ObjectCaretaker::get(size_t id) {
  auto &saves = saveData[id].second;
  MemPtr res = nullptr;

  if (saves.size()) {
    res = saves.back();
    saves.pop_back();
  }

  clear_expired();

  return res;
}

void ObjectCaretaker::clear_expired() {
  auto tmp = saveData;

  for (auto [id, data] : tmp)
    if (data.first.expired())
      saveData.erase(id);
}

void ObjectCaretaker::set(size_t id, std::weak_ptr<Object> origin,
                          ObjectCaretaker::MemPtr memento) {
  saveData[id].first = origin;
  saveData[id].second.push_back(std::move(memento));

  clear_expired();
}
