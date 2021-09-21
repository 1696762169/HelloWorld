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
class myNode
{
public:
	myNode()
	{
		m_key = NULL;
		m_prev = NULL;
		m_next = NULL;
	}
	myNode(T key)
	{
		m_key = key;
		m_prev = NULL;
		m_next = NULL;
	}

	T m_key;
	myNode<T>* m_prev;
	myNode<T>* m_next;
};
// 链表类
template<class T> 
class myList : public myNode<T>
{
public:
	myList();
	~myList();

	myNode<T>* search(T key);
	void insert(T key);
	void del(myNode<T>* node);
private:
	myNode<T>* m_nil;
};
