//Write a C program to perform the following a) Linear search b) Binary search.
#include <stdio.h>
int linSearch(int arr[], int n, int key) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == key) return 1;
    }
    return 0;
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
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == key) return 1;
        if (arr[mid] < key) low = mid + 1;
        else high = mid - 1;
    }
    return 0;
}

void main(){
    int n, choice, key;
    printf("Number of elements in array: ");
    scanf("%d", &n);
    int arr[n];
    printf("Enter elements: ");
    for(int i =0; i<n; i++){
        scanf("%d", &arr[i]);
    }
    printf("1. Binary search.\n2. Linear search.\n3. Quit.\n Enter choice: ");
    scanf("%d", &choice);
    switch(choice){
    case 1:
        printf("Key to search: \n");
        scanf("%d", &key);
        sortArray(arr, n);
        if(binSearch(arr, n, key)==1) printf("Value found.\n");
        else printf("Value not found.\n");
        break;
    case 2:
        printf("Key to search: \n");
        scanf("%d", &key);
        if(linSearch(arr, n, key)==1) printf("Value found.\n");
        else printf("Value not found.\n");
        break;
    default:
        printf("Exiting.\n");
    }

}
