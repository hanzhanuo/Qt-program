#include "http_cilent.h"
#include "ui_http_cilent.h"
#include <QUrl>

HTTP_cilent::HTTP_cilent(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::HTTP_cilent)
{
    ui->setupUi(this);
}

HTTP_cilent::~HTTP_cilent()
{
    delete ui;
}

void HTTP_cilent::Audio_Create()
{
    QPushButton* select_btn=new QPushButton("点击选择音频文件",this);

    select_btn->move(100,100);
    //这种移动就和画家的translate一样，都是以坐标系作为视角进行的操作。
    //所以在Qt中一定要有坐标系的视角

    select_btn->resize(300,40);
}

void HTTP_cilent::network_connect()   //这个作为槽函数，设计为对整个http进行连接的函数
{
    //对于这个上半部分，就是通过从设计这个request的对象开始，然后一步步往上推这些参数应该怎么获取
    //其实往上推的思路不难，难的是对于推到最终一步——————从lineedit的text中获取内容比较难想

    //其实并不是它本身比较难想，而是我没有建立text就是cin，setText就是cout这样的思想
    //所以最终一定要能想到——————最终一定会需要从文本中的cin中进行对最起始参数的获取
    //这种对于最起始参数获取的思路，和setText的时候的字符串拼接一样，都是必须要在Qt项目中极其熟练的语句

    QUrl url();
    QNetworkRequest* mp_request=new QNetworkRequest(url);


    //对于代码上半部分思路难点和下半部分思路难点的分界线--------------------------------


    QNetworkAccessManager* mp_manager=new QNetworkAccessManager();

    QNmp_manager->get();

    connect(,[](){

        if(){  //如果没有发生错误的情况

            //由于http只有客户端，所以这里一定是和TCP的客户端一模一样，
            //都是先读入bytearray，再转为qstring，然后再cout(即setText)到纯文本界面上

            //和TCP类比着看：read内容的返回值是qbytearray，write的参数是qbytearray
            //所以每次承接下read需要转换为qstring，write时要先把string转换为bytearray
            //这种规律无论是客户端还是服务端，都是满足这种规律的，从而是可以方便助记的


        }else{  //发生错误的情况

            //但是错误的承接就是qstring，而不是qbytearray
            //然后再cout出来即可

        }
    });



}



