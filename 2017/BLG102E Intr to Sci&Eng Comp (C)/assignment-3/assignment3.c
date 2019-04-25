#include <stdio.h>   // printf, scanf
#include <stdlib.h>  // EXIT_FAILURE, EXIT_SUCCESS
#include <stdbool.h> // true, false


/*
 * Takes two integer end returns their absolute difference.
 * @param x an integer
 * @param y an integer
 * @return absolute difference of x and y.
*/
int abs_diff(int x, int y)
{
    return x>y?x-y:y-x;
}

/*
 * Determines whether the given location is available.
 * @param arr an array that holds the location of the cars.
 * @param x a positive integer that represents x coordinate of the location.
 * @param y a positive integer that represents y coordinate of the location.
 * @param size a positive integer between 1 and 50 that represents size of the available parking area.
 * @return true if the given location is in the boundaries and empty, false otherwise.
*/
bool is_available(int arr[][51],int x, int y, int size)
{
    if (x>size || y>size || x<1 || y<1){
        return false;
    }
    if(arr[size-y+1][x] != 0){
        return false;
    }
    return true;
}

/*
 * Calculates and returns nearest car's distance.
 * @param cars_arr an array that holds the location of the cars.
 * @param x a positive integer that represents x coordinate of the location.
 * @param y a positive integer that represents y coordinate of the location.
 * @param size a positive integer between 1 and 50 that represents size of the available parking area.
 * @return manhattan distance between the given location and nearest car. 
*/
int calculate_nearest_car_distance(int cars_arr[][51],int x, int y, int size)
{
    int min_distance = 101; // This is because 101 is maximum possible distance between two location on a 50x50 grid.
    for(int i = 1; i <= size; i++){
        for(int j = 1; j <= size; j++){
            int distance = abs_diff(i,x) + abs_diff(j,y);
            if (cars_arr[i][j] == 1 && distance < min_distance ){
                min_distance = distance;
            }
        }
    }
    return min_distance;
}

/*
 * Fills each slot of given array with distances.
 * @param cars_arr an array that holds the location of the cars.
 * @param dist_arr an empty array that is going to be filled.
 * @param size a positive integer between 1 and 50 that represents size of the available parking area.
*/
void fill_distance_array(int cars_arr[][51], int dist_arr[][51], int size)
{
    for(int i = 1; i <= size; i++){
        for(int j = 1; j <= size; j++){
            if (cars_arr[i][j] != 1){
                dist_arr[i][j] = calculate_nearest_car_distance(cars_arr,i,j,size);
            }
            else{
                dist_arr[i][j] = 0;
            }
        }
    }
}

int main()
{
    // Get size of parking area from user.
    int size = 0;
    printf("Size: ");
    scanf("%d", &size);
    while(size > 50 || size < 1){
        printf("Size must be between 50 and 1\n");
        printf("Size: ");
        scanf("%d", &size);
    }
    
    // Initialize the parking area.
    int car_parking_area[51][51] = {0};

    // Get number of cars from user.
    int number_of_cars = 0;
    printf("Cars: ");
    scanf("%d", &number_of_cars);
    
    // Input validation
    if (number_of_cars > size * size){
        printf("There should be at most %d cars.\n",size*size);
        return EXIT_FAILURE;
    }
    if (number_of_cars < 0 ){
        printf("There is a problem with your input.\n");
        return EXIT_FAILURE;
    }
    if (number_of_cars == size * size){
        printf("Best Slot Found In: 0 0\n");
        return EXIT_SUCCESS;
    }
    
    
    // Get the location information for each car.
    for(int i = 0; i < number_of_cars; i++){
        printf("Locations: ");
        int x = 1, y = 1;
        scanf("%d %d",&x, &y);
        if (is_available(car_parking_area, x, y, size)){
            car_parking_area[size-y+1][x] = 1;
        }
    }
    
    // Find the distance to the nearest car for all slots and assign it to an array.
    int distance_to_nearest_car[51][51] = {0};
    fill_distance_array(car_parking_area, distance_to_nearest_car, size);
    
    // Determine the best slot by looking the largest element of the array and print it.
    int x = 0, y = size + 1, largest_distance_so_far = 0;
    for(int j = size; j >= 1; j--){ // j is the columns of the array. In this case it is related with x. So starting from the most right side makes things easier.
        for(int i=1; i <= size; i++) // i is the rows of the array and it is related with y. We are starting from the top and going down for each column.
            if (distance_to_nearest_car[i][j] >= largest_distance_so_far){
                x = j;
                y = size-i+1; // Here, we needed to flip y, because i = 1 corresponds to y = 5 if size is equal to 5.
                largest_distance_so_far = distance_to_nearest_car[i][j];
            }
    }
    printf("Best Slot Found In: %d %d\n",x,y);


    return EXIT_SUCCESS;
}
