#include <aspire/core/Signal.h>

int main()
{
	aspire::Signal<void(int)> test;
	test.emit(5);
	return 0;
}
