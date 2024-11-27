#include <iostream>
#include <utility>
#include <cassert>

template<typename T>
class TRefCounter {
private:
    size_t count;

public:
    TRefCounter() : count(0) {}

    void AddRef() {
        count++;
    }

    void Release() {
        count--;
        if (count == 0) {
            delete static_cast<T*>(this);
        }
    }

    size_t RefCount() const {
        return count;
    }
};

template<typename T>
class TBasePtr {
protected:
    T* ptr;

public:
    TBasePtr(T* p = nullptr) : ptr(p) {}

    T& operator*() const {
        return *ptr;
    }

    T* operator->() const {
        return ptr;
    }

    bool operator==(const TBasePtr& other) const {
        return ptr == other.ptr;
    }

    bool operator!=(const TBasePtr& other) const {
        return ptr != other.ptr;
    }

    operator bool() const {
        return ptr != nullptr;
    }

    T* Get() const {
        return ptr;
    }
};

template<typename T>
class TIntrusivePtr : public TBasePtr<T> {
public:
    using TBasePtr<T>::TBasePtr;

    TIntrusivePtr(T* p = nullptr) : TBasePtr<T>(p) {
        if (this->ptr) {
            this->ptr->AddRef();
        }
    }

    TIntrusivePtr(const TIntrusivePtr& other) : TBasePtr<T>(other.ptr) {
        if (this->ptr) {
            this->ptr->AddRef();
        }
    }

    TIntrusivePtr(TIntrusivePtr&& other) noexcept : TBasePtr<T>(other.ptr) {
        other.ptr = nullptr;
    }

    ~TIntrusivePtr() {
        Reset();
    }

    TIntrusivePtr& operator=(const TIntrusivePtr& other) {
        if (this != &other) {
            if (this->ptr) {
                this->ptr->Release();
            }
            this->ptr = other.ptr;
            if (this->ptr) {
                this->ptr->AddRef();
            }
        }
        return *this;
    }

    TIntrusivePtr& operator=(TIntrusivePtr&& other) noexcept {
        if (this != &other) {
            if (this->ptr) {
                this->ptr->Release();
            }
            this->ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }

    void Reset(T* p = nullptr) {
        if (this->ptr) {
            this->ptr->Release();
        }
        this->ptr = p;
        if (this->ptr) {
            this->ptr->AddRef();
        }
    }

    void Reset(TIntrusivePtr& other) {
        if (this != &other) {
            if (this->ptr) {
                this->ptr->Release();
            }
            this->ptr = other.ptr;
            if (this->ptr) {
                this->ptr->AddRef();
            }
        }
    }

    void Reset(TIntrusivePtr&& other) {
        if (this != &other) {
            if (this->ptr) {
                this->ptr->Release();
            }
            this->ptr = other.ptr;
            other.ptr = nullptr;
        }
    }

    T* Release() {
        T* releasedPtr = this->ptr;
        this->ptr = nullptr;
        return releasedPtr;
    }

    size_t UseCount() const {
        return (this->ptr) ? this->ptr->RefCount() : 0;
    }
};
