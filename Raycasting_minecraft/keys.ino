
void setup_buttons(){
  pinMode(LCD_BUTTON_DOWN,INPUT_PULLUP);
  pinMode(LCD_BUTTON_CENTER,INPUT_PULLUP);
  pinMode(LCD_BUTTON_L,INPUT_PULLUP);
  pinMode(LCD_BUTTON_UP,INPUT_PULLUP);
  pinMode(LCD_BUTTON_R,INPUT_PULLUP);   
}

unsigned int down_up(){
  int d,u,r,l,c;
  d=digitalRead(LCD_BUTTON_DOWN);
  u=digitalRead(LCD_BUTTON_UP);
  r=digitalRead(LCD_BUTTON_R);
  l=digitalRead(LCD_BUTTON_L);
  c=digitalRead(LCD_BUTTON_CENTER);
  if(d==LOW && r!=LOW && l!=LOW){
    //Serial.write("down!\n");
    return blockdown;
  }else if(u==LOW && r!=LOW && l!=LOW){
    //Serial.write("up!\n");
    return blockup;
  }else if(r==LOW && u!=LOW && d!=LOW){
    //Serial.write("right!\n");
    return blockright;
  }else if(l==LOW && u!=LOW && d!=LOW){
    //Serial.write("lift!\n");
    return blocklift;
  }else if(c==LOW){
    //Serial.write("center!\n");
    return blockc;
  }else{
    return 0;
  }
  //delay(50);
}
