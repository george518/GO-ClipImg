#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCache>
#include <QFile>
#include <QFileInfoList>
#include <QTableView>
#include <QSize>


class QDataModel;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
protected:
    QFileInfoList GetFileList(QString path);

private slots:

    void on_btnIn_clicked();

    void on_rbCenter_clicked(bool checked);

    void on_rbBottom_clicked(bool checked);

    void on_btnStart_clicked();

    void Results();

    void on_btnReset_clicked();

    void on_rbTop_clicked(bool checked);

    void on_rbLeft_clicked(bool checked);

    void on_rbRight_clicked(bool checked);

    void on_actionAbout_triggered();

private:
    Ui::MainWindow *ui;
    QString infilePath;
    QList<QString> *pathlist;
    QString pos;
    QSize out_size;
    int out_space;
    int handle_count;
    int total_count;

};

#endif // MAINWINDOW_H
