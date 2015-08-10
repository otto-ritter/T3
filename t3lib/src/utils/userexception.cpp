#include "userexception.h"

UserException::UserException(const QString errorMsgForUser, const QString errorMsg, const QString errorLocation ) : MainException(errorMsg, errorLocation)
{    
     m_userErrorMessage = errorMsgForUser;
     if(errorMsg.isEmpty()){
        m_errorMessage = errorMsgForUser;
     }
}

UserException::~UserException() throw() {}

QString UserException::getMessage() throw()
{
    return m_userErrorMessage;
}

QString UserException::getDebugMessage() throw() {
    return m_errorMessage;
}
