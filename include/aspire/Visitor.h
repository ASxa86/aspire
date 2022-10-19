#pragma once

namespace aspire
{
	class Node;

	class Visitor
	{
	public:
		virtual void visit(Node& x) {}

	};
}
