#pragma once

#include<iostream>
using namespace std;

// ջ��
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

// ������
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
}