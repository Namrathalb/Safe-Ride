#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QByteArrayList>
#include <QString>
#include <QJsonArray>
#include <QLabel>
#include "News.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    bool eventFilter(QObject *watched, QEvent *event);
    void replyFinished(QNetworkReply *reply);
    void slot_netwManagerFinished(QNetworkReply *reply);
    void loadNext();
	void on_pushButtonExit_clicked();
	void on_pushButtonSearch_clicked();
    void on_pushButton_Next_clicked();
    void on_pushButton_Back_clicked();
	void on_pushButton_cancel_clicked();
    void on_pushButton_refresh_clicked();
	void on_actionExit_triggered();

private:
    Ui::MainWindow *ui;

	// Members
    QByteArrayList newsheadlines;
	int nextCount = 0;
	QString nextCode = "";
	QString hashTag = "";
	QJsonArray nodesArray;
    QNetworkRequest request;

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
	QNetworkAccessManager *m_netwManager = new QNetworkAccessManager(this);

	// Constants
    const QString windowTitle = "Hash Tag News"; // Application window title
	const QString windowIcon = ":/loadimg/icon.png"; // Application icon
	const int maxFrame = 12; // Number of image frames can be display at one time
	const QString pushButtonBackLoading = "Back ...... Please wait";
	const QString pushButtonBackDefault = "Back";
	const QString pushButtonSearchDefault = "Search";
    const QString urlFirstPart = "https://www.indiatoday.in/topic";
	const QString urlSecondPart = "/?__a=1";
	const QString urlNextPagePart = "&max_id=";
};

#endif // MAINWINDOW_H
