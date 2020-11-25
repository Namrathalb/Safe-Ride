#ifndef MYWEBENGINEPAGE_H
#define MYWEBENGINEPAGE_H

#include <QObject>
#include <QWebEnginePage>
#include<QUrl>
#include<QDebug>
class MyWebEnginePage : public QWebEnginePage
{
    Q_OBJECT
public:
    MyWebEnginePage(QObject* parent = 0) : QWebEnginePage(parent){}
    bool acceptNavigationRequest(const QUrl &url, NavigationType type, bool isMainFrame);
signals:
    void linkClicked(QUrl url);
};

#endif // MYWEBENGINEPAGE_H
