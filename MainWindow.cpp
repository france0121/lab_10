#include "MainWindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QTextEdit>
#include <QListWidget>
#include <QPushButton>
#include <QGroupBox>
#include <QMessageBox>
#include <algorithm>

using namespace std;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("ЛР 10 — Вариант 29");
    resize(900, 650);

    // ========== ГРУППА ВВОДА ==========
    textEditInput = new QTextEdit;
    textEditInput->setPlaceholderText("Введите целые числа, каждое на новой строке:\n15\n20\n7\n30\n42");

    QGroupBox *inputGroup = new QGroupBox("Входные данные");
    QVBoxLayout *inputLayout = new QVBoxLayout;
    inputLayout->addWidget(new QLabel("Введите числа (каждое на новой строке):"));
    inputLayout->addWidget(textEditInput);
    inputGroup->setLayout(inputLayout);

    // ========== ГРУППА ВЫВОДА ==========
    listOriginal = new QListWidget;
    listResult = new QListWidget;

    QGroupBox *outputGroup = new QGroupBox("Результаты");
    QHBoxLayout *outputLayout = new QHBoxLayout;

    QVBoxLayout *leftLayout = new QVBoxLayout;
    leftLayout->addWidget(new QLabel("Исходная структура:"));
    leftLayout->addWidget(listOriginal);

    QVBoxLayout *rightLayout = new QVBoxLayout;
    rightLayout->addWidget(new QLabel("Результат (обратный порядок):"));
    rightLayout->addWidget(listResult);

    outputLayout->addLayout(leftLayout);
    outputLayout->addLayout(rightLayout);
    outputGroup->setLayout(outputLayout);

    // ========== КНОПКИ ==========
    btnSolve = new QPushButton("Решение");
    btnClear = new QPushButton("Очистить");
    btnExit = new QPushButton("Выход");

    QHBoxLayout *btnLayout = new QHBoxLayout;
    btnLayout->addStretch();
    btnLayout->addWidget(btnSolve);
    btnLayout->addWidget(btnClear);
    btnLayout->addWidget(btnExit);
    btnLayout->addStretch();

    // ========== СТАТУСНАЯ СТРОКА ==========
    labelStatus = new QLabel("Введите числа и нажмите 'Решение'");
    labelStatus->setAlignment(Qt::AlignCenter);
    labelStatus->setMinimumHeight(40);
    labelStatus->setStyleSheet("QLabel { padding: 10px; border-radius: 5px; background-color: #ecf0f1; color: #34495e; }");

    // ========== ОСНОВНОЙ МАКЕТ ==========
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(inputGroup);
    mainLayout->addWidget(outputGroup);
    mainLayout->addLayout(btnLayout);
    mainLayout->addWidget(labelStatus);

    QWidget *central = new QWidget;
    central->setLayout(mainLayout);
    setCentralWidget(central);

    // ========== ПОДКЛЮЧЕНИЕ СИГНАЛОВ ==========
    connect(btnSolve, &QPushButton::clicked, this, &MainWindow::onSolveClicked);
    connect(btnClear, &QPushButton::clicked, this, &MainWindow::onClearClicked);
    connect(btnExit, &QPushButton::clicked, this, &MainWindow::onExitClicked);
}

void MainWindow::onSolveClicked() {
    listOriginal->clear();
    listResult->clear();

    // Чтение чисел из текстового поля
    vector<int> nums;
    QString text = textEditInput->toPlainText();
    QStringList lines = text.split('\n', Qt::SkipEmptyParts);

    for (const QString& line : lines) {
        bool ok;
        int val = line.trimmed().toInt(&ok);
        if (ok) {
            nums.push_back(val);
        }
    }

    if (nums.empty()) {
        labelStatus->setText("Ошибка: введите хотя бы одно число!");
        labelStatus->setStyleSheet("QLabel { background-color: #f8d7da; color: #721c24; padding: 10px; border-radius: 5px; }");
        QMessageBox::warning(this, "Ошибка", "Введите хотя бы одно число!");
        return;
    }

    // Вывод исходного массива
    for (size_t i = 0; i < nums.size(); i++) {
        listOriginal->addItem(QString("[%1] = %2").arg(i).arg(nums[i]));
    }

    // Проверка: есть ли число, оканчивающееся на 0
    bool hasZero = false;
    for (int v : nums) {
        if (v % 10 == 0) {
            hasZero = true;
            break;
        }
    }

    if (!hasZero) {
        listResult->addItem("(нет чисел, оканчивающихся на 0)");
        labelStatus->setText("Условие не выполнено: нет чисел, оканчивающихся на 0");
        labelStatus->setStyleSheet("QLabel { background-color: #f8d7da; color: #721c24; padding: 10px; border-radius: 5px; }");
        return;
    }

    // Обратный порядок
    reverse(nums.begin(), nums.end());
    for (size_t i = 0; i < nums.size(); i++) {
        listResult->addItem(QString("[%1] = %2").arg(i).arg(nums[i]));
    }

    labelStatus->setText(QString("Выполнено. Найдено чисел, оканчивающихся на 0. Новый размер: %1").arg(nums.size()));
    labelStatus->setStyleSheet("QLabel { background-color: #d4edda; color: #155724; padding: 10px; border-radius: 5px; }");
}

void MainWindow::onClearClicked() {
    textEditInput->clear();
    listOriginal->clear();
    listResult->clear();
    labelStatus->setText("Введите числа и нажмите 'Решение'");
    labelStatus->setStyleSheet("QLabel { padding: 10px; border-radius: 5px; background-color: #ecf0f1; color: #34495e; }");
    textEditInput->setFocus();
}

void MainWindow::onExitClicked() {
    close();
}

MainWindow::~MainWindow() {}
