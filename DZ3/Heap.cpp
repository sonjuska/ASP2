#include "Heap.h"

void Heap::makeCopy(const Heap& h)
{
	Heap novi(h.m);
	novi.size = h.size;
	for (int i = 0; i < h.size; i++) {
		novi.storage[i] = h.storage[i];
	}

}

void Heap::makeHeap(int red)
{
	size = 1;
	int br=0;
	for (int i = 1; i < 100000; i++) add(storage[i],br);
}

void Heap::sort()
{
	int steps;
	while (size > 0) {
		int first = deleteKey(steps);
		storage[size--] = first;
	}
}

Heap::Heap(int red)
{
	storage = new int[100000];
	capacity = 100000;
	m = red;
	size = 0;
}

void Heap::add(int key, int &steps)
{
	if (size == capacity) { "Container full"; return; }
	int f = father(size);
	int s = size++;
	while (s > 0 && storage[f] > key) {
		storage[s] = storage[f];
		s = f;
		f = father(f);
		steps+=2;
	}
	steps += 1;
	storage[s] = key;
}

int Heap::get() const
{
	if (size == 0) {
		return -1;
	}
	else {
		return storage[0];
	}
}

int Heap::deleteKey(int&steps)
{
	if (size == 0) {
		return -1;
	}
	int first = storage[0];
	storage[0] = storage[--size];
	int f = 0;
	while (f < size- 1) {
		int a = firstSon(f), b = lastSon(f);
		if (b > size - 1) b = size - 1;
		if (a > size - 1) break;
		int min = minSon(a, b, steps);
		if (storage[min] < storage[f]) {
			int temp = storage[min];
			storage[min] = storage[f];
			storage[f] = temp;
			steps += 2;
			
		}
		steps += 1;
		
		f = min;
		
	}
	return first;
}

int Heap::minSon(int a, int b, int& steps)
{
	int min = storage[a],ind=a, i;
	for (i = a; i <= b; i++) {
		if (storage[i] < min) {
			min = storage[i]; 
			ind = i;
			steps++;
		}
			
	}
	return ind;
}

void Heap::convertTo(int newM,int*keys,int steps)
{
	m = newM;
	int len = size;
	for (int i = 0; i < len; i++) {
		deleteKey(steps);
	}
	for (int i = 0; i < len; i++) {
		add(keys[i],steps);
	}
	cout << *this;
}

void Heap::destroy()
{
	clear();
	//cout << "Hip je uspesno obrisan!" << endl;
}

int Heap::find(int elem)
{
	int i;
	for (i = 0; i < size; i++) {
		if (storage[i] == elem) return i;
	}
}

void Heap::change(int elem, int zam)
{
	int index=find(elem),steps=0;
	if (zam > elem) {							//ako je zamena veca od proslog broja, propagiramo na;
		storage[index] = zam;
		int f = index;
		while (f < size) {
			int a = firstSon(f), b = lastSon(f);
			if (b > size) b = size - 1;
			if (a > size) break;
			int min = minSon(a, b,steps);
			if (storage[min] < storage[f]) {
				int temp = storage[min];
				storage[min] = storage[f];
				storage[f] = temp;
			}
			f = min;
		}
	}
	else if (zam < elem) {						//ako je zamena manja od proslog broja, propagiramo na
		int f = father(index);
		int s = index;
		while (s > 0 && storage[f] > zam) {
			int temp = storage[f];
			storage[f] = storage[s];
			storage[s] = temp;
			s = f;
			f = father(f);
		}
		storage[s] = zam;
	}
	else {
		return;
	}
}

void Heap::printRow()
{
	for (int i = 0; i < size; i++) {
		cout << storage[i]<<" ";
	}
	cout << endl;
}


ostream& operator<<(ostream& os, const Heap& h)
{
	int i, koef = 1, j = 0, flag = 0;
	for (i = 0; i < h.size; i++) {
		os << h.storage[i] << " ";
		if (i == 0 || (i == koef + j && koef != 1)) {
			koef = koef * h.m;
			j = i;
			os << endl;
			flag = 1;
		}
		if (i % h.m == 0 && !flag) {
			os << " ";
		}
		flag = 0;
		if (i == h.size - 1) os << endl;
	}
	return os;
}
	