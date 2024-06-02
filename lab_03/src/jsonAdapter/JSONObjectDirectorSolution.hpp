#ifndef JSON_OBJECT_DIRECTOR_SOLUTION_HPP
#define JSON_OBJECT_DIRECTOR_SOLUTION_HPP

#include "BaseJSONAdapter.hpp"
#include "BaseSource.hpp"
#include "ObjectBuilder.hpp"


class JsonObjDirectorSolution {
public:
  enum class TYPES { WIREFRAME, ORTHOCAM, PROJCAM };
  BaseObjectDirector create(BaseSource src);
};

#endif
