/*
 * CSerialPortSettings.h
 *
 *  Created on: 29.05.2009
 *      Author: martin
 */

#ifndef CSERIALPORTSETTINGS_H_
#define CSERIALPORTSETTINGS_H_

#include <QStringList>
#include "qextserialport/qextserialbase.h"

class CSerialPortSettings : public PortSettings {
public:
	CSerialPortSettings();
	virtual ~CSerialPortSettings();

	inline QString getName() const {return m_name; };
	inline void setName(QString name) { m_name = name; };

	inline int getSpeedSize() {return m_speed_labels.size(); };
	inline QStringList getSpeedLabels() {return m_speed_labels; };
	inline QString getSpeedLabel(int index) {return m_speed_labels.at(index); };
	inline enum BaudRateType getSpeedEnum(int index) {return m_speed_vals.at(index); };
	inline void setBaudRateFromIndex(int index) { BaudRate = m_speed_vals.at(index); };

	inline int getDataBitsSize() {return m_data_bit_labels.size(); };
	inline QStringList getDataBitsLabels() {return m_data_bit_labels; };
	inline QString getDataBitsLabel(int index) {return m_data_bit_labels.at(index); };
	inline enum DataBitsType getDataBitsEnum(int index) {return m_data_bit_vals.at(index); };
	inline void setDataBitsFromIndex(int index) { DataBits = m_data_bit_vals.at(index); };

	inline int getParitySize() {return m_parity_labels.size(); };
	inline QStringList getParityLabels() {return m_parity_labels; };
	inline QString getParityLabel(int index) {return m_parity_labels.at(index); };
	inline enum ParityType getParityEnum(int index) {return m_parity_vals.at(index); };
	inline void setParityFromIndex(int index) { Parity = m_parity_vals.at(index); };

	inline int getStopBitsSize() {return m_stop_bits_labels.size(); };
	inline QStringList getStopBitsLabels() {return m_stop_bits_labels; };
	inline QString getStopBitsLabel(int index) {return m_stop_bits_labels.at(index); };
	inline enum StopBitsType getStopBitsEnum(int index) {return m_stop_bits_vals.at(index); };
	inline void setStopBitsFromIndex(int index) { StopBits = m_stop_bits_vals.at(index); };

	inline int getFlowControlSize() {return m_flow_type_labels.size(); };
	inline QStringList getFlowControlLabels() {return m_flow_type_labels; };
	inline QString getFlowControlLabel(int index) {return m_flow_type_labels.at(index); };
	inline enum FlowType getFlowControlEnum(int index) {return m_flow_type_vals.at(index); };
	inline void setFlowControlFromIndex(int index) { FlowControl = m_flow_type_vals.at(index); };


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

	QStringList m_speed_labels;
	QList<enum BaudRateType> m_speed_vals;

	QStringList m_data_bit_labels;
	QList<enum DataBitsType> m_data_bit_vals;

	QStringList m_parity_labels;
	QList<enum ParityType> m_parity_vals;

	QStringList m_stop_bits_labels;
	QList<enum StopBitsType> m_stop_bits_vals;

	QStringList m_flow_type_labels;
	QList<enum FlowType> m_flow_type_vals;

};

#endif /* CSERIALPORTSETTINGS_H_ */
