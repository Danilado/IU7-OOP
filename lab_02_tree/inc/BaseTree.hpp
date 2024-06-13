#ifndef _BASE_CONTAINER_H_
#define _BASE_CONTAINER_H_

#include <cstdlib>

class BaseTree {

	using size_type = size_t;

public:
	BaseTree()
	{
		size = 0;
	}

	explicit operator bool() const {
		return this->IsEmpty();
	}

	[[nodiscard]] bool IsEmpty() const
	{
		return size == 0;
	}

	[[nodiscard]] size_t Size() const
	{
		return size;
	}

	virtual ~BaseTree() = default;

protected:
	size_type size = 0;
};

#endif // _BASE_CONTAINER_H_