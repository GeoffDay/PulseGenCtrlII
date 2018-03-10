#ifndef BSPINBOXWIDGET_H
#define BSPINBOXWIDGET_H

#include "ui_bSpinBoxWidget.h"


class bSpinBoxWidget : public QWidget
{
    Q_OBJECT

public:
    bSpinBoxWidget(QWidget *parent = 0);
    void setGBName(QString tTitle);
//    void setValue(int value);
    void setValue(quint32 value);
    quint32 value();

signals:
    void valueChanged(int bSpinBoxVal);

private slots:
    void on_AddOne_Clicked();
    void on_AddTen_Clicked();
    void on_AddHundred_Clicked();
    void on_AddThousand_Clicked();
    void on_AddTenThou_Clicked();
    void on_AddHundredThou_Clicked();
    void on_SubOne_Clicked();
    void on_SubTen_Clicked();
    void on_SubHundred_Clicked();
    void on_SubThousand_Clicked();
    void on_SubTenThou_Clicked();
    void on_SubHundredThou_Clicked();

    void enableSubtractButtons();


protected:
    QValidator::State validate(QString &text, int &pos) const;
//    int valueFromText(const QString &text) const;
//    QString textFromValue(quint32 value) const;

private:
    Ui::bSpinBoxWidget ui;
    quint32 bSpinBoxVal;
    QRegExpValidator *validator;
};

#endif // BSPINBOXWIDGET_H
