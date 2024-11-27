#include <iostream>
#include <stdexcept>
#include <sstream>
#include <string>
#include <gtest/gtest.h>

class TMyException : public std::runtime_error {
private:
    std::string msg;
public:
    TMyException() : std::runtime_error("My Exception") {}

    const char* what() const noexcept override {
        return msg.c_str();
    }

    template <typename T>
    TMyException& operator<<(const T& value) {
        std::ostringstream oss;
        oss << msg << value;
        msg = oss.str();
        return *this;
    }
};

class TMyExceptionA : public TMyException {};

class TMyExceptionB : public TMyException {};

void ThrowMyException() {
    try {
        throw TMyException() << "TMyException";
    } catch (const TMyException& exception) {
        std::cout << exception.what() << std::endl;
    }
}

void ThrowExceptionA() {
    throw TMyExceptionA() << "This is an exception of type A";
}

void ThrowExceptionB() {
    throw TMyExceptionB() << "This is an exception of type B";
}

TEST(MyExceptionTest, TestThrowExceptionA) {
    EXPECT_THROW(ThrowExceptionA(), TMyException);
}

TEST(MyExceptionTest, TestThrowExceptionB) {
    EXPECT_THROW(ThrowExceptionB(), TMyException);
}

int main(int argc, char** argv) {
    ThrowMyException();
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

