#include "ProjectionCamera.hpp"

void ProjectionCamera::accept(BaseVisitor &vis) { vis.visit(*this); }
