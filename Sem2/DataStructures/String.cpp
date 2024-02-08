#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <memory>
#include <string>

//.........................................shared Pointer...................................//

template<class T>
class sharedPtr{
    T* m_ptr;
    uint32_t *m_refCount;
public:
    sharedPtr(T* ptr = nullptr) : m_ptr(ptr) {
        if (m_ptr) {
	        m_refCount = new uint32_t(1);
        } else {
	        m_refCount = nullptr;
        }
    
    }

	sharedPtr(T* data, std::default_delete<T>& dl) : m_ptr(data) {}

	~sharedPtr() {
	    if (m_refCount != nullptr) {
		    (*m_refCount)--;
		    if ((*m_refCount) == 0) {
			    delete m_ptr;
			    delete m_refCount;
		    }
	    }
	}

	sharedPtr(const sharedPtr& a) {
		m_ptr = a.m_ptr;
		m_refCount = a.m_refCount;
		(*m_refCount)++;
	}

	sharedPtr(sharedPtr&& a) : m_ptr(a.m_ptr), m_refCount(a.m_refCount) {
		a.m_ptr = nullptr;
		a.m_refCount = nullptr;
	}

	sharedPtr(std::weak_ptr<T>& x) {
		m_ptr = x.m_ptr;
		m_refCount = x.m_refCount;
		(*m_refCount)++;
	};

    friend std::ostream& operator<<(std::ostream& os, sharedPtr<T>& sp) {
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
bool sharedPtr<T>::operator==(const sharedPtr& src) const {
    return m_ptr == src.m_ptr;
}

template<class T>
bool sharedPtr<T>::operator!=(const sharedPtr& src) const {
    return m_ptr != src.m_ptr;
}

template<class T>
bool sharedPtr<T>::operator==(std::nullptr_t) const {
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
class sharedPtr<T[]> {
	T* m_ptr;
	uint32_t *m_refCount;
public:
	sharedPtr() {}

	explicit sharedPtr(T *m_ptr) {
        sharedPtr<T[]>::m_ptr = m_ptr;
		m_refCount = new uint32_t(1);
	}

	sharedPtr(const sharedPtr<T[]>& a) {
		m_ptr = a.m_ptr;
		m_refCount = a.m_refCount;
		(*m_refCount)++;
	}

	sharedPtr(sharedPtr<T[]>&& a) : m_ptr(a.m_ptr), m_refCount(a.m_refCount) {
		a.m_ptr = nullptr;
		a.m_refCount = nullptr;
	}

	~sharedPtr() {
		if (m_refCount != nullptr) {
			(*m_refCount)--;
			if ((*m_refCount) == 0) {
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
sharedPtr<T[]>& sharedPtr<T[]>::operator=(const sharedPtr<T[]>& a) {
    m_ptr = a.m_ptr;
    m_refCount = a.m_refCount;
    (*m_refCount)++;
    return *this;
}

template<class T>
sharedPtr<T[]>& sharedPtr<T[]>::operator=(sharedPtr<T[]>&& a) {
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
T& sharedPtr<T[]>::operator*() const { 
    return *m_ptr; 
}

template<class T>
T* sharedPtr<T[]>::operator->() const {
    return m_ptr; 
}

template<class T>
void sharedPtr<T[]>::swap(sharedPtr<T[]>& src) noexcept {
    std::swap(m_ptr, src.m_ptr);
}

template<class T>
int sharedPtr<T[]>::unique() {
    if (use_count() > 1) {
        return 0;
    }
    return 1;
}

template<class T>
T* sharedPtr<T[]>::get()const {
    return m_ptr;
}

template<class T>
T* sharedPtr<T[]>::release() noexcept {
    T* result = nullptr;
    std::swap(result, m_ptr);
    return result;
}

template<class T>
void sharedPtr<T[]>::reset() {
    T* tmp = release();
    delete tmp;
}

template<class T>
T& sharedPtr<T[]>::operator[](int pos) const {
    return sharedPtr<T[]>::m_ptr[pos];
}

template<class T>
uint32_t sharedPtr<T[]>::use_count() {
    return *m_refCount;
}

template <class T, class ...Args>
std::enable_if_t<!std::is_array_v<T>, sharedPtr<T>>
makeShared(Args&& ...args) {
	return sharedPtr<T>(new T(std::forward<Args>(args)...));
};

template <class T>
std::enable_if_t<std::is_array_v<T>, sharedPtr<T>>
makeShared(int size) {
	using type = std::remove_extent_t<T>;
	return sharedPtr<T>(new type[size]);
};

size_t mystrlen(const char* p) {
    const char* start = p;
    while (*p) p++;
    return static_cast<size_t>(p - start);
}

//.........................................shared Pointer.............................//


//...............................C functions.........................................//

void mystrcpy(char* s, const char* t) {
    while (*t) {
        *s = *t;
        s++;
        t++;
    }
    *s = *t;
}

char* my_strncat(char* destination, const char* source, size_t num) {

    char* ptr = destination + mystrlen(destination);
    while (*source != '\0' && num--) {
        *ptr++ = *source++;
    }
    *ptr = '\0';
    return destination;
}

char* mystrcat(char* s1, const char* s2) {
    char* ptr = s1 + mystrlen(s1);
    while (*s2 != '\0') {
        *ptr++ = *s2++;
    }
    *ptr = '\0';
    return ptr;
}

void mymemcpy(void *dest, const void *src, size_t n) {
    char *csrc = (char *)src;
    char *cdest = (char *)dest;
    for (size_t i = 0; i < n; i++)
        cdest[i] = csrc[i];

}

char* mystrncpy(char* destination, const char* source, size_t num)
{
    if (destination == nullptr) {
        return nullptr;
    }

    char* ptr = destination;
    while (*source && num--) {
        *destination = *source;
        destination++;
        source++;
    }

    *destination = '\0';
    return ptr;
}

size_t mystrcmp(const char* str1, const char* str2) {
    if (str1 == nullptr || str2 == nullptr)
        return -1;

    const size_t size1 = mystrlen(str1);
    const size_t size2 = mystrlen(str2);

    if (size1 != size2)
        return -1;

    for (size_t i = 0; str1[i] != '\0' && str2[i] != '\0'; i++) {
        if (str1[i] != str2[i])
            return -1;
    }
    return 0;
}

char* mystrtok(char * String, const char * delim) {
    static char * index;
    if (String != nullptr) {
        index = String;
    } else {

        String = index;
    }

    if (*index == '\0') {
        return nullptr;
    }

    while (*index != '\0') {
        for (size_t i = 0; delim[i] != '\0'; i++) {
            if (*index == delim[i]) {
                if (index == String) {
                    index++;
                    String++;
                } else {
                    *index = '\0';
                    break;
                }
            }
        }

        if (*index == '\0') {
            index++;
            return String;
        }

        index++;
    }
    return String;

}

void* mymemset(void *b, char c, int len) {
    char *b_char = (char *)b;
    if (b == NULL) return NULL;

    while (*b_char && len > 0) {
        *b_char = c;
        b_char++;
        len--;
    }

    return b;
}

int mystrcoll(const char* str1, const char* str2) {
    while (*str1 &&  *str2 && *str1 == *str2) {
        str1++;
        str2++;
    }
    return(*str1 > *str2) - (*str1 < *str2);
}

void* mymemmove(void *dest, const void *src, unsigned int n) {
    unsigned char isCopyRequire = 0;
    char *pcSource = (char *)src;
    char *pcDstn = (char *)dest;

    if ((pcSource == NULL) || (pcDstn == NULL)) {
        return NULL;
    }

    if ((pcSource < pcDstn) && (pcDstn < pcSource + n)) {
        for (pcDstn += n, pcSource += n; n--;) {
            *--pcDstn = *--pcSource;
        }
    } else {
        while (n--) {
            *pcDstn++ = *pcSource++;
        }
    }
    return dest;
}

int mystrncmp(const char * str1, const char * str2, unsigned int n) {
    while (*str1 == *str2) {
        if (*str1 == '\0' || *str2 == '\0')
            break;
        str1++;
        str2++;
    }

    if (*str1 == '\0' && *str2 == '\0')
        return 0;
    else
        return -1;
}

int my_memcmp(void *b, void *c, int len) {
    char *p = (char *)b;
    char *q = (char *)c;

    while (len > 0) {
        if (*p != *q)
            return (*p - *q);
        len--;
        p++;
        q++;
    }
    return 0;
}

size_t mystrxfrm(char* s1, const char *s2, size_t n) {
    size_t n2 = mystrlen(s2);
    if (n2 > n) {
        mystrcpy(s1, s2);
    }
    return n2;
}


//...............................C functions.........................................//


//.........................................String.............................//

class String {
private:
    sharedPtr<char[]> str;
    size_t size;
    size_t capacity;
public:
    String() : str(makeShared<char[]>(1)), size(0), capacity(15) {}
    ~String() { 
        str.reset();
    }
    String(const String& other) : str(other.str), size(other.size) {} 
    String(String&& other) noexcept
    {
        str = other.str;
        size = other.size;
        other.str.release();
        other.size = 0;
    }
    explicit String(const char* other);

    String& operator+=(const String& other);
    String& operator=(const char* other);
    String& operator=(String &&other) noexcept;

    size_t length();
    size_t _capacity();
    size_t maxSize();

    const char& operator[](size_t pos)const;
    char& operator[](size_t pos);
    char at(size_t pos);
    char* c_str();
    
    void reserve(size_t newCapacity);
    void append(const char* c);
    void resize(size_t newSize);
    void clear();
    void pushBack(char c);
    void popBack();

    bool empty();
    bool operator==(const char* chars);

    friend std::ostream& operator<<(std::ostream& os, const String& obj)
    {
        os << obj.str.get();
        return os;
    }
};

String& String::operator=(String &&other) noexcept
{
    str = other.str;
    size = other.size;
    other.str.release();
    other.size = 0;
    return *this;
}

String& String::operator=(const char* other)
{
	size = 0;
   	while (other[size] != '\0')
        size++;
    std::copy(other, other + size, str.get());
    return *this;
}

String& String::operator+=(const String& other) 
{
    size_t size = mystrlen(str.get());
    size_t otherSize = mystrlen(other.str.get());

    size_t newSize = size + otherSize;
    if (newSize >= capacity) 
    {
        reserve(newSize * 2);
    }
    mystrcat(str.get(), other.str.get());
    size = newSize;
    return *this;
}


void String::popBack() 
{
    if (!size) 
        throw std::out_of_range("Nothing to delete!");
    str[size-1] = '\0';
    --size;
}

void String::pushBack(char c) 
{
    if (size >= capacity) 
    {
        capacity = capacity * 2;
        sharedPtr<char[]> newStr = makeShared<char[]>(capacity);
        std::copy(str.get(), str.get() + capacity, newStr.get());
        str = newStr;
    }

    str[size] = c;
    size++;
    str[size] = '\0'; // Add null-terminator at the end
}

char* String::c_str() 
{
    return str.get();
}

void String::resize(size_t newSize) 
{
    if (newSize <= size) 
    {
        size = newSize;
        str[size] = '\0';
    } else if (newSize <= capacity) 
    {
        std::fill(str.get() + size, str.get() + newSize, '\0');
        size = newSize;
    } else 
    {
        capacity = newSize;
        sharedPtr<char[]> newStr = makeShared<char[]>(capacity + 1);
        std::copy(str.get(), str.get() + size, newStr.get());
        std::fill(newStr.get() + size, newStr.get() + capacity, '\0');
        str = newStr;
        size = newSize;
    }
}

void String::clear() 
{
    str.reset();
    size = 0;
    str = makeShared<char[]>(1);
}

bool String::empty() 
{
    return size != 0 ? true : false;
}

char String::at(size_t pos) 
{
    if (pos < 0 || pos >= size) 
    {
        throw std::out_of_range("String index out of bounds!");
    }
    return str[pos];
}

size_t String::maxSize() 
{
    return (size_t)-1 / sizeof(char);
}

char& String::operator[](size_t pos) 
{
    if (pos < 0 || pos >= size) 
    {
        throw std::out_of_range("String index out of bounds!");
    }
    return str[pos];
}

const char& String::operator[](size_t pos)const 
{
    if (pos < 0 || pos >= size) 
    {
        throw std::out_of_range("String index out of bounds!");
    }
    return str[pos];
}

void String::reserve(size_t newCapacity) 
{
    auto newData = makeShared<char[]>(newCapacity);
    std::copy(str.get(), str.get() + capacity, newData.get());
    str = std::move(newData);
    capacity = newCapacity;
}

void String::append(const char* c) 
{
    while(*c) 
    {
        if (size >= capacity) 
        {
            capacity = capacity * 2;
            sharedPtr<char[]> newStr = makeShared<char[]>(capacity);
            std::copy(str.get(), str.get() + capacity, newStr.get());
            str = newStr;
        }
        str[size] = *c;
        size++;
        c++;
    }
    str[size] = '\0'; // Add null-terminator at the end
}

size_t String::length() 
{
    return size;
}

size_t String::_capacity() 
{
    return capacity;
}

bool String::operator==(const char* chars) 
{
    if (!chars) 
        return false;
    return mystrcmp(str.get(), chars) == 0;
} 


//.........................................String.............................//


int main() 
{
    String b;
    b = "qwr";
    b.append("PIZDEC");
    b.popBack();
    String A;
    A = std::move(b);
    String c;
    std::cout<<A;
}