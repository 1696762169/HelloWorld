#include"BasicStructure.h"
#include"files.h"

// 栈功能的实现
template<class T>
myStack<T>::myStack(int capacity) // 构造函数
{
	m_capacity = capacity;
	m_stack = new T[m_capacity + 1];
	m_top = m_stack;
}
template<class T>
myStack<T>::~myStack() // 析构函数
{
	if (m_stack != NULL)
	{
		delete[] m_stack;
		m_stack = NULL;
		m_top = NULL;
	}
}
template<class T>
bool myStack<T>::is_empty() // 判断是否为空
{
	return (m_top == m_stack);
}
template<class T>
bool myStack<T>::is_full() // 判断是否已满
{
	return (m_top == m_stack + m_capacity);
}
template<class T>
void myStack<T>::push(T elem) // 压入
{
	*++m_top = elem;
}
template<class T>
T myStack<T>::pop() // 弹出
{
	T elem = *m_top--;
	return elem;
}

// 队列功能的实现
template<class T>
myQueue<T>::myQueue(int capacity) // 构造函数
{
	m_capacity = capacity;
	m_queue = new T[m_capacity + 1];
	m_out = m_queue;
	m_in = m_out;
}
template<class T>
myQueue<T>::~myQueue() // 析构函数
{
	if (m_queue != NULL)
	{
		delete[] m_queue;
		m_queue = NULL;
		m_out = NULL;
		m_in = NULL;
	}
}
template<class T>
bool myQueue<T>::is_empty() // 判断是否为空
{
	return (m_out == m_in);
}
template<class T>
bool myQueue<T>::is_full() // 判断是否已满
{
	if (m_out == m_queue && m_in == m_queue + m_capacity)
	{
		return true;
	}
	return (m_out == m_in + 1);
}
template<class T>
void myQueue<T>::enqueue(T elem) // 入队
{
	*m_in = elem;
	m_in = (m_in == m_queue + m_capacity) ? m_queue : m_in + 1;
}
template<class T>
T myQueue<T>::dequeue() // 出队
{
	T elem = *m_out;
	m_out = (m_out == m_queue + m_capacity) ? m_queue : m_out + 1;
	return elem;
}
template<class T>
T myQueue<T>::m_head() // 访问队头元素
{
	return *m_out;
}
template<class T>
T myQueue<T>::m_tail() // 访问队尾元素
{
	if (m_in == m_queue)
	{
		return *(m_queue + m_capacity);
	}
	return *(m_in - 1);
}

// 链表功能的实现
template<class T>
myList<T>::myList() // 构造函数
{
	m_nil = new myNode<T>;
	(*m_nil).m_prev = m_nil;
	(*m_nil).m_next = m_nil;
}
template<class T>
myList<T>::~myList() // 析构函数
{
	while (m_nil->m_next != m_nil)
	{
		cout << m_nil->m_next->m_key << endl;
		del(m_nil->m_next);
	}
	del(m_nil);
}
template<class T>
myNode<T>* myList<T>::search(T key) // 查找
{
	myNode<T>* sp = m_nil->m_next;
	while (sp != m_nil && sp->m_key != key)
	{
		sp = sp->m_next;
	}
	return sp;
}
template<class T>
void myList<T>::insert(T key) // 插入(头插)
{
	myNode<T>* node = new myNode<T>(key);
	node->m_next = m_nil->m_next;
	node->m_prev = m_nil;
	m_nil->m_next->m_prev = node;
	m_nil->m_next = node;
}
template<class T>
void myList<T>::del(myNode<T>* node) // 删除
{
	node->m_next->m_prev = node->m_prev;
	node->m_prev->m_next = node->m_next;
	delete node;
}

void basicStructure()
{
	int capacity = 10;

	// 栈测试
	/*myStack<int> s(capacity);
	for (int i = 0; i < capacity; ++i)
	{
		s.push(i);
		cout << *(s.m_top) << endl;
	}
	cout << "-----------" << endl;
	for (int i = 0; i < capacity; ++i)
	{
		cout << s.pop() << endl;
	}
	cout << "-----------" << endl;*/

	// 队列测试
	/*myQueue<int> q(capacity);
	for (int i = 0; i < capacity; ++i)
	{
		q.enqueue(i);
		cout << q.m_tail() << endl;
	}
	cout << "-----------" << endl;
	for (int i = 0; i < capacity / 2; ++i)
	{
		cout << q.dequeue() << endl;
	}
	cout << "-----------" << endl;
	for (int i = 0; i < capacity / 2; ++i)
	{
		q.enqueue(i);
		cout << q.m_tail() << endl;
	}*/

	// 链表测试
	myList<int> l;
	for (int i = 0; i < 13; ++i)
	{
		l.insert(i);
		cout << i << endl;
	}
}