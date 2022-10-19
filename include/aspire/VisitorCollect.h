#pragma once

#include <aspire/Visitor.h>
#include <vector>

namespace aspire
{
	template <typename T>
	class VisitorCollector : public Visitor
	{
	public:
		VisitorCollector(unsigned int x = 1) : Visitor{x}
		{
		}

		auto visit(T& x) -> void override
		{
			this->nodes.emplace_back(&x);

			this->traverse(x);
		}

		auto getCollection() noexcept -> const std::vector<T*>&
		{
			return this->nodes;
		}

		std::vector<T*> nodes;
	};
}
