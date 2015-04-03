#ifndef SERVERERRORS
#define SERVERERRORS
#include <QObject>

enum SERVER_ERRORS{REQ_OK,TIMEOUT, NO_CONNECTION, APP_SERVER_ERR,WEB_SERVER_ERR, REQFILE_SAVE_ERR, REQFILE_OPEN_ERR, NO_GRP, NO_CARD};
class ServerEror: public QObject
{
    Q_OBJECT
public: static QString errToString(SERVER_ERRORS err)
    {
        switch (err) {
        case REQ_OK:
            return tr("ЗАПРОС УСПЕШНО ВЫПОЛНЕН");
        case TIMEOUT:
        case NO_CONNECTION:
            return tr("СЕРВЕР НЕ ДОСТУПЕН");
        case WEB_SERVER_ERR:
        case REQFILE_SAVE_ERR:
        case REQFILE_OPEN_ERR:
            return tr("ОШИБКА ЗАПРОСА");
        case NO_GRP:
            return tr("НЕТ ТАКОЙ ГРУППЫ");
        case NO_CARD:
            return tr("НЕТ ТАКОЙ КАРТЫ");
        default:
            break;
        }
        return "";
    }
};

#endif // SERVERERRORS

