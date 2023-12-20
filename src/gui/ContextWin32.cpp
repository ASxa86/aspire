#include "ContextWin32.h"

using aspire::ContextWin32;

ContextWin32::ContextWin32(HWND x) : window{x}, deviceContext{GetDC(this->window)}
{
}

ContextWin32::~ContextWin32()
{
	this->makeRelease();
	wglDeleteContext(this->handle);
	ReleaseDC(this->window, this->deviceContext);
}

auto ContextWin32::makeCurrent() -> void
{
	wglMakeCurrent(this->deviceContext, this->handle);
}

auto ContextWin32::makeRelease() -> void
{
	wglMakeCurrent(nullptr, nullptr);
}

auto ContextWin32::create() -> void
{
	PIXELFORMATDESCRIPTOR pfd{};

	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;

	auto& surface = this->getSurface();
	pfd.cColorBits = surface.bufferColor;
	pfd.cDepthBits = surface.bufferDepth;
	pfd.cStencilBits = surface.bufferStencil;
	pfd.cAlphaBits = surface.bitsAlpha;
	pfd.cRedBits = surface.bitsRed;
	pfd.cGreenBits = surface.bitsGreen;
	pfd.cBlueBits = surface.bitsBlue;

	auto pixelFormat = ChoosePixelFormat(this->deviceContext, &pfd);
	SetPixelFormat(this->deviceContext, pixelFormat, &pfd);

	this->handle = wglCreateContext(this->deviceContext);
	this->makeCurrent();
}
