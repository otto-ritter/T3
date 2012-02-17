#include "mainexception.h"


MainException::MainException(const QString errorMsg, const QString errorLocation, int errorType) : exception()
{
    ErrorLogger::instanceOf().logError(errorMsg, errorLocation, errorType);
    m_errorMessage = "MainException: " + errorLocation + " -> " + errorMsg;
}

MainException::~MainException() throw()
{

}

const char* MainException::what() const throw()
{
   return  qPrintable(m_errorMessage);
}

QString MainException::getMessage()
{
    return m_errorMessage;
}
