#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include "bst.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_InsertButton_clicked();
    void on_DeleteButton_clicked();
    void on_SearchButton_clicked();
    void on_DeleteWholeTreeButton_clicked();
    void update_description();

private:
    Ui::MainWindow *ui;
    BST bst;
    QGraphicsScene* scene;
};

#endif // MAINWINDOW_H
