#ifndef STRINGS_MAINWINDOW_H
#define STRINGS_MAINWINDOW_H

#include <QObject>
#include <QString>

namespace mainwindowStrings
{
    QString MSG_MAINWINDOW_TITLE()
    {
        return QString::fromUtf8("Своя игра. Клиент игрока");
    }
    QString MSG_ERROR()
    {
        return QString::fromUtf8("Ошибка");
    }

    QString MSG_PLAYER_NAME_NOT_FOUND()
    {
        return QString::fromUtf8("Не задано имя игрока");
    }

    QString MSG_OK_PREFFIX()
    {
        return QString::fromUtf8("OK:#");
    }

    QString MSG_NAME1_PREFFIX()
    {
        return QString::fromUtf8("NAME1:#");
    }

    QString MSG_NAME2_PREFFIX()
    {
        return QString::fromUtf8("NAME2:#");
    }

    QString MSG_NAME3_PREFFIX()
    {
        return QString::fromUtf8("NAME3:#");
    }

    QString MSG_NAME4_PREFFIX()
    {
        return QString::fromUtf8("NAME4:#");
    }

    QString MSG_SUM1_PREFFIX()
    {
        return QString::fromUtf8("SUM1:#");
    }

    QString MSG_SUM2_PREFFIX()
    {
        return QString::fromUtf8("SUM2:#");
    }

    QString MSG_SUM3_PREFFIX()
    {
        return QString::fromUtf8("SUM3:#");
    }

    QString MSG_SUM4_PREFFIX()
    {
        return QString::fromUtf8("SUM4:#");
    }

    QString MSG_ID_PREFFIX()
    {
        return QString::fromUtf8("ID:#");
    }

    QString MSG_NAME_PREFFIX()
    {
        return QString::fromUtf8("NAME:#");
    }

    QString MSG_NUMBER_PREFFIX()
    {
        return QString::fromUtf8("NUMBER:#");
    }

    QString MSG_THEME_PREFFIX()
    {
        return QString::fromUtf8("THEME:#");
    }

    QString MSG_VALUE_PREFFIX()
    {
        return QString::fromUtf8("VALUE:#");
    }

    QString MSG_QUESTION_PREFFIX()
    {
        return QString::fromUtf8("QUESTION:#");
    }

    QString MSG_ANSWER_PREFFIX()
    {
        return QString::fromUtf8("ANSWER:#");
    }

    QString MSG_QUEUE_PREFFIX()
    {
        return QString::fromUtf8("QUEUE:#");
    }

    QString MSG_CORRECTNESS_PREFFIX()
    {
        return QString::fromUtf8("CORRECTNESS:#");
    }

    QString MSG_TIMEOUT_PREFFIX()
    {
        return QString::fromUtf8("TIMEOUT:#");
    }

    QString MSG_INWRITTING_PREFFIX()
    {
        return QString::fromUtf8("INWRITTING:#");
    }

    QString MSG_FALSTART()
    {
        return QString::fromUtf8("Фальстарт!");
    }

    QString MSG_TIME_PREFFIX()
    {
        return QString::fromUtf8("Время!");
    }

    QString MSG_BLOCK_PREFFIX()
    {
        return QString::fromUtf8("Block:#");
    }
}

#endif // STRINGS_MAINWINDOW_H
