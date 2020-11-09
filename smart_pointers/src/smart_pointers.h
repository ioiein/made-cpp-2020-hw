#pragma once


namespace task {

    template <class T>
    class UniquePtr {
    public:
        T* ptr;

        explicit UniquePtr(T* p) noexcept : ptr(p) {}
        UniquePtr(UniquePtr&& u) noexcept;
        ~UniquePtr();

        UniquePtr(const UniquePtr&) = delete;
        UniquePtr& operator=(const UniquePtr&) = delete;

        UniquePtr& operator=( UniquePtr&& r ) noexcept;
        T& operator*();
        T* operator->();
        T* get() const noexcept;
        T* release() noexcept;
        void reset( T* p = new T ) noexcept;
        void swap(UniquePtr& other) noexcept;
    };

    template<class T>
    class WeakPtr;

    template<class T>
    struct ControlBlock {
        T* ptr;
        size_t ref_count;
        size_t weak_ref_count;
    };

    template <class T>
    class SharedPtr {
    public:
        ControlBlock<T>* cb;

        constexpr SharedPtr() noexcept {
            cb = nullptr;
        }
        explicit SharedPtr( T* ptr );
        SharedPtr( const SharedPtr<T>& r ) noexcept;
        SharedPtr( SharedPtr<T>&& r ) noexcept;
        explicit SharedPtr( const WeakPtr<T>& r );
        ~SharedPtr();

        SharedPtr& operator=( const SharedPtr<T>& r ) noexcept;
        SharedPtr& operator=( SharedPtr<T>&& r ) noexcept;
        T& operator*() const noexcept;
        T* operator->() const noexcept;
        T* get() const noexcept;
        size_t use_count() const noexcept;
        void reset() noexcept;
        void reset( T* ptr );
        void swap( SharedPtr& r ) noexcept;
    };

    template <class T>
    class WeakPtr {
    public:
        ControlBlock<T>* cb;

        constexpr WeakPtr() noexcept {
            cb = nullptr;
        }
        WeakPtr( const WeakPtr<T>& r ) noexcept;
        WeakPtr( const SharedPtr<T>& r ) noexcept;
        WeakPtr( WeakPtr<T>&& r ) noexcept;
        WeakPtr& operator=( const WeakPtr<T>& r ) noexcept;
        WeakPtr& operator=( WeakPtr<T>&& r ) noexcept;
        WeakPtr& operator=( const SharedPtr<T>& r ) noexcept;
        ~WeakPtr();
        size_t use_count() const noexcept;
        bool expired() const noexcept;
        SharedPtr<T> lock() const noexcept;
        void reset() noexcept;
        void swap( WeakPtr<T>& r ) noexcept;

    };



}  // namespace task


#include "smart_pointers.tpp"
