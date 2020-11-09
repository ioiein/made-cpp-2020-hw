namespace task {
//unique_ptr
    template<class T>
    UniquePtr<T>::UniquePtr(UniquePtr&& u) noexcept {
        this->ptr = std::move(u.ptr);
        u.ptr = nullptr;
    }

    template<class T>
    UniquePtr<T>::~UniquePtr() {
        delete ptr;
    }

    template<class T>
    UniquePtr<T>& UniquePtr<T>::operator=( UniquePtr&& r ) noexcept {
        this->ptr = std::move(r.ptr);
        r.ptr = nullptr;
        return *this;
    }

    template<class T>
    T& UniquePtr<T>::operator*() {
        return *ptr;
    }

    template<class T>
    T* UniquePtr<T>::operator->() {
        return ptr;
    }

    template<class T>
    T* UniquePtr<T>::get() const noexcept {
        return ptr;
    }

    template<class T>
    T* UniquePtr<T>::release() noexcept {
        return std::move(ptr);
    }

    template<class T>
    void UniquePtr<T>::reset( T* p) noexcept {
        T* old_ptr = ptr;
        ptr = p;
        if (old_ptr) {
            delete old_ptr;
        }
    }

    template<class T>
    void UniquePtr<T>::swap(UniquePtr& other) noexcept {
        std::swap(ptr, other.ptr);
    }


//shared_ptr
    template<class T>
    SharedPtr<T>::SharedPtr( T* ptr ) {
        try {
            cb = new ControlBlock<T>;
            cb->ptr = ptr;
            cb->ref_count = 1;
            cb->weak_ref_count = 0;
        }
        catch (...) {
            delete ptr;
        }
    }

    template<class T>
    SharedPtr<T>::SharedPtr( const SharedPtr& r ) noexcept {
        cb = r.cb;
        if (cb) {
            ++cb->ref_count;
        }
    }

    template<class T>
    SharedPtr<T>::SharedPtr( SharedPtr&& r ) noexcept {
        this->cb = std::move(r.cb);
        r.cb = nullptr;
    }

    template<class T>
    SharedPtr<T>::SharedPtr( const WeakPtr<T>& r ) {
        cb = r.cb;
        ++cb->ref_count;
    }

    template<class T>
    SharedPtr<T>::~SharedPtr() {
        if (cb != nullptr) {
            if (cb->ref_count + cb->weak_ref_count == 1) {
                delete cb->ptr;
                delete cb;
            } else {
                --cb->ref_count;
            };
        }
    }

    template<class T>
    SharedPtr<T>& SharedPtr<T>::operator=( const SharedPtr& r ) noexcept {
        if (cb && cb->ref_count > 1) {
            --cb->ref_count;
        }
        cb = r.cb;
        ++cb->ref_count;
        return *this;
    }

    template<class T>
    SharedPtr<T>& SharedPtr<T>::operator=( SharedPtr&& r ) noexcept {
        this->cb = std::move(r.cb);
        r.cb = nullptr;
        return *this;
    }

    template<class T>
    T& SharedPtr<T>::operator*() const noexcept {
        return *(cb->ptr);
    }

    template<class T>
    T* SharedPtr<T>::operator->() const noexcept {
        return cb->ptr;
    }

    template<class T>
    T* SharedPtr<T>::get() const noexcept {
        return cb->ptr;
    }

    template<class T>
    size_t SharedPtr<T>::use_count() const noexcept {
        return cb->ref_count;
    }

    template<class T>
    void SharedPtr<T>::reset() noexcept {
        delete cb->ptr;
        cb->ptr = nullptr;
    }

    template<class T>
    void SharedPtr<T>::reset( T* ptr ) {
        cb->ptr = ptr;
    }

    template<class T>
    void SharedPtr<T>::swap( SharedPtr& r ) noexcept {
        std::swap(cb, r.cb);
    }


//weak_ptr
    template<class T>
    WeakPtr<T>::WeakPtr( const WeakPtr& r ) noexcept {
        cb = r.cb;
        ++cb->weak_ref_count;
    }
    template<class T>
    WeakPtr<T>::WeakPtr( const SharedPtr<T>& r ) noexcept {
        cb = r.cb;
        ++cb->weak_ref_count;
    }
    template<class T>
    WeakPtr<T>::WeakPtr( WeakPtr&& r ) noexcept {
        this->cb = std::move(r.cb);
        r.cb = nullptr;
    }
    template<class T>
    WeakPtr<T>& WeakPtr<T>::operator=( const WeakPtr& r ) noexcept {
        cb = r.cb;
        ++cb->weak_ref_count;
        return *this;
    }
    template<class T>
    WeakPtr<T>& WeakPtr<T>::operator=( WeakPtr&& r ) noexcept {
        this->cb = std::move(r.cb);
        r.cb = nullptr;
        return *this;
    }
    template<class T>
    WeakPtr<T>& WeakPtr<T>::operator=( const SharedPtr<T>& r ) noexcept {
        if (cb && cb->weak_ref_count > 1) {
            --cb->weak_ref_count;
        }
        cb = r.cb;
        ++cb->weak_ref_count;
        return *this;
    }
    template<class T>
    WeakPtr<T>::~WeakPtr() {
        if (cb != nullptr ) {
            if (cb->ref_count + cb->weak_ref_count == 1) {
                delete cb->ptr;
                delete cb;
            } else {
                --cb->weak_ref_count;
            };
        }
    }
    template<class T>
    size_t WeakPtr<T>::use_count() const noexcept {
        if (cb == nullptr) {
            return 0;
        }
        else {
            return cb->ref_count;
        }
    }
    template<class T>
    bool WeakPtr<T>::expired() const noexcept {
        return use_count() == 0;
    }
    template<class T>
    SharedPtr<T> WeakPtr<T>::lock() const noexcept {
        return SharedPtr(*this);
    }
    template<class T>
    void WeakPtr<T>::reset() noexcept {
        delete cb->ptr;
    }
    template<class T>
    void WeakPtr<T>::swap( WeakPtr& r ) noexcept {
        std::swap(cb->ptr, r.cb->ptr);
    }
}