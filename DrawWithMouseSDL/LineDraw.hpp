#ifndef LINEDRAW_HPP
#define LINEDRAW_HPP

#include <vector>
#include <SDL_rect.h>

// specify the points that need to be drawn around center point x, y
// 13 points are drawn around the center point following pattern:
//		  x
//		x x x
//	  x x o x x
//		x x x
//		  x
void calculate_points(const int c_x, const int c_y, SDL_Point points[13]);

/**
* This function handles calculating best fit lines if ending position has a greater
* y value than starting.
* Example coordinate: (3,1) and (5,6).
*/
void draw_line_Rise(const int c_y1, const int c_y2, const float m, const float b, std::vector<SDL_Point>& vec_points);

/**
* This function handles calculating best fit lines if ending position has a lesser
* y value than starting.
* Example coordinate: (5,6) and (3,1).
*/
void draw_line_Run(const int c_y1, const int c_y2, const float m, const float b, std::vector<SDL_Point>& vec_points);

/**
* Given a starting and ending position in a x,y window. Calculate
* a set of points that would best make a line between the points.
*/
void interpolate_points(const int c_x1, const int c_y1, const int c_x2, const int c_y2, std::vector<SDL_Point>& vec_points);


#endif // !LINEDRAW_HPP
