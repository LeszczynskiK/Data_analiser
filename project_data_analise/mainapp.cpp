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

    exit_button = new QPushButton("Exit app...", this);//leave from app
    exit_button->setFont(font);
    exit_button->setStyleSheet("color: yellow;");
    exit_button->setGeometry(30, 770, 360, 70);
    connect(exit_button, &QPushButton::clicked, this, &mainapp::exitApp);

    //Add frame based on QLabel
    QLabel *frame = new QLabel(this);//Frame 1
    int frame_x=x/2+130;//frame x_size
    int frame_y=y/2 + 370;//frame y_size
    frame->setGeometry(600, 30, frame_x, frame_y);//Pos and size
    frame->setStyleSheet("border: 3px solid black;");//Style of frame

    selectFileButton = new QPushButton("Select .csv File...", this);
    selectFileButton->setFont(font);
    selectFileButton->setStyleSheet("color: yellow;");
    selectFileButton->setGeometry(10, 10, 360, 70);
    connect(selectFileButton, &QPushButton::clicked, this, &mainapp::selectFile);

    // Create labels and input fields
    const int x_box_size=50;
    const int y_box_size=50;
    const int x_box_start=10;
    const int y_box_start=95;
    const int gap=60;
    QLabel *columnLabel = new QLabel(": Column number", this);
    columnLabel->setStyleSheet("color: yellow;");
    columnLabel->setFont(font);
    columnLabel->setGeometry(x_box_start+gap, y_box_start, 300, 50);

    columnInput = new QLineEdit(this);
    columnInput->setFont(font);
    columnInput->setGeometry(x_box_start, y_box_start, x_box_size, y_box_size);

    QLabel *rowStartLabel = new QLabel(": Start row number", this);
    rowStartLabel->setStyleSheet("color: yellow;");
    rowStartLabel->setFont(font);
    rowStartLabel->setGeometry(x_box_start+gap, y_box_start+gap, 300, 50);

    rowStartInput = new QLineEdit(this);
    rowStartInput->setFont(font);
    rowStartInput->setGeometry(x_box_start, y_box_start+gap, x_box_size, y_box_size);

    QLabel *rowEndLabel = new QLabel(": End row number", this);
    rowEndLabel->setStyleSheet("color: yellow;");
    rowEndLabel->setFont(font);
    rowEndLabel->setGeometry(x_box_start+gap, y_box_start+2*gap, 300, 50);

    rowEndInput = new QLineEdit(this);
    rowEndInput->setFont(font);
    rowEndInput->setGeometry(x_box_start, y_box_start+2*gap, x_box_size, y_box_size);

    //display data field(screen)
    dataDisplay = new QTextEdit(this);
    dataDisplay->setGeometry(600+10, 30+10, frame_x-20, frame_y-20);;
    dataDisplay->setFont(font);
    dataDisplay->setReadOnly(true);//only to read
    dataDisplay->setStyleSheet("background-color: white; color: black;");//background colour and font colour

    QPushButton *showDataButton = new QPushButton("Show Data", this);
    showDataButton->setFont(font);
    showDataButton->setStyleSheet("color: yellow;");
    showDataButton->setGeometry(10, 280, 360, 70);
    connect(showDataButton, &QPushButton::clicked, this, &mainapp::displaySelectedData);


}

void mainapp::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.drawPixmap(0, 0, background);//Background
    QWidget::paintEvent(event);
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
}

void mainapp::displaySelectedData() {
    if (csvFilePath.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please select a CSV file first.");
        return;
    }

    // Load inputs
    bool columnOk, startRowOk, endRowOk;
    int column = columnInput->text().toInt(&columnOk) - 1; // Adjust for 0-based indexing
    int startRow = rowStartInput->text().toInt(&startRowOk)-1;
    int endRow = rowEndInput->text().toInt(&endRowOk)-1;

    if (!columnOk || !startRowOk || !endRowOk || startRow < 0 || endRow < startRow) {//check if correct input
        QMessageBox::warning(this, "Error", "Invalid input for column or row range.");
        return;
    }

    QFile file(csvFilePath);//file csv
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {//if not correct
        QMessageBox::critical(this, "Error", "Failed to open the CSV file.");
        return;
    }

    QTextStream in(&file);//transform to qtextstream
    QStringList lines;//lines to iterate
    int currentRow = 0;

    while (!in.atEnd()) {
        QString line = in.readLine();
        if (currentRow >= startRow && currentRow <= endRow) {//show only choosen data
            QStringList columns = line.split(',');//default separator is ,
            if (column >= 0 && column < columns.size()) {
                lines.append(QString::number(currentRow + 1) + "row is:  " + columns[column].trimmed());
            } else {
                lines.append(QString("Error: Index out of range"));
            }
        }
        currentRow++;
    }

    file.close();

    if (lines.isEmpty()) {//if no data in current line
        QMessageBox::warning(this, "Warning", "No valid data found in the specified range.");
    }

    dataDisplay->clear();
    dataDisplay->setText(lines.join("\n"));//connect all data from lines and separate them by new line
}


