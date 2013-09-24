#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //own logic
    this->allAccounts = new Account("allAccounts", 0.0f);

    ui->setupUi(this);

    //addBar
    ui->lineEditDescription->setFocus();

    //set dateEdit to currentDate
    ui->dateEdit->setDate(QDate::currentDate());

    //setColumn, it's width and how they named
    ui->tableWidgetBooking->setColumnCount(4);
    ui->tableWidgetBooking->setColumnWidth(0, 250); //Description
    ui->tableWidgetBooking->setColumnWidth(1, 100); //Price
    ui->tableWidgetBooking->setColumnWidth(2, 100); //Date
    ui->tableWidgetBooking->setColumnWidth(2, 100); //Total
    QStringList columnText;
    columnText << "Description" << "Price" << "Date" << "Total";
    ui->tableWidgetBooking->setHorizontalHeaderLabels(columnText);

    //sidebar
    ui->rbtn_allAccounts->setChecked(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::add2List()
{
    //Get a new row
    int insertRow = ui->tableWidgetBooking->rowCount();
    ui->tableWidgetBooking->insertRow(insertRow);

    //insert description, price and date into the table
    ui->tableWidgetBooking->setItem(insertRow, 0, new QTableWidgetItem(ui->lineEditDescription->text()));
    ui->tableWidgetBooking->setItem(insertRow, 1, new QTableWidgetItem(ui->lineEditPrice->text()));
    ui->tableWidgetBooking->setItem(insertRow, 2,  new QTableWidgetItem(ui->dateEdit->date().toString()));

    //Set

    //Total calculation
    QString *qstr_allAccount = new QString(ui->lineEditPrice->text());
    this->allAccounts->setMoney(qstr_allAccount->toFloat());
    QString qstr_totalTable = QString("%1").arg(this->allAccounts->getMoney()); //convert: float ==> qstring
    ui->tableWidgetBooking->setItem(insertRow, 3, new QTableWidgetItem( qstr_totalTable ));
}

//LINE EDIT for add accounts
void MainWindow::on_lineEdit_accountName_returnPressed()
{
    //Add newUser-radiobutton
    QString new_account_name = ui->lineEdit_accountName->text();

//    Account new_account_name

    QRadioButton *newAccount = new QRadioButton(this);
    newAccount->setText(new_account_name);
    newAccount->setChecked(true);
    newAccount->show();
    int userRow = ui->gLay_userSwitch->rowCount();
    ui->gLay_userSwitch->addWidget(newAccount, userRow, 0, 1, 1);

    //add newLabel for total account TODO: GROUP RADIOBUTTONS
    QLabel *newLabel = new QLabel(this);
    newLabel->setText("0,00");
    ui->gLay_userSwitch->addWidget(newLabel, userRow, 1, 1, 1);

    ui->lineEdit_accountName->setText(NULL);
}



void MainWindow::on_lineEditDescription_returnPressed()
{
    this->add2List();
}

void MainWindow::on_lineEditPrice_returnPressed()
{
    this->add2List();
}
