#pragma once
#include <iostream>

using namespace std;

class Heap {

	int* storage;
	int capacity;
	int size;
	int m;

	void makeCopy(const Heap& h);
	void move(Heap& h) {
		storage = h.storage;
		capacity = h.capacity;
		size = h.size;
		m = h.m;
		h.storage = nullptr;
		h.capacity = h.size = h.m = 0;
	}

	void clear() {
		delete[] storage;
		storage = nullptr;
		capacity = size = m = 0;
	}

	void makeHeap(int red);
	void makeHeap() { makeHeap(m); }
	int firstSon(int i) { return i * this->m + 1; }
	int lastSon(int i) { return (i + 1) * this->m; }
	int father(int i) { return (i - 1) / this->m; }
	void sort();
	friend ostream& operator <<(ostream &os, const Heap& h);

public:
	Heap(int red);
	Heap(int* keys, int red) {
		capacity = 100000;
		size = 0;
		m = red;
		this->storage = keys;
		makeHeap();
	}
	Heap(const Heap& h) { makeCopy(h); }
	Heap(Heap&& h) { move(h); }
	Heap& operator =(const Heap& h) {
		if (this != &h) { clear(); makeCopy(h); }
		return *this;
	}
	Heap& operator=(Heap&& h) {
		if (this != &h) { clear(); move(h); }
		return *this;
	}
	~Heap() { clear(); }

	int getCap()const { return capacity; }
	int getSize()const { return size; }
	int getM()const { return m; }
	void sort(int* niz,int red) {
		Heap h(niz, red);
		h.sort();
		h.storage = nullptr;
	}

	void add(int key,int&steps);
	int get()const;
	int deleteKey(int &steps);
	int minSon(int a, int b, int&steps);
	void convertTo(int newM,int*keys,int steps);
	void destroy();
	int find(int elem);
	void change(int elem, int zam);
	void printRow();
};