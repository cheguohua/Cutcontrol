#include <QWidget>
#include <QTextCodec>
#include <QSettings>
#define CONGIG_DEV  "CutControlConf.ini"


void WriteConfig(QString key,QString value)
{
    QSettings *configIniWrite = new QSettings(CONGIG_DEV, QSettings::IniFormat);
    configIniWrite->setValue(key, value.toStdString().c_str());
    delete configIniWrite;
}

QString ReadConfig(QString key,QString defaultvalue)
{
    QSettings *configIniWrite = new QSettings(CONGIG_DEV, QSettings::IniFormat);
    QString value = configIniRead->value(key,"").toString();
    if(value == "")
    {
        value = defaultvalue;
    }
    delete configIniWrite;
    return value;
}

