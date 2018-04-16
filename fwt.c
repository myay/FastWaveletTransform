#include <stdio.h>

#define X 8
#define Y 8

float w0 = 0.5f;
float w1 = -0.5f;
float s0 = 0.5f;
float s1 = 0.5f;

double input_img[X];
double temp[X];

void read_input (const char* file_name)
{
  FILE *numbers;
  numbers = fopen(file_name, "r");

  if (numbers == NULL)
  {
    printf("Error reading file, try ./fwt /path/to/inputfile\n");
    return;
  }

  int read_nr = 0;

  for (int x = 0; x < X; x++)
  {
    //for (int y = 0; y < Y; y++)
    {
      fscanf(numbers, "%d,", &read_nr);
      input_img[x] = read_nr;
    }
  }
  fclose(numbers);
}

void print_array (double *array)
{
  printf("\n");
  for (int x = 0; x < X; x++)
  {
    //for (int y = 0; y < Y; y++)
    {
      printf("%.2f ", array[x]);
    }
    //printf("\n");
  }
  printf("\n");
}

void fwt(void)
{
  for (int length = X/2; ; length/=2)
  {
    // length is current length of working area
    // it is halved in every iteration until it is 1
    // iterate through working area
    for (int i = 0; i < length; i++)
    {
      temp[i] = input_img[i*2] + input_img[i*2 + 1];
      temp[i] /= 2;

      temp[i + length] = input_img[i*2] - input_img[i*2 + 1];
      temp[i + length] /= 2;
    }
    if (length == 1)
    {
      return;
    }

    // copy for next iteration
    for (int i = 0; i < X; i++)
    {
      input_img[i] = temp[i];
    }
  }
}

void ifwt(void)
{

}


int main (int argc, char *argv[])
{
  if (argc != 2)
  {
    printf("Specify a file with input numbers. Try: ./fwt /path/to/file\n");
    return -1;
  }

  read_input(argv[1]);
  fwt();
  printf("\nInput:\n");
  print_array(input_img);
  printf("\nOutput:\n");
  print_array(temp);

  return 0;
}
