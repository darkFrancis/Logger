/**
 * @file Logger.hpp
 * @brief Definition du logger des projets
 * @author Dark Francis
 * @copyright 2021 Dark Francis
 * @date 08/04/2021
 */
#ifndef LOGGER_HPP
#define LOGGER_HPP

    #include <QtCore/qglobal.h>

    #if defined(D_BUILD_PROJECTS)
    #  define LOGGER_EXPORT Q_DECL_EXPORT
    #else
    #  define LOGGER_EXPORT Q_DECL_IMPORT
    #endif

    #include <QString>

    /**
     * @header_table Logger.hpp @end_table
     * @relatesalso Logger
     * @brief L'énumération LogLvl défini le niveau de log de référence.
     *
     * Ce niveau de log est utilisé de la façon suivante : si le niveau de log
     * demandé par une fonction est inférieur ou égale à #Logger::m_lvl, le log est
     * écrit, sinon, le log est ignoré.
     */
    enum LogLvl : int
    {
        Debug   = 5, /**< Tout est logué */
        Info    = 4, /**< Seuls les logs d'info, de warning et d'erreur sont logués */
        Warning = 3, /**< Seuls les logs de warning et d'erreur sont logués */
        Error   = 2, /**< Seuls les logs d'erreur sont logués */
        Fatal   = 1, /**< Seuls les logs d'erreur fatale sont logués */
        Off     = 0  /**< Rien n'est logué */
    };

    /**
     * @header_table Logger.hpp @end_table
     * @brief La classe Logger définie l'instance de log.
     *
     * Un objet de cette classe doit être créé dans la fonction principale pour
     * pouvoir être utilisé dans le reste du code.
     */
    class LOGGER_EXPORT Logger
    {
        public:
            Logger();
            ~Logger();
            static Logger* Instance() { return m_instance; }
            bool createLog(const QString& file, int rotation = 0);
            void closeLog();
            QString currentFile() const;
            static QString version();

        public: // log
            void setLogLevel(LogLvl lvl)     { m_lvl = lvl;            }
            void debug(const QString& msg)   { printLog(Debug, msg);   }
            void info(const QString& msg)    { printLog(Info, msg);    }
            void warning(const QString& msg) { printLog(Warning, msg); }
            void error(const QString& msg)   { printLog(Error, msg);   }
            void fatal(const QString& msg)   { printLog(Fatal, msg);   }

        private:
            void printLog(LogLvl lvl, const QString& msg);
            QString rotationFileName(const QString& file, int rotation);

        private:
            static Logger* m_instance;  /**< Instance unique de la classe Logger */
            void* m_stream;             /**< Pointeur vers le flux à utiliser */
            void* m_file;               /**< Pointeur vers le fichier a utiliser */
            LogLvl m_lvl;               /**< Niveau actuel de log */
    };

    /**
     * @relatesalso Logger
     * Pointeur vers l'instance de la classe Logger.
     */
    #define qLog Logger::Instance()

#endif // LOGGER_HPP
