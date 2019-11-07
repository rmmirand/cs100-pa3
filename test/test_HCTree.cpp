#include <iostream>
#include <string>
#include <vector>

#include <gtest/gtest.h>
#include "HCTree.hpp"

using namespace std;
using namespace testing;

class SimpleHCTreeFixture : public ::testing::Test {
  protected:
    HCTree tree;

  public:
    SimpleHCTreeFixture() {
        // initialization code here
        vector<unsigned int> freqs(256);
        freqs['a'] = 10;
        freqs['b'] = 10;
	freqs['c'] = 10;
	freqs['d'] = 10;
	freqs['\n'] = 1;
        tree.build(freqs);
    }
};
TEST_F(SimpleHCTreeFixture, TEST_ENCODE) {
    ostringstream os;
    tree.encode('\n', os);
    ASSERT_EQ(os.str(), "110");
}
TEST_F(SimpleHCTreeFixture, TEST_ENCODE2) {
    ostringstream os;
    tree.encode('d', os);
    ASSERT_EQ(os.str(), "111");
}
TEST_F(SimpleHCTreeFixture, TEST_ENCODE3) {
    ostringstream os;
    tree.encode('b', os);
    ASSERT_EQ(os.str(), "01");
}
TEST_F(SimpleHCTreeFixture, TEST_ENCODE4) {
    ostringstream os;
    tree.encode('c', os);
    ASSERT_EQ(os.str(), "00");
}
TEST_F(SimpleHCTreeFixture, TEST_ENCODE5) {
    ostringstream os;
    tree.encode('a', os);
    ASSERT_EQ(os.str(), "10");
}
TEST_F(SimpleHCTreeFixture, TEST_DECODE) {
    istringstream is("01");
    ASSERT_EQ(tree.decode(is), 'b');
}
TEST_F(SimpleHCTreeFixture, TEST_DECODE2) {
    istringstream is("00");
    ASSERT_EQ(tree.decode(is), 'c');
}
