#include "csettingsdlg.h"
#include "TrackEditor.h"

CSettingsDlg::CSettingsDlg(LogReader *parent)
    : QDialog(parent), m_parent(parent)
{
	ui.setupUi(this);

	loadSettings();

	connect(ui.okButton, SIGNAL(clicked()), this, SLOT(accept()));
	connect(ui.cancelButton, SIGNAL(clicked()), this, SLOT(reject()));

    createIcons();
    ui.contentsWidget->setCurrentRow(0);

    m_diagram_settings = new CDiagramSettings(this);

    ui.pagesWidget->addWidget(m_diagram_settings);

}

CSettingsDlg::~CSettingsDlg()
{

}

void CSettingsDlg::createIcons()
{

	QListWidgetItem *configButton = new QListWidgetItem(ui.contentsWidget);
	configButton->setIcon(QIcon(":/images/config.png"));
	configButton->setText(tr("Configuration"));
	configButton->setTextAlignment(Qt::AlignHCenter);
	configButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

	QListWidgetItem *updateButton = new QListWidgetItem(ui.contentsWidget);
	updateButton->setIcon(QIcon(":/images/update.png"));
	updateButton->setText(tr("Update"));
	updateButton->setTextAlignment(Qt::AlignHCenter);
	updateButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

	QListWidgetItem *queryButton = new QListWidgetItem(ui.contentsWidget);
	queryButton->setIcon(QIcon(":/images/diagram.png"));
	queryButton->setText(tr("Diagrams"));
	queryButton->setTextAlignment(Qt::AlignHCenter);
	queryButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

	connect(ui.contentsWidget, SIGNAL(currentItemChanged(QListWidgetItem *, QListWidgetItem *)),
        this, SLOT(changePage(QListWidgetItem *, QListWidgetItem*)));
}

void CSettingsDlg::changePage(QListWidgetItem *current, QListWidgetItem *previous)
{
	if (!current)
		current = previous;

	ui.pagesWidget->setCurrentIndex(ui.contentsWidget->row(current));
}


void CSettingsDlg::apply() {
	// save settings somewhere

	m_parent->setDiagramQuantities(m_diagram_settings->getDistVals(), m_diagram_settings->getTimeVals(), m_diagram_settings->getTrackPointVals());

	saveSettings();
}

void CSettingsDlg::accept() {
	// save settings somewhere
	apply();
	QDialog::accept();
}

void CSettingsDlg::reject() {
	// discard changes
	QDialog::reject();
}

void CSettingsDlg::loadSettings() {

}

void CSettingsDlg::saveSettings() {

}
