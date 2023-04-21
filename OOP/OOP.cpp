#include <iostream>
#include <windows.h>
#include <conio.h>

using namespace std;

HDC hdc;//Контекст устройства(содержит описание видеокарты и всех необходимых графических элементов)

HWND GetConcolWindow()
{
	char str[128];
	// char title[128]="xxxxxxxxxxxxxxxxxx";
	LPWSTR title = (LPWSTR)"xxxxxxxxxxxxxxxxxx";	//новая версия Windows
	GetConsoleTitle((LPWSTR)str, sizeof((LPWSTR)str)); // получить заголовок окна
	SetConsoleTitle(title);						// установить новый заголовок окна
	Sleep(100);									// ждем смены заголовка окна (100 мс);

	HWND hwnd = FindWindow(NULL, (LPWSTR)title);// определяем дескриптор окна
	SetConsoleTitle((LPWSTR)str);				//возвращаем прежний заголовок

	return hwnd;//вернуть дескриптор окна
}//end GetConcolWindow()

//Класс местоположение
class Location
{
protected:
	int X;//Координата X
	int Y;//Координата Y

public:
	//Конструктор
	Location(int ind_X, int ind_Y)
	{
		X = ind_X;
		Y = ind_Y;
	}

	//Возвращает X
	int Get_X()
	{
		return X;
	};

	//Возвращает Y
	int Get_Y()
	{
		return Y;
	}
};

//Класс точка
class Point:public Location
{
protected:
	bool Visible;//Видимость точки
public:
	//Делает видимой точку
	void set_visible()
	{
		Visible = true;
	};

	//Делает невидимой точку
	void set_invisible()
	{
		Visible = false;
	};
};

//Класс фигура (Башня)
class Tower :public Point
{


};

int main()
{
	//получим дескриптор консольного окна
	HWND hwnd = GetConcolWindow();
	hdc = GetDC(hwnd);    // контекст устройства консольного окна

	// Зададим перо и цвет пера
	HPEN Pen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
	SelectObject(hdc, Pen);

	// Нарисуем круг установленным цветом
	Ellipse(hdc, 8, 8, 8, 8);

	return 0;
}