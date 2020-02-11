/*
 * 太鼓达人自动演奏上分emmmm
 * 好像外挂啊。。。
 * zpxrainbowdash编写
 * 版本1.0
 */
#include "Keyboard.h"
int buttonPin = 5;   //针脚定义
int buttonState = 0; // 存储按键状态值

void setup() {
  Keyboard.begin();
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop(){
//输入歌曲信息
  int bpm=154;                         //歌曲bpm bpm请勿高于210
  int total=1808;                      //输入总共谱面数字部分数量
  char pumian[total]={                 //歌曲谱面如果谱面不满的请补0

/*
 * 输入tja谱面
 * 1,0,0,1,0,0,1,0,1,0,0,1,0,0,1,0,
 * 1,0,0,1,0,0,1,0,2,0,0,0,2,0,0,0,
 * 1,0,0,1,0,0,1,0,1,0,0,1,0,0,1,0,
 * 2,0,0,0,2,0,0,0,1,0,0,0,2,0,0,0,
 * 2,0,2,0,1,1,1,0,2,0,2,0,1,1,1,0,
 * 像这样的谱面
 */

  };
/*
 * 之后的数据尽量不要改
 * 
 */
int shaky = 25;                      //抖动修正(按键从按下到抬起的时间)
int bpm_speed = 15000/bpm;           //计算延迟时间
bpm_speed = bpm_speed - shaky;
int hit = bpm_speed/shaky;           //计算黄条在单位时间内能打几次 
int i=0;                             //初始化i的值
int e=0;                             //初始化e的值

//按钮触发

buttonState = digitalRead(buttonPin);
 if (buttonState == LOW) {           // 若按键被按下
     delay(80);                      //等待跳过按键抖动的不稳定过程
     if (buttonState == LOW){        // 若按键被按下 

//运行核心代码

        while (i<=total-1)
        {
            if(pumian[i]=='0'){
              i++;
              delay (bpm_speed+shaky);
            }
            
            else if(pumian[i]=='1'){   //咚
              i++;
              Keyboard.press('J');
              delay(shaky);
              Keyboard.release('J');
              delay (bpm_speed);
            }
            
            else if(pumian[i]=='2'){   //咔
              i++;
              Keyboard.press('K');
              delay(shaky);
              Keyboard.release('K');
              delay (bpm_speed);
            }
            
            else if(pumian[i]=='3'){   //大咚
              i++;
              Keyboard.press('J');
              Keyboard.press('F');
              delay(shaky);
              Keyboard.release('J');
              Keyboard.release('F');
              delay (bpm_speed);
            }
            
            else if(pumian[i]=='4'){   //大咔
              i++;
              Keyboard.press('K');
              Keyboard.press('D');
              delay(shaky);
              Keyboard.release('K');
              Keyboard.release('D');
              delay (bpm_speed);
            }

            else if(pumian[i]=='5'||pumian[i]=='6'||pumian[i]=='7'){  //黄条 大黄条 气球 这里指一个字符的时长
              
              i++;
              while(hit!=e){
                Keyboard.press('J');
                delay(shaky);
                Keyboard.release('J');
                Keyboard.press('F');
                delay(shaky);
                Keyboard.release('J');
                e++;
              }
               
              delay(bpm_speed-2*hit*shaky); //2个shaky的hit倍
              e=0;                          //初始化e的值
              
              while(pumian[i]!='8'){
                i++;
                while(hit!=e){              //直到时间不够击打跳出循环
                  Keyboard.press('J');
                  delay(shaky);
                  Keyboard.release('J');
                  Keyboard.press('F');
                  delay(shaky);
                  Keyboard.release('J');
                  e++;
                }
                delay(bpm_speed-2*hit*shaky);//2个shaky的hit倍
              }
              
              e=0;                          //初始化e的值
              
              while(hit!=e){                //直到时间不够击打跳出循环
                Keyboard.press('J');
                delay(shaky);
                Keyboard.release('J');
                Keyboard.press('F');
                delay(shaky);
                Keyboard.release('J');
                e++;
              }
              
              delay(bpm_speed-2*hit*shaky);//2个shaky的hit倍
              e=0;                         //初始化e的值
            }
            else {
            i++;
            delay (bpm_speed+shaky);
            }
        }
     }
 }
}
