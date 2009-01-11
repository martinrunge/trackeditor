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
    contentsWidget->setCurrentRow(0);

}

CSettingsDlg::~CSettingsDlg()
{

}

void CSettingsDlg::createIcons()
{

	QListWidgetItem *configButton = new QListWidgetItem(contentsWidget);
	configButton->setIcon(QIcon(":/images/config.png"));
	configButton->setText(tr("Configuration"));
	configButton->setTextAlignment(Qt::AlignHCenter);
	configButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

	QListWidgetItem *updateButton = new QListWidgetItem(contentsWidget);
	updateButton->setIcon(QIcon(":/images/update.png"));
	updateButton->setText(tr("Update"));
	updateButton->setTextAlignment(Qt::AlignHCenter);
	updateButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

	QListWidgetItem *queryButton = new QListWidgetItem(contentsWidget);
	queryButton->setIcon(QIcon(":/images/query.png"));
	queryButton->setText(tr("Query"));
	queryButton->setTextAlignment(Qt::AlignHCenter);
	queryButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

	connect(contentsWidget, SIGNAL(currentItemChanged(QListWidgetItem *, QListWidgetItem *)),
        this, SLOT(changePage(QListWidgetItem *, QListWidgetItem*)));
}

void ConfigDialog::changePage(QListWidgetItem *current, QListWidgetItem *previous)
{
	if (!current)
		current = previous;

	pagesWidget->setCurrentIndex(contentsWidget->row(current));
}


void CSettingsDlg::apply() {
	// save settings somewhere
	saveSettings();
}

void CSettingsDlg::accept() {
	// save settings somewhere
	saveSettings();
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
