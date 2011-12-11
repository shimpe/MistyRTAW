#ifndef SYNTHSELECTOR_H
#define SYNTHSELECTOR_H

#include <QComboBox>
#include <QStringList>

class SynthSelector : public QComboBox
{
    Q_OBJECT
public:
    explicit SynthSelector(QWidget *parent, QStringList qsl);

signals:

public slots:

};

#endif // SYNTHSELECTOR_H
