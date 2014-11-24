#ifndef __ZEN_LOG__
#define __ZEN_LOG__

#include <mutex>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <ctime>

#include <loki/SmartPtr.h>
#include <loki/Singleton.h>

#include "threads.h"

namespace Zen
{

    /**
     * @brief Система ведения логов
     */
    namespace Log
    {
    
        /**
         * @brief Базовый класс каналов логгирования
         * Используется как полиморфная база
         */
        class ChannelBase
        {
        public:
            ChannelBase() {};
            virtual ~ChannelBase()
            {};

            /**
             * @brief Отправить сообщение в канал
             *
             * @param level Уровень сообщения
             * @param message Текст сообщения
             * @param time Время возникновения сообщения
             */
            virtual void SendMessage(std::string level, std::string message, std::time_t time) = 0;
        protected:

            /**
             * @brief Форматирование даты-времени
             *
             * @param timeptr Указатель на структуру std::tm
             * @return Строка форматированного времени
             */
            std::string formattime(const std::tm *timeptr);

        };

        /**
         * @brief Базовый класс каналов сообщений
         * @details Исползуется как база для наследования каналов с стратегиями синхронизации
         *
         * @tparam LockStrategy Стратегия многопоточной синхронизации
         */
        template <
            class LockStrategy //Стратегия многопоточной синхронизации
            >
        class Channel : public ChannelBase
        {
        public:
            Channel() {};
            virtual ~Channel() {};

            /**
             * @brief Отправить сообщение в канал
             *
             * @param level Уровень сообщения
             * @param message Текст сообщения
             * @param time Время возникновения сообщения
             */
            virtual void SendMessage(std::string level, std::string message, std::time_t time)
            {
                LockStrategy lock;
                SendMessageImpl(std::string(formattime(std::localtime(&time))) + "\t" + level + "\t" + message);
            }
        protected:

            /**
             * @brief Реализация отправки сообщения в канал
             * @details Перегруженная в наследниках выполняет реальную работу по остылке сообщений в канал
             *
             * @param txt Текст сообщения после форматирования
             */
            virtual void SendMessageImpl(std::string txt) = 0;
        };

        /**
         * @brief Канал логгирующий в io stream (std::cout по умолчанию)
         *
         * @tparam LockStrategy Стратегия многопоточной синхронизации
         */
        template <
            class LockStrategy //Стратегия многопоточной синхронизации
            >
        class OstreamChannel: public Channel<LockStrategy>
        {
        public:
            OstreamChannel()
                : mOut(&std::cout)
            {};

            OstreamChannel(std::ostream *out)
                : mOut(out)
            {};


            virtual ~OstreamChannel() {};
        protected:
            virtual void SendMessageImpl(std::string txt)
            {
                (*mOut) << txt << std::endl;
            };
        private:
            std::ostream *mOut;
        };

        /**
         * @brief Логгирование в файл
         *
         * @tparam LockStrategy Стратегия многопоточной синхронизации
         */
        template <
            class LockStrategy //Стратегия многопоточной синхронизации
            >
        class FstreamChannel : public OstreamChannel<LockStrategy>
        {
        public:
            FstreamChannel(const char *filename)
                : mStream(filename,  std::ofstream::out | std::ofstream::app)
                , OstreamChannel<LockStrategy>(&mStream)
            {};
            virtual ~FstreamChannel()
            {
            };
        private:
            std::ofstream mStream;
        };

        template<class LogType> class LogStream;

        /**
         * @brief Стандартная конфигурация логгера
         *
         * @tparam TLog Полный тип логгера для конфигурирования
         */
        template<class TLog>
        struct LogConfiguration
        {
            static void Configure(TLog *log)
            {
                log->template AddChannel<OstreamChannel>();
                log->template AddChannel<FstreamChannel>("log.txt");
            }
        };

        /**
         * @brief Базовая реализация логгера
         *
         * @tparam LockStrategy Стратегия многопоточной синхронизации
         * @tparam Configuration Конфигурация логгера
         */
        template <
            class LockStrategy =  NoLock, //Стратегия многопоточной синхронизации
            template<class> class Configuration = LogConfiguration //Конфигурация логгера
            >
        class LogImpl
        {

        public:
            /**
             * @brief Полная спецификация текущего типа логгера
             */
            typedef LogImpl<LockStrategy, Configuration> LogType;


            /**
             * @brief Тип потока логгирования
             */
            typedef LogStream<LogType> LogStreamType;

            /**
             * @brief Тип указателя на канал
             */
            typedef Loki::SmartPtr<ChannelBase> ChannelPtr;

            /**
             * @brief Тип контейнера заблокированных каналов
             */
            typedef std::map<std::string, bool> LevelMap;

            LogImpl()
                : mChannels()
            {
                Configuration<LogType>::Configure(this);
            };
            ~LogImpl()
            {};

            /**
             * @brief Добавить канал логгирования
             * @details Добавить канал лггирования с конструктором по умолчанию
             *
             * @tparam ChannelType Тип канала логгирования
             */
            template <template<class> class ChannelType>
            void AddChannel()
            {
                LockStrategy lock;
                ChannelPtr p(new ChannelType<LockStrategy>());
                mChannels.push_back(p);
            };

            /**
             * @brief Добавить канал логгирования
             * @details Добавить канал логгирования с параметром конструктора
             *
             * @param param Параметр конструктора
             * @tparam ChannelType Тип канала логгирования
             * @tparam TParam Тип параметра конструктора канала логгирования
             */
            template <template<class> class ChannelType, class TParam>
            void AddChannel(TParam param)
            {
                LockStrategy lock;
                ChannelPtr p(new ChannelType<LockStrategy>(param));
                mChannels.push_back(p);
            };

            /**
             * @brief Записать сообщение лога
             *
             * @param level Уровень сообщения
             * @param message Текст сообщения
             */
            void LogMessage(std::string level, std::string message)
            {

				if (message == "" || level == "")
					return;
                bool disabled = false;
                LevelMap::iterator it = mDisabledLevels.find(level);
                if (it != mDisabledLevels.end())
                {
                    disabled = it->second;
                }
                else
                {
                    mDisabledLevels[level] = false;
                }

                if (!disabled)
                {
                    std::time_t msgTime = std::time(NULL);
                    for (auto channel : mChannels)
                    {
                        channel->SendMessage(level, message, msgTime);
                    }
                }
            }

            /**
             * @brief Отключить уровень логгирования
             *
             * @param level Уровень
             */
            inline void DisableLevel(std::string level)
            {
                mDisabledLevels[level] = true;
            }

            inline LogStreamType Debug()
            {
                return GetLogStream("Debug");
            }

            inline void Debug(std::string msg)
            {
                return LogMessage("Debug", msg);
            }

            inline LogStreamType Info()
            {
                return GetLogStream("Info");
            }

            inline void Info(std::string msg)
            {
                return LogMessage("Info", msg);
            }

            inline LogStreamType Error()
            {
                return GetLogStream("Error");
            }

            inline void Error(std::string msg)
            {
                return LogMessage("Error", msg);
            }

            inline LogStreamType Critical()
            {
                return GetLogStream("Critical");
            }

            inline void Critical(std::string msg)
            {
                return LogMessage("Critical", msg);
            }

            inline LogStreamType Warning()
            {
                return GetLogStream("Warning");
            }

            inline void Warning(std::string msg)
            {
                return LogMessage("Warning", msg);
            }

            inline LogStreamType Log(std::string lvl)
            {
                return GetLogStream(lvl);
            }

        private:
            inline LogStreamType GetLogStream(std::string lvl)
            {
                return LogStreamType(this, lvl);
            }

            std::vector<ChannelPtr> mChannels;
            LevelMap mDisabledLevels;
        };

        /**
         * @brief Однопоточный лог
         */
        typedef LogImpl<NoLock> STLogType;

        /**
         * @brief Синглтон однопоточного лога
         */
        typedef Loki::SingletonHolder<STLogType> STLog;

        /**
         * @brief Многопоточный лог
         */
        typedef LogImpl<MutexLock> MTLogType;

        /**
         * @brief Синглтон многопоточного лога
         */
        typedef Loki::SingletonHolder<MTLogType, Loki::CreateUsingNew, Loki::DefaultLifetime, Zen::MutexLockerPolicy> MTLog;

        /**
         * @brief Поток помошник логгирования
         * @details Используется для реализации констркуций log.Debug() << "msg";
         *
         * @tparam LogType Полная типизация лога
         */
        template<class LogType>
        class LogStream : public std::stringstream
        {
        public:

            LogStream(LogType *log, std::string level)
                : mLog(log)
                , mLevel(level)
            {};
            ~LogStream()
            {
                flush();
                mLog->LogMessage(mLevel, str());
            };

            LogStream(LogStream   &&__rhs)
                : mLog(std::move(__rhs.mLog))
                , mLevel(std::move(__rhs.mLevel))
            {};

            LogStream(const LogStream &r)
                : mLog(r.mLog)
                , mLevel(r.mLevel)
            {
                str(r.str());
            }

        private:
            LogType *mLog;
            std::string mLevel;
        };

    }

}

#endif