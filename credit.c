#include <stdio.h>
#include <stdlib.h>

// Create a dictionary structure to store card types
struct dict {
  char *name;
  int *value;
} dict;

// A function to return card type
char *creditCardType(int *FirstTwo){
  int checkSum = FirstTwo[0] * 10 + FirstTwo[1];
  int visaCheckSum = checkSum / 10;

  int AMEX_NUMBERS[] = {34, 37, '\0'};
  int MASTERCARD_NUMBERS[] = {51, 52, 53, 54, 55, 22, '\0'};
  int JCB_NUMBERS[] = {35, '\0'};
  int DISCOVER_NUMBERS[] = {60, 30, '\0'};
  int VISA_NUMBERS[] = {4, '\0'};

  struct dict MASTERCARD;
  struct dict AMEX;
  struct dict JCB;
  struct dict DISCOVER;
  struct dict VISA;

  MASTERCARD.name = "MASTERCARD";
  MASTERCARD.value = MASTERCARD_NUMBERS;

  AMEX.name = "AMEX";
  AMEX.value = AMEX_NUMBERS;

  JCB.name = "JCB";
  JCB.value = JCB_NUMBERS;

  DISCOVER.name = "DISCOVER";
  DISCOVER.value = DISCOVER_NUMBERS;

  VISA.name = "VISA";
  VISA.value = VISA_NUMBERS;

  int len = 5;

  struct dict cards[] = {MASTERCARD, AMEX, JCB, DISCOVER, VISA, '\0'};

  struct dict *ptr =  cards;

  for (int i = 0; i < len; i++){
    for (int j = 0; ptr[i].value[j]; j++){
      if (checkSum == ptr[i].value[j] || visaCheckSum == ptr[i].value[j]){
          return(ptr[i].name);
      }
    }
  }
  return("INVALID: Card type not found.");

}

// Check if a number is even in order to multiply every other number
int isEven(int number){
    return (number % 2 == 0) ? 1 : 0;
}

// Check if total modulo 10 is congruent to 0
int isValid(int number){
    (number % 10 == 0) ? 1 : 0;
}

// Obtain the first two numbers from number array
char *finalizeChecks(int *newNumber, int size){
    int i = 0, firstTwo[2];
    // Check for known cards types
    while (size--){
        firstTwo[i++] = newNumber[size];
        if (i == 2)
            return creditCardType(firstTwo);
    }
}

// Check card number according to Luhn’s Algorithm
int checkNumber(int *newNumber, int size){
    int total = 0, totalM = 0, newTotal = 0, current = 0, i = 0, tmp = 0, sum = 0;
    while (size--){
        current = isEven(i+1);
        if (current){
            sum = newNumber[i] * 2;
            if (sum >= 10) {
                tmp += sum % 10;
                sum /= 10;
                tmp += sum;
                sum = tmp;
            }
            totalM += sum;
        }
        else
            total += newNumber[i];
        i++;
    }
    newTotal = totalM + total;
    return (isValid(newTotal)) ? 1 : 0;
}

// Prompt user for card number
long int get_input(char *s){
  long int value;
  printf("%s", s);
  scanf("%ld", &value);
  return value;
}

// Main method
int main(int argc, char **argv){
    long cardNumber;
    int newNumber[30];
    int size = 0, current = 0;
    char *eptr;

    // Check for input (testing purposes)
     if( argc == 2 ) {
        cardNumber = strtol(argv[1], &eptr, 10);
     } else if( argc > 2 ) {
        printf("Too many arguments supplied.\n");
     } else {
        cardNumber = get_input("Enter Credit Card Number: ");
     }

    // Obtain size of number and create iterable version
    while (cardNumber){
        current = cardNumber % 10;
        newNumber[size++] = current;
        cardNumber /= 10;
    }
    // If card number is less than any valid number size, return invalid
    if (size < 13){
        printf("INVALID: Not enough digits.\n");
        return 1;
    }
    // Obtain first two numbers and check if numbers matches known card types + return  validity
    checkNumber(newNumber, size) ? printf("VALID Card of Type: %s.\n", finalizeChecks(newNumber, size)) :   printf("INVALID: total modulo 10 not congruent to 0.\n");
}
