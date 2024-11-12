#include <type_traits>
#include <cstdint>

template <typename... Tp>
struct are_same;

template <>
struct are_same<> : std::true_type {};

template <typename T, typename... Tp>
struct are_same<T, Tp...> : std::integral_constant<bool, (std::is_same_v<std::remove_cv_t<std::remove_reference_t<T>>, std::remove_cv_t<std::remove_reference_t<Tp>>> && ...)> {};

template <typename... Tp>
constexpr bool are_same_v = are_same<Tp...>::value;


int main() {
    static_assert(are_same_v<int, int32_t, signed int>, "compile assert");
    static_assert(!are_same_v<bool, int32_t, signed int>, "compile assert");
    return 0;
}
