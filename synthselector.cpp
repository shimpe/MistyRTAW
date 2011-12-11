#include "synthselector.h"

SynthSelector::SynthSelector(QWidget *parent, QStringList qsl) : QComboBox(parent) {
    addItems(qsl);
}
