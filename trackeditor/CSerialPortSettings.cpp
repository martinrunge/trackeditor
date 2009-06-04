/*
 * CSerialPortSettings.cpp
 *
 *  Created on: 29.05.2009
 *      Author: martin
 */

#include "CSerialPortSettings.h"

CSerialPortSettings::CSerialPortSettings() {
	// TODO Auto-generated constructor stub

	m_speed_labels << "2400" << "4800" << "9600" << "19200" << "38400" << "57600" << "115200";
	m_speed_vals << BAUD2400 << BAUD4800 << BAUD9600 << BAUD19200 << BAUD38400 << BAUD57600 << BAUD115200 ;

	m_data_bit_labels << "5" << "6" << "7" << "8";
	m_data_bit_vals << DATA_5 << DATA_6 << DATA_7 << DATA_8;

	m_parity_labels << "none" << "odd" << "even";
	m_parity_vals << PAR_NONE << PAR_ODD << PAR_EVEN;

	m_stop_bits_labels << "1" << "1.5" << "2";
	m_stop_bits_vals << STOP_1 << STOP_1_5 << STOP_2;

	m_flow_type_labels << "off" << "hardware" << "xonxoff";
	m_flow_type_vals << FLOW_OFF << FLOW_HARDWARE << FLOW_XONXOFF;

}

CSerialPortSettings::~CSerialPortSettings() {
	// TODO Auto-generated destructor stub
}
