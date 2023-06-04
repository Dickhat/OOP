#include "classes.h"

HDC hdc;//Контекст устройства(содержит описание видеокарты и всех необходимых графических элементов)

//ПРоверка столкновений
bool check(vector <Tower*>& Tow, vector <ball*>& BALL);

void Drag(Point* current, vector <Tower*>& Tow, vector <ball*>& BALL)
{
	//while 7 - выход
	while (!KEY_DOWN(55))
	{
		// A - влево
		if (KEY_DOWN(65))
		{
			
			current->Move_To(current->Get_X() - 20, current->Get_Y());
			if (check(Tow, BALL) == 1)
				break;
		}
		// W - вверх
		else if (KEY_DOWN(87))
		{
			current->Move_To(current->Get_X(), current->Get_Y() - 20);
			if (check(Tow, BALL) == 1)
				break;
		}
		// D - вправо
		else if (KEY_DOWN(68))
		{
			current->Move_To(current->Get_X() + 20, current->Get_Y());
			if (check(Tow, BALL) == 1)
				break;
		}
		// S - Вниз
		else if (KEY_DOWN(83))
		{
			current->Move_To(current->Get_X(), current->Get_Y() + 20);
			if (check(Tow, BALL) == 1)
				break;
		}
		Sleep(10);
	}
}

int main()
{
	//получим дескриптор консольного окна
	HWND hwnd = GetConcolWindow();
	hdc = GetWindowDC(hwnd);    // контекст устройства консольного окна

	// Зададим перо и цвет пера
	HPEN Pen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
	SelectObject(hdc, Pen);

	Point APoint(200, 200);

	vertical_Tower_1 green_tw_1(400, 200);
	vertical_Tower_2 green_tw_2(600, 200);

	left_construction_Tower cons_tw_1(200, 400);
	right_construction_Tower cons_tw_2(400, 400);

	ball bill_1(APoint.Get_X(), APoint.Get_Y(), 10);
	ball bill_2(800, 400, 40);
	ball bill_3(1000, 400, 70);
	bill_1.set_visible();
	bill_2.set_visible();
	bill_3.set_visible();

	//Массив указателей для определения коллизий
	vector <Tower*> Tow(4);
	Tow[0] = &green_tw_1;
	Tow[1] = &green_tw_2;
	Tow[2] = &cons_tw_1;
	Tow[3] = &cons_tw_2;

	vector <ball*> BALL(3);
	BALL[0] = &bill_1;
	BALL[1] = &bill_2;
	BALL[2] = &bill_3;

	PressKey(49);			//1
	green_tw_1.set_visible();
	Drag(Tow[0], Tow, BALL);
	Sleep(200);

	PressKey(50);			//2
	green_tw_2.set_visible();
	Drag(Tow[1], Tow, BALL);

	PressKey(51);			//3
	cons_tw_1.set_visible();
	Drag(Tow[2], Tow, BALL);

	PressKey(52);			//4
	cons_tw_2.set_visible();
	Drag(Tow[3], Tow, BALL);

	DeleteObject(Pen);

	return 0;
}

//Проверка столкновений
bool check(vector <Tower*>& Tow, vector <ball*>& BALL)
{
	for(int i = 0; i < Tow.size(); ++i)
		for (int j = 0; j < BALL.size(); ++j)
		{
			//if Проверка, что объекты столкнулись
			if (Tow[i]->get().end_X < BALL[j]->get().start_X
				|| Tow[i]->get().start_X > BALL[j]->get().end_X
				|| Tow[i]->get().end_Y > BALL[j]->get().start_Y
				|| Tow[i]->get().start_Y < BALL[j]->get().end_Y)
			{
				//Ничего не делать, если не столкнулись
			}
			else
			{
				Tow[i]->set_invisible();	//Разрушить объект
				Tow[i]->Move_To(Tow[i]->Get_X() + 10000, Tow[i]->Get_Y() + 10000);
				BALL[j]->set_invisible();		//Разрушить объект
				BALL[j]->Move_To(BALL[j]->Get_X() + 15000, BALL[j]->Get_Y() + 15000);
				return true;
			}
		}
	return false;
};