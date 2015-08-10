#include "errorlogger.h"

ErrorLogger& ErrorLogger::instanceOf()
{
    static ErrorLogger m_instance;
    return m_instance;
}

void ErrorLogger::logError(QString ErrorMsg, QString ErrorLocation, int type)
{
    QDate currentDate = QDate::currentDate();
    QTime currentTime = QTime::currentTime();
    QString errorType;

    switch(type)
    {
        case 1: {errorType="( Information )"; break;}
        case 2: {errorType="( Warning )"; break;}
        case 3: {errorType="( Error )"; break;}
        default: {errorType="( Warning )"; break;}
    }

    QString MSG = QString(currentDate.toString("dd.MM.yyyy")+"-"+currentTime.toString("hh:mm:ss") +""+ErrorLocation+": "+ErrorMsg+" "+errorType);
    qDebug() << MSG;
    QFile file(m_appPath+"/"+LOG_FILENAME);
    if (file.open(QIODevice::Append))
    {
        QTextStream log(&file);
        log << MSG << endl;
    }
}

void ErrorLogger::setAppPath(QString path)
{
    m_appPath = path;
}
