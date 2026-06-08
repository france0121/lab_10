#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onSolveClicked();
    void onClearClicked();
    void onExitClicked();

private:
    QTextEdit *textEditInput;
    QListWidget *listOriginal;
    QListWidget *listResult;
    QLabel *labelStatus;
    QPushButton *btnSolve, *btnClear, *btnExit;
};

#endif
