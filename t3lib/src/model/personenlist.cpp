#include "personenlist.h"

PersonenList::PersonenList()
{    
    m_isChanged = false;
    m_isLoaded = false;
}

PersonenList::~PersonenList(){

    if(m_isChanged) {
        #ifdef DEBUG_MSG
            ErrorLogger::instanceOf().logError("Will save list", ErrorPosition::getErrorPosition(ErrorPOS),1);
        #endif
        exportList();
    }
}

void PersonenList::addPerson(QString name, QByteArray rsaKey)
{
    m_isChanged = true;
    m_PersonList.insert(name, rsaKey);
}

QByteArray PersonenList::getRSAKey(QString name)
{
    return m_PersonList.value(name);
}


QList<QString> PersonenList::getNameList() const
{
    return m_PersonList.keys();
}

void PersonenList::setRSAKey(QString name, QByteArray rsaKey)
{
    m_isChanged = true;
    m_PersonList.insert(name, rsaKey);
}

int PersonenList::deletePerson(QString name)
{
   m_isChanged = true;
   return m_PersonList.remove(name);
}

bool PersonenList::importList()
{
    QDomDocument doc("Friendlist");

    QDir dataDir(m_appPath+"/Data");
    if(!dataDir.exists()) {
        #ifdef DEBUG_MSG
            ErrorLogger::instanceOf().logError("Create dir in :"+ dataDir.path(), ErrorPosition::getErrorPosition(ErrorPOS),1);
        #endif
        dataDir.mkdir(dataDir.path());
    }
    QFile file(dataDir.path()+"/"+FRIENDLIST_FILENAME);

    if(!file.exists()) {
        #ifdef DEBUG_MSG
            ErrorLogger::instanceOf().logError("No friendlist exist. :", ErrorPosition::getErrorPosition(ErrorPOS),1);
        #endif
        return false;
    }
    if (!file.open(QIODevice::ReadOnly)) {
        ErrorLogger::instanceOf().logError("Can't load friendlist -> ."+file.errorString(), ErrorPosition::getErrorPosition(ErrorPOS));
        return false;
    }
    if (!doc.setContent(&file))  {
        file.close();
        ErrorLogger::instanceOf().logError("Can't parse the XML-File.", ErrorPosition::getErrorPosition(ErrorPOS),2);
        return false;
    }
   QDomElement docElement = doc.documentElement();

   QDomNode node = docElement.firstChild();
    while(!node.isNull()) {
        QDomElement element = node.toElement();
        if(!element.isNull()) {
            if(element.tagName() == "Friend" && element.attribute("Hash") == QString(QCryptographicHash::hash(element.attribute("Key").toUtf8(), QCryptographicHash::Md5).toHex())) {
                addPerson(element.attribute("Name"), element.attribute("Key").toUtf8());
            }
        }
        node = node.nextSibling();
    }
    return true;
}

void PersonenList::exportList()
{        
    QDir dataDir(m_appPath+"/Data");

    if(!dataDir.exists()) {
        #ifdef DEBUG_MSG
            ErrorLogger::instanceOf().logError("Create dir in :"+ dataDir.path(), ErrorPosition::getErrorPosition(ErrorPOS),1);
        #endif
        dataDir.mkdir(dataDir.path());
    }

    QFile file(dataDir.path()+"/"+FRIENDLIST_FILENAME);
    if (!file.open(QIODevice::WriteOnly)) {
        ErrorLogger::instanceOf().logError("Can't save friendlist " + file.errorString() + dataDir.path(), ErrorPosition::getErrorPosition(ErrorPOS));
        return;
    }

    QList<QString> FriendNames = m_PersonList.keys();
    QDomDocument doc;
    QDomElement root = doc.createElement("Friends");

    for (int i = 0; i < FriendNames.size(); i++) {
    QDomElement Friend = doc.createElement("Friend");

    Friend.setAttribute("Name", FriendNames.at(i));
    Friend.setAttribute("Key", QString(m_PersonList.value(FriendNames.at(i))));
    Friend.setAttribute("Hash", QString(QCryptographicHash::hash(m_PersonList.value(FriendNames.at(i)), QCryptographicHash::Md5).toHex()) );

    root.appendChild(Friend);
    }

    doc.appendChild(root);

    QTextStream out(&file);
    out << doc.toString();
    file.close();
    #ifdef DEBUG_MSG
        ErrorLogger::instanceOf().logError("Save friendlist successful.", ErrorPosition::getErrorPosition(ErrorPOS),1);
    #endif
}

void PersonenList::setAppPath(QString path)
{
    m_appPath = path;
    if(importList())
    {
        m_isLoaded = true;
        m_isChanged = false;
        #ifdef DEBUG_MSG
        ErrorLogger::instanceOf().logError("Load friendlist successful", ErrorPosition::getErrorPosition(ErrorPOS),1);
        #endif
    }
}
