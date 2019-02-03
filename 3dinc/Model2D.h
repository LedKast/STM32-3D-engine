#ifndef MODEL2D_H
#define MODEL2D_H

//#include <string>
#include "Matrix.h"
#include "AffineTransform.h"

// Вариант #6
// предполагается, что последняя точка в модели это центр фигуры
// UPD identity заменилось на identity3D
class Model2D
{
protected:
    Matrix<> vertices;      // вершины
    Matrix<> cumulativeAT;  // накопленное аффинное преобразование
    Matrix<> initVertices;  // исходные вершины
    Matrix<bool> edges;      // ребра


public:
    Model2D() : vertices(), edges(), initVertices(), cumulativeAT(identity3D()) {}

    Model2D(Matrix<> vert, Matrix<bool> edg);
    explicit Model2D(Matrix<> vert);

    ~Model2D() = default;

    // получение координат X,Y вершины под номером i
    double getVertexX(int i) { return vertices(1, i); }
    double getVertexY(int i) { return vertices(2, i); }
    Matrix<> getVertices() { return vertices; }
    Matrix<bool> getEdges() { return edges; }

    double getOVecX() { return vertices(1, vertices.getCols()); }
    double getOVecY() { return vertices(2, vertices.getCols()); }

    void apply(Matrix<> AT);
};


Model2D::Model2D(Matrix<> vert, const Matrix<bool> edg) : edges(edg), initVertices(), cumulativeAT(identity3D())
{
    initVertices = vertices = vert;
}
Model2D::Model2D(Matrix<> vert) : edges(), initVertices(), cumulativeAT(identity3D())
{
    initVertices = vertices = vert;
}

void Model2D::apply(Matrix<> AT)
{
    cumulativeAT = AT * cumulativeAT;
    vertices = cumulativeAT * initVertices;
}

#endif // MODEL2D_H
