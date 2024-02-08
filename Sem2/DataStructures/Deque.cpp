#include <iostream>
#include <cstdlib>
#include <string>
#include <cstdio>
#include <type_traits>
#include <memory>

template <class T, class Del = std::default_delete<T>>
class uniquePtr 
{
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
    if (ptr_ != ptr) 
	{
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

template <class T, class ...Args>
std::enable_if_t<!std::is_array_v<T>, uniquePtr<T>>
makeUnique(Args&& ...args)
{
	return uniquePtr<T>(new T(std::forward<Args>(args)...));
};

template <class T>
std::enable_if_t<std::is_array_v<T>, uniquePtr<T>>
makeUnique(int size)
{
	using type = std::remove_extent_t<T>;
	return uniquePtr<T>(new type[size]);
};


template <class X>
class Deque {
private:
	int frontIndex;
	int backIndex;
	uniquePtr<X[]> arr;
	int sizeVar;
	int capacityVar = 4;

public:
	Deque()
	{
		arr = makeUnique<X[]>(capacityVar);
		frontIndex = backIndex = -1;
		sizeVar = 0;
	}

	bool empty();
	bool full();
	void push_back(X x);
	void push_front(X x);
	void pop_front();
	void pop_back();
	X front();
	X back();
	int capacity();
	int size();

	X& operator[](int index)
	{
		return arr[index];
	}

	void clear() 
	{
		arr.reset(); 
	}
};

template <class X>
int Deque<X>::capacity() 
{
	return capacityVar;
}

template <class X>
int Deque<X>::size() 
{
    return sizeVar;
}

template <class X>
bool Deque<X>::empty() 
{
	if (frontIndex == -1 && backIndex == -1)
		return true;
	else
		return false;
}

template <class X>
bool Deque<X>::full() 
{
	if (sizeVar == capacityVar)
		return true;
	else
		return false;
}

template <class X>
X Deque<X>::front() 
{
	// If deque is empty
	if (empty()) 
	{
		std::cout << "Deque underflow" << std::endl;
		abort();
	}
	return arr[frontIndex];
}

template <class X>
X Deque<X>::back()
{
	// If deque is empty
	if (empty()) 
	{
		std::cout << "Deque underflow" << std::endl;
		abort();
	}
	return arr[backIndex];
}

template <class X>
void Deque<X>::push_back(X x)
{
	if (full()) 
	{
		capacityVar = capacityVar * 2;
		uniquePtr<X[]> temp = makeUnique<X[]>(capacityVar);
		int i = frontIndex;
		int j = 0;
		while (i != backIndex) 
		{
			temp[j] = arr[i];
			i = (i + 1) % sizeVar;
			j++;
		}
		temp[j] = arr[i];

		frontIndex = 0;
		backIndex = sizeVar - 1;
		arr.reset();
		arr = std::move(temp);
	}

	// If size is zero
	if (empty()) 
	{
		frontIndex = backIndex = 0;
		arr[backIndex] = x;
		sizeVar++;
		return;
	}

	// Increment back index cyclically
	backIndex = (backIndex + 1) % capacityVar;
	arr[backIndex] = x;
	sizeVar++;
	return;
}

template <class X>
void Deque<X>::push_front(X x)
{
	if (full()) 
	{
		capacityVar = capacityVar * 2;
		uniquePtr<X[]> temp = makeUnique<X[]>(capacityVar);
		int i = frontIndex;
		int j = 0;
		while (i != backIndex) 
		{
			temp[j] = arr[i];
			i = (i + 1) % sizeVar;
			j++;
		}
		temp[j] = arr[i];

		frontIndex = 0;
		backIndex = sizeVar - 1;
		arr.reset();
		arr = std::move(temp);
	}

	// If size is zero
	if (empty()) 
	{
		frontIndex = backIndex = 0;
		arr[backIndex] = x;
		sizeVar++;
		return;
	}

	// Decrement front index cyclically
	frontIndex
		= (frontIndex - 1 + capacityVar) % capacityVar;
	arr[frontIndex] = x;
	sizeVar++;
	return;
}

template <class X>
void Deque<X>::pop_front()
{
	// If deque is empty
	if (empty()) {
		std::cout << "Deque underflow" << std::endl;
		abort();
	}

	// If there is only one character
	if (frontIndex == backIndex) 
	{
		frontIndex = backIndex = -1;
		sizeVar--;
		return;
	}

	// Increment frontIndex cyclically
	frontIndex = (frontIndex + 1) % capacityVar;
	sizeVar--;
	return;
}

template <class X>
void Deque<X>::pop_back()
{
	// If deque is empty
	if (empty()) {
		std::cout << "Deque underflow" << std::endl;
		abort();
	}

	if (frontIndex == backIndex) {
		frontIndex = backIndex = -1;
		sizeVar--;
		return;
	}

	backIndex = (backIndex - 1 + capacityVar) % capacityVar;
	sizeVar--;
	return;
}

int main() 
{
    Deque<int> intDeque;

    // Example of push_back()
    intDeque.push_back(10);
    intDeque.push_back(20);
    intDeque.push_back(30);

    // Example of push_front()
    intDeque.push_front(5);
    intDeque.push_front(2);

    // Example of size()
    std::cout << "Size: " << intDeque.size() << std::endl;

    // Example of capacity()
    std::cout << "Capacity: " << intDeque.capacity() << std::endl;

    // Example of empty()
    std::cout << "Empty: " << (intDeque.empty() ? "true" : "false") << std::endl;

    // Example of front()
    std::cout << "Front element: " << intDeque.front() << std::endl;

    // Example of back()
    std::cout << "Back element: " << intDeque.back() << std::endl;

    // Example of operator[]
    std::cout << "Element at index 2: " << intDeque[2] << std::endl;

    // Example of pop_front()
    intDeque.pop_front();

    // Example of pop_back()
    intDeque.pop_back();

    // Example of clear()
    intDeque.clear();

    // Example of empty() after clear()
    std::cout << "Empty after clear: " << (intDeque.empty() ? "true" : "false") << std::endl;

    return 0;
}