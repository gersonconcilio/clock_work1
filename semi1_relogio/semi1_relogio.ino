#include<LiquidCrystal.h>

LiquidCrystal lcd(13,12,11,10,9,8);

// VARIAVEIS RELÓGIO
int hh = 23;
int mm = 59;
int ss = 50;

//CONTADOR
int cont = 0;

void setup() {
  //---------------SETUP 16X2------------------
    lcd.begin(16,2);
    lcd.clear();
  
  //-----------SETUP TIMER1 SEGUNDOS-----------
    TCCR1A = 0;
    TCCR1B = 0;
    TIMSK1 |= (1 << TOIE1);
    TCCR1B = 1;
    TCNT1  = 0;
}

ISR(TIMER1_OVF_vect){
  if(cont == 245){
    action();
    cont = 0;
  }
  TCNT1 = 0;
  cont++;    
}

void show_time(){
  lcd.setCursor(4,0);

  if(hh < 10)
    lcd.print("0");
  lcd.print(hh);
  lcd.print(":");
  if(mm < 10)
    lcd.print("0");
  lcd.print(mm);
  lcd.print(":");
  if(ss < 10)
    lcd.print("0");
  lcd.print(ss);
  
}

void rule_clock(){
    ss += 1;
    if((ss == 60) && (mm < 59)){
      ss = 0;
      mm += 1;      
    }
    else if((ss == 60) && (mm == 59) && (hh < 23)){
      ss = 0;
      mm = 0;
      hh += 1;        
    }
    else if((ss == 60) && (mm == 59) && (hh == 23)){
      ss = 0;
      mm = 0;
      hh = 0; 
    }
}

void action(){
  rule_clock();
  show_time();
}

void loop(){

}