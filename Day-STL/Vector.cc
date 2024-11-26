// 了解std::allocator的用法之后,实现自定义的Vector类
// 接口形式：
// template<typename T>
// class Vector
// {
// public:
//     Vector();
//     ~Vector();
//     void push_back(const T &);
//     void pop_back();
//     int size();
//     int capacity();
// private:
//     void reallocate();//重新分配内存,动态扩容要用的
// private:
//     static std::allocator<T> _alloc;
//     T *_start;                 //指向数组中的第一个元素
//     T *_finish;                //指向最后一个实际元素之后的那个元素
//     T *_end_of_storage;        //指向数组本身之后的位置
// };

//  Vector模型
//  ______________________________
//  |_|_|_|_|_|____________________|
//  ↑          ↑                    ↑
//  _start   _finish            _end_of_storage

#include <iostream>
#include <memory>
#include <stdexcept>

using std::cout;
using std::endl;

template <typename T>
class Vector
{
    typedef T *iterator;

public:
    Vector()
        : _start(nullptr), _finish(nullptr), _end_of_storage(nullptr)
    {
        // _start = _alloc.allocate(1);
        // _finish = _start;
        // _end_of_storage = _start + 1;
    }

    ~Vector()
    {
        for (int i = 0; i < size(); ++i)
        {
            _alloc.destroy(_start + i);
        }
        _alloc.deallocate(_start, capacity());
    }

    void push_back(const T &val)
    {
        if (size() == capacity())
        {
            reallocate();
        }
        _alloc.construct(_finish, val);
        ++_finish;
    }

    void pop_back()
    {
        if (size() == 0)
            throw std::out_of_range("Vector is empty.");
        --_finish;
        _alloc.destroy(_finish);
    }

    iterator begin()
    {
        return _start;
    }

    iterator end()
    {
        return _finish;
    }

    int size() const
    {
        return _finish - _start;
    }

    int capacity() const
    {
        return _end_of_storage - _start;
    }

    void print() const
    {
        for (int i = 0; i < size(); ++i)
        {
            cout << *(_start + i) << " ";
        }
        cout << endl;
    }

private:
    // 重新分配内存,动态扩容要用的
    void reallocate()
    {
        /*
        int s = size();
        int new_capa = 2 * capacity();
        T *new_start = _alloc.allocate(new_capa);
        _finish = new_start;
        _end_of_storage = new_start + new_capa;

        for (int i = 0; i < s; ++i)
        {
            _alloc.construct(_finish, *(_start + i));
            _alloc.destroy(_start + i);
            _finish++;
        }

        _alloc.deallocate(_start, new_capa / 2);
        _start = new_start;
        */

        int oldCapacity = capacity();
        int newCapacity = 2 * oldCapacity > 0 ? 2 * oldCapacity : 1;
        // 分配新的内存空间
        T *ptmp = _alloc.allocate(newCapacity);
        if (_start)
        {
            /* copy(_start, _finish, ptmp); */
            // 使用未初始化内存的复制，因为新分配的空间尚未构造对象
            std::uninitialized_copy(_start, _finish, ptmp);
            // 销毁旧的内存空间上的对象
            while (_finish != _start)
            {
                _alloc.destroy(--_finish);
            }
            // 释放旧的内存空间
            _alloc.deallocate(_start, oldCapacity);
        }
        // 更新指针以指向新的内存空间
        _start = ptmp;
        _finish = _start + oldCapacity;
        _end_of_storage = _start + newCapacity;
    }

private:
    static std::allocator<T> _alloc;
    T *_start;          // 指向数组中的第一个元素
    T *_finish;         // 指向最后一个实际元素之后的那个元素
    T *_end_of_storage; // 指向数组本身之后的位置
};

template <class T>
std::allocator<T> Vector<T>::_alloc;

template <class Container>
void display(const Container &vec)
{
    cout << "vec.size() = " <<vec.size() << endl
         << "vec.capacity() = " << vec.capacity() << endl;
}

void test0()
{
    Vector<int> vector;
    display(vector);
    vector.push_back(1);
    vector.print();
    display(vector);
    vector.push_back(2);
    display(vector);
    vector.push_back(3);
    vector.push_back(4);
    vector.push_back(5);
    vector.print();
    display(vector);    
    vector.pop_back();
    display(vector);
    
    // 自定义类中实现iteator，可以增强for循环遍历
    for (auto & ele : vector)
    {
        cout << ele << " ";
    }
    cout << endl;
}

int main()
{
    test0();
    return 0;
}
