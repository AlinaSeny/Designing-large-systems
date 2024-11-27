#include "intrusive_ptr.h"

template<typename T, typename... Args>
TIntrusivePtr<T> MakeIntrusive(Args&&... args) {
    return TIntrusivePtr<T>(new T(std::forward<Args>(args)...));
}

class TDoc : public TRefCounter<TDoc> {
};

int main() {
    TIntrusivePtr<TDoc> ptr = nullptr;
    ptr = MakeIntrusive<TDoc>(); // ptr.RefCount() == 1
    TIntrusivePtr<TDoc> ptr2 = ptr; // ptr.RefCount() == 2
    TIntrusivePtr<TDoc> ptr3 = MakeIntrusive<TDoc>();
    ptr3.Reset(ptr2); // ptr.RefCount() == ptr3.RefCount() == 3
    ptr3.Reset(); // ptr.RefCount() == ptr3.RefCount() == 2
    ptr3.Reset(std::move(ptr2)); // ptr.RefCount() == ptr3.RefCount() == 2
    static_assert(sizeof(TDoc*) == sizeof(ptr));

    return 0;
}
