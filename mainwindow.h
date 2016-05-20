#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
  void getData();
  void putData();
private slots:
  void on_ConnectpushButton_clicked();

  void on_LimitespushButton_clicked();

  void on_Limitesslider_valueChanged(int value);
  void timerEvent(QTimerEvent *e);
  void on_StoppushButton_clicked();

private:
  int idTimer;
  Ui::MainWindow *ui;
  QTcpSocket *socket;
};

#endif // MAINWINDOW_H
