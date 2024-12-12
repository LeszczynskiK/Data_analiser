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
    dataDisplay->setFont(font);
    dataDisplay->setReadOnly(true);//only to read
    dataDisplay->setStyleSheet("background-color: white; color: black;");//background colour and font colour

    showDataButton = new QPushButton("Show Data", this);
    showDataButton->setFont(font);
    showDataButton->setStyleSheet("color: yellow;");
    showDataButton->setGeometry(295, 10, 275, 70);
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

    while (!in.atEnd()) {//if not end
        QString line = in.readLine();
        if (currentRow >= startRow && currentRow <= endRow) {
            QStringList columns = line.split(',');
            QString rowDataLeft, rowDataRight;

            if (column >= 0 && column < columns.size()) {
                rowDataLeft = QString::number(currentRow + 1) + ": " + columns[column].trimmed();
            } else {
                rowDataLeft = QString("Error: Index out of range for Column 1");
            }

            if (doubleColumnRadio->isChecked()) {
                if (secondColumn >= 0 && secondColumn < columns.size()) {
                    rowDataRight = columns[secondColumn].trimmed();
                } else {
                    rowDataRight = QString("Error: Index out of range for Column 2");
                }
            }

            //format the output with fixed-width columns
            QString formattedRow = rowDataLeft.leftJustified(40, ' ') + rowDataRight;
            lines.append(formattedRow);
        }
        currentRow++;
    }

    file.close();//close .csv

    if (lines.isEmpty()) {//if empty
        QMessageBox::warning(this, "Warning", "No valid data found in the specified range.");
    }

    dataDisplay->clear();
    dataDisplay->setText(lines.join("\n"));//display data separately
}




