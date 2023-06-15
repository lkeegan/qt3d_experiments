#include <QApplication>
#include <QMainWindow>
#include <QLabel>
#include <QVBoxLayout>

#include <Qt3DCore/QEntity>
#include <Qt3DRender/QCamera>
#include <Qt3DRender/QCameraLens>
#include <Qt3DCore/QTransform>
#include <Qt3DCore/QAspectEngine>

#include <Qt3DInput/QInputAspect>

#include <Qt3DRender/QRenderAspect>
#include <Qt3DRender/QGeometryRenderer>
#include <Qt3DExtras/QForwardRenderer>
#include <Qt3DExtras/QDiffuseSpecularMaterial>
#include <Qt3DExtras/QCuboidMesh>
#include <Qt3DExtras/QTorusMesh>

#include <QPropertyAnimation>

#include "qt3dwindow.h"

// #include "orbittransformcontroller.h"
#include "qorbitcameracontroller.h"


void addCubes(Qt3DCore::QEntity* rootEntity, const QColor& color, const QList<QVector3D>& positions){
    // Material
    auto *material = new Qt3DExtras::QDiffuseSpecularMaterial(rootEntity);
    material->setAmbient(color);
    for (const auto& position : positions){
        // cuboid entity
        Qt3DCore::QEntity *cuboidEntity = new Qt3DCore::QEntity(rootEntity);
        // cube mesh
        Qt3DExtras::QCuboidMesh *cuboid = new Qt3DExtras::QCuboidMesh();
        cuboidEntity->addComponent(cuboid);
        // cube transform
        Qt3DCore::QTransform *cuboidTransform = new Qt3DCore::QTransform();
        cuboidTransform->setScale(1.0f);
        cuboidTransform->setTranslation(position);
        cuboidEntity->addComponent(cuboidTransform);
        // cube material
        cuboidEntity->addComponent(material);
    }
}

Qt3DCore::QEntity *createScene()
{
    // Root entity
    Qt3DCore::QEntity *rootEntity = new Qt3DCore::QEntity;

    // Cube locations
    QList<QVector3D> positions{{5.0f, -4.0f, 0.0f}, {4.0f, -4.0f, 0.0f}, {3.0f, -4.0f, 0.0f}, {3.0f, -3.0f, 0.0f}};
    addCubes(rootEntity, QColor(255,128,0), positions);

    return rootEntity;
}

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    Qt3DExtras::Qt3DWindow *view = new Qt3DExtras::Qt3DWindow();
    QWidget *container = QWidget::createWindowContainer(view);

    Qt3DCore::QEntity *scene = createScene();

    // Camera
    Qt3DRender::QCamera *camera = view->camera();
    camera->lens()->setPerspectiveProjection(45.0f, 16.0f/9.0f, 0.1f, 1000.0f);
    camera->setPosition(QVector3D(0, 0, 40.0f));
    camera->setViewCenter(QVector3D(0, 0, 0));

    // For camera controls
    Qt3DExtras::QOrbitCameraController *camController = new Qt3DExtras::QOrbitCameraController(scene);
    camController->setLinearSpeed( 50.0f );
    camController->setLookSpeed( 180.0f );
    camController->setCamera(camera);

    view->setRootEntity(scene);
    view->show();

    QMainWindow mainWin{};
    mainWin.setCentralWidget(container);
    mainWin.show();

    return app.exec();
}
