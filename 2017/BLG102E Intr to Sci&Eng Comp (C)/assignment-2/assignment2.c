#include <stdbool.h> // true, false
#include <stdio.h>   // printf, scanf
#include <stdlib.h>  // EXIT_SUCCESS
/*
 * Calculates and returns points for throw.
 * @param points points corresponds to numeric value of each segment. 
 * @param ring ring is either a scalar for throw (double,triple) or a special value for throw (Bull's Eye).
 * @return Point value for the throw.
 * points should be a positive integer between 1-20.
 * ring should be a character. 'I' for inner bull, 'O' for outer bull, 'T' for triple, 'D' for double, 'S' for single.
 * */
int points_for_throw(int points, char ring)
{
    if (ring == 'D') {
        points *= 2;
    } else if (ring == 'T') {
        points *= 3;
    } else if (ring == 'O') {
        points = 25;
    } else if (ring == 'I') {
        points = 50;
    }
    return points;
}

/*
 * Determines remaining points for each throw.
 * @param points points is the value that player needs to reduce to 0.
 * @param segment is numeric value for each throw.
 * @param ring ring is either a scalar for throw (double,triple) or a special value for throw (Bull's Eye).
 * @param game_started game started is just a helper parameter to determine whether the game started.
*/
int remaining_points(int points, int segment, char ring, bool game_started)
{
    int remaining_points = points;
    
    if (game_started) {
        int decrement_amount = points_for_throw(segment, ring);
        if (remaining_points - decrement_amount > 1) {
            remaining_points -= decrement_amount;
        } else if (ring == 'D' && remaining_points - decrement_amount == 0) {
            remaining_points -= decrement_amount;
        }
    }
    return remaining_points;
}
int main()
{

    // Get target points from user.
    int points = 0;
    printf("Target: ");
    scanf("%d", &points);
    printf("\n");
    
    // Game will not really start untill player throws a double.
    bool game_started = false;

    // Create main loop for the game.
    while (points > 0) {

        // Get a throw from user.
        int segment = 0;
        char ring = 'S';
        printf("Throw: ");
        scanf("%d %c", &segment, &ring);

        if (ring == 'D') {       // When player throws a double once,
            game_started = true; // game should start.
        }

        // Calculate and show remaining points.
        points = remaining_points(points, segment, ring, game_started);
        printf("Points: %d\n", points);
    }

    return EXIT_SUCCESS;
}

