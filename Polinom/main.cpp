#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <fstream>
#include "Polinom.h"

using namespace std;

int main() {
//	string monom = "12.5x^10y^9z^5";
	string monom = "-1.5x^-1y^2z^1";
	string polinom = "12.5x^10y^0z^5-2.6x^2y^5z^0-10";
//	string polinom = "x^1y^0z^5-3";   
//	Monom m (1.5, -1, 0, 3);
//	cout << m << endl << endl;
//
//	istringstream m_in(monom);
//	m_in >> m;
//	cout << m << endl << endl;
//
//	cout << "Calc monom: " << m.calc(2, 2, 3);
//	cout << endl << endl;

    Polinom p, p_1, p_2, p_3, p_4, p_5;
/*	istringstream p_in(polinom);
	p_in >> p;
	cout << p << endl << endl;*/

	ifstream file("Polinom_1.txt");
	file >> p_1;
	cout << "Polinom_1: " << p_1 << endl << endl;
    cout << "Polynom_1 at the point: " << p_1.calc(2, 2, 1) << endl << endl;

    ifstream file2("Polinom_2.txt");
    file2 >> p_2;
    cout << "Polinom_2: " << p_2 << endl << endl;
    cout << "Polynom_2 at the point: " << p_2.calc(2, 2, 1) << endl << endl;
    
    p_3 = p_1 + p_2;
    cout << "Polinom_3: " << p_3 << endl << endl;
    cout << "Polynom_3 at the point: " << p_3.calc(2, 2, 1) << endl << endl;
    
    p_4 = p_2 - p_1;
    cout << "Polinom_4: " << p_4 << endl << endl;
    cout << "Polynom_4 at the point: " << p_4.calc(2, 2, 1) << endl << endl;

	p_5 = p_1 * p_2;
	cout << "Polinom_5: " << p_5 << endl << endl;
	cout << "Polynom_5 at the point: " << p_5.calc(2, 2, 1) << endl << endl;

	ofstream file_3("Polinom_3.txt");
	file_3 << p_5;

	/*Polinom p1, p2, p3, p4;
	string polinom1 = "2x^1y^2z^1-3";
	istringstream p_in1(polinom1);
	p_in1 >> p1;
	string polinom2 = "2x^1y^2z^1+3";
	istringstream p_in2(polinom2);
	p_in2 >> p2;
	p3 = p1 * p2;
	cout << p1 << endl;
	cout << p2 << endl;
	cout << p3 << endl;

/*	Monom m_1(0, 1, 0, 0), m_2(3, 1, 2, 0), m_3;
	m_3 = m_1 * m_2;
	cout << "Monom 3 proizv: " << m_3 << endl;
	cout << " hggh: " << m_3 * 0;
	return 0;*/
}