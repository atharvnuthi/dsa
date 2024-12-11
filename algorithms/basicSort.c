// Basic Sort 

#include <stdio.h>
#define N 10

void swap(int*,int*); // swap variables 
void display_array(int*,int); // display array 
void insertion(int*,int); 
void bubble(int*,int);
void selection(int*,int);

int main(){
  int array[N] = {1,80,9,9,9,6,7,8,9,1};
  // selection(array,N);
  // bubble(array,N);
  insertion(array,N);
  display_array(array,N);
  return 0;  
};

void bubble(int *array, int n){
  // For comparison purposes in an array, two adjacent cells are needed; 
  // in an array of 6 elements, you do 6-1 comparisons only
  for (int i=0; i<n-1; ++i){
      int swapped = 0; 
      // highest value goes in the last position after 1st cycle, 
      // so no need to compare that value with anything else, therefore array is shortened
      for (int j =0; j<n-1-i; ++j){
        if (array[j] > array[j+1]){
            swap(&array[j],&array[j+1]);
            swapped = 1; 
        };
      };
  if (swapped == 0){
        break; // end the loop if nothing gets swapped, meaning our array is already sorted 
     };
  };
};

void selection(int *array, int n){
    for (int i =0; i<n-1; ++i){
    for (int j = i+1; j<n; ++j){
        if (array[j]<array[i]){
            swap(&array[j],&array[i]);
        };
      };
    };
  // keeps moving minimum value to the leftmost side,
  // j = i+1, and always ends < N, so i has to be < N-1 
  // we don't need to save the position of a minimum value in a variable 
};

void insertion(int *array, int n){
    int i , j;
    for (i = 1; i < n; ++i){ // j does not need to start from 0
      for (j = i; j > 0; j--){
          if (array[j-1] > array[j]){
            swap(&array[j],&array[j-1]);
          }
        } 
    };
};

void display_array(int *array, int n){
  printf("[");
  for (int k = 0; k < N; k++){
    printf("%d,",array[k]);  
  };
  printf("]\n");
};

void swap(int *a, int *b){
  int temp = *a;
  *a = *b;
  *b = temp;
};
