/*
 * CDeviceDialog.cpp
 *
 *  Created on: 23.05.2009
 *      Author: Martin Runge
 */

#include "CDeviceDialog.h"
#include "TrackEditor.h"
#include "CWintec.h"

CDeviceDialog::CDeviceDialog(LogReader *parent) : QDialog(parent) {

	m_dlg = new Ui::DeviceDialog;
    m_dlg->setupUi(this);

    connect(m_dlg->modelComboBox,SIGNAL(currentIndexChanged(int)) ,this, SLOT(modelChanged(int)));
    connect(m_dlg->interfaceComboBox,SIGNAL(currentIndexChanged(int)) ,this, SLOT(interfaceChanged(int)));

    loadSettings();

}

CDeviceDialog::~CDeviceDialog() {
	delete m_dlg;
}


void CDeviceDialog::setPortSettings(CSerialPortSettings settings) {
	m_port_settings = settings;
}

CSerialPortSettings CDeviceDialog::getPortSettings() {
	return m_port_settings;
}

void CDeviceDialog::modelChanged(int index) {


}

void CDeviceDialog::interfaceChanged(int index) {
	m_dlg->tabWidget->setCurrentIndex(index);
	for(int i=0; i < m_dlg->tabWidget->count(); i++) {
		m_dlg->tabWidget->setTabEnabled(i, i==index );
	}
}

void CDeviceDialog::accept() {

	int model = m_dlg->modelComboBox->currentIndex();
	int idx = m_dlg->interfaceComboBox->currentIndex();
	enum interfaces_t interface = (enum interfaces_t)(idx);
	// get a temporary object to ask for interface's serial parameters

	switch(interface)
	{
	case E_USB:
	{
		CWintec wintec("WBT-201");
		m_port_settings = wintec.getSerialPortSettings(interface);
		m_port_settings.setName( m_dlg->usbTab->getDeviceFileName());
		break;
	}
	case E_BLUETOOTH:
	{
		CWintec wintec("WBT-201");
		m_port_settings = wintec.getSerialPortSettings(interface);
		m_port_settings.setName( m_dlg->bluetoothTab->getDeviceFileName());
		break;
	}
	case E_GENERIC_SERIAL:
		m_port_settings = m_dlg->genericSerialTab->getSerialPortSettings();
		break;

	default:
		break;
	}

	// write settings
	saveSettings();

	QDialog::accept();
}

void CDeviceDialog::reject() {

	QDialog::reject();
}


void CDeviceDialog::loadSettings()
{
    // load settings
    int model = m_settings.value("gps/model").toInt();
    int interface = m_settings.value("gps/interface").toInt();

    m_dlg->modelComboBox->setCurrentIndex(model);
    m_dlg->interfaceComboBox->setCurrentIndex(idx);

    QString usb_device = m_settings.value("gps/usb/device").toString();
    QString bt_device = m_settings.value("gps/bluetooth/address").toString();


}

void CDeviceDialog::saveSettings()
{
	int model = m_dlg->modelComboBox->currentIndex();
	int idx = m_dlg->interfaceComboBox->currentIndex();


	m_settings.value("gps/interface", model );
	m_settings.value("gps/model", idx);


}
