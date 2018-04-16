#include <stdio.h>

#define X 8
#define Y 8

double input_img[X][Y];
double temp[X][Y];

void print_array (double array[X][Y])
{
  printf("\n");
  for (int x = 0; x < X; x++)
  {
    for (int y = 0; y < Y; y++)
    {
      printf("%.2f ", array[x][y]);
    }
    printf("\n");
  }
  printf("\n");
}

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
    for (int y = 0; y < Y; y++)
    {
      fscanf(numbers, "%d,", &read_nr);
      input_img[x][y] = read_nr;
    }
  }
  fclose(numbers);

  printf("\nInput:\n");
  print_array(input_img);
}

void fwt_rows(void)
{
  for (int row = 0; row < X; row++)
  {
    for (int length = X/2; ; length/=2)
    {
      // length is current length of working area
      // it is halved in every iteration until it is 1
      // iterate through working area
      for (int i = 0; i < length; i++)
      {
        temp[row][i] = input_img[row][i*2] + input_img[row][i*2 + 1];
        temp[row][i] /= 2;

        temp[row][i + length] = input_img[row][i*2] - input_img[row][i*2 + 1];
        temp[row][i + length] /= 2;
      }
      if (length == 1)
      {
        goto end1;
      }

      // copy for next iteration
      for (int i = 0; i < X; i++)
      {
        input_img[row][i] = temp[row][i];
      }
    }
    end1: ;
  }
}

void fwt_columns(void)
{
  for (int column = 0; column < Y; column++)
  {
    for (int length = Y/2; ; length/=2)
    {
      // length is current length of working area
      // it is halved in every iteration until it is 1
      // iterate through working area
      for (int i = 0; i < length; i++)
      {
        temp[i][column] = input_img[i*2][column] + input_img[i*2 + 1][column];
        temp[i][column] /= 2;

        temp[i + length][column] = input_img[i*2][column] - input_img[i*2 + 1][column];
        temp[i + length][column] /= 2;
      }
      if (length == 1)
      {
        goto end2;
      }

      // copy for next iteration
      for (int i = 0; i < Y; i++)
      {
        input_img[i][column] = temp[i][column];
      }
    }
    end2: ;
  }
}

int main (int argc, char *argv[])
{
  if (argc != 2)
  {
    printf("Specify a file with input numbers. Try: ./fwt /path/to/file\n");
    return -1;
  }

  read_input(argv[1]);
  fwt_rows();
  printf("\nOutput:\n");
  print_array(temp);

  fwt_columns();
  printf("\nColumns output:\n");
  print_array(temp);

  return 0;
}
