/**
 * @file Logger.cpp
 * @brief Logger sources
 * @author Dark Francis
 * @copyright 2021 Dark Francis
 * @date 08/04/2021
 */
#include "Logger.hpp"

#include <QFile>
#include <QTextStream>
#include <QFileInfo>
#include <QDir>
#include <QDateTime>
#include <QDebug>

#include "version.hpp"

// Useful macros
#define logStream reinterpret_cast<QTextStream*>(m_stream)
#define logFile reinterpret_cast<QFile*>(m_file)

Logger* Logger::m_instance = nullptr;

/**
 * Logger constructor.
 * @throw std::runtime_error if another Logger instance is already defined.
 */
Logger::Logger()
{
    if(m_instance != nullptr)
    {
        throw std::runtime_error("Une instance de Logger éxiste déjà !");
    }
    m_lvl = Debug; // Log everything by default
    m_instance = this;
    m_stream = nullptr;
    m_file = nullptr;
}

/**
 * Logger destructor. @n
 * Close the logging file.
 */
Logger::~Logger()
{
    closeLog();
}

/**
 * @fn Logger* Logger::Instance()
 * @return Unique instance of logger
 */

/**
 * @param file Log file to create
 * @param rotation File used for the rotation
 * @return @li @b true if the file is opened
 *         @li @b false otherwise
 *
 * Close the current log file if there is one. If @p rotation is setted,
 * remove the maximum authorized file and rename other log files to N+1.
 * Open the new log file.
 * @sa rotationFileName().
 */
bool Logger::createLog(const QString& file, int rotation)
{
    closeLog();
    QDir dir(QFileInfo(file).absoluteDir());
    if(!dir.exists())
    {
        dir.mkpath(".");
    }
    if(rotation > 0)
    {
        QString rotationFile = rotationFileName(file, rotation);
        if(QFile::exists(rotationFile))
        {
            QFile::remove(rotationFile);
        }
        for(int i = rotation-1; i >= 0; i--)
        {
            rotationFile = rotationFileName(file, i);
            if(QFile::exists(rotationFile))
            {
                QFile::rename(rotationFile, rotationFileName(file, i+1));
            }
        }
    }

    m_file = new QFile(QFileInfo(file).absoluteFilePath());
    if(logFile->open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate))
    {
        m_stream = new QTextStream(logFile);
        logStream->setCodec("UTF-8");
        return true;
    }
    closeLog();
    return false;
}

/**
 * Close the current log file.
 */
void Logger::closeLog()
{
    if(logFile)
    {
        logFile->close();
        delete logFile;
        m_file = nullptr;
    }
    if(logStream)
    {
        delete logStream;
        m_stream = nullptr;
    }
}

/**
 * @return Current log file
 */
QString Logger::currentFile() const { return logFile ? logFile->fileName() : ""; }

/**
 * @return Logger version
 */
QString Logger::version() { return _VERSION_; }

/**
 * @fn Logger::setLogLevel(LogLvl lvl)
 * @param lvl New log level.
 */

/**
 * @fn void Logger::error(const QString& msg)
 * @param msg Message to log on Debug.
 * @sa LogLvl, printLog().
 */

/**
 * @fn void Logger::error(const QString& msg)
 * @param msg Message to log on Info.
 * @sa LogLvl, printLog().
 */

/**
 * @fn void Logger::error(const QString& msg)
 * @param msg Message to log on Warning.
 * @sa LogLvl, printLog().
 */

/**
 * @fn void Logger::error(const QString& msg)
 * @param msg Message to log on Error.
 * @sa LogLvl, printLog().
 */

/**
 * @fn void Logger::fatal(const QString& msg)
 * @param msg Message to log on Fatal.
 * @sa LogLvl, printLog().
 */ 

/**
 * @param lvl Log level requested
 * @param msg Message to log
 *
 * Write a new line in the current log file as follow :@n
 * "<timestamp> | <lvl> | <msg>".
 * @note If it's a multiline message, following lines are added :@n
 * "<timestamp> |       | <msg>".
 */
void Logger::printLog(LogLvl lvl, const QString& msg)
{
    if(logStream && logFile && m_lvl >= lvl)
    {
        QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss.zzz");
        QString lvlStr = "###";
        switch(lvl)
        {
            case Debug:   lvlStr = "DBG"; break;
            case Info:    lvlStr = "INF"; break;
            case Warning: lvlStr = "WRN"; break;
            case Error:   lvlStr = "ERR"; break;
            case Fatal:   lvlStr = "FTL"; break;
            default: break;
        }
        QStringList msgLines = msg.split('\n');
        for(const QString& line : msgLines)
        {
            *logStream << timestamp + " | " + lvlStr + " | " + line << endl;
            // Reset
            lvlStr = "   ";
            timestamp = "                       ";
        }
    }
}

/**
 * @param file Log file base name
 * @param rotation Rotation number
 * @return Full log file name
 *
 * Log file with rotation follow the form @p &lt;file>.&lt;rotation>.&lt;ext>.
 * @note The current log file follow the form @p &lt;file>.&lt;ext>.
 */
QString Logger::rotationFileName(const QString& file, int rotation)
{
    QFileInfo info(file);
    if(rotation == 0)
    {
        return info.absoluteFilePath();
    }

    QString base = info.baseName();
    QString ext = info.suffix();
    return info.absoluteDir().absoluteFilePath(base + '.' + QString::number(rotation) + '.' + ext);
}
