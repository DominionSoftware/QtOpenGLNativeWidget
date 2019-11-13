
#pragma once
#include <QMainWindow>
#include <QSplitter>
 
 
#include <vtkPiecewiseFunction.h>
#include <vtkColorTransferFunction.h>
#include <vtkGenericOpenGLRenderWindow.h>
 
#include <vtkSmartVolumeMapper.h>
 
 
#include <QVTKOpenGLNativeWidget.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
	void addVolumeFromFile(const QString & pathName);
    

   

 

private:
    
	void loadImage(const QString & pathName);
	QWidget * centralWidget = nullptr;
	QSplitter * mainSplitter = nullptr;

	QVTKOpenGLNativeWidget* vtkWidget1 = nullptr;
	QVTKOpenGLNativeWidget* vtkWidget2 = nullptr;

	vtkSmartPointer<vtkGenericOpenGLRenderWindow> window1;
	vtkSmartPointer<vtkGenericOpenGLRenderWindow> window2;
	vtkSmartPointer < vtkRenderer> renderer1;
	vtkSmartPointer < vtkRenderer> renderer2;

	
	vtkSmartPointer<vtkVolume> volume;
	vtkSmartPointer<vtkSmartVolumeMapper> volumeMapper;
	vtkSmartPointer<vtkPiecewiseFunction> opacityTransferFunction;
	vtkSmartPointer<vtkColorTransferFunction> colorTransferFunction;
	vtkSmartPointer<vtkPiecewiseFunction> volumeGradientOpacityFunction;
};
