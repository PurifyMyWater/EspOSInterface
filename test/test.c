#include <unity.h>
#include <adder.h>

TEST_CASE("test add", "[adder]")
{
    TEST_ASSERT_EQUAL(3, add(1, 2));
}
