/**
 * @file Logger.hpp
 * @brief Logger definition
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
     * @brief The LogLvl enum defines all log levels.
     *
     * The log level is use as follow : if the log level requested by a function
     * is less than or equal to #Logger::m_lvl, the log is written. The log is
     * ignored otherwise.
     */
    enum LogLvl : int
    {
        Debug   = 5, /**< Log everything */
        Info    = 4, /**< Log only info, warning or errors */
        Warning = 3, /**< Log only warning or errors */
        Error   = 2, /**< Log only errors */
        Fatal   = 1, /**< Log only fatal */
        Off     = 0  /**< Log nothing */
    };

    /**
     * @header_table Logger.hpp @end_table
     * @brief The Logger class defines the logger instance.
     *
     * A logger instance should be created in the main function. Then it can be
     * used everywhere else with the static function Logger::Instance().
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
            static Logger* m_instance;  /**< Unique instance of Logger */
            void* m_stream;             /**< Pointer to current stream */
            void* m_file;               /**< Pointer to current file */
            LogLvl m_lvl;               /**< Current log level */
    };

    /**
     * @relatesalso Logger
     * Pointer to the unique instance of Logger.
     */
    #define qLog Logger::Instance()

#endif // LOGGER_HPP
