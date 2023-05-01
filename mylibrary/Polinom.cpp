#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <fstream>
#include "Polinom.h"

using namespace std;

Polinom :: Polinom() {
	Link* p = new Link(0);
	p->next = p;
	first = p;
	end = p;
}

Polinom :: Polinom(const Polinom& p) {
	first = new Link(0);
	first->next = first;
	end = first;
	Link* tmp = p.first->next;
	while (tmp != p.first) {
		addLast(tmp->m);
		tmp = tmp->next;
	}
}

Polinom& Polinom :: operator=(const Polinom& p) {
	if (this != &p) {
		Link* tmp = p.first->next;
		this->clean();
		while (tmp != p.first) {
			addLast(tmp->m);
			tmp = tmp->next;
		}
	}
	return *this;
}

void Polinom :: addLast(Monom x) {
	Link* p = new Link(x, first);
	end->next = p;
	end = end->next;
}

void Polinom :: add(Monom x) {
	Link* tmp = first;
	while (tmp->next != first) {
		if (tmp->next->m.s > x.s) {
			Link* b = new Link(x, tmp->next);
			tmp->next = b;
			return;
		}
		if (tmp->next->m.s == x.s) {
			tmp->next->m.coef += x.coef;
			return;

		}
		tmp = tmp->next;
	}
	Link* c = new Link(x, first);
	tmp->next = c;
	end = c;
}

ostream& operator<<(ostream& out, Polinom& p) {
	Link* tmp = p.first->next;
	while (tmp != p.first) {
		out << tmp->m;
		tmp = tmp->next;
	}
	return out;
}

istream& operator>>(istream& in, Polinom& p) {
	p.clean();
	string str;
	in >> str;
	string t;
	str += " ";
	for (int i = 0; i < str.size(); i++) {
		if (i == 0) {
			if (str[i] == '-') {
				t = "";
			}
			t += str[i];
			continue;
		}
		if ((str[i] == ' ') || (str[i] == '+') || ((str[i] == '-') && (str[i - 1] != '^') && (i > 0))) {
			if (t.size() > 0) {
				istringstream ss(t);
				Monom m;
				ss >> m;
				//p.addLast(m);
				p.add(m);
			}
			t = "";
			if (str[i] == ' ') {
				t += " - ";
			}
		}
		t += str[i];
	}
	return in;
}

void Polinom :: clean() {
	first->next = first;
}

double Polinom :: calc(double x, double y, double z) {
	double s = 0;
	Link* tmp = first->next;
	while (tmp != first) {
		s += tmp->m.calc(x, y, z);
		tmp = tmp->next;
	}
	return s;
}

Polinom Polinom :: operator+(const Polinom& p) {
	Polinom tmp;
	Link* tmp_1 = first->next;
	Link* tmp_2 = p.first->next;
	while ((tmp_1 != first) && (tmp_2 != p.first)) {
		if (tmp_1->m.s < tmp_2->m.s) {
			tmp.addLast(tmp_1->m);
			tmp_1 = tmp_1->next;
		}
		else if (tmp_1->m.s > tmp_2->m.s) {
			tmp.addLast(tmp_2->m);
			tmp_2 = tmp_2->next;
		}
		else {
			tmp_1->m.coef += tmp_2->m.coef;
			if (tmp_1->m.coef != 0)
				tmp.addLast(tmp_1->m);
			tmp_1->m.coef -= tmp_2->m.coef;
			tmp_1 = tmp_1->next;
			tmp_2 = tmp_2->next;
		}
	}
	if (tmp_1 == first) {
		tmp.addLast(tmp_2->m);
	}
	else if (tmp_2 == p.first) {
		tmp.addLast(tmp_1->m);
	}
	return tmp;
}

Polinom Polinom :: operator-(const Polinom& p) {
	Polinom tmp;
	Link* tmp_1 = first->next;
	Link* tmp_2 = p.first->next;
	while ((tmp_1 != first) && (tmp_2 != p.first)) {
		if (tmp_1->m.s < tmp_2->m.s) {
			tmp.addLast(tmp_1->m);
			tmp_1 = tmp_1->next;
		}
		else if (tmp_1->m.s > tmp_2->m.s) {
			tmp.addLast(tmp_2->m * (-1));
			tmp_2 = tmp_2->next;
		}
		else {
			tmp_1->m.coef -= tmp_2->m.coef;
			if (tmp_1->m.coef != 0)
				tmp.addLast(tmp_1->m);
			tmp_1->m.coef += tmp_2->m.coef;
			tmp_1 = tmp_1->next;
			tmp_2 = tmp_2->next;
		}
	}
	if (tmp_1 == first) {
		tmp.addLast(tmp_2->m * (-1));
	}
	else if (tmp_2 == p.first) {
		tmp.addLast(tmp_1->m);
	}
	return tmp;
}

Polinom Polinom :: operator*(const Polinom& p) {
	Polinom tmp, tmp1;
	Monom monom;
	Link* tmp_1 = first->next;
	while (tmp_1 != first) {
		Link* tmp_2 = p.first->next;
		while (tmp_2 != p.first) {
			tmp.add(tmp_1->m * tmp_2->m);
			tmp_2 = tmp_2->next;
		}
		tmp_1 = tmp_1->next;
	}
	Link* tmp_3 = tmp.first->next;
	while (tmp_3 != tmp.first) {
		if (tmp_3->m.coef != 0) {
			monom.coef = tmp_3->m.coef;
			monom.s = tmp_3->m.s;
			tmp1.add(monom);
		}
		tmp_3 = tmp_3->next;
	}
	return tmp1;
}

int Polinom::size() {
	int i = 0;
	Link* tmp = first->next;
	while (tmp != first) {
		i++;
		tmp = tmp->next;
	}
	return i;
}

bool Polinom :: operator==(const Polinom& p) const noexcept
{
	int i = 0, j = 0;
	Link* tmp = first->next;
	Link* tmp_1 = p.first->next;
	while ((tmp != first) && (tmp_1 != p.first)) {
		if (tmp->m.s != tmp_1->m.s) {
			return false;
		}
		else {
			if (tmp->m.coef != tmp_1->m.coef) {
				return false;
			}
			else {
				tmp = tmp->next;
				tmp_1 = tmp_1->next;
			}
		}
	}
	return true;
}

bool Polinom :: operator!=(const Polinom& p) const noexcept
{
	int i = 0, j = 0;
	Link* tmp = first->next;
	Link* tmp_1 = p.first->next;
	while ((tmp != first) && (tmp_1 != p.first)) {
		if (tmp->m.s != tmp_1->m.s) {
			return true;
		}
		else {
			if (tmp->m.coef != tmp_1->m.coef) {
				return true;
			}
			else {
				tmp = tmp->next;
				tmp_1 = tmp_1->next;
			}
		}
	}
	return false;
}

Polinom :: ~Polinom() {
	while (first != end) {
		Link* tmp = first->next;
		delete first;
		first = tmp;
	}
}