#pragma once

namespace aspire
{
	struct Surface
	{
		int bitsRed{8};
		int bitsGreen{8};
		int bitsBlue{8};
		int bitsAlpha{8};
		int versionMajor{3};
		int versionMinor{3};
		int bufferColor{32};
		int bufferDepth{24};
		int bufferStencil{8};
	};
}
