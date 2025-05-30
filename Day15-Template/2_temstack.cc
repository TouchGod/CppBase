#include <iostream>
using std::cout;
using std::endl;

template <typename T = int, int capacity = 10>
class Stack
{
public:
	Stack()
	: _top(-1)
	, _query(new T[capacity]()){}

	~Stack()
	{
		if (_query)
		{
			delete [] _query;
			_query = nullptr;
		}
	}
	bool full()
	{
		return _top == capacity - 1;
	}
	bool empty()
	{
		return _top == -1;
	}

	void push(T t)
	{
		if (!full()){
			_query[++_top] = t;
		}
	}
	void pop()
	{
		if(!empty()){
			--_top;
		}
	}

	T top()
	{
		if (!empty()){
			return _query[_top];
		}
		else {
			throw "The stack is empty!";
		}
	}
private:
	int _top = -1;
	T * _query;
};
void test0(){
	Stack<double,10> s1;
	s1.push(1.23);
	s1.push(2.543);
	cout << s1.top() << endl;
	s1.pop();
	cout << s1.top() << endl;
	

}

int main()
{
	test0();
    return 0;
}

