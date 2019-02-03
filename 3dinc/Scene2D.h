#ifndef SCENE_2D_H
#define SCENE_2D_H

//#define _USE_MATH_DEFINES
#include <math.h>
#include <string>

#include "Camera2D.h"
#include "Model2D.h"

class Scene2D : public Camera2D
{
    int modelcount;
    int currmodel;
    Model2D *model;
protected:
	Scene2D(double X0, double Y0, double px, double py);

	void render();
public:
    void addModel(Matrix<> &vert, Matrix<bool> &edg);
    void removeLastModel();
    void selectModel(int i);
    void selectNextModel();
    void selectPrevModel();
    Model2D &getModel();
};

Scene2D::Scene2D(double X0, double Y0, double px, double py) : Camera2D(X0, Y0, px, py)
{
    model = nullptr;
    modelcount = currmodel = 0;
}

void Scene2D::render() {
	// TODO render
    for (int curr = 0; curr < modelcount; ++curr) // цикл по моделькам
        for (int i = 1; i < model[curr].getEdges().getRows(); ++i) // рассматриваем только верхний треугольник матрицы
            for (int j = i + 1; j <= model[curr].getEdges().getCols(); ++j)
                if (model[curr].getEdges()(i, j)) // если в верхнетреугольной матрице стоит 1, значит проводим линию
                {
                    MoveTo(model[curr].getVertexX(i), model[curr].getVertexY(i));
                    LineTo(model[curr].getVertexX(j), model[curr].getVertexY(j));
                }
}

void Scene2D::addModel(Matrix<> &vert, Matrix<bool> &edg) // добавить модель из матрицы
{
    modelcount++;
    Model2D *temp = new Model2D[modelcount];
    for (int i = 0; i < modelcount - 1; ++i) // переопределение массива с моделями
        temp[i] = model[i];

    temp[modelcount - 1] = Model2D(vert, edg); // добавляем новую модель
    model = temp;
}

void Scene2D::removeLastModel() // удалить последнюю модель
{
    if (modelcount <= 1 || currmodel == modelcount - 1)
        return;

    modelcount--;
    Model2D *temp = new Model2D[modelcount];
    for (int i = 0; i < modelcount; ++i) // переопределение массива с моделями
        temp[i] = model[i];

    // возможно вызывать деструктор конкретной модели
    //delete model;
    model = temp;
}

void Scene2D::selectModel(int i) // выбрать модель по номеру
{
    if (i <= modelcount)
        currmodel = i;
}

void Scene2D::selectNextModel() {
    if (currmodel < modelcount - 1)
        currmodel++;
    else
        currmodel = 0;
}

void Scene2D::selectPrevModel() {
    if (currmodel > 0)
        currmodel--;
    else
        currmodel = modelcount - 1;
}

Model2D &Scene2D::getModel() {
    return model[currmodel];
}

#endif // SCENE_2D_H
