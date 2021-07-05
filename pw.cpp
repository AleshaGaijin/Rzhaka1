#define _CRT_SECURE_NO_WARNINGS

#include <string.h>
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>

int Menu() {
  int option = 0;
  printf("1) Перегляд\n2) Пошук oзера < 50м & солоність > 20%\n");
  scanf_s("%i", &option);

  return option;
}

bool CheckSource(char* path) {
  FILE* stream = fopen(path, "rb");
  if (stream == NULL)
    return false;

  fclose(stream);
  return true;
}

void Seek(char* path) {
  FILE* stream = fopen(path, "rb");
  char line[100];

  for (int i = 1; fgets(line, sizeof(line), stream) != NULL; i++) {
    printf("%i) %s\n", i, line);
  }
  fclose(stream);
}

void SeekForSpecails(char* path) {
  FILE* stream = fopen(path, "rb");
  char line[100];
  char* temp;
  float deepness = 0;
  int salt = 0;

  for (int i = 1; fgets(line, sizeof(line), stream) != NULL; i++) {
    temp = _strdup(line);
    char* t1 = strtok(line, ";");
    t1 = strtok(NULL, ";");
    t1 = strtok(NULL, ";");
    deepness = atof(t1);
    t1 = strtok(NULL, ";");
    salt = atoi(t1);

    if(deepness < 50.f && salt > 20)
      printf("\n%i) %s\n", i, temp);
  }
  fclose(stream);
}

int main()
{
  setlocale(LC_ALL, "ukr");
  printf("Введіть путь до файлу: ");

  char path[100];
  gets_s(path);

  system("CLS");

  if (CheckSource(path) == false)
  {
    printf("Путь к файлу не найден!");
    return 1;
  }

  switch (Menu()) {
  case 1:
    Seek(path);
    break;
  case 2:
    system("CLS");
    SeekForSpecails(path);
    break;
  default:
    system("CLS");
    printf("Вы вышли из программы!");
  }
  system("PAUSE");
}
