/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the demonstration applications of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QAction>
#include <QApplication>
#include <QClipboard>
#include <QColorDialog>
#include <QComboBox>
#include <QFontComboBox>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QFontDatabase>
#include <QMenu>
#include <QMenuBar>
#include <QTextCodec>
#include <QTextEdit>
#include <QStatusBar>
#include <QToolBar>
#include <QTextCursor>
#include <QTextDocumentWriter>
#include <QTextList>
#include <QtDebug>
#include <QCloseEvent>
#include <QMessageBox>
#include <QMimeData>
#include <QMimeDatabase>
#if defined(QT_PRINTSUPPORT_LIB)
#include <QtPrintSupport/qtprintsupportglobal.h>
#if QT_CONFIG(printer)
#if QT_CONFIG(printdialog)
#include <QPrintDialog>
#endif
#include <QPrinter>
#if QT_CONFIG(printpreviewdialog)
#include <QPrintPreviewDialog>
#endif
#endif
#endif

#include "textedit.h"

#ifdef Q_OS_MAC
const QString rsrcPath = ":/images/mac";
#else
const QString rsrcPath = ":/images/win";
#endif

TextEdit::TextEdit(QWidget *parent, Client *client, QString filename)
    : QMainWindow(parent), client(client), fileName(filename)
{
    counter=0;
    siteId=client->getSiteId();
#ifdef Q_OS_OSX
    setUnifiedTitleAndToolBarOnMac(true);
#endif
    setWindowTitle(QCoreApplication::applicationName());
    textEdit = new QTextEdit(this);
    connect(textEdit, &QTextEdit::currentCharFormatChanged,
            this, &TextEdit::currentCharFormatChanged);
    connect(textEdit, &QTextEdit::cursorPositionChanged,
            this, &TextEdit::cursorPositionChanged);
    /*------------Aggiunta da noi------*/
    //connect(this, SIGNAL(message_ready(Message m)),
    //        client, SLOT(onMessageReady(Message m)));
    connect(this, &TextEdit::message_ready,
            client, &Client::onMessageReady);
    connect(client, &Client::message_from_server,
            this, &TextEdit::onMessageFromServer);
    connect(textEdit->document(), &QTextDocument::contentsChange,
            this, &TextEdit::onTextChanged);
    connect(client, &Client::file_Ready,this,&TextEdit::onFileReady);

    /*------------Fine aggiunta--------*/
    setCentralWidget(textEdit);

    setToolButtonStyle(Qt::ToolButtonFollowStyle);
    setupFileActions();
    setupEditActions();
    setupTextActions();

    {
        QMenu *helpMenu = menuBar()->addMenu(tr("Help"));
        helpMenu->addAction(tr("About"), this, &TextEdit::about);
        helpMenu->addAction(tr("About &Qt"), qApp, &QApplication::aboutQt);
    }

    QFont textFont("Helvetica");
    textFont.setStyleHint(QFont::SansSerif);
    textEdit->setFont(textFont);
    fontChanged(textEdit->font());
    colorChanged(textEdit->textColor());
    alignmentChanged(textEdit->alignment());

    connect(textEdit->document(), &QTextDocument::modificationChanged,
            actionSave, &QAction::setEnabled);
    connect(textEdit->document(), &QTextDocument::modificationChanged,
            this, &QWidget::setWindowModified);
    connect(textEdit->document(), &QTextDocument::undoAvailable,
            actionUndo, &QAction::setEnabled);
    connect(textEdit->document(), &QTextDocument::redoAvailable,
            actionRedo, &QAction::setEnabled);

    setWindowModified(textEdit->document()->isModified());
    actionSave->setEnabled(textEdit->document()->isModified());
    actionUndo->setEnabled(textEdit->document()->isUndoAvailable());
    actionRedo->setEnabled(textEdit->document()->isRedoAvailable());

#ifndef QT_NO_CLIPBOARD
    actionCut->setEnabled(false);
    connect(textEdit, &QTextEdit::copyAvailable, actionCut, &QAction::setEnabled);
    actionCopy->setEnabled(false);
    connect(textEdit, &QTextEdit::copyAvailable, actionCopy, &QAction::setEnabled);

    connect(QApplication::clipboard(), &QClipboard::dataChanged, this, &TextEdit::clipboardDataChanged);
#endif

    textEdit->setFocus();
    //setCurrentFileName(QString());  ****MODIFICATA DA NOI*****
    setCurrentFileName(fileName);


#ifdef Q_OS_MACOS
    // Use dark text on light background on macOS, also in dark mode.
    QPalette pal = textEdit->palette();
    pal.setColor(QPalette::Base, QColor(Qt::white));
    pal.setColor(QPalette::Text, QColor(Qt::black));
    textEdit->setPalette(pal);
#endif
}


void TextEdit::closeEvent(QCloseEvent *e)
{
    /*qui devo sostituirlo con la disconnessione non dal server ma eliminare il file dalla connessione */

    /*aggiunta*/
    client->closeFile(fileName);
    emit closeWindow();
    /*fine aggiunta*/
    hide();
    /*if (maybeSave())
        e->accept();
    else
        e->ignore();*/
}

void TextEdit::setupFileActions()
{
    QToolBar *tb = addToolBar(tr("File Actions"));
    QMenu *menu = menuBar()->addMenu(tr("&File"));

    const QIcon newIcon = QIcon::fromTheme("document-new", QIcon(rsrcPath + "/filenew.png"));
    QAction *a = menu->addAction(newIcon,  tr("&New"), this, &TextEdit::fileNew);
    tb->addAction(a);
    a->setPriority(QAction::LowPriority);
    a->setShortcut(QKeySequence::New);

    const QIcon openIcon = QIcon::fromTheme("document-open", QIcon(rsrcPath + "/fileopen.png"));
    a = menu->addAction(openIcon, tr("&Open..."), this, &TextEdit::fileOpen);
    a->setShortcut(QKeySequence::Open);
    tb->addAction(a);

    menu->addSeparator();

    const QIcon saveIcon = QIcon::fromTheme("document-save", QIcon(rsrcPath + "/filesave.png"));
    actionSave = menu->addAction(saveIcon, tr("&Save"), this, &TextEdit::fileSave);
    actionSave->setShortcut(QKeySequence::Save);
    actionSave->setEnabled(false);
    tb->addAction(actionSave);

    a = menu->addAction(tr("Save &As..."), this, &TextEdit::fileSaveAs);
    a->setPriority(QAction::LowPriority);
    menu->addSeparator();

#if defined(QT_PRINTSUPPORT_LIB) && QT_CONFIG(printer)
    const QIcon printIcon = QIcon::fromTheme("document-print", QIcon(rsrcPath + "/fileprint.png"));
    a = menu->addAction(printIcon, tr("&Print..."), this, &TextEdit::filePrint);
    a->setPriority(QAction::LowPriority);
    a->setShortcut(QKeySequence::Print);
    tb->addAction(a);

    const QIcon filePrintIcon = QIcon::fromTheme("fileprint", QIcon(rsrcPath + "/fileprint.png"));
    menu->addAction(filePrintIcon, tr("Print Preview..."), this, &TextEdit::filePrintPreview);

    const QIcon exportPdfIcon = QIcon::fromTheme("exportpdf", QIcon(rsrcPath + "/exportpdf.png"));
    a = menu->addAction(exportPdfIcon, tr("&Export PDF..."), this, &TextEdit::filePrintPdf);
    a->setPriority(QAction::LowPriority);
    a->setShortcut(Qt::CTRL + Qt::Key_D);
    tb->addAction(a);

    menu->addSeparator();
#endif

    a = menu->addAction(tr("&Quit"), this, &QWidget::close);
    a->setShortcut(Qt::CTRL + Qt::Key_Q);
}

void TextEdit::setupEditActions()
{
    QToolBar *tb = addToolBar(tr("Edit Actions"));
    QMenu *menu = menuBar()->addMenu(tr("&Edit"));

    const QIcon undoIcon = QIcon::fromTheme("edit-undo", QIcon(rsrcPath + "/editundo.png"));
    actionUndo = menu->addAction(undoIcon, tr("&Undo"), textEdit, &QTextEdit::undo);
    actionUndo->setShortcut(QKeySequence::Undo);
    tb->addAction(actionUndo);

    const QIcon redoIcon = QIcon::fromTheme("edit-redo", QIcon(rsrcPath + "/editredo.png"));
    actionRedo = menu->addAction(redoIcon, tr("&Redo"), textEdit, &QTextEdit::redo);
    actionRedo->setPriority(QAction::LowPriority);
    actionRedo->setShortcut(QKeySequence::Redo);
    tb->addAction(actionRedo);
    menu->addSeparator();

#ifndef QT_NO_CLIPBOARD
    const QIcon cutIcon = QIcon::fromTheme("edit-cut", QIcon(rsrcPath + "/editcut.png"));
    actionCut = menu->addAction(cutIcon, tr("Cu&t"), textEdit, &QTextEdit::cut);
    actionCut->setPriority(QAction::LowPriority);
    actionCut->setShortcut(QKeySequence::Cut);
    tb->addAction(actionCut);

    const QIcon copyIcon = QIcon::fromTheme("edit-copy", QIcon(rsrcPath + "/editcopy.png"));
    actionCopy = menu->addAction(copyIcon, tr("&Copy"), textEdit, &QTextEdit::copy);
    actionCopy->setPriority(QAction::LowPriority);
    actionCopy->setShortcut(QKeySequence::Copy);
    tb->addAction(actionCopy);

    const QIcon pasteIcon = QIcon::fromTheme("edit-paste", QIcon(rsrcPath + "/editpaste.png"));
    actionPaste = menu->addAction(pasteIcon, tr("&Paste"), textEdit, &QTextEdit::paste);
    actionPaste->setPriority(QAction::LowPriority);
    actionPaste->setShortcut(QKeySequence::Paste);
    tb->addAction(actionPaste);
    if (const QMimeData *md = QApplication::clipboard()->mimeData())
        actionPaste->setEnabled(md->hasText());
#endif
}

void TextEdit::setupTextActions()
{
    QToolBar *tb = addToolBar(tr("Format Actions"));
    QMenu *menu = menuBar()->addMenu(tr("F&ormat"));

    const QIcon boldIcon = QIcon::fromTheme("format-text-bold", QIcon(rsrcPath + "/textbold.png"));
    actionTextBold = menu->addAction(boldIcon, tr("&Bold"), this, &TextEdit::textBold);
    actionTextBold->setShortcut(Qt::CTRL + Qt::Key_B);
    actionTextBold->setPriority(QAction::LowPriority);
    QFont bold;
    bold.setBold(true);
    actionTextBold->setFont(bold);
    tb->addAction(actionTextBold);
    actionTextBold->setCheckable(true);

    const QIcon italicIcon = QIcon::fromTheme("format-text-italic", QIcon(rsrcPath + "/textitalic.png"));
    actionTextItalic = menu->addAction(italicIcon, tr("&Italic"), this, &TextEdit::textItalic);
    actionTextItalic->setPriority(QAction::LowPriority);
    actionTextItalic->setShortcut(Qt::CTRL + Qt::Key_I);
    QFont italic;
    italic.setItalic(true);
    actionTextItalic->setFont(italic);
    tb->addAction(actionTextItalic);
    actionTextItalic->setCheckable(true);

    const QIcon underlineIcon = QIcon::fromTheme("format-text-underline", QIcon(rsrcPath + "/textunder.png"));
    actionTextUnderline = menu->addAction(underlineIcon, tr("&Underline"), this, &TextEdit::textUnderline);
    actionTextUnderline->setShortcut(Qt::CTRL + Qt::Key_U);
    actionTextUnderline->setPriority(QAction::LowPriority);
    QFont underline;
    underline.setUnderline(true);
    actionTextUnderline->setFont(underline);
    tb->addAction(actionTextUnderline);
    actionTextUnderline->setCheckable(true);

    menu->addSeparator();

    const QIcon leftIcon = QIcon::fromTheme("format-justify-left", QIcon(rsrcPath + "/textleft.png"));
    actionAlignLeft = new QAction(leftIcon, tr("&Left"), this);
    actionAlignLeft->setShortcut(Qt::CTRL + Qt::Key_L);
    actionAlignLeft->setCheckable(true);
    actionAlignLeft->setPriority(QAction::LowPriority);
    const QIcon centerIcon = QIcon::fromTheme("format-justify-center", QIcon(rsrcPath + "/textcenter.png"));
    actionAlignCenter = new QAction(centerIcon, tr("C&enter"), this);
    actionAlignCenter->setShortcut(Qt::CTRL + Qt::Key_E);
    actionAlignCenter->setCheckable(true);
    actionAlignCenter->setPriority(QAction::LowPriority);
    const QIcon rightIcon = QIcon::fromTheme("format-justify-right", QIcon(rsrcPath + "/textright.png"));
    actionAlignRight = new QAction(rightIcon, tr("&Right"), this);
    actionAlignRight->setShortcut(Qt::CTRL + Qt::Key_R);
    actionAlignRight->setCheckable(true);
    actionAlignRight->setPriority(QAction::LowPriority);
    const QIcon fillIcon = QIcon::fromTheme("format-justify-fill", QIcon(rsrcPath + "/textjustify.png"));
    actionAlignJustify = new QAction(fillIcon, tr("&Justify"), this);
    actionAlignJustify->setShortcut(Qt::CTRL + Qt::Key_J);
    actionAlignJustify->setCheckable(true);
    actionAlignJustify->setPriority(QAction::LowPriority);
    const QIcon indentMoreIcon = QIcon::fromTheme("format-indent-more", QIcon(rsrcPath + "/format-indent-more.png"));
    actionIndentMore = menu->addAction(indentMoreIcon, tr("&Indent"), this, &TextEdit::indent);
    actionIndentMore->setShortcut(Qt::CTRL + Qt::Key_BracketRight);
    actionIndentMore->setPriority(QAction::LowPriority);
    const QIcon indentLessIcon = QIcon::fromTheme("format-indent-less", QIcon(rsrcPath + "/format-indent-less.png"));
    actionIndentLess = menu->addAction(indentLessIcon, tr("&Unindent"), this, &TextEdit::unindent);
    actionIndentLess->setShortcut(Qt::CTRL + Qt::Key_BracketLeft);
    actionIndentLess->setPriority(QAction::LowPriority);

    // Make sure the alignLeft  is always left of the alignRight
    QActionGroup *alignGroup = new QActionGroup(this);
    connect(alignGroup, &QActionGroup::triggered, this, &TextEdit::textAlign);

    if (QApplication::isLeftToRight()) {
        alignGroup->addAction(actionAlignLeft);
        alignGroup->addAction(actionAlignCenter);
        alignGroup->addAction(actionAlignRight);
    } else {
        alignGroup->addAction(actionAlignRight);
        alignGroup->addAction(actionAlignCenter);
        alignGroup->addAction(actionAlignLeft);
    }
    alignGroup->addAction(actionAlignJustify);

    tb->addActions(alignGroup->actions());
    menu->addActions(alignGroup->actions());
    tb->addAction(actionIndentMore);
    tb->addAction(actionIndentLess);
    menu->addAction(actionIndentMore);
    menu->addAction(actionIndentLess);

    menu->addSeparator();

    QPixmap pix(16, 16);
    pix.fill(Qt::black);
    actionTextColor = menu->addAction(pix, tr("&Color..."), this, &TextEdit::textColor);
    tb->addAction(actionTextColor);

    menu->addSeparator();

    const QIcon checkboxIcon = QIcon::fromTheme("status-checkbox-checked", QIcon(rsrcPath + "/checkbox-checked.png"));
    actionToggleCheckState = menu->addAction(checkboxIcon, tr("Chec&ked"), this, &TextEdit::setChecked);
    actionToggleCheckState->setShortcut(Qt::CTRL + Qt::Key_K);
    actionToggleCheckState->setCheckable(true);
    actionToggleCheckState->setPriority(QAction::LowPriority);
    tb->addAction(actionToggleCheckState);

    tb = addToolBar(tr("Format Actions"));
    tb->setAllowedAreas(Qt::TopToolBarArea | Qt::BottomToolBarArea);
    addToolBarBreak(Qt::TopToolBarArea);
    addToolBar(tb);

    comboStyle = new QComboBox(tb);
    tb->addWidget(comboStyle);
    comboStyle->addItem("Standard");
    comboStyle->addItem("Bullet List (Disc)");
    comboStyle->addItem("Bullet List (Circle)");
    comboStyle->addItem("Bullet List (Square)");
    comboStyle->addItem("Task List (Unchecked)");
    comboStyle->addItem("Task List (Checked)");
    comboStyle->addItem("Ordered List (Decimal)");
    comboStyle->addItem("Ordered List (Alpha lower)");
    comboStyle->addItem("Ordered List (Alpha upper)");
    comboStyle->addItem("Ordered List (Roman lower)");
    comboStyle->addItem("Ordered List (Roman upper)");
    comboStyle->addItem("Heading 1");
    comboStyle->addItem("Heading 2");
    comboStyle->addItem("Heading 3");
    comboStyle->addItem("Heading 4");
    comboStyle->addItem("Heading 5");
    comboStyle->addItem("Heading 6");

    connect(comboStyle, QOverload<int>::of(&QComboBox::activated), this, &TextEdit::textStyle);

    comboFont = new QFontComboBox(tb);
    tb->addWidget(comboFont);
    connect(comboFont, &QComboBox::textActivated, this, &TextEdit::textFamily);

    comboSize = new QComboBox(tb);
    comboSize->setObjectName("comboSize");
    tb->addWidget(comboSize);
    comboSize->setEditable(true);

    const QList<int> standardSizes = QFontDatabase::standardSizes();
    for (int size : standardSizes)
        comboSize->addItem(QString::number(size));
    comboSize->setCurrentIndex(standardSizes.indexOf(QApplication::font().pointSize()));

    connect(comboSize, &QComboBox::textActivated, this, &TextEdit::textSize);
}

bool TextEdit::load(const QString &f)
{
    if (!QFile::exists(f))
        return false;
    QFile file(f);
    if (!file.open(QFile::ReadOnly))
        return false;

    QByteArray data = file.readAll();
    QTextCodec *codec = Qt::codecForHtml(data);
    QString str = codec->toUnicode(data);
    if (Qt::mightBeRichText(str)) {
        QUrl baseUrl = (f.front() == QLatin1Char(':') ? QUrl(f) : QUrl::fromLocalFile(f)).adjusted(QUrl::RemoveFilename);
        textEdit->document()->setBaseUrl(baseUrl);
        textEdit->setHtml(str);
    } else {
#if QT_CONFIG(textmarkdownreader)
        QMimeDatabase db;
        if (db.mimeTypeForFileNameAndData(f, data).name() == QLatin1String("text/markdown"))
            textEdit->setMarkdown(QString::fromUtf8(data));
        else
#endif
            textEdit->setPlainText(QString::fromUtf8(data));
    }

    setCurrentFileName(f);
    return true;
}

bool TextEdit::maybeSave()
{
    if (!textEdit->document()->isModified())
        return true;

    const QMessageBox::StandardButton ret =
        QMessageBox::warning(this, QCoreApplication::applicationName(),
                             tr("The document has been modified.\n"
                                "Do you want to save your changes?"),
                             QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    if (ret == QMessageBox::Save)
        return fileSave();
    else if (ret == QMessageBox::Cancel)
        return false;
    return true;
}

void TextEdit::setCurrentFileName(const QString &fileName)
{
    this->fileName = fileName;
    textEdit->document()->setModified(false);

    QString shownName;
    if (fileName.isEmpty())
        shownName = "untitled.txt";
    else
        shownName = QFileInfo(fileName).fileName();

    setWindowTitle(tr("%1[*] - %2").arg(shownName, QCoreApplication::applicationName()));
    setWindowModified(false);
}

void TextEdit::fileNew()
{
    if (maybeSave()) {
        textEdit->clear();
        setCurrentFileName(QString());
    }
}

void TextEdit::fileOpen()
{
    QFileDialog fileDialog(this, tr("Open File..."));
    fileDialog.setAcceptMode(QFileDialog::AcceptOpen);
    fileDialog.setFileMode(QFileDialog::ExistingFile);
    fileDialog.setMimeTypeFilters(QStringList()
#if QT_CONFIG(texthtmlparser)
                                  << "text/html"
#endif
#if QT_CONFIG(textmarkdownreader)

                                  << "text/markdown"
#endif
                                  << "text/plain");
    if (fileDialog.exec() != QDialog::Accepted)
        return;
    const QString fn = fileDialog.selectedFiles().first();
    if (load(fn))
        statusBar()->showMessage(tr("Opened \"%1\"").arg(QDir::toNativeSeparators(fn)));
    else
        statusBar()->showMessage(tr("Could not open \"%1\"").arg(QDir::toNativeSeparators(fn)));
}

bool TextEdit::fileSave()
{
    if (fileName.isEmpty())
        return fileSaveAs();
    if (fileName.startsWith(QStringLiteral(":/")))
        return fileSaveAs();

    QTextDocumentWriter writer(fileName);
    bool success = writer.write(textEdit->document());
    if (success) {
        textEdit->document()->setModified(false);
        statusBar()->showMessage(tr("Wrote \"%1\"").arg(QDir::toNativeSeparators(fileName)));
    } else {
        statusBar()->showMessage(tr("Could not write to file \"%1\"")
                                 .arg(QDir::toNativeSeparators(fileName)));
    }
    return success;
}

bool TextEdit::fileSaveAs()
{
    QFileDialog fileDialog(this, tr("Save as..."));
    fileDialog.setAcceptMode(QFileDialog::AcceptSave);
    QStringList mimeTypes;
    mimeTypes << "text/plain"
#if QT_CONFIG(textodfwriter)
              << "application/vnd.oasis.opendocument.text"
#endif
#if QT_CONFIG(textmarkdownwriter)
              << "text/markdown"
#endif
              << "text/html";
    fileDialog.setMimeTypeFilters(mimeTypes);
#if QT_CONFIG(textodfwriter)
    fileDialog.setDefaultSuffix("odt");
#endif
    if (fileDialog.exec() != QDialog::Accepted)
        return false;
    const QString fn = fileDialog.selectedFiles().first();
    setCurrentFileName(fn);
    return fileSave();
}

void TextEdit::filePrint()
{
#if defined(QT_PRINTSUPPORT_LIB) && QT_CONFIG(printdialog)
    QPrinter printer(QPrinter::HighResolution);
    QPrintDialog *dlg = new QPrintDialog(&printer, this);
    if (textEdit->textCursor().hasSelection())
        dlg->addEnabledOption(QAbstractPrintDialog::PrintSelection);
    dlg->setWindowTitle(tr("Print Document"));
    if (dlg->exec() == QDialog::Accepted)
        textEdit->print(&printer);
    delete dlg;
#endif
}

void TextEdit::filePrintPreview()
{
#if defined(QT_PRINTSUPPORT_LIB) && QT_CONFIG(printpreviewdialog)
    QPrinter printer(QPrinter::HighResolution);
    QPrintPreviewDialog preview(&printer, this);
    connect(&preview, &QPrintPreviewDialog::paintRequested, this, &TextEdit::printPreview);
    preview.exec();
#endif
}

void TextEdit::printPreview(QPrinter *printer)
{
#if defined(QT_PRINTSUPPORT_LIB) && QT_CONFIG(printer)
    textEdit->print(printer);
#else
    Q_UNUSED(printer)
#endif
}


void TextEdit::filePrintPdf()
{
#if defined(QT_PRINTSUPPORT_LIB) && QT_CONFIG(printer)
//! [0]
    QFileDialog fileDialog(this, tr("Export PDF"));
    fileDialog.setAcceptMode(QFileDialog::AcceptSave);
    fileDialog.setMimeTypeFilters(QStringList("application/pdf"));
    fileDialog.setDefaultSuffix("pdf");
    if (fileDialog.exec() != QDialog::Accepted)
        return;
    QString fileName = fileDialog.selectedFiles().first();
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);
    textEdit->document()->print(&printer);
    statusBar()->showMessage(tr("Exported \"%1\"")
                             .arg(QDir::toNativeSeparators(fileName)));
//! [0]
#endif
}

void TextEdit::textBold()
{
    QTextCharFormat fmt;
    fmt.setFontWeight(actionTextBold->isChecked() ? QFont::Bold : QFont::Normal);


    QTextCursor cursor = textEdit->textCursor();
    Message mess{};
    if(cursor.hasSelection()){
        int inizio = cursor.selectionStart();
        localInsert(inizio, textEdit->fontPointSize(), textEdit->alignment(), actionTextBold->isChecked(), actionTextItalic->isChecked(), actionTextUnderline->isChecked(), textEdit->textColor().name(), this->font().toString(),mess);
        message_ready(mess, fileName);
        int fine = cursor.selectionEnd();
        localInsert(fine, textEdit->fontPointSize(), textEdit->alignment(), !actionTextBold->isChecked(), actionTextItalic->isChecked(), actionTextUnderline->isChecked(), textEdit->textColor(), this->font().toString(),mess);
        message_ready(mess, fileName);
    }else{
        int index = cursor.position();
        localInsert(index, textEdit->fontPointSize(), textEdit->alignment(), actionTextBold->isChecked(), actionTextItalic->isChecked(), actionTextUnderline->isChecked(), textEdit->textColor(), this->font().toString(),mess);
        message_ready(mess, fileName);
    }

      mergeFormatOnWordOrSelection(fmt);
    mergeFormatOnWordOrSelection(fmt);
}

void TextEdit::textUnderline()
{
    QTextCharFormat fmt;
    fmt.setFontUnderline(actionTextUnderline->isChecked());
    mergeFormatOnWordOrSelection(fmt);
}

void TextEdit::textItalic()
{
    QTextCharFormat fmt;
    fmt.setFontItalic(actionTextItalic->isChecked());
    mergeFormatOnWordOrSelection(fmt);
}

void TextEdit::textFamily(const QString &f)
{
    QTextCharFormat fmt;
    fmt.setFontFamily(f);
    mergeFormatOnWordOrSelection(fmt);
}

void TextEdit::textSize(const QString &p)
{
    qreal pointSize = p.toFloat();
    if (p.toFloat() > 0) {
        QTextCharFormat fmt;
        fmt.setFontPointSize(pointSize);
        mergeFormatOnWordOrSelection(fmt);
    }
}

void TextEdit::textStyle(int styleIndex)
{
    QTextCursor cursor = textEdit->textCursor();
    QTextListFormat::Style style = QTextListFormat::ListStyleUndefined;
    QTextBlockFormat::MarkerType marker = QTextBlockFormat::MarkerType::NoMarker;

    switch (styleIndex) {
    case 1:
        style = QTextListFormat::ListDisc;
        break;
    case 2:
        style = QTextListFormat::ListCircle;
        break;
    case 3:
        style = QTextListFormat::ListSquare;
        break;
    case 4:
        if (cursor.currentList())
            style = cursor.currentList()->format().style();
        else
            style = QTextListFormat::ListDisc;
        marker = QTextBlockFormat::MarkerType::Unchecked;
        break;
    case 5:
        if (cursor.currentList())
            style = cursor.currentList()->format().style();
        else
            style = QTextListFormat::ListDisc;
        marker = QTextBlockFormat::MarkerType::Checked;
        break;
    case 6:
        style = QTextListFormat::ListDecimal;
        break;
    case 7:
        style = QTextListFormat::ListLowerAlpha;
        break;
    case 8:
        style = QTextListFormat::ListUpperAlpha;
        break;
    case 9:
        style = QTextListFormat::ListLowerRoman;
        break;
    case 10:
        style = QTextListFormat::ListUpperRoman;
        break;
    default:
        break;
    }

    cursor.beginEditBlock();

    QTextBlockFormat blockFmt = cursor.blockFormat();

    if (style == QTextListFormat::ListStyleUndefined) {
        blockFmt.setObjectIndex(-1);
        int headingLevel = styleIndex >= 11 ? styleIndex - 11 + 1 : 0; // H1 to H6, or Standard
        blockFmt.setHeadingLevel(headingLevel);
        cursor.setBlockFormat(blockFmt);

        int sizeAdjustment = headingLevel ? 4 - headingLevel : 0; // H1 to H6: +3 to -2
        QTextCharFormat fmt;
        fmt.setFontWeight(headingLevel ? QFont::Bold : QFont::Normal);
        fmt.setProperty(QTextFormat::FontSizeAdjustment, sizeAdjustment);
        cursor.select(QTextCursor::LineUnderCursor);
        cursor.mergeCharFormat(fmt);
        textEdit->mergeCurrentCharFormat(fmt);
    } else {
        blockFmt.setMarker(marker);
        cursor.setBlockFormat(blockFmt);
        QTextListFormat listFmt;
        if (cursor.currentList()) {
            listFmt = cursor.currentList()->format();
        } else {
            listFmt.setIndent(blockFmt.indent() + 1);
            blockFmt.setIndent(0);
            cursor.setBlockFormat(blockFmt);
        }
        listFmt.setStyle(style);
        cursor.createList(listFmt);
    }

    cursor.endEditBlock();
}

void TextEdit::textColor()
{
    QColor col = QColorDialog::getColor(textEdit->textColor(), this);
    if (!col.isValid())
        return;
    QTextCharFormat fmt;
    fmt.setForeground(col);
    mergeFormatOnWordOrSelection(fmt);
    colorChanged(col);
}

void TextEdit::textAlign(QAction *a)
{
    if (a == actionAlignLeft)
        textEdit->setAlignment(Qt::AlignLeft | Qt::AlignAbsolute);
    else if (a == actionAlignCenter)
        textEdit->setAlignment(Qt::AlignHCenter);
    else if (a == actionAlignRight)
        textEdit->setAlignment(Qt::AlignRight | Qt::AlignAbsolute);
    else if (a == actionAlignJustify)
        textEdit->setAlignment(Qt::AlignJustify);
}

void TextEdit::setChecked(bool checked)
{
    textStyle(checked ? 5 : 4);
}

void TextEdit::indent()
{
    modifyIndentation(1);
}

void TextEdit::unindent()
{
    modifyIndentation(-1);
}

void TextEdit::modifyIndentation(int amount)
{
    QTextCursor cursor = textEdit->textCursor();
    cursor.beginEditBlock();
    if (cursor.currentList()) {
        QTextListFormat listFmt = cursor.currentList()->format();
        // See whether the line above is the list we want to move this item into,
        // or whether we need a new list.
        QTextCursor above(cursor);
        above.movePosition(QTextCursor::Up);
        if (above.currentList() && listFmt.indent() + amount == above.currentList()->format().indent()) {
            above.currentList()->add(cursor.block());
        } else {
            listFmt.setIndent(listFmt.indent() + amount);
            cursor.createList(listFmt);
        }
    } else {
        QTextBlockFormat blockFmt = cursor.blockFormat();
        blockFmt.setIndent(blockFmt.indent() + amount);
        cursor.setBlockFormat(blockFmt);
    }
    cursor.endEditBlock();
}

void TextEdit::currentCharFormatChanged(const QTextCharFormat &format)
{
    fontChanged(format.font());
    colorChanged(format.foreground().color());
}

void TextEdit::cursorPositionChanged()
{
    alignmentChanged(textEdit->alignment());
    QTextList *list = textEdit->textCursor().currentList();
    if (list) {
        switch (list->format().style()) {
        case QTextListFormat::ListDisc:
            comboStyle->setCurrentIndex(1);
            break;
        case QTextListFormat::ListCircle:
            comboStyle->setCurrentIndex(2);
            break;
        case QTextListFormat::ListSquare:
            comboStyle->setCurrentIndex(3);
            break;
        case QTextListFormat::ListDecimal:
            comboStyle->setCurrentIndex(6);
            break;
        case QTextListFormat::ListLowerAlpha:
            comboStyle->setCurrentIndex(7);
            break;
        case QTextListFormat::ListUpperAlpha:
            comboStyle->setCurrentIndex(8);
            break;
        case QTextListFormat::ListLowerRoman:
            comboStyle->setCurrentIndex(9);
            break;
        case QTextListFormat::ListUpperRoman:
            comboStyle->setCurrentIndex(10);
            break;
        default:
            comboStyle->setCurrentIndex(-1);
            break;
        }
        switch (textEdit->textCursor().block().blockFormat().marker()) {
        case QTextBlockFormat::MarkerType::NoMarker:
            actionToggleCheckState->setChecked(false);
            break;
        case QTextBlockFormat::MarkerType::Unchecked:
            comboStyle->setCurrentIndex(4);
            actionToggleCheckState->setChecked(false);
            break;
        case QTextBlockFormat::MarkerType::Checked:
            comboStyle->setCurrentIndex(5);
            actionToggleCheckState->setChecked(true);
            break;
        }
    } else {
        int headingLevel = textEdit->textCursor().blockFormat().headingLevel();
        comboStyle->setCurrentIndex(headingLevel ? headingLevel + 10 : 0);
    }
}

void TextEdit::clipboardDataChanged()
{
#ifndef QT_NO_CLIPBOARD
    if (const QMimeData *md = QApplication::clipboard()->mimeData())
        actionPaste->setEnabled(md->hasText());
#endif
}

void TextEdit::about()
{
    QMessageBox::about(this, tr("About"), tr("This example demonstrates Qt's "
        "rich text editing facilities in action, providing an example "
        "document for you to experiment with."));
}

void TextEdit::mergeFormatOnWordOrSelection(const QTextCharFormat &format)
{
    QTextCursor cursor = textEdit->textCursor();
    if (!cursor.hasSelection())
        cursor.select(QTextCursor::WordUnderCursor);
    cursor.mergeCharFormat(format);
    textEdit->mergeCurrentCharFormat(format);
}

void TextEdit::fontChanged(const QFont &f)
{
    comboFont->setCurrentIndex(comboFont->findText(QFontInfo(f).family()));
    comboSize->setCurrentIndex(comboSize->findText(QString::number(f.pointSize())));
    actionTextBold->setChecked(f.bold());
    actionTextItalic->setChecked(f.italic());
    actionTextUnderline->setChecked(f.underline());
}

void TextEdit::colorChanged(const QColor &c)
{
    QPixmap pix(16, 16);
    pix.fill(c);
    actionTextColor->setIcon(pix);
}

void TextEdit::alignmentChanged(Qt::Alignment a)
{
    if (a & Qt::AlignLeft)
        actionAlignLeft->setChecked(true);
    else if (a & Qt::AlignHCenter)
        actionAlignCenter->setChecked(true);
    else if (a & Qt::AlignRight)
        actionAlignRight->setChecked(true);
    else if (a & Qt::AlignJustify)
        actionAlignJustify->setChecked(true);
}

/*-----FATTE DA NOI-----*/
void TextEdit::onTextChanged(int pos, int del, int add){
    QString added = textEdit->toPlainText().mid(pos, add);
    qDebug() << "pos " << pos << "; del " << del << "; add " << add << "; added" << added;
    if(add==1){ //PER ORA GESTISCO SOLO L'INSERIMENTO (NO COPIA E INCOLLA)
        Message mess{};
        localInsert(pos, added.back(), mess);
        //TextSymbol ts = static_cast<TextSymbol>(mess.getSymbol());
         //qDebug() << "Action " << mess.getAction() << "; Position " << mess.getSymbol().getPosition();
        message_ready(mess, fileName);
    }else{
        if(del==1){ // per ora non gestisco la funzione taglia
            Message mess{'d', this->_symbols[pos]};
            this->_symbols.erase(this->_symbols.begin() + pos);
            message_ready(mess, fileName);
        }
    }

}

void TextEdit::onMessageFromServer(Message m){

    if(m.getAction()=='i'){
        if(m.getSymbol()->isStyle()){
            StyleSymbol* sym = static_cast<StyleSymbol*>(m.getSymbol());
        }else{
            TextSymbol* sym = static_cast<TextSymbol*>(m.getSymbol());
            remoteInsert(sym);
        }
    }else{
        if(m.getAction()=='d'){
            if(m.getSymbol()->isStyle()){
                StyleSymbol* sym = static_cast<StyleSymbol*>(m.getSymbol());
            }else{
                TextSymbol* sym = static_cast<TextSymbol*>(m.getSymbol());
                remoteDelete(sym);
            }
        }
    }
}

void TextEdit::onFileReady(QVector<GenericSymbol*> gs, QString text){

    this->_symbols = gs;
    textEdit->textCursor().beginEditBlock();
    textEdit->textCursor().insertText(text);
    textEdit->textCursor().endEditBlock();


    textEdit->setPlainText(text);
    textEdit->textCursor();
}



std::string TextEdit::localInsert(int index, QChar value, Message& m)
{
    QVector<int> pos;
    if ((index > (this->_symbols.size())) || index < 0) {
        return "Errore";//IO NON PERMETTEREI DI INSERIRE IN QUALSIASI PUNTO DEL NOSTRO VETTORE. SOLO INDICI DA 1 A SIZE+1 TODO ECCEZIONE
    }
    this->counter++;
    pos = generatePos(index);
    if (pos.size() == 0) {
        return "Errore";
    }
    TextSymbol* symbol = new TextSymbol(false, pos, this->counter, this->siteId, value);
    this->_symbols.insert(this->_symbols.begin() + index, symbol);

    m.setAction('i');
    m.setSymbol(symbol);

    return "OK";
}

std::string TextEdit::localInsert(int index, int textSize, int alignment,  bool isBold, bool isItalic, bool isUnderlined, QColor color, QString font, Message& m)
{
    QVector<int> pos;
    if ((index > (this->_symbols.size())) || index < 0) {
        return "Errore";//IO NON PERMETTEREI DI INSERIRE IN QUALSIASI PUNTO DEL NOSTRO VETTORE. SOLO INDICI DA 1 A SIZE+1 TODO ECCEZIONE
    }
    this->counter++;
    pos = generatePos(index);
    if (pos.size() == 0) {
        return "Errore";
    }
    StyleSymbol* symbol = new StyleSymbol(true, pos , this->counter, this->siteId, isBold, isItalic, isUnderlined, alignment, textSize , color, font);


    this->_symbols.insert(this->_symbols.begin() + index, symbol);

    m.setAction('i');
    m.setSymbol(symbol);


    return "OK";
}

// index: indice in cui inserire. Restituisco un vettore della posizione adatto.
QVector<int> TextEdit::generatePos(int index) {
    QVector<int> pos;
    int i;

    if ((index > (this->_symbols.size())) || index < 0) {
        return pos;//IO NON PERMETTEREI DI INSERIRE IN QUALSIASI PUNTO DEL NOSTRO VETTORE. SOLO INDICI DA 1 A SIZE+1 TODO ECCEZIONE
    }
    if (this->_symbols.empty()) {
        pos.push_back(index + 1);
    }
    else {
        if (index == 0) { //indice uguale a 0, inserisco con compresa tra 0 e 1. Inserimento in TESTA
            QVector<int> pos_successivo = _symbols[index]->getPosition();   //OTTENGO IL POS DELLA PRECEDENTE TESTA, ORA DEVO GENERARE IL NUOVO.
            QVector<int> vuoto;
            vuoto.push_back(0);
            pos = calcIntermediatePos(pos_successivo, vuoto);
        }
        else {
            QVector<int> pos_precedente = _symbols[index - 1]->getPosition();

            if (_symbols.size() == index) {         //Inserimento in CODA
                for (i = 0; i < _symbols[index - 1]->getPosition().size(); i++) {
                    if (pos_precedente[i] == INT_MAX) {
                        pos.push_back(INT_MAX);
                    }
                    else break;
                }
                pos.push_back(pos_precedente[i] + 1);

            }
            else {     //Inserimento in un indice diverso dalla coda o dalla testa.
                QVector<int> pos_successivo = _symbols[index]->getPosition();
                pos = calcIntermediatePos(pos_successivo, pos_precedente);
            }
        }
    }
    pos.push_back(this->siteId);
    /*Il siteId viene messo per garantire che se due client scrivono nello stesso istante un carattere in una certa posizione,
     l'unicit� della posizione e garantito da questa ultima cifra.*/
    return pos;
}
QVector<int> TextEdit::calcIntermediatePos(QVector<int> pos_sup, QVector<int> pos_inf) {
    QVector<int> pos;
    int inf, sup, k = 20, i = 0, nuovo_valore, flag = 0, MAX = INT_MAX - 100;
    //todo con un comparatore posso verificare che successivo sia davvero un num frazionario maggiore di prec

    /***
     In questa funzione si cerca di creare un vettore di posizioni che abbia un valore compreso tra quello indicato
     come pos_sup e quello indicato come pos_inf. Si � deciso di non limitarci alle cifre che vanno da 0 fino
     a 9 ma di arrivare fino a MAX. Per ogni posizione del vettore si cerca di inserire nel nuovo vettore un valore
     che sia maggiore di pos_inf[i] (se non esiste questa posizione del vettore si usa il valore 0) e minore di
     pos_sup[i] (se non esiste questa posizione del vettore si usa il valore MAX), e nel caso questo valore intermedio
     non esista si copia il valore pos_inf[i] per continuare la ricerca incrementando i. Quando troviamo un valore
     intermedio si inserisce nel nuovo vettore e finisce qui la nostra ricerca di un vettore intermedio.
     Il calcolo del valore intermedio viene fatto nella seguente maniera: se la differenza tra i due numeri � superiore
     a un valore constante (k) si inserisce il valore inf + k, altrimenti si cerca di inserire un valore che stia a
     met� tra pos_inf[i] e pos_sup[i]. Questo viene fatto per provare a mantenere dei valori intermedi liberi tra i vari
     campi del vettore e allo stesso tempo in caso di normale scrittura sequenziale, non arrivare velocemente al valore
     MAX ma con incrementi costanti di k. La variabile flag assume il valore 1 quando abbiamo trovato un valore di
     pos_sup[i] superiore a pos_inf[i]. Infatti dal prossimo valore di i non abbiamo pi� bisogno di trovare un valore
     tra pos_sup[i] e pos_inf[i], ma ci basta solo che sia superiore a pos_inf[i] e inferiore a MAX (guardare esempio).


                                                    Dopo questo 6 il valore di flag sar� 1
     Esempio:   vettore con indice maggiore     0 |6| 1
                vettore con indice minore       0 |5| 1
                                                -------
                                 Risultato      0 |5|(k+1)  <--- Qui non ho pi� bisogno di cercare un valore intermedio
                                                                 perch� il flag vale 1.
    ***/



    int lung_vett_max = (int)std::max(pos_sup.size(), pos_inf.size());

    for (i = 0; i < lung_vett_max; i++) {
        if (pos_inf.size() <= i)
            inf = 0;
        else
            inf = pos_inf[i];
        if (pos_sup.size() <= i)
            sup = MAX;
        else
            sup = pos_sup[i];

        if (flag == 1 && (inf + k) < MAX) {
            pos.push_back(inf + k);
            return pos;
        }
        if ((inf + 1) < sup) {              //cerco un valore intermedio
            nuovo_valore = k + inf;
            if (nuovo_valore >= sup || nuovo_valore > MAX) {
                nuovo_valore = ((sup - inf) / 2) + inf;
                if (nuovo_valore >= sup || nuovo_valore > MAX) {
                    pos.push_back(inf);     //non esiste un valore intermedio
                    continue;               //continua a ciclare il for
                }
            }
            pos.push_back(nuovo_valore);    //valore intermedio trovato, finisco la ricerca.
            return pos;
        }
        else {                            // se non esiste un valore intermedio
            if (inf < sup) {
                flag = 1;                   //da ora in poi qualsiasi cifra superiore a inf andr� bene
            }
            pos.push_back(inf);
        }
    }
    pos.push_back(k);
    return pos;
}

void TextEdit::remoteInsert(GenericSymbol* sym){ //per ora gestito solo il caso in cui ci siano solo caratteri normali nella nostra app.
    int index = findIndexFromNewPosition(sym->getPosition());
    QTextCursor cursor = textEdit->textCursor();
    cursor.setPosition(index, QTextCursor::MoveAnchor);
    if(!sym->isStyle()){
        TextSymbol* ts= static_cast<TextSymbol*>(sym);
        this->_symbols.insert(this->_symbols.begin() + index, ts);
        cursor.insertText(ts->getValue());
    }\
}
void TextEdit::remoteDelete(GenericSymbol* sym){
    int index = findIndexFromExistingPosition(sym->getPosition());
    if(index!=-1){
        QTextCursor cursor = textEdit->textCursor();
        cursor.setPosition(index, QTextCursor::MoveAnchor);
        cursor.deleteChar();
        this->_symbols.erase(this->_symbols.begin() + index);
    }
}


int TextEdit::findIndexFromNewPosition(QVector<int> position){
    int index = _symbols.size();
        if (_symbols.size() == 0) {
            index = 0;
        }
        if (_symbols.size() == 1) {
            if (_symbols[0]->getPosition() > position) {
                index = 0;
            }
            else {
                index = 1;
            }
        }
        if (_symbols.size() > 1) {
            if (position < _symbols[0]->getPosition()) {
                index = 0;
            }
            for (int i = 1; i < _symbols.size(); i++) {
                if (_symbols[i - 1]->getPosition() < position && position < _symbols[i]->getPosition()) {
                    index = i;
                    break;
                }
            }
        }
       return index;
}

int TextEdit::findIndexFromExistingPosition(QVector<int> position){
    int index=-1;
    for(int i=0; i<this->_symbols.size(); i++){
        if(this->_symbols[i]->getPosition() == position){
            index=i;
            break;
        }
    }
    return index;
}
