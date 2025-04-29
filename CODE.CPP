#include <iostream.h>
#include <conio.h>
#include <dos.h>
#include <time.h>

/*#define ONE_MICROSECOND (CLOCKS_PER_SEC / 1000000)
void delay_microseconds(unsigned long useconds){
clock_t start = clock();
clock_t end = start + useconds * ONE_MICROSECOND;
while (clock() < end);
} */



#define PortAddress 0x378
#define TR1 0x80
#define TR2 0x40
#define TR3 0x20
int cw[7] = { 0x01, 0x03, 0x02, 0x06, 0x04, 0x0c, 0x08 };
int ccw[7] = { 0x08, 0x0c, 0x04, 0x06, 0x02, 0x03, 0x01 };
int k = 0;
int pos = 0;
int true = 1;
char input;
char SelectMask;


void CW(int rotationDegree) {

  k = pos;


  for (int i = 0; i < rotationDegree; i++) {
    if (k >= 7) { k = 0; }

    cout << "CW" << endl;
    outportb(PortAddress, cw[k]);
    delay(2);
    k++;
  }
  pos = k;
}
void CCW(int rotationDegree) {
  k = pos;
  for (int i = 0; i < rotationDegree; i++) {
    if (k >= 7) { k = 0; }

    cout << "CCW" << endl;
    outportb(PortAddress, ccw[k]);
    delay(2);
    k++;
  }
  pos = k;
}




void main() {
  clrscr();

  while (true == 1) {
    for (int i = 0; i <= 6; i++) {
      cw[i] = cw[i] & 0x1f; //make last 3 bit zeros
      ccw[i] = ccw[i] & 0x1f;
    }
    cout << "enter number of stepper" << endl;
    SelectMask = getch();  //take char and jamp to another line
    if (SelectMask == '1') {
      for (int i = 0; i <= 6; i++) {
        cw[i] = cw[i] | TR1;
        ccw[i] = ccw[i] | TR1;
      }
    } else if (SelectMask == '2') {
      for (int i = 0; i <= 6; i++) {
        cw[i] = cw[i] | TR2;
        ccw[i] = ccw[i] | TR2;
      }
    } else if (SelectMask == '3') {
      for (int i = 0; i <= 6; i++) {
        cw[i] = cw[i] | TR3;
        ccw[i] = ccw[i] | TR3;
      }
    } else if (SelectMask == 'm') {
      break;
    }

    while (true == 1) {
      cout << "enter your input" << endl;
      input = getch();
      if (input == 'd') {
        CW(10);
      } else if (input == 's') {
        CCW(10);
      } else if (input == 'b') {
        break;
      }
    }
  }
  cout << "Program is end" << endl;
  getch();
}
