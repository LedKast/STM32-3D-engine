#include "Camera2D.h"


int Camera2D::WorldToScreenX(double X)		// ������� �� ������� ��������� � �������� (��� ��������)
{
	return static_cast<int>(X0 + px * X);
}
int Camera2D::WorldToScreenY(double Y)		// ������� �� ������� ��������� � �������� (��� ��������)
{
	return static_cast<int>(Y0 - py * Y);
}
double Camera2D::ScreenToWorldX(int X)		// ������� �� �������� ��������� � ������� (��� ��������)
{
	return ((double)X - X0 + 0.5) / px;
}
double Camera2D::ScreenToWorldY(int Y)		// ������� �� �������� ��������� � ������� (��� ��������)
{
	return -((double)Y - Y0 + 0.5) / py;
}
double Camera2D::L()							// �������� ����� ������� ������� ������� ���� (� ������� �����������)
{
	return ScreenToWorldX(0);
}
double Camera2D::R()							// �������� ������ ������� ������� ������� ���� (� ������� �����������)
{
	return ScreenToWorldX(W);
}

Camera2D::Camera2D() {};

Camera2D::Camera2D(double X0, double Y0, double px, double py) : X0(X0), Y0(Y0), px(px), py(py)
{
	H = SSD1306_HEIGHT;
	W = SSD1306_WIDTH;
}

// ������� ������� ������� ����
void Camera2D::Clear()
{
	ssd1306_Fill(Black);
}

// ����������� ������������ ������� (posX, posY)
// �������� ��������, ��� �� ��������� � ������� �����������
void Camera2D::MoveTo(double X, double Y)
{
	posX = X;
	posY = Y;
}

// ��������� ����� �� ������� ������� ������������ ������� � ����� (X, Y) � ��� ����������� � ��� �����
// �������� ��������, ��� �� ��������� � ������� �����������
// ��� ��������� ����� ����� ���� ������������ WinApi �������
// ::MoveToEx(dc, Xs, Ys, nullptr) � ::LineTo(dc, Xs, Ys)
void Camera2D::LineTo(double X, double Y)
{
	//ssd1306_SetCursor(WorldToScreenX(posX), WorldToScreenY(posY));
	ssd1306_DrawLine(WorldToScreenX(posX), WorldToScreenY(posY),
					 WorldToScreenX(X), WorldToScreenY(Y),  White);
	MoveTo(X, Y);
}
