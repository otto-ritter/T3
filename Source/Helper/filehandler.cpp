#include "filehandler.h"

FileHandler::FileHandler()
{
    init();
}

void FileHandler::init()
{
    m_inputFileHandler = new QFile();
    m_outputFileHandler = new QFile();
    m_infoForInputFile = new QFileInfo();
    m_infoForOutputFile = new QFileInfo();
}

void FileHandler::setInputPath(QString filePath) throw (MainException)
{
    if(filePath.isEmpty())
        return;
    QFileInfo tempInputFile(filePath) ;
    if(tempInputFile.suffix() == "key") {
        filePath = tempInputFile.canonicalPath() + "/" + tempInputFile.completeBaseName() + ".enc";
    }
    m_inputFileHandler->close();
    // Open the plan file.
    m_inputFileHandler->setFileName(filePath);
    if (!m_inputFileHandler->open(QIODevice::ReadOnly)) {
        m_inputFileHandler->close();       
        throw new MainException("Can't open file to read." + m_inputFileHandler->errorString(), ErrorPosition::getErrorPosition(ErrorPOS));
    }
    // After check the path set it.
    m_infoForInputFile->setFile(filePath);
    parseKeyPath(m_infoForInputFile);
}

void FileHandler::setOutputPath(QString filePath) throw (MainException)
{
    if(filePath.isEmpty())
        return;
    m_outputFileHandler->close();

    m_infoForOutputFile->setFile(filePath);
    qDebug() << "Check if is relative";
    if(m_infoForOutputFile->isRelative()) {
        QString tmpPath;
        filePath = m_infoForInputFile->canonicalPath() + "/" + filePath;

        qDebug() << filePath;
        m_infoForOutputFile->setFile(filePath);
    }

    // Open the plan file.
    m_outputFileHandler->setFileName(filePath);
    if(m_outputFileHandler->exists()){
        m_outputFileHandler->remove();
    }
    if (!m_outputFileHandler->open(QIODevice::Append)) {
        m_outputFileHandler->close();        
        throw new MainException("Can't open file to write. " + m_outputFileHandler->errorString(), ErrorPosition::getErrorPosition(ErrorPOS));
    }
}

bool FileHandler::write(const QByteArray & writeData)
{   
    return write(writeData, writeData.size() );
}

bool FileHandler::write(const QByteArray & writeData, int length)
{
    #ifdef DEBUG_MSG
        ErrorLogger::instanceOf().logError("(FH) Path:"+m_infoForOutputFile->absoluteFilePath()+" Write Size: = " + QString::number(writeData.size(),10) +" Content: "+ writeData +" Given Length: " + QString::number((int)length, 10), ErrorPosition::getErrorPosition(ErrorPOS),1);
    #endif
    if(!m_outputFileHandler->isOpen()){
        m_outputFileHandler->open(QIODevice::Append);
    }

    if(m_outputFileHandler->write(writeData.data(), length) > 0 ){
        m_outputFileHandler->flush();
        m_outputFileHandler->close();
        parseKeyPath(m_infoForOutputFile);
        return true;
    }
    m_outputFileHandler->close();
    return false;
}

void FileHandler::writeKey(const QString keyContent) throw (MainException)
{
    QFile file(m_keyPath);
    if (!file.open(QIODevice::WriteOnly)) {
        throw MainException("Internal Error: Can't create key-file at "+ m_keyPath +". " + QString(file.errorString()), ErrorPosition::getErrorPosition(ErrorPOS));
    }
    #ifdef DEBUG_MSG
        ErrorLogger::instanceOf().logError("(FH) KeyPath: = " + m_keyPath, ErrorPosition::getErrorPosition(ErrorPOS),1);
    #endif
    QTextStream out(&file);
    out << keyContent;
    file.close();
}

void FileHandler::parseKeyPath(QFileInfo *fromPath)
{    
    m_keyPath = fromPath->canonicalPath() + "/" + fromPath->completeBaseName() + ".key";
}

QByteArray FileHandler::readAll()
{
    QByteArray fileContent;
    fileContent = m_inputFileHandler->readAll();
    #ifdef DEBUG_MSG
        ErrorLogger::instanceOf().logError("(FH) ReadAll from Path:"+m_infoForOutputFile->absoluteFilePath()+" Size: = " + QString::number(fileContent.size(),10) +" Content: "+ fileContent , ErrorPosition::getErrorPosition(ErrorPOS),1);
    #endif
    return fileContent;
}

QByteArray FileHandler::read(int numberOfBytes) throw (MainException)
{
    QByteArray fileContent;
    if(hasNext()){
        fileContent.append(m_inputFileHandler->read(numberOfBytes));
    }
    return fileContent;
}

bool FileHandler::hasNext()
{
  return (m_inputFileHandler->atEnd()) ? false : true;
}

void FileHandler::clear()
{
    init();
}
