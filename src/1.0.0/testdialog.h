#ifndef TESTDIALOG_H
#define TESTDIALOG_H

#include <QDialog>
#include <QVector>
#include <QPair>
#include <QSpinBox>
#include <QRadioButton>
#include <QMessageBox>
#include <QDebug>
#include <QRandomGenerator>
#include <QTranslator>
#include <QProgressBar>
#include <QPropertyAnimation>


namespace Ui {
class TestDialog;
}

class TestDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TestDialog(QWidget *parent = nullptr);
    void setMaxTestCount(int count);
    ~TestDialog();
    
    void setTestData(const QVector<QPair<QString, QString>>& words, bool wordToMeaning, int testCount);

protected:
    void resizeEvent(QResizeEvent *event) override;  // 添加这行声明

private slots:
    void on_submitButton_clicked();

private:
    Ui::TestDialog *ui;
    QVector<QPair<QString, QString>> wordList;
    QString currentAnswer;
    bool testMode;
    QSpinBox *testCountSpinBox;
    QProgressBar *progressBar;
    QSet<int> usedIndices;
    QTranslator translator;  // 添加翻译器成员变量
    
    void generateQuestion();
    int currentTestCount;
    int maxTestCount;
    int lastQuestionIndex = -1;
    void retranslateUi();
    int correctAnswers = 0;

public slots:
    void changeLanguage(bool isChinese);  // 添加语言切换槽函数
};

#endif // TESTDIALOG_H
