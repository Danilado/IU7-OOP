#include "OrthogonalCamera.hpp"

void OrthogonalCamera::accept(BaseVisitor &vis) { vis.visit(*this); }
