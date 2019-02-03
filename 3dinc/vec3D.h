#ifndef LAB_3_3D_SCENE_VEC3_H
#define LAB_3_3D_SCENE_VEC3_H

#include "Matrix.h"

// вектор размером 1x3
template <typename Cell = double>
class vec3D : public Matrix<Cell>
{
public:
    vec3D() : Matrix<Cell>(1, 3)
    {  }
    vec3D(Cell* list) : Matrix<Cell>(1, 3, list)
    {  }
    vec3D(const vec3D<Cell>& V) : Matrix<Cell>(V)
    {  }
    vec3D(const Matrix<Cell>& M) : Matrix<Cell>(M)
    {  }

    inline Cell operator()(int i) { // получение значения из вектора
        return (i >= 0 && i <= 3) ? this->cells[0][i-1] : -1;
    }

    // задание значения вектора
    inline void operator() (int i, Cell data) { this->cells[0][i-1] = data; }

    double scalarprod(vec3D<Cell> right) // скалярное произведение
    {
        double sprod = 0;
        for (int i = 0; i < 3; ++i)
            sprod += this->cells[0][i]*right.cells[0][i];
        return sprod;
    }

    vec3D<Cell> vecprod(vec3D<Cell> right) // векторное произведение
    {
        vec3D<Cell> temp;
        temp(1, this->cells[0][1]*right.cells[0][2] - this->cells[0][2]*right.cells[0][1]);
        temp(2, -(this->cells[0][0]*right.cells[0][2] - this->cells[0][2]*right.cells[0][0]));
        temp(3, this->cells[0][0]*right.cells[0][1] - this->cells[0][1]*right.cells[0][0]);

        return temp;
    }
};


#endif //LAB_3_3D_SCENE_VEC3_H
