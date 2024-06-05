#include "OrthocamBuilder.hpp"
#include "JsonAdapterSolution.hpp"
#include "OrthogonalCamera.hpp"

std::unique_ptr<Object> OrthogonalCameraDirector::create(BaseSource &src) {
  src.reset();
  OrthogonalCameraBuilder builder{};

  std::unique_ptr<OrthogonalCamera> res = std::make_unique<OrthogonalCamera>();
  res->transform =
      std::shared_ptr<TransformationMatrix>(builder.buildTransformMatrix(src));

  return std::move(res);
}
