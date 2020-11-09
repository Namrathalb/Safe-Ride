#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QtNetwork/QNetworkAccessManager>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	this->setWindowIcon(QIcon(windowIcon));
	this->setWindowTitle(windowTitle);

	ui->pushButtonSearch->setEnabled(false);

	// Setup SIGNAL and SLOT
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
    connect(m_netwManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(slot_netwManagerFinished(QNetworkReply*)));
	ui->pushButtonSearch->setEnabled(true);
}

MainWindow::~MainWindow()
{
    delete ui;
//	delete currentFrame;
	delete manager;
	delete m_netwManager;
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonRelease)
    {

    }

    return QMainWindow::eventFilter(watched, event);
}

void MainWindow::on_pushButtonExit_clicked()
{
    this->close();
}

void MainWindow::on_pushButtonSearch_clicked()
{
	ui->pushButtonSearch->setEnabled(false);
	hashTag = ui->lineEdit->text();
	if (hashTag == "")
    {
        ui->pushButton_Back->setEnabled(false);
        ui->pushButton_Next->setEnabled(false);
		ui->pushButtonSearch->setEnabled(true);
		ui->pushButtonSearch->setText(pushButtonSearchDefault);
        return;
    }
	nextCount = 0;
	nextCode = "";
    newsheadlines.clear();
	nodesArray = QJsonArray{};
	QString url = urlFirstPart;
	url.append(hashTag);
	url.append(urlSecondPart);
    QNetworkRequest req(url);
	manager->get(req);
}

void MainWindow::replyFinished(QNetworkReply *reply)
{

}

void MainWindow::slot_netwManagerFinished(QNetworkReply *reply)
{
    //CONNECT m_netwManager SIGNAL finished
    if (reply->error() != QNetworkReply::NoError)
    {
        qDebug() << "Error in" << reply->url() << ":" << reply->errorString();
        return;
    }
}

void MainWindow::on_actionExit_triggered()
{
    this->close();
}

void MainWindow::loadNext()
{

}


void MainWindow::on_pushButton_refresh_clicked()
{

}

void MainWindow::on_pushButton_Next_clicked()
{
    ui->pushButton_Next->setEnabled(false);
	ui->pushButton_Back->setEnabled(false);
	ui->pushButtonSearch->setEnabled(false);
	ui->pushButton_Back->setText(pushButtonBackLoading);
	nextCount++;
    loadNext();
}

void MainWindow::on_pushButton_Back_clicked()
{

}

void MainWindow::on_pushButton_cancel_clicked()
{
	// Back to the first tab
    ui->tabWidget->setCurrentIndex(0);
}

