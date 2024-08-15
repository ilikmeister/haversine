#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <math.h>

#define M_PI 3.1415926535897932384626433
#define MIN_LAT -90
#define MAX_LAT 90
#define MIN_LON -180
#define MAX_LON 180
#define EARTH_R 6371000

struct point {
	double lat;
	double lon;
};

double degrees_to_radians (double degrees) {
	return (degrees * M_PI) / 180.0;
}
bool valid_location (struct point location) {
	if (location.lat >= MIN_LAT && location.lat <= MAX_LAT && location.lon >= MIN_LON && location.lon <= MAX_LON) {
		return true;
	}
	printf("location %f, %f is invalid\n", location.lat, location.lon);
	return false;
}
double haversine (struct point location1, struct point location2) {
	double deltalat = (location2.lat - location1.lat) / 2.0;
	double deltalon = (location2.lon - location1.lon) / 2.0;
	
	double sin1 = sin(degrees_to_radians(deltalat));
	double sin2 = sin(degrees_to_radians(deltalon));
	
	double cos1 = cos(degrees_to_radians(location1.lat));
	double cos2 = cos(degrees_to_radians(location2.lat));
	
	double x = sin1*sin1 + cos1*cos2*sin2*sin2;
	
	return 2 * EARTH_R * asin(sqrt(x));
}

int main (int argc, char *argv[]) {
	if  (argc != 5) {
		fprintf(stderr, "Usage: %s latitude1 longitude1 latitude2 longitude2\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	else {
		struct point	p1;
		struct point	p2;
		
		p1.lat = atof(argv[1]);
		p1.lon = atof(argv[2]);
		p2.lat = atof(argv[3]);
		p2.lon = atof(argv[4]);
		 
		if (valid_location(p1) && valid_location(p2)) {
			printf("distance = %i metres\n", (int)haversine(p1, p2));
		}
	}
	
	return EXIT_SUCCESS;
}
