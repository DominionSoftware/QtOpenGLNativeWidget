#include "MainWindow.h"
#include <QDockWidget>
#include <QHBoxLayout>
#include <QVTKOpenGLNativeWidget.h>
#include <vtkRenderWindow.h>
#include <vtkRendererCollection.h>
#include <vtkNamedColors.h>
#include <vtkMetaImageReader.h>
#include <vtkVolumeProperty.h>
#include <QPushButton>
#include <QFileDialog>
#include "vtkCamera.h"


MainWindow::MainWindow()
{
	 
	window1 = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
	window2 = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();

	renderer1 = vtkSmartPointer < vtkRenderer>::New();
	renderer2 = vtkSmartPointer < vtkRenderer>::New();
	window1->AddRenderer(renderer1);
	window2->AddRenderer(renderer2);
    vtkWidget1 = new QVTKOpenGLNativeWidget();
	vtkWidget1->SetRenderWindow(window1);
	vtkWidget2 = new QVTKOpenGLNativeWidget();
	vtkWidget2->SetRenderWindow(window2);
	mainSplitter = new QSplitter(this);
	this->setCentralWidget(mainSplitter);
	mainSplitter->setObjectName(QStringLiteral("mainWindowSplitter"));
	mainSplitter->show();

	mainSplitter->addWidget(vtkWidget1);
	mainSplitter->addWidget(vtkWidget2);

 
}

 
void MainWindow::loadImage(const QString& pathName)
{
	vtkSmartPointer<vtkMetaImageReader> metaReader = vtkSmartPointer<vtkMetaImageReader>::New();
	metaReader->SetFileName(pathName.toStdString().c_str());
	metaReader->Update();
	vtkImageData* imageData = metaReader->GetOutput();
	colorTransferFunction = vtkSmartPointer<vtkColorTransferFunction>::New();
	colorTransferFunction->AddRGBPoint(0, 0.0, 0.0, 0.0);
	colorTransferFunction->AddRGBPoint(500, 1.0, 0.5, 0.3);
	colorTransferFunction->AddRGBPoint(1000, 1.0, 0.5, 0.3);
	colorTransferFunction->AddRGBPoint(1150, 1.0, 1.0, 0.9);
	opacityTransferFunction = vtkSmartPointer<vtkPiecewiseFunction>::New();
	opacityTransferFunction->AddPoint(0, 0.00);
	opacityTransferFunction->AddPoint(500, 0.15);
	opacityTransferFunction->AddPoint(1000, 0.15);
	opacityTransferFunction->AddPoint(1150, 0.85);
	volumeGradientOpacityFunction = vtkSmartPointer<vtkPiecewiseFunction>::New();
	volumeGradientOpacityFunction->AddPoint(0, 0.0);
	volumeGradientOpacityFunction->AddPoint(90, 0.5);
	volumeGradientOpacityFunction->AddPoint(100, 1.0);
	vtkSmartPointer<vtkVolumeProperty> volumeProperty = vtkSmartPointer<vtkVolumeProperty>::New();


	volumeProperty->SetScalarOpacity(opacityTransferFunction);
	volumeProperty->SetColor(colorTransferFunction);
	volumeProperty->SetGradientOpacity(volumeGradientOpacityFunction);
	volumeProperty->SetInterpolationTypeToLinear();
	volumeProperty->ShadeOn();
	volumeProperty->SetAmbient(0.4);
	volumeProperty->SetDiffuse(0.8);
	volumeProperty->SetSpecular(0.2);
	volumeProperty->SetSpecularPower(105.0);
	volumeProperty->SetScalarOpacityUnitDistance(0.7);

	volume =
		vtkSmartPointer<vtkVolume>::New();
	volumeMapper = vtkSmartPointer<vtkSmartVolumeMapper>::New();

	volume->SetMapper(volumeMapper);
	volume->SetProperty(volumeProperty);

	 
	volumeMapper->SetInputData(imageData);
	volume->SetMapper(volumeMapper);
	volume->Update();
}

void MainWindow::addVolumeFromFile(const QString & pathName)
{
	loadImage(pathName);

	 
	
	renderer1->AddVolume(volume);
	volume->SetVisibility(true);
	vtkCamera * camera = renderer1->GetActiveCamera();
	double* c = volume->GetCenter();
	camera->SetViewUp(0, 0, -1);
	camera->SetPosition(c[0], c[1] - 400, c[2]);
	camera->SetFocalPoint(c[0], c[1], c[2]);
	camera->Azimuth(30.0);
	camera->Elevation(30.0);
	renderer1->Render();
}