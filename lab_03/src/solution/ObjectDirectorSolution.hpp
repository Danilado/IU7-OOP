#ifndef OBJECT_DIRECTOR_SOLUTION_HPP
#define OBJECT_DIRECTOR_SOLUTION_HPP

#include "BaseSource.hpp"
#include "ObjectBuilder.hpp"

class ObjectDirectorSolution {
public:
  static std::unique_ptr<BaseObjectDirector> create(BaseSource &src);
};

#endif
