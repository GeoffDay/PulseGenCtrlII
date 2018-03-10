#include "PulseGenCtrl2.h"

#include <QtGui>
#include <QFile>
#include <QLabel>
#include <QTimer>
#include <QDebug>
#include <QString>
#include <QRegExp>
#include <QGroupBox>
#include <QMessageBox>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>



PulseGenCtrl2::PulseGenCtrl2(QWidget *parent)
 : QWidget(parent)
{
    setMouseTracking(true);
    setAttribute(Qt::WA_Hover);
    ComPortSelected = "COM1";
    QFile qss("stylesheyet.qss");
    qss.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(qss.readAll());
    qApp->setStyleSheet(styleSheet);

    diff = 0;

    QSignalMapper *signalMapper = new QSignalMapper(this);

    /************************************ Osc *******************************/

    QGroupBox *OscGBox = new QGroupBox(tr("Retriggerable Osc"));
    OscGBox->setObjectName("Osc");

//    connect(OscGBox, SIGNAL()

    QLabel *OscOutLabel = new QLabel("Out:");
    OscVCombo = new QComboBox;
//    OscVCombo->addItem(tr("Off"));
    OscVCombo->addItem(tr("3V "));
    OscVCombo->addItem(tr("5V "));

    connect(OscVCombo, SIGNAL(currentIndexChanged(int)), signalMapper, SLOT(map()));
    signalMapper->setMapping(OscVCombo, "V0");

    OscPCombo = new QComboBox;
    OscPCombo->addItem(tr("Comp"));
    OscPCombo->addItem(tr("Norm"));

    connect(OscPCombo, SIGNAL(currentIndexChanged(int)), signalMapper, SLOT(map()));
    signalMapper->setMapping(OscPCombo, "P0");

    QLabel *OscTrigLabel = new QLabel("Trig:");

    OscECombo = new QComboBox(this);
    OscECombo->addItem(tr("- edge"));
    OscECombo->addItem(tr("+ edge"));

    connect(OscECombo, SIGNAL(currentIndexChanged(int)), signalMapper, SLOT(map()));
    signalMapper->setMapping(OscECombo, "E0");

    OscTCombo = new QComboBox(this);
    OscTCombo->addItem(tr(" Osc"));
    OscTCombo->addItem(tr(" PG1"));
    OscTCombo->addItem(tr(" PG2"));
    OscTCombo->addItem(tr(" PG3"));
    OscTCombo->addItem(tr(" PG4"));
    OscTCombo->addItem(tr(" Mod"));
    OscTCombo->addItem(tr(" Cnt"));
    OscTCombo->addItem(tr(" InA"));
    OscTCombo->addItem(tr(" InB"));
    OscTCombo->addItem(tr(" InC"));

    connect(OscTCombo, SIGNAL(currentIndexChanged(int)), signalMapper, SLOT(map()));
    signalMapper->setMapping(OscTCombo, "T0");

    QLabel *OscGateLabel = new QLabel("Gate:");

    OscLCombo = new QComboBox(this);
    OscLCombo->addItem(tr("Low"));
    OscLCombo->addItem(tr("Hi "));

    connect(OscLCombo, SIGNAL(currentIndexChanged(int)), signalMapper, SLOT(map()));
    signalMapper->setMapping(OscLCombo, "L0");

    OscGCombo = new QComboBox(this);
    OscGCombo->addItem(tr(" Osc"));
    OscGCombo->addItem(tr(" PG1"));
    OscGCombo->addItem(tr(" PG2"));
    OscGCombo->addItem(tr(" PG3"));
    OscGCombo->addItem(tr(" PG4"));
    OscGCombo->addItem(tr(" Mod"));
    OscGCombo->addItem(tr(" Cnt"));
    OscGCombo->addItem(tr(" InA"));
    OscGCombo->addItem(tr(" InB"));
    OscGCombo->addItem(tr(" InC"));

    connect(OscGCombo, SIGNAL(currentIndexChanged(int)), signalMapper, SLOT(map()));
    signalMapper->setMapping(OscGCombo, "G0");


    OscDelaySpinBox = new bSpinBoxWidget(this);
    OscDelaySpinBox->setGBName("Delay");
    connect(OscDelaySpinBox, SIGNAL(valueChanged(int)), signalMapper, SLOT(map()));
    signalMapper->setMapping(OscDelaySpinBox, "D0");

    OscWidthSpinBox = new bSpinBoxWidget(this);
    OscWidthSpinBox->setGBName("Width");
    connect(OscWidthSpinBox, SIGNAL(valueChanged(int)), signalMapper, SLOT(map()));
    signalMapper->setMapping(OscWidthSpinBox, "W0");

    QGridLayout *ctrls0Layout = new QGridLayout;
    ctrls0Layout->addWidget(OscOutLabel     , 0, 0, 1, 1);
    ctrls0Layout->addWidget(OscVCombo       , 0, 1, 1, 1);
    ctrls0Layout->addWidget(OscPCombo       , 0, 2, 1, 1);
    ctrls0Layout->addWidget(OscTrigLabel    , 1, 0, 1, 1);
    ctrls0Layout->addWidget(OscECombo       , 1, 1, 1, 1);
    ctrls0Layout->addWidget(OscTCombo       , 1, 2, 1, 1);
    ctrls0Layout->addWidget(OscGateLabel    , 2, 0, 1, 1);
    ctrls0Layout->addWidget(OscLCombo       , 2, 1, 1, 1);
    ctrls0Layout->addWidget(OscGCombo       , 2, 2, 1, 1);
    ctrls0Layout->addWidget(OscDelaySpinBox , 3, 0, 3, 3);
    ctrls0Layout->addWidget(OscWidthSpinBox , 6, 0, 3, 3);

    OscGBox->setLayout(ctrls0Layout);

    /************************************ PG1 *******************************/

    QGroupBox *PG1GBox = new QGroupBox(tr("PG1"));
    PG1GBox->setObjectName("PG1");

    QLabel *PG1OutLabel = new QLabel("Out:");
    PG1VCombo = new QComboBox;
    PG1VCombo->addItem(tr("Off"));
    PG1VCombo->addItem(tr("3V "));
    PG1VCombo->addItem(tr("5V "));

    connect(PG1VCombo, SIGNAL(currentIndexChanged(int)), signalMapper, SLOT(map()));
    signalMapper->setMapping(PG1VCombo, "V1");

    PG1PCombo = new QComboBox;
    PG1PCombo->addItem(tr("Comp"));
    PG1PCombo->addItem(tr("Norm"));

    connect(PG1PCombo, SIGNAL(currentIndexChanged(int)), signalMapper, SLOT(map()));
    signalMapper->setMapping(PG1PCombo, "P1");

    QLabel *PG1TrigLabel = new QLabel("Trig:");

    PG1ECombo = new QComboBox(this);
    PG1ECombo->addItem(tr("- edge"));
    PG1ECombo->addItem(tr("+ edge"));

    connect(PG1ECombo, SIGNAL(currentIndexChanged(int)), signalMapper, SLOT(map()));
    signalMapper->setMapping(PG1ECombo, "E1");

    PG1TCombo = new QComboBox(this);
    PG1TCombo->addItem(tr(" Osc"));
    PG1TCombo->addItem(tr(" PG1"));
    PG1TCombo->addItem(tr(" PG2"));
    PG1TCombo->addItem(tr(" PG3"));
    PG1TCombo->addItem(tr(" PG4"));
    PG1TCombo->addItem(tr(" Mod"));
    PG1TCombo->addItem(tr(" Cnt"));
    PG1TCombo->addItem(tr(" InA"));
    PG1TCombo->addItem(tr(" InB"));
    PG1TCombo->addItem(tr(" InC"));

    connect(PG1TCombo, SIGNAL(currentIndexChanged(int)), signalMapper, SLOT(map()));
    signalMapper->setMapping(PG1TCombo, "T1");

    QLabel *PG1GateLabel = new QLabel("Gate:");

    PG1LCombo = new QComboBox(this);
    PG1LCombo->addItem(tr("Low"));
    PG1LCombo->addItem(tr("Hi "));

    connect(PG1LCombo, SIGNAL(currentIndexChanged(int)), signalMapper, SLOT(map()));
    signalMapper->setMapping(PG1LCombo, "L1");

    PG1GCombo = new QComboBox(this);
    PG1GCombo->addItem(tr(" Osc"));
    PG1GCombo->addItem(tr(" PG1"));
    PG1GCombo->addItem(tr(" PG2"));
    PG1GCombo->addItem(tr(" PG3"));
    PG1GCombo->addItem(tr(" PG4"));
    PG1GCombo->addItem(tr(" Mod"));
    PG1GCombo->addItem(tr(" Cnt"));
    PG1GCombo->addItem(tr(" InA"));
    PG1GCombo->addItem(tr(" InB"));
    PG1GCombo->addItem(tr(" InC"));

    connect(PG1GCombo, SIGNAL(currentIndexChanged(int)), signalMapper, SLOT(map()));
    signalMapper->setMapping(PG1GCombo, "G1");


    PG1DelaySpinBox = new bSpinBoxWidget(this);
    PG1DelaySpinBox->setGBName("Delay");
    connect(PG1DelaySpinBox, SIGNAL(valueChanged(int)), signalMapper, SLOT(map()));
    signalMapper->setMapping(PG1DelaySpinBox, "D1");

    PG1WidthSpinBox = new bSpinBoxWidget(this);
    PG1WidthSpinBox->setGBName("Width");
    connect(PG1WidthSpinBox, SIGNAL(valueChanged(int)), signalMapper, SLOT(map()));
    signalMapper->setMapping(PG1WidthSpinBox, "W1");

    QGridLayout *ctrls1Layout = new QGridLayout;
    ctrls1Layout->addWidget(PG1OutLabel     , 0, 0, 1, 1);
    ctrls1Layout->addWidget(PG1VCombo       , 0, 1, 1, 1);
    ctrls1Layout->addWidget(PG1PCombo       , 0, 2, 1, 1);
    ctrls1Layout->addWidget(PG1TrigLabel    , 1, 0, 1, 1);
    ctrls1Layout->addWidget(PG1ECombo       , 1, 1, 1, 1);
    ctrls1Layout->addWidget(PG1TCombo       , 1, 2, 1, 1);
    ctrls1Layout->addWidget(PG1GateLabel    , 2, 0, 1, 1);
    ctrls1Layout->addWidget(PG1LCombo       , 2, 1, 1, 1);
    ctrls1Layout->addWidget(PG1GCombo       , 2, 2, 1, 1);
    ctrls1Layout->addWidget(PG1DelaySpinBox , 3, 0, 3, 3);
    ctrls1Layout->addWidget(PG1WidthSpinBox , 6, 0, 3, 3);

    PG1GBox->setLayout(ctrls1Layout);


    /************************************ PG2 *******************************/

    QGroupBox *PG2GBox = new QGroupBox(tr("PG2"));
    PG2GBox->setObjectName("PG2");

    QLabel *PG2OutLabel = new QLabel("Out:");
    PG2VCombo = new QComboBox;
    PG2VCombo->addItem(tr("Off"));
    PG2VCombo->addItem(tr("3V "));
    PG2VCombo->addItem(tr("5V "));

    connect(PG2VCombo, SIGNAL(currentIndexChanged(int)), signalMapper, SLOT(map()));
    signalMapper->setMapping(PG2VCombo, "V2");

    PG2PCombo = new QComboBox;
    PG2PCombo->addItem(tr("Comp"));
    PG2PCombo->addItem(tr("Norm"));

    connect(PG2PCombo, SIGNAL(currentIndexChanged(int)), signalMapper, SLOT(map()));
    signalMapper->setMapping(PG2PCombo, "P2");

    QLabel *PG2TrigLabel = new QLabel("Trig:");

    PG2ECombo = new QComboBox(this);
    PG2ECombo->addItem(tr("- edge"));
    PG2ECombo->addItem(tr("+ edge"));

    connect(PG2ECombo, SIGNAL(currentIndexChanged(int)), signalMapper, SLOT(map()));
    signalMapper->setMapping(PG2ECombo, "E2");

    PG2TCombo = new QComboBox(this);
    PG2TCombo->addItem(tr(" Osc"));
    PG2TCombo->addItem(tr(" PG1"));
    PG2TCombo->addItem(tr(" PG2"));
    PG2TCombo->addItem(tr(" PG3"));
    PG2TCombo->addItem(tr(" PG4"));
    PG2TCombo->addItem(tr(" Mod"));
    PG2TCombo->addItem(tr(" Cnt"));
    PG2TCombo->addItem(tr(" InA"));
    PG2TCombo->addItem(tr(" InB"));
    PG2TCombo->addItem(tr(" InC"));

    connect(PG2TCombo, SIGNAL(currentIndexChanged(int)), signalMapper, SLOT(map()));
    signalMapper->setMapping(PG2TCombo, "T2");

    QLabel *PG2GateLabel = new QLabel("Gate:");

    PG2LCombo = new QComboBox(this);
    PG2LCombo->addItem(tr("Low"));
    PG2LCombo->addItem(tr("Hi "));

    connect(PG2LCombo, SIGNAL(currentIndexChanged(int)), signalMapper, SLOT(map()));
    signalMapper->setMapping(PG2LCombo, "L2");

    PG2GCombo = new QComboBox(this);
    PG2GCombo->addItem(tr(" Osc"));
    PG2GCombo->addItem(tr(" PG1"));
    PG2GCombo->addItem(tr(" PG2"));
    PG2GCombo->addItem(tr(" PG3"));
    PG2GCombo->addItem(tr(" PG4"));
    PG2GCombo->addItem(tr(" Mod"));
    PG2GCombo->addItem(tr(" Cnt"));
    PG2GCombo->addItem(tr(" InA"));
    PG2GCombo->addItem(tr(" InB"));
    PG2GCombo->addItem(tr(" InC"));

    connect(PG2GCombo, SIGNAL(currentIndexChanged(int)), signalMapper, SLOT(map()));
    signalMapper->setMapping(PG2GCombo, "G2");


    PG2DelaySpinBox = new bSpinBoxWidget(this);
    PG2DelaySpinBox->setGBName("Delay");
    connect(PG2DelaySpinBox, SIGNAL(valueChanged(int)), signalMapper, SLOT(map()));
    signalMapper->setMapping(PG2DelaySpinBox, "D2");

    PG2WidthSpinBox = new bSpinBoxWidget(this);
    PG2WidthSpinBox->setGBName("Width");
    connect(PG2WidthSpinBox, SIGNAL(valueChanged(int)), signalMapper, SLOT(map()));
    signalMapper->setMapping(PG2WidthSpinBox, "W2");

    QGridLayout *ctrls2Layout = new QGridLayout;
    ctrls2Layout->addWidget(PG2OutLabel     , 0, 0, 1, 1);
    ctrls2Layout->addWidget(PG2VCombo       , 0, 1, 1, 1);
    ctrls2Layout->addWidget(PG2PCombo       , 0, 2, 1, 1);
    ctrls2Layout->addWidget(PG2TrigLabel    , 1, 0, 1, 1);
    ctrls2Layout->addWidget(PG2ECombo       , 1, 1, 1, 1);
    ctrls2Layout->addWidget(PG2TCombo       , 1, 2, 1, 1);
    ctrls2Layout->addWidget(PG2GateLabel    , 2, 0, 1, 1);
    ctrls2Layout->addWidget(PG2LCombo       , 2, 1, 1, 1);
    ctrls2Layout->addWidget(PG2GCombo       , 2, 2, 1, 1);
    ctrls2Layout->addWidget(PG2DelaySpinBox , 3, 0, 3, 3);
    ctrls2Layout->addWidget(PG2WidthSpinBox , 6, 0, 3, 3);

    PG2GBox->setLayout(ctrls2Layout);

    /************************************ PG3 *******************************/

    QGroupBox *PG3GBox = new QGroupBox(tr("PG3"));
    PG3GBox->setObjectName("PG3");

    QLabel *PG3OutLabel = new QLabel("Out:");
    PG3VCombo = new QComboBox;
    PG3VCombo->addItem(tr("Off"));
    PG3VCombo->addItem(tr("3V "));
    PG3VCombo->addItem(tr("5V "));

    connect(PG3VCombo, SIGNAL(currentIndexChanged(int)), signalMapper, SLOT(map()));
    signalMapper->setMapping(PG3VCombo, "V3");

    PG3PCombo = new QComboBox;
    PG3PCombo->addItem(tr("Comp"));
    PG3PCombo->addItem(tr("Norm"));

    connect(PG3PCombo, SIGNAL(currentIndexChanged(int)), signalMapper, SLOT(map()));
    signalMapper->setMapping(PG3PCombo, "P3");

    QLabel *PG3TrigLabel = new QLabel("Trig:");

    PG3ECombo = new QComboBox(this);
    PG3ECombo->addItem(tr("- edge"));
    PG3ECombo->addItem(tr("+ edge"));

    connect(PG3ECombo, SIGNAL(currentIndexChanged(int)), signalMapper, SLOT(map()));
    signalMapper->setMapping(PG3ECombo, "E3");

    PG3TCombo = new QComboBox(this);
    PG3TCombo->addItem(tr(" Osc"));
    PG3TCombo->addItem(tr(" PG1"));
    PG3TCombo->addItem(tr(" PG2"));
    PG3TCombo->addItem(tr(" PG3"));
    PG3TCombo->addItem(tr(" PG4"));
    PG3TCombo->addItem(tr(" Mod"));
    PG3TCombo->addItem(tr(" Cnt"));
    PG3TCombo->addItem(tr(" InA"));
    PG3TCombo->addItem(tr(" InB"));
    PG3TCombo->addItem(tr(" InC"));

    connect(PG3TCombo, SIGNAL(currentIndexChanged(int)), signalMapper, SLOT(map()));
    signalMapper->setMapping(PG3TCombo, "T3");

    QLabel *PG3GateLabel = new QLabel("Gate:");

    PG3LCombo = new QComboBox(this);
    PG3LCombo->addItem(tr("Low"));
    PG3LCombo->addItem(tr("Hi "));

    connect(PG3LCombo, SIGNAL(currentIndexChanged(int)), signalMapper, SLOT(map()));
    signalMapper->setMapping(PG3LCombo, "L3");

    PG3GCombo = new QComboBox(this);
    PG3GCombo->addItem(tr(" Osc"));
    PG3GCombo->addItem(tr(" PG1"));
    PG3GCombo->addItem(tr(" PG2"));
    PG3GCombo->addItem(tr(" PG3"));
    PG3GCombo->addItem(tr(" PG4"));
    PG3GCombo->addItem(tr(" Mod"));
    PG3GCombo->addItem(tr(" Cnt"));
    PG3GCombo->addItem(tr(" InA"));
    PG3GCombo->addItem(tr(" InB"));
    PG3GCombo->addItem(tr(" InC"));

    connect(PG3GCombo, SIGNAL(currentIndexChanged(int)), signalMapper, SLOT(map()));
    signalMapper->setMapping(PG3GCombo, "G3");


    PG3DelaySpinBox = new bSpinBoxWidget(this);
    PG3DelaySpinBox->setGBName("Delay");
    connect(PG3DelaySpinBox, SIGNAL(valueChanged(int)), signalMapper, SLOT(map()));
    signalMapper->setMapping(PG3DelaySpinBox, "D3");

    PG3WidthSpinBox = new bSpinBoxWidget(this);
    PG3WidthSpinBox->setGBName("Width");
    connect(PG3WidthSpinBox, SIGNAL(valueChanged(int)), signalMapper, SLOT(map()));
    signalMapper->setMapping(PG3WidthSpinBox, "W3");

    QGridLayout *ctrls3Layout = new QGridLayout;
    ctrls3Layout->addWidget(PG3OutLabel     , 0, 0, 1, 1);
    ctrls3Layout->addWidget(PG3VCombo       , 0, 1, 1, 1);
    ctrls3Layout->addWidget(PG3PCombo       , 0, 2, 1, 1);
    ctrls3Layout->addWidget(PG3TrigLabel    , 1, 0, 1, 1);
    ctrls3Layout->addWidget(PG3ECombo       , 1, 1, 1, 1);
    ctrls3Layout->addWidget(PG3TCombo       , 1, 2, 1, 1);
    ctrls3Layout->addWidget(PG3GateLabel    , 2, 0, 1, 1);
    ctrls3Layout->addWidget(PG3LCombo       , 2, 1, 1, 1);
    ctrls3Layout->addWidget(PG3GCombo       , 2, 2, 1, 1);
    ctrls3Layout->addWidget(PG3DelaySpinBox , 3, 0, 3, 3);
    ctrls3Layout->addWidget(PG3WidthSpinBox , 6, 0, 3, 3);

    PG3GBox->setLayout(ctrls3Layout);

    /************************************ PG4 *******************************/

    QGroupBox *PG4GBox = new QGroupBox(tr("PG4"));
    PG4GBox->setObjectName("PG4");

    QLabel *PG4OutLabel = new QLabel("Out:");
    PG4VCombo = new QComboBox;
    PG4VCombo->addItem(tr("Off"));
    PG4VCombo->addItem(tr("3V "));
    PG4VCombo->addItem(tr("5V "));

    connect(PG4VCombo, SIGNAL(currentIndexChanged(int)), signalMapper, SLOT(map()));
    signalMapper->setMapping(PG4VCombo, "V4");

    PG4PCombo = new QComboBox;
    PG4PCombo->addItem(tr("Comp"));
    PG4PCombo->addItem(tr("Norm"));

    connect(PG4PCombo, SIGNAL(currentIndexChanged(int)), signalMapper, SLOT(map()));
    signalMapper->setMapping(PG4PCombo, "P4");

    QLabel *PG4TrigLabel = new QLabel("Trig:");

    PG4ECombo = new QComboBox(this);
    PG4ECombo->addItem(tr("- edge"));
    PG4ECombo->addItem(tr("+ edge"));

    connect(PG4ECombo, SIGNAL(currentIndexChanged(int)), signalMapper, SLOT(map()));
    signalMapper->setMapping(PG4ECombo, "E4");

    PG4TCombo = new QComboBox(this);
    PG4TCombo->addItem(tr(" Osc"));
    PG4TCombo->addItem(tr(" PG1"));
    PG4TCombo->addItem(tr(" PG2"));
    PG4TCombo->addItem(tr(" PG3"));
    PG4TCombo->addItem(tr(" PG4"));
    PG4TCombo->addItem(tr(" Mod"));
    PG4TCombo->addItem(tr(" Cnt"));
    PG4TCombo->addItem(tr(" InA"));
    PG4TCombo->addItem(tr(" InB"));
    PG4TCombo->addItem(tr(" InC"));

    connect(PG4TCombo, SIGNAL(currentIndexChanged(int)), signalMapper, SLOT(map()));
    signalMapper->setMapping(PG4TCombo, "T4");

    QLabel *PG4GateLabel = new QLabel("Gate:");

    PG4LCombo = new QComboBox(this);
    PG4LCombo->addItem(tr("Low"));
    PG4LCombo->addItem(tr("Hi "));

    connect(PG4LCombo, SIGNAL(currentIndexChanged(int)), signalMapper, SLOT(map()));
    signalMapper->setMapping(PG4LCombo, "L4");

    PG4GCombo = new QComboBox(this);
    PG4GCombo->addItem(tr(" Osc"));
    PG4GCombo->addItem(tr(" PG1"));
    PG4GCombo->addItem(tr(" PG2"));
    PG4GCombo->addItem(tr(" PG3"));
    PG4GCombo->addItem(tr(" PG4"));
    PG4GCombo->addItem(tr(" Mod"));
    PG4GCombo->addItem(tr(" Cnt"));
    PG4GCombo->addItem(tr(" InA"));
    PG4GCombo->addItem(tr(" InB"));
    PG4GCombo->addItem(tr(" InC"));

    connect(PG4GCombo, SIGNAL(currentIndexChanged(int)), signalMapper, SLOT(map()));
    signalMapper->setMapping(PG4GCombo, "G4");


    PG4DelaySpinBox = new bSpinBoxWidget(this);
    PG4DelaySpinBox->setGBName("Delay");
    connect(PG4DelaySpinBox, SIGNAL(valueChanged(int)), signalMapper, SLOT(map()));
    signalMapper->setMapping(PG4DelaySpinBox, "D4");

    PG4WidthSpinBox = new bSpinBoxWidget(this);
    PG4WidthSpinBox->setGBName("Width");
    connect(PG4WidthSpinBox, SIGNAL(valueChanged(int)), signalMapper, SLOT(map()));
    signalMapper->setMapping(PG4WidthSpinBox, "W4");

    QGridLayout *ctrls4Layout = new QGridLayout;
    ctrls4Layout->addWidget(PG4OutLabel     , 0, 0, 1, 1);
    ctrls4Layout->addWidget(PG4VCombo       , 0, 1, 1, 1);
    ctrls4Layout->addWidget(PG4PCombo       , 0, 2, 1, 1);
    ctrls4Layout->addWidget(PG4TrigLabel    , 1, 0, 1, 1);
    ctrls4Layout->addWidget(PG4ECombo       , 1, 1, 1, 1);
    ctrls4Layout->addWidget(PG4TCombo       , 1, 2, 1, 1);
    ctrls4Layout->addWidget(PG4GateLabel    , 2, 0, 1, 1);
    ctrls4Layout->addWidget(PG4LCombo       , 2, 1, 1, 1);
    ctrls4Layout->addWidget(PG4GCombo       , 2, 2, 1, 1);
    ctrls4Layout->addWidget(PG4DelaySpinBox , 3, 0, 3, 3);
    ctrls4Layout->addWidget(PG4WidthSpinBox , 6, 0, 3, 3);

    PG4GBox->setLayout(ctrls4Layout);

    /************************************ Mod *******************************/

    QGroupBox *ModGBox = new QGroupBox(tr("Modulator"));
    ModGBox->setObjectName("Mod");

    QLabel *ModOutLabel = new QLabel("Out:");
    ModVCombo = new QComboBox;
    ModVCombo->addItem(tr("Off"));
    ModVCombo->addItem(tr("3V "));
    ModVCombo->addItem(tr("5V "));

    connect(ModVCombo, SIGNAL(currentIndexChanged(int)), signalMapper, SLOT(map()));
    signalMapper->setMapping(ModVCombo, "V5");

    ModPCombo = new QComboBox;
    ModPCombo->addItem(tr("Comp"));
    ModPCombo->addItem(tr("Norm"));

    connect(ModPCombo, SIGNAL(currentIndexChanged(int)), signalMapper, SLOT(map()));
    signalMapper->setMapping(ModPCombo, "P5");

    QLabel *ModTrigLabel = new QLabel("Trig:");

    ModECombo = new QComboBox(this);
    ModECombo->addItem(tr("- edge"));
    ModECombo->addItem(tr("+ edge"));

    connect(ModECombo, SIGNAL(currentIndexChanged(int)), signalMapper, SLOT(map()));
    signalMapper->setMapping(ModECombo, "E5");

    ModTCombo = new QComboBox(this);
    ModTCombo->addItem(tr(" Osc"));
    ModTCombo->addItem(tr(" PG1"));
    ModTCombo->addItem(tr(" PG2"));
    ModTCombo->addItem(tr(" PG3"));
    ModTCombo->addItem(tr(" PG4"));
    ModTCombo->addItem(tr(" Mod"));
    ModTCombo->addItem(tr(" Cnt"));
    ModTCombo->addItem(tr(" InA"));
    ModTCombo->addItem(tr(" InB"));
    ModTCombo->addItem(tr(" InC"));

    connect(ModTCombo, SIGNAL(currentIndexChanged(int)), signalMapper, SLOT(map()));
    signalMapper->setMapping(ModTCombo, "T5");

    QLabel *ModGateLabel = new QLabel("Gate:");

    ModLCombo = new QComboBox(this);
    ModLCombo->addItem(tr("Low"));
    ModLCombo->addItem(tr("Hi "));

    connect(ModLCombo, SIGNAL(currentIndexChanged(int)), signalMapper, SLOT(map()));
    signalMapper->setMapping(ModLCombo, "L5");

    ModGCombo = new QComboBox(this);
    ModGCombo->addItem(tr(" Osc"));
    ModGCombo->addItem(tr(" PG1"));
    ModGCombo->addItem(tr(" PG2"));
    ModGCombo->addItem(tr(" PG3"));
    ModGCombo->addItem(tr(" PG4"));
    ModGCombo->addItem(tr(" Mod"));
    ModGCombo->addItem(tr(" Cnt"));
    ModGCombo->addItem(tr(" InA"));
    ModGCombo->addItem(tr(" InB"));
    ModGCombo->addItem(tr(" InC"));

    connect(ModGCombo, SIGNAL(currentIndexChanged(int)), signalMapper, SLOT(map()));
    signalMapper->setMapping(ModGCombo, "G5");


    ModEndSpinBox = new bSpinBoxWidget(this);
    ModEndSpinBox->setGBName("Delay");
    connect(ModEndSpinBox, SIGNAL(valueChanged(int)), signalMapper, SLOT(map()));
    signalMapper->setMapping(ModEndSpinBox, "D5");

    QGroupBox *ModPG4GBox = new QGroupBox(tr("PG4 Delay"));
    ModPG4GBox->setObjectName("ModPG4");

    QLabel *PG4DelayLabel = new QLabel("0");
    PG4DelayLabel->setAlignment(Qt::AlignRight);
    PG4DelayLabel->setStyleSheet("font: 20px;");

    QVBoxLayout *labelLayout = new QVBoxLayout;
    labelLayout->addWidget(PG4DelayLabel);

    ModPG4GBox->setLayout(labelLayout);

//    connect(PG4DelaySpinBox, SIGNAL(valueChanged(int)), signalMapper, SLOT(map()));
//    signalMapper->setMapping(PG4DelaySpinBox, "W5");

    QGridLayout *ctrls5Layout = new QGridLayout;
    ctrls5Layout->addWidget(ModOutLabel     , 0, 0, 1, 1);
    ctrls5Layout->addWidget(ModVCombo       , 0, 1, 1, 1);
    ctrls5Layout->addWidget(ModPCombo       , 0, 2, 1, 1);
    ctrls5Layout->addWidget(ModTrigLabel    , 1, 0, 1, 1);
    ctrls5Layout->addWidget(ModECombo       , 1, 1, 1, 1);
    ctrls5Layout->addWidget(ModTCombo       , 1, 2, 1, 1);
    ctrls5Layout->addWidget(ModGateLabel    , 2, 0, 1, 1);
    ctrls5Layout->addWidget(ModLCombo       , 2, 1, 1, 1);
    ctrls5Layout->addWidget(ModGCombo       , 2, 2, 1, 1);
    ctrls5Layout->addWidget(ModEndSpinBox   , 3, 0, 3, 3);
    ctrls5Layout->addWidget(ModPG4GBox      , 6, 0, 3, 3);

    ModGBox->setLayout(ctrls5Layout);

    /************************************ Cnt *******************************/

    QGroupBox *CntGBox = new QGroupBox(tr("Count"));
    CntGBox->setObjectName("Cnt");

    QLabel *CntOutLabel = new QLabel("Out:");
    CntVCombo = new QComboBox;
    CntVCombo->addItem(tr("Off"));
    CntVCombo->addItem(tr("3V "));
    CntVCombo->addItem(tr("5V "));

    connect(CntVCombo, SIGNAL(currentIndexChanged(int)), signalMapper, SLOT(map()));
    signalMapper->setMapping(CntVCombo, "V6");
    CntPCombo = new QComboBox;
    CntPCombo->addItem(tr("Comp"));
    CntPCombo->addItem(tr("Norm"));

    connect(CntPCombo, SIGNAL(currentIndexChanged(int)), signalMapper, SLOT(map()));
    signalMapper->setMapping(CntPCombo, "P6");

    QLabel *CntTrigLabel = new QLabel("Trig:");

    CntECombo = new QComboBox(this);
    CntECombo->addItem(tr("- edge"));
    CntECombo->addItem(tr("+ edge"));

    connect(CntECombo, SIGNAL(currentIndexChanged(int)), signalMapper, SLOT(map()));
    signalMapper->setMapping(CntECombo, "E6");

    CntTCombo = new QComboBox(this);
    CntTCombo->addItem(tr(" Osc"));
    CntTCombo->addItem(tr(" PG1"));
    CntTCombo->addItem(tr(" PG2"));
    CntTCombo->addItem(tr(" PG3"));
    CntTCombo->addItem(tr(" PG4"));
    CntTCombo->addItem(tr(" Mod"));
    CntTCombo->addItem(tr(" Cnt"));
    CntTCombo->addItem(tr(" InA"));
    CntTCombo->addItem(tr(" InB"));
    CntTCombo->addItem(tr(" InC"));

    connect(CntTCombo, SIGNAL(currentIndexChanged(int)), signalMapper, SLOT(map()));
    signalMapper->setMapping(CntTCombo, "T6");

    QLabel *CntGateLabel = new QLabel("Gate:");

    CntLCombo = new QComboBox(this);
    CntLCombo->addItem(tr("Low"));
    CntLCombo->addItem(tr("Hi "));

    connect(CntLCombo, SIGNAL(currentIndexChanged(int)), signalMapper, SLOT(map()));
    signalMapper->setMapping(CntLCombo, "L6");

    CntGCombo = new QComboBox(this);
    CntGCombo->addItem(tr(" Osc"));
    PG1GCombo->addItem(tr(" Cnt"));
    CntGCombo->addItem(tr(" PG2"));
    CntGCombo->addItem(tr(" PG3"));
    CntGCombo->addItem(tr(" PG4"));
    CntGCombo->addItem(tr(" Mod"));
    CntGCombo->addItem(tr(" Cnt"));
    CntGCombo->addItem(tr(" InA"));
    CntGCombo->addItem(tr(" InB"));
    CntGCombo->addItem(tr(" InC"));

    connect(CntGCombo, SIGNAL(currentIndexChanged(int)), signalMapper, SLOT(map()));
    signalMapper->setMapping(CntGCombo, "G6");


    CntCSpinBox = new bSpinBoxWidget(this);
    CntCSpinBox->setGBName("Count");
    connect(CntCSpinBox, SIGNAL(valueChanged(int)), signalMapper, SLOT(map()));
    signalMapper->setMapping(CntCSpinBox, "D6");

    QGridLayout *ctrls6Layout = new QGridLayout;
    ctrls6Layout->addWidget(CntOutLabel     , 0, 0, 1, 1);
    ctrls6Layout->addWidget(CntVCombo       , 0, 1, 1, 1);
    ctrls6Layout->addWidget(CntPCombo       , 0, 2, 1, 1);
    ctrls6Layout->addWidget(CntTrigLabel    , 1, 0, 1, 1);
    ctrls6Layout->addWidget(CntECombo       , 1, 1, 1, 1);
    ctrls6Layout->addWidget(CntTCombo       , 1, 2, 1, 1);
    ctrls6Layout->addWidget(CntGateLabel    , 2, 0, 1, 1);
    ctrls6Layout->addWidget(CntLCombo       , 2, 1, 1, 1);
    ctrls6Layout->addWidget(CntGCombo       , 2, 2, 1, 1);
    ctrls6Layout->addWidget(CntCSpinBox     , 3, 0, 3, 3);

    CntGBox->setLayout(ctrls6Layout);


    /************************************ Comms *******************************/

    QGroupBox *CommsGBox = new QGroupBox(tr("Comms"));

    QPushButton *Status = new QPushButton("Status", this);
    connect(Status, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(Status, "St");

    QPushButton *Help = new QPushButton("Help", this);
    connect(Help, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(Help, "Hl");


    ComPortCombo = new QComboBox;
    ComPortCombo->addItem(tr("COM1"));
    ComPortCombo->addItem(tr("COM2"));
    ComPortCombo->addItem(tr("COM3"));
    ComPortCombo->addItem(tr("COM4"));
    ComPortCombo->addItem(tr("COM5"));
    ComPortCombo->addItem(tr("COM6"));
    ComPortCombo->addItem(tr("COM7"));
    ComPortCombo->addItem(tr("COM8"));
    ComPortCombo->addItem(tr("COM9"));
    ComPortCombo->addItem(tr("COM10"));

    connect(ComPortCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(SelectComPort(int)));


    QVBoxLayout * buttonLayout = new QVBoxLayout;
    buttonLayout->addSpacing(150);
    buttonLayout->addWidget(ComPortCombo);
    buttonLayout->addWidget(Status);
    buttonLayout->addWidget(Help);


    received_msg = new QTextEdit(this);
    received_msg->setFixedWidth(350);
//    received_msg->setFixedHeight(150);

    QHBoxLayout *CommsLayout = new QHBoxLayout;
    CommsLayout->addLayout(buttonLayout);
    CommsLayout->addWidget(received_msg);
    CommsGBox->setLayout(CommsLayout);

    QGridLayout *BigLayout = new QGridLayout;
    BigLayout->addWidget(OscGBox    , 0, 0, 4, 4);
    BigLayout->addWidget(PG1GBox    , 0, 4, 4, 4);
    BigLayout->addWidget(PG2GBox    , 0, 8, 4, 4);
    BigLayout->addWidget(PG3GBox    , 0, 12, 4, 4);
    BigLayout->addWidget(PG4GBox    , 0, 16, 4, 4);
    BigLayout->addWidget(ModGBox    , 5, 0, 4, 4);
    BigLayout->addWidget(CntGBox    , 5, 4, 4, 4);
    BigLayout->addWidget(CommsGBox  , 5, 8, 4, 12);

    setLayout(BigLayout);
    BigLayout->setSpacing(2);

    setWindowTitle(tr("Pulse Generator Control II"));

    serial = new QSerialPort(this);
    openSerialPort();
    connect(serial, SIGNAL(error(QSerialPort::SerialPortError)), this,
            SLOT(handleError(QSerialPort::SerialPortError)));

    connect(serial, SIGNAL(readyRead()), this, SLOT(waitIn()));

    connect(signalMapper, SIGNAL(mapped(QString)), this, SLOT(SendData(QString)));
}



void PulseGenCtrl2::changeModEndSpinBox(int tModEndSpinBox)
{
//    ModEndSpinBox->setValue(QString("%1").arg(tModEndSpinBox + diff, 4, 16));
//    qDebug() << "PG3 mod diff wahhhahhsgsyfdehf" << ModEndSpinBox->value() << diff;
}



QString PulseGenCtrl2::niceNumbers(int tNumber, int tRes)
{
    double timeVal = double(tNumber * tRes);

    if (timeVal >= 1000000){
        return QString("%1ms").arg(timeVal/1000000);
    } else if (timeVal >= 1000){
        return QString("%1us").arg(timeVal/1000);
    } else {
        return QString("%1ns").arg(timeVal);
    }
}



void PulseGenCtrl2::SelectComPort(int tComPortSelected)
{
    closeSerialPort();

    switch (tComPortSelected)
       {
        case 0: ComPortSelected = "COM1";
            break;
        case 1: ComPortSelected = "COM2";
            break;
        case 2: ComPortSelected = "COM3";
            break;
        case 3: ComPortSelected = "COM4";
            break;
        case 4: ComPortSelected = "COM5";
            break;
        case 5: ComPortSelected = "COM6";
            break;
        case 6: ComPortSelected = "COM7";
            break;
        case 7: ComPortSelected = "COM8";
            break;
        case 8: ComPortSelected = "COM9";
            break;
        case 9: ComPortSelected = "COM10";
            break;
        default: ComPortSelected = "COM1";
            break;
    }

    openSerialPort();
}


void PulseGenCtrl2::SendData(QString Prefix)
{
    /********************************************** Osc *****************************************************/

    if (Prefix == "P0"){transmit_msg.sprintf("0P%d", OscPCombo->currentIndex());}      // Output Polarity
    if (Prefix == "V0"){transmit_msg.sprintf("0V%d", OscVCombo->currentIndex());}      // Output Voltage

    if (Prefix == "T0"){transmit_msg.sprintf("0T%d", OscTCombo->currentIndex());}       // Trigger Source

    if (Prefix == "E0"){                                                                // Trigger Edge
        if (OscECombo->currentIndex() == 0) {
            transmit_msg.sprintf("0T-");
        } else {
            transmit_msg.sprintf("0T+");
        }
    }

    if (Prefix == "G0"){transmit_msg.sprintf("0G%d", OscGCombo->currentIndex());}       // Gate Source

    if (Prefix == "L0"){                                                                // Gate Level
        if (OscLCombo->currentIndex() == 0) {
            transmit_msg.sprintf("0G-");
        } else {
            transmit_msg.sprintf("0G+");
        }
    }

    if (Prefix == "D0"){transmit_msg.sprintf("d%d", OscDelaySpinBox->value());}        // Delay Value
    if (Prefix == "W0"){transmit_msg.sprintf("w%d", OscWidthSpinBox->value());}        // Width Value

    /********************************************** PG1 *****************************************************/

    if (Prefix == "P1"){transmit_msg.sprintf("1P%d", PG1PCombo->currentIndex());}      // Output Polarity
    if (Prefix == "V1"){transmit_msg.sprintf("1V%d", PG1VCombo->currentIndex());}      // Output Voltage

    if (Prefix == "T1"){transmit_msg.sprintf("1T%d", PG1TCombo->currentIndex());}       // Trigger Source

    if (Prefix == "E1"){                                                                // Trigger Edge
        if (PG1ECombo->currentIndex() == 0) {
            transmit_msg.sprintf("1T-");
        } else {
            transmit_msg.sprintf("1T+");
        }
    }

    if (Prefix == "G1"){transmit_msg.sprintf("1G%d", PG1GCombo->currentIndex());}       // Gate Source

    if (Prefix == "L1"){                                                                // Gate Level
        if (PG1LCombo->currentIndex() == 0) {
            transmit_msg.sprintf("1G-");
        } else {
            transmit_msg.sprintf("1G+");
        }
    }

    if (Prefix == "D1"){transmit_msg.sprintf("1D%d", PG1DelaySpinBox->value());}        // Delay Value
    if (Prefix == "W1"){transmit_msg.sprintf("1W%d", PG1WidthSpinBox->value());}        // Width Value

    /********************************************** PG2 *****************************************************/

    if (Prefix == "P2"){transmit_msg.sprintf("2P%d", PG2PCombo->currentIndex());}      // Output Polarity
    if (Prefix == "V2"){transmit_msg.sprintf("2V%d", PG2VCombo->currentIndex());}      // Output Voltage

    if (Prefix == "T2"){transmit_msg.sprintf("2T%d", PG2TCombo->currentIndex());}       // Trigger Source

    if (Prefix == "E2"){                                                                // Trigger Edge
        if (PG2ECombo->currentIndex() == 0) {
            transmit_msg.sprintf("2T-");
        } else {
            transmit_msg.sprintf("2T+");
        }
    }

    if (Prefix == "G2"){transmit_msg.sprintf("2G%d", PG2GCombo->currentIndex());}       // Gate Source

    if (Prefix == "L2"){                                                                // Gate Level
        if (PG2LCombo->currentIndex() == 0) {
            transmit_msg.sprintf("2G-");
        } else {
            transmit_msg.sprintf("2G+");
        }
    }

    if (Prefix == "D2"){transmit_msg.sprintf("2D%d", PG2DelaySpinBox->value());}        // Delay Value
    if (Prefix == "W2"){transmit_msg.sprintf("2W%d", PG2WidthSpinBox->value());}        // Width Value

    /********************************************** PG3 *****************************************************/

    if (Prefix == "P3"){transmit_msg.sprintf("3P%d", PG3PCombo->currentIndex());}      // Output Polarity
    if (Prefix == "V3"){transmit_msg.sprintf("3V%d", PG3VCombo->currentIndex());}      // Output Voltage

    if (Prefix == "T3"){transmit_msg.sprintf("3T%d", PG3TCombo->currentIndex());}       // Trigger Source

    if (Prefix == "E3"){                                                                // Trigger Edge
        if (PG3ECombo->currentIndex() == 0) {
            transmit_msg.sprintf("3T-");
        } else {
            transmit_msg.sprintf("3T+");
        }
    }

    if (Prefix == "G3"){transmit_msg.sprintf("3G%d", PG3GCombo->currentIndex());}       // Gate Source

    if (Prefix == "L3"){                                                                // Gate Level
        if (PG3LCombo->currentIndex() == 0) {
            transmit_msg.sprintf("3G-");
        } else {
            transmit_msg.sprintf("3G+");
        }
    }

    if (Prefix == "D3"){transmit_msg.sprintf("3D%d", PG3DelaySpinBox->value());}        // Delay Value
    if (Prefix == "W3"){transmit_msg.sprintf("3W%d", PG3WidthSpinBox->value());}        // Width Value

    /********************************************** PG4 *****************************************************/

    if (Prefix == "P4"){transmit_msg.sprintf("4P%d", PG4PCombo->currentIndex());}      // Output Polarity
    if (Prefix == "V4"){transmit_msg.sprintf("4V%d", PG4VCombo->currentIndex());}      // Output Voltage

    if (Prefix == "T4"){transmit_msg.sprintf("4T%d", PG4TCombo->currentIndex());}       // Trigger Source

    if (Prefix == "E4"){                                                                // Trigger Edge
        if (PG4ECombo->currentIndex() == 0) {
            transmit_msg.sprintf("4T-");
        } else {
            transmit_msg.sprintf("4T+");
        }
    }

    if (Prefix == "G4"){transmit_msg.sprintf("4G%d", PG4GCombo->currentIndex());}       // Gate Source

    if (Prefix == "L4"){                                                                // Gate Level
        if (PG4LCombo->currentIndex() == 0) {
            transmit_msg.sprintf("4G-");
        } else {
            transmit_msg.sprintf("4G+");
        }
    }

    if (Prefix == "D4"){transmit_msg.sprintf("4D%d", PG4DelaySpinBox->value());}        // Delay Value
    if (Prefix == "W4"){transmit_msg.sprintf("4W%d", PG4WidthSpinBox->value());}        // Width Value

    /********************************************** Mod *****************************************************/

    if (Prefix == "P5"){transmit_msg.sprintf("5P%d", ModPCombo->currentIndex());}      // Output Polarity
    if (Prefix == "V5"){transmit_msg.sprintf("5V%d", ModVCombo->currentIndex());}      // Output Voltage

    if (Prefix == "T5"){transmit_msg.sprintf("5T%d", ModTCombo->currentIndex());}       // Trigger Source

    if (Prefix == "E5"){                                                                // Trigger Edge
        if (ModECombo->currentIndex() == 0) {
            transmit_msg.sprintf("5T-");
        } else {
            transmit_msg.sprintf("5T+");
        }
    }

    if (Prefix == "G5"){transmit_msg.sprintf("5G%d", ModGCombo->currentIndex());}       // Gate Source

    if (Prefix == "L5"){                                                                // Gate Level
        if (ModLCombo->currentIndex() == 0) {
            transmit_msg.sprintf("5G-");
        } else {
            transmit_msg.sprintf("5G+");
        }
    }

    if (Prefix == "D5"){transmit_msg.sprintf("5D%d", ModEndSpinBox->value());}        // Delay Value
//    if (Prefix == "W5"){transmit_msg.sprintf("5W%d", ModWidthSpinBox->value());}        // Width Value

    /********************************************** Cnt *****************************************************/

    if (Prefix == "P6"){transmit_msg.sprintf("6P%d", CntPCombo->currentIndex());}      // Output Polarity
    if (Prefix == "V6"){transmit_msg.sprintf("6V%d", CntVCombo->currentIndex());}      // Output Voltage

    if (Prefix == "T6"){transmit_msg.sprintf("6T%d", CntTCombo->currentIndex());}       // Trigger Source

    if (Prefix == "E6"){                                                                // Trigger Edge
        if (CntECombo->currentIndex() == 0) {
            transmit_msg.sprintf("6T-");
        } else {
            transmit_msg.sprintf("6T+");
        }
    }

    if (Prefix == "G6"){transmit_msg.sprintf("6G%d", CntGCombo->currentIndex());}       // Gate Source

    if (Prefix == "L6"){                                                                // Gate Level
        if (CntLCombo->currentIndex() == 0) {
            transmit_msg.sprintf("6G-");
        } else {
            transmit_msg.sprintf("6G+");
        }
    }

    if (Prefix == "D6"){transmit_msg.sprintf("6D%d", CntCSpinBox->value());}        // Delay Value




    //help
    if (Prefix == "Hl"){transmit_msg.sprintf("H");}
    //Status
    if (Prefix == "St"){transmit_msg.sprintf("S");}

//    //Verbosity
//    if (Prefix == "Yp"){
//        if (YapCombo->currentIndex() == 0){
//            transmit_msg.sprintf("Q");
//        } else {
//            transmit_msg.sprintf("V");
//        }
//    }

    QTimer::singleShot(100, this, SLOT(transmitMsg()));

    received_msg->setTextColor(Qt::blue);
    received_msg->insertPlainText(transmit_msg);
    received_msg->insertPlainText("\n");
    received_msg->moveCursor(QTextCursor::End, QTextCursor::MoveAnchor);
}


void PulseGenCtrl2::openSerialPort()
{
    serial->setPortName(ComPortSelected);
    if (serial->open(QIODevice::ReadWrite)) {
        if (serial->setBaudRate(QSerialPort::Baud115200) && serial->setDataBits(QSerialPort::Data8)
            && serial->setParity(QSerialPort::NoParity) && serial->setStopBits(QSerialPort::OneStop)
            && serial->setFlowControl(QSerialPort::NoFlowControl)) {
            received_msg->append(QString("Connected as %1\n").arg(serial->portName()));
        } else {
            serial->close();
            QMessageBox::critical(this, tr("Error"), serial->errorString());
            received_msg->setTextColor(Qt::red);
            received_msg->append("Open error \n");
        }
    } else {
        QMessageBox::critical(this, tr("Error"), serial->errorString());
        received_msg->setTextColor(Qt::red);
        received_msg->append(QString("Configure error on %1\n").arg(serial->portName()));
    }
}


void PulseGenCtrl2::closeSerialPort()
{
    serial->close();
    received_msg->append(QString("Disconnected from %1\n").arg(serial->portName()));
}


void PulseGenCtrl2::transmitMsg()
{
    serial->write(transmit_msg.toLocal8Bit());
}


void PulseGenCtrl2::waitIn()
{
    QTimer::singleShot(100, this, SLOT(readData()));
}


void PulseGenCtrl2::readData()
{
    QByteArray pgStatus = serial->readLine(1024);
    bool ok;
    int Channel, Voltage, Polarity, TrigSrc, TrigEdge;
    int GateSrc, GateEdge, Delay, Width, PG4Delay, Count;

    if (pgStatus.length() > 0) {
        qDebug(pgStatus);
        received_msg->setTextColor(Qt::darkGreen);
        received_msg->insertPlainText(pgStatus);
        received_msg->moveCursor(QTextCursor::End, QTextCursor::MoveAnchor);

        QList<QByteArray> list = pgStatus.split(' ');

        if (pgStatus.contains("Channel:")) Channel = list[1].toInt(&ok, 10);

        if (pgStatus.contains("Out:")) {
            Voltage = list[1].toInt(&ok, 10);
            Polarity = list[2].toInt(&ok, 10);
        }

        if (pgStatus.contains("Trig:")) {
            TrigSrc = list[1].toInt(&ok, 10);
            TrigEdge = list[2].toInt(&ok, 10);
        }

        if (pgStatus.contains("Gate:")) {
            GateSrc = list[1].toInt(&ok, 10);
            GateEdge = list[2].toInt(&ok, 10);
        }

        if (pgStatus.contains("Delay:")) Delay = list[1].toInt(&ok, 10);

        if (pgStatus.contains("Width:")) Width = list[1].toInt(&ok, 10);

        if (pgStatus.contains("PG4 Dly:")) PG4Delay = list[2].toInt(&ok, 10);
        if (pgStatus.contains("Count:")) Count = list[1].toInt(&ok, 10);


        switch (Channel) {
            case 0: OscVCombo->setCurrentIndex(Voltage);
                    OscPCombo->setCurrentIndex(Polarity);
                    OscECombo->setCurrentIndex(TrigEdge);
                    OscTCombo->setCurrentIndex(TrigSrc);
                    OscLCombo->setCurrentIndex(GateEdge);
                    OscGCombo->setCurrentIndex(GateSrc);
                    OscDelaySpinBox->setValue(Delay);
                    OscWidthSpinBox->setValue(Width);
                 break;

            case 1: PG1VCombo->setCurrentIndex(Voltage);
                    PG1PCombo->setCurrentIndex(Polarity);
                    PG1ECombo->setCurrentIndex(TrigEdge);
                    PG1TCombo->setCurrentIndex(TrigSrc);
                    PG1LCombo->setCurrentIndex(GateEdge);
                    PG1GCombo->setCurrentIndex(GateSrc);
                    PG1DelaySpinBox->setValue(Delay);
                    PG1WidthSpinBox->setValue(Width);
                 break;

            case 2: PG2VCombo->setCurrentIndex(Voltage);
                    PG2PCombo->setCurrentIndex(Polarity);
                    PG2ECombo->setCurrentIndex(TrigEdge);
                    PG2TCombo->setCurrentIndex(TrigSrc);
                    PG2LCombo->setCurrentIndex(GateEdge);
                    PG2GCombo->setCurrentIndex(GateSrc);
                    PG2DelaySpinBox->setValue(Delay);
                    PG2WidthSpinBox->setValue(Width);
                 break;

            case 3: PG3VCombo->setCurrentIndex(Voltage);
                    PG3PCombo->setCurrentIndex(Polarity);
                    PG3ECombo->setCurrentIndex(TrigEdge);
                    PG3TCombo->setCurrentIndex(TrigSrc);
                    PG3LCombo->setCurrentIndex(GateEdge);
                    PG3GCombo->setCurrentIndex(GateSrc);
                    PG3DelaySpinBox->setValue(Delay);
                    PG3WidthSpinBox->setValue(Width);
                 break;

            case 4: PG4VCombo->setCurrentIndex(Voltage);
                    PG4PCombo->setCurrentIndex(Polarity);
                    PG4ECombo->setCurrentIndex(TrigEdge);
                    PG4TCombo->setCurrentIndex(TrigSrc);
                    PG4LCombo->setCurrentIndex(GateEdge);
                    PG4GCombo->setCurrentIndex(GateSrc);
                    PG4DelaySpinBox->setValue(Delay);
                    PG4WidthSpinBox->setValue(Width);
                 break;

            case 5: ModVCombo->setCurrentIndex(Voltage);
                    ModPCombo->setCurrentIndex(Polarity);
                    ModECombo->setCurrentIndex(TrigEdge);
                    ModTCombo->setCurrentIndex(TrigSrc);
                    ModLCombo->setCurrentIndex(GateEdge);
                    ModGCombo->setCurrentIndex(GateSrc);
                    ModEndSpinBox->setValue(Delay);
                    PG4DelaySpinBox->setValue(Width);
                 break;

            case 6: CntVCombo->setCurrentIndex(Voltage);
                    CntPCombo->setCurrentIndex(Polarity);
                    CntECombo->setCurrentIndex(TrigEdge);
                    CntTCombo->setCurrentIndex(TrigSrc);
                    CntLCombo->setCurrentIndex(GateEdge);
                    CntGCombo->setCurrentIndex(GateSrc);
                    CntCSpinBox->setValue(Delay);
                 break;

        }

    }
}


void PulseGenCtrl2::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {
        QMessageBox::critical(this, tr("Critical Error"), serial->errorString());
        closeSerialPort();
    }
}

