#include <iostream>
#include <QFile>
#include <QImage>
#include <QColor>
#include <QString>

using namespace std;

bool verification_of_existence(char *filename);
std::string convertToString(char* input, int size);
void create_ASCII_art(QImage main_image, char *filename);

int main(int argc,char *argv[])
{
    QImage main_image;

    if(argc < 2)
    {
        cerr << "Error: no arguments. " << endl;
        return 0;
    }

    for(int k = 1; k < argc; k++)
    {
        if(!verification_of_existence(argv[k]))
            return 0;
        create_ASCII_art(main_image, argv[k]);
        cout << "Art " << argv[k] << " create" << endl;
    }
    return 0;
}

bool verification_of_existence(char *filename)
{
    if(!QFile(filename).exists())
    {
        cerr << "\nError: file _" << filename << "_ not exists" << endl;
        return false;
    }
    return true;
}

std::string convertToString(char *input, int size)
{
    string s = "";
    for(int i = 0; i < size; i++)
        s += input[i];
    s.erase(size-4,size-1); //delete .jpg or .png
    s += "txt";
    return s;
}

void create_ASCII_art(QImage main_image, char *filename)
{
    main_image.load(filename);
    int gray_intensity = 0;
    QColor pixel_color;

    if(main_image.isNull())
    {
        cerr << "Error: failed open file _" << filename << "_" << endl;
        exit(0);
    }

    int char_size = sizeof(filename) / sizeof(char);
    QString  filename_txt = QString::fromStdString(convertToString(filename, char_size));
    QFile art(filename_txt);
    art.open(QIODevice::WriteOnly | QIODevice::Text);

    for(int i=0;i < main_image.height(); i++)
    {
        for(int j=0 ;j < main_image.width(); j++)
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
                    cerr << "Error: gray_intensity error";
                    break;
                }
            }
        }
        art.write("\n");
    }
    art.close();
}
