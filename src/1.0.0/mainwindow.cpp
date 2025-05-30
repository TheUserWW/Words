#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "testdialog.h"
#include "translations.h"

ButtonDelegate::ButtonDelegate(QObject *parent) : QStyledItemDelegate(parent) {}

void ButtonDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &/*index*/) const
{
    QStyleOptionButton button;
    button.text = Translations::PLAY_PRONUNCIATION(); // 添加括号调用函数
    button.rect = option.rect;

    if (option.state & QStyle::State_Selected) {
        button.state |= QStyle::State_Selected;
    }

    QApplication::style()->drawControl(QStyle::CE_PushButton, &button, painter);
}

bool ButtonDelegate::editorEvent(QEvent *event, QAbstractItemModel */*model*/, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    if (event->type() == QEvent::MouseButtonRelease) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        if (option.rect.contains(mouseEvent->pos())) {
            emit playButtonClicked(index.row());
            return true;
        }
    }
    return false;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_translator(new QTranslator(this))
{
    ui->setupUi(this);
    
    // 加载初始翻译器（中文）
    if(m_translator->load("words_zh_CN.qm", ":/translations")) {
        qApp->installTranslator(m_translator);
        currentLanguage = Chinese;
    }
    // 添加这行连接
    connect(this, &MainWindow::languageChanged, this, &MainWindow::retranslateUi);
    
    connect(ui->actionEnglish, &QAction::triggered, this, &MainWindow::on_actionEnglish_triggered);
    // 添加中文按钮连接
    connect(ui->actionChinese, &QAction::triggered, this, &MainWindow::on_actionChinese_triggered);




    // 修改声音选项
    actionVoice1 = new QAction(Translations::FEMALE_VOICE(), this);  // 添加括号调用函数
    actionVoice2 = new QAction(Translations::MALE_VOICE(), this);  // 添加括号调用函数

    // 将声音选项添加到设置菜单
    ui->menuSettings->addSeparator();
    ui->menuSettings->addAction(actionVoice1);
    ui->menuSettings->addAction(actionVoice2);

    // 连接声音选项信号
    connect(actionVoice1, &QAction::triggered, this, [this](){
        speech->setVoice(speech->availableVoices().first());
    });
    connect(actionVoice2, &QAction::triggered, this, [this](){
        speech->setVoice(speech->availableVoices().last());
    });

    model = new QStandardItemModel(this);
    model->setHorizontalHeaderLabels(QStringList{
        Translations::WORD_COLUMN(),
        Translations::MEANING_COLUMN(),
        Translations::ACTION_COLUMN()
    });
    ui->tableView->setModel(model);
    loadCSV();
    speech = new QTextToSpeech(this);

    // 移除这里的局部变量声明
    // QTranslator translator; <-- 删除这行

    ButtonDelegate *delegate = new ButtonDelegate(this);
    ui->tableView->setItemDelegateForColumn(2, delegate);
    connect(delegate, &ButtonDelegate::playButtonClicked, this, [this](int row) {
        if (row >= 0 && row < model->rowCount()) {
            QString word = model->item(row, 0)->text();
            speech->say(word);
        }
    });
}

void MainWindow::on_addButton_clicked()
{
    QString word = ui->wordInput->text();
    QString meaning = ui->meaningInput->text();

    if(!word.isEmpty() && !meaning.isEmpty()) {
        QList<QStandardItem*> rowItems;
        rowItems << new QStandardItem(word);
        rowItems << new QStandardItem(meaning);
        model->appendRow(rowItems);

        ui->wordInput->clear();
        ui->meaningInput->clear();
        
        // 添加后自动保存
        saveCSV();
    }
}

void MainWindow::on_deleteButton_clicked()
{
    QModelIndex index = ui->tableView->currentIndex();
    if(index.isValid()) {
        model->removeRow(index.row());
        // 删除后自动保存
        saveCSV();
    }
}

void MainWindow::on_playButton_clicked()
{
    QModelIndex index = ui->tableView->currentIndex();
    if(index.isValid()) {
        QString word = model->item(index.row(), 0)->text();
        speech->say(word);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


// 实现 loadCSV 函数
void MainWindow::loadCSV()
{
    QString fileName = "words.csv"; // 默认文件名
    
    QFile file(fileName);
    if (!file.exists()) {
        qDebug() << "CSV文件不存在，尝试创建新文件";
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            qDebug() << "文件创建失败，错误信息:" << file.errorString();
            QMessageBox::warning(this, Translations::FILE_CREATE_ERROR(),  // 添加括号
                Translations::FILE_CREATE_ERROR_MESSAGE());  // 添加括号
            return;
        }
        file.close();
        qDebug() << "成功创建空CSV文件";
    }

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, Translations::FILE_OPEN_ERROR(), 
            Translations::FILE_OPEN_ERROR_MESSAGE());
        return;
    }

    model->removeRows(0, model->rowCount());
    
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(",");
        if (fields.size() >= 2) {
            QList<QStandardItem*> rowItems;
            rowItems << new QStandardItem(fields[0].trimmed());
            rowItems << new QStandardItem(fields[1].trimmed());
            model->appendRow(rowItems);
        }
    }
    file.close();
}

void MainWindow::saveCSV()
{
    QString fileName = "words.csv"; // 默认文件名
    
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, Translations::FILE_SAVE_ERROR(), 
            Translations::FILE_SAVE_ERROR_MESSAGE());
        return;
    }

    QTextStream out(&file);
    for (int i = 0; i < model->rowCount(); ++i) {
        QString word = model->item(i, 0)->text();
        QString meaning = model->item(i, 1)->text();
        out << word << "," << meaning << "\n";
    }
    file.close();
}

// 实现 playPronunciation 函数
void MainWindow::playPronunciation(int row)
{
    if (row >= 0 && row < model->rowCount()) {
        QString word = model->item(row, 0)->text();
        speech->say(word);
    }
}



void MainWindow::on_actionSettings_triggered()
{
    // 这里可以添加设置功能的具体逻辑
    // 目前留空，方便后续扩展
}


void MainWindow::retranslateUi()
{
    ui->retranslateUi(this);
    
    // 更新动态创建的控件文本
    actionVoice1->setText(tr("Female Voice"));
    actionVoice2->setText(tr("Male Voice"));
    
    // 更新表格标题
    model->setHorizontalHeaderLabels(QStringList{
        tr("Word"),
        tr("Meaning"),
        tr("Action")
    });
}

void MainWindow::on_actionEnglish_triggered()
{
    qApp->removeTranslator(m_translator);
    delete m_translator;
    
    m_translator = new QTranslator(this);
    if(m_translator->load("words_en_US.qm", ":/translations")) {
        qApp->installTranslator(m_translator);
        currentLanguage = English;
        retranslateUi(); // 强制立即刷新界面
        model->setHorizontalHeaderLabels(QStringList{tr("Word"), tr("Meaning"), tr("Action")}); // 二次刷新表格标题
    }
}

void MainWindow::on_actionChinese_triggered()
{
    qApp->removeTranslator(m_translator);
    delete m_translator;
    
    m_translator = new QTranslator(this);
    if(m_translator->load("words_zh_CN.qm", ":/translations")) {
        qApp->installTranslator(m_translator);
        currentLanguage = Chinese;
        retranslateUi(); // 强制立即刷新界面
        model->setHorizontalHeaderLabels(QStringList{tr("Word"), tr("Meaning"), tr("Action")}); 
    }
}






void MainWindow::on_testButton_clicked()
{
    if(model->rowCount() == 0) {
        QMessageBox::warning(this, Translations::EMPTY_WORD_LIST_WARNING(), 
            Translations::EMPTY_WORD_LIST_WARNING());
        return;
    }

    // 获取所有单词数据
    QVector<QPair<QString, QString>> words;
    for(int i = 0; i < model->rowCount(); ++i) {
        QString word = model->index(i, 0).data().toString();
        QString meaning = model->index(i, 1).data().toString();
        words.append(qMakePair(word, meaning));
    }

    // 创建测试对话框
    TestDialog *dialog = new TestDialog(this);

    // 创建模式选择对话框
    QDialog modeDialog(this);
    modeDialog.setWindowTitle(Translations::TEST_SETTINGS_TITLE());  // 添加括号
    QVBoxLayout layout(&modeDialog);

    // 添加模式选择
    QGroupBox modeGroup(Translations::TEST_MODE_GROUP());  // 添加括号调用函数
    QVBoxLayout modeLayout;
    QRadioButton *wordToMeaning = new QRadioButton(Translations::WORD_TO_MEANING_MODE());  // 添加括号调用函数
    QRadioButton *meaningToWord = new QRadioButton(Translations::MEANING_TO_WORD_MODE());  // 添加括号调用函数
    wordToMeaning->setChecked(true);
    modeLayout.addWidget(wordToMeaning);
    modeLayout.addWidget(meaningToWord);
    modeGroup.setLayout(&modeLayout);

    // 添加测试数量设置
    QSpinBox *testCountSpin = new QSpinBox();
    testCountSpin->setRange(1, words.size());
    testCountSpin->setValue(10);

    // 添加确定按钮
    QPushButton *confirmBtn = new QPushButton(Translations::START_TEST_BUTTON_TEXT());

    QAction* chineseAction = new QAction(tr("中文"), this);
    QAction* englishAction = new QAction(tr("English"), this);
    connect(chineseAction, &QAction::triggered, [=](){ dialog->changeLanguage(true); });
    connect(englishAction, &QAction::triggered, [=](){ dialog->changeLanguage(false); });
    layout.addWidget(&modeGroup);
    layout.addWidget(new QLabel("测试数量:"));
    layout.addWidget(testCountSpin);
    layout.addWidget(confirmBtn);

    // 连接信号
    connect(confirmBtn, &QPushButton::clicked, [&](){
        bool testMode = wordToMeaning->isChecked();
        dialog->setTestData(words, testMode, testCountSpin->value());
        dialog->show();
        modeDialog.close();
    });

    modeDialog.exec();
}

void MainWindow::changeLanguage(const QString &languageFile) {
    if(m_translator) {
        qApp->removeTranslator(m_translator);
        delete m_translator;
    }
    
    m_translator = new QTranslator(this);
    qDebug() << "尝试加载翻译文件:" << ":/translations/" + languageFile;
    if(m_translator->load(":/translations/" + languageFile)) {
        qDebug() << "翻译文件加载成功";
        qApp->installTranslator(m_translator);
        emit languageChanged();  // 确保发出信号
    } else {
        qDebug() << "翻译文件加载失败:" << ":/translations/" + languageFile;
    }
}

