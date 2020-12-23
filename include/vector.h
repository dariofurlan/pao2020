#ifndef VECTOR_H
#define VECTOR_H

template <class T>
class Vector {
   private:
    T* _buffer;
    unsigned int _size;
    unsigned int _capacity;

   public:
    Vector(unsigned int = 0);
    Vector(const Vector&);
    ~Vector();
    Vector& operator=(const Vector&);

    class iterator;
    class const_iterator;

    class iterator {
       protected:
        T* _current;

       public:
        iterator(T* i = nullptr) : _current(i) {}
        iterator(const iterator& i) : _current(i._current) {}
        T& operator*() const { return *_current; }
        T* operator->() const { return _current; }
        T& operator[](int n) const { return _current[n]; }
        iterator& operator++() {
            ++_current;
            return *this;
        }
        iterator operator++(int) { return iterator(_current++); }
        iterator& operator--() {
            --_current;
            return *this;
        }
        iterator operator--(int) { return iterator(_current--); }
        iterator& operator+=(int n) {
            return _current += n;
            return *this;
        }
        iterator operator+(int n) const { return iterator(_current + n); }
        iterator& operator-=(int n) {
            return _current -= n;
            return *this;
        }
        iterator operator-(int n) const { return iterator(_current - n); }
        const T* base() const { return _current; }
        bool operator==(const iterator& i) const { return _current == i.base(); }
        bool operator!=(const iterator& i) const { return _current != i.base(); }
        bool operator<(const iterator& i) const { return _current < i.base(); }
        bool operator>(const iterator& i) const { return _current > i.base(); }
        bool operator<=(const iterator& i) const { return _current <= i.base(); }
        bool operator>=(const iterator& i) const { return _current >= i.base(); }
    };

    class const_iterator {
       protected:
        T* _current;

       public:
        const_iterator(T* i = nullptr) : _current(i) {}
        const_iterator(const const_iterator& i) : _current(i._current) {}
        const T& operator*() const { return *_current; }
        const T* operator->() const { return _current; }
        const T& operator[](int n) const { return _current[n]; }
        const_iterator& operator++() {
            ++_current;
            return *this;
        }
        const_iterator operator++(int) { return const_iterator(_current++); }
        const_iterator& operator--() {
            --_current;
            return *this;
        }
        const_iterator operator--(int) { return const_iterator(_current--); }
        const_iterator& operator+=(int n) {
            return _current += n;
            return *this;
        }
        const_iterator operator+(int n) const { return const_iterator(_current + n); }
        const_iterator& operator-=(int n) {
            return _current -= n;
            return *this;
        }
        const_iterator operator-(int n) const { return const_iterator(_current - n); }
        const T* base() const { return _current; }
        bool operator==(const const_iterator& i) const { return _current == i.base(); }
        bool operator!=(const const_iterator& i) const { return _current != i.base(); }
        bool operator<(const const_iterator& i) const { return _current < i.base(); }
        bool operator>(const const_iterator& i) const { return _current > i.base(); }
        bool operator<=(const const_iterator& i) const { return _current <= i.base(); }
        bool operator>=(const const_iterator& i) const { return _current >= i.base(); }
    };

    unsigned int
    size();
    unsigned int capacity();
    bool is_empty();

    iterator begin() { return Vector<T>::iterator(_buffer); };
    iterator end() { return Vector<T>::iterator(_buffer + _size); };
    T& at(unsigned int);
    T& operator[](unsigned int);
    T& front();
    T& back();

    const_iterator begin() const { return Vector<T>::const_iterator(_buffer); }
    const_iterator end() const { return Vector<T>::const_iterator(_buffer + _size); };
    const T& at(unsigned int) const;
    const T& operator[](unsigned int) const;
    const T& front() const;
    const T& back() const;

    void push_back(const T&);
    void pop_back();
    iterator erase(iterator);
    void clear();
    void reserve(unsigned int);

    void insert(iterator pos, const T& val);
    void insert(iterator pos, unsigned int fill, const T& val);
    void swap(Vector&);

    void resize(unsigned int);
    void resize(unsigned int, const T&);
    void shrink_to_fit();

    // assign();  // assign vector content with many overloads if I remember correctly
};

template <class T>
Vector<T>::Vector(unsigned int capacity) : _buffer(new T[capacity == 0 ? 1 : capacity]), _size(0), _capacity(capacity) {
}

template <class T>
Vector<T>::Vector(const Vector& v) : _buffer(new T[v._capacity]), _size(v._size), _capacity(v._capacity) {
    for (unsigned int i = 0; i < v._size; i++) _buffer[i] = v._buffer[i];
}

template <class T>
Vector<T>::~Vector() { delete[] _buffer; }

template <class T>
Vector<T>& Vector<T>::operator=(const Vector<T>& v) {
    if (this != &v) {
        delete[] _buffer;

        _buffer = new T[v._capacity];
        _size = v._size;
        _capacity = v._capacity;

        for (unsigned int i = 0; i < v._size; i++) _buffer[i] = v._buffer[i];
    }
    return *this;
}

template <class T>
unsigned int Vector<T>::size() { return _size; };

template <class T>
unsigned int Vector<T>::capacity() { return _capacity; };

template <class T>
bool Vector<T>::is_empty() { return _size == 0; };

template <class T>
T& Vector<T>::at(unsigned int index) { return _buffer[index]; }
template <class T>
const T& Vector<T>::at(unsigned int index) const { return _buffer[index]; }

template <class T>
T& Vector<T>::operator[](unsigned int index) { return _buffer[index]; }
template <class T>
const T& Vector<T>::operator[](unsigned int index) const { return _buffer[index]; }

template <class T>
T& Vector<T>::front() { return _buffer[0]; }  // access element at the front
template <class T>
const T& Vector<T>::front() const { return _buffer[0]; }

template <class T>
T& Vector<T>::back() { return _buffer[_size - 1]; }  // access element at the back
template <class T>
const T& Vector<T>::back() const { return _buffer[_size - 1]; }

template <class T>
void Vector<T>::push_back(const T& v) {
    if (_size >= _capacity)
        reserve(_capacity * 2);
    _buffer[_size++] = v;
}

template <class T>
void Vector<T>::pop_back() { --_size; }

template <class T>
typename Vector<T>::iterator Vector<T>::erase(Vector<T>::iterator pos) {  // TODO CHECK THIS
    Vector<T>::iterator aux = pos;
    while (pos < (_buffer + _size - 1)) {
        pos[0] = pos[1];
        pos++;
    }
    --_size;
    return aux;
}

template <class T>
void Vector<T>::clear() {
    delete[] _buffer;
    _size = 0;
    _capacity = 1;
    _buffer = new T[1];
}

template <class T>
void Vector<T>::reserve(unsigned int n) {
    if (n > _capacity) {
        T* newbuff = new T[n];
        for (unsigned int i = 0; i < _size; i++)
            newbuff[i] = _buffer[i];

        _capacity = n;
        delete[] _buffer;
        _buffer = newbuff;
    }
}

template <class T>
void Vector<T>::insert(Vector<T>::iterator pos, const T& v) {
    reserve(++_size);

    for (T* scorri = end() - 1; scorri > pos; pos--) scorri[0] = scorri[-1];
    *pos = v;
}

template <class T>
void Vector<T>::insert(Vector<T>::iterator pos, unsigned int fill, const T& v) {
    if (fill == 0) return;
    _size += fill;
    reserve(_size);

    for (T* scorri = end() - 1; scorri > pos; pos--) scorri[0] = scorri[-1];
    *pos = v;
}

template <class T>
void Vector<T>::resize(unsigned int newsize) {
    if (newsize > _capacity)
        reserve(newsize);
    _size = newsize;
}

template <class T>
void Vector<T>::resize(unsigned int newsize, const T& v) {
    if (newsize > _capacity) {
        reserve(newsize);
        for (unsigned int i = _size; i < newsize; i++) _buffer[i] = v;
    }
    _size = newsize;
}

template <class T>
void Vector<T>::shrink_to_fit() {
    if (_size == _capacity) return;
    if (_size == 0) {
        _buffer = new T[1];
        _capacity = 1;
        return;
    }
    T* newbuff = new T[_size];
    for (unsigned int i = 0; i < _size; i++) newbuff[i] = _buffer[i];

    _buffer = newbuff;
    _capacity = _size;
}

#endif