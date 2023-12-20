#pragma once

#include <Windows.h>
#include <aspire/gui/Context.h>

namespace aspire
{
	class ContextWin32 : public Context
	{
	public:
		explicit ContextWin32(HWND x);
		~ContextWin32() override;

		auto makeCurrent() -> void override;
		auto makeRelease() -> void override;
		auto create() -> void override;

	private:
		HWND window{};
		HDC deviceContext{};
		HGLRC handle{};
	};
}
