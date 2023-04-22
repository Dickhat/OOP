#include <iostream>
#include <windows.h>
#include <conio.h>

using namespace std;

HDC hdc;//Контекст устройства(содержит описание видеокарты и всех необходимых графических элементов)

//макрос для определения кода нажатой клавиши
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

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

//функция паузы до нажатия кнопки
void PressKey(int VkCode)
{
	while (1)
		if (KEY_DOWN(VkCode))
			break;
}

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

	//Устанавливает X
	void Set_X(int ind_X)
	{
		X = ind_X;
	};

	//Устанавливает Y
	void Set_Y(int ind_Y)
	{
		Y = ind_Y;
	};
};

//Класс точка
class Point :public Location
{
protected:
	bool Visible;//Видимость точки
public:
	//КОНСТРУКТОР
	Point(int X, int Y) :Location(X, Y) 
	{ 
		Visible = false;
	};

	//Делает видимой точку
	virtual void set_visible()
	{
		Visible = true;
		SetPixel(hdc, X, Y, RGB(255, 0, 0));//рисуем точку установленным цветом
		SetPixel(hdc, X + 1, Y, RGB(255, 0, 0));//рисуем точку установленным цветом
		SetPixel(hdc, X, Y + 1, RGB(255, 0, 0));//рисуем точку установленным цветом
		SetPixel(hdc, X + 1, Y + 1, RGB(255, 0, 0));//рисуем точку установленным цветом
	};

	//Делает невидимой точку
	virtual void set_invisible()
	{
		Visible = false;
		SetPixel(hdc, X, Y, RGB(0, 0, 0));//рисуем точку установленным цветом
		SetPixel(hdc, X + 1, Y, RGB(0, 0, 0));//рисуем точку установленным цветом
		SetPixel(hdc, X, Y + 1, RGB(0, 0, 0));//рисуем точку установленным цветом
		SetPixel(hdc, X + 1, Y + 1, RGB(0, 0, 0));//рисуем точку установленным цветом
	};

	//Перемещает точку
	void Move_To(int X, int Y)
	{
		set_invisible();
		Set_X(X);
		Set_Y(Y);
		set_visible();
	}

	//Перетаскивание точки
	void Drag()
	{
		//while 7 - выход
		while (!KEY_DOWN(55))
		{
			// A - влево
			if (KEY_DOWN(65)) Move_To(Get_X() - 20, Get_Y());
			// W - вверх
			else if (KEY_DOWN(87)) Move_To(Get_X(), Get_Y() - 20);
			// D - вправо
			else if (KEY_DOWN(68)) Move_To(Get_X() + 20, Get_Y());
			// S - Вниз
			else if (KEY_DOWN(83)) Move_To(Get_X(), Get_Y() + 20);
			Sleep(10);
		}
	}
};

//Класс фигура (Башня)
class Tower :public Point
{
public:
	Tower(int X, int Y) :Point(X, Y) {
		//
	};
	void Paint();

	//Делает видимой точку
	void set_visible()
	{
		cout << __FUNCSIG__ << endl;
		Visible = true;
		HPEN PenBlack = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
		//делаем перо активным 
		SelectObject(hdc, PenBlack);
		Paint();

		DeleteObject(PenBlack);
	};

	//Делает невидимой точку
	void set_invisible()
	{
		cout << __FUNCSIG__ << endl;
		Visible = false;
		HPEN PenBlack = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
		//делаем перо активным 
		SelectObject(hdc, PenBlack);
		Paint();
		DeleteObject(PenBlack);
	};

	////Перемещает точку (static)
	//void Move_To(int X, int Y)
	//{
	//	set_invisible();
	//	Set_X(X);
	//	Set_Y(Y);
	//	set_visible();
	//}

	////Перетаскивание точки (static)
	//void Drag()
	//{
	//	//while 7 - выход
	//	while (!KEY_DOWN(55))
	//	{
	//		// A - влево
	//		if (KEY_DOWN(65)) Move_To(Get_X() - 20, Get_Y());
	//		// W - вверх
	//		else if (KEY_DOWN(87)) Move_To(Get_X(), Get_Y() - 20);
	//		// D - вправо
	//		else if (KEY_DOWN(68)) Move_To(Get_X() + 20, Get_Y());
	//		// S - Вниз
	//		else if (KEY_DOWN(83)) Move_To(Get_X(), Get_Y() + 20);
	//		Sleep(10);
	//	}
	//}
};

//Рисование Башни
void Tower::Paint()
{
	//Основание башни
	MoveToEx(hdc, X, Y, NULL);
	LineTo(hdc, X + 40, Y);
	LineTo(hdc, X + 40, Y + 100);
	LineTo(hdc, X, Y + 100);
	LineTo(hdc, X, Y);

	//Крыша башни
	LineTo(hdc, X - 20, Y);
	LineTo(hdc, X + 17, Y - 60);
	LineTo(hdc, X + 60, Y);
	LineTo(hdc, X - 20, Y);
}

int main()
{
	//получим дескриптор консольного окна
	HWND hwnd = GetConcolWindow();
	hdc = GetWindowDC(hwnd);    // контекст устройства консольного окна

	// Зададим перо и цвет пера
	HPEN Pen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
	SelectObject(hdc, Pen);

	Point APoint(200, 200);	//Точка с координатами 200,200
	APoint.set_visible();	//Появление точки

	PressKey(49);			//1
	APoint.Move_To(APoint.Get_X() + 100, APoint.Get_Y());//Перемещение точки

	PressKey(50);			//2
	APoint.set_invisible();	//Исчезновение точки

	PressKey(51);			//3
	Tower bashna(APoint.Get_X(), APoint.Get_Y());//Создание объекта башни в координатах 200,200
	bashna.Paint();			//Рисование башни
	bashna.set_visible();   //Появление башни

	PressKey(52);			//4
	bashna.Move_To(bashna.Get_X() + 100, bashna.Get_Y());//Перемещение башни

	PressKey(53);			//5
	bashna.set_invisible();	//Исчезновение башни

	PressKey(54);			//6
	bashna.Drag();			//Перетаскивание башни

	DeleteObject(Pen);
	return 0;
}