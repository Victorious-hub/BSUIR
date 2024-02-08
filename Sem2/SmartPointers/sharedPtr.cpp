#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <memory>

template<class T>
class sharedPtr
{
    T* m_ptr;
    uint32_t *m_refCount;
public:
    sharedPtr(T* ptr = nullptr) : m_ptr(ptr) 
    {
        if (m_ptr) 
        {
	        m_refCount = new uint32_t(1);
        } else
        {
	        m_refCount = nullptr;
        }
    
    }

	sharedPtr(T* data, std::default_delete<T>& dl) : m_ptr(data) {}

	~sharedPtr() 
    {
	    if (m_refCount != nullptr) 
        {
		    (*m_refCount)--;
		    if ((*m_refCount) == 0) 
            {
			    delete m_ptr;
			    delete m_refCount;
		    }
	    }
	}

	sharedPtr(const sharedPtr& a) 
    {
		m_ptr = a.m_ptr;
		m_refCount = a.m_refCount;
		(*m_refCount)++;
	}

	sharedPtr(sharedPtr&& a) : m_ptr(a.m_ptr), m_refCount(a.m_refCount)
    {
		a.m_ptr = nullptr;
		a.m_refCount = nullptr;
	}

	sharedPtr(std::weak_ptr<T>& x) 
    {
		m_ptr = x.m_ptr;
		m_refCount = x.m_refCount;
		(*m_refCount)++;
	};

    friend std::ostream& operator<<(std::ostream& os, sharedPtr<T>& sp) 
    {
        os << "Address pointed : " << sp.get() << std::endl;
        return os;
    }

    sharedPtr& operator=(sharedPtr&& a);
    sharedPtr& operator=(const sharedPtr& a);
	sharedPtr& operator=(std::weak_ptr<T>& x);
	T& operator*() const;
	T* operator->() const;
    T* get()const; 
	T* release() noexcept;
    uint32_t use_count();
	void swap(sharedPtr& src) noexcept;
	void reset();
    int unique();
	bool operator==(std::nullptr_t) const;
	bool operator!=(const sharedPtr& src) const;
	bool operator==(const sharedPtr& src) const;
};

template<class T>
sharedPtr<T>& sharedPtr<T>::operator=(const sharedPtr& a) {
    m_ptr = a.m_ptr;
    m_refCount = a.m_refCount;
    (*m_refCount)++;

    return *this;
}

template<class T>
sharedPtr<T>& sharedPtr<T>::operator=(sharedPtr&& a) {
    if (&a == this) {
        return *this;
    }

    delete m_ptr;
    delete m_refCount;

    m_ptr = a.m_ptr;
    a.m_ptr = nullptr;

    m_refCount = a.m_refCount;
    a.m_refCount = nullptr;

    return *this;
}

template<class T>
sharedPtr<T>& sharedPtr<T>::operator=(std::weak_ptr<T>& x)
{
    m_ptr = x.m_ptr;
    m_refCount = x.m_refCount;
    (*m_refCount)++;

    return *this;
}

template<class T>
T* sharedPtr<T>::operator->() const
{
    return m_ptr;
}

template<class T>
T& sharedPtr<T>::operator*() const 
{
    return *m_ptr;
}

template<class T>
bool sharedPtr<T>::operator==(const sharedPtr& src) const 
{
    return m_ptr == src.m_ptr;
}

template<class T>
bool sharedPtr<T>::operator!=(const sharedPtr& src) const 
{
    return m_ptr != src.m_ptr;
}

template<class T>
bool sharedPtr<T>::operator==(std::nullptr_t) const 
{
    return m_ptr == nullptr;
}

template<class T>
uint32_t sharedPtr<T>::use_count()
{
    return *m_refCount;
}

template<class T>
void sharedPtr<T>::reset()
{
    T* tmp = release();
    delete tmp;
}

template<class T>
T* sharedPtr<T>::release() noexcept
{
    T* result = nullptr;
    std::swap(result, m_ptr);
    return result;
}

template<class T>
void sharedPtr<T>::swap(sharedPtr& src) noexcept
{
    std::swap(m_ptr, src.m_ptr);
}

template<class T>
int sharedPtr<T>::unique()
{
    if (use_count() > 1) {
        return 0;
    }
    return 1;
}

template<class T>
T* sharedPtr<T>::get() const 
{
    return m_ptr;
}


template<class T>
class sharedPtr<T[]> 
{
	T* m_ptr;
	uint32_t *m_refCount;
public:
	sharedPtr() {}

	explicit sharedPtr(T *m_ptr) 
    {
        sharedPtr<T[]>::m_ptr = m_ptr;
		m_refCount = new uint32_t(1);
	}

	sharedPtr(const sharedPtr<T[]>& a) 
    {
		m_ptr = a.m_ptr;
		m_refCount = a.m_refCount;
		(*m_refCount)++;
	}


	sharedPtr(sharedPtr<T[]>&& a) : m_ptr(a.m_ptr), m_refCount(a.m_refCount) 
    {
		a.m_ptr = nullptr;
		a.m_refCount = nullptr;
	}

	~sharedPtr() 
    {
		if (m_refCount != nullptr) 
        {
			(*m_refCount)--;
			if ((*m_refCount) == 0) 
            {
				delete[] m_ptr;
				delete m_refCount;
			}
		}
	}

    sharedPtr<T[]>& operator=(const sharedPtr<T[]>& a);
	sharedPtr<T[]>& operator=(sharedPtr<T[]>&& a);
	T& operator*() const;
    T& operator[](int pos) const;
	T* operator->() const;
    T* get()const;
	T* release() noexcept;
	void swap(sharedPtr<T[]>& src) noexcept;
	void reset();
    int unique();
	uint32_t use_count();

};

template<class T>
sharedPtr<T[]>& sharedPtr<T[]>::operator=(const sharedPtr<T[]>& a) 
{
    m_ptr = a.m_ptr;
    m_refCount = a.m_refCount;
    (*m_refCount)++;
    return *this;
}

template<class T>
sharedPtr<T[]>& sharedPtr<T[]>::operator=(sharedPtr<T[]>&& a) 
{
    if (&a == this)
        return *this;

    delete m_ptr;
    delete m_refCount;

    m_ptr = a.m_ptr;
    a.m_ptr = nullptr;

    m_refCount = a.m_refCount;
    a.m_refCount = nullptr;

    return *this;
}

template<class T>
T& sharedPtr<T[]>::operator*() const 
{ 
    return *m_ptr; 
}

template<class T>
T* sharedPtr<T[]>::operator->() const
{
    return m_ptr; 
}

template<class T>
void sharedPtr<T[]>::swap(sharedPtr<T[]>& src) noexcept 
{
    std::swap(m_ptr, src.m_ptr);
}

template<class T>
int sharedPtr<T[]>::unique() 
{
    if (use_count() > 1) 
    {
        return 0;
    }
    return 1;
}

template<class T>
T* sharedPtr<T[]>::get()const 
{
    return m_ptr;
}

template<class T>
T* sharedPtr<T[]>::release() noexcept 
{
    T* result = nullptr;
    std::swap(result, m_ptr);
    return result;
}

template<class T>
void sharedPtr<T[]>::reset() 
{
    T* tmp = release();
    delete tmp;
}

template<class T>
T& sharedPtr<T[]>::operator[](int pos) const 
{
    return sharedPtr<T[]>::m_ptr[pos];
}

template<class T>
uint32_t sharedPtr<T[]>::use_count() 
{
    return *m_refCount;
}

template <class T, class ...Args>
std::enable_if_t<!std::is_array_v<T>, sharedPtr<T>>
makeShared(Args&& ...args) 
{
	return sharedPtr<T>(new T(std::forward<Args>(args)...));
};

template <class T>
std::enable_if_t<std::is_array_v<T>, sharedPtr<T>>
makeShared(int size) 
{
	using type = std::remove_extent_t<T>;
	return sharedPtr<T>(new type[size]);
};

int main() 
{
    // Example 1: sharedPtr for a single object (std::string)
    sharedPtr<std::string> ptr1 = makeShared<std::string>("Hello, World!");
    std::cout << "ptr1: " << *ptr1 << std::endl;

    // Example 2: sharedPtr for an array of objects (double)
    sharedPtr<double[]> ptr2 = makeShared<double[]>(3);
    ptr2[0] = 1.1;
    ptr2[1] = 2.2;
    ptr2[2] = 3.3;
    std::cout << "ptr2[0]: " << ptr2[0] << std::endl;
    std::cout << "ptr2[1]: " << ptr2[1] << std::endl;
    std::cout << "ptr2[2]: " << ptr2[2] << std::endl;

    // Example 3: Copying sharedPtr
    sharedPtr<int> ptr3 = makeShared<int>(10);
    sharedPtr<int> ptr4 = ptr3;
    std::cout << "ptr3: " << *ptr3 << std::endl;
    std::cout << "ptr4: " << *ptr4 << std::endl;

    // Example 4: Moving sharedPtr
    sharedPtr<int> ptr5 = makeShared<int>(20);
    sharedPtr<int> ptr6 = std::move(ptr5);
    std::cout << "ptr6: " << *ptr6 << std::endl;

    // Example 5: Resetting sharedPtr
    sharedPtr<int> ptr7 = makeShared<int>(30);
    std::cout << "ptr7: " << *ptr7 << std::endl;
    ptr7.reset();
    return 0;
}