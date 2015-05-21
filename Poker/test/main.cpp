#define BOOST_TEST_MAIN 1
#define BOOST_TEST_MODULE TestPoker
#include <boost/test/unit_test.hpp>
#include "TestCard.hpp"
#include "TestRules.hpp"
using namespace boost::unit_test;


BOOST_AUTO_TEST_SUITE(TestEnvironment)

BOOST_AUTO_TEST_CASE(test_success)
{
    BOOST_CHECK( true );
}

BOOST_AUTO_TEST_SUITE_END()

//int main() {
//    std::cout << "asdasd";
//    return 0;
//}
//

