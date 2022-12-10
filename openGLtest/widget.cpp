#include "widget.h"
#include <QOpenGLFunctions>

Widget::Widget(QWidget *parent)
    : QOpenGLWidget(parent)
{
}

Widget::~Widget()
{
}

void Widget::initializeGL() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);    //  включаем буфер глубины
    glEnable(GL_CULL_FACE);     //  отсечение задних граней

    initCube(1);
}

void Widget::resizeGL(int w, int h) {
    float aspect = w / (float)h;
    m_projectionMatrix.setToIdentity();
    m_projectionMatrix.perspective(45, aspect, 0.1, 10.0f);
}

void Widget::paintGl() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    QMatrix4x4 modelMatrix;
    modelMatrix.setToIdentity();
    modelMatrix.translate(0, 0, -5);

    m_indexBuffer.bind();

    glDrawElements(GL_TRIANGLES, m_indexBuffer.size(), GL_UNSIGNED_INT, 0);

}

void Widget::initCube(float width)
{
    float width_div = width / 2;
    QVector<VertexData> vertexes;
    vertexes.append(VertexData(QVector3D(-width_div, width_div, width_div), QVector2D(0, 1), QVector3D(0, 0, 1)));
    vertexes.append(VertexData(QVector3D(-width_div, -width_div, width_div), QVector2D(0, 0), QVector3D(0, 0, 1)));
    vertexes.append(VertexData(QVector3D(width_div, width_div, width_div), QVector2D(1, 1), QVector3D(0, 0, 1)));
    vertexes.append(VertexData(QVector3D(width_div, -width_div, width_div), QVector2D(1, 0), QVector3D(0, 0, 1)));

    vertexes.append(VertexData(QVector3D(width_div, width_div, width_div), QVector2D(0, 1), QVector3D(1, 0, 0)));
    vertexes.append(VertexData(QVector3D(width_div, -width_div, width_div), QVector2D(0, 0), QVector3D(1, 0, 0)));
    vertexes.append(VertexData(QVector3D(width_div, width_div, -width_div), QVector2D(1, 1), QVector3D(1, 0, 0)));
    vertexes.append(VertexData(QVector3D(width_div, -width_div, -width_div), QVector2D(1, 0), QVector3D(1, 0, 0)));

    vertexes.append(VertexData(QVector3D(width_div, width_div, width_div), QVector2D(0, 1), QVector3D(0, 1, 0)));
    vertexes.append(VertexData(QVector3D(width_div, width_div, -width_div), QVector2D(0, 0), QVector3D(0, 1, 0)));
    vertexes.append(VertexData(QVector3D(-width_div, width_div, width_div), QVector2D(1, 1), QVector3D(0, 1, 0)));
    vertexes.append(VertexData(QVector3D(-width_div, width_div, -width_div), QVector2D(1, 0), QVector3D(0, 1, 0)));

    vertexes.append(VertexData(QVector3D(width_div, width_div, -width_div), QVector2D(0, 1), QVector3D(0, 1, 0)));
    vertexes.append(VertexData(QVector3D(width_div, -width_div, -width_div), QVector2D(0, 0), QVector3D(0, 1, 0)));
    vertexes.append(VertexData(QVector3D(-width_div, width_div, -width_div), QVector2D(1, 1), QVector3D(0, 1, 0)));
    vertexes.append(VertexData(QVector3D(-width_div, -width_div, -width_div), QVector2D(1, 0), QVector3D(0, 1, 0)));

    vertexes.append(VertexData(QVector3D(-width_div, width_div, width_div), QVector2D(0, 1), QVector3D(0, 1, 0)));
    vertexes.append(VertexData(QVector3D(-width_div, width_div, -width_div), QVector2D(0, 0), QVector3D(0, 1, 0)));
    vertexes.append(VertexData(QVector3D(-width_div, -width_div, width_div), QVector2D(1, 1), QVector3D(0, 1, 0)));
    vertexes.append(VertexData(QVector3D(-width_div, -width_div, -width_div), QVector2D(1, 0), QVector3D(0, 1, 0)));

    vertexes.append(VertexData(QVector3D(-width_div, -width_div, width_div), QVector2D(0, 1), QVector3D(0, 1, 0)));
    vertexes.append(VertexData(QVector3D(-width_div, -width_div, -width_div), QVector2D(0, 0), QVector3D(0, 1, 0)));
    vertexes.append(VertexData(QVector3D(width_div, -width_div, width_div), QVector2D(1, 1), QVector3D(0, 1, 0)));
    vertexes.append(VertexData(QVector3D(width_div, -width_div, -width_div), QVector2D(1, 0), QVector3D(0, 1, 0)));

    QVector<GLuint> indexes;
    for (int i = 0; i < 24; i += 4) {
        indexes.append(i + 0);
        indexes.append(i + 1);
        indexes.append(i + 2);
        indexes.append(i + 2);
        indexes.append(i + 1);
        indexes.append(i + 3);
    }

    m_arrayBuffer.create();
    m_arrayBuffer.bind();
    m_arrayBuffer.allocate(vertexes.constData(), vertexes.size() * sizeof(VertexData));
    m_arrayBuffer.release();

    m_indexBuffer.create();
    m_indexBuffer.bind();
    m_indexBuffer.allocate(indexes.constData(), indexes.size() * sizeof(GLuint));
    m_indexBuffer.release();

}
