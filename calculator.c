#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

/*
  Xavier Thomas
  Section U01
  I affirm that this program is entirely my own work and none of it is the work of any other person.
*/

// function declarations
int commandLineArgs (int num_of_args,char *type_of_arg[]);
int determineOperationType (int a, char operator, int b);
int calculator(char *type_of_arg[]);
int saveToFile(int a, char ob, int b, int output);

int main(int argc, char *argv[]){
  int a;
  char ob;
  int b;

  printf("Please enter an integer with an operator and another integer\nex format: 5 + 6\n");
  if(scanf("%d %c %d",&a,&ob,&b) != 3){
    printf("Incorrect values passed\n");
    return -1;
  }else if (isdigit(ob)){
    printf("Incorrect values passed\n");
    return -1;
  }else if (isdigit(a)){
    printf("Incorrect values passed\n");
    return -1;
  }else if (isdigit(b)){
    printf("Incorrect values passed\n");
    return -1;
  }

  int output = determineOperationType(a,ob,b);

  printf("What we have is %d %c %d = %d\n", a,ob,b,output);
  saveToFile(a,ob,b,output);

  // command line option
  if(argc > 2){
    if(commandLineArgs(argc,argv) == 0){
      printf("When inputting arguments from the command line \nPlease Input only an integer an operator and another integer with spaces in between\n If you are doing a multiplication please use single quotes for the * sign");
      return -1;
    }
    calculator(argv);
  }

  return 0;
}

int saveToFile(int a, char ob, int b, int output){
  // gets current directory
  char path[1024];
  // makes sure there isnt an error before opening files
  if(getcwd(path, sizeof(path)) != NULL){
    FILE *fp; // file initializer
    char fileName[40];

    // Concatenates chars
    strcpy(fileName, "/calculatoroutput.txt");
    strcat(path, fileName);

    // Opens file
    fp = fopen(path,"a+");
    // Writes the output to the file
    fprintf(fp, "Expression output %d %c %d = %d \n", a,ob,b,output);
    // closes the file
    fclose(fp);
  }else{
    printf("Some error occured");
  }
  return 0;
}

int calculator(char *type_of_arg[]){
  int a = *type_of_arg[1] - '0';
  char op = *type_of_arg[2];
  int b = *type_of_arg[3] - '0';
  printf("Formated: %d %c %d\n",a,op,b);
  int output = determineOperationType (a,op,b);
  printf("Return function is %d %c %d = %d\n",a,op,b,output);
  saveToFile(a, op, b, output);
  return 0;
}
// Determines if the values from the command line are valid
int commandLineArgs (int num_of_args,char *type_of_arg[]){

  if(num_of_args != 4){
    return 0;
  }

  /*
    searches through the list of operators
    compares them against whats inside the
    second argument to determine if it's
    an operator
  */
  char operators[] = {'*','+','/','-','%'};
  int possibleAmountOfOperators = sizeof(operators) / sizeof(char);
  int i = 0;

  /*
    Lesson on pointers:
    to access a value in that address of the pointer
    i need to add the unary operator "*" so that
    it returns the value of the variable at that
    location
    A gotcha about this is that the "*" needs to be passed
    with quotations when taking the input from the command line
    meaning 5 "*" 5. for some reason it dosent work like the
    rest do.
  */
  for( i = 0; i < possibleAmountOfOperators; i++){
    if(*type_of_arg[2] == operators[i]){
      return 1;
    }
  }
  return 0;
}
//Determine the type of operator and then execute the expression
int determineOperationType (int a, char operator, int b){
  int value = 0;
  switch(operator){
    case '+': value = a + b; break;
    case '-': value = a - b; break;
    case '*': value = a * b; break;
    case '/': value = a / b; break;
    case '%': value = a % b; break;
  }
  return value;
}
