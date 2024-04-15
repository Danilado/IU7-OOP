#include "BaseIterator.h"

BaseIterator::BaseIterator() {
  index = 0;
  size = 0;
}

BaseIterator::BaseIterator(const BaseIterator &iter) {
  index = iter.index;
  size = iter.size;
}
