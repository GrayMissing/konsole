/*
    Copyright 2007-2008 by Robert Knight <robertknight@gmail.com>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
    02110-1301  USA.
*/

// Own
#include "HistorySizeDialog.h"

// Qt
#include <QtGui/QButtonGroup>
#include <QtGui/QVBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QRadioButton>
#include <QtGui/QWidget>

// KDE
#include <KLocalizedString>
#include <KNumInput>

// Konsole
#include "SessionManager.h"

using namespace Konsole;

HistorySizeDialog::HistorySizeDialog(QWidget* aParent)
    :  KDialog(aParent)
    ,  _noHistoryButton(0)
    ,  _fixedHistoryButton(0)
    ,  _unlimitedHistoryButton(0)
    ,  _lineCountBox(0)
{
    // basic dialog properties
    setPlainCaption(i18n("Adjust Scrollback"));
    setButtons(KDialog::Ok | KDialog::Cancel);
    setDefaultButton(KDialog::Ok);
    setModal(false);

    // dialog widgets
    QWidget* dialogWidget = new QWidget(this);
    setMainWidget(dialogWidget);

    QVBoxLayout* dialogLayout = new QVBoxLayout(dialogWidget);

    _noHistoryButton        = new QRadioButton(i18n("No scrollback"));
    _fixedHistoryButton     = new QRadioButton(i18n("Fixed size scrollback: "));
    _unlimitedHistoryButton = new QRadioButton(i18n("Unlimited scrollback"));

    QButtonGroup* modeGroup = new QButtonGroup(this);
    modeGroup->addButton(_noHistoryButton);
    modeGroup->addButton(_fixedHistoryButton);
    modeGroup->addButton(_unlimitedHistoryButton);

    _lineCountBox = new KIntSpinBox(this);

    // minimum lines = 1 ( for 0 lines , "No History" mode should be used instead )
    // maximum lines is arbitrarily chosen, I do not think it is sensible to allow this
    // to be set to a very large figure because that will use large amounts of memory,
    // if a very large log is required, "Unlimited History" mode should be used
    _lineCountBox->setRange(1 , 100000);

    _lineCountBox->setValue(HistorySizeDialog::defaultLineCount);
    _lineCountBox->setSingleStep(HistorySizeDialog::defaultLineCount / 10);
    _lineCountBox->setSuffix(ki18ncp("Unit of scrollback", " line", " lines"));

    _fixedHistoryButton->setFocusProxy(_lineCountBox);
    connect(_fixedHistoryButton , SIGNAL(clicked()) ,
            _lineCountBox , SLOT(selectAll()));

    QHBoxLayout* lineCountLayout = new QHBoxLayout();
    lineCountLayout->addWidget(_fixedHistoryButton);
    lineCountLayout->addWidget(_lineCountBox);

    QLabel* warningLabel = new QLabel(i18n("<center>The adjustment is only temporary</center>"), this);
    warningLabel->setStyleSheet("text-align:center; font-weight:normal; color:palette(dark)");

    dialogLayout->addWidget(warningLabel);
    dialogLayout->insertSpacing(-1, 5);
    dialogLayout->addWidget(_noHistoryButton);
    dialogLayout->addLayout(lineCountLayout);
    dialogLayout->addWidget(_unlimitedHistoryButton);
    dialogLayout->insertSpacing(-1, 10);

    connect(this, SIGNAL(accepted()), this, SLOT(emitOptionsChanged()));
}

void HistorySizeDialog::emitOptionsChanged()
{
    emit optionsChanged(mode() , lineCount());
}

void HistorySizeDialog::setMode(Enum::HistoryModeEnum historyMode)
{
    if (historyMode == Enum::NoHistory) {
        _noHistoryButton->setChecked(true);
    } else if (historyMode == Enum::FixedSizeHistory) {
        _fixedHistoryButton->setChecked(true);
    } else if (historyMode == Enum::UnlimitedHistory) {
        _unlimitedHistoryButton->setChecked(true);
    }

}

Enum::HistoryModeEnum HistorySizeDialog::mode() const
{
    if (_noHistoryButton->isChecked())
        return Enum::NoHistory;
    else if (_fixedHistoryButton->isChecked())
        return Enum::FixedSizeHistory;
    else if (_unlimitedHistoryButton->isChecked())
        return Enum::UnlimitedHistory;

    Q_ASSERT(false);
    return Enum::NoHistory;
}

int HistorySizeDialog::lineCount() const
{
    return _lineCountBox->value();
}

void HistorySizeDialog::setLineCount(int lines)
{
    _lineCountBox->setValue(lines);
    _lineCountBox->setSingleStep(lines / 10);
}

#include "HistorySizeDialog.moc"
