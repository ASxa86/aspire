#include <aspire/test/Test.h>

using aspire::Test;

Test::~Test()
{
	// Report results of test?
}

auto Test::registerTest(std::function<void()> x) -> void
{
	this->tests.emplace_back(std::make_unique<Unit>(std::move(x)));
}

auto Test::run() -> void
{
	for(const auto& test : this->tests)
	{
		// Assign a current unit test so that registered tests may access the comparison functions of Test.
		this->current = test.get();
		test->run();
		this->result &= test->getResult();
	}
}