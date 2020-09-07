#include <iostream>
#include <QFile>
#include <QImage>
#include <QColor>
#include <QString>

using namespace std;

#define TXT_TYPE ".txt"

bool verification_of_existence(char *filename);
bool open_image(QImage main_image, char *filename);
std::string convertToString(char* input, int size);
void create_ASCII_art(QImage main_image, char *filename);

int main(int argc,char *argv[])
{
    QImage main_image;
    if(argc < 2)
    {
        cout << "Error: no arguments. " << endl;
        return 0;
    }

    for(int i = 1; i < argc; i++)
    {
        if(!verification_of_existence(argv[i]))
            return 0;
        create_ASCII_art(main_image, argv[i]);

    }
    return 0;
}

bool verification_of_existence(char *filename)
{
    if(!QFile(filename).exists())
    {
        cout << "\nError: file _" << filename << "_ not exists" << endl;
        return false;
    }
    return true;
}

bool open_image(QImage main_image, char *filename)
{
    main_image.load(filename);
    if(main_image.isNull())
    {
        cout << "Error: failed open file _" << filename << "_" << endl;
        return false;
    }
    return true;
}

std::string convertToString(char *input, int size)
{
    string s = "";
    for(int i = 0; i < size; i++)
        s += input[i];
    s.erase(size-4,size-1); //remove .jpg or .png
    s += "txt";
    return s;
}

void create_ASCII_art(QImage main_image, char *filename)
{
    main_image.load(filename);
    if(main_image.isNull())
    {
        cout << "Error: failed open file _" << filename << "_" << endl;
        exit(0);
    }

    int char_size = sizeof(filename) / sizeof(char);
    QString  filename_txt = QString::fromStdString(convertToString(filename, char_size));
    QFile art(filename_txt);

    int gray_intensity = 0;
    QColor pixel_color;
    art.open(QIODevice::WriteOnly | QIODevice::Text);

    int height_MImage = main_image.height();
    int width_MImage = main_image.width();

    for(int i=0;i < height_MImage;i++)
    {
        for(int j=0;j < width_MImage;j++)
        {
            pixel_color = QColor(main_image.pixel(j,i));
            gray_intensity = pixel_color.value();
            switch(gray_intensity)
            {
                case 0 ... 27:
                {
                    art.write("  ");
                    break;
                }
                case 28 ... 52:
                {
                    art.write(".");
                    break;
                }
                case 53 ... 77:
                {
                    art.write(",");
                    break;
                }
                case 78 ... 102:
                {
                    art.write(":");
                    break;
                }
                case 103 ... 127:
                {
                    art.write(";");
                    break;
                }
                case 128 ... 152:
                {
                    art.write("o");
                    break;
                }
                case 153 ... 177:
                {
                    art.write("x");
                    break;
                }
                case 178 ... 202:
                {
                    art.write("%");
                    break;
                }
                case 203 ... 227:
                {
                    art.write("#");
                    break;
                }
                case 228 ... 255:
                {
                    art.write("@");
                    break;
                }
                default:
                {
                    cout << "Error: gray_intensity error";
                    break;
                }
            }
        }
        art.write("\n");
    }
    art.close();
}
