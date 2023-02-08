#include<iostream>
#include<fstream>
#include <string>
#include<list>
#include<set>
#include<vector>
#include<map>
using namespace std;

//Aplicatie pentru gestiunea unui atelier de reparatii produse electrocasnice pentru care se inregistreaza aparatele electrocasnice primite,
//care au asociate liste cu interventii si costurile acestora.Aplicatia trebuie sa permita adaugarea unui obiect electrocasnic 
//in atelier si stabilirea listei de interventii, determinarea costului reparatiei pentru un obiect cat si pentru toate obiectele din atelier.


enum TipInterventie {electrica=0, tehnica=1, deSistem=5};

class Produs
{
private:
	const int serie;
	char* producator;
	string denumire;
	int pret;
	float dimensiune;
	
public:
	Produs() :serie(0)
	{
		pret = 0;
		dimensiune = 0;
		producator = new char[strlen("Anonim") + 1];
		strcpy(producator, "Anonim");
		denumire = "";
	}
	Produs(int serie, const char* producator, string denumire, int pret, float dimensiune) :serie(serie)
	{
		this->producator = new char[strlen(producator) + 1];
		strcpy(this->producator, producator);
		this->denumire = denumire;
		pret = pret;
		this->dimensiune = dimensiune;
	}

	Produs(const char* producator, string denumire, int pret):serie(0)
	{
		this->producator = new char[strlen(producator) + 1];
		strcpy(this->producator, producator);
		this->denumire = denumire;
		pret = pret;
	}
	
	char* getProducator()
	{
		if (producator != NULL)
		{
			char* copie = new char[strlen(producator) + 1];
			strcpy(copie, producator);
			return copie;
		}
		else {
			return NULL;
		}
	}

	void setProducator(const char* producator)
	{
		if (producator != NULL)
		{
			if (this->producator != NULL)
			{
				delete[] this->producator;
			}
			this->producator = new char[strlen(producator) + 1];
			strcpy(this->producator, producator);
		}
	}
	const int getSerie()
	{
		return serie;
	}


	string getDenumire()
	{
			return denumire;
	}
	void setDenumire(string denumire)
	{
		if (denumire.length() > 0)
		{
			this->denumire = denumire;
		}
	}
	int getPret()
	{
		return pret;
	}
	void setPret(int pret)
	{
		if (pret > 0)
		{
			this->pret = pret;
		}
	}
	float getDimensiune()
	{
		return dimensiune;
	}
	void setDimensiune(float dimensiune)
	{
		if (dimensiune > 0)
		{
			this->dimensiune = dimensiune;
		}
	}

	Produs(const Produs& p) :serie(p.serie)
	{
		if (p.producator != NULL)
		{
			this->producator = new char[strlen(p.producator) + 1];
			strcpy(this->producator, p.producator);
		}
		else {
			this->producator = nullptr;
		}
		this->pret = p.pret;
		this->dimensiune = p.dimensiune;
		this->denumire = p.denumire;
	}

	Produs& operator=(const Produs& p)
	{
		if (this != &p)
		{
			if (producator != NULL)
			{
				delete[]producator;
				producator = NULL;
			}
			if (producator != NULL)
			{
				this->producator = new char[strlen(p.producator) + 1];
				strcpy(this->producator, producator);
			}
			else {
				this->producator = nullptr;
			}
			this->pret = p.pret;
			this->dimensiune = p.dimensiune;
			this->denumire = p.denumire;
		}
		return *this;
	}
	~Produs()
	{
		if (producator != NULL)
		{
			delete[]producator;
			producator = NULL;
		}
	}

	Produs operator++() 
	{
		this->dimensiune++;
		return *this;

	}
	Produs operator++(int) 
	{
		Produs aux = *this;
		this->dimensiune++;
		return aux;
	}

	Produs operator--()
	{
		this->pret--;
		return *this;

	}
	Produs operator--(int)
	{
		Produs aux = *this;
		this->pret--;
		return aux;
	}

	bool operator!=(Produs p)
	{
		if (strcmp(this->producator, p.producator) == 0)
		{
			return false; 
		}
		else
		{
			return true;
		}
	}

	bool operator<(Produs  p)
	{
		if (this->pret > p.pret)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool operator>=(Produs  p)
	{
		if (this->dimensiune > p.dimensiune)
		{
			return true;
		}
		else
		{
			return false;
		}
	}


	void scrieInFisiserBinar(fstream& fisier)
	{
		int lungime = strlen(this->producator);
		fisier.write((char*)&lungime, sizeof(int));
		for (int i = 0; i < lungime; i++)
		{
			fisier.write((char*)&this->producator[i], sizeof(char));
		}
		fisier.write((char*)&this->serie, sizeof(int));
		fisier.write((char*)&this->denumire, sizeof(int));
		fisier.write((char*)&this->dimensiune, sizeof(int));
		fisier.write((char*)&this->pret, sizeof(int));
	}
	void citesteDinFisiserBinar(fstream& fisier) 
	{
		int lungime = 0;
		fisier.read((char*)&lungime, sizeof(int));
		if (this->producator != NULL)
		{
			delete[]this->producator;
		}
		this->producator = new char[lungime + 1];
		for (int i = 0; i < lungime; i++)
		{
			fisier.read((char*)&this->producator[i], sizeof(char));
		}
		this->producator[lungime] = '\0';
		fisier.read((char*)&this->serie, sizeof(int));
		fisier.read((char*)&this->denumire, sizeof(int));
		fisier.read((char*)&this->dimensiune, sizeof(int));
		fisier.read((char*)&this->pret, sizeof(int));
	}

	friend ostream& operator<<(ostream& out, Produs p);
	friend istream& operator>>(istream& in, Produs& p);
	friend ofstream& operator<<(ofstream& f, Produs p);
	friend ifstream& operator>>(ifstream& f, Produs& b);
};

ofstream& operator<<(ofstream& f, Produs p)
{
	if (f.is_open())
	{
		f << " " << p.serie << endl;
		f << p.denumire << endl;
		f << p.dimensiune << endl;
		f << p.producator << endl;
		f << p.pret << endl;
	}
	return f;
}

ifstream& operator>>(ifstream& f, Produs& p)
{
	if (f.is_open())
	{
		f >> ws;
		getline(f, p.denumire);
		f >> p.dimensiune;
		f >> p.producator;
		f >> p.pret;
		
	}
	return f;
}



ostream& operator<<(ostream& out, Produs p)
{
	out << endl<< "Serie " << p.serie << endl;
	out << "Denumire " << p.denumire << endl;
	out << "Pret " << p.pret << endl;
	out << "Producator: " << p.producator << endl;
	out << "Dimensiune " << p.dimensiune << endl;
	return out;
}
istream& operator>>(istream& in, Produs& p)
{
	cout << "Denumire: ";
	in >> p.denumire;
	cout << "Pret: ";
	in >> p.pret;
	cout << "Dimensine: ";
	in >> p.dimensiune;
	cout << "Producator: ";
	char aux[30];
	in >> aux;
	if (p.producator != NULL)
	{
		delete[] p.producator;
	}
	p.producator = new char[strlen(aux) + 1];
	strcpy(p.producator, aux);
	return in;
}




class ProdusElectroCasnic: Produs
{
private:
	int* interventii=nullptr;
	int nrInterventii;
	TipInterventie tipInterventie;
	static string taraProductie;
	int anProductie;
public:
	
	ProdusElectroCasnic():Produs()
	{
		tipInterventie = electrica;
		this->nrInterventii = 1;
		this->interventii = new int[nrInterventii];
		this->interventii[0] = 7;
		anProductie = 2006;

	}


	ProdusElectroCasnic(TipInterventie tip, const char* producator, int* interventii, int nrInterventii, string denumire, int pret, int an):Produs(producator,denumire,pret)
	{
		this->tipInterventie = tip;
		this->anProductie = an;
		if (interventii != nullptr && nrInterventii > 0) {
			this->interventii = new int[nrInterventii];
			for (int i = 0; i < nrInterventii; i++)
			{
				this->interventii[i] = interventii[i];
			}
			this->nrInterventii = nrInterventii;
		}
	}

	ProdusElectroCasnic(int* interventii, int nrInterventii, const char* producator, string denumire, int pret) :Produs(producator, denumire, pret)
	{
		if (interventii != nullptr && nrInterventii > 0) {
			this->interventii = new int[nrInterventii];
			for (int i = 0; i < nrInterventii; i++)
			{
				this->interventii[i] = interventii[i];
			}
			this->nrInterventii = nrInterventii;
		}
	}
	ProdusElectroCasnic(const ProdusElectroCasnic& pe):Produs(pe)
	{
		this->anProductie = pe.anProductie;
		this->tipInterventie = pe.tipInterventie;
		if (pe.interventii != nullptr && pe.nrInterventii > 0) {
			this->interventii = new int[pe.nrInterventii];
			for (int i = 0; i < pe.nrInterventii; i++)
			{
				this->interventii[i] = pe.interventii[i];
			}
			this->nrInterventii = pe.nrInterventii;
		}
	}
	~ProdusElectroCasnic()
	{
		if (interventii != NULL)
		{
			delete[] interventii;
		}
		interventii = NULL;
	}

	ProdusElectroCasnic operator=(const ProdusElectroCasnic& pe)
	{
		if (this != &pe)
		{
			Produs::operator=(pe);
			if (interventii != NULL)
			{
				delete[] interventii;
				interventii = nullptr;
			}
			this->anProductie = pe.anProductie;
			this->tipInterventie = pe.tipInterventie;
			if (pe.interventii != nullptr && pe.nrInterventii > 0) {
				this->interventii = new int[pe.nrInterventii];
				for (int i = 0; i < pe.nrInterventii; i++)
				{
					this->interventii[i] = pe.interventii[i];
				}
				this->nrInterventii = pe.nrInterventii;
			}
		}
		return *this;
	}



	TipInterventie getTipInterventie()
	{
		return tipInterventie;
	}
	void setTipInterventie(TipInterventie tip)
	{
		if (tipInterventie != 0)
		{
			tipInterventie = tip;
		}
	}

	int getNrInterventii()
	{
		return nrInterventii;
	}
	void setNrInterventii(int nrInterventii)
	{
		if (nrInterventii > 0)
		{
			this->nrInterventii = nrInterventii;
		}
	}

	static string getTaraProductie() {
		return taraProductie;
	}

	static void setTaraProductie(string taraProductie)
	{
		if (taraProductie.length() > 0)
		{
			ProdusElectroCasnic::taraProductie = taraProductie;
		}
	}
	int* getInterventii() {
		if (nrInterventii > 0 && interventii != NULL)
		{
			int* copie = new int[nrInterventii];
			for (int i = 0; i < nrInterventii; i++) {
				copie[i] = interventii[i];
			}
			return copie;
		}
		else {
			return NULL;
		}
	}
	void setInterventii(int* interventii, int nrInterventii) {
		if (interventii != NULL && nrInterventii > 0) {
			if (this->interventii != NULL) {
				delete[] this->interventii;
			}
			this->interventii = new int[nrInterventii];
			this->nrInterventii = nrInterventii;
			for (int i = 0; i < nrInterventii; i++)
				this->interventii[i] = interventii[i];
		}
	}
	int getAnProductie()
	{
		return anProductie;
	}
	void setAnProductire(int anProductie)
	{
		if (anProductie > 0)
		{
			this->anProductie = anProductie;
		}
	}

	int& operator[](int index)
	{
		if (index >= 0 && index < nrInterventii && interventii != nullptr)
		{
			return interventii[index];
		}
		else
		{
			throw exception("Invalid");
		}
	}

	operator float() 
	{
		return 2023 - anProductie;
	}
	ProdusElectroCasnic operator++()
	{
		this->anProductie++;
		return *this;
	}


	ProdusElectroCasnic operator+(ProdusElectroCasnic p)
	{
		ProdusElectroCasnic rezultat = *this;
		rezultat.anProductie = this->anProductie + p.anProductie;
		return rezultat;
	}

	int calculareCost()
	{
		int suma = 50;
		if (tipInterventie == electrica)
		{
			suma += 30;
		}
		else if (tipInterventie == deSistem)
		{
			suma += 20;
		}
		else {
			suma += 40;
		}
		return suma;
	}


	friend ostream& operator<<(ostream& out, ProdusElectroCasnic pe);
	friend istream& operator>>(istream& in, ProdusElectroCasnic& pe);
};
string ProdusElectroCasnic::taraProductie = "Romania";
ostream& operator<<(ostream& out, ProdusElectroCasnic pe)
{
	out << (Produs&)pe;
	out << endl << "Tip Interventie: " << pe.tipInterventie;
	out << endl << "An productie " << pe.anProductie;
	out << endl << "Nr interventii: " << pe.nrInterventii;
	out <<endl<< "Interventii: ";
	if (pe.nrInterventii == 0)
	{
		out << "NU exista interventii!";
	}
	else {
		for (int i = 0; i < pe.nrInterventii; i++)
		{
			out << pe.interventii[i] << " ";
		}
	}
	
	out << endl;
	return out;
}
istream& operator>>(istream& in, ProdusElectroCasnic& pe)
{
	in >> (Produs&)pe;
	cout << "Tip Interventie: ";
	cout << "An productie:";
	in >> pe.anProductie;
	int tip;
	in >> tip;
	switch (tip)
	{
	case 1: pe.tipInterventie = electrica; break;
	case 2: pe.tipInterventie = tehnica; break;
	case 3: pe.tipInterventie = deSistem; break;
	default:
		pe.tipInterventie = tehnica; break;
	}
	int nr;
	cout << "nr Interventii: ";
	in >> nr;
	int* vector = new int[nr];
	for (int i = 0; i < nr; i++)
	{
		cout << "interventia[" << i << "]: ";
		in >> vector[i];
	}
	pe.setInterventii(vector, nr);
	delete[]vector;
	vector = nullptr;
	return in;
}
class Atelier
{
private:
	ProdusElectroCasnic* produse;
	int nrProduse;
	string numeAtelier;
public:
	Atelier()
	{
		nrProduse = 2;
		numeAtelier = "Necunoscut";
		produse = new ProdusElectroCasnic[2];
		produse[0].setTipInterventie(electrica);
		produse[1].setTipInterventie(deSistem);
	}
	Atelier(ProdusElectroCasnic* produse, int nrProduse, string numeAtelier)
	{
		this->numeAtelier = numeAtelier;
		if (nrProduse > 0 && produse != NULL)
		{
			produse = new ProdusElectroCasnic[nrProduse];
			for (int i = 0; i < nrProduse; i++)
			{
				this->produse[i] = produse[i];
			}
			this->nrProduse = nrProduse;
		}
	}
	Atelier(string numeAtelier)
	{
		this->numeAtelier = numeAtelier;
		nrProduse = 2;
		produse = new ProdusElectroCasnic[2];
		produse[0].setTipInterventie(electrica);
		produse[1].setTipInterventie(deSistem);

	}

	Atelier(const Atelier& a)
	{
		numeAtelier = a.numeAtelier;
		if (a.nrProduse > 0 && a.produse != NULL)
		{
			produse = new ProdusElectroCasnic[a.nrProduse];
			for (int i = 0; i < nrProduse; i++)
			{
				produse[i] = a.produse[i];
			}
			nrProduse = a.nrProduse;
		}
		
	}
	Atelier operator=(const Atelier& a)
	{
		if (this != &a)
		{
			if (produse != NULL)
			{
				delete[]produse;
			}
			numeAtelier = a.numeAtelier;
			if (a.nrProduse > 0 && a.produse != NULL)
			{
				produse = new ProdusElectroCasnic[a.nrProduse];
				for (int i = 0; i < nrProduse; i++)
				{
					produse[i] = a.produse[i];
				}
				nrProduse = a.nrProduse;
			}
		}
		return *this;
	}
	~Atelier()
	{
		if (produse != NULL)
		{
			delete[]produse;
		}
		produse = NULL;
	}

	int getnrProduse()
	{
		return nrProduse;
	}
	void setNrProduse(int nrProduse)
	{
		if (nrProduse > 0)
		{
			this->nrProduse = nrProduse;
		}
	}

	string getNumeAtelier()
	{
		return numeAtelier;
	}
	void setNumeAtelier()
	{
		if (numeAtelier.length() > 0)
		{
			this->numeAtelier = numeAtelier;
		}
	}

	bool operator!=(Atelier a)
	{
		if (this->nrProduse!=a.nrProduse)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	bool operator>=(Atelier a)
	{
		if (this->nrProduse >= a.nrProduse)
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	Atelier operator+=(ProdusElectroCasnic p) {
		this->nrProduse++;
		ProdusElectroCasnic* aux = new ProdusElectroCasnic[nrProduse];
		if (this->produse != NULL) {
			for (int i = 0; i < nrProduse - 1; i++) {
				aux[i] = this->produse[i];
			}
			delete[]produse;
		}
		aux[nrProduse - 1] = p;
		produse = aux;
		return *this;
	}

	bool operator<(Atelier a)
	{
		if ((this->numeAtelier).length() < (a.numeAtelier).length())
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	int calculeaza()
	{
		int suma = 0;
		for (int i = 0; i < nrProduse; i++)
		{
			suma += produse[i].calculareCost();
		}
		return suma;
	}

	ProdusElectroCasnic& operator[](int index)
	{
		if (index >= 0 && index < this->nrProduse)
		{
			return produse[index];
		}
		else
		{
			throw exception("Index in afara intervalului!");
		}
	}


	friend ostream& operator<<(ostream& out, Atelier a);
	friend istream& operator>>(istream& in, Atelier& a);
};
ostream& operator<<(ostream& out, Atelier a)
{
	out <<endl<< "Nume atelier: " << a.numeAtelier;
	out << endl << "nr Produse: " << a.nrProduse;
	cout << endl;
	for (int i = 0; i < a.nrProduse; i++)
	{
		out << "Interventia [ " << i << " ]";
		out << a.produse[i] << endl;
	}
	return out;
}


istream& operator>>(istream& in, Atelier& a)
{
	cout << "Nume atelier: ";
	in >> a.numeAtelier;
	int aux;
	cout << "Introduceti numarul de vacante: ";
	in >> aux;

	if (aux > 0)
	{
		if (a.produse)
		{
			delete[]a.produse;
		}

		a.nrProduse = aux;
		a.produse = new ProdusElectroCasnic[aux];

		for (int i = 0; i < aux; i++)
		{
			in >> a.produse[i];
		}
	}

	return in;
}

class TurnOnOFF
{
public:
	virtual void turnOn() = 0;
	virtual void turnOff() = 0;
};
class Programare:TurnOnOFF
{
private: 
	string programLucru;
	string numeClient;
	bool programare=true;
public:

	Programare()
	{
		programLucru = "10:00-17:00";
		numeClient = "Andrei";
		
	}
	void turnOn() override
	{
		cout <<endl<< "Atelierul este deschis!";
	}
	void turnOff() override
	{
		cout <<endl<< "Atelierul este inchis!";
	}
	virtual void getProgram()
	{
		cout << "Programul de lucru al atelierului este intre orele " << programLucru;
	}
	virtual void afisare()
	{
		if (programare != true)
		{
			cout << "Clientul " << numeClient << " nu are programare.";
		}
		else {
			cout << "Clientul " << numeClient << " are programare.";
		}
	}

};



void main()
{
	Produs p1;
	cout << p1.getProducator() << endl;
	cout << p1;
	cout << endl;
	Produs p2(2, "AAA", "Mixer", 120, 23);
	cout << p2;
	p2.setProducator("ss");
	cout << p2.getProducator();
	cout << endl;
	cout << p2;
	//cin >> p1;
	cout << endl;
	cout << p1.getDenumire() << endl;
	cout << p1.getPret() << endl;
	cout << p1.getDenumire() << endl;
	Produs p3(p2);
	cout << p3;
	Produs p4 = p1;
	cout << endl;
	cout << p4;
	cout << endl;


	Produs p5;
	p5++;
	++p5;
	cout << p5;
	p5--;
	--p5;
	cout << p5;

	if (p1 != p2)
	{
		cout << endl << "Nu au acelasi producator";
	}
	else
	{
		cout << endl << "Au au acelasi producator";
	}

	if (p1 < p5)
	{
		cout << endl << "Pretul p5 este mai mic decat p1";

	}
	else
	{
		cout << endl << "Pretul p5 este mai mare decat p1";
	}


	if (p1 >= p5)
	{
		cout << endl << "Dimensiunea p5 este mai mare decat p1";
	}
	else
	{
		cout << endl << "Dimensiunea p5 este mai mica decat p1";
	}
	cout << endl;
	cout << endl;
	cout << endl;
	ProdusElectroCasnic pe1;
	cout << pe1;
	cout << pe1.getInterventii();
	int interv[3] = { 3,5,7 };
	ProdusElectroCasnic pe2(interv, 3, "Producator", "Denumire", 200);
	cout << endl << pe2;
	

	cout<<pe2[2];
	ProdusElectroCasnic pe3;
	++pe3;
	cout << pe3;
	cout << "Numarul de ani ai produsului este: " << float(pe1);


	cout << endl;
	cout << endl;
	cout << endl;
	Atelier a1;
	cout << a1;
	cout <<endl;
	Atelier a2("Atelier a2");


	ofstream g("fisier.txt");
	g << p1;
	g.close();

	Produs p10;
	ifstream h;
	h.open("fisier.txt");
	h >> p10;
	h.close();


	fstream outBin("fisier.dat", ios::out | ios::binary);
	p2.scrieInFisiserBinar(outBin);
	outBin.close();
	cout << "S-a reusit scrierea!";

	/*fstream inBin("fisier.dat", ios::in | ios::binary);
	Produs p11;
	p11.citesteDinFisiserBinar(inBin);
	cout << p11;
	inBin.close();*/
	

	Programare pr1;
	cout << endl;
	pr1.afisare();
	pr1.turnOff();
	pr1.turnOn();
	cout << endl;
	pr1.getProgram();

	cout << endl;
	cout << "Suma interventiei pentru produsul pe1 este: ";
	cout<<pe1.calculareCost();
	cout << endl;
	cout << "Suma produselor pentru atelierul a1 este: " << a1.calculeaza();

	Produs prod1;
	Produs prod2;
	Produs prod3;
	Produs prod4;
	cout << "VECTOR" << endl;
	vector<Produs> vectorProdusSTL;
	vectorProdusSTL.push_back(prod1);
	vectorProdusSTL.push_back(prod2);
	vectorProdusSTL.push_back(prod3);
	vectorProdusSTL.push_back(prod4);
	for (int i = 0; i < vectorProdusSTL.size(); i++) {
		cout << vectorProdusSTL[i] << endl;
	}
	cout << endl << endl;

	cout << "LIST";
	list<Produs> listProdusSTL;
	listProdusSTL.push_back(prod1);
	listProdusSTL.push_back(prod2);
	listProdusSTL.push_back(prod3);
	listProdusSTL.push_back(prod4);

	list<Produs>::iterator lit;
	for (lit = listProdusSTL.begin(); lit != listProdusSTL.end(); lit++) {
		cout << *lit << endl;
	}

}
