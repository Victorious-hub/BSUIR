#include <iostream>
#include <string>
#include <memory>
#include <type_traits>
#include <algorithm>
#include <queue>
#include <vector>

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


typedef bool color_type;
template<class KeyType>
struct Node {

	std::pair<KeyType, char> container;

	sharedPtr<Node<KeyType>> parent;

	sharedPtr<Node<KeyType>> left;

	sharedPtr<Node<KeyType>> right;

	color_type color; // 1 -> Red, 0 -> Black
	Node(KeyType key)
	{
		container.first = key;
		left = nullptr;
		right = nullptr;
		parent = nullptr;
		color = true;
	}
	Node()
	{
		container.first = KeyType();
		left = nullptr;
		right = nullptr;
		parent = nullptr;
		color = true;
	}

};

template<class KeyType>
class Set {
private:
	sharedPtr<Node<KeyType>> root;

	sharedPtr<Node<KeyType>> nullptr_node;

	KeyType searchTreeHelper(sharedPtr<Node<KeyType>> node, KeyType key) {
		if (node == nullptr_node || key == node->container.first) {
			return  node->container.first;
		}

		if (key < node->container.first) {
			return searchTreeHelper(node->left, key);
		}
		return searchTreeHelper(node->right, key);
	}


	void getRotationColorChange(sharedPtr<Node<KeyType>> node) {
		sharedPtr<Node<KeyType>> uncle_node;
		while (node->parent->color == true) {
			if (node->parent == node->parent->parent->right) {
				uncle_node = node->parent->parent->left; // uncle
				if (uncle_node->color == true) {
					// case 3.1
					uncle_node->color = false;
					node->parent->color = false;
					node->parent->parent->color = true;
					node = node->parent->parent;
				}
				else {
					if (node == node->parent->left) {
						// case 3.2.2
						node = node->parent;
						rightRotate(node);
					}
					// case 3.2.1
					node->parent->color = false;
					node->parent->parent->color = true;
					leftRotate(node->parent->parent);
				}
			}
			else {
				uncle_node = node->parent->parent->right; // uncle

				if (uncle_node->color == true) {
					// mirror case 3.1
					uncle_node->color = false;
					node->parent->color = false;
					node->parent->parent->color = true;
					node = node->parent->parent;
				}
				else {
					if (node == node->parent->right) {
						// mirror case 3.2.2
						node = node->parent;
						leftRotate(node);
					}
					// mirror case 3.2.1
					node->parent->color = false;
					node->parent->parent->color = true;
					rightRotate(node->parent->parent);
				}
			}
			if (node == root) {
				break;
			}
		}
		root->color = false;
	}

	void deleteFix(sharedPtr<Node<KeyType>> x) {
		sharedPtr<Node<KeyType>> s;
		while (x != root && x->color == 0) {
			if (x == x->parent->left) {
				s = x->parent->right;
				if (s->color == 1) {
					s->color = 0;
					x->parent->color = 1;
					leftRotate(x->parent);
					s = x->parent->right;
				}

				if (s->left->color == 0 && s->right->color == 0) {
					s->color = 1;
					x = x->parent;
				}
				else {
					if (s->right->color == 0) {
						s->left->color = 0;
						s->color = 1;
						rightRotate(s);
						s = x->parent->right;
					}

					s->color = x->parent->color;
					x->parent->color = 0;
					s->right->color = 0;
					leftRotate(x->parent);
					x = root;
				}
			}
			else {
				s = x->parent->left;
				if (s->color == 1) {
					s->color = 0;
					x->parent->color = 1;
					rightRotate(x->parent);
					s = x->parent->left;
				}

				if (s->right->color == 0 && s->right->color == 0) {
					s->color = 1;
					x = x->parent;
				}
				else {
					if (s->left->color == 0) {
						s->right->color = 0;
						s->color = 1;
						leftRotate(s);
						s = x->parent->left;
					}

					s->color = x->parent->color;
					x->parent->color = 0;
					s->left->color = 0;
					rightRotate(x->parent);
					x = root;
				}
			}
		}
		x->color = 0;
	}

	void rbTransplant(sharedPtr<Node<KeyType>> u, sharedPtr<Node<KeyType>> v) {
		if (u->parent == nullptr) {
			root = v;
		}
		else if (u == u->parent->left) {
			u->parent->left = v;
		}
		else {
			u->parent->right = v;
		}
		v->parent = u->parent;
	}

	void deleteNodeHelper(sharedPtr<Node<KeyType>> node, KeyType key) {
		sharedPtr<Node<KeyType>>  z = nullptr_node;
		sharedPtr<Node<KeyType>>  x, y;
		while (node != nullptr_node) {
			if (node->container.first == key) {
				z = node;
			}

			if (node->container.first <= key) {
				node = node->right;
			}
			else {
				node = node->left;
			}
		}

		if (z == nullptr_node) {
			std::cout << "Key not found in the tree" << std::endl;
			return;
		}

		y = z;
		int y_original_color = y->color;
		if (z->left == nullptr_node) {
			x = z->right;
			rbTransplant(z, z->right);
		}
		else if (z->right == nullptr_node) {
			x = z->left;
			rbTransplant(z, z->left);
		}
		else {
			y = minimum(z->right);
			y_original_color = y->color;
			x = y->right;
			if (y->parent == z) {
				x->parent = y;
			}
			else {
				rbTransplant(y, y->right);
				y->right = z->right;
				y->right->parent = y;
			}

			rbTransplant(z, y);
			y->left = z->left;
			y->left->parent = y;
			y->color = z->color;
		}
		z.reset();
		if (y_original_color == 0) {
			deleteFix(x);
		}
	}

	std::vector<std::string>& inOrderHelper(sharedPtr<Node<KeyType>> node) {
		if (node != nullptr_node) {
			inOrderHelper(node->left);
			vec.push_back(node->container.first);
			inOrderHelper(node->right);
		}
		return vec;
	}


public:
	std::vector<std::string> vec;
	Set() {
		nullptr_node = sharedPtr<Node<KeyType>>(new Node<KeyType>());
		nullptr_node->color = false;
		nullptr_node->left = nullptr;
		nullptr_node->right = nullptr;
		root = nullptr_node;
	}

	std::vector<std::string>& inorder() {
		inOrderHelper(this->root);
		return vec;
	}

	sharedPtr<Node<KeyType>> minimum(sharedPtr<Node<KeyType>> node) {
		while (node->left != nullptr_node) {
			node = node->left;
		}
		return node;
	}

	sharedPtr<Node<KeyType>> maximum(sharedPtr<Node<KeyType>> node) {
		while (node->right != nullptr_node) {
			node = node->right;
		}
		return node;
	}

	sharedPtr<Node<KeyType>> successor(sharedPtr<Node<KeyType>> x) {
		if (x->right != nullptr_node) {
			return minimum(x->right);
		}

		sharedPtr<Node<KeyType>> y = x->parent;
		while (y != nullptr_node && x == y->right) {
			x = y;
			y = y->parent;
		}
		return y;
	}

	sharedPtr<Node<KeyType>> predecessor(sharedPtr<Node<KeyType>> x) {
		if (x->left != nullptr_node) {
			return maximum(x->left);
		}

		sharedPtr<Node<KeyType>> y = x->parent;
		while (y != nullptr_node && x == y->left) {
			x = y;
			y = y->parent;
		}

		return y;
	}


	void leftRotate(sharedPtr<Node<KeyType>> x) {
		sharedPtr<Node<KeyType>> y = x->right;
		x->right = y->left;
		if (y->left != nullptr_node) {
			y->left->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == nullptr) {
			this->root = y;
		}
		else if (x == x->parent->left) {
			x->parent->left = y;
		}
		else {
			x->parent->right = y;
		}
		y->left = x;
		x->parent = y;
	}

	void rightRotate(sharedPtr<Node<KeyType>> x) {
		sharedPtr<Node<KeyType>> y = x->left;
		x->left = y->right;
		if (y->right != nullptr_node) {
			y->right->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == nullptr) {
			this->root = y;
		}
		else if (x == x->parent->right) {
			x->parent->right = y;
		}
		else {
			x->parent->left = y;
		}
		y->right = x;
		x->parent = y;
	}

	void insert(KeyType key) {

		sharedPtr<Node<KeyType>> node = sharedPtr<Node<KeyType>>(new Node<KeyType>(key));
		node->container.first = key;

		node->left = nullptr_node;
		node->right = nullptr_node;

		sharedPtr<Node<KeyType>> y;
		y = nullptr;
		sharedPtr<Node<KeyType>> x = this->root;

		while (x != nullptr_node) {
			y = x;
			if (node->container.first < x->container.first) {
				x = x->left;
			}
			else {
				x = x->right;
			}
		}


		node->parent = y;
		if (y == nullptr) {
			root = node;
		}
		else if (node->container.first < y->container.first) {
			y->left = node;
		}
		else {
			y->right = node;
		}

		if (node->parent == nullptr) {
			node->color = false;
			return;
		}


		if (node->parent->parent == nullptr) {
			return;
		}

		getRotationColorChange(node);
	}


	void deleteNode(KeyType data) {
		deleteNodeHelper(this->root, data);
	}

	KeyType searchTree(KeyType k) {
		return searchTreeHelper(this->root, k);
	}

	KeyType operator[](const KeyType& key)
	{
		return searchTree(key);
	}

	sharedPtr<Node<KeyType>> getRoot() {
		return this->root;
	}

	sharedPtr<Node<KeyType>> next(sharedPtr<Node<KeyType>> node)
	{
		sharedPtr<Node<KeyType>> tmp = node->right;

		if (tmp) {
			while (tmp->left) tmp = tmp->left;
			return tmp;
		}
		tmp = node;
		while (tmp->parent && tmp.equals(tmp->parent->right))
			tmp = tmp->parent;

		return tmp->parent;
	}

	class iterator
	{
	private:
		sharedPtr<Node<KeyType>> iter;
		sharedPtr<Node<KeyType>> root_iter;
	public:
		std::pair<KeyType, char> pair;
		iterator() {}
		iterator(sharedPtr<Node<KeyType>> root) :iter(root) {
			pair.first = root->container.first;
		}

		bool operator==(const iterator& wp)
		{
			return wp.iter == iter;
		}
		bool operator!=(const iterator& wp)
		{
			return wp.iter != iter;
		}
	};


	iterator begin()
	{
		sharedPtr<Node<KeyType>> current = this->root;

		return iterator(minimum(current));
	}
	iterator end()
	{
		sharedPtr<Node<KeyType>> current = this->root;
		return iterator(maximum(current));
	}
	//NOT FINISHED

};

int main()
{
	Set<int> f;
	f.insert(5);
	std::cout << f.searchTree(6);
}