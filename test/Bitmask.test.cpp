#include <aspire/Bitmask.h>
#include <gtest/gtest.h>

namespace
{
	enum class Mask : uint8_t
	{
		One = 0b00000001,
		Two = 0b00000010,
		Four = 0b00000100,
		Eight = 0b00001000
	};
}

TEST(Bitmask, add)
{
	aspire::Bitmask<Mask> mask;
	EXPECT_EQ(mask.get(), 0);

	mask.add(Mask::One);

	EXPECT_EQ(mask.get(), static_cast<uint8_t>(Mask::One));

	mask.add(Mask::Two);

	EXPECT_EQ(mask.get(), static_cast<uint8_t>(Mask::One) | static_cast<uint8_t>(Mask::Two));
}

TEST(Bitmask, test)
{
	aspire::Bitmask<Mask> mask;
	EXPECT_EQ(mask.get(), 0);

	mask.add(Mask::One);

	EXPECT_TRUE(mask.test(Mask::One));

	mask.add(Mask::Two);

	EXPECT_TRUE(mask.test(Mask::Two));
	EXPECT_FALSE(mask.test(Mask::Four));

	mask.remove(Mask::One);

	EXPECT_FALSE(mask.test(Mask::One));
	EXPECT_TRUE(mask.test(Mask::Two));
	EXPECT_FALSE(mask.test(Mask::Four));
}
