//Write a C program to find if there are duplicates in an array.
#include <stdio.h>
int duplicateSearch(int arr[], int n, int key){
    int dup=0;
    for(int i=0; i<n; i++){
        for(int j=i+1;j<n; j++){
            if(arr[i]==arr[j]){
                dup=1;
                break;
            }

        }
    }
    return dup;
}

void sortArray(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

int binSearch(int arr[], int n, int key) {
    int low = 0, high = n - 1;
    sortArray(arr, n);
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == key) return 1;
        if (arr[mid] < key) low = mid + 1;
        else high = mid - 1;
    }
    return 0;
}

void main(){
    int n, key;
    printf("Number of elements in array: ");
    scanf("%d", &n);
    int arr[n];
    printf("Enter elements: ");
    for(int i =0; i<n; i++){
        scanf("%d", &arr[i]);
    }
    printf("Key to be searched: ");
    scanf("%d", &key);

    if(binSearch(arr, n, key)==0) printf("\nKey not in array.\n");
    else if(duplicateSearch(arr, n, key)==1) printf("\nKey %d duplicate in array.\n", key);
    else printf("\nKey %d unique in array.\n", key);


}
