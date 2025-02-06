// ConsoleApplication2.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <string>
#include <Windows.h> // para controlar la ventana
#include <conio.h> 
#include <stdlib.h>



using namespace std;
#define Up 72
#define Low 80	
#define L 75
#define R 77
#define E 101
#define Q 113

bool gameOver = false;
char tecla;
int tiempo = 0;
int kills = 0;
int plantadas = 0;
int soles = 500;
int plantar = 0;
int opcion_planta = 0;
int numero_planta = 0;
int nivel = 1;
int numero_guisantes = 0;
bool cerebro = false;

void color(int x) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, x);
}
void gotoxy(int x, int y) { //POSICION DEL MOUSE

	HANDLE hCon; // objeto de tipo ventana(la ventana de conbsola la negra), indentificador de nuestra ventana 
	hCon = GetStdHandle(STD_OUTPUT_HANDLE); // Tomar el control de la salida de consola (al objeto de handle le estas dando el control de la salida de la consola)
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(hCon, pos); //permite dar una posicion al curso en la ventana de consola
}
void cursor(bool x) { //FUNCOIN DEL CURSOR
	HANDLE hCon; // objeto de tipo ventana(la ventana de conbsola la negra), indentificador de nuestra ventana 
	hCon = GetStdHandle(STD_OUTPUT_HANDLE); // Tomar el control de la salida de consola (al objeto de handle le estas dando el control de la salida de la consola)

	CONSOLE_CURSOR_INFO cci; //objeto de tipo cursor con la informacion
	cci.dwSize = 1; //tamaño del cursor
	cci.bVisible = x; //el que se vea o no el cursor (true o false) x es bool por eso

	SetConsoleCursorInfo(hCon, &cci); //Metodo para modificar el cursor
}

//******Plantas********//
class Plantas {
private:
	int vida, costo, x, y, tipo;
public:
	Plantas(int _v, int _c, int _x, int _y, int _t);
	~Plantas();
	void setX(int _x);
	void setY(int _y);
	int getX();
	int getY();
	void setvida(int _vida);
	void setcosto(int _costo);
	int getvida();
	int getcosto();
	void desprint();
	virtual void print();
	virtual void printPlanta(int x, int y);
	void setTipo(int _t);
	int getTipo();
};
Plantas::Plantas(int _v, int _c, int _x, int _y, int _t) {
	vida = _v;
	costo = _c;
	x = _x;
	y = _y;
	tipo = _t;
}
Plantas::~Plantas() {
}
void Plantas::setX(int _x) {

	x = _x;

}
void Plantas::setY(int _y) {
	y = _y;
}
void Plantas::setvida(int _vida) {
	vida = _vida;
}
int Plantas::getX() {
	return x;
}
int Plantas::getY() {
	return y;
}
void Plantas::setcosto(int _costo) {
	costo = _costo;
}
int Plantas::getvida() {
	return vida;
}
int Plantas::getcosto() {
	return costo;
}
void Plantas::desprint() {
	gotoxy(x, y); cout << endl;
	gotoxy(x, y + 1); cout << "                   ";
	gotoxy(x, y + 2); cout << "                   ";
	gotoxy(x, y + 3); cout << "                   ";
	gotoxy(x, y + 4); cout << "                   ";
	gotoxy(x, y + 5); cout << "                   ";
	gotoxy(x, y + 6); cout << "                   ";
	gotoxy(x, y + 7); cout << "                   ";
	gotoxy(x, y + 8); cout << "                   ";

	Plantas::~Plantas();
}
void Plantas::printPlanta(int x, int y) {
	cout << endl;
}
void Plantas::print() {
	cout << "vida: " << vida << endl;
	cout << "coste: " << costo << " soles" << endl;
}
void Plantas::setTipo(int _t) {
	tipo = _t;
}
int Plantas::getTipo() {
	return tipo;
}

//LANZAGUISANTES
class Lanzaguisantes :public Plantas {
private:
	int damage;

public:
	Lanzaguisantes(int _v, int _c, int _d, int _x, int _y, int _t);
	void setdamage(int _damage);
	int getdamage();
	void printPlanta(int x, int y);
};
Lanzaguisantes::Lanzaguisantes(int _v, int _c, int _d, int _x, int _y, int _t) :Plantas(_v, _c, _x, _y, _t) {
	damage = _d;
}
void Lanzaguisantes::setdamage(int _damage) {
	damage = _damage;
}
int Lanzaguisantes::getdamage() {
	return damage;
}
void Lanzaguisantes::printPlanta(int x, int y) {
	gotoxy(x, y); cout << endl;
	gotoxy(x, y + 1); color(10); cout << "      ▄▄▄▄▄        " << endl;
	gotoxy(x, y + 2); color(2); cout << " ▀█■"; color(10); cout << "███████▀█▄ ▄▄  " << endl;
	gotoxy(x, y + 3); cout << "    ████▄██████▌ █ " << endl;
	gotoxy(x, y + 4); cout << "    ▀████████▀ ▀▀  " << endl;
	gotoxy(x, y + 5); color(2); cout << "        ▀█▀        " << endl;
	gotoxy(x, y + 6); cout << "         █         " << endl;
	gotoxy(x, y + 7); cout << "      ▀▀▄▄█▄▄▀▀    " << endl;
	gotoxy(x, y + 8); cout << "     ▄▄▀▀▀ ▀▀▀▄▄   " << endl; color(7);
}


//GIRASOL
class Girasol :public Plantas {
private:
	int sunratio;//cada cuanto lanza un sol
public:
	Girasol(int _v, int _c, int _s, int _x, int _y, int _t);
	void setsunratio(int _sunratio);
	int getsunratio();
	void print();
	void soltarsoles();
	void printPlanta(int x, int y);
};
Girasol::Girasol(int _v, int _c, int _s, int _x, int _y, int _t) :Plantas(_v, _c, _x, _y, _t) {
	sunratio = _s;
}
void Girasol::setsunratio(int _sunratio) {
	sunratio = _sunratio;
}
int Girasol::getsunratio() {
	return sunratio;
}
void Girasol::print() {
	Plantas::print();
	cout << "Sun ratio: " << sunratio << endl;
}
void Girasol::printPlanta(int x, int y) {
	gotoxy(x, y); cout << endl;
	gotoxy(x, y + 1); color(6); cout << "    ▄▀"; color(12); cout << "▄"; color(6); cout << "▀"; color(12); cout << "▄█▄"; color(6); cout << "▀"; color(12); cout << "▄"; color(6); cout << "▀"; color(12); cout << "▄    " << endl;
	gotoxy(x, y + 2); color(6); cout << "  ▄▀"; color(12); cout << "▄██▄███▄███"; color(6); cout << "▀▄  " << endl;
	gotoxy(x, y + 3); color(6); cout << " ■"; color(12); cout << "████▀█████▀████"; color(6); cout << "■ " << endl;
	gotoxy(x, y + 4); color(6); cout << "  ▀▄"; color(12); cout << "███▄▄▄▄▄██▀"; color(6); cout << "▄▀  " << endl;
	gotoxy(x, y + 5); cout << "    ▀▀▄"; color(12); cout << "▀▀"; color(6); cout << "█"; color(12); cout << "▀▀"; color(6); cout << "▄▀▀   " << endl; color(10);
	gotoxy(x, y + 6); cout << "         █         " << endl;
	gotoxy(x, y + 7); cout << "     ▄▀█▄█▄█▀▄     " << endl;
	gotoxy(x, y + 8); cout << "      ▀▄███▄▀      " << endl; color(7);
}
void Girasol::soltarsoles() {
}
//Funcvion de crear plantas

void plantarPlanta(int x, int y, Plantas* plantitas[46]) {
	plantar = 0;
	if (opcion_planta == 1 && soles > 99) {
		if (plantitas[0]->getvida() == 0) { plantitas[0]->~Plantas(); }
		plantitas[numero_planta] = new Lanzaguisantes(6, 100, 1, 0, 0, 1);
		plantitas[numero_planta]->setX(x - 7);
		plantitas[numero_planta]->setY(y - 3);
		plantitas[numero_planta]->setcosto(100);
		soles -= plantitas[numero_planta]->getcosto();
		numero_planta++;
		opcion_planta = 0;
		plantar = 0;
		numero_guisantes++;
	}
	if (opcion_planta == 2 && soles > 49) {
		if (plantitas[0]->getvida() == 0) { plantitas[0]->~Plantas(); }
		plantitas[numero_planta] = new Girasol(6, 50, 26, 0, 0, 2);
		plantitas[numero_planta]->setX(x - 7);
		plantitas[numero_planta]->setY(y - 3);
		plantitas[numero_planta]->setcosto(50);
		soles -= plantitas[numero_planta]->getcosto();
		numero_planta++;
		opcion_planta = 0;
		plantar = 0;
	}

}

//disparo
class Disparo {
private:
	int x;
	int y;
public:
	Disparo();
	~Disparo();
	// imprimir Disparo
	void pDisparo(int xc, int yc);
	void setX(int _x);
	int getX();
	void setY(int _y);
	int getY();
};
Disparo::Disparo() {
	x = 200;
	y = 2;
}
Disparo::~Disparo() {
	gotoxy(x, y);     cout << "         " << endl;
	gotoxy(x, y + 1); cout << "         " << endl;
	gotoxy(x, y + 2); cout << "         " << endl;
}
void Disparo::setX(int _x) {
	x = _x;
}
int Disparo::getX() {
	return x;
}
void Disparo::setY(int _y) {
	y = _y;
}
int Disparo::getY() {
	return y;
}
void Disparo::pDisparo(int xc, int yc) {
	// borrar 
	gotoxy(x, y);     cout << "         " << endl;
	gotoxy(x, y + 1); cout << "         " << endl;
	gotoxy(x, y + 2); cout << "         " << endl;
	x += 3;

	if (x > 200) {
		Sleep(20);
		x = xc;
		y = yc;
		setX(x);
		setY(y);
	}
	gotoxy(x, y);     color(10); cout << " ▄███▄" << endl;
	gotoxy(x, y + 1);			 cout << "███████" << endl;
	gotoxy(x, y + 2);			 cout << " ▀███▀" << endl; color(15);
	//cout << getX() << " , " << getY();
}



// Clase del cursor e imprecion de las plantas
class Cursor {
private:
	int x;
	int y;
public:
	Cursor();
	void pCursor(int nivel, Plantas* plantitas[46]);
	void bCursor();
	void mCursor(int nivel, Plantas* plantitas[46]);
	void setX(int);
	int getX();
	void setY(int);
	int getY();
};
Cursor::Cursor() {
	x = 100;
	y = 30;
}
void Cursor::pCursor(int nivel, Plantas* plantitas[46]) {

	SetConsoleOutputCP(CP_UTF8);
	if (nivel == 1) {
		gotoxy(40, 2); cout << endl;
		gotoxy(40, 3); color(10); cout << "      ▄▄▄▄▄        " << endl;
		gotoxy(40, 4); color(2); cout << " ▀█■"; color(10); cout << "███████▀█▄ ▄▄  " << endl;
		gotoxy(40, 5); cout << "    ████▄██████▌ █ " << endl;
		gotoxy(40, 6); cout << "    ▀████████▀ ▀▀  " << endl;
		gotoxy(40, 7); color(2); cout << "        ▀█▀        " << endl;
		gotoxy(40, 8); cout << "         █         " << endl;
		gotoxy(40, 9); cout << "      ▀▀▄▄█▄▄▀▀    " << endl;
		gotoxy(40, 10); cout << "     ▄▄▀▀▀ ▀▀▀▄▄   " << endl;
		gotoxy(39, 2); color(14);   cout << "█████████████████████" << endl; color(7);
		gotoxy(39, 3); color(14);   cout << "█" << endl; color(7); gotoxy(59, 3); color(14);  cout << "█" << endl; color(7);
		gotoxy(39, 4); color(14);   cout << "█" << endl; color(7); gotoxy(59, 4); color(14);  cout << "█" << endl; color(7);
		gotoxy(39, 5); color(14);   cout << "█" << endl; color(7); gotoxy(59, 5); color(14);  cout << "█" << endl; color(7);
		gotoxy(39, 6); color(14);   cout << "█" << endl; color(7); gotoxy(59, 6); color(14);  cout << "█" << endl; color(7);
		gotoxy(39, 7); color(14);   cout << "█" << endl; color(7); gotoxy(59, 7); color(14);  cout << "█" << endl; color(7);
		gotoxy(39, 8); color(14);   cout << "█" << endl; color(7); gotoxy(59, 8); color(14);  cout << "█" << endl; color(7);
		gotoxy(39, 9); color(14);   cout << "█" << endl; color(7); gotoxy(59, 9); color(14);  cout << "█" << endl; color(7);
		gotoxy(39, 10); color(14);  cout << "█" << endl; color(7); gotoxy(59, 10); color(14); cout << "█" << endl; color(7);
		gotoxy(39, 11); color(14);  cout << "██████▀█▀▀▀▀█▀▀▀▀████" << endl; color(7);
		gotoxy(39, 12); color(14);  cout << "█████▄ █ ██ █ ██ ████" << endl; color(7);
		gotoxy(39, 13); color(14);  cout << "██████ █ ██ █ ██ ████" << endl; color(7);
		gotoxy(39, 14); color(14);  cout << "██████▄█▄▄▄▄█▄▄▄▄████" << endl; color(7);


		gotoxy(65, 2); cout << endl;
		gotoxy(65, 3); color(6); cout << "    ▄▀"; color(12); cout << "▄"; color(6); cout << "▀"; color(12); cout << "▄█▄"; color(6); cout << "▀"; color(12); cout << "▄"; color(6); cout << "▀"; color(12); cout << "▄    " << endl;
		gotoxy(65, 4); color(6); cout << "  ▄▀"; color(12); cout << "▄██▄███▄███"; color(6); cout << "▀▄  " << endl;
		gotoxy(65, 5); color(6); cout << " ■"; color(12); cout << "████▀█████▀████"; color(6); cout << "■ " << endl;
		gotoxy(65, 6); color(6); cout << "  ▀▄"; color(12); cout << "███▄▄▄▄▄██▀"; color(6); cout << "▄▀  " << endl;
		gotoxy(65, 7); cout << "    ▀▀▄"; color(12); cout << "▀▀"; color(6); cout << "█"; color(12); cout << "▀▀"; color(6); cout << "▄▀▀   " << endl; color(10);
		gotoxy(65, 8); cout << "         █         " << endl;
		gotoxy(65, 9); cout << "     ▄▀█▄█▄█▀▄     " << endl;
		gotoxy(65, 10); cout << "      ▀▄███▄▀      " << endl;
		gotoxy(64, 2); color(14);   cout << "█████████████████████" << endl; color(7);
		gotoxy(64, 3); color(14);   cout << "█" << endl; color(7); gotoxy(84, 3); color(14);  cout << "█" << endl; color(7);
		gotoxy(64, 4); color(14);   cout << "█" << endl; color(7); gotoxy(84, 4); color(14);  cout << "█" << endl; color(7);
		gotoxy(64, 5); color(14);   cout << "█" << endl; color(7); gotoxy(84, 5); color(14);  cout << "█" << endl; color(7);
		gotoxy(64, 6); color(14);   cout << "█" << endl; color(7); gotoxy(84, 6); color(14);  cout << "█" << endl; color(7);
		gotoxy(64, 7); color(14);   cout << "█" << endl; color(7); gotoxy(84, 7); color(14);  cout << "█" << endl; color(7);
		gotoxy(64, 8); color(14);   cout << "█" << endl; color(7); gotoxy(84, 8); color(14);  cout << "█" << endl; color(7);
		gotoxy(64, 9); color(14);   cout << "█" << endl; color(7); gotoxy(84, 9); color(14);  cout << "█" << endl; color(7);
		gotoxy(64, 10); color(14);  cout << "█" << endl; color(7); gotoxy(84, 10); color(14); cout << "█" << endl; color(7);
		gotoxy(64, 11); color(14);  cout << "█████▀▀▀▀██▀▀▀▀██████" << endl; color(7);
		gotoxy(64, 12); color(14);  cout << "█████ ▀▀▀██ ██ ██████" << endl; color(7);
		gotoxy(64, 13); color(14);  cout << "████████ ██ ██ ██████" << endl; color(7);
		gotoxy(64, 14); color(14);  cout << "█████▄▄▄▄██▄▄▄▄██████" << endl; color(7);

		for (int j = 16; j < 76; j += 10) {
			for (int i = 0; i < 237; i++) {
				gotoxy(i, j); cout << "-";
			}
		}

		for (int j = 16; j < 66; j++) {
			for (int i = 0; i < 217; i += 20) {
				gotoxy(i, j); cout << "|";
			}
		}


		for (int i = 0; i < numero_planta; i++) {
			plantitas[i]->printPlanta(plantitas[i]->getX(), plantitas[i]->getY());
		}

		gotoxy(x + 2, y);	  cout << "█";
		gotoxy(x, y + 1); cout << "■■●■■";
		gotoxy(x + 2, y + 2); cout << "█";
	}
}
void Cursor::bCursor() {
	gotoxy(x, y);	cout << "       ";
	gotoxy(x, y + 1); cout << "      ";
	gotoxy(x, y + 2); cout << "      ";

}
void Cursor::mCursor(int nivel, Plantas* plantitas[46]) {
	char tecla;
	if (_kbhit()) {//detectar si se presiono alguna tecla
		tecla = _getch(); //guardar el valor presionado en tecla
		bCursor();



		//detectar el movimiento
		if (tecla == L && x > 8) x -= 20;
		if (tecla == R && x < 222) x += 20;
		if (tecla == Up && y > 5) y -= 10;
		if (tecla == Low && y < 60) y += 10;
		//escoger lanzaguisantes
		if (tecla == E && (x > 39 && x < 60) && (y < 15 && y>2)) {
			plantar = 1;
			opcion_planta = 1;
		}
		// escoger girasol
		if (tecla == E && (x > 60 && x < 81) && (y < 15 && y>2)) {
			plantar = 1;
			opcion_planta = 2;
		}
		// escoger nuez
		if (tecla == E && (x > 81 && x < 102) && (y < 15 && y>2)) {
			plantar = 1;
			opcion_planta = 3;
		}
		//escoger papa
		if (tecla == E && (x > 102 && x < 123) && (y < 15 && y>2)) {
			plantar = 1;
			opcion_planta = 4;
		}
		//Cancelar accion
		if (tecla == Q) {
			plantar = 0;
			opcion_planta = 0;
		}

		//booleabno para no plantar donde ya hay
		bool si = false;

		// fila 1
		if ((tecla == E) && (x == 28) && (y == 20) && (plantar == 1)) {
			for (int i = 0; i < numero_planta; i++) {
				if (plantitas[i]->getX() == x-7 && plantitas[i]->getY() == y-3) {
					si = true; cout << "mota";
				}
			}

			if(numero_planta==0){
				plantar = 0;
				plantarPlanta(x, y, plantitas);
			}
			if (si == false) {
				plantar = 0;
				plantarPlanta(x, y, plantitas);
			}
			si = false;
		}
		if ((tecla == E) && (x == 48) && (y == 20) && (plantar == 1)) {
			for (int i = 0; i < numero_planta; i++) {
				if (plantitas[i]->getX() == x - 7 && plantitas[i]->getY() == y - 3) {
					si = true; cout << "mota";
				}
			}

			if (numero_planta == 0) {
				plantar = 0;
				plantarPlanta(x, y, plantitas);
			}
			if (si == false) {
				plantar = 0;
				plantarPlanta(x, y, plantitas);
			}
			si = false;
		}
		if ((tecla == E) && (x == 68) && (y == 20) && (plantar == 1)) {
			for (int i = 0; i < numero_planta; i++) {
				if (plantitas[i]->getX() == x - 7 && plantitas[i]->getY() == y - 3) {
					si = true; cout << "mota";
				}
			}

			if (numero_planta == 0) {
				plantar = 0;
				plantarPlanta(x, y, plantitas);
			}
			if (si == false) {
				plantar = 0;
				plantarPlanta(x, y, plantitas);
			}
			si = false;
		}
		if ((tecla == E) && (x == 88) && (y == 20) && (plantar == 1)) {
			for (int i = 0; i < numero_planta; i++) {
				if (plantitas[i]->getX() == x - 7 && plantitas[i]->getY() == y - 3) {
					si = true; cout << "mota";
				}
			}

			if (numero_planta == 0) {
				plantar = 0;
				plantarPlanta(x, y, plantitas);
			}
			if (si == false) {
				plantar = 0;
				plantarPlanta(x, y, plantitas);
			}
			si = false;
		}
		if ((tecla == E) && (x == 108) && (y == 20) && (plantar == 1)) {
			for (int i = 0; i < numero_planta; i++) {
				if (plantitas[i]->getX() == x - 7 && plantitas[i]->getY() == y - 3) {
					si = true; cout << "mota";
				}
			}

			if (numero_planta == 0) {
				plantar = 0;
				plantarPlanta(x, y, plantitas);
			}
			if (si == false) {
				plantar = 0;
				plantarPlanta(x, y, plantitas);
			}
			si = false;
		}
		if ((tecla == E) && (x == 128) && (y == 20) && (plantar == 1)) {
			for (int i = 0; i < numero_planta; i++) {
				if (plantitas[i]->getX() == x - 7 && plantitas[i]->getY() == y - 3) {
					si = true; cout << "mota";
				}
			}

			if (numero_planta == 0) {
				plantar = 0;
				plantarPlanta(x, y, plantitas);
			}
			if (si == false) {
				plantar = 0;
				plantarPlanta(x, y, plantitas);
			}
			si = false;
		}
		if ((tecla == E) && (x == 148) && (y == 20) && (plantar == 1)) {
			for (int i = 0; i < numero_planta; i++) {
				if (plantitas[i]->getX() == x - 7 && plantitas[i]->getY() == y - 3) {
					si = true; cout << "mota";
				}
			}

			if (numero_planta == 0) {
				plantar = 0;
				plantarPlanta(x, y, plantitas);
			}
			if (si == false) {
				plantar = 0;
				plantarPlanta(x, y, plantitas);
			}
			si = false;
		}
		if ((tecla == E) && (x == 168) && (y == 20) && (plantar == 1)) {
			for (int i = 0; i < numero_planta; i++) {
				if (plantitas[i]->getX() == x - 7 && plantitas[i]->getY() == y - 3) {
					si = true; cout << "mota";
				}
			}

			if (numero_planta == 0) {
				plantar = 0;
				plantarPlanta(x, y, plantitas);
			}
			if (si == false) {
				plantar = 0;
				plantarPlanta(x, y, plantitas);
			}
			si = false;
		}
		if ((tecla == E) && (x == 188) && (y == 20) && (plantar == 1)) {
			for (int i = 0; i < numero_planta; i++) {
				if (plantitas[i]->getX() == x - 7 && plantitas[i]->getY() == y - 3) {
					si = true; cout << "mota";
				}
			}

			if (numero_planta == 0) {
				plantar = 0;
				plantarPlanta(x, y, plantitas);
			}
			if (si == false) {
				plantar = 0;
				plantarPlanta(x, y, plantitas);
			}
			si = false;
		}

		//fila 2
		if ((tecla == E) && (x == 28) && (y == 30) && (plantar == 1)) {
			for (int i = 0; i < numero_planta; i++) {
				if (plantitas[i]->getX() == x - 7 && plantitas[i]->getY() == y - 3) {
					si = true; cout << "mota";
				}
			}

			if (numero_planta == 0) {
				plantar = 0;
				plantarPlanta(x, y, plantitas);
			}
			if (si == false) {
				plantar = 0;
				plantarPlanta(x, y, plantitas);
			}
			si = false;
		}
		if ((tecla == E) && (x == 48) && (y == 30) && (plantar == 1)) {
			for (int i = 0; i < numero_planta; i++) {
				if (plantitas[i]->getX() == x - 7 && plantitas[i]->getY() == y - 3) {
					si = true; cout << "mota";
				}
			}

			if (numero_planta == 0) {
				plantar = 0;
				plantarPlanta(x, y, plantitas);
			}
			if (si == false) {
				plantar = 0;
				plantarPlanta(x, y, plantitas);
			}
			si = false;
		}
		if ((tecla == E) && (x == 68) && (y == 30) && (plantar == 1)) {
			for (int i = 0; i < numero_planta; i++) {
				if (plantitas[i]->getX() == x - 7 && plantitas[i]->getY() == y - 3) {
					si = true; cout << "mota";
				}
			}

			if (numero_planta == 0) {
				plantar = 0;
				plantarPlanta(x, y, plantitas);
			}
			if (si == false) {
				plantar = 0;
				plantarPlanta(x, y, plantitas);
			}
			si = false;
		}
		if ((tecla == E) && (x == 88) && (y == 30) && (plantar == 1)) {
			for (int i = 0; i < numero_planta; i++) {
				if (plantitas[i]->getX() == x - 7 && plantitas[i]->getY() == y - 3) {
					si = true; cout << "mota";
				}
			}

			if (numero_planta == 0) {
				plantar = 0;
				plantarPlanta(x, y, plantitas);
			}
			if (si == false) {
				plantar = 0;
				plantarPlanta(x, y, plantitas);
			}
			si = false;
		}
		if ((tecla == E) && (x == 108) && (y == 30) && (plantar == 1)) {
			for (int i = 0; i < numero_planta; i++) {
				if (plantitas[i]->getX() == x - 7 && plantitas[i]->getY() == y - 3) {
					si = true; cout << "mota";
				}
			}

			if (numero_planta == 0) {
				plantar = 0;
				plantarPlanta(x, y, plantitas);
			}
			if (si == false) {
				plantar = 0;
				plantarPlanta(x, y, plantitas);
			}
			si = false;
		}
		if ((tecla == E) && (x == 128) && (y == 30) && (plantar == 1)) {
			for (int i = 0; i < numero_planta; i++) {
				if (plantitas[i]->getX() == x - 7 && plantitas[i]->getY() == y - 3) {
					si = true; cout << "mota";
				}
			}

			if (numero_planta == 0) {
				plantar = 0;
				plantarPlanta(x, y, plantitas);
			}
			if (si == false) {
				plantar = 0;
				plantarPlanta(x, y, plantitas);
			}
			si = false;
		}
		if ((tecla == E) && (x == 148) && (y == 30) && (plantar == 1)) {
			for (int i = 0; i < numero_planta; i++) {
				if (plantitas[i]->getX() == x - 7 && plantitas[i]->getY() == y - 3) {
					si = true; cout << "mota";
				}
			}

			if (numero_planta == 0) {
				plantar = 0;
				plantarPlanta(x, y, plantitas);
			}
			if (si == false) {
				plantar = 0;
				plantarPlanta(x, y, plantitas);
			}
			si = false;
		}
		if ((tecla == E) && (x == 168) && (y == 30) && (plantar == 1)) {
			for (int i = 0; i < numero_planta; i++) {
				if (plantitas[i]->getX() == x - 7 && plantitas[i]->getY() == y - 3) {
					si = true; cout << "mota";
				}
			}

			if (numero_planta == 0) {
				plantar = 0;
				plantarPlanta(x, y, plantitas);
			}
			if (si == false) {
				plantar = 0;
				plantarPlanta(x, y, plantitas);
			}
			si = false;
		}
		if ((tecla == E) && (x == 188) && (y == 30) && (plantar == 1)) {
			for (int i = 0; i < numero_planta; i++) {
				if (plantitas[i]->getX() == x - 7 && plantitas[i]->getY() == y - 3) {
					si = true; cout << "mota";
				}
			}

			if (numero_planta == 0) {
				plantar = 0;
				plantarPlanta(x, y, plantitas);
			}
			if (si == false) {
				plantar = 0;
				plantarPlanta(x, y, plantitas);
			}
			si = false;;
		}

		//fila 3
		if ((tecla == E) && (x == 28) && (y == 40) && (plantar == 1)) {
			for (int i = 0; i < numero_planta; i++) {
				if (plantitas[i]->getX() == x - 7 && plantitas[i]->getY() == y - 3) {
					si = true; cout << "mota";
				}
			}

			if (numero_planta == 0) {
				plantar = 0;
				plantarPlanta(x, y, plantitas);
			}
			if (si == false) {
				plantar = 0;
				plantarPlanta(x, y, plantitas);
			}
			si = false;
		}
		if ((tecla == E) && (x == 48) && (y == 40) && (plantar == 1)) {
			for (int i = 0; i < numero_planta; i++) {
				if (plantitas[i]->getX() == x - 7 && plantitas[i]->getY() == y - 3) {
					si = true; cout << "mota";
				}
			}

			if (numero_planta == 0) {
				plantar = 0;
				plantarPlanta(x, y, plantitas);
			}
			if (si == false) {
				plantar = 0;
				plantarPlanta(x, y, plantitas);
			}
			si = false;
		}
		if ((tecla == E) && (x == 68) && (y == 40) && (plantar == 1)) {
			for (int i = 0; i < numero_planta; i++) {
				if (plantitas[i]->getX() == x - 7 && plantitas[i]->getY() == y - 3) {
					si = true; cout << "mota";
				}
			}

			if (numero_planta == 0) {
				plantar = 0;
				plantarPlanta(x, y, plantitas);
			}
			if (si == false) {
				plantar = 0;
				plantarPlanta(x, y, plantitas);
			}
			si = false;
		}
		if ((tecla == E) && (x == 88) && (y == 40) && (plantar == 1)) {
			for (int i = 0; i < numero_planta; i++) {
				if (plantitas[i]->getX() == x - 7 && plantitas[i]->getY() == y - 3) {
					si = true; cout << "mota";
				}
			}

			if (numero_planta == 0) {
				plantar = 0;
				plantarPlanta(x, y, plantitas);
			}
			if (si == false) {
				plantar = 0;
				plantarPlanta(x, y, plantitas);
			}
			si = false;
		}
		if ((tecla == E) && (x == 108) && (y == 40) && (plantar == 1)) {
			for (int i = 0; i < numero_planta; i++) {
				if (plantitas[i]->getX() == x - 7 && plantitas[i]->getY() == y - 3) {
					si = true; cout << "mota";
				}
			}

			if (numero_planta == 0) {
				plantar = 0;
				plantarPlanta(x, y, plantitas);
			}
			if (si == false) {
				plantar = 0;
				plantarPlanta(x, y, plantitas);
			}
			si = false;
		}
		if ((tecla == E) && (x == 128) && (y == 40) && (plantar == 1)) {
			for (int i = 0; i < numero_planta; i++) {
				if (plantitas[i]->getX() == x - 7 && plantitas[i]->getY() == y - 3) {
					si = true; cout << "mota";
				}
			}

			if (numero_planta == 0) {
				plantar = 0;
				plantarPlanta(x, y, plantitas);
			}
			if (si == false) {
				plantar = 0;
				plantarPlanta(x, y, plantitas);
			}
			si = false;
		}
		if ((tecla == E) && (x == 148) && (y == 40) && (plantar == 1)) {
			for (int i = 0; i < numero_planta; i++) {
				if (plantitas[i]->getX() == x - 7 && plantitas[i]->getY() == y - 3) {
					si = true; cout << "mota";
				}
			}

			if (numero_planta == 0) {
				plantar = 0;
				plantarPlanta(x, y, plantitas);
			}
			if (si == false) {
				plantar = 0;
				plantarPlanta(x, y, plantitas);
			}
			si = false;
		}
		if ((tecla == E) && (x == 168) && (y == 40) && (plantar == 1)) {
			for (int i = 0; i < numero_planta; i++) {
				if (plantitas[i]->getX() == x - 7 && plantitas[i]->getY() == y - 3) {
					si = true; cout << "mota";
				}
			}

			if (numero_planta == 0) {
				plantar = 0;
				plantarPlanta(x, y, plantitas);
			}
			if (si == false) {
				plantar = 0;
				plantarPlanta(x, y, plantitas);
			}
			si = false;
		}
		if ((tecla == E) && (x == 188) && (y == 40) && (plantar == 1)) {
			for (int i = 0; i < numero_planta; i++) {
				if (plantitas[i]->getX() == x - 7 && plantitas[i]->getY() == y - 3) {
					si = true; cout << "mota";
				}
			}

			if (numero_planta == 0) {
				plantar = 0;
				plantarPlanta(x, y, plantitas);
			}
			if (si == false) {
				plantar = 0;
				plantarPlanta(x, y, plantitas);
			}
			si = false;
		}

		//fila 4
		if ((tecla == E) && (x == 28) && (y == 50) && (plantar == 1)) {
			for (int i = 0; i < numero_planta; i++) {
				if (plantitas[i]->getX() == x - 7 && plantitas[i]->getY() == y - 3) {
					si = true; cout << "mota";
				}
			}

			if (numero_planta == 0) {
				plantar = 0;
				plantarPlanta(x, y, plantitas);
			}
			if (si == false) {
				plantar = 0;
				plantarPlanta(x, y, plantitas);
			}
			si = false;
		}
		if ((tecla == E) && (x == 48) && (y == 50) && (plantar == 1)) {
			for (int i = 0; i < numero_planta; i++) {
				if (plantitas[i]->getX() == x - 7 && plantitas[i]->getY() == y - 3) {
					si = true; cout << "mota";
				}
			}

			if (numero_planta == 0) {
				plantar = 0;
				plantarPlanta(x, y, plantitas);
			}
			if (si == false) {
				plantar = 0;
				plantarPlanta(x, y, plantitas);
			}
			si = false;
		}
		if ((tecla == E) && (x == 68) && (y == 50) && (plantar == 1)) {
			for (int i = 0; i < numero_planta; i++) {
				if (plantitas[i]->getX() == x - 7 && plantitas[i]->getY() == y - 3) {
					si = true; cout << "mota";
				}
			}

			if (numero_planta == 0) {
				plantar = 0;
				plantarPlanta(x, y, plantitas);
			}
			if (si == false) {
				plantar = 0;
				plantarPlanta(x, y, plantitas);
			}
			si = false;
		}
		if ((tecla == E) && (x == 88) && (y == 50) && (plantar == 1)) {
			for (int i = 0; i < numero_planta; i++) {
				if (plantitas[i]->getX() == x - 7 && plantitas[i]->getY() == y - 3) {
					si = true; cout << "mota";
				}
			}

			if (numero_planta == 0) {
				plantar = 0;
				plantarPlanta(x, y, plantitas);
			}
			if (si == false) {
				plantar = 0;
				plantarPlanta(x, y, plantitas);
			}
			si = false;
		}
		if ((tecla == E) && (x == 108) && (y == 50) && (plantar == 1)) {
			for (int i = 0; i < numero_planta; i++) {
				if (plantitas[i]->getX() == x - 7 && plantitas[i]->getY() == y - 3) {
					si = true; cout << "mota";
				}
			}

			if (numero_planta == 0) {
				plantar = 0;
				plantarPlanta(x, y, plantitas);
			}
			if (si == false) {
				plantar = 0;
				plantarPlanta(x, y, plantitas);
			}
			si = false;
		}
		if ((tecla == E) && (x == 128) && (y == 50) && (plantar == 1)) {
			for (int i = 0; i < numero_planta; i++) {
				if (plantitas[i]->getX() == x - 7 && plantitas[i]->getY() == y - 3) {
					si = true; cout << "mota";
				}
			}

			if (numero_planta == 0) {
				plantar = 0;
				plantarPlanta(x, y, plantitas);
			}
			if (si == false) {
				plantar = 0;
				plantarPlanta(x, y, plantitas);
			}
			si = false;
		}
		if ((tecla == E) && (x == 148) && (y == 50) && (plantar == 1)) {
			for (int i = 0; i < numero_planta; i++) {
				if (plantitas[i]->getX() == x - 7 && plantitas[i]->getY() == y - 3) {
					si = true; cout << "mota";
				}
			}

			if (numero_planta == 0) {
				plantar = 0;
				plantarPlanta(x, y, plantitas);
			}
			if (si == false) {
				plantar = 0;
				plantarPlanta(x, y, plantitas);
			}
			si = false;
		}
		if ((tecla == E) && (x == 168) && (y == 50) && (plantar == 1)) {
			for (int i = 0; i < numero_planta; i++) {
				if (plantitas[i]->getX() == x - 7 && plantitas[i]->getY() == y - 3) {
					si = true; cout << "mota";
				}
			}

			if (numero_planta == 0) {
				plantar = 0;
				plantarPlanta(x, y, plantitas);
			}
			if (si == false) {
				plantar = 0;
				plantarPlanta(x, y, plantitas);
			}
			si = false;
		}
		if ((tecla == E) && (x == 188) && (y == 50) && (plantar == 1)) {
			for (int i = 0; i < numero_planta; i++) {
				if (plantitas[i]->getX() == x - 7 && plantitas[i]->getY() == y - 3) {
					si = true; cout << "mota";
				}
			}

			if (numero_planta == 0) {
				plantar = 0;
				plantarPlanta(x, y, plantitas);
			}
			if (si == false) {
				plantar = 0;
				plantarPlanta(x, y, plantitas);
			}
			si = false;
		}

		//fila 5
		if ((tecla == E) && (x == 28) && (y == 60) && (plantar == 1)) {
			for (int i = 0; i < numero_planta; i++) {
				if (plantitas[i]->getX() == x - 7 && plantitas[i]->getY() == y - 3) {
					si = true; cout << "mota";
				}
			}

			if (numero_planta == 0) {
				plantar = 0;
				plantarPlanta(x, y, plantitas);
			}
			if (si == false) {
				plantar = 0;
				plantarPlanta(x, y, plantitas);
			}
			si = false;
		}
		if ((tecla == E) && (x == 48) && (y == 60) && (plantar == 1)) {
			for (int i = 0; i < numero_planta; i++) {
				if (plantitas[i]->getX() == x - 7 && plantitas[i]->getY() == y - 3) {
					si = true; cout << "mota";
				}
			}

			if (numero_planta == 0) {
				plantar = 0;
				plantarPlanta(x, y, plantitas);
			}
			if (si == false) {
				plantar = 0;
				plantarPlanta(x, y, plantitas);
			}
			si = false;
		}
		if ((tecla == E) && (x == 68) && (y == 60) && (plantar == 1)) {
			for (int i = 0; i < numero_planta; i++) {
				if (plantitas[i]->getX() == x - 7 && plantitas[i]->getY() == y - 3) {
					si = true; cout << "mota";
				}
			}

			if (numero_planta == 0) {
				plantar = 0;
				plantarPlanta(x, y, plantitas);
			}
			if (si == false) {
				plantar = 0;
				plantarPlanta(x, y, plantitas);
			}
			si = false;
		}
		if ((tecla == E) && (x == 88) && (y == 60) && (plantar == 1)) {
			for (int i = 0; i < numero_planta; i++) {
				if (plantitas[i]->getX() == x - 7 && plantitas[i]->getY() == y - 3) {
					si = true; cout << "mota";
				}
			}

			if (numero_planta == 0) {
				plantar = 0;
				plantarPlanta(x, y, plantitas);
			}
			if (si == false) {
				plantar = 0;
				plantarPlanta(x, y, plantitas);
			}
			si = false;
		}
		if ((tecla == E) && (x == 108) && (y == 60) && (plantar == 1)) {
			for (int i = 0; i < numero_planta; i++) {
				if (plantitas[i]->getX() == x - 7 && plantitas[i]->getY() == y - 3) {
					si = true; cout << "mota";
				}
			}

			if (numero_planta == 0) {
				plantar = 0;
				plantarPlanta(x, y, plantitas);
			}
			if (si == false) {
				plantar = 0;
				plantarPlanta(x, y, plantitas);
			}
			si = false;
		}
		if ((tecla == E) && (x == 128) && (y == 60) && (plantar == 1)) {
			for (int i = 0; i < numero_planta; i++) {
				if (plantitas[i]->getX() == x - 7 && plantitas[i]->getY() == y - 3) {
					si = true; cout << "mota";
				}
			}

			if (numero_planta == 0) {
				plantar = 0;
				plantarPlanta(x, y, plantitas);
			}
			if (si == false) {
				plantar = 0;
				plantarPlanta(x, y, plantitas);
			}
			si = false;
		}
		if ((tecla == E) && (x == 148) && (y == 60) && (plantar == 1)) {
			for (int i = 0; i < numero_planta; i++) {
				if (plantitas[i]->getX() == x - 7 && plantitas[i]->getY() == y - 3) {
					si = true; cout << "mota";
				}
			}

			if (numero_planta == 0) {
				plantar = 0;
				plantarPlanta(x, y, plantitas);
			}
			if (si == false) {
				plantar = 0;
				plantarPlanta(x, y, plantitas);
			}
			si = false;
		}
		if ((tecla == E) && (x == 168) && (y == 60) && (plantar == 1)) {
			for (int i = 0; i < numero_planta; i++) {
				if (plantitas[i]->getX() == x - 7 && plantitas[i]->getY() == y - 3) {
					si = true; cout << "mota";
				}
			}

			if (numero_planta == 0) {
				plantar = 0;
				plantarPlanta(x, y, plantitas);
			}
			if (si == false) {
				plantar = 0;
				plantarPlanta(x, y, plantitas);
			}
			si = false;
		}
		if ((tecla == E) && (x == 188) && (y == 60) && (plantar == 1)) {
			for (int i = 0; i < numero_planta; i++) {
				if (plantitas[i]->getX() == x - 7 && plantitas[i]->getY() == y - 3) {
					si = true; cout << "mota";
				}
			}

			if (numero_planta == 0) {
				plantar = 0;
				plantarPlanta(x, y, plantitas);
			}
			if (si == false) {
				plantar = 0;
				plantarPlanta(x, y, plantitas);
			}
			si = false;
		}


		pCursor(nivel, plantitas);

	}
}
void Cursor::setX(int _x) {
	x = _x;
}
int Cursor::getX() {
	return x;
}
void Cursor::setY(int _y) {
	y = _y;
}
int Cursor::getY() {
	return y;
}

class Chombi {
private:
	int x;
	int y;
	int damage, vida;
public:
	Chombi();
	void setX(int);
	int getX();
	void setY(int);
	int getY();
	// imprimir Chombi
	void pChombi();
	void impacto(class Disparo guisante[46]); // detectar choque y quitar
	void setdamage(int _damage);
	void setvida(int _vida);
	int getvida();
	int getdamage();
};
Chombi::Chombi() {
	int fila = rand() % 5 + 1;
	switch (fila) {
	case 1:
		y = 18;
		x = rand() % 20 + 200; break;
	case 2:
		y = 28;
		x = rand() % 20 + 200; break;
	case 3:
		y = 38;
		x = rand() % 20 + 200; break;
	case 4:
		y = 48;
		x = rand() % 20 + 200; break;
	case 5:
		y = 58;
		x = rand() % 20 + 200; break;
	}
	vida = 10;
	damage = 1;
}
void Chombi::setdamage(int _damage) {
	damage = _damage;
}
int Chombi::getdamage() {
	return damage;
}
void Chombi::setvida(int _vida) {
	vida = _vida;
}
int Chombi::getvida() {
	return vida;
}
void Chombi::setX(int _x) {
	x = _x;
}
int Chombi::getX() {
	return x;
}
void Chombi::setY(int _y) {
	y = _y;
}
int Chombi::getY() {
	return y;
}
void Chombi::pChombi() {
	// borrar 
	gotoxy(x, y);     cout << "         " << endl;
	gotoxy(x, y + 1); cout << "         " << endl;
	gotoxy(x, y + 2); cout << "         " << endl;
	gotoxy(x, y + 3); cout << "         " << endl;
	gotoxy(x, y + 4); cout << "         " << endl;
	gotoxy(x, y + 5); cout << "         " << endl;
	gotoxy(x, y + 6); cout << "         " << endl;
	gotoxy(x, y + 7); cout << "         " << endl;
	gotoxy(x, y + 8); cout << endl;

	//asignar coordenada
	//x-> debe ser aleatorio
	// y->  debe de incrementar una unidad
	x--;
	if (x == 2) {
		if (numero_planta < 5) {
			Sleep(80);
		}
		if (numero_planta > 5 && numero_planta < 10) {
			Sleep(60);
		}
		if (numero_planta > 10 && numero_planta < 15) {
			Sleep(40);
		}
		if (numero_planta > 15 && numero_planta < 20) {
			Sleep(20);
		}
		int fila = rand() % 5 + 1;
		switch (fila) {
		case 1:
			y = 18;
			x = rand() % 20 + 200; break;
		case 2:
			y = 28;
			x = rand() % 20 + 200; break;
		case 3:
			y = 38;
			x = rand() % 20 + 200; break;
		case 4:
			y = 48;
			x = rand() % 20 + 200; break;
		case 5:
			y = 58;

		}
	}
	if (x > 2 && x < 20) {
		cerebro = true;
		gameOver = true;
	}

	// print
	gotoxy(x, y);     cout << "  ▄███▄" << endl;
	gotoxy(x, y + 1); cout << " █▄█▄██▌" << endl;
	gotoxy(x, y + 2); cout << "  ▀▄▄▄█▄" << endl;
	gotoxy(x, y + 3); cout << "▄▄▄▄████" << endl;
	gotoxy(x, y + 4); cout << "▄▄▀▀████" << endl;
	gotoxy(x, y + 5); cout << "    █  █" << endl;
	gotoxy(x, y + 6); cout << "   █    ▌" << endl;
	gotoxy(x, y + 7); cout << "   █▄ ▄▄█" << endl;

}
//colocion chombis
void Chombi::impacto(class Disparo guisante[46]) {
	for (int i = 0; i < numero_guisantes; i++) {
		if (x >= guisante[i].getX() - 5 && x <= guisante[i].getX() + 5 && y >= guisante[i].getY() - 2 && y <= guisante[i].getY() + 5) {
			vida = 0;
			gotoxy(x, y);     cout << "           " << endl;
			gotoxy(x, y + 1); cout << "           " << endl;
			gotoxy(x, y + 2); cout << "           " << endl;
			gotoxy(x, y + 3); cout << "           " << endl;
			gotoxy(x, y + 4); cout << "           " << endl;
			gotoxy(x, y + 5); cout << "           " << endl;
			gotoxy(x, y + 6); cout << "           " << endl;
			gotoxy(x, y + 7); cout << "           " << endl;

			int x2 = guisante[i].getX();
			int y2 = guisante[i].getY();
			guisante[i].setX(200);
			gotoxy(x2, y2);     cout << "         " << endl;
			gotoxy(x2, y2 + 1); cout << "         " << endl;
			gotoxy(x2, y2 + 2); cout << "         " << endl;
			int fila = rand() % 5 + 1;
			switch (fila) {
			case 1:
				y = 18;
				x = rand() % 20 + 200; break;
			case 2:
				y = 28;
				x = rand() % 20 + 200; break;
			case 3:
				y = 38;
				x = rand() % 20 + 200; break;
			case 4:
				y = 48;
				x = rand() % 20 + 200; break;
			case 5:
				y = 58;
				x = rand() % 20 + 200; break;
			}
			kills++;
		}
	}
}

void AltEnter()
{
	keybd_event(VK_MENU,
		0x38,
		0,
		0);
	keybd_event(VK_RETURN,
		0x1c,
		0,
		0);
	keybd_event(VK_RETURN,
		0x1c,
		KEYEVENTF_KEYUP,
		0);
	keybd_event(VK_MENU,
		0x38,
		KEYEVENTF_KEYUP,
		0);
	return;
} // Funcion para poner en pantalla completa
void pIntro() {
	gotoxy(85, 2); cout << endl; color(10);
	gotoxy(85, 3); cout << "██████  ██       █████  ███    ██ ████████ ███████ " << endl;
	gotoxy(85, 4); cout << "██   ██ ██      ██   ██ ████   ██    ██    ██		" << endl;
	gotoxy(85, 5); cout << "██████  ██      ███████ ██ ██  ██    ██    ███████ " << endl;
	gotoxy(85, 6); cout << "██      ██      ██   ██ ██  ██ ██    ██         ██ " << endl;
	gotoxy(85, 7); cout << "██      ███████ ██   ██ ██   ████    ██    ███████ " << endl;
	gotoxy(85, 8); cout << endl; color(6);
	gotoxy(85, 9);  cout << "                 ██    ██ ███████							" << endl;
	gotoxy(85, 10); cout << "                 ██    ██ ██								" << endl;
	gotoxy(85, 11); cout << "                 ██    ██ ███████							" << endl;
	gotoxy(85, 12); cout << "                  ██  ██       ██							" << endl;
	gotoxy(85, 13); cout << "                   ████   ███████ ██						" << endl;
	gotoxy(85, 14); cout << endl; color(8);
	gotoxy(85, 15); cout << "███████  ██████  ███    ███ ██████  ██ ███████ ███████ " << endl;
	gotoxy(85, 16); cout << "   ███  ██    ██ ████  ████ ██   ██ ██ ██      ██		" << endl;
	gotoxy(85, 17); cout << "  ███   ██    ██ ██ ████ ██ ██████  ██ █████   ███████ " << endl;
	gotoxy(85, 18); cout << " ███    ██    ██ ██  ██  ██ ██   ██ ██ ██           ██ " << endl;
	gotoxy(85, 19); cout << "███████  ██████  ██      ██ ██████  ██ ███████ ███████ " << endl;
	gotoxy(85, 20); cout << endl;
	gotoxy(85, 21); cout << endl; color(7);



	color(7);
	gotoxy(70, 22); cout << "                       ((((((######((((((/(//////***********                    " << endl;
	gotoxy(70, 23); cout << "                     *(((########(((((//////////**************                  " << endl;
	gotoxy(70, 24); cout << "                    (((##((#((((((((((////////******************                " << endl;
	gotoxy(70, 25); cout << "                  (((((((((((((((((((((//////********,,,*,,,**,**               " << endl;
	gotoxy(70, 26); cout << "                 ((###(((##((((((((#((////*******,,,,,,,,,,,,,,,,*              " << endl;
	gotoxy(70, 27); cout << "                (###########((((((###(//////*****,,*,,,,,,,,,,,,,,,             " << endl;
	gotoxy(70, 28); cout << "               (###########(((((#((((((/**///*****,,,,,,,,,,,,,,,,,/            " << endl;
	gotoxy(70, 29); cout << "              ((#############((((#(////*,,**,,*****,,,,,,,,,,,,,,,,,            " << endl;
	gotoxy(70, 30); cout << "        #(#/.(,(##################((/////***,,,.,,,,,,,,***,***,,,,,            " << endl;
	gotoxy(70, 31); cout << "       ,,(#%/*/#################%#(/*/,,,,****/*,...,,,,,,*,**,,,,,,            " << endl;
	gotoxy(70, 32); cout << "       /,(#((%###########((#####(/,.,*/(//*,.. ..**,,,,..,,,,,,,..,,            " << endl;
	gotoxy(70, 33); cout << "       (((((/##%#############(//*,.**%(.  .....  ..**,,*/*...,,,...*            " << endl;
	gotoxy(70, 34); cout << "       /*,,.*##%###########((//****/%//.. .,,. ....*(/((*,   .......            " << endl;
	gotoxy(70, 35); cout << "        ((/*((############(((////////***,........,*/(#(*,         .             " << endl;
	gotoxy(70, 36); cout << "        (%%(/%%########%#((//////////***,,,..,,***((##(/*.                      " << endl;
	gotoxy(70, 37); cout << "        .%%###%########%%%(//**********,,,*///////((##((*,..   .                " << endl;
	gotoxy(70, 38); cout << "          #%(*#########%%#(//**************/////(((###((*,.......               " << endl;
	gotoxy(70, 39); cout << "          .##(###########(//***************//((########(**,,.....               " << endl;
	gotoxy(70, 40); cout << "          ###########%###(//*****//////****/(##(((#%#((/**,.....                " << endl;
	gotoxy(70, 41); cout << "          ###(#######%%%##(///*///((((///**/##%#(((##((//***...                 " << endl;
	gotoxy(70, 42); cout << "          ###((######%####((((((((######(/**##(////(((/,,,,,..                  " << endl;
	gotoxy(70, 43); cout << "          #####(##%%%%###((/###########(((/*,,.,/((*(/*,....                    " << endl;
	gotoxy(70, 44); cout << "         (########%%%%%##((##%###%%%##((//****,.,*,.   ..,.                     " << endl;
	gotoxy(70, 45); cout << "        ######((##%%%%%##(##%%%%%%#%#((///**,,,,.,.   .....                     " << endl;
	gotoxy(70, 46); cout << "      (#####(((((#########%%%%%%#(((/*,****,,,,,,,,.......                      " << endl;
	gotoxy(70, 47); cout << "    ((######(((((((#####(#%%%%%(/*******,..,...        .*/                      " << endl;
	gotoxy(70, 48); cout << " #(##(#####(((((((((((####%%###/***/(//***/**,,........*,*                      " << endl;
	gotoxy(70, 49); cout << "##((((######((((//(/(((((####(//***/(//*,,,..     .....,,*,**,,                 " << endl;
	gotoxy(70, 50); cout << "(((/(######(((((/(////***/(((#((/*////******,.............,.**,,,,.             " << endl;
	gotoxy(70, 51); cout << "/***/((((###(((((//*/****////((#((////(/****,,,.........  /.**,,,,,,,,.         " << endl;
	gotoxy(70, 52); cout << "*,,,**/((((##((((//**,,,,///**,*/((///****,,...........   //**,,,,,,*,,,,,,,,,,," << endl;
	gotoxy(70, 53); cout << ",...,*//(((((((///**,,,..,**,,.   .******,..............  */(*,,,,,,,,,,*,,,,.,," << endl;
	//						PLANTAS						//
	cout << endl;
	cout << endl;
}
int main() {
	Plantas* plantitas[46]; //**************************************************************
	cursor(false); // apagar el cursor en la ventana de consola
	AltEnter(); //Lo hace pantalla completa


	//musica intro 
	const wchar_t* cancion = L"intro.wav";
	bool played = PlaySound(cancion, NULL, SND_LOOP | SND_ASYNC);

	SetConsoleOutputCP(CP_UTF8);

	//inicio
	pIntro();
	gotoxy(85, 55); cout << "Precione flecha derecha para iniciar ( -> ) ";
	while (true) {
		cursor(false); // apagar el cursor en la ventana de consola
		if (_kbhit()) {//detectar si se presiono alguna tecla
			tecla = _getch(); //guardar el valor presionado en tecla
			//detectar el movimiento
			if (tecla == R) break;

		}

	}

	//musica partida
	const wchar_t* cancion2 = L"jardin.wav";
	played = PlaySound(cancion2, NULL, SND_LOOP | SND_ASYNC);
	const wchar_t* cancion4 = L"ganar.wav";
	const wchar_t* cancion5 = L"perder.wav";

	system("cls");


	played = PlaySound(cancion2, NULL, SND_LOOP | SND_ASYNC);


	plantitas[0] = new Girasol(0, 0, 0, 0, 0, 0);

	while (true) {


		cursor(false); // apagar el cursor en la ventana de consola
		if (kills == 20) { system("cls"); cout << "GRACIAS POR JUGAR LA VERSION ALFA " << endl; played = PlaySound(cancion4, NULL, SND_LOOP | SND_SYNC); break; }
		if (cerebro == true) { system("cls"); cout << "ZOMBIES EAT YOUR BRAAAAIN" << endl; played = PlaySound(cancion5, NULL, SND_LOOP | SND_SYNC); break; }
		Cursor cursor;
		cursor.setX(108); //coord incial mouse
		cursor.setY(30); // coord inicial mouse
		cursor.pCursor(nivel, plantitas);
		//inicio del juego
		Chombi zombi[5];

		Disparo guisante[46];

		while (gameOver != true) {
			gotoxy(1, 1); cout << tiempo;

			for (int i = 0; i < 3; i++) {
				zombi[i].pChombi(); //imprime el zombi
				zombi[i].impacto(guisante);// colicion del disparo y el chombi
			}
			for (int i = 0; i < numero_planta; i++) {
				if (plantitas[i]->getTipo() == 1) {
					int xc = plantitas[i]->getX();
					int yc = plantitas[i]->getY();
					guisante[i].pDisparo(xc + 18, yc + 2);
				}
			}


			gotoxy(20, 5); color(14); cout << "SOLES: " << soles; color(7);
			gotoxy(20, 2); cout << "KILLS: " << kills; color(7);
			cursor.pCursor(nivel, plantitas);
			cursor.mCursor(nivel, plantitas);
			Sleep(1);
			tiempo++;
			if (tiempo % 50 == 0) { soles += 50; }
			if (kills == 20) { gameOver = true; }
		}
	}

}
