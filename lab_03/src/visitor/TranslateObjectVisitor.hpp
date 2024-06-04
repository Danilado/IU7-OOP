#ifndef TRANSLATE_OBJECT_VISITOR_HPP
#define TRANSLATE_OBJECT_VISITOR_HPP

#include "BaseVisitor.hpp"
#include "Point3D.hpp"
#include <memory>

class TransformationMatrix;
class Object;

class TranslateObjectVisitor : public BaseVisitor {
private:
  Point3D offset;
  void translate(Object &ref);

public:
  TranslateObjectVisitor() = delete;
  TranslateObjectVisitor(double dx, double dy, double dz);
  TranslateObjectVisitor(const Point3D &offset);

  void visit(WireframeModel &ref) override;
  void visit(OrthogonalCamera &ref) override;
  void visit(ProjectionCamera &ref) override;
  void visit(Scene &ref) override;
};

#endif
