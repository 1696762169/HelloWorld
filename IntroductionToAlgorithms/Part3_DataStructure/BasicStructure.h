#pragma once

#include<iostream>
using namespace std;

// 栈类
template<class T>
class myStack
{
public:
	myStack(int size);
	~myStack();

	bool is_empty();
	bool is_full();
	void push(T elem);
	T pop();

	T* m_top;

private:
	int m_capacity;
	T* m_stack;
};

// 队列类
template<class T>
class myQueue
{
public:
	myQueue(int capacity);
	~myQueue();

	bool is_empty();
	bool is_full();
	void enqueue(T elem);
	T dequeue();

	T m_head();
	T m_tail();

private:
	int m_capacity;
	T* m_queue;
	T* m_out;
	T* m_in;
};

// 为链表类准备的节点类
template<class T>
class myListNode
{
public:
	myListNode()
	{
		m_key = NULL;
		m_prev = NULL;
		m_next = NULL;
	}
	myListNode(T key)
	{
		m_key = key;
		m_prev = NULL;
		m_next = NULL;
	}

	T m_key;
	myListNode<T>* m_prev;
	myListNode<T>* m_next;
};
// 链表类
template<class T> 
class myList
{
public:
	myList();
	~myList();

	myListNode<T>* search(T key);
	void insert(T key);
	void del(myListNode<T>* node);
private:
	myListNode<T>* m_nil;
};

// 使用数组实现链表类
template<class T>
class VList
{
public:
	VList(int len);
	~VList();
	void allocateObject(T elem);
	void freeObject(int no);
	void for_each();
	int search(T elem);
	
private:
	int m_size;
	int m_free;
	int* m_next_v;
	T* m_key_v;
	int* m_prev_v;
};

// 为二叉树准备的节点类
template<class T>
class myBTNode
{
public:
	myBTNode()
	{
		m_p = NULL;
		m_lc = NULL;
		m_rc = NULL;
	}
	myBTNode<T>* m_p;
	myBTNode<T>* m_lc;
	myBTNode<T>* m_rc;
	T m_key;
};
// 二叉树类
template<class T>
class myBinaryTree : public myBTNode<T>
{
public:
	myBinaryTree();
	~myBinaryTree();

	void addLeft(T key, myBTNode<T>* parent);
	void addRight(T key, myBTNode<T>* parent);
	void for_each(myBTNode<T>* doing, void(*f)(myBTNode<T>* d));

	static void print_key(myBTNode<T>* doing);
	static void deleteNode(myBTNode<T>* doing);

	myBTNode<T>* m_root;
};

// 为无限节点树准备的节点类
template<class T>
class myTreeNode
{
public:
	myTreeNode()
	{
		m_p = NULL;
		m_child = NULL;
		m_sib = NULL;
	}
	myTreeNode<T>* m_p;
	myTreeNode<T>* m_child;
	myTreeNode<T>* m_sib;
	T m_key;
};

// 无限节点树类
template<class T>
class myTree
{
public:
	myTree();
	~myTree();

	void addchild(T key, myTreeNode<T>* parent);
	void for_each(myTreeNode<T>* doing, void(*f)(myTreeNode<T>* d));

	static void print_key(myTreeNode<T>* doing);
	static void deleteNode(myTreeNode<T>* doing);

	myTreeNode<T>* m_root;
};
