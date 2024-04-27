#pragma once

#include <aspire/widget/Widget.h>
#include <aspire/widget/export.hxx>

namespace aspire::widget
{
	class ASPIRE_WIDGET_EXPORT Window : public aspire::core::Object
	{
	public:
		auto setWidget(std::unique_ptr<Widget> x) -> void;
		[[nodiscard]] auto getWidget() const -> Widget*;

	private:
		std::unique_ptr<Widget> widget;
	};
}