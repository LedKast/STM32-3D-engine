#ifndef AFFINE_TRANSFORM_H
#define AFFINE_TRANSFORM_H

#include <math.h>
#include "Matrix.h"

enum reftype{MAPX, MAPY, MAP00, MAPZ, MAPYZ, MAPZX, MAPXY, MAP000}; // типы отражений

// Перенос на вектор
Matrix<> translation(double x, double y)
{
	double T[9] = {
		1, 0, x,
		0, 1, y,
		0, 0, 1};
	return Matrix<>(3, T);
}
Matrix<> translation3D(double x, double y, double z)
{
	double T[] = {
            1.0, 0.0, 0.0, x,
            0.0, 1.0, 0.0, y,
            0.0, 0.0, 1.0, z,
            0.0, 0.0, 0.0, 1.0};
	return Matrix<>(4, T);
}

// identity() - тождественное АП;
Matrix<> identity()
{
    double T[9] = {
            1, 0, 0,
            0, 1, 0,
            0, 0, 1};
    return Matrix<>(3, T);
}
Matrix<> identity3D()
{
    double T[] = {
            1.0, 0.0, 0.0, 0.0,
            0.0, 1.0, 0.0, 0.0,
            0.0, 0.0, 1.0, 0.0,
            0.0, 0.0, 0.0, 1.0};
    return Matrix<>(4, T);
}

// rotation(t) - поворот на угол t;
Matrix<> rotation(double t)
{
    double T[9] = {
            cos(t), -sin(t), 0,
            sin(t), cos(t), 0,
            0, 0, 1};
    return Matrix<>(3, T);
}
// повороты для 3D
Matrix<> rotationX(double t)
{
    double T[] = {
            1.0, 0.0, 0.0, 0.0,
            0.0, cos(t), -sin(t), 0.0,
            0.0, sin(t), cos(t), 0.0,
            0.0, 0.0, 0.0, 1.0};
    return Matrix<>(4, T);
}
Matrix<> rotationY(double t)
{
    double T[] = {
            cos(t), 0.0, sin(t), 0.0,
            0.0, 1.0, 0.0, 0.0,
            -sin(t), 0.0, cos(t), 0.0,
            0.0, 0.0, 0.0, 1.0};
    return Matrix<>(4, T);
}
Matrix<> rotationZ(double t){
    double T[] = {
            cos(t), -sin(t), 0.0, 0.0,
            sin(t), cos(t), 0.0, 0.0,
            0.0, 0.0, 1.0, 0.0,
            0.0, 0.0, 0.0, 1.0};
    return Matrix<>(4, T);
}
/// против часовой стрелки (counter clockwise)
Matrix<> crotationX(double c, double s)
{
    double d = 1.0/sqrt(c*c+s*s);
    double T[16] = {
            1, 0, 0, 0,
            0, c*d, s*d, 0,
            0, -s*d, c*d, 0,
            0, 0, 0, 1};
    return Matrix<>(4, T);
}
Matrix<> crotationY(double c, double s)
{
    double d = 1.0/sqrt(c*c+s*s);
    double T[16] = {
            c*d, 0, -s*d, 0,
            0, 1, 0, 0,
            s*d, 0, c*d, 0,
            0, 0, 0, 1};
    return Matrix<>(4, T);
}
Matrix<> crotationZ(double c, double s)
{
    double d = 1.0/sqrt(c*c+s*s);
    double T[16] = {
            c*d, s*d, 0, 0,
            -s*d, c*d, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1};
    return Matrix<>(4, T);
}

// scaling(kx, ky) - масштабирование;
Matrix<> scaling(double kx, double ky)
{
    double T[9] = {
            kx, 0, 0,
            0, ky, 0,
            0, 0, 1};
    return Matrix<>(3, T);
}

Matrix<> scaling3D(double kx, double ky, double kz)
{
    double T[16] = {
            kx, 0, 0, 0,
            0, ky, 0, 0,
            0, 0, kz, 0,
            0, 0, 0, 1};
    return Matrix<>(4, T);
}

// mapping (различные виды отражений) - по желанию, для создания матриц отражения можно использовать функцию Scaling.
Matrix<> mapping(reftype type)
{
    double T[9]= {
            1, 0, 0,
            0, 1, 0,
            0, 0, 1};
    switch (type)
    {
        case MAPX:
            T[4] = -1;
            break;
        case MAPY:
            T[0] = -1;
            break;

        case MAP00:
            T[0] = T[4] = -1;
            break;
    }

    return Matrix<>(3, T);
}
Matrix<> mapping3D(reftype type)
{
    double T[16]= {
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1};
    switch (type)
    {
        case MAPX:
            T[5] = T[10] = -1;
            break;
        case MAPY:
            T[0] = T[10] = -1;
            break;
        case MAPZ:
            T[0] = T[5] = -1;
            break;

        case MAP000:
            T[0] = T[5] = T[10] = -1;
            break;

        case MAPYZ:
            T[0] = -1;
            break;
        case MAPZX:
            T[5] = -1;
            break;
        case MAPXY:
            T[10] = -1;
            break;
    }

    return Matrix<>(4, T);
}

#endif // AFFINE_TRANSFORM_H
