#include "base_container.hpp"

BaseContainer::BaseContainer() noexcept { size = 0; }

BaseContainer::BaseContainer(size_t size) noexcept : size(size){};

BaseContainer::~BaseContainer() = default;

bool BaseContainer::isEmpty() const noexcept { return size == 0; }

size_t BaseContainer::getSize() const noexcept { return size; }
