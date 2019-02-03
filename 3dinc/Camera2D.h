#ifndef CAMERA_2D_H
#define CAMERA_2D_H

extern "C"{
#include "ssd1306.h"
}

class Camera2D
{
protected:
	double posX, posY;					// Позиция графического курсора в мировых координатах (для функций MoveTo и LineTo)
	
	double X0, Y0;						// Экранные координаты начала мировой системы координат (в пикселях)
	double prevX0, prevY0;
	double px, py;						// Единицы масштаба мировой системы координат (в пикселях)
	int W, H;							// Разрешение рабочей области окна
public:
	int WorldToScreenX(double X);
	int WorldToScreenY(double Y);
	double ScreenToWorldX(int X);
	double ScreenToWorldY(int Y);
	double L();
	double R();
	Camera2D();

	Camera2D(double X0, double Y0, double px, double py);

	// Очистка рабочей области окна
	void Clear();

	// Перемещение графического курсора (posX, posY)
	// Обратите внимание, что мы действуем в мировых координатах
	void MoveTo(double X, double Y);

	// Отрисовка линии из текущей позиции графического курсора в точку (X, Y) и его перемещение в эту точку
	// Обратите внимание, что мы действуем в мировых координатах
	// При отрисовке линии могут быть использованы WinApi функции
	// ::MoveToEx(dc, Xs, Ys, nullptr) и ::LineTo(dc, Xs, Ys)
	void LineTo(double X, double Y);
};

#endif // CAMERA_2D_H
