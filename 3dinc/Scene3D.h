#ifndef LAB_3_3D_SCENE_SCENE3D_H
#define LAB_3_3D_SCENE_SCENE3D_H

#include "Camera3D.h"
#include "Model3D.h"


class Scene3D : public Camera3D
{
    Model3D *model;
    int modelcount;
    int currmodel;
public:

    Scene3D(double X0, double Y0, double px, double py);

    void render();    // отрисовка

    void apply(Matrix<> AT); // apply + project к модели
    void fullProject(); // project ко всем моделям

    void setDefPos(); // перемещает всю фигуру так, что бы центр совпадал с 000

    void addModel(Matrix<> &v, const Matrix<int> &f, const Matrix<int> &im);
    void removeLastModel();
    void selectModel(int i);
    void selectNextModel();
    void selectPrevModel();
    Model3D &getModel();
};

Scene3D::Scene3D(double X0, double Y0, double px, double py) : Camera3D(X0, Y0, px, py)
{
    model = nullptr;
    modelcount = currmodel = 0;
}

void Scene3D::render()
{
    for (int curr = 0; curr < modelcount; ++curr) // цикл по моделькам
        for (int i = 1; i < model[curr].getEdges().getRows(); ++i) // рассматриваем только верхний треугольник матрицы
            for (int j = i + 1; j <= model[curr].getEdges().getCols(); ++j)
                if (model[curr].getEdges()(i, j)) // если в верхнетреугольной матрице стоит 1, значит проводим линию
                {
                    MoveTo(model[curr].getProjVertexX(i), model[curr].getProjVertexY(i));
                    LineTo(model[curr].getProjVertexX(j), model[curr].getProjVertexY(j));
                }
}

void Scene3D::apply(Matrix<> AT) // вызывает apply и project у текущей модели
{
    model[currmodel].apply(AT);
    model[currmodel].project(WorldToProject);
}

void Scene3D::fullProject() {
    for (int i = 0; i < modelcount; i++)
        model[i].project(WorldToProject);
}

void Scene3D::setDefPos() // перемещает всю фигуру так, что бы центр совпадал с 000
{
    apply(translation3D(-model[currmodel].getOVecX(), -model[currmodel].getOVecY(), -model[currmodel].getOVecZ()));
}


void Scene3D::addModel(Matrix<> &v, const Matrix<int> &f, const Matrix<int> &im) // добавить модель из матрицы
{
    modelcount++;
    auto *temp = new Model3D[modelcount];
    for (int i = 0; i < modelcount - 1; ++i) // переопределение массива с моделями
        temp[i] = model[i];

    temp[modelcount - 1] = Model3D(v, f, im); // добавляем новую модель
    model = temp;

    model[modelcount - 1].project(WorldToProject);
    setDefPos();
}

void Scene3D::removeLastModel() // удалить последнюю модель
{
    if (modelcount <= 1 || currmodel == modelcount - 1)
        return;

    modelcount--;
    auto temp = new Model3D[modelcount];
    for (int i = 0; i < modelcount; ++i) // переопределение массива с моделями
        temp[i] = model[i];

    // возможно вызывать деструктор конкретной модели
    model = temp;
}

void Scene3D::selectModel(int i) // выбрать модель по номеру
{
    if (i <= modelcount)
        currmodel = i;
}

void Scene3D::selectNextModel() {
    if (currmodel < modelcount - 1)
        currmodel++;
    else
        currmodel = 0;
}

void Scene3D::selectPrevModel() {
    if (currmodel > 0)
        currmodel--;
    else
        currmodel = modelcount - 1;
}

Model3D &Scene3D::getModel() {
    return model[currmodel];
}

#endif //LAB_3_3D_SCENE_SCENE3D_H
