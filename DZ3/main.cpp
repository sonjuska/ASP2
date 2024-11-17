#include "Heap.h"
#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include "PriorityQueue.h"

using namespace std;
using namespace std::chrono;

int main() {
	int m, i = 0, b, opcija, newM, m2, unos, zamena, elem, insert_steps = 0, delete_steps = 0, convert_steps = 0, len = 0;;
	cout << "Kako zelite da napravite hip?\n1. Iz datoteke\n2. Sa komandne linije\nUnesi 1 ili 2: ";
	cin >> unos;
	cout << "Unesi m: ";
	cin >> m;
	Heap h1(m);
	int* keys = new int[100000];
	if (unos == 1) {
		fstream dat;
		string ime_dat;
		cout << "Unesi ime datoteke: ";
		cin >> ime_dat;
		dat.open(ime_dat, ios::in);
		if (dat.is_open()) {
			cout << "Fajl otvoren!\n";
			while (1) {
				dat >> b;
				h1.add(b,insert_steps);
				keys[len++] = b;
				if(dat.eof() )break;
			}
		}
		else {
			cout << "Greska pri otvaranju fajla\n";
		}
		dat.close();
	}
	
	while (1) {
		cout << "1. Ubaci u hip\n2. Ispisi hip kao stablo\n3. Dohvati koren hipa (min)\n"
			"4. Izbrisi koren (min)\n5. Konvertuj\n6. Unisti\n7. Unija 2 hipa\n8. Promeni vrednost kljuca\n"
			"9. Prioritetni red\n\n";
		cout << "Unesi opciju: ";
		cin >> opcija;
		if (opcija == 1) {
			cout << "Unesi broj: ";
			while (i < h1.getCap()) {
				cin >> b;
				if (b == -1) break;
				h1.add(b, insert_steps);
				keys[i] = b;
				i++;
			}
			cout << h1;
		}
		else if (opcija == 2) {
			cout << h1;
		}
		else if (opcija == 3) {
			cout << "Koren, tj. najmanji element heap-a je " << h1.get()<<endl;
		}
		else if (opcija == 4) {
			int obrisan=h1.deleteKey(delete_steps);
			if (obrisan == -1) cout << "Hip je prazan!\n";
			else cout << h1;
		}
		else if (opcija == 5) {
			cout << "Unesi novo m za konvertovanje: ";
			cin >> newM;
			cout << "Konvertovan hip:" << endl;
			h1.convertTo(newM,keys,convert_steps);
			
		}
		else if (opcija == 6) {
			h1.destroy();
			cout << "Hip je uspesno obrisan!" << endl;
			cout << h1;
			break;
		}
		else if (opcija == 7) {
			i = 0;
			cout << "Unesi m: ";
			cin >> m2;
			Heap h2(m2);
			cout << "Unesi broj: ";
			while (i < h2.getCap()) {
				cin >> b;
				if (b == -1) break;
				h2.add(b,insert_steps);
				h1.add(b,insert_steps);
			}
			
			cout << h1<<endl;
			
		}
		else if (opcija == 0) {
			break;
		}
		else if (opcija == 8) {
			cout << "Zameni broj: ";
			cin >> elem;
			cout << "sa brojem: ";
			cin >> zamena;
			h1.change(elem, zamena);
			cout << "Zamenjeno! Zamenjen hip:\n";
			cout << h1;
		}
		else if (opcija == 9) {
			int op, pqInsertSteps = 0, pqDeleteSteps = 0;;
			PriorityQueue pq(h1.getCap());
			while (1) {
				cout << "1. Stvori pq\n2. Ispitaj jel pq prazan\n3. Dohvati prvi element\n4. Obrisi prvi element\n5. Umetni u red\n6. Performanse\n\nUnesi opciju: ";
				cin >> op;
				if (op == 1) {
					cout << "PQ je stvoren pri pozivanju opcije 9. Prioritetni red!\n";
				}
				else if (op == 2) {
					if (pq.isEmpty()) cout << "PQ je prazan!\n";
					else cout << "PQ nije prazan!\n";
				}
				else if (op == 3) {
					int dohvacen = pq.get();
					if (dohvacen == -1)cout << "PQ je prazan!\n";
					else cout << "Dohvacen prvi element je: " << dohvacen<<endl;
				}
				else if (op == 4) {
					int obrisan = pq.remove(pqDeleteSteps);
					if (obrisan == -1) cout << "PQ je prazan!\n";
					else cout << "Prvi element " << obrisan << " je obrisan!\n";
					//pq.printPQ();
				}
				else if (op == 5) {
					i = 0;
					while (i < h1.getCap()) {
						cin >> b;
						if (b == -1) break;
						pq.insert(b,pqInsertSteps);
						i++;
						if (pq.isFull()) { cout << "Red je pun! Umetanje zavrseno. \n"; break; }
					}
					//pq.printPQ();
					cout << endl;
				}
				else if (op==6) {
					cout << "Velicina, red\tVreme umetanja\t\tKoraci um.\tVreme br.\tKoraci br." << endl;
					int delete_steps = 0, insert_steps = 0,red,j,vel,len=0,niz[100000];
					fstream dat;
					dat.open("test100.txt", ios::in);
					if (dat.is_open()) {
						while (1) {
							dat >> niz[len++];
							if (dat.eof())break;
						}
						for (red = 2; red <= 8; red = red * 2) {
							Heap h(red);
							auto start = std::chrono::high_resolution_clock::now();
							for(b=0;b<len;b++) h.add(niz[b], insert_steps);
							auto end = std::chrono::high_resolution_clock::now();
							duration<double, std::milli> time1 = end - start;
							vel = h.getSize();
							auto s = std::chrono::high_resolution_clock::now();
							for (j = 0; j < h.getSize(); j++) {
								h.deleteKey(delete_steps);
							}
							auto e = std::chrono::high_resolution_clock::now();
							duration<double, std::milli> time2 = e - s;
							cout << vel<<", " << red << "\t\t" << time1.count() << "ms "<<"\t\t" << insert_steps << "\t\t" <<time2.count() << "ms "<<"\t" << delete_steps << endl;
							insert_steps = 0, delete_steps=0;
							h.destroy();
						}
						
					}
					dat.close();
					len = 0;
					dat.open("test1000.txt", ios::in);
					if (dat.is_open()) {
						while (1) {
							dat >> niz[len++];
							if (dat.eof())break;
						}
						for (red = 2; red <= 8; red = red * 2) {
							Heap h(red);
							auto start = std::chrono::high_resolution_clock::now();
							for (b = 0; b < len; b++) h.add(niz[b], insert_steps);
							auto end = std::chrono::high_resolution_clock::now();
							vel = h.getSize();
							duration<double, std::milli> time1 = end - start;
							auto s = std::chrono::high_resolution_clock::now();
							for (j = 0; j < h.getSize(); j++) h.deleteKey(delete_steps);
							auto e = std::chrono::high_resolution_clock::now();
							duration<double, std::milli> time2 = e - s;
							cout << vel << ", " << red << "\t\t" <<time1.count() << "ms "<<"\t\t" << insert_steps << "\t\t" <<time2.count() << "ms "<<"\t" << delete_steps << endl;
							insert_steps = 0, delete_steps = 0;
							h.destroy();
						}

					}
					dat.close();
					len = 0;
					dat.open("test10000.txt", ios::in);
					if (dat.is_open()) {
						while (1) {
							dat >> niz[len++];
							if (dat.eof())break;
						}
						for (red = 2; red <= 8; red = red * 2) {
							Heap h(red);
							auto start = std::chrono::high_resolution_clock::now();
							for (b = 0; b < len; b++) h.add(niz[b], insert_steps);
							auto end = std::chrono::high_resolution_clock::now();
							duration<double, std::milli> time1 = end - start;
							vel = h.getSize();
							auto s = std::chrono::high_resolution_clock::now();
							for (j = 0; j < h.getSize(); j++) h.deleteKey(delete_steps);
							auto e = std::chrono::high_resolution_clock::now();
							duration<double, std::milli> time2 = e - s;
		
							cout << vel << ", " << red << "\t" <<time1.count() << "ms "<<"\t\t" << insert_steps << "\t\t" <<time2.count() << "ms "<<"\t" << delete_steps << endl;
							insert_steps = 0, delete_steps = 0;
							h.destroy();
						}

					}
					dat.close();
					len = 0;
					dat.open("test100000.txt", ios::in);
					if (dat.is_open()) {
						while (1) {
							dat >> niz[len++];
							if (dat.eof())break;
						}
						for (red = 2; red <= 8; red = red * 2) {
							Heap h(red);
							auto start = std::chrono::high_resolution_clock::now();
							for (b = 0; b < len; b++) h.add(niz[b], insert_steps);
							auto end = std::chrono::high_resolution_clock::now();
							duration<double, std::milli> time1 = end - start;
							vel = h.getSize();
							auto s = std::chrono::high_resolution_clock::now();
							for (j = 0; j < h.getSize(); j++) h.deleteKey(delete_steps);
							auto e = std::chrono::high_resolution_clock::now();
							duration<double, std::milli> time2 = e - s;
							
							cout << vel << ", " << red << "\t" <<time1.count() << "ms "<<"\t\t" << insert_steps << "\t\t" << time2.count() << "ms "<<"\t" << delete_steps << endl;
							insert_steps = 0, delete_steps = 0;
							h.destroy();
						}

					}
					dat.close();
				}
				else if (op == 0) {
					break;
				}
			}
		}
		
	}
	delete[] keys;

	return 0;
}