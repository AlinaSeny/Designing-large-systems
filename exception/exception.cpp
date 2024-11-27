#include <iostream>
#include <stdexcept>
#include <sstream>
#include <string>
#include <gtest/gtest.h>

class TMyException : public std::runtime_error {
public:
    explicit TMyException(const std::string& msg) : std::runtime_error(msg) {}

    friend std::ostream& operator<<(std::ostream& os, const TMyException& e) {
        os << "TMyException: " << e.what();
        return os;
    }
};

class TMyExceptionA : public TMyException {
public:
    explicit TMyExceptionA(const std::string& msg) : TMyException("A: " + msg) {}
};

class TMyExceptionB : public TMyException {
public:
    explicit TMyExceptionB(const std::string& msg) : TMyException("B: " + msg) {}
};

void ThrowExceptionA() {
    throw TMyExceptionA("This is an exception of type A");
}

void ThrowExceptionB() {
    throw TMyExceptionB("This is an exception of type B");
}

TEST(MyExceptionTest, TestThrowExceptionA) {
    EXPECT_THROW(ThrowExceptionA(), TMyExceptionA);
}

TEST(MyExceptionTest, TestThrowExceptionB) {
    EXPECT_THROW(ThrowExceptionB(), TMyExceptionB);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

