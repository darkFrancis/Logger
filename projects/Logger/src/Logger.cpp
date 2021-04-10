/**
 * @file Logger.cpp
 * @brief Source du logger des projets
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

// Macro de simplification d'écriture
#define logStream reinterpret_cast<QTextStream*>(m_stream)
#define logFile reinterpret_cast<QFile*>(m_file)

Logger* Logger::m_instance = nullptr;

/**
 * Constructeur de la classe Logger.
 * @throw Si une instance de la classe éxiste déjà.
 */
Logger::Logger()
{
    if(m_instance != nullptr)
    {
        throw "Une instance de Logger éxiste déjà !";
    }
    m_lvl = Debug; // Log tout par défaut
    m_instance = this;
    m_stream = nullptr;
    m_file = nullptr;
}

/**
 * Destructeur de la classe Logger. @n
 * Ferme le fichier de log en cours.
 */
Logger::~Logger()
{
    closeLog();
}

/**
 * @fn Logger* Logger::Instance()
 * @return Unique instance créée du logger
 */

/**
 * @param file Fichier de log à créé
 * @param rotation Nombre de fichiers de rotation
 * @return @li @b true si le fichier a été ouvert
 *         @li @b false sinon
 *
 * Ferme le fichier de log en cours. Si la @p rotation est fixé, supprime
 * le log maximum autorisé et décale tous les fichiers. Ouvre le nouveau
 * fichier de log.
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
 * Ferme le fichier de log en cours.
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
 * @return Fichier de log courant
 */
QString Logger::currentFile() const { return logFile ? logFile->fileName() : ""; }

/**
 * @return Version du logger
 */
QString Logger::version() { return _VERSION_; }

/**
 * @fn Logger::setLogLevel(LogLvl lvl)
 * @param lvl Nouveau niveau de log.
 */

/**
 * @fn void Logger::error(const QString& msg)
 * @param msg Message à loguer en Debug.
 * @sa LogLvl, printLog().
 */

/**
 * @fn void Logger::error(const QString& msg)
 * @param msg Message à loguer en Info.
 * @sa LogLvl, printLog().
 */

/**
 * @fn void Logger::error(const QString& msg)
 * @param msg Message à loguer en Warning.
 * @sa LogLvl, printLog().
 */

/**
 * @fn void Logger::error(const QString& msg)
 * @param msg Message à loguer en Error.
 * @sa LogLvl, printLog().
 */

/**
 * @fn void Logger::fatal(const QString& msg)
 * @param msg Message à loguer en Fatal.
 * @sa LogLvl, printLog().
 */ 

/**
 * @param lvl Niveau de log demandé
 * @param msg Message à loguer
 *
 * Ecrit une ligne de log dans le fichier ouvert en cours.@n
 * Ligne de la forme "<timestamp> | <lvl> | <msg>".
 * @note Si le message tiens sur plusieurs lignes, les lignes suivantes
 * sont de la forme "<timestamp> |       | <msg>".
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
 * @param file Fichier de base des logs
 * @param rotation Numéro de fichier de rotation
 * @return Nom du fichier avec rotation
 *
 * Le nom de fichier avec rotation est de la forme @p &lt;file>.&lt;rotation>.&lt;ext>.
 * @note La seul exception à la règle est le fichier de rotation 0 qui est le fichier
 * de log en cours.
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
