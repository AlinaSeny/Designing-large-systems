#include <iostream>
#include <cstring>

template <char... c>
struct TString {
    static constexpr char value[] = {c..., '\0'};
    constexpr const char* get() const { return value; }

    template <char... other>
    constexpr auto operator+(TString<other...>) const {
        return TString<c..., other...>{};
    }

    template <char... other>
    constexpr bool operator==(TString<other...>) const {
        constexpr char str1[] = {other..., '\0'};
        return std::strcmp(get(), str1) == 0;
    }
};


template <typename T, T... c>
constexpr auto operator""_s() {
    return TString<c...>{};
}



int main() {
    constexpr auto hello = "hello"_s + " world"_s;
    static_assert(!(hello == "hello worl"_s), "failed");
    static_assert(hello == "hello world"_s, "failed");
    std::cout << hello.get() << std::endl;
}
