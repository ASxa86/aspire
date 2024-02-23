#include <aspire/core/Kernel.h>
#include <aspire/test/Test.h>

int main()
{
	aspire::Kernel kernel;

	// kernel.addChild<SignalTest>();
	// kernel.addChild<ConnectionTest>();

	return kernel.run();
}