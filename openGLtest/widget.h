#ifndef WIDGET_H
#define WIDGET_H

#include <QtOpenGLWidgets/QtOpenGLWidgets>
#include <QMatrix4x4>

struct VertexData {
    VertexData() {

    }
    VertexData(QVector3D p, QVector2D t, QVector3D n) :
        position(p), texCoord(t), normal(n) {}
    QVector3D position;
    QVector2D texCoord;
    QVector3D normal;
};

class Widget : public QOpenGLWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGl();

    void initCube(float width);

private:
    QMatrix4x4 m_projectionMatrix;
    QOpenGLBuffer m_arrayBuffer;
    QOpenGLBuffer m_indexBuffer;

};
#endif // WIDGET_H
