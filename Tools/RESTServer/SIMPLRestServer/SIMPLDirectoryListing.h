#ifndef _simpldirectorylisting_h_
#define _simpldirectorylisting_h_

#include <QtCore/QDir>
#include <QtCore/QString>
#include <QtCore/QDate>
#include <QtCore/QVector>

class SIMPLDirectoryListing
{
public:
    static void ParseDir(QDir directory, QVector<QString>& fileNames, QVector<QDate>& dates);
    static QString CreateHTMLTable(QVector<QString> fileNames, QVector<QDate> dates);
};

#endif
