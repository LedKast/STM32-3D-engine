#ifndef LAB_3_3D_SCENE_MODEL3D_H
#define LAB_3_3D_SCENE_MODEL3D_H

#include "Model2D.h"
#include "Matrix.h"

// наследует Model2D
class Model3D : public Model2D
{
    // vertices, cumulativeAT, initVertices, edges - в классе Model2D
    Matrix<> projVertices;
    Matrix<int> faces;
    Matrix<int> imEdges; // мнимые рёбра. матрица 2xM, где М - кол-во мнимых рёбер

    // создание карты рёбер по заданной карте граней
    void setEdges();

public:
    Model3D() : Model2D(), faces(), projVertices(), imEdges() { }

    // конструктор создания модели по заданным карте вершин и карте граней
    Model3D(const Matrix<> &v, const Matrix<int> &f, const Matrix<int> &im);

    Matrix<int> getFaces() { return faces; }
    double getVertexZ(int i) { return vertices(3, i); }

    double getProjVertexX(int i) { return projVertices(1, i) / getProjVertexZ(i); }
    double getProjVertexY(int i) { return projVertices(2, i) / getProjVertexZ(i); }
    double getProjVertexZ(int i) { return projVertices(3, i); }

    double getOVecZ() { return vertices(3, vertices.getCols()); }

    void project(Matrix<> P) { projVertices = P * vertices; } // проецирование модели.
};

void Model3D::setEdges() {
    edges = Matrix<bool>(faces.getRows());
    for (int i = 1; i <= faces.getRows(); ++i)
        for (int j = 1; j <= 2; ++j) {
            edges(faces(i, j), faces(i, j + 1), 1);
            edges(faces(i, j + 1), faces(i, j), 1);
        }
    for (int i = 1; i <= imEdges.getRows(); ++i)
    {
        edges(imEdges(i, 1), imEdges(i, 2), 0);
        edges(imEdges(i, 2), imEdges(i, 1), 0);
    }
}

Model3D::Model3D(const Matrix<> &v, const Matrix<int> &f, const Matrix<int> &im) :
        Model2D(v), faces(f), projVertices(), imEdges(im)
{
    setEdges();
}


#endif //LAB_3_3D_SCENE_MODEL3D_H
