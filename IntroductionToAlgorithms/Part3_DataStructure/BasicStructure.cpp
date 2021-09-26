#include"BasicStructure.h"
#include"files.h"

// ջ���ܵ�ʵ��
template<class T>
myStack<T>::myStack(int capacity) // ���캯��
{
	m_capacity = capacity;
	m_stack = new T[m_capacity + 1];
	m_top = m_stack;
}
template<class T>
myStack<T>::~myStack() // ��������
{
	if (m_stack != NULL)
	{
		delete[] m_stack;
		m_stack = NULL;
		m_top = NULL;
	}
}
template<class T>
bool myStack<T>::is_empty() // �ж��Ƿ�Ϊ��
{
	return (m_top == m_stack);
}
template<class T>
bool myStack<T>::is_full() // �ж��Ƿ�����
{
	return (m_top == m_stack + m_capacity);
}
template<class T>
void myStack<T>::push(T elem) // ѹ��
{
	*++m_top = elem;
}
template<class T>
T myStack<T>::pop() // ����
{
	T elem = *m_top--;
	return elem;
}

// ���й��ܵ�ʵ��
template<class T>
myQueue<T>::myQueue(int capacity) // ���캯��
{
	m_capacity = capacity;
	m_queue = new T[m_capacity + 1];
	m_out = m_queue;
	m_in = m_out;
}
template<class T>
myQueue<T>::~myQueue() // ��������
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
bool myQueue<T>::is_empty() // �ж��Ƿ�Ϊ��
{
	return (m_out == m_in);
}
template<class T>
bool myQueue<T>::is_full() // �ж��Ƿ�����
{
	if (m_out == m_queue && m_in == m_queue + m_capacity)
	{
		return true;
	}
	return (m_out == m_in + 1);
}
template<class T>
void myQueue<T>::enqueue(T elem) // ���
{
	*m_in = elem;
	m_in = (m_in == m_queue + m_capacity) ? m_queue : m_in + 1;
}
template<class T>
T myQueue<T>::dequeue() // ����
{
	T elem = *m_out;
	m_out = (m_out == m_queue + m_capacity) ? m_queue : m_out + 1;
	return elem;
}
template<class T>
T myQueue<T>::m_head() // ���ʶ�ͷԪ��
{
	return *m_out;
}
template<class T>
T myQueue<T>::m_tail() // ���ʶ�βԪ��
{
	if (m_in == m_queue)
	{
		return *(m_queue + m_capacity);
	}
	return *(m_in - 1);
}

// �����ܵ�ʵ��
template<class T>
myList<T>::myList() // ���캯��
{
	m_nil = new myListNode<T>;
	(*m_nil).m_prev = m_nil;
	(*m_nil).m_next = m_nil;
}
template<class T>
myList<T>::~myList() // ��������
{
	while (m_nil->m_next != m_nil)
	{
		//cout << m_nil->m_next->m_key << endl;
		del(m_nil->m_next);
	}
	del(m_nil);
}
template<class T>
myListNode<T>* myList<T>::search(T key) // ����
{
	myListNode<T>* sp = m_nil->m_next;
	while (sp != m_nil && sp->m_key != key)
	{
		sp = sp->m_next;
	}
	return sp;
}
template<class T>
void myList<T>::insert(T key) // ����(ͷ��)
{
	myListNode<T>* node = new myListNode<T>(key);
	node->m_next = m_nil->m_next;
	node->m_prev = m_nil;
	m_nil->m_next->m_prev = node;
	m_nil->m_next = node;
}
template<class T>
void myList<T>::del(myListNode<T>* node) // ɾ��
{
	node->m_next->m_prev = node->m_prev;
	node->m_prev->m_next = node->m_next;
	delete node;
}

// ʹ������ʵ��������
template<class T>
VList<T>::VList(int len) // ���캯��
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
VList<T>::~VList() // ��������
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
void VList<T>::allocateObject(T elem) // ���루����ռ䣩
{
	// Ϊ�����ڵ㸳ֵ
	m_key_v[m_free] = elem;
	// �����ڵ�����һ����ʹ�ýڵ�����
	m_prev_v[m_next_v[m_free]] = m_free;
	// �ƶ�free��ָ�롱����һ��δʹ�ýڵ�
	m_free = m_next_v[m_free];
	++m_size;
}
template<class T>
void VList<T>::freeObject(int no) // ɾ�����ͷſռ䣩
{
	// ɾ���ڵ��ǰ��ڵ��໥����
	m_next_v[m_prev_v[no]] = m_next_v[no];
	m_prev_v[m_next_v[no]] = m_prev_v[no];
	// ɾ���ڵ������һ����ʹ�ýڵ�����
	m_next_v[m_prev_v[m_free]] = no;
	m_prev_v[no] = m_prev_v[m_free];
	// ɾ���ڵ���Ϊ�µ�δʹ�ýڵ㣬����һ��δʹ�ýڵ�����
	m_prev_v[m_free] = no;
	m_next_v[no] = m_free;
	// �ƶ�free��ָ�롱
	m_free = no;
	--m_size;
}
template<class T>
void VList<T>::for_each() // ����Ԫ��
{
	int p = m_free;
	for (int i = 0; i < m_size; ++i)
	{
		p = m_prev_v[p];
		cout << m_key_v[p] << endl;
	}
}
template<class T>
int VList<T>::search(T elem) // ����Ԫ��
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

// ��������
template<class T>
myBinaryTree<T>::myBinaryTree() // ���캯��
{
	m_root = new myBTNode<T>;
}
template<class T>
myBinaryTree<T>::~myBinaryTree() // ��������
{
	if (m_root != NULL)
	{
		for_each(m_root, &deleteNode);
		deleteNode(m_root);
	}
}
template<class T>
void myBinaryTree<T>::addLeft(T key, myBTNode<T>* parent) // �����ڵ�
{
	if (parent == NULL)
		return;
	parent->m_lc = new myBTNode<T>;
	parent->m_lc->m_p = parent;
	parent->m_lc->m_key = key;
}
template<class T>
void myBinaryTree<T>::addRight(T key, myBTNode<T>* parent) // ����ҽڵ�
{
	if (parent == NULL)
		return;
	parent->m_rc = new myBTNode<T>;
	parent->m_rc->m_p = parent;
	parent->m_rc->m_key = key;
}
template<class T>
void myBinaryTree<T>::for_each(myBTNode<T>* doing, void(*f)(myBTNode<T>* d)) // �����ڵ�
{
	if (doing->m_lc != NULL) // ������ڵ�
	{
		for_each(doing->m_lc, f);
	}
	if (doing->m_rc != NULL) // �����ҽڵ�
	{
		for_each(doing->m_rc, f);
	}
	if (doing != m_root) // ִ�в���
	{
		f(doing);
	}
}
template<class T>
void myBinaryTree<T>::print_key(myBTNode<T>* doing) // ����ڵ��ֵ
{
	cout << doing->m_key << endl;
}
template<class T>
void myBinaryTree<T>::deleteNode(myBTNode<T>* doing) // ɾ���ڵ�
{
	delete doing;
	doing = NULL;
}

// ���޷�֧����
template<class T>
myTree<T>::myTree() // ���캯��
{
	m_root = new myTreeNode<T>;
}
template<class T>
myTree<T>::~myTree() // ��������
{
	if (m_root != NULL)
	{
		for_each(m_root, &deleteNode);
		deleteNode(m_root);
	}
}
template<class T>
void myTree<T>::addchild(T key, myTreeNode<T>* parent) // ����ӽڵ�
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
void myTree<T>::for_each(myTreeNode<T>* doing, void(*f)(myTreeNode<T>* d)) // �����ڵ�
{
	if (doing->m_child != NULL) // �����ӽڵ�
	{
		for_each(doing->m_child, f);
	}
	if (doing->m_sib != NULL) // ����ͬ���ڵ�
	{
		for_each(doing->m_sib, f);
	}
	if (doing != m_root) // ִ�в���
	{
		f(doing);
	}
}
template<class T>
void myTree<T>::print_key(myTreeNode<T>* doing) // ����ڵ�ֵ
{
	cout << doing->m_key << endl;
}
template<class T>
void myTree<T>::deleteNode(myTreeNode<T>* doing) // ɾ���ڵ�
{
	delete doing;
	doing = NULL;
	cout << "���Ͱ���" << endl;
}

void basicStructure()
{
	int capacity = 10;

	// ջ����
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

	// ���в���
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

	// �������
	/*myList<int> l;
	for (int i = 0; i < 13; ++i)
	{
		l.insert(i);
		cout << i << endl;
	}
	l.del(l.search(10));*/

	// �������������
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

	// �����������
	/*myBinaryTree<string> bt;
	bt.addLeft("L", bt.m_root);
	bt.addRight("R", bt.m_root);
	bt.addLeft("LL", bt.m_root->m_lc);
	bt.addLeft("RL", bt.m_root->m_rc);
	bt.addRight("LR", bt.m_root->m_lc);
	bt.addRight("RR", bt.m_root->m_rc);
	bt.for_each(bt.m_root, &(bt.print_key));*/

	// ���޷�֧������
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