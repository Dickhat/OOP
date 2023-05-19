#pragma once
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <vector>

using namespace std;

//����� ��������������
class Location
{
protected:
	int X;//���������� X
	int Y;//���������� Y

public:
	//�����������
	Location(int ind_X, int ind_Y)
	{
		X = ind_X;
		Y = ind_Y;
	}

	//���������� X
	int Get_X()
	{
		return X;
	};

	//���������� Y
	int Get_Y()
	{
		return Y;
	}

	//������������� X
	void Set_X(int ind_X)
	{
		X = ind_X;
	};

	//������������� Y
	void Set_Y(int ind_Y)
	{
		Y = ind_Y;
	};
};

//����� �����
class Point :public Location
{
protected:
	bool Visible;//��������� �����

	struct heat_box
	{
		int start_X, end_X, start_Y, end_Y;	//���������� ������(� ����� ��������)
	} boxheat;

public:
	//�����������
	Point(int X, int Y) :Location(X, Y)
	{
		Visible = false;
		boxheat.start_X = X;
		boxheat.end_X = X + 1;
		boxheat.start_Y = Y;
		boxheat.end_Y = Y + 1;
	};

	//���������� ��������
	const heat_box& get()
	{
		return boxheat;
	}

	//������ ������� �����
	virtual void set_visible();

	//������ ��������� �����
	virtual void set_invisible();

	//������� ������� ������
	virtual void current_region(int X, int Y);

	//���������� �����
	void Move_To(int X, int Y);

	//�������������� �����
	void Drag();
};

//����� ����
class ball :public Point
{
protected:
	int radius;
public:
	//�����������
	ball(int X, int Y, int Rad) :Point(X, Y) { radius = Rad; };

	void Paint_ball();

	void set_rad(int Rad) { radius = Rad; };
	int get_rad() { return radius; };

	//���������� �������������� ������
	void current_region(int X, int Y);

	void set_visible();

	void set_invisible();
};

//����� ������ (�����)
class Tower :public Point
{
public:
	Tower(int X, int Y) :Point(X, Y) {

	};
	void virtual Paint();

	void current_region(int X, int Y);

	//������ ������� �����
	void set_visible();

	//������ ��������� �����
	void set_invisible();

	////���������� ����� (static)
	//void Move_To(int X, int Y)
	//{
	//	set_invisible();
	//	Set_X(X);
	//	Set_Y(Y);
	//	set_visible();
	//}

	////�������������� ����� (static)
	//void Drag()
	//{
	//	//while 7 - �����
	//	while (!KEY_DOWN(55))
	//	{
	//		// A - �����
	//		if (KEY_DOWN(65)) Move_To(Get_X() - 20, Get_Y());
	//		// W - �����
	//		else if (KEY_DOWN(87)) Move_To(Get_X(), Get_Y() - 20);
	//		// D - ������
	//		else if (KEY_DOWN(68)) Move_To(Get_X() + 20, Get_Y());
	//		// S - ����
	//		else if (KEY_DOWN(83)) Move_To(Get_X(), Get_Y() + 20);
	//		Sleep(10);
	//	}
	//}
};

//������������ �������� 1
class vertical_Tower_1 :public Tower
{
public:
	//�����������
	vertical_Tower_1(int X, int Y) :Tower(X, Y) {};

	void current_region(int X, int Y);

	//������ ������� �����
	void set_visible();

	//������ ��������� �����
	void set_invisible();
};

//������������ �������� 2
class vertical_Tower_2 :public vertical_Tower_1
{
public:
	//�����������
	vertical_Tower_2(int X, int Y) :vertical_Tower_1(X, Y) {};

	void print_construction();

	void current_region(int X, int Y);

	//������ ������� �����
	void set_visible();

	//������ ��������� �����
	void set_invisible();
};

//������� �������� 1
class left_construction_Tower : public Tower
{
public:
	//�����������
	left_construction_Tower(int X, int Y) :Tower(X, Y) {};

	//����� �����������
	void left_print();

	void current_region(int X, int Y);

	//������ ������� �����
	void set_visible();

	//������ ��������� �����
	void set_invisible();
};

//������� �������� 2
class right_construction_Tower : public Tower
{
public:
	//�����������
	right_construction_Tower(int X, int Y) :Tower(X, Y) {};

	//������ �����������
	void right_print();

	void current_region(int X, int Y);

	//������ ������� �����
	void set_visible();

	//������ ��������� �����
	void set_invisible();
};