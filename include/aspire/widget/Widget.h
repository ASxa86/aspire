#pragma once

#include <aspire/core/Object.h>
#include <aspire/scene/Node.h>
#include <aspire/widget/export.hxx>

namespace aspire::widget
{
	class ASPIRE_WIDGET_EXPORT Widget : public aspire::core::Object
	{
	public:
		auto onRender(std::function<void()> x) const -> sigslot::connection;

		auto render(std::shared_ptr<aspire::scene::Node> x) -> std::shared_ptr<aspire::scene::Node>;

	private:
	};
}