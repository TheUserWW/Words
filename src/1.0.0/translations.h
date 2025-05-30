#ifndef TRANSLATIONS_H
#define TRANSLATIONS_H

#include <QString>




// 定义语言枚举
enum Language {
    Chinese,
    English
};


extern Language currentLanguage; // 在main.cpp中定义

// 声明一个语言变化的信号，需要配合 Qt 的信号槽机制使用
extern void languageChanged();


namespace Translations {
    // 根据当前语言选择返回对应的翻译文本
    inline QString tr(const QString& chinese, const QString& english) {
        return currentLanguage == Chinese ? chinese : english;
    }

    // MainWindow
    // 将所有常量改为内联函数
    inline const QString& MAIN_WINDOW_TITLE() {
        static QString title = tr("单词学习", "Words");
        return title;
    }
    inline const QString& WORD_INPUT_PLACEHOLDER() {
        static QString placeholder = tr("输入单词", "Enter word");
        return placeholder;
    }
    inline const QString& MEANING_INPUT_PLACEHOLDER() {
        static QString placeholder = tr("输入词义", "Enter meaning");
        return placeholder;
    }
    inline const QString& ADD_BUTTON_TEXT() {
        static QString text = tr("添加", "Add");
        return text;
    }
    inline const QString& DELETE_BUTTON_TEXT() {
        static QString text = tr("删除选中单词", "Delete selected word");
        return text;
    }
    inline const QString& TEST_BUTTON_TEXT() {
        static QString text = tr("测试单词", "Test words");
        return text;
    }
    
    // Menu
    inline const QString& MENU_SETTINGS() {
        static QString text = tr("设置", "Settings");
        return text;
    }
    inline const QString& ACTION_SETTINGS() {
        static QString text = tr("设置", "Settings");
        return text;
    }
    inline const QString& ACTION_CHINESE() {
        static QString text = tr("中文", "Chinese");
        return text;
    }
    inline const QString& ACTION_ENGLISH() {
        static QString text = tr("English", "English");
        return text;
    }
    
    // TestDialog
    inline const QString& TEST_DIALOG_TITLE() {
        static QString text = tr("单词测试", "Word Test");
        return text;
    }
    inline const QString& SUBMIT_BUTTON_TEXT() {
        static QString text = tr("提交", "Submit");
        return text;
    }
    
    // 其他常量
    inline const QString& PLAY_PRONUNCIATION() {
        static QString text = tr("播放发音", "Play Pronunciation");
        return text;
    }
    inline const QString& FEMALE_VOICE() {
        static QString text = tr("女声", "Female Voice");
        return text;
    }
    inline const QString& MALE_VOICE() {
        static QString text = tr("男声", "Male Voice");
        return text;
    }
    inline const QString& WORD_COLUMN() {
        static QString text = tr("单词", "Word");
        return text;
    }
    inline const QString& MEANING_COLUMN() {
        static QString text = tr("词义", "Meaning");
        return text;
    }
    inline const QString& ACTION_COLUMN() {
        static QString text = tr("操作", "Action");
        return text;
    }
    inline const QString& EMPTY_WORD_LIST_WARNING() {
        static QString text = tr("单词列表为空，请先添加单词", "Word list is empty, please add words first");
        return text;
    }
    inline const QString& TEST_SETTINGS_TITLE() {
        static QString text = tr("测试设置", "Test Settings");
        return text;
    }
    inline const QString& TEST_MODE_GROUP() {
        static QString text = tr("测试模式", "Test Mode");
        return text;
    }
    inline const QString& WORD_TO_MEANING_MODE() {
        static QString text = tr("单词→词义", "Word→Meaning");
        return text;
    }
    inline const QString& MEANING_TO_WORD_MODE() {
        static QString text = tr("词义→单词", "Meaning→Word");
        return text;
    }
    inline const QString& START_TEST_BUTTON_TEXT() {
        static QString text = tr("开始测试", "Start Test");
        return text;
    }
    inline const QString& INSUFFICIENT_WORDS() {
        static QString text = tr("单词数量不足，至少需要4个单词", "Insufficient words, at least 4 words required");
        return text;
    }
    inline const QString& SELECT_ANSWER_PROMPT() {
        static QString text = tr("请选择一个答案", "Please select an answer");
        return text;
    }
    inline const QString& CORRECT_ANSWER() {
        static QString text = tr("回答正确!", "Correct answer!");
        return text;
    }
    inline const QString& WRONG_ANSWER() {
        static QString text = tr("回答错误! 正确答案是: %1", "Wrong answer! The correct answer is: %1");
        return text;
    }
    inline const QString& OPEN_CSV_DIALOG_TITLE() {
        static QString text = "打开CSV文件";
        return text;
    }
    inline const QString& FILE_OPEN_ERROR() {
        static QString text = "文件打开错误";
        return text;
    }
    inline const QString& FILE_OPEN_ERROR_MESSAGE() {
        static QString text = "无法打开文件，请检查文件是否存在或是否有权限访问";
        return text;
    }
    inline const QString& SAVE_CSV_DIALOG_TITLE() {
        static QString text = "保存CSV文件";
        return text;
    }
    inline const QString& FILE_SAVE_ERROR() {
        static QString text = "文件保存错误";
        return text;
    }
    inline const QString& FILE_SAVE_ERROR_MESSAGE() {
        static QString text = "无法保存文件，请检查路径是否有效";
        return text;
    }
    inline const QString& FILE_CREATE_ERROR() {
        static QString text = tr("文件创建错误", "File Creation Error");
        return text;
    }
    inline const QString& FILE_CREATE_ERROR_MESSAGE() {
        static QString text = tr("无法创建CSV文件", "Cannot create CSV file");
        return text;
    }
}

#endif // TRANSLATIONS_H
