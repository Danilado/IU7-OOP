#ifndef SCENE_BUILDER_HPP
#define SCENE_BUILDER_HPP

#include "BaseSource.hpp"
#include "Object.hpp"
#include "ObjectComposite.hpp"
#include "Scene.hpp"

class SceneDirector {
public:
  std::unique_ptr<Scene> create(BaseSource &src);
};

class SceneBuilder {
public:
  using ObjectIterator = ObjectVector::const_iterator;

  ObjectIterator buildObjects(BaseSource &src);
};

#endif
