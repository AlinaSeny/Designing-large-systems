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

    constexpr bool operator==(const TString& other) const {
        return std::strcmp(get(), other.get()) == 0;
    }
};



template <typename T, T... c>
constexpr auto operator""_s() {
    return TString<c...>{};
}



int main() {
    constexpr auto hello = "hello"_s + " world"_s;
    static_assert(hello == "hello world"_s);
    std::cout << hello.get() << std::endl;
}
