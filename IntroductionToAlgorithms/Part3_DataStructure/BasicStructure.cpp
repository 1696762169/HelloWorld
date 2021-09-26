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
	m_nil = new myListNode<T>;
	(*m_nil).m_prev = m_nil;
	(*m_nil).m_next = m_nil;
}
template<class T>
myList<T>::~myList() // 析构函数
{
	while (m_nil->m_next != m_nil)
	{
		//cout << m_nil->m_next->m_key << endl;
		del(m_nil->m_next);
	}
	del(m_nil);
}
template<class T>
myListNode<T>* myList<T>::search(T key) // 查找
{
	myListNode<T>* sp = m_nil->m_next;
	while (sp != m_nil && sp->m_key != key)
	{
		sp = sp->m_next;
	}
	return sp;
}
template<class T>
void myList<T>::insert(T key) // 插入(头插)
{
	myListNode<T>* node = new myListNode<T>(key);
	node->m_next = m_nil->m_next;
	node->m_prev = m_nil;
	m_nil->m_next->m_prev = node;
	m_nil->m_next = node;
}
template<class T>
void myList<T>::del(myListNode<T>* node) // 删除
{
	node->m_next->m_prev = node->m_prev;
	node->m_prev->m_next = node->m_next;
	delete node;
}

// 使用数组实现链表类
template<class T>
VList<T>::VList(int len) // 构造函数
{
	m_size = 0;
	m_free = 0;
	m_next_v = new int[len + 1];
	m_key_v = new T[len + 1];
	m_prev_v = new int[len + 1];
	for (int i = 0; i < len; ++i)
	{
		m_next_v[i] = i + 1;
		//m_prev_v[i + 1] = i;
	}
	m_next_v[len] = 0;
	//m_prev_v[0] = len;
}
template<class T>
VList<T>::~VList() // 析构函数
{
	if (m_next_v != NULL)
	{
		delete[] m_next_v;
	}
	if (m_key_v != NULL)
	{
		delete[] m_key_v;
	}
	if (m_prev_v != NULL)
	{
		delete[] m_prev_v;
	}
}
template<class T>
void VList<T>::allocateObject(T elem) // 插入（分配空间）
{
	// 为新增节点赋值
	m_key_v[m_free] = elem;
	// 新增节点与上一个已使用节点链接
	m_prev_v[m_next_v[m_free]] = m_free;
	// 移动free“指针”至下一个未使用节点
	m_free = m_next_v[m_free];
	++m_size;
}
template<class T>
void VList<T>::freeObject(int no) // 删除（释放空间）
{
	// 删除节点的前后节点相互链接
	m_next_v[m_prev_v[no]] = m_next_v[no];
	m_prev_v[m_next_v[no]] = m_prev_v[no];
	// 删除节点与最后一个已使用节点链接
	m_next_v[m_prev_v[m_free]] = no;
	m_prev_v[no] = m_prev_v[m_free];
	// 删除节点作为新的未使用节点，与上一个未使用节点链接
	m_prev_v[m_free] = no;
	m_next_v[no] = m_free;
	// 移动free“指针”
	m_free = no;
	--m_size;
}
template<class T>
void VList<T>::for_each() // 遍历元素
{
	int p = m_free;
	for (int i = 0; i < m_size; ++i)
	{
		p = m_prev_v[p];
		cout << m_key_v[p] << endl;
	}
}
template<class T>
int VList<T>::search(T elem) // 查找元素
{
	int p = m_free;
	for (int i = 0; i < m_size; ++i)
	{
		p = m_prev_v[p];
		if (m_key_v[p] == elem)
		{
			return p;
		}
	}
	return 0;
}

// 二叉树类
template<class T>
myBinaryTree<T>::myBinaryTree() // 构造函数
{
	m_root = new myBTNode<T>;
}
template<class T>
myBinaryTree<T>::~myBinaryTree() // 析构函数
{
	if (m_root != NULL)
	{
		for_each(m_root, &deleteNode);
		deleteNode(m_root);
	}
}
template<class T>
void myBinaryTree<T>::addLeft(T key, myBTNode<T>* parent) // 添加左节点
{
	if (parent == NULL)
		return;
	parent->m_lc = new myBTNode<T>;
	parent->m_lc->m_p = parent;
	parent->m_lc->m_key = key;
}
template<class T>
void myBinaryTree<T>::addRight(T key, myBTNode<T>* parent) // 添加右节点
{
	if (parent == NULL)
		return;
	parent->m_rc = new myBTNode<T>;
	parent->m_rc->m_p = parent;
	parent->m_rc->m_key = key;
}
template<class T>
void myBinaryTree<T>::for_each(myBTNode<T>* doing, void(*f)(myBTNode<T>* d)) // 遍历节点
{
	if (doing->m_lc != NULL) // 访问左节点
	{
		for_each(doing->m_lc, f);
	}
	if (doing->m_rc != NULL) // 访问右节点
	{
		for_each(doing->m_rc, f);
	}
	if (doing != m_root) // 执行操作
	{
		f(doing);
	}
}
template<class T>
void myBinaryTree<T>::print_key(myBTNode<T>* doing) // 输出节点的值
{
	cout << doing->m_key << endl;
}
template<class T>
void myBinaryTree<T>::deleteNode(myBTNode<T>* doing) // 删除节点
{
	delete doing;
	doing = NULL;
}

// 无限分支树类
template<class T>
myTree<T>::myTree() // 构造函数
{
	m_root = new myTreeNode<T>;
}
template<class T>
myTree<T>::~myTree() // 析构函数
{
	if (m_root != NULL)
	{
		for_each(m_root, &deleteNode);
		deleteNode(m_root);
	}
}
template<class T>
void myTree<T>::addchild(T key, myTreeNode<T>* parent) // 添加子节点
{
	if (parent == NULL)
		return;
	if (parent->m_child == NULL)
	{
		parent->m_child = new myTreeNode<T>;
		parent->m_child->m_p = parent;
		parent->m_child->m_key = key;
	}
	else
	{
		myTreeNode<T>* newc = parent->m_child;
		while (newc->m_sib != NULL)
		{
			newc = newc->m_sib;
		}
		newc->m_sib = new myTreeNode<T>;
		newc = newc->m_sib;
		newc->m_p = parent;
		newc->m_key = key;
	}
}
template<class T>
void myTree<T>::for_each(myTreeNode<T>* doing, void(*f)(myTreeNode<T>* d)) // 遍历节点
{
	if (doing->m_child != NULL) // 访问子节点
	{
		for_each(doing->m_child, f);
	}
	if (doing->m_sib != NULL) // 访问同级节点
	{
		for_each(doing->m_sib, f);
	}
	if (doing != m_root) // 执行操作
	{
		f(doing);
	}
}
template<class T>
void myTree<T>::print_key(myTreeNode<T>* doing) // 输出节点值
{
	cout << doing->m_key << endl;
}
template<class T>
void myTree<T>::deleteNode(myTreeNode<T>* doing) // 删除节点
{
	delete doing;
	doing = NULL;
	cout << "阿巴阿巴" << endl;
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
	/*myList<int> l;
	for (int i = 0; i < 13; ++i)
	{
		l.insert(i);
		cout << i << endl;
	}
	l.del(l.search(10));*/

	// 数组型链表测试
	/*VList<int> vl(capacity);
	for (int i = 0; i < capacity + 1; ++i)
	{
		vl.allocateObject(i);
	}
	vl.freeObject(3);
	vl.freeObject(5);
	vl.allocateObject(100);
	vl.allocateObject(100000);
	vl.for_each();
	cout << "-----------" << endl;
	vl.freeObject(vl.search(100));
	vl.freeObject(vl.search(100000));
	vl.for_each();*/

	// 二叉树类测试
	/*myBinaryTree<string> bt;
	bt.addLeft("L", bt.m_root);
	bt.addRight("R", bt.m_root);
	bt.addLeft("LL", bt.m_root->m_lc);
	bt.addLeft("RL", bt.m_root->m_rc);
	bt.addRight("LR", bt.m_root->m_lc);
	bt.addRight("RR", bt.m_root->m_rc);
	bt.for_each(bt.m_root, &(bt.print_key));*/

	// 无限分支树测试
	myTree<string> t;
	t.addchild("C1", t.m_root);
	t.addchild("C2", t.m_root);
	t.addchild("C3", t.m_root);
	t.addchild("C1C1", t.m_root->m_child);
	t.addchild("C1C2", t.m_root->m_child);
	t.addchild("C3C1", t.m_root->m_child->m_sib->m_sib);
	t.addchild("C3C2", t.m_root->m_child->m_sib->m_sib);
	t.addchild("C3C3", t.m_root->m_child->m_sib->m_sib);
	t.for_each(t.m_root, &(t.print_key));
}