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
#include "qorbitcameracontroller.h"

#include "sme/model.hpp"
#include "sme/image_stack.hpp"

Qt3DCore::QEntity *createScene(const sme::common::ImageStack& imageStack){
    Qt3DCore::QEntity *rootEntity = new Qt3DCore::QEntity;

    // for (std::size_t iz=0; iz<imageStack.volume().depth(); ++iz){
    //     for(int iy=0; iy<imageStack.volume().height(); ++iy){
    //         for(int ix=0; ix<imageStack.volume().width(); ++ix){


    for (std::size_t iz=10; iz<20; ++iz){
     for(int iy=20; iy<30; ++iy){
        for(int ix=20; ix<30; ++ix){
                // material with color
                auto *material = new Qt3DExtras::QDiffuseSpecularMaterial(rootEntity);
                material->setAmbient(imageStack[iz].pixelColor(ix, iy));
                // cuboid entity
                Qt3DCore::QEntity *cuboidEntity = new Qt3DCore::QEntity(rootEntity);
                // cube mesh
                Qt3DExtras::QCuboidMesh *cuboid = new Qt3DExtras::QCuboidMesh();
                cuboidEntity->addComponent(cuboid);
                // cube transform
                Qt3DCore::QTransform *cuboidTransform = new Qt3DCore::QTransform();
                cuboidTransform->setScale(1.0f);
                cuboidTransform->setTranslation({static_cast<float>(ix),static_cast<float>(iy),static_cast<float>(iz)});
                cuboidEntity->addComponent(cuboidTransform);
                // cube material
                cuboidEntity->addComponent(material);
            }
        }
    }
    return rootEntity;
}

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    sme::model::Model model{};
    model.importFile(argv[1]);

    Qt3DExtras::Qt3DWindow *view = new Qt3DExtras::Qt3DWindow();
    QWidget *view_container = QWidget::createWindowContainer(view);

    Qt3DCore::QEntity *scene = createScene(model.getGeometry().getImages());

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
    mainWin.setCentralWidget(view_container);
    mainWin.show();

    return app.exec();
}
