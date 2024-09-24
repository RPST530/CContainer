#include <iostream>
#include <iterator> 
#include <cstddef>

template<class T, std::size_t s>
class CContainer
{
    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    using size_type = size_t;
    using difference_type = std::ptrdiff_t;

    template<class T>
    struct Iterator {
        using iterator_category = std::random_access_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T*;  
        using reference = T&;  

        Iterator(pointer ptr) : m_ptr(ptr) {}

        T& operator*() const { return *m_ptr; }
        T* operator->() { return m_ptr; }

        
        Iterator& operator++() { m_ptr++; return *this; }

        
        Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }

        Iterator& operator--() { m_ptr--; return *this; }


        Iterator operator--(int) { Iterator tmp = *this; --(*this); return tmp; }

        friend bool operator== (const Iterator& a, const Iterator& b) { return a.m_ptr == b.m_ptr; };
        friend bool operator!= (const Iterator& a, const Iterator& b) { return a.m_ptr != b.m_ptr; };
        friend bool operator< (const Iterator& a, const Iterator& b) { return b - a > 0; };
        friend bool operator> (const Iterator& a, const Iterator& b) { return b < a; }
        friend bool operator<= (const Iterator& a, const Iterator& b) { return !(a > b); }
        friend bool operator>= (const Iterator& a, const Iterator& b) { return !(a < b); }
        T& operator[](difference_type n) { return *(m_ptr + n); }

        Iterator operator+(difference_type n) { return Iterator(m_ptr + n); }
        Iterator operator-(difference_type n) { return Iterator(m_ptr - n); }

        Iterator& operator+=(difference_type n) { m_ptr += n; return *this; }
        Iterator& operator-=(difference_type n) { m_ptr -= n; return *this; }

        difference_type operator-(const Iterator& other) { return m_ptr - other.m_ptr; }
    private:
        pointer m_ptr;
    };
    template<class T>
    struct ConstIterator {
        using iterator_category = std::random_access_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = const T;
        using pointer = const T*;  
        using reference = const T&;  

        ConstIterator(pointer ptr) : m_ptr(ptr) {}

        T& operator*() const { return*m_ptr; }
        T* operator->() { return m_ptr; }

        ConstIterator& operator++() { m_ptr++; return *this; }
        ConstIterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }
        ConstIterator& operator--() { m_ptr--; return *this; }


        ConstIterator operator--(int) { Iterator tmp = *this; --(*this); return tmp; }

        friend bool operator== (const ConstIterator& a, const ConstIterator& b) { return a.m_ptr == b.m_ptr; };
        friend bool operator!= (const ConstIterator& a, const ConstIterator& b) { return a.m_ptr != b.m_ptr; };
        friend bool operator< (const ConstIterator& a, const ConstIterator& b) { return b - a > 0; };
        friend bool operator> (const ConstIterator& a, const ConstIterator& b) { return b < a; }
        friend bool operator<= (const ConstIterator& a, const ConstIterator& b) { return !(a > b); }
        friend bool operator>= (const ConstIterator& a, const ConstIterator& b) { return !(a < b); }
        T& operator[](difference_type n) const { return *(m_ptr + n); }

        ConstIterator operator+(difference_type n) const { return Iterator(m_ptr + n); }
        ConstIterator operator-(difference_type n) const { return Iterator(m_ptr - n); }

        ConstIterator& operator+=(difference_type n) { m_ptr += n; return *this; }
        ConstIterator& operator-=(difference_type n) { m_ptr -= n; return *this; }

        difference_type operator-(const Iterator& other) const { return m_ptr - other.m_ptr; }

        bool operator==(const Iterator& other) const { return m_ptr == other.m_ptr; }
        bool operator!=(const Iterator& other) const { return m_ptr != other.m_ptr; }
    private:
        pointer m_ptr;
    };

    using iterator = Iterator<T>;
    using const_iterator = ConstIterator<T>;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;
private:
    T data[s];
public:
    CContainer() {
    }
    CContainer(const CContainer& a)
    {
        for (size_t i = 0; i < s; i++)
        {
            data[i] = a.data[i];
        }
    }
    CContainer(CContainer&& other) {
        for (size_t i = 0; i < s; i++) {
            data[i] = std::move(other.data[i]); 
        }
    }
    ~CContainer()
    {

    }
    

    Iterator<T> begin() { return Iterator<T>(&data[0]); }
    Iterator<T> end() { return Iterator<T>(&data[s]); }
    ConstIterator<T> Cbegin() { return const_cast<const CContainer&>(*this).begin(); }
    ConstIterator<T> Cend() { return const_cast<const CContainer&>(*this).end(); }
   


    CContainer& operator =(const CContainer& other)
    {
        for (size_t i = 0; i < s; i++) {
            data[i] = other.data[i];
        }
        return *this;
    }
    CContainer& operator=(const CContainer&& other)  {
            for (size_t i = 0; i < s; i++) {
                data[i] = std::move(other.data[i]);
            }
        return *this; 
    }
    T& operator [](size_t i)
    {
        return data[i];
    }
    T& front() {
       
        return data[0];
    }
    T& back() {
       
        return data[size() - 1];
    }

    T* Getdata() {
        return data;
    }

    bool empty() const {
        return begin() == end();
    }

    void fill(const T& value) {
        for (size_t i = 0; i < s; i++) {
            data[i] = value;
        }
    }

    void swap(CContainer& other) {
        std::swap(data, other.data);
    }

    reverse_iterator rbegin() {
        return reverse_iterator(end());
    }

    reverse_iterator rend() {
        return reverse_iterator(begin());
    }

    const_reverse_iterator crbegin() const {
        return const_reverse_iterator(Cend());
    }

    const_reverse_iterator crend() const {
        return const_reverse_iterator(Cbegin());
    }
    size_t max_size()
    {
        return s;
    }
    size_t size()
    {
        return std::distance(this->begin(), this->end());
    }
   
    bool operator==(const CContainer& other) const {
        if (s != other.max_size()) {
            return false;
        }
        return std::equal(this->begin(), this->end(), other.begin(), other.end());
    }


    bool operator!=(const CContainer& other) const {
        return !(*this == other);
    }


    bool operator<(const CContainer& other) const {
        size_t minSize = std::min(s, other.max_size());
        for (size_t i = 0; i < minSize; ++i) {
            if (data[i] < other.data[i]) return true;
            if (data[i] > other.data[i]) return false;
        }
        return s < other.max_size();
    }


    bool operator<=(const CContainer& other) const {
        return *this < other || *this == other;
    }


    bool operator>(const CContainer& other) const {
        return !(*this <= other);
    }


    bool operator>=(const CContainer& other) const {
        return !(*this < other);
    }

    friend void swap(CContainer& a, CContainer& b)  {
        a.swap(b);
    }

};