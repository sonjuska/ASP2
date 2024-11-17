#pragma once
#include "Heap.h"

class PriorityQueue {

	Heap h;

public:

	explicit PriorityQueue(int size) :  h(3) {};
	int get() const { return h.get(); }
	int remove(int steps) { return h.deleteKey(steps); }
	void insert(int elem,int steps) {
		h.add(elem,steps);
	}
	int isEmpty() const{
		if (h.getSize() == 0) return 1;
		else return 0;
	}
	int isFull() const {
		if (h.getCap() == h.getSize()) return 1;
		else return 0;
	}
	void printPQ() {
		h.printRow();
	}

};
