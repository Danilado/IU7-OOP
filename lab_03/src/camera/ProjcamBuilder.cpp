#include "ProjcamBuilder.hpp"
#include "JsonAdapterSolution.hpp"
#include "ProjectionCamera.hpp"

std::unique_ptr<Object> ProjectionCameraDirector::create(BaseSource &src) {
  src.reset();
  ProjectionCameraBuilder builder{};

  std::unique_ptr<ProjectionCamera> res = std::make_unique<ProjectionCamera>();
  res->transform =
      std::shared_ptr<TransformationMatrix>(builder.buildTransformMatrix(src));

  return std::move(res);
}
