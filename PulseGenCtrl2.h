#ifndef PULSEGENCTRL2_H
#define PULSEGENCTRL2_H

#include "bSpinBoxWidget.h"

#include<QDial>
#include <QWidget>
#include <QString>
#include <QLayout>
#include <QDial>
#include <QLineEdit>
#include <QTextEdit>
#include <QComboBox>
#include <QPushButton>
#include <QSignalMapper>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

//QT_BEGIN_NAMESPACE
//class QGroupBox;
//QT_END_NAMESPACE

class PulseGenCtrl2 : public QWidget
{
  Q_OBJECT
public:
  PulseGenCtrl2(QWidget *parent = 0);
  QString niceNumbers(int tNumber, int tRes);

private:
  int temp;
  int diff;

  QComboBox *OscVCombo;
  QComboBox *OscPCombo;
  QComboBox *OscECombo;
  QComboBox *OscTCombo;
  QComboBox *OscLCombo;
  QComboBox *OscGCombo;
  bSpinBoxWidget *OscDelaySpinBox;
  bSpinBoxWidget *OscWidthSpinBox;

  QComboBox *PG1VCombo;
  QComboBox *PG1PCombo;
  QComboBox *PG1ECombo;
  QComboBox *PG1TCombo;
  QComboBox *PG1LCombo;
  QComboBox *PG1GCombo;
  bSpinBoxWidget *PG1DelaySpinBox;
  bSpinBoxWidget *PG1WidthSpinBox;

  QComboBox *PG2VCombo;
  QComboBox *PG2PCombo;
  QComboBox *PG2ECombo;
  QComboBox *PG2TCombo;
  QComboBox *PG2LCombo;
  QComboBox *PG2GCombo;
  bSpinBoxWidget *PG2DelaySpinBox;
  bSpinBoxWidget *PG2WidthSpinBox;

  QComboBox *PG3VCombo;
  QComboBox *PG3PCombo;
  QComboBox *PG3ECombo;
  QComboBox *PG3TCombo;
  QComboBox *PG3LCombo;
  QComboBox *PG3GCombo;
  bSpinBoxWidget *PG3DelaySpinBox;
  bSpinBoxWidget *PG3WidthSpinBox;

  QComboBox *PG4VCombo;
  QComboBox *PG4PCombo;
  QComboBox *PG4ECombo;
  QComboBox *PG4TCombo;
  QComboBox *PG4LCombo;
  QComboBox *PG4GCombo;
  bSpinBoxWidget *PG4DelaySpinBox;
  bSpinBoxWidget *PG4WidthSpinBox;


  QComboBox *ModVCombo;
  QComboBox *ModPCombo;
  QComboBox *ModECombo;
  QComboBox *ModTCombo;
  QComboBox *ModLCombo;
  QComboBox *ModGCombo;
  bSpinBoxWidget *ModEndSpinBox;

  QComboBox *CntVCombo;
  QComboBox *CntPCombo;
  QComboBox *CntECombo;
  QComboBox *CntTCombo;
  QComboBox *CntLCombo;
  QComboBox *CntGCombo;
  bSpinBoxWidget *CntCSpinBox;

  QPushButton *Status;
  QPushButton *Help;
  QComboBox *YapCombo;
  QComboBox *ComPortCombo;

  QTextEdit *received_msg;
  QString transmit_msg;
  QSerialPort *serial;

  QString ComPortSelected;


public slots:
  void changeModEndSpinBox(int tModEndSpinBox);
  void SendData(QString);
  void SelectComPort(int);
  void openSerialPort();
  void closeSerialPort();
  void transmitMsg();
  void readData();
  void waitIn();
  void handleError(QSerialPort::SerialPortError error);
};

#endif


