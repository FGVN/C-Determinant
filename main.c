#include <stdio.h>
#include <math.h>
#include <malloc.h>

double det(int n, double **a);

int main(void) {
  
  printf("In data.txt Please enter numbers like following:\n/first number/ = number of unknowns\n/1st coefficient, 2nd... nth, free member/\n etc\n");
  size_t n;
  FILE* datafile = fopen("data.txt", "r+");
  if(datafile == NULL){
    printf("File is emty");
    return 0;
  }
  
  // Зчитування з файлу розмарності матриці
  fscanf(datafile, "%zu", &n);
  //Виділення пам'яті під основну матрицю
  double **a = (double**)malloc(sizeof(double*)*n);
  for(int i = 0; i < n; i++){
    a[i] = (double*)malloc(sizeof(double)*n);
  }
  //Під векторну
  double *vect = (double*)malloc(sizeof(double)*n);
  //Та буферну
  double **detbuf = (double**)malloc(sizeof(double*)*n);
  for(int i = 0; i < n; i++){
    detbuf[i] = (double*)malloc(sizeof(double)*n);
  }
  //Зчитування з файлу в матриці та виведення в консоль
  printf("\nRead matrix A %zu x %zu\n", n, n);
  for(size_t i = 0; i < n; i++){
    for(size_t j = 0; j <= n; j++){
      if(j == n){
       fscanf(datafile, "%lf", &vect[i]);
      }
      else{
       fscanf(datafile, "%lf", &a[i][j]);
       printf("%.f\t", a[i][j]);
      }
    }
    printf("\n");
  }
  //вивід значень векторної матриці
  printf("\nRead Vector Matrix\n");
  for(int i = 0; i < n; i++){
    printf("%.f\n", vect[i]);
  }
  //Вивід рівняння в цілому
  printf("\nThe equasion");
  for(int i = 0; i < n; i++){
    printf("\n");
    for(int j = 0 ; j < n+1; j++){
      if(j == n){
        printf(" = %.f", vect[i]);
      }
      else{
        if(j == 0){
         printf("%.f x%d",a[i][j], j);
        }
        else{ 
        printf(" + %.f x%d",a[i][j], j);
        }
      }
    }
  }
  //обрахунок визначника матриці та перевірка на рівність нулю
  if(det(n, a) == 0){
    printf("\n\nMain det = 0, so equasion can not be solved");
    return(0);
  }
  //вивід визначника
  printf("\n\nMain det = %.f",det(n, a));

  for(int k = 0; k < n; k++){
  for(int i = 0; i < n; i++){
    //почергово підставляємо вектор-стовпчик в кожен стовпець основної матриці
    for(int j = 0; j < n; j++){
      if(j == k){
        detbuf[i][j] = vect[i];
      }
      else{
        detbuf[i][j] = a[i][j];
      }
    }
    
  }
      //виводимо результат ділення визначника основної матриці та утворених підстановкою в консоль та файл
      printf("\ndet%d = %.f", k ,det(n, detbuf));
      double res = (det(n, detbuf) * 1.0/det(n, a));
      fprintf(datafile, "\nx%d = %lf", k ,res);
      printf("\nx%d = %lf", k ,res);
  }
  //вивільнення пам'яті виділеної під матриці
  for(int i = 0; i < n; i++){
    free(detbuf[i]);
  }
  free(detbuf);

  for(int i = 0; i < n; i++){
    free(a[i]);
  }
  free(a);

  free(vect);
  
  fclose(datafile);
}

double det(int n, double **a){
  //повертаємо якщо матриця розмірності 2 на 2
  if(n==2){
    return a[0][0]*a[1][1] - a[1][0]*a[0][1];
  }
  else{
       double detfin = 0;//змінна що відповідає кінцевому значенню визначника операції
       //виділення пам'яті під буферну матрицю
       double **buf = (double**)malloc(sizeof(double*)*(n-1));
       for(int i = 0; i < n-1; i++){
         buf[i] = (double*)malloc(sizeof(double)*(n-1));
       };
       for(int i = 0; i < n; i++){
       for(int j = 0; j < n; j++){ 
       int row = 0; //змінна що відповідає за рядок що викреслюється
       for(int k = 0; k < (n-1); k++){ 
         
       int col=0; //змінна що відповідає за стовпець що викреслюється
       for(int l = 0; l < (n-1); l++){
         
       if(row == (i)){
         row++;
       }
       if(col == (j)){
         col++;
       }
          buf[k][l] = a[row][col];//заповнюємо буферну матрицю 
          col++;
      }
      
      
      row++;
     } 
     //рекурсивно обраховуємо визначник мінору 
     detfin = detfin + (a[0][j]*det(n-1, buf))*pow(-1, i+j);
    }
    if(i == 0){
        break;
    } 
   }
   return detfin; //повертаємо кінцеве значення визначника
}
}