#include "mainapp.h"

//pre-initialisation for static members - to remember choosen till the end of program working and till the user change
QString mainapp::csvFilePath = " ";//keep path to csv in static to keep once choosen all the time
vector<double> mainapp::left_column_vec = {};
vector<double> mainapp::right_column_vec = {};
bool mainapp::all_numbers_left = false;
bool mainapp::all_numbers_right = false;
bool mainapp::two_column_mode = false;
int mainapp::column=1;//1st column number
int mainapp::secondColumn=1;//2nd column number
int mainapp::startRow=1;//start row in column
int mainapp::endRow=1;//end row in column
bool mainapp::columnOk=false;
bool mainapp::startRowOk=false;
bool mainapp::endRowOk=false;
bool mainapp::secondColumnOk=false;
bool mainapp::change_dist=false;


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

    exit_button = new QPushButton("Exit app", this);//leave from app
    exit_button->setFont(font);
    exit_button->setStyleSheet("color: yellow;");
    exit_button->setGeometry(10, 770, 160, 70);
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
    secondColumnLabel->setGeometry(x_box_start+gap+295, y_box_start, 210, 50);
    secondColumnLabel->hide();

    secondColumnInput = new QLineEdit(this);
    secondColumnInput->setFont(font);
    secondColumnInput->setStyleSheet("color: yellow;");
    secondColumnInput->setGeometry(x_box_start+gap+230, y_box_start, x_box_size, y_box_size);
    secondColumnInput->hide();

    //display data field(screen)
    dataDisplay = new QTextEdit(this);
    dataDisplay->setGeometry(600+10, 30+10, frame_x-20, frame_y-20);
    dataDisplay->setFont(font_screen);
    dataDisplay->setReadOnly(true);//only to read

    //white background colour, black 1px wide frame around, black font of messages - display
    dataDisplay->setStyleSheet("background-color: white;color: black; border: 1px solid black;");
    dataDisplay->setText("Before going to stats, display data... \n\nYou will see your data here, on the screen...\n");

    dataDisplay->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);//with horisontal scroll
    dataDisplay->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);//with vertical scroll
    dataDisplay->setLineWrapMode(QTextEdit::NoWrap);//lines are no wrapping - the whole row is in one line

    showDataButton = new QPushButton("Show Data", this);
    showDataButton->setFont(font);
    showDataButton->setStyleSheet("color: yellow;");
    showDataButton->setGeometry(295, 10, 275, 70);
    connect(showDataButton, &QPushButton::clicked, this, &mainapp::displaySelectedData);

    const int y_start=440;
    const int gap1=10;
    const int y_size=70;

    plotterButton = new QPushButton("Plotter", this);
    plotterButton->setFont(font);
    plotterButton->setStyleSheet("color: yellow;");
    plotterButton->setGeometry(10, y_start, 275, 70);
    connect(plotterButton, &QPushButton::clicked, this, &mainapp::plotter_page);

    stats1Button = new QPushButton("Math stats I", this);
    stats1Button->setFont(font);
    stats1Button->setStyleSheet("color: yellow;");
    stats1Button->setGeometry(10, y_start+gap1+y_size, 275, 70);
    connect(stats1Button, &QPushButton::clicked, this, &mainapp::stats1_page);

    stats2Button = new QPushButton("Math stats II", this);
    stats2Button->setFont(font);
    stats2Button->setStyleSheet("color: yellow;");
    stats2Button->setGeometry(10, y_start+2*gap1+2*y_size, 275, 70);
    connect(stats2Button, &QPushButton::clicked, this, &mainapp::stats2_page);

    clear_chat_button = new QPushButton("Clear chat", this);
    clear_chat_button->setFont(font);
    clear_chat_button->setStyleSheet("color: yellow;");
    clear_chat_button->setGeometry(180, 770, 170, 70);
    connect(clear_chat_button, &QPushButton::clicked, this, &mainapp::clear_chat);

    change_csv_button = new QPushButton("Change .csv", this);
    change_csv_button->setFont(font);
    change_csv_button->setStyleSheet("color: yellow;");
    change_csv_button->setGeometry(360, 770, 200, 70);
    connect(change_csv_button, &QPushButton::clicked, this, &mainapp::change_csv);

    area_change_button = new QPushButton("Enable column or row change", this);
    area_change_button->setFont(font);
    area_change_button->setStyleSheet("color: yellow;");
    area_change_button->setGeometry(10, 280, 450, 70);
    connect(area_change_button, &QPushButton::clicked, this, &mainapp::area_change);

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
    if (filePath.isEmpty()) {
        filePath = QFileDialog::getOpenFileName(this, "Select CSV file", "", "CSV Files (*.csv)");//use .csv
        //Store the file path for further processing
        csvFilePath = filePath;
        qDebug() << "Selected file:" << csvFilePath;//check if selection is ok
        if(!csvFilePath.isEmpty()){
        QMessageBox::information(this, "Success", ".csv has been loaded succesfully...");
        }
    }
    else
    {
        QMessageBox::warning(this, "ERROR! Click change csv button", "path is not empty now...");
    }
}

void mainapp::toggleDoubleColumn(bool checked)
{
    secondColumnInput->setVisible(checked);//if option 2 columns, then visible
    secondColumnLabel->setVisible(checked);
    two_column_mode = checked;//switch state if bool(information if mode single or double selected)
}

void mainapp::displaySelectedData() {    
    if (csvFilePath.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please select a CSV file first.");
        return;
    }

    if(change_dist == true){
    //put inputs to variables from qlineedit
    bool columnOk, secondColumnOk, startRowOk, endRowOk;//if valid bool variables
    column = columnInput->text().toInt(&columnOk) - 1;//Adjust for 0-based indexing
    secondColumn = secondColumnInput->text().toInt(&secondColumnOk) - 1;//Second column
    startRow = rowStartInput->text().toInt(&startRowOk) - 1;
    endRow = rowEndInput->text().toInt(&endRowOk) - 1;

    //check data correction
    qDebug() << "File path:" << csvFilePath;
    qDebug() << "Column:" << column << ", Start row:" << startRow << ", End row:" << endRow;
    qDebug() << "Second column:" << secondColumn << ", Double column enabled:" << doubleColumnRadio->isChecked();

    if (!columnOk || !startRowOk || !endRowOk || startRow < 0 || endRow < startRow ||
        (doubleColumnRadio->isChecked() && !secondColumnOk)) {
        QMessageBox::warning(this, "Error", "Invalid input for column(s) or row range.");
        return;
    }
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
                    left_column_vec.push_back(columns[column].toDouble());//save data column from row in vector
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
                        right_column_vec.push_back(columns[secondColumn].toDouble());//save data column from row in vector
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

void mainapp::change_csv()//delete choosen file (clear path)
{
    csvFilePath.clear();
    QMessageBox::information(this, "Success", ".csv path is empty now...");

     QString filePath = QFileDialog::getOpenFileName(this, "Select CSV file", "", "CSV Files (*.csv)");//use .csv
     if (filePath.isEmpty()) {
         return;
     }

     //Store the file path for further processing
     csvFilePath = filePath;
     qDebug() << "Selected file:" << csvFilePath;//check if selection is ok
}

void mainapp::area_change()//enable to change column and row /not enable
{
    change_dist = !change_dist;//change condition of permittion to change column or row

    if(change_dist == true)
    {
        dataDisplay->setText("You are able to change column and area value... \n \nRemember to turn off this mode before going to stats if you want to keep those values...\n\n\n\nTo save, display data on screen...\n");
        area_change_button->setText("Column and row edit. -> Mode ON!");
    }
    if(change_dist == false)
    {
        dataDisplay->setText("You are not able to change row and column values... Your previous values are in memory!!!\n");
        area_change_button->setText("Column and row edit. ->Mode OFF!");
    }

}

void mainapp::stats1_page()
{
    stats1* stat1 = new stats1(left_column_vec,right_column_vec,all_numbers_left,all_numbers_right,two_column_mode,nullptr);
    qDebug() << "two_column_mode: " << two_column_mode;
    stat1->setAttribute(Qt::WA_DeleteOnClose);
    stat1->show();
    this->close();
}

void mainapp::stats2_page()
{
    stats2* stat2 = new stats2(left_column_vec,right_column_vec,all_numbers_left,all_numbers_right,two_column_mode,nullptr);
    stat2->setAttribute(Qt::WA_DeleteOnClose);
    stat2->show();
    this->close();
}

void mainapp::plotter_page()
{
    plotter* plott = new plotter(left_column_vec,right_column_vec,all_numbers_left,all_numbers_right,two_column_mode,nullptr);
    plott->setAttribute(Qt::WA_DeleteOnClose);
    plott->show();
    this->close();
}

void mainapp::clear_chat()
{
    dataDisplay->clear();
}
