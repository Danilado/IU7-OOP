#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "CommonUsings.hpp"
#include "TransformationMatrix.hpp"

#include "JSONStringifyVisitor.hpp"
#include "RotateObjectVisitor.hpp"
#include "ScaleObjectVisitor.hpp"
#include "TranslateObjectVisitor.hpp"

#include <memory>
#include <vector>

class ObjectMemento;

class Object {
  friend JSONStringifyVisitor;
  friend RotateObjectVisitor;
  friend ScaleObjectVisitor;
  friend TranslateObjectVisitor;
  friend ObjectMemento;

protected:
  size_t id;
  std::unique_ptr<TransformationMatrix> transform;

public:
  using value_type = Object;
  using size_type = size_t;
  using iterator = ObjectVector::const_iterator;
  using const_iterator = ObjectVector::const_iterator;

  Object();
  explicit Object(std::unique_ptr<ObjectMemento> memento);
  Object(const Object &origin);
  virtual ~Object() = default;

  size_t getId(void) const noexcept;
  void setId(size_t id) noexcept;

  virtual void accept(std::shared_ptr<BaseVisitor> vis);
  virtual bool isVisible(void) const noexcept = 0;

  virtual bool constexpr isComposite(void) const noexcept;
  virtual bool add(ObjectPtr &obj);
  virtual bool add(std::unique_ptr<Object> obj);
  virtual bool remove(const iterator &it);
  virtual iterator begin() const noexcept;
  virtual iterator end() const noexcept;

  virtual std::unique_ptr<ObjectMemento> createMemento(void) const;
  void restoreMemento(std::unique_ptr<ObjectMemento> memento);

  virtual std::unique_ptr<Object> clone() const;
};

class ObjectMemento {
  friend class Object;

private:
  size_t id;
  std::unique_ptr<TransformationMatrix> transform;
  void set(const Object &o);
  std::unique_ptr<Object> get();

public:
  ObjectMemento(const Object &o);
};

class ObjectCaretaker {
private:
  std::vector<std::unique_ptr<ObjectMemento>> mementos;

public:
  std::unique_ptr<ObjectMemento> get();
  void set(std::unique_ptr<ObjectMemento> memento);
};

#endif
