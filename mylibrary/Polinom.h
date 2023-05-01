#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <fstream>

using namespace std;

const int a = 10;
const int p = 21;

struct Monom {
	double coef;// коэффициент
	int s; // свёртка
	Monom(double coef = 1.0, int x = 0, int y = 0, int z = 0) {
		this->coef = coef;
		x += a, y += a, z += a;
		s = x + y * p + z * p * p;
	}

	int getX() {
		if ((s % p) != 0)
			return s % p - a; // остаток от деления
		else return s % p;
	}

	int getY() {
		if (((s / p) % p) != 0)
			return (s / p) % p - a;
		else return (s / p) % p;
	}

	int getZ() {
		if (((s / p / p) % p) != 0)
			return (s / p / p) % p - a;
		else return (s / p / p) % p;
	}

	friend istream& operator>>(istream& in, Monom& m) {
		string str;
		in >> str;
		m.coef = 1.0;
		m.s = 0;
		int st = 0; // состояние = 0, разбираем коэф-ты
		int p_st = 0;
		bool ch = false;
		string t = "";
		for (int i = 0; i < str.size(); i++) {
			if (str[i] == '^') {
				t = "";
				continue;
			}
			if (str[i] == 'x') {
				ch = true;
				p_st = st;
				st = 1;
			}
			if (str[i] == 'y') {
				ch = true;
				p_st = st;
				st = 2;
			}
			if (str[i] == 'z') {
				ch = true;
				p_st = st;
				st = 3;
			}
			if (!ch) {
				t += str[i];
			}
			else {
				if (p_st == 0) { // накапливали коэф-т
					if (t.size() > 0) {
						m.coef = stof(t);
					}
				}
				if (p_st > 0) {
					int pp = pow(p, p_st - 1);
					m.s += (stoi(t) + a) * pp;
					i++;
				}
				t = "";
				ch = false;
			}
		}
		if (t.size() > 0) {
			if (st == 0) {
				m.coef = stof(t);
			}
			if (st > 0) {
				int pp = pow(p, p_st - 1);
				m.s += (stoi(t) + a) * pp * pp;
			}
		}
		return in;
	}

	friend ostream& operator<<(ostream& out, Monom& m) {
		int t;
		if (m.coef != 0) {
			if (m.coef > 0.0) out << "+";
			out << m.coef;
			t = m.getX(); if (t != 0) out << "x^" << m.getX(); //if (t > 0) out << "x^" << m.getX();
			t = m.getY(); if (t != 0) out << "y^" << m.getY(); //if (t > 0) out << "y^" << m.getY();
			t = m.getZ(); if (t != 0) out << "z^" << m.getZ(); //if (t > 0) out << "z^" << m.getZ();
			return out;
		}
	}

	double calc(double x, double y, double z) {
		double s = coef;
		s *= pow(x, getX());
		s *= pow(y, getY());
		s *= pow(z, getZ());
		return s;
	}

	Monom operator*(double x) {
		Monom tmp;
		tmp.coef = coef * x;
		tmp.s = s;
		if (tmp.coef != 0)
			return tmp;
		else
			return 0;
	}

	Monom operator*(const Monom& m) {
		Monom tmp;
		tmp.coef = coef * m.coef;
		if ((s != 0) && (m.s != 0)) {
			tmp.s = s + m.s - (a + a * p + a * p * p);
		}
		else {
			tmp.s = s + m.s;
		}
		if (tmp.coef != 0)
			return tmp;
		else
			return 0;
	}

	bool operator==(const Monom& m) const noexcept
	{
		if (s != m.s)
			return false;
		if (coef != m.coef)
			return false;
		return true;
	}

	bool operator!=(const Monom& m) const noexcept
	{
		if (s != m.s)
			return true;
		if (coef != m.coef)
			return true;
		return false;
	}
};

struct Link {
	Monom m;
	Link* next;
	Link(Monom _m, Link* _n = nullptr) :m(_m), next(_n) {}
};

class Polinom {
	Link* first;
	Link* end;
public:
	Polinom();
	Polinom(const Polinom& p);
	Polinom& operator=(const Polinom& p);
	void addLast(Monom x);
	void add(Monom x);
	friend ostream& operator<<(ostream& out, Polinom& p);
	friend istream& operator>>(istream& in, Polinom& p);
	void clean();
	double calc(double x, double y, double z);
	Polinom operator+(const Polinom& p);
	Polinom operator-(const Polinom& p);
	Polinom operator*(const Polinom& p);
	bool operator==(const Polinom& p) const noexcept;
	bool operator!=(const Polinom& p) const noexcept;
	int size();
	~Polinom();
};
