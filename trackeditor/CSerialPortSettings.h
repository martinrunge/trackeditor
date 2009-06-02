/*
 * CSerialPortSettings.h
 *
 *  Created on: 29.05.2009
 *      Author: martin
 */

#ifndef CSERIALPORTSETTINGS_H_
#define CSERIALPORTSETTINGS_H_

#include "qextserialport/qextserialbase.h"

class CSerialPortSettings : public PortSettings {
public:
	CSerialPortSettings();
	virtual ~CSerialPortSettings();

	inline QString getName() const {return m_name; };
	inline void setName(QString name) { m_name = name; };

	inline CSerialPortSettings& operator=(const CSerialPortSettings& rhs)
	{
		if(this != &rhs) {
			BaudRate = rhs.BaudRate;
			DataBits = rhs.DataBits;
			FlowControl = rhs.FlowControl;
			Parity = rhs.Parity;
			StopBits = rhs.StopBits;
			Timeout_Millisec = rhs.Timeout_Millisec;
			m_name = rhs.getName();

		}
		return *this;
	};

private:
	QString m_name;
};

#endif /* CSERIALPORTSETTINGS_H_ */
