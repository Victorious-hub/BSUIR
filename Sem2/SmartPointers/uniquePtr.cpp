#include <iostream>
#include <cstdlib>
#include <string>
#include <cstdio>
#include <type_traits>
#include <iostream>
#include <memory>

template <class T, class Del = std::default_delete<T>>
class uniquePtr {
public:
	// Constructors
	uniquePtr() noexcept : ptr_(nullptr), deleter_(Del()) {}
	uniquePtr(nullptr_t) noexcept : ptr_(nullptr), deleter_(Del()) {}
	explicit uniquePtr(T* ptr) noexcept : ptr_(ptr), deleter_(Del()) {}
	uniquePtr(T* ptr, const Del& deleter) noexcept : ptr_(ptr), deleter_(deleter) {}
	uniquePtr(T* ptr, Del&& deleter) noexcept : ptr_(ptr), deleter_(std::move(deleter)) {}
	uniquePtr(uniquePtr&& other) noexcept : ptr_(other.release()), deleter_(std::move(other.deleter_)) {}
    // Copy operations deleted
	uniquePtr(const uniquePtr&) = delete;
	uniquePtr& operator=(const uniquePtr&) = delete;
	T* release() noexcept;
    T& operator*() const noexcept;
	T* operator->() const noexcept;
    T* get() const noexcept;
	void reset(T* ptr = nullptr) noexcept;
	void swap(uniquePtr& other) noexcept;
	Del& get_deleter();
	const Del& get_deleter() const;
	bool operator!=(std::nullptr_t) const;
    bool operator==(std::nullptr_t) const;

	// Move assignment operator
	uniquePtr& operator=(uniquePtr&& other) noexcept 
	{
		reset(other.release());
		deleter_ = std::move(other.deleter_);
		return *this;
	}

    ~uniquePtr() noexcept 
	{
		reset();
	}

	friend std::ostream& operator<<(std::ostream& os, const uniquePtr<T>& p) 
	{
		os << p.ptr_;
		return os;
	}

	explicit operator bool() const noexcept 
	{
		return ptr_ != nullptr;
	}

private:
	T* ptr_;
	Del deleter_;
};

template <class T, class Del>
T* uniquePtr<T, Del>::release() noexcept 
{
		T* ptr = ptr_;
		ptr_ = nullptr;
		return ptr;
}

template <class T, class Del>
void uniquePtr<T, Del>::reset(T* ptr) noexcept 
{
    if (ptr_ != ptr) {
        deleter_(ptr_);
        ptr_ = ptr;
    }
}

template <class T, class Del>
void uniquePtr<T, Del>::swap(uniquePtr<T, Del>& other) noexcept 
{
    std::swap(ptr_, other.ptr_);
    std::swap(deleter_, other.deleter_);
}

template <class T, class Del>
T* uniquePtr<T, Del>::get() const noexcept 
{
    return ptr_;
}

template <class T, class Del>
Del& uniquePtr<T, Del>::get_deleter()
{
    return deleter_;
}

template <class T, class Del>
const Del& uniquePtr<T, Del>::get_deleter() const 
{
    return deleter_;
}

template <class T, class Del>
T& uniquePtr<T, Del>::operator*() const noexcept 
{
    return *ptr_;
}

template <class T, class Del>
T* uniquePtr<T, Del>::operator->() const noexcept 
{
    return ptr_;
}

template <class T, class Del>
bool uniquePtr<T, Del>::operator!=(std::nullptr_t) const 
{
    return ptr_ == nullptr;
}

template <class T, class Del>
bool uniquePtr<T, Del>::operator==(std::nullptr_t) const 
{
    return ptr_ == nullptr;
}


template <class T, class D>
class uniquePtr<T[], D> 
{
public:
	constexpr uniquePtr() noexcept : ptr_(nullptr), deleter_(D()) {}

	template <class U>
	explicit uniquePtr(U p) noexcept : ptr_(p), deleter_(D()) {}

	template <class U>
	uniquePtr(U p, typename std::enable_if<std::is_convertible<U, T*>::value, D>::type d) noexcept
		: ptr_(p), deleter_(d) {}

	template <class U>
	uniquePtr(U p, typename std::enable_if<std::is_convertible<U, T*>::value, D&&>::type d) noexcept
		: ptr_(p), deleter_(std::move(d)) {}

	uniquePtr(uniquePtr&& u) noexcept : ptr_(u.ptr_), deleter_(std::move(u.deleter_)) 
	{
		u.ptr_ = nullptr;
	}

	template <class U, class E>
	uniquePtr(uniquePtr<U, E>&& u) noexcept : ptr_(u.release()), deleter_(std::move(u.get_deleter())) {}

	~uniquePtr() 
	{
		reset();
	}

	uniquePtr& operator=(uniquePtr&& u) noexcept;

	template <class U, class E>
	uniquePtr& operator=(uniquePtr<U, E>&& u) noexcept 
	{
		reset(u.release());
		deleter_ = std::move(u.get_deleter());
		return *this;
	}

	uniquePtr& operator=(nullptr_t) noexcept;
	T& operator[](size_t i) const;
	T* get() const noexcept;
	D& get_deleter() noexcept;
	const D& get_deleter() const noexcept;

	explicit operator bool() const noexcept 
	{
		return ptr_ != nullptr;
	}

	T* release() noexcept;
	void reset(T* p = nullptr) noexcept;
	void reset(nullptr_t) noexcept;
	bool operator!=(std::nullptr_t) const;
	bool operator==(std::nullptr_t) const;

	template <class U>
	void reset(U p) noexcept = delete;
	void swap(uniquePtr& u) noexcept;

private:
	T* ptr_;
	D deleter_;
};

template <class T, class D>
void uniquePtr<T[], D>::swap(uniquePtr& u) noexcept 
{
    std::swap(ptr_, u.ptr_);
    std::swap(deleter_, u.deleter_);
}

template <class T, class D>
bool uniquePtr<T[], D>::operator==(std::nullptr_t) const 
{
    return ptr_ == nullptr;
}

template <class T, class D>
bool uniquePtr<T[], D>::operator!=(std::nullptr_t) const 
{
    return ptr_ == nullptr;
}

template <class T, class D>
void uniquePtr<T[], D>::reset(nullptr_t) noexcept 
{
    reset();
}

template <class T, class D>
void uniquePtr<T[], D>::reset(T* p) noexcept 
{
    if (ptr_ != p) 
	{
        deleter_(ptr_);
        ptr_ = p;
    }
}

template <class T, class D>
T* uniquePtr<T[], D>::release() noexcept 
{
    T* p = ptr_;
    ptr_ = nullptr;
    return p;
}

template <class T, class D>
const D& uniquePtr<T[], D>::get_deleter() const noexcept 
{
    return deleter_;
}

template <class T, class D>
D& uniquePtr<T[], D>::get_deleter() noexcept 
{
    return deleter_;
}

template <class T, class D>
uniquePtr<T[], D>& uniquePtr<T[], D>::operator=(uniquePtr<T[], D>&& u) noexcept 
{
    reset(u.release());
    deleter_ = std::move(u.deleter_);
    return *this;
}

template <class T, class D>
uniquePtr<T[], D>& uniquePtr<T[], D>::operator=(nullptr_t) noexcept 
{
    reset();
    return *this;
}

template <class T, class D>
T& uniquePtr<T[], D>::operator[](size_t i) const 
{
    return ptr_[i];
}

template <class T, class D>
T* uniquePtr<T[], D>::get() const noexcept 
{
    return ptr_;
}

// Non-member swap function
template <class T, class Del>
void Swap(uniquePtr<T, Del>& lhs, uniquePtr<T, Del>& rhs) noexcept 
{
	lhs.swap(rhs);
}

// Make unique function
template <class T, size_t N>
uniquePtr<T[]> makeUnique() 
{
	return uniquePtr<T[]>(new T[N]);
}

template <class T, class... Args>
uniquePtr<T> makeUnique(Args&&... args) 
{
	return uniquePtr<T>(new T(std::forward<Args>(args)...));
}

class MyClass 
{
public:
    MyClass() 
	{
        std::cout << "MyClass constructor called!" << std::endl;
    }

    ~MyClass() 
	{
        std::cout << "MyClass destructor called!" << std::endl;
    }

    void sayHello() 
	{
        std::cout << "Hello, World!" << std::endl;
    }
};

int main() 
{
    // Example 1: Managing a single object with uniquePtr

    std::cout << "Example 1:" << std::endl;

    // Creating a uniquePtr with a MyClass object
    uniquePtr<MyClass> ptr1(new MyClass());

    // Accessing the object's member function
    ptr1->sayHello();

    // Example 2: Managing an array of objects with uniquePtr

    std::cout << "\nExample 2:" << std::endl;

    // Creating a uniquePtr with an array of MyClass objects
    uniquePtr<MyClass[]> ptr2(new MyClass[3]);

    // Accessing the objects in the array and calling member functions
    for (int i = 0; i < 3; ++i) 
	{
        ptr2.get()[i].sayHello();
    }

    // Example 3: Resetting and releasing a uniquePtr

    std::cout << "\nExample 3:" << std::endl;

    // Creating a uniquePtr with a MyClass object
    uniquePtr<MyClass> ptr3(new MyClass());

    // Resetting the uniquePtr with a new MyClass object
    ptr3.reset(new MyClass());

    // Releasing the ownership of the pointer from the uniquePtr
    MyClass* rawPtr = ptr3.release();

    // Using the raw pointer
    rawPtr->sayHello();

    // Deleting the raw pointer manually
    delete rawPtr;

    return 0;
}