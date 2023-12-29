#include <iostream>

template<typename T>
class weakPtr;

template<typename T>
class sharedPtr {
private:
	T* ptr_;
	size_t* ref_count;
public:
	sharedPtr() : ptr_(nullptr), ref_count(nullptr) {}
	explicit sharedPtr(T* p) : ptr_(p), ref_count(new size_t(1)) {}

	sharedPtr(const sharedPtr<T>& other) : ptr_(other.ptr_), ref_count(other.ref_count) {
		if (ref_count) {
			++(*ref_count);
		}
	}

	sharedPtr(sharedPtr<T>&& other) : ptr_(nullptr), ref_count(nullptr) {
		swap(other);
	}

	sharedPtr& operator=(const sharedPtr& sp) noexcept;

	sharedPtr& operator=(sharedPtr&& sp) noexcept;

	template <class Other>
	sharedPtr& operator=(const sharedPtr<Other>& sp) noexcept {
		release();
		ptr_ = sp.ptr_;
		ref_count = sp.ref_count;
		if (ref_count) {
			++(*ref_count);
		}
		return *this;
	}

	template <class Other>
	sharedPtr& operator=(sharedPtr<Other>&& sp) noexcept {
		release();
		std::swap(ptr_, sp.ptr_);
		std::swap(ref_count, sp.ref_count);
		return *this;
	}

	~sharedPtr() {
		release();
	}

	T* get() const noexcept;
	T& operator*() const noexcept;
	T* operator->() const;
	bool owner_before(const sharedPtr<T>& other) const;
	bool operator==(std::nullptr_t) const noexcept;
	bool unique() const;
	void reset(T* p = nullptr);
	void swap(sharedPtr<T>& other);
	void release();
	size_t use_count() const;

	explicit operator bool() const noexcept {
		return ptr_ != nullptr;
	}

	friend std::ostream& operator<<(std::ostream& os, const sharedPtr<T>& p) {
		os << p.ptr_;
		return os;
	}

	template<typename U>
	explicit sharedPtr(const weakPtr<U>& wp) : ptr_(wp.lock().get()), ref_count(wp.ref_count) {
		if (ref_count) {
			++(*ref_count);
		}
	}

	friend class weakPtr<T>;
};

template<class T>
void sharedPtr<T>::release() {
	if (ref_count) {
		--(*ref_count);
		if (*ref_count == 0) {
			delete ptr_;
			delete ref_count;
		}
		ptr_ = nullptr;
		ref_count = nullptr;
	}
}

template<class T>
bool sharedPtr<T>::operator==(std::nullptr_t) const noexcept {
	return ptr_ == nullptr;
}

template<class T>
T* sharedPtr<T>::operator->() const {
	return ptr_;
}

template<class T>
T& sharedPtr<T>::operator*() const noexcept {
	return *ptr_;
}

template<class T>
size_t sharedPtr<T>::use_count() const {
	return ref_count ? *ref_count : 0;
}

template<class T>
bool sharedPtr<T>::unique() const {
	return use_count() == 1;
}

template<class T>
void sharedPtr<T>::swap(sharedPtr<T>& other) {
	std::swap(ptr_, other.ptr_);
	std::swap(ref_count, other.ref_count);
}

template<class T>
void sharedPtr<T>::reset(T* p) {
	release();
	ptr_ = p;
	ref_count = new size_t(1);
}

template<class T>
bool sharedPtr<T>::owner_before(const sharedPtr<T>& other) const {
	return std::less<T*>()(ptr_, other.ptr_);
}

template<class T>
T* sharedPtr<T>::get() const noexcept {
	return ptr_;
}

template<class T>
sharedPtr<T>& sharedPtr<T>::operator=(const sharedPtr<T>& sp) noexcept {
	if (ptr_ != sp.ptr_) {
		release();
		ptr_ = sp.ptr_;
		ref_count = sp.ref_count;
		if (ref_count) {
			++(*ref_count);
		}
	}
	return *this;
}

template<class T>
sharedPtr<T>& sharedPtr<T>:: operator=(sharedPtr<T>&& sp) noexcept {
	if (ptr_ != sp.ptr_) {
		release();
		std::swap(ptr_, sp.ptr_);
		std::swap(ref_count, sp.ref_count);
	}
	return *this;
}

template<typename T, typename... Args>
sharedPtr<T> MakeShared(Args&&... args) {
	return sharedPtr<T>(new T(std::forward<Args>(args)...));
}


template<typename T>
class weakPtr 
{
private:
	T* ptr_;
	size_t* ref_count;
public:
	weakPtr() noexcept : ptr_(nullptr), ref_count(nullptr) {}
	explicit weakPtr(const sharedPtr<T>& sp) noexcept : ptr_(sp.get()), ref_count(sp.ref_count) {}
	weakPtr(const weakPtr<T>& other) noexcept : ptr_(other.ptr_), ref_count(other.ref_count) {}

	weakPtr(weakPtr<T>&& other) noexcept : ptr_(nullptr), ref_count(nullptr) {
		swap(other);
	}

	weakPtr& operator=(const sharedPtr<T>& sp) noexcept;
	weakPtr& operator=(const weakPtr<T>& other) noexcept;
	weakPtr& operator=(weakPtr<T>&& other) noexcept;
	~weakPtr() {}
	sharedPtr<T> lock() const noexcept;
	void reset() noexcept;
	void swap(weakPtr<T>& other) noexcept;
	size_t use_count() const;
	bool expired() const noexcept;
	bool owner_before(const weakPtr<T>& other) const;
	T* get_ptr();
	
	explicit operator bool() const noexcept {
		return ptr_ != nullptr;
	}
	friend class sharedPtr<T>;
};


template<typename T>
weakPtr<T>& weakPtr<T>::operator=(weakPtr<T>&& other) noexcept {
	swap(other);
	return *this;
}

template<typename T>
sharedPtr<T> weakPtr<T>::lock() const noexcept {
	return sharedPtr<T>(*this);
}

template<typename T>
T* weakPtr<T>::get_ptr() {
	return ptr_;
}

template<typename T>
bool weakPtr<T>::owner_before(const weakPtr<T>& other) const {
	return std::less<T*>()(ptr_, other.ptr_);
}

template<typename T>
bool weakPtr<T>::expired() const noexcept {
	return use_count() == 0;
}

template<typename T>
size_t weakPtr<T>::use_count() const {
	return ref_count ? *ref_count : 0;
}

template<typename T>
void weakPtr<T>::swap(weakPtr<T>& other) noexcept {
	std::swap(ptr_, other.ptr_);
	std::swap(ref_count, other.ref_count);
}

template<typename T>
void weakPtr<T>::reset() noexcept {
	ptr_ = nullptr;
	ref_count = nullptr;
}

template<typename T>
weakPtr<T>& weakPtr<T>::operator=(const weakPtr<T>& other) noexcept {
	ptr_ = other.ptr_;
	ref_count = other.ref_count;
	return *this;
}

template<typename T>
weakPtr<T>& weakPtr<T>::operator=(const sharedPtr<T>& sp) noexcept {
	ptr_ = sp.get();
	ref_count = sp.ref_count;
	return *this;
}

class myClass {
public:
    myClass() {
        std::cout << "myClass constructor called!" << std::endl;
    }

    ~myClass() {
        std::cout << "myClass destructor called!" << std::endl;
    }

    void sayHello() {
        std::cout << "Hello, World!" << std::endl;
    }
};

int main() {
    // Example 1: Creating sharedPtr and weakPtr instances

    std::cout << "Example 1:" << std::endl;

    sharedPtr<myClass> shared(new myClass());
    weakPtr<myClass> weak(shared);

    std::cout << "shared.use_count(): " << shared.use_count() << std::endl;
    std::cout << "weak.use_count(): " << weak.use_count() << std::endl;
}