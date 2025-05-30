#include "testdialog.h"
#include "ui_testdialog.h"
#include "translations.h"
#include <QPainter>
#include <QTimer>
#include <QRandomGenerator>


TestDialog::TestDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TestDialog)
{
    ui->setupUi(this);
    
    // 设置初始窗口大小
    this->resize(800, 600); // 宽度800像素，高度600像素
    
    // 设置窗口缩放策略
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->setMinimumSize(600, 400); // 最小尺寸
    
    // 设置布局缩放
    ui->verticalLayout->setSizeConstraint(QLayout::SetMinimumSize);
    
    currentTestCount = 0;
    maxTestCount = 10;
    
    // 添加进度条
    progressBar = new QProgressBar(this);
    progressBar->setRange(0, maxTestCount);
    progressBar->setValue(0);
    progressBar->setTextVisible(true);
    ui->verticalLayout->insertWidget(0, progressBar);
    
    if (!ui->questionLabel || !ui->option1 || !ui->option2 || 
        !ui->option3 || !ui->option4 || !ui->submitButton) {
        QMessageBox::critical(this, "错误", "UI组件初始化失败");
        return;
    }
    
    retranslateUi();  // 添加这行
}

void TestDialog::retranslateUi()
{
    ui->retranslateUi(this);
    // 更新动态生成的文本
    progressBar->setFormat(tr("Progress: %p%"));
    // 添加其他需要动态更新的文本
}

void TestDialog::changeLanguage(bool isChinese)
{
    qApp->removeTranslator(&translator);
    if(isChinese) {
        if(translator.load(":/translations/words_zh_CN.qm")) {
            qApp->installTranslator(&translator);
        }
    } else {
        // 添加英文翻译文件加载
        if(translator.load(":/translations/words_en_US.qm")) {
            qApp->installTranslator(&translator);
        }
    }
    retranslateUi();
    update();  // 强制界面刷新
}

TestDialog::~TestDialog()
{
    delete ui;
}

void TestDialog::setTestData(const QVector<QPair<QString, QString>>& words, bool wordToMeaning, int testCount)
{
    wordList = words;
    testMode = wordToMeaning;
    maxTestCount = testCount;
    progressBar->setRange(0, maxTestCount);
    generateQuestion();
}

void TestDialog::generateQuestion()
{
    if(wordList.isEmpty()) {
        QMessageBox::warning(this, "提示", "单词列表为空");
        return;
    }
    
    // 确保有足够的不同选项
    if(wordList.size() < 4) {
        QMessageBox::warning(this, Translations::EMPTY_WORD_LIST_WARNING(), 
            Translations::INSUFFICIENT_WORDS());
        return;
    }

    // 创建可用索引列表（优先选择未使用过的单词）
    QList<int> availableIndices;
    for(int i = 0; i < wordList.size(); ++i) {
        if(!usedIndices.contains(i)) {
            availableIndices.append(i);
        }
    }

    // 如果没有未使用的单词，重置使用记录
    if(availableIndices.isEmpty()) {
        usedIndices.clear();
        for(int i = 0; i < wordList.size(); ++i) {
            availableIndices.append(i);
        }
    }

    // 随机选择一个未使用过的单词
    int questionIndex = availableIndices.at(QRandomGenerator::global()->bounded(availableIndices.size()));
    usedIndices.insert(questionIndex);
    
    // 随机选择一个单词作为问题，确保与上一题不同

    do {
        questionIndex = QRandomGenerator::global()->bounded(wordList.size());
    } while (wordList.size() > 1 && questionIndex == lastQuestionIndex);
    
    lastQuestionIndex = questionIndex; // 记录当前题目索引
    auto questionPair = wordList[questionIndex];
    
    if(testMode) {
        ui->questionLabel->setText(questionPair.first);
        currentAnswer = questionPair.second;
    } else {
        ui->questionLabel->setText(questionPair.second);
        currentAnswer = questionPair.first;
    }
    
    // 生成选项（1个正确答案+3个干扰项）
    QVector<QString> options;
    options.append(currentAnswer);
    
    // 限制尝试次数避免无限循环
    int maxAttempts = 100;
    while(options.size() < 4 && maxAttempts-- > 0) {
        int randomIndex = QRandomGenerator::global()->bounded(wordList.size());
        QString option = testMode ? wordList[randomIndex].second : wordList[randomIndex].first;
        if(!options.contains(option) && option != currentAnswer) {
            options.append(option);
        }
    }
    
    if(options.size() < 4) {
        QMessageBox::warning(this, "提示", "无法生成足够的测试选项");
        return;
    }
    
    // 打乱选项顺序
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(options.begin(), options.end(), g);
    
    // 设置选项文本
    ui->option1->setText(options[0]);
    ui->option2->setText(options[1]);
    ui->option3->setText(options[2]);
    ui->option4->setText(options[3]);
}

void TestDialog::setMaxTestCount(int count)
{
    maxTestCount = count;
}

void TestDialog::on_submitButton_clicked()
{
    QString selectedAnswer;
    if(ui->option1->isChecked()) selectedAnswer = ui->option1->text();
    else if(ui->option2->isChecked()) selectedAnswer = ui->option2->text();
    else if(ui->option3->isChecked()) selectedAnswer = ui->option3->text();
    else if(ui->option4->isChecked()) selectedAnswer = ui->option4->text();
    
    if(selectedAnswer.isEmpty()) {
        QMessageBox::warning(this, Translations::SELECT_ANSWER_PROMPT(), 
            Translations::SELECT_ANSWER_PROMPT());
        return;
    }
    
    if(selectedAnswer == currentAnswer) {
        correctAnswers++;  // 新增正确答题计数
        // 在问题标签下方显示答对提示
        ui->questionLabel->setText(ui->questionLabel->text() + "\n✔️ 你答对了!");
        
        // 暂停2秒
        QEventLoop loop;
        QTimer::singleShot(2000, &loop, &QEventLoop::quit);
        loop.exec();
        
        currentTestCount++;
        progressBar->setValue(currentTestCount);
        
        if(currentTestCount >= maxTestCount) {
            // 计算正确率
            double accuracy = (double)correctAnswers / maxTestCount * 100;
            
            // 创建自定义结果对话框
            QDialog resultDialog(this);
            resultDialog.setWindowTitle("测试结果");
            
            QVBoxLayout* layout = new QVBoxLayout(&resultDialog);
            
            // 添加正确率文字
            QLabel* accuracyLabel = new QLabel(QString("正确率: %1%").arg(accuracy, 0, 'f', 1));
            accuracyLabel->setAlignment(Qt::AlignCenter);
            
            // 添加环状进度条
            QProgressBar* circleBar = new QProgressBar();
            circleBar->setRange(0, 100);
            circleBar->setValue(accuracy);
            circleBar->setTextVisible(true);
            circleBar->setFormat("%p%");
            circleBar->setStyleSheet(R"(
                QProgressBar {
                    height: 100px;
                    width: 100px;
                    text-align: center;
                    border-radius: 50px;
                    border: 5px solid #ddd;
                }
                QProgressBar::chunk {
                    border-radius: 50px;
                    background-color: #4CAF50;
                }
            )");
            
            layout->addWidget(accuracyLabel);
            layout->addWidget(circleBar);
            layout->addWidget(new QLabel(QString("答对 %1 题 / 共 %2 题").arg(correctAnswers).arg(maxTestCount)));
            
            resultDialog.exec();
            this->close();
        } else {
            generateQuestion();
        }
    } else {
        QMessageBox::information(this, Translations::WRONG_ANSWER(),  // 添加括号
            Translations::WRONG_ANSWER().arg(currentAnswer));  // 添加括号并调用arg方法
        
        currentTestCount++;
        progressBar->setValue(currentTestCount);
        
        if(currentTestCount >= maxTestCount) {
            QMessageBox::information(this, "测试完成", QString("测试已完成! 共测试了%1题").arg(maxTestCount));
            this->close();
        } else {
            generateQuestion();
        }
    }
}

void TestDialog::resizeEvent(QResizeEvent *event)
{
    QDialog::resizeEvent(event);
    
    // 根据窗口大小调整字体大小
    int fontSize = qMax(12, this->height() / 30);
    QFont font = ui->questionLabel->font();
    font.setPointSize(fontSize);
    
    ui->questionLabel->setFont(font);
    ui->option1->setFont(font);
    ui->option2->setFont(font);
    ui->option3->setFont(font);
    ui->option4->setFont(font);
}
