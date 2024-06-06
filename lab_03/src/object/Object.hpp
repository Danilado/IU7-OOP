#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "BaseVisitor.hpp"
#include "CommonUsings.hpp"
#include "TransformationMatrix.hpp"

#include <map>
#include <memory>
#include <vector>

class ObjectMemento;
class JsonStringifyVisitor;
class RotateObjectVisitor;
class ScaleObjectVisitor;
class TranslateObjectVisitor;

class Object {
  friend JsonStringifyVisitor;
  friend RotateObjectVisitor;
  friend ScaleObjectVisitor;
  friend TranslateObjectVisitor;
  friend ObjectMemento;

protected:
  std::shared_ptr<TransformationMatrix> transform;

public:
  using value_type = Object;
  using size_type = size_t;
  using iterator = ObjectVector::const_iterator;
  using const_iterator = ObjectVector::const_iterator;

  Object();
  explicit Object(std::unique_ptr<ObjectMemento> memento);
  Object(const Object &origin);
  virtual ~Object() = default;
  std::shared_ptr<TransformationMatrix> getTransformation();

  virtual void accept(BaseVisitor &vis);
  virtual bool isVisible() const noexcept = 0;

  virtual bool isComposite() const noexcept;
  virtual bool add(ObjectPtr &obj);
  virtual bool add(std::unique_ptr<Object> obj);
  virtual bool remove(const iterator &it);
  virtual iterator begin() const noexcept;
  virtual iterator end() const noexcept;

  virtual std::unique_ptr<ObjectMemento> createMemento() const;
  void restoreMemento(std::shared_ptr<ObjectMemento> memento);

  virtual std::unique_ptr<Object> clone() const = 0;
};

class ObjectMemento {
private:
  std::unique_ptr<TransformationMatrix> transform;

public:
  ObjectMemento(const Object &o);

  void set(const Object &o);
  std::unique_ptr<TransformationMatrix> get();
};

class ObjectCaretaker {
public:
  using MemPtr = std::shared_ptr<ObjectMemento>;
  using Save = std::pair<std::weak_ptr<Object>, std::vector<MemPtr>>;

private:
  std::map<size_t, Save> saveData;
  void clear_expired();

public:
  ObjectCaretaker();
  std::shared_ptr<ObjectMemento> get(size_t id);
  void set(size_t id, std::weak_ptr<Object> origin, MemPtr memento);
  void clear_id(size_t id);
  bool contains(size_t id);
  void clear();
};

#endif
