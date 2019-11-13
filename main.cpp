#include <Windows.h>

#include <string>
#include <iostream>
#include <ostream>


#include <fstream>
 
#include <QApplication>
#include <QSurfaceFormat>
#include <QVTKOpenGLNativeWidget.h>
#include "MainWindow.h"
#include <QScreen>

 

 
 
 

 

int main(int c, char** argv)
{
	try
	{
		if (c < 2)
		{
			cout << "Usage: " << argv[0] << "file.mhd" << endl;
			return EXIT_FAILURE;
		}


		QSurfaceFormat::setDefaultFormat(QVTKOpenGLNativeWidget::defaultFormat());
		QApplication app(c, argv);

		std::unique_ptr<MainWindow> mw(new MainWindow());
		mw->setWindowTitle("OPENGL NATIVE WIDGET");
		mw->move(0, 0);
		mw->resize(QApplication::primaryScreen()->size().width(), QApplication::primaryScreen()->size().height());
		mw->setWindowState(Qt::WindowMaximized);

		mw->show();
		mw->addVolumeFromFile(QString(argv[1]));
		return app.exec();
	}
	catch (std::exception& ex)
	{
		std::cerr << ex.what() << std::endl;
		return -1;
	}
	return 0;
}
