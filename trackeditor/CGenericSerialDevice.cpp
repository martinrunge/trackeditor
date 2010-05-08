/*
 * CGenericSerialDevice.cpp
 *
 *  Created on: 23.05.2009
 *      Author: martin
 */

#include <QFileDialog>
#include "CGenericSerialDevice.h"

CGenericSerialDevice::CGenericSerialDevice() : m_valid(false) {

	m_ui = new Ui::genericserialwidget;
	m_ui->setupUi(this);

	m_validator = new CDeviceFileValidator;
	m_ui->deviceFileLineEdit->setValidator( m_validator );

	m_ui->speedComboBox->addItems(m_settings.getSpeedLabels());
	m_ui->dataBitsComboBox->addItems(m_settings.getDataBitsLabels());
	m_ui->parityComboBox->addItems(m_settings.getParityLabels());
	m_ui->stopBitsComboBox->addItems(m_settings.getStopBitsLabels());
	m_ui->flowControlComboBox->addItems(m_settings.getFlowControlLabels());


	connect(m_ui->pushButton, SIGNAL(clicked()), this, SLOT(chooseDeviceFile()));
	connect(m_ui->deviceFileLineEdit,SIGNAL(textChanged(QString)), this, SLOT(textChanged(QString)));

	textChanged(m_ui->deviceFileLineEdit->text());

}

CGenericSerialDevice::~CGenericSerialDevice() {
	delete m_ui;
	delete m_validator;
}


const CSerialPortSettings CGenericSerialDevice::getSerialPortSettings()
{
	m_settings.setName(m_ui->deviceFileLineEdit->text());

	int index = m_ui->speedComboBox->currentIndex();
	m_settings.setBaudRateFromIndex(index);

	index = m_ui->dataBitsComboBox->currentIndex();
	m_settings.setDataBitsFromIndex(index);

	index = m_ui->parityComboBox->currentIndex();
	m_settings.setParityFromIndex(index);

	index = m_ui->stopBitsComboBox->currentIndex();
	m_settings.setStopBitsFromIndex(index);

	index = m_ui->flowControlComboBox->currentIndex();
	m_settings.setFlowControlFromIndex(index);

	return m_settings;
}


void CGenericSerialDevice::chooseDeviceFile()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Choose Device File"), "/dev");

	if(!fileName.isEmpty())
	{
		m_ui->deviceFileLineEdit->setText(fileName);
	}
}


void CGenericSerialDevice::textChanged(QString text)
{
	QFileInfo fi(text);
	if(fi.exists() && m_valid == false)
	{
		m_valid = true;
		emit setValid(m_valid);
	}
	else if( ! fi.exists() && m_valid == true )
	{
		m_valid = false;
		emit setValid(m_valid);
	}
}
