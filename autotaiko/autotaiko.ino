#include <avr/pgmspace.h>

PROGMEM const char pumianFlash[] = 
"";//谱面信息
/*铺面格式
"1110111011101110,"
"1110111011101110,"
"1110111011101110,"
........
*/

//输出与输入端口定义
int Left_blue = 2;
int Left_red = 3;
int Right_red = 8;
int Right_blue = 9;
int button = 0;

void setup(){
  pinMode(button, INPUT);
  pinMode(Left_red, OUTPUT);
  pinMode(Right_red, OUTPUT);
  pinMode(Left_blue, OUTPUT);
  pinMode(Right_blue, OUTPUT);
  }
  
void loop(){
   if(digitalRead(button) == LOW){
	   
    int total = 50;                     //总note数+乐段数
    int bpm = 120;                        //初始BPM
    int shaky = 5;                        //按键从按下到抬起的时间
    float measure = 4;                    //初始拍子
    int bar_place[] = {1};         //改变节奏bar的位置
    int CM_data[] = {4};              //改变的节拍
    int CBPM_data[] = {120};      //改变的BPM
	
	int pai = 60000/bpm;                  //计算延迟时间
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
	  
      if(bar==bar_place[p]){				//变速
        bpm = CBPM_data[p];                 //改变BPM
        pai = 60000/bpm;                    //计算延迟时间
        measure = CM_data[p];
        T_measure = 1/measure;
        bpm_speed = pai*T_measure;
        bpm_speed = bpm_speed - shaky;
        p++;
        }
        
      if(pumian=='0'&&yellow==0){	//空
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
