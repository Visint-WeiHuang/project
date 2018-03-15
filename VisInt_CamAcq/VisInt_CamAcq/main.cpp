#include "visint_camacq.h"
#include <QtWidgets/QApplication>
#include "SapCLassBasic.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	VisInt_CamAcq w;
	w.show();
	SapAcqDevice  *acq = new SapAcqDevice;

	return a.exec();
}
