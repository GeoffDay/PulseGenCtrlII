//this is a 6 digit decimal version

#include "bSpinBoxWidget.h"

bSpinBoxWidget::bSpinBoxWidget(QWidget *parent) :
    QWidget(parent)
{
    ui.setupUi(this);
    validator = new QRegExpValidator(QRegExp("[0-9]{1,8}"), this);
}


QValidator::State bSpinBoxWidget::validate(QString &text, int &pos) const
{
    return validator->validate(text, pos);
}


void bSpinBoxWidget::setGBName(QString tTitle)
{
    ui.groupBox->setTitle(tTitle);
}


void bSpinBoxWidget::setValue(quint32 value)
{
    ui.spinBox->setValue(value);
    bSpinBoxVal = ui.spinBox->value();
    enableSubtractButtons();
}


quint32 bSpinBoxWidget::value()
{
    return bSpinBoxVal;
}


void bSpinBoxWidget::enableSubtractButtons()
{
    if (bSpinBoxVal > 327680) {bSpinBoxVal = 327680;}

    if (bSpinBoxVal > 0) {ui.SubOneButton->setEnabled(true);}
    if (bSpinBoxVal > 10) {ui.SubTenButton->setEnabled(true);}
    if (bSpinBoxVal > 100) {ui.SubHundredButton->setEnabled(true);}
    if (bSpinBoxVal > 1000) {ui.SubThousandButton->setEnabled(true);}
    if (bSpinBoxVal > 10000) {ui.SubTenThouButton->setEnabled(true);}
    if (bSpinBoxVal > 100000) {ui.SubHundredThouButton->setEnabled(true);}

    if (bSpinBoxVal < 5) {ui.SubOneButton->setEnabled(false);}
    if (bSpinBoxVal < 10) {ui.SubTenButton->setEnabled(false);}
    if (bSpinBoxVal < 100) {ui.SubHundredButton->setEnabled(false);}
    if (bSpinBoxVal < 1000) {ui.SubThousandButton->setEnabled(false);}
    if (bSpinBoxVal < 10000) {ui.SubTenThouButton->setEnabled(false);}
    if (bSpinBoxVal < 100000) {ui.SubHundredThouButton->setEnabled(false);}
}


void bSpinBoxWidget::on_AddOne_Clicked()
{
    bSpinBoxVal = ui.spinBox->value() + 5;
    enableSubtractButtons();
    ui.spinBox->setValue(bSpinBoxVal);
    emit valueChanged(bSpinBoxVal);
}


void bSpinBoxWidget::on_AddTen_Clicked()
{
    bSpinBoxVal = ui.spinBox->value() + 10;
    enableSubtractButtons();
    ui.spinBox->setValue(bSpinBoxVal);
    emit valueChanged(bSpinBoxVal);
}


void bSpinBoxWidget::on_AddHundred_Clicked()
{
    bSpinBoxVal = ui.spinBox->value() + 100;
    enableSubtractButtons();
    ui.spinBox->setValue(bSpinBoxVal);
    emit valueChanged(bSpinBoxVal);
}


void bSpinBoxWidget::on_AddThousand_Clicked()
{
    bSpinBoxVal = ui.spinBox->value() + 1000;
    enableSubtractButtons();
    ui.spinBox->setValue(bSpinBoxVal);
    emit valueChanged(bSpinBoxVal);
}


void bSpinBoxWidget::on_AddTenThou_Clicked()
{
    bSpinBoxVal = ui.spinBox->value() + 10000;
    enableSubtractButtons();
    ui.spinBox->setValue(bSpinBoxVal);
    emit valueChanged(bSpinBoxVal);
}


void bSpinBoxWidget::on_AddHundredThou_Clicked()
{
    bSpinBoxVal = ui.spinBox->value() + 100000;
    enableSubtractButtons();
    ui.spinBox->setValue(bSpinBoxVal);
    emit valueChanged(bSpinBoxVal);
}


void bSpinBoxWidget::on_SubOne_Clicked()
{
    bSpinBoxVal = ui.spinBox->value() - 5;
    enableSubtractButtons();
    ui.spinBox->setValue(bSpinBoxVal);
    emit valueChanged(bSpinBoxVal);
}


void bSpinBoxWidget::on_SubTen_Clicked()
{
    bSpinBoxVal = ui.spinBox->value() - 10;
    enableSubtractButtons();
    ui.spinBox->setValue(bSpinBoxVal);
    emit valueChanged(bSpinBoxVal);
}


void bSpinBoxWidget::on_SubHundred_Clicked()
{
    bSpinBoxVal = ui.spinBox->value() - 100;
    enableSubtractButtons();
    ui.spinBox->setValue(bSpinBoxVal);
    emit valueChanged(bSpinBoxVal);
}


void bSpinBoxWidget::on_SubThousand_Clicked()
{
    bSpinBoxVal = ui.spinBox->value() - 1000;
    enableSubtractButtons();
    ui.spinBox->setValue(bSpinBoxVal);
    emit valueChanged(bSpinBoxVal);
}


void bSpinBoxWidget::on_SubTenThou_Clicked()
{
    bSpinBoxVal = ui.spinBox->value() - 10000;
    enableSubtractButtons();
    ui.spinBox->setValue(bSpinBoxVal);
    emit valueChanged(bSpinBoxVal);
}


void bSpinBoxWidget::on_SubHundredThou_Clicked()
{
    bSpinBoxVal = ui.spinBox->value() - 100000;
    enableSubtractButtons();
    ui.spinBox->setValue(bSpinBoxVal);
    emit valueChanged(bSpinBoxVal);
}

