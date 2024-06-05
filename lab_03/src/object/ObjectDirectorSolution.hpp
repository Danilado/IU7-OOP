#ifndef OBJECT_DIRECTOR_SOLUTION_HPP
#define OBJECT_DIRECTOR_SOLUTION_HPP

#include "OrthocamBuilder.hpp"
#include "ProjcamBuilder.hpp"
#include "WireframeBuilder.hpp"
#include <map>

class ObjectDirectorSolution {
public:
  enum class types { WIREFRAME, ORTHOCAM, PROJCAM };

private:
  std::map<types, std::shared_ptr<BaseObjectDirector>> typemap{
      {types::WIREFRAME, std::make_shared<WireframeModelDirector>()},
      {types::ORTHOCAM, std::make_shared<OrthogonalCameraDirector>()},
      {types::PROJCAM, std::make_shared<ProjectionCameraDirector>()},
  };

public:
  ObjectDirectorSolution() = default;
  ~ObjectDirectorSolution() = default;

  std::shared_ptr<BaseObjectDirector> create(BaseSource &src);

  ObjectDirectorSolution(const ObjectDirectorSolution &) = delete;
  ObjectDirectorSolution &operator=(const ObjectDirectorSolution &) = delete;
};

#endif
