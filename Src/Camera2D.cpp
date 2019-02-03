#include "Camera2D.h"


int Camera2D::WorldToScreenX(double X)		// Переход от мировых координат к экранным (для абсциссы)
{
	return static_cast<int>(X0 + px * X);
}
int Camera2D::WorldToScreenY(double Y)		// Переход от мировых координат к экранным (для ординаты)
{
	return static_cast<int>(Y0 - py * Y);
}
double Camera2D::ScreenToWorldX(int X)		// Переход от экранных координат к мировым (для абсциссы)
{
	return ((double)X - X0 + 0.5) / px;
}
double Camera2D::ScreenToWorldY(int Y)		// Переход от экранных координат к мировым (для ординаты)
{
	return -((double)Y - Y0 + 0.5) / py;
}
double Camera2D::L()							// Абсцисса левой границы рабочей области окна (в мировых координатах)
{
	return ScreenToWorldX(0);
}
double Camera2D::R()							// Абсцисса правой границы рабочей области окна (в мировых координатах)
{
	return ScreenToWorldX(W);
}

Camera2D::Camera2D() {};

Camera2D::Camera2D(double X0, double Y0, double px, double py) : X0(X0), Y0(Y0), px(px), py(py)
{
	H = SSD1306_HEIGHT;
	W = SSD1306_WIDTH;
}

// Очистка рабочей области окна
void Camera2D::Clear()
{
	ssd1306_Fill(Black);
}

// Перемещение графического курсора (posX, posY)
// Обратите внимание, что мы действуем в мировых координатах
void Camera2D::MoveTo(double X, double Y)
{
	posX = X;
	posY = Y;
}

// Отрисовка линии из текущей позиции графического курсора в точку (X, Y) и его перемещение в эту точку
// Обратите внимание, что мы действуем в мировых координатах
// При отрисовке линии могут быть использованы WinApi функции
// ::MoveToEx(dc, Xs, Ys, nullptr) и ::LineTo(dc, Xs, Ys)
void Camera2D::LineTo(double X, double Y)
{
	//ssd1306_SetCursor(WorldToScreenX(posX), WorldToScreenY(posY));
	ssd1306_DrawLine(WorldToScreenX(posX), WorldToScreenY(posY),
					 WorldToScreenX(X), WorldToScreenY(Y),  White);
	MoveTo(X, Y);
}
