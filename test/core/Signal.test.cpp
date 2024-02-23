#include <aspire/test/Test.h>

// Test under the hood registers itself to the test instance?
class TestSignal : public aspire::Test
{
public:
	TestSignal()
	{
		// When the test gets registered, does it get wrapped in the unit test object?
		this->registerTest([this] { this->testConnect(); });
	}

	// Is there a way to wrap this in an object that observes time, tracks results, log information, etc...
	void testConnect()
	{
		this->expectEQ(0, 0);
	}
};
