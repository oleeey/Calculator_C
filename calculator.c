#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* getUserInput();
void removeWhiteSpace(char* input);
int checkInput(char* input, float* num1, float* num2, char* op);
void calculateResult(float num1, float num2, char op, float* result);

int main(int argc, char* argv[])
{
  while (1)
  {
    char* input = getUserInput();
    float num1, num2, result;
    char operator;
    if (checkInput(input, &num1, &num2, &operator) == 0)
    {
      calculateResult(num1, num2, operator, &result);
      printf("= %0.2f\n", result);
    }
    printf("\n");
    free(input);
  }
  return 0;
}

char* getUserInput()
{
  int input_size = 10;
  char* input = malloc(input_size * sizeof(char));
  if (input == NULL)
  {
    return NULL;
  }

  if (fgets(input, input_size, stdin) == NULL)
  {
    free(input);
    return NULL;
  }

  while (input[strlen(input) - 1] != '\n' && !feof(stdin))
  {
    input_size += input_size;
    char* tmp = realloc(input, input_size * sizeof(char));
    if (tmp == NULL)
    {
      free(input);
      return NULL;
    }
    input = tmp;
    if (fgets(input + strlen(input), input_size - strlen(input), stdin) == NULL)
    {
      free(input);
      return NULL;
    }
  }
  input[strlen(input) - 1] = '\0';
  return input;
}

void removeWhiteSpace(char* input)
{
  int count = 0;
  size_t len = strlen(input);
  for (int i = 0; i < len; i++)
  {
    if (isspace(input[i]))
    {
      count++;
    }
  }

  // new string = old string without spaces + 1 for '\0'
  char* tmp = malloc(len - count + 1);

  int j = 0;
  for (int i = 0; i < len; i++)
  {
    if (!isspace(input[i]))
    {
      tmp[j] = input[i];
      j++;
    }
  }
  strcpy(input, tmp);
  free(tmp);
}

int checkInput(char* input, float* num1, float* num2, char* op)
{
  char operators[] = "+-*/";
  removeWhiteSpace(input);

  if (sscanf(input, "%f%c%f", num1, op, num2) != 3)
  {
    printf("Invalid Format! E.g: 5 + 10\n");
    return 1;
  }

  int valid = 0;
  for (int i = 0; i < strlen(operators); i++)
  {
    if (*op == operators[i])
    {
      valid = 1;
    }
  }
  if (!valid)
  {
    printf("Invalid Operator! Allowed operators: +, -, *, /\n");
    return 1;
  }
  return 0;
}

void calculateResult(float num1, float num2, char op, float* result)
{
  switch (op)
  {
    case '+':
      *result = num1 + num2;
      break;
    case '-':
      *result = num1 - num2;
      break;
    case '*':
      *result = num1 * num2;
      break;
    case '/':
      *result = num1 / num2;
      break;
    default:
      *result = 0;
  }
}

