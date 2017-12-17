#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qfiledialog.h>
#include <qmessagebox.h>
#include <qstandarditemmodel.h>
#include <QProcess>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
       pathlist(new QList<QString>)
{
    ui->setupUi(this);
    setWindowFlags(Qt::CustomizeWindowHint|Qt::WindowCloseButtonHint|Qt::WindowMinimizeButtonHint);
    statusBar()->showMessage("Power by Qt & Golang");
}

MainWindow::~MainWindow()
{
    delete ui;
}


//图片目录
void MainWindow::on_btnIn_clicked()
{
    QString file_path = QFileDialog::getExistingDirectory(this,"请选择模板保存路径...","./");
    if(file_path.isEmpty())
    {
        return;
    }
    else
    {
        ui->lineEdit->setText(file_path);
        infilePath = file_path;
    }
}

//居中
void MainWindow::on_rbCenter_clicked(bool checked)
{
   if(checked)
   {
       pos = "center";
   }
}
//底部
void MainWindow::on_rbBottom_clicked(bool checked)
{
    if(checked)
    {
        pos = "bottom";
    }
}

//顶部
void MainWindow::on_rbTop_clicked(bool checked)
{
    if(checked)
    {
        pos = "top";
    }
}
//偏左
void MainWindow::on_rbLeft_clicked(bool checked)
{
    if(checked)
    {
        pos = "left";
    }
}
//偏右
void MainWindow::on_rbRight_clicked(bool checked)
{
    if(checked)
    {
        pos = "right";
    }
}

//开始生成
void MainWindow::on_btnStart_clicked()
{
    if(ui->lineEdit->text() == nullptr)
    {
        QMessageBox::about(NULL, "提示", "请选择或输入文件路径");
        return;
    }

    out_size = QSize(500,500);
    out_space = 10;


    if(ui->spWidth->text() != nullptr){
        out_size.setWidth(ui->spWidth->text().toInt());
    }

    if(ui->spHeight->text() != nullptr){
        out_size.setHeight(ui->spHeight->text().toInt());
    }

    if(ui->spMargin->text() != nullptr){
        out_space = ui->spMargin->text().toInt();
    }

    if(pos==""){
        pos = "center";
    }

    QFileInfoList list = GetFileList(infilePath);
    total_count = 0;
    //计算图片总数
    for (int i = 0; i < list.count(); i++) {
        QFileInfo tmpFileInfo = list.at(i);
        QString filePath = tmpFileInfo.filePath();
        if(tmpFileInfo.isFile() &&((tmpFileInfo.suffix().toLower() == "png")||(tmpFileInfo.suffix().toLower() == "jpg")||(tmpFileInfo.suffix().toLower() == "jpeg"))&& -1 == pathlist->indexOf(filePath) ) {
            total_count++;
        }
    }

    if(total_count < 1) {
        QMessageBox::about(NULL, "提示", "没有找到文件");
        return;
    }

    ui->label_8->setText("总共：" + QString::number(total_count));

    for (int i = 0; i < list.count(); i++) {
        QFileInfo tmpFileInfo = list.at(i);
        QString filePath = tmpFileInfo.filePath();
        if(tmpFileInfo.isFile() &&((tmpFileInfo.suffix().toLower() == "png")||(tmpFileInfo.suffix().toLower() == "jpg")||(tmpFileInfo.suffix().toLower() == "jpeg"))&& -1 == pathlist->indexOf(filePath) ) {
            QString fileName = tmpFileInfo.fileName();
            QString fullPath = infilePath + "/" + fileName;
            QProcess p(0);
            QString runPath = QCoreApplication::applicationDirPath();
            QString command = runPath+"/PPGo_ClipImg";
            p.setWorkingDirectory(runPath);
            QStringList args;
            args.append("-f="+fullPath);
            args.append("-h=" + QString::number(out_size.height()));
            args.append("-w=" + QString::number(out_size.width()));
            args.append("-p=" + pos);
            args.append("-m=" + QString::number(out_space));
            p.execute(command,args);//command是要执行的命令,args是参数
            p.waitForFinished();
            Results();
        }
    }

    QMessageBox::about(NULL, "提示", "处理完成,图片文件夹查看结果");

}

//处理结果
void MainWindow::Results()
{
    this->handle_count++;
    double value = ((double)this->handle_count/(double)this->total_count);
    value = 100*value;
    ui->progressBar->setValue((int)value);
    ui->label_7->setText("已处理："+ QString::number(this->handle_count));
}

//获取列表
QFileInfoList MainWindow::GetFileList(QString path)
{
    QDir dir(path);
    QFileInfoList file_list = dir.entryInfoList(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    QFileInfoList folder_list = dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);

    for(int i = 0; i != folder_list.size(); i++)
    {
         QString name = folder_list.at(i).absoluteFilePath();
         QFileInfoList child_file_list = GetFileList(name);
         file_list.append(child_file_list);
    }

    return file_list;
}

//清理
void MainWindow::on_btnReset_clicked()
{
    ui->label_8->setText("总共：0");
    ui->label_7->setText("已处理：0");
    ui->lineEdit->setText("");
    ui->progressBar->setValue(0);
    this->handle_count = 0;
}


void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this,"关于图片工具","本工具可以将底色是白色或者纯色图片的核心图片切割出来，并按照自定义尺寸、边距和位置重新生成图片。https://github.com/george518/PPGo_ClipImg");
}
