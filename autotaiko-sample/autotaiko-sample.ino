#include <avr/pgmspace.h>

PROGMEM const char pumianFlash[] = 
"111100111100,"
"111100111222,"
"111100111100,"
"111100221221,"
"111100111100,"
"111100111222,"
"111100111100,"
"111100221212,"
"211121212121,"
"212212212121,"
"000000000000,"
"2010201020110020,"
"2020201020201120,"
"2010201020110020,"
"2020102020101120,"
"2010201020101020,"
"2010102010121222,"
"1020102010222020,"
"1020112121201122,"
"1020102010221120,"
"1020102010221220,"
"1020102011221122,"
"1020102010222222,"
"1020102010221120,"
"1020102010221220,"
"1020102011221122,"
"1020102010222222,"
"1020102010201022,"
"1111222211112222,"
"1122112212222222,"
"1000100000101222,"
"1010100020202000,"
"1010100020102012,"
"1010100020202000,"
"1010100012221222,"
"1010100020202000,"
"1010100021212122,"
"1010100020202000,"
"1010100012221122,"
"2020101020201010,"
"2222111122221111,"
"2211221122221111,"
"1000000020000000,"
"1000202020002000,"
"1000100020001000,"
"1000202020002000,"
"1000000020000000,"
"1000202020002000,"
"1000100020001000,"
"2020102020002000,"
"1000100020001000,"
"1000202020002000,"
"2010101020202020,"
"2010101020201010,"
"2020202020202020,"
"1010202010102020,"
"1010202010202020,"
"1010202010102020,"
"1212121210202020,"
"1010202010102020,"
"1010202010202020,"
"1020201020101020,"
"1020102021022122,"
"1010202010102020,"
"1010202010202020,"
"1010202010102020,"
"1212121210202020,"
"1010202010102020,"
"1010202010202020,"
"1020201020101020,"
"1020102021022122,"
"1022222222222222,"
"1111111111111111,"
"2222222211111111,"
"2222222211111111,"
"2222111122221111,"
"2121212121212121,"
"2010201020201020,"
"2010201020102020,"
"2010201020201020,"
"2010211101112120,"
"2010201020201020,"
"2010201010201020,"
"2020102010201020,"
"2020112201211120,"
"2020102010201020,"
"1010202020102010,"
"2020102010201020,"
"1010211101112120,"
"2010201020201020,"
"1020102010202010,"
"2010202010201020,"
"111122112020202022102210,"
"1120221022102212,"
"2122121210001000,"
"1000100010002020,"
"1000102010001020,"
"1121212110001211,"
"2112100021112111,"
"2112112112112112,"
"1212121212121212,"
"1000100000300000,"
"2000200000400000,"
"1000100000300000,"
"2000200000400000,"
"1000100000300000,"
"2000200000400000,"
"1000100000300000,"
"2020102020102222,"
"2020101020201010,"
"2020101020101020,"
"2020101020201010,"
"2020101012222222,"
"2020101020201010,"
"2020101020102010,"
"2020101020201010,"
"2020101022221122,"
"2020101020010102,"
"1022201020201022,"
"1111111122222222,"
"1010202010201010,"
"1020101020101010,"
"2020102010201010,"
"2010102010102010,"
"2010102010102010,"
"1020102010201020,"
"1020100020101020,"
"1000201010002010,"
"1000211110201020,"
"1020102010201021,"
"1110201010201020,"
"1010201010222222,"
"1010300000101030,"
"0010101021212121,"
"1010300000100030,"
"2020202010222222,"
"1010300000101030,"
"0010101021212121,"
"1010300000100030,"
"1111112121212121,"
"5,"
"000000000000000000000000000000000000000000000008,";

int Left_blue = 2;
int Left_red = 3;
int Right_red = 8;
int Right_blue = 9;
int button = 0;

void setup(){
  Serial.begin(9600);
  pinMode(button, INPUT);
  pinMode(Left_red, OUTPUT);
  pinMode(Right_red, OUTPUT);
  pinMode(Left_blue, OUTPUT);
  pinMode(Right_blue, OUTPUT);
  }
  
void loop(){
   if(digitalRead(button) == LOW){
    int total = 2580;                     //总note数+乐段数
    int bpm = 160;                        //初始BPM
    int shaky = 5;                        //按键从按下到抬起的时间
    int pai = 60000/bpm;                  //计算延迟时间
    float measure = 3;                    //初始拍子
    int bar_place[] = {11,92,93};         //改变节奏bar的位置
    int CM_data[] = {4,4,4};              //改变的节拍
    int CBPM_data[] = {300,300,300};      //改变的BPM
    int change = -1;
    float T_measure = 1/measure;
    float bpm_speed = pai*T_measure;
    bpm_speed = bpm_speed - shaky;
    int i = 0;                             //初始化i的值
    int state = 0;                         //左右交替状态
    int yellow = 0;
    int p = 0;                             //变速位置
    int bar = 0;
    while (i<=total-1){
      char pumian = pgm_read_byte(&pumianFlash[i]);//flash读取谱面信息
      if(bar==bar_place[p]){
        bpm = CBPM_data[p];                        //改变BPM
        pai = 60000/bpm;                  //计算延迟时间
        measure = CM_data[p];
        T_measure = 1/measure;
        bpm_speed = pai*T_measure;
        bpm_speed = bpm_speed - shaky;
        p++;
        Serial.println(bpm_speed);
        Serial.println(pumian);
        }
        
      if(pumian=='0'&&yellow==0){
        i++;
        delay (bpm_speed+shaky+change);
        }
      
      else if(pumian=='1'){   //咚
        if(state==0){
          i++;
          digitalWrite(Left_red,HIGH);
          delay(shaky);
          digitalWrite(Left_red,LOW);
          delay (bpm_speed);
          state = 1;
          }
        else{
          i++;
          digitalWrite(Right_red,HIGH);
          delay(shaky);
          digitalWrite(Right_red,LOW);
          delay (bpm_speed);
          state = 0;
          }
        }
      
      else if(pumian=='2'){   //咔
        if(state==0){
          i++;
          digitalWrite(Left_blue,HIGH);
          delay(shaky);
          digitalWrite(Left_blue,LOW);
          delay (bpm_speed);
          state = 1;
          }
        else{
          i++;
          digitalWrite(Right_blue,HIGH);
          delay(shaky);
          digitalWrite(Right_blue,LOW);
          delay (bpm_speed);
          state = 0;
          }
        }
      
      else if(pumian=='3'){   //大咚
        i++;
        digitalWrite(Left_red,HIGH);
        digitalWrite(Right_red,HIGH);
        delay(shaky);
        digitalWrite(Left_red,LOW);
        digitalWrite(Right_red,LOW);
        delay (bpm_speed);
        }
      
      else if(pumian=='4'){   //大咔
        i++;
        digitalWrite(Left_blue,HIGH);
        digitalWrite(Right_blue,HIGH);
        delay(shaky);
        digitalWrite(Left_blue,LOW);
        digitalWrite(Right_blue,LOW);
        delay (bpm_speed);
        }
      else if(pumian=='8'){
        yellow = 0;
        delay (yellow);
        }
      else if(pumian=='5'||pumian=='6'||pumian=='7'||yellow==1){   //连打
        i++;
        digitalWrite(Left_blue,HIGH);
        digitalWrite(Right_blue,HIGH);
        digitalWrite(Left_red,HIGH);
        digitalWrite(Right_red,HIGH);
        delay(shaky);
        digitalWrite(Left_blue,LOW);
        digitalWrite(Right_blue,LOW);
        digitalWrite(Left_red,LOW);
        digitalWrite(Right_red,LOW);
        delay (bpm_speed);
        yellow = 1;
        delay (yellow);
        }
      else if(pumian==','){
        i++;
        bar++;
        }
      else {
        i++;
        delay (bpm_speed + shaky + change);
        }
      }
    }
  }
