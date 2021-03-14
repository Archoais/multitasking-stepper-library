

/*
 * Multitasking Stepper Library
 * 
 * A library that allows to move steppers at different rates simultaneously
 *
 * Developer: Benjamin F. Medina
 * 
 * Library under construction!
 */


/**********************************************************************************
 *                                  MOVEMENT

 **********************************************************************************
 */

//Simple movement program, moves three motors in partially synchronized sequence.
void cnc(int xi, bool x_dir, int yi, bool y_dir, int zi, bool z_dir, int t, float a)
{
  digitalWrite(dx_pin,  !x_dir);
  digitalWrite(dy_pin,   y_dir);
  digitalWrite(dz_pin,   z_dir);

  //Updating steps into current robot position
  if(x_dir == HIGH)
  { coord[0] += xi; }
  else
  { coord[0] -= xi; }
  
  if(y_dir == HIGH)
  { coord[1] += yi; }
  else
  { coord[1] -= yi; }

  if(z_dir == HIGH)
  { coord[2] += zi; }
  else
  { coord[2] -= zi; }
  
  float d;
  comparator(xi, yi, zi);
  
  for (int i = 0; i < longest_pulse; i++)
  {   d = t + (float)(longest_pulse/6)*cos((6.2831*(float)i*a)/longest_pulse);

    pwr(d);
    if(xi>0)
    {
      digitalWrite(x_pin, HIGH);
      delayMicroseconds(d);
      digitalWrite(x_pin, LOW);
      delayMicroseconds(d);
      xi--;
    }
    if(yi>0)
    {
      digitalWrite(y_pin, HIGH);
      delayMicroseconds(d);
      digitalWrite(y_pin, LOW);
      delayMicroseconds(d);
      yi--;
    }
    if(zi>0)
    {
      digitalWrite(z_pin, HIGH);
      delayMicroseconds(d);
      digitalWrite(z_pin, LOW);
      delayMicroseconds(d);
      zi--;
    }
  }
}

//Moves three motors, indefinitely until a cancellation order is received
void cnst(bool xi, bool x_dir, bool yi, bool y_dir, bool zi, bool z_dir, int t)
{
  digitalWrite(dx_pin,  !x_dir);
  digitalWrite(dy_pin,   y_dir);
  digitalWrite(dz_pin,   z_dir);
  
  ok = false;
  bool step_n[3] =  { xi,     yi,     zi    };
  bool direc[3] =   { x_dir,  y_dir,  z_dir };
 
  while (ok == false)
  {     
      digitalWrite(x_pin, xi);
      digitalWrite(y_pin, yi);
      digitalWrite(z_pin, zi);
      delayMicroseconds(t-100);
      ir_step_ctrl(100);
      digitalWrite(x_pin, LOW);
      digitalWrite(y_pin, LOW);
      digitalWrite(z_pin, LOW);
      delayMicroseconds(t-100);
      pwr(100);

      //Updating succesful steps into current robot position
      for(int i = 0;  i < 3;  i++)
      {
             if(direc[i] == HIGH && step_n[i] == HIGH)
        { coord[i] += 1;  }
        else if(direc[i] == LOW  && step_n[i] == HIGH)
        { coord[i] -= 1;  }
      }
      
      ir_step_ctrl(100);
  }
  reset_val();
}

//Moves all three motors simultaneosly, at different rates and Updates Position.
void sync(int xi, bool x_dir, int yi, bool y_dir, int zi, bool z_dir, int t)
{


  digitalWrite(dx_pin,  !x_dir);
  digitalWrite(dy_pin,   y_dir);
  digitalWrite(dz_pin,   z_dir);

  //Updating steps into current robot position
    if(x_dir == HIGH)
  { coord[0] += xi; }
  else
  { coord[0] -= xi; }
  
  if(y_dir == HIGH)
  { coord[1] += yi; }
  else
  { coord[1] -= yi; }

  if(z_dir == HIGH)
  { coord[2] += zi; }
  else
  { coord[2] -= zi; }

  comparator(xi, yi, zi);

  const int res = longest_pulse;
  byte  pulse[longest_pulse+1];

  float f = 1.0;
  float x_ratio = (float)longest_pulse / (xi);
  
  float y_ratio = (float)longest_pulse / (yi);
  float z_ratio = (float)longest_pulse / (zi);

  int xj = 1;
  int yj = 1;
  int zj = 1;

  int pulse_x;
  int pulse_y;
  int pulse_z;
  int pulses;

  for(int n = 0; n < longest_pulse; n++)
  {
    if(f >= x_ratio*xj  &&  f <= 1.0 + x_ratio*xj)
    {
      pulse_x = 1;
      xj++;
    }
    else
    {
      pulse_x = 0;
    }
    
    if(f >= y_ratio*yj  &&  f <= 1.0 + y_ratio*yj)
    {
      pulse_y = 2;
      yj++;
    }
    else
    {
      pulse_y = 0;
    }

    if(f >= z_ratio*zj  &&  f <= 1.0 + z_ratio*zj)
    {
      pulse_z = 4;
      zj++;
    }
    else
    {
      pulse_z = 0;
    }

    pulses = pulse_x + pulse_y + pulse_z;
    //Serial.println(pulse[n], BIN);
    f = f + 1.0;
    byte pulse_data = (byte)pulses;

    digitalWrite(x_pin, bitRead(pulse_data,0));
    digitalWrite(y_pin, bitRead(pulse_data,1));
    digitalWrite(z_pin, bitRead(pulse_data,2));
    delayMicroseconds(t);
    digitalWrite(x_pin, LOW);
    digitalWrite(y_pin, LOW);
    digitalWrite(z_pin, LOW);
    delayMicroseconds(t-100);
    pwr(100); 
  }
}


//Finds larger number amongst three ints
void comparator(int x, int y, int z)
{
    if(x >= y &&  x >= z)
  {
    longest_pulse = x;
  }
  else if(y >= x  &&  y >= z)
  {
    longest_pulse = y;
  }
  else if(z >= x  &&  z >= y)
  {
    longest_pulse = z;
  }

  Serial.print("Longest Pulse is: ");
  Serial.println(longest_pulse);
}


//Power Interruptor RESET
void pwr(int t)
{
  if(ir.decode())
  {
    delay(t);
    if(ir.results.value == 0xAF5E817)
    {
      digitalWrite(pwr_pin, !digitalRead(pwr_pin));
      lcd.setCursor(0,1);
      lcd.print("PWR: RELAY RESET");
    }
  }
}
