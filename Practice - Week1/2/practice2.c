//Write a C program to print the smallest number and its position in an
//array of size n.
#include <stdio.h>
void smallestSearch(int arr[], int n){
    int smallest=arr[0];
    int index=1;
    for(int i=0; i<n; i++){
        if(arr[i]<smallest) smallest = arr[i];
        index = i+1;
    }
    printf("\nSmallest number in array : %d\n", smallest);
    printf("\nIndex of smallest number: %d\n", index);
}

void main(){
    int n;
    printf("Enter number of elements in array: ");
    scanf("%d", &n);
    int arr[n];

    printf("Enter elements: \n");
    for(int i=0; i<n; i++) scanf("%d", &arr[i]);

    smallestSearch(arr, n);
}
