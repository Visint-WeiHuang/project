#ifndef CONFIGUE_PARAMETERS_H
#define CONFIGUE_PARAMETERS_H

#include <QDialog>
#include "ui_Configue_Parameters.h"

class Configue_Parameters : public QDialog
{
	Q_OBJECT

public:
	Configue_Parameters(QWidget *parent = 0);
	~Configue_Parameters();

private:
	Ui::Configue_Parameters ui;
};

#endif // CONFIGUE_PARAMETERS_H
