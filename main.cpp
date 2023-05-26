#include <QApplication>
#include <QGridLayout>
#include <QPushButton>
#include <QLineEdit>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QWidget window;
    window.setWindowTitle("Калькулятор");

    QGridLayout *layout = new QGridLayout(&window);

    QLineEdit *display = new QLineEdit();
    layout->addWidget(display, 0, 0, 1, 4);

    QPushButton *buttons[16];

    // Создание кнопок с цифрами и операторами
    for (int i = 0; i < 10; ++i) {
        buttons[i] = new QPushButton(QString::number(i));
        layout->addWidget(buttons[i], (i + 3) / 3, (i - 1) % 3);
    }

    buttons[10] = new QPushButton("+");
    layout->addWidget(buttons[10], 1, 3);

    buttons[11] = new QPushButton("-");
    layout->addWidget(buttons[11], 2, 3);

    buttons[12] = new QPushButton("*");
    layout->addWidget(buttons[12], 3, 3);

    buttons[13] = new QPushButton("/");
    layout->addWidget(buttons[13], 4, 3);

    buttons[14] = new QPushButton("Сброс");
    layout->addWidget(buttons[14], 4, 0);

    buttons[15] = new QPushButton("=");
    layout->addWidget(buttons[15], 4, 1, 1, 2);

    // Подключение сигналов и слотов для кнопок
    for (int i = 0; i < 16; ++i) {
        if (i != 14 && i != 15) {
            QObject::connect(buttons[i], &QPushButton::clicked, [=]() {
                display->setText(display->text() + buttons[i]->text());
            });
        }
    }

    // Обработка сброса
    QObject::connect(buttons[14], &QPushButton::clicked, [=]() {
        display->setText("");
    });

    // Обработка вычисления
    QObject::connect(buttons[15], &QPushButton::clicked, [=]() {
        QString expression = display->text();
        float result = 0.0;

        // Выполнение вычислений
        // В данном примере не реализовано полноценное вычисление выражений, 
        // а просто выполняется операция между двумя числами.
        QStringList tokens = expression.split(" ");
        if (tokens.size() == 3) {
            float num1 = tokens[0].toFloat();
            float num2 = tokens[2].toFloat();
            QString op = tokens[1];

            if (op == "+") {
                result = num1 + num2;
            } else if (op == "-") {
                result = num1 - num2;
            } else if (op == "*") {
                result = num1 * num2;
            } else if (op == "/") {
                result = num1 / num2;
            }
        }

        display->setText(QString::number(result));
    });

    window.setLayout(layout);
    window.show();

    return app.exec();
}
