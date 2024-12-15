#include "mainapp.h"

mainapp::mainapp(QWidget *parent) : QWidget(parent)
{
    setWindowTitle("Data menager window");

    const int x =1920*0.8;//x window size
    const int y=1080*0.8;//y window size

    setFixedSize(x, y);//Set window size

    //Background image
    background = QPixmap("/home/krzysiek89/Desktop/QT_aplikacje/Data_analiser/background1.jpg").scaled(x, y);

    QFont font;
    font.setPointSize(21);//Font size -all font size

    QFont font_screen;
    font_screen.setPointSize(14);//Font size -all font size

    exit_button = new QPushButton("Exit app...", this);//leave from app
    exit_button->setFont(font);
    exit_button->setStyleSheet("color: yellow;");
    exit_button->setGeometry(30, 770, 360, 70);
    connect(exit_button, &QPushButton::clicked, this, &mainapp::exitApp);

    //Add frame based on QLabel
    frame = new QLabel(this);//Frame 1
    int frame_x=x/2+130;//frame x_size
    int frame_y=y/2 + 370;//frame y_size
    frame->setGeometry(600, 30, frame_x, frame_y);//Pos and size
    frame->setStyleSheet("border: 3px solid black;");//Style of frame

    selectFileButton = new QPushButton("Select .csv File...", this);
    selectFileButton->setFont(font);
    selectFileButton->setStyleSheet("color: yellow;");
    selectFileButton->setGeometry(10, 10, 275, 70);
    connect(selectFileButton, &QPushButton::clicked, this, &mainapp::selectFile);

    // Create labels and input fields
    const int x_box_size=50;
    const int y_box_size=50;
    const int x_box_start=10;
    const int y_box_start=150;
    const int gap=60;
    columnLabel = new QLabel(": 1st column", this);
    columnLabel->setStyleSheet("color: yellow;");
    columnLabel->setFont(font);
    columnLabel->setGeometry(x_box_start+gap, y_box_start, 300, 50);

    columnInput = new QLineEdit(this);
    columnInput->setFont(font);
    columnInput->setStyleSheet("color: yellow;");
    columnInput->setGeometry(x_box_start, y_box_start, x_box_size, y_box_size);

    rowStartLabel = new QLabel(": start row", this);
    rowStartLabel->setStyleSheet("color: yellow;");
    rowStartLabel->setFont(font);
    rowStartLabel->setGeometry(x_box_start+gap, y_box_start+gap, 300, 50);

    rowStartInput = new QLineEdit(this);
    rowStartInput->setFont(font);
    rowStartInput->setStyleSheet("color: yellow;");
    rowStartInput->setGeometry(x_box_start, y_box_start+gap, x_box_size, y_box_size);

    rowEndLabel = new QLabel(": end row", this);
    rowEndLabel->setStyleSheet("color: yellow;");
    rowEndLabel->setFont(font);
    rowEndLabel->setGeometry(x_box_start+gap+295, y_box_start+gap,  300, 50);

    rowEndInput = new QLineEdit(this);
    rowEndInput->setFont(font);
    rowEndInput->setStyleSheet("color: yellow;");
    rowEndInput->setGeometry(x_box_start+gap+230, y_box_start+gap, x_box_size, y_box_size);

    //Add radio buttons for selecting number of columns(1 or 2)
    singleColumnRadio = new QRadioButton("Single Column", this);
    singleColumnRadio->setFont(font);
    singleColumnRadio->setStyleSheet("color: yellow;");
    singleColumnRadio->setGeometry(50, 80, 210, 70);
    singleColumnRadio->setChecked(true);

    doubleColumnRadio = new QRadioButton("Two Columns", this);
    doubleColumnRadio->setFont(font);
    doubleColumnRadio->setStyleSheet("color: yellow;");
    doubleColumnRadio->setGeometry(330, 80, 210, 70);

    connect(doubleColumnRadio, &QRadioButton::toggled, this, &mainapp::toggleDoubleColumn);

    secondColumnLabel = new QLabel(": 2nd column", this);
    secondColumnLabel->setStyleSheet("color: yellow;");
    secondColumnLabel->setFont(font);
    secondColumnLabel->setGeometry(x_box_start+gap+295, y_box_start, 210, 70);
    secondColumnLabel->hide();

    secondColumnInput = new QLineEdit(this);
    secondColumnInput->setFont(font);
    secondColumnInput->setStyleSheet("color: yellow;");
    secondColumnInput->setGeometry(x_box_start+gap+230, y_box_start, x_box_size, y_box_size);
    secondColumnInput->hide();

    //display data field(screen)
    dataDisplay = new QTextEdit(this);
    dataDisplay->setGeometry(600+10, 30+10, frame_x-20, frame_y-20);;
    dataDisplay->setFont(font_screen);
    dataDisplay->setReadOnly(true);//only to read

    //white background colour, black 1px wide frame around, black font of messages - display
    dataDisplay->setStyleSheet("background-color: white;color: black; border: 1px solid black;");
    dataDisplay->setText("You will see your data here, on the screen...");

    dataDisplay->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);//with horisontal scroll
    dataDisplay->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);//with vertical scroll
    dataDisplay->setLineWrapMode(QTextEdit::NoWrap);//lines are no wrapping - the whole row is in one line

    showDataButton = new QPushButton("Show Data", this);
    showDataButton->setFont(font);
    showDataButton->setStyleSheet("color: yellow;");
    showDataButton->setGeometry(295, 10, 275, 70);
    connect(showDataButton, &QPushButton::clicked, this, &mainapp::displaySelectedData);

    plotterButton = new QPushButton("Plotter", this);
    plotterButton->setFont(font);
    plotterButton->setStyleSheet("color: yellow;");
    plotterButton->setGeometry(10, 380, 275, 70);
    connect(plotterButton, &QPushButton::clicked, this, &mainapp::plotter_page);

    stats1Button = new QPushButton("Math stats I", this);
    stats1Button->setFont(font);
    stats1Button->setStyleSheet("color: yellow;");
    stats1Button->setGeometry(10, 470, 275, 70);
    connect(stats1Button, &QPushButton::clicked, this, &mainapp::stats1_page);

    stats2Button = new QPushButton("Math stats II", this);
    stats2Button->setFont(font);
    stats2Button->setStyleSheet("color: yellow;");
    stats2Button->setGeometry(10, 560, 275, 70);
    connect(stats2Button, &QPushButton::clicked, this, &mainapp::stats2_page);
}

void mainapp::paintEvent(QPaintEvent *event) {
    QWidget::paintEvent(event);
    QPainter painter(this);
    painter.drawPixmap(0, 0, background);//first draw background, later added elements on the background
}

void mainapp::exitApp()
{
    this->close();//turn off app...
}

void mainapp::selectFile()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Select CSV file", "", "CSV Files (*.csv)");//use .csv
    if (filePath.isEmpty()) {
        return;
    }

    //Store the file path for further processing
    csvFilePath = filePath;
    qDebug() << "Selected file:" << csvFilePath;//check if selection is ok

}

void mainapp::toggleDoubleColumn(bool checked)
{
    secondColumnInput->setVisible(checked);//if option 2 columns, then visible
    secondColumnLabel->setVisible(checked);
}

void mainapp::displaySelectedData() {    
    if (csvFilePath.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please select a CSV file first.");
        return;
    }

    //put inputs to variables from qlineedit
    bool columnOk, secondColumnOk, startRowOk, endRowOk;//if valid bool variables
    int column = columnInput->text().toInt(&columnOk) - 1;//Adjust for 0-based indexing
    int secondColumn = secondColumnInput->text().toInt(&secondColumnOk) - 1;//Second column
    int startRow = rowStartInput->text().toInt(&startRowOk) - 1;
    int endRow = rowEndInput->text().toInt(&endRowOk) - 1;

    //check data correction
    qDebug() << "File path:" << csvFilePath;
    qDebug() << "Column:" << column << ", Start row:" << startRow << ", End row:" << endRow;
    qDebug() << "Second column:" << secondColumn << ", Double column enabled:" << doubleColumnRadio->isChecked();

    if (!columnOk || !startRowOk || !endRowOk || startRow < 0 || endRow < startRow ||
        (doubleColumnRadio->isChecked() && !secondColumnOk)) {
        QMessageBox::warning(this, "Error", "Invalid input for column(s) or row range.");
        return;
    }

    QFile file(csvFilePath);//put file
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "Failed to open the CSV file.");
        return;
    }

    QTextStream in(&file);//put file into text stream
    QStringList lines;//tu iteration variable
    int currentRow = 0;//temp line number
    int validCount_left = 0;//number of number-type values - for 1st column choosen
    int validCount_right = 0;//number of number-type values - for 2st column choosen
    int length_rows=endRow-startRow+1;

    while (!in.atEnd()) {//if not end
        QString line = in.readLine();
        if (currentRow >= startRow && currentRow <= endRow) {
            QStringList columns = line.split(',');
            QString rowDataLeft, rowDataRight;

            if (column >= 0 && column < columns.size()) {
                rowDataLeft = QString::number(currentRow + 1) + ": " + columns[column].trimmed();
                qDebug()<<"Test: "<<columns[column].toDouble();
                if(columns[column].toDouble())//transformable to number?
                {
                    validCount_left++;
                }
            } else {
                rowDataLeft = QString("Error: Index out of range for Column 1");
            }

            if (doubleColumnRadio->isChecked()) {
                if (secondColumn >= 0 && secondColumn < columns.size()) {
                    rowDataRight = columns[secondColumn].trimmed();
                    qDebug()<<"Test: "<<columns[secondColumn].toDouble();
                    if(columns[secondColumn].toDouble())//transformable to number?
                    {
                        validCount_right++;
                    }
                } else {
                    rowDataRight = QString("Error: Index out of range for Column 2");
                }
            }
            //format the output with fixed-width columns
            QString formattedRow = rowDataLeft.leftJustified(100, ' ') + rowDataRight;//max lenght is 80 char, is less fill with space
            lines.append(formattedRow);
        }
        currentRow++;
    }

//----------------------------------------check if column is all numerical type
    //all data is numerical type check on left columnt
    qDebug()<<"Numerical count left: "<<validCount_left;
    qDebug()<<"Rows amount: "<<length_rows;
    if (validCount_left == length_rows) {//check if amount of lines is the same as amount of int type
        QMessageBox::information(this, "Success", "All entries are valid numbers on left column");
        all_numbers_left=true;
    } else {
        QMessageBox::critical(this, "Error", "Some entries are invalid on left column");
        all_numbers_left=false;
    }


    if (doubleColumnRadio->isChecked()) {//if option with 2nd column selected
    two_column_mode = true;//managing with 2 column analisys
    //check if right column data if numerical type
    qDebug()<<"Numerical count right: "<<validCount_right;
    qDebug()<<"Rows amount: "<<length_rows;
    if (validCount_right == length_rows) {//check if amount of lines is the same as amount of int type
        QMessageBox::information(this, "Success", "All entries are valid numbers on right column");
        all_numbers_right=true;
    } else {
        QMessageBox::critical(this, "Error", "Some entries are invalid on right column");
        all_numbers_right=false;
    }
    }
//---------------------------------------------------------------------

    file.close();//close .csv

    if (lines.isEmpty()) {//if empty
        QMessageBox::warning(this, "Warning", "No valid data found in the specified range.");
    }
    dataDisplay->clear();
    dataDisplay->setText(lines.join("\n"));
}

void mainapp::stats1_page()
{
    stats1* stat1 = new stats1(all_numbers_left,all_numbers_right,two_column_mode,nullptr);
    stat1->setAttribute(Qt::WA_DeleteOnClose);
    stat1->show();
    this->close();
}

void mainapp::stats2_page()
{
    stats2* stat2 = new stats2(nullptr);
    stat2->setAttribute(Qt::WA_DeleteOnClose);
    stat2->show();
    this->close();
}

void mainapp::plotter_page()
{
    plotter* plott = new plotter(nullptr);
    plott->setAttribute(Qt::WA_DeleteOnClose);
    plott->show();
    this->close();
}
