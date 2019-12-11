/*to install keypad library in IDE
 * Sketch->Include Library->Manage Libraries... Then search for Keypad by Mark Stanley and Alexander Brevig.
 * do same for LiquidCrystal
 * 
 * check the pins for your project.
 * 
 * i made the code a little moduler. it will run first time then after that it will ask for 0 or 1 to play again.
 * 
 * main_program function runs most of the codes you gave me. rest of the details are commented.
 * 
 * 
 * CHANGE THE DISPLAY MESSAGE. ITS TOO LONG AND 
 * 
 * 
*/



/*import libraries*/
/**/
#include <Keypad.h>
#include <LiquidCrystal.h>

#define input_length 4

/*initialize LCD pins*/
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

/*define KEYPAD rows and col*/
const byte ROWS = 4; 
const byte COLS = 3; 


/*initialize KEYPAD chars*/
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};


/*initialize KEYPAD pins*/
byte rowPins[ROWS] = {9, 8, 7, 6}; 
byte colPins[COLS] = {14, 15, 16}; 


/*initialize KEYPAD*/
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 


/*initialize variables*/
int Data[input_length]; 
byte data_count = 0;
bool flag = true;
char customKey;
String s;
//tries count
int numberoftries = 0;


/*declare functions*/
bool main_program();
bool playAgain();
int getInput();
int getNumber(int a, int b, int c);
int convert_num(char a);



void setup() {
  // put  your setup code here, to run once:
  Serial.begin(9600);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Game On");
  //delay as you wish
  delay(2000);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  if(flag){
    main_program();
    }
    else{
      if (playAgain()){
        main_program();
      }
    }
}

//runs the main program
bool main_program(){
    // put your main code here, to run repeatedly:
  //take random number between 0 to 100
  //long theNumber=random(1,101);
  //test  
  long theNumber=69;
  //user input
  int guess = 0;
  //hint
  int hint = 0;
  //abs of hint
  int hintNumber = 0;
  String divisiblity = "";
  if (theNumber%2 == 0){
    divisiblity = "2";
    }
  else if  (theNumber%3 == 0){
    divisiblity = "3";
    }
  else if  (theNumber%5 == 0){
    divisiblity ="5";
    }  
  else if  (theNumber%7 == 0){
    divisiblity ="7";
    }
  else if (theNumber%11 == 0){
    divisiblity = "11";
    }
  else{
    divisiblity = "prime number";
    }  
  //jodi lost na dekhae then 0 dio
  while(numberoftries<8){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Put Number from");
    lcd.setCursor(0, 1);
    lcd.print("0 to 100:");
    
  
    //takes input form keypad
    guess = int(getInput());
    numberoftries =numberoftries +1;
    hint =   guess-theNumber;
    hintNumber = abs(hint);
  
  
    lcd.clear();
    delay(200);
    
    if(guess<theNumber && hintNumber >10){
      //prints the number in first row
      lcd.setCursor(0, 0);
      lcd.print(guess);
      
      //prints the msg in 2nd row
      lcd.setCursor(3, 0);
      s=" is too low";
      lcd.print(s);
      delay(2000);
      
      //clears screen
      lcd.clear();
      
      //display next msg
      lcd.setCursor(0,1);
      s="divisible by " + divisiblity;
      lcd.print(s);
    }
    else if(guess<theNumber && hintNumber <9){
      //prints the number in first row
      lcd.setCursor(0, 0);
      lcd.print(guess);

      //prints the msg in 2nd row
      lcd.setCursor(0, 1);
      s="you are close";
      lcd.print(s);
      delay(2000);

      //clears screen
      lcd.clear();

      //display next msg
      lcd.setCursor(0, 1); 
      s= "divisible by " + divisiblity;
      lcd.print(s);
    }
    else if(guess>theNumber && hintNumber >10){
      //prints the number in first row
      lcd.setCursor(0, 0);
      lcd.print(guess);

      //prints the msg in 2nd row
      lcd.setCursor(0, 1);
      s=" is too high";
      lcd.print(s);
      delay(2000);
      
      //clears screen
      lcd.clear();
      
      //display next msg
      lcd.setCursor(0,1);
      s="divisible by " + divisiblity;
      lcd.print(s);
    }
    else if(guess>theNumber && hintNumber <9){
      //prints the number in first row
      lcd.setCursor(0, 0);
      lcd.print(guess);
      
      //prints the msg in 2nd row
      lcd.setCursor(0, 1);
      s=" you are close";
      lcd.print(s);
      delay(2000);
      
      //clears screen
      lcd.clear();
      
      //display next msg
      lcd.setCursor(0, 1); 
      s= "divisible by " + divisiblity;
      lcd.print(s);
    }
    else{
      //prints the number in first row
      lcd.setCursor(0, 0);
      lcd.print(guess);

      //prints the msg in 2nd row
      lcd.setCursor(0, 1);
      s=" right,You win!";
      lcd.print(s);
      
      break;
    }
  
    //choose as much delay as you want
    delay(2000);
  }

  lcd.clear();
  delay(100);
  if(numberoftries>7){
    //prints the msg in first row
    lcd.setCursor(0, 0);
    s= "YOU LOST!";
    lcd.print(s);
    delay(2000);

    //clears screen
    lcd.clear();
    delay(100);
  
    //prints the msg in first row
    lcd.setCursor(0, 0);
    s=" the answer is: ";
    lcd.print(s);

    //prints the msg in 2nd row
    lcd.setCursor(0, 1); 
    lcd.print(s);

    lcd.clear();
    }
  else if(numberoftries>5){
    //prints the number in first row
    lcd.setCursor(0, 0);
    lcd.print(numberoftries);
    
    //prints the msg in 2nd row
    lcd.setCursor(1, 0);
    s= ",moves!cool!";
    lcd.print(s);
    }
  else if(numberoftries>3){
    //prints the number in first row
    lcd.setCursor(0, 0);
    lcd.print(numberoftries);

    //prints the msg in 2nd row
    lcd.setCursor(1, 0);
    s= ",moves!great!";
    lcd.print(s);
    }
  else {
    //prints the number in first row
    lcd.setCursor(0, 0);
    lcd.print(numberoftries);
    
    //prints the msg in 2nd row
    lcd.setCursor(1, 0);
    s= ",move!awesome";
    lcd.print(s);
    }
    //choose as much delay as you want
    delay(2000);
    lcd.clear();
    delay(500);
    
  //resets number of tries
  numberoftries=0;
  //use this flag for running first time only then use play again to run again
  flag=false;
  
}

  



bool playAgain(){
  lcd.clear();
  delay(100);
  lcd.print( "wanna play again, (1/0)?");
  bool playAgain;
  customKey = customKeypad.waitForKey();
    if (customKey){
      char tempChar = customKey;
      //convert char to num
      int tempNum=convert_num(tempChar);
      if(tempNum==1){
        playAgain = true;
      }
      else{
        playAgain = false;
      }
       
    }
    lcd.clear();
    delay(100);
  return playAgain;
}




/*
 * gets input
 * keypad library takes input as char.
 * so needs to convert char into input
*/
int getInput(){
  //run loop till all the digits are given
  while(data_count != input_length-1){
    customKey = customKeypad.getKey();
    if (customKey){
      char tempChar = customKey;
      
      //convert char to num
      int tempNum=convert_num(tempChar);
      lcd.clear();
      Data[data_count] = tempNum;
      lcd.setCursor(data_count,1); 
      lcd.print(Data[data_count]); 
      data_count++; 
    }
  }


//sums up the digits.
  int inputNum=getNumber(Data[0],Data[1],Data[2]);

//display input
  lcd.clear();
  delay(100);
  lcd.setCursor(0,0); 
  lcd.print("input");
  lcd.setCursor(0,1); 
  lcd.print(inputNum);
  delay(2000); 
      
  
  lcd.clear();
  delay(500);
  //clearData();
//resets counter  
  data_count=0;
  
  return inputNum;
}

//converts digits to number
int getNumber(int a, int b, int c){
  int num=a*100+b*10+c;
  return num;
  }
//converts the char to int
 int convert_num(char a){
  int num=a-'0';
  return num;
  }
