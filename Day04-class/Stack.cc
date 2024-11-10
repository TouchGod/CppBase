#include <iostream>
using std::cerr;
using std::cout;
using std::endl;

class Stack {
public:
	bool empty();	//判断栈是否为空
	bool full();	//判断栈是否已满
	void push(int); //元素入栈
	void pop();     //元素出栈
	int  top();		//获取栈顶元素
	
	Stack(size_t capacity = 10)
		: _capacity(capacity)
		, _top(-1)
		, _array(new int[capacity]())
	{}

	~Stack()
	{
		if(_array){
			delete [] _array;
			_array = nullptr;
		}
	}

private:
	int _capacity;
	int _top;
	int * _array;
};

bool Stack::empty(){
	return -1 == _top;
}

bool Stack::full(){
	return _top == _capacity;
}

void Stack::push(int num){
	if (!full()){
		_array[++_top] = num;
	}else{
        cerr << "stack is full!!!" << endl;
        return ;
    }
}

void Stack::pop(){
	if (!empty()){
        --_top;
    }else {
        cerr << "stack is empty!!!" << endl;
        return ;
    }
}

int Stack::top(){
	if (!empty()){
		return _array[_top];
	}
	else {
        throw "stack is empty!!!";
    }
}


void test0(){
	Stack stack;
	cout << "empty? " << stack.empty() << endl;
	cout << "full? " << stack.full() << endl;

	stack.push(1);
	stack.push(2);
	stack.push(3);
	cout << stack.top() << endl;
	stack.pop();
	cout << stack.top() << endl;
    stack.pop();
    stack.pop();

    stack.pop();
}



int main()
{
	test0();
    return 0;
}