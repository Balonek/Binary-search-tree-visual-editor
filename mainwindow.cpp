#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRegularExpression>
#include <QIntValidator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    QIntValidator* validator = new QIntValidator(this);
    validator->setBottom(0);
    ui->lineEdit->setValidator(validator);

    ui->statusbar->setFixedHeight(50);
    QFont font = ui->statusbar->font();
    font.setPointSize(20);
    ui->statusbar->setFont(font);

}

MainWindow::~MainWindow()
{
    delete ui;
    delete scene;
}

void MainWindow::on_InsertButton_clicked()
{
    ui->statusbar->clearMessage();
    int value = ui->lineEdit->text().toInt();
    bst.insert(value);
    bst.visualize(scene);
    ui->statusbar->showMessage("Dodano liczbę " + QString::number(value),5000);
    update_description();
    ui->lineEdit->clear();
}

void MainWindow::on_DeleteButton_clicked()
{
    ui->statusbar->clearMessage();
    QString input = ui->lineEdit->text().trimmed();
    int value = input.toInt();
    bst.remove(value);
    if (bst.size() == 0) {
        scene->clear();
        ui->statusbar->showMessage("Drzewo jest puste.", 3000);
    } else {
        bst.visualize(scene);
    }
    update_description();
    ui->lineEdit->setText("");
}

void MainWindow::on_SearchButton_clicked()
{
    ui->statusbar->clearMessage();
    QString input = ui->lineEdit->text().trimmed();
    int value = input.toInt();
    Node* result = bst.search(value);
    if (result != nullptr) {
        ui->statusbar->showMessage("Znaleziono liczbę: " + QString::number(value) + " , jest obecna w drzewie.", 7500);
        ui->lineEdit->setText("");
    } else {
        ui->statusbar->showMessage("Nie znaleziono liczby: " + QString::number(value) + " , nie jest obecna w drzewie.", 5000);
        ui->lineEdit->setText("");
    }
}


void MainWindow::on_DeleteWholeTreeButton_clicked()
{
    scene->clear();
    bst.clear();
    ui->label_4->clear();
    ui->statusbar->showMessage("Scena została zresetowana", 5000);
}
void MainWindow::update_description() {
    QString text;
    if (bst.size() == 0) {
    } else {
        text += "Liczba elementów: " + QString::number(bst.size()) + "<br>";
        text += "Głębokość drzewa: " + QString::number(bst.depth()) + "<br>";
        text += "Minimum: " + QString::number(bst.minimum()) + "<br>";
        text += "Maksimum: " + QString::number(bst.maximum()) + "<br>";
        text += "Inorder: ";
        std::vector<int> inorderElements = bst.inorder();
        for (size_t i = 0; i < inorderElements.size(); ++i) {
            text += QString::number(inorderElements[i]) + " ";
            if ((i + 1) % 8 == 0) {
                text += "<br>";
            }
        }
    }
    text += "<br>";
    ui->label_4->setText(text);
}
