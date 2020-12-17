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
void draw_line_TopDown(const int c_y1, const int c_y2, const float m, const float b, std::vector<SDL_Point>& vec_points);

/**
* This function handles calculating best fit lines if ending position has a lesser
* y value than starting.
* Example coordinate: (5,6) and (3,1).
*/
void draw_line_DownTop(const int c_y1, const int c_y2, const float m, const float b, std::vector<SDL_Point>& vec_points);

/**
* This function handles calculating best fit lines if starting position has a greater x
* value than ending.
* Example coordinates: (6,2) and (12, 4).
*/
void draw_lineLeftRight(const int c_x1, const int c_x2, const float m, const float b, std::vector<SDL_Point>& vec_points);

/**
* This function handles calculating best fit lines if starting position has a lesser x
* value than ending.
* Example coordinates: (12, 4) and (6,2).
*/
void draw_lineRightLeft(const int c_x1, const int c_x2, const float m, const float b, std::vector<SDL_Point>& vec_points);

/**
* This function draws a linear line from starting position to ending position.
* Example coordinates: (6, 11) and (9, 8). Or (9, 8) and (6, 11).
*/
void draw_lineLinear(const int c_x1, const int c_x2, const float m, const float b, std::vector<SDL_Point>& vec_points);

/**
* Given a starting and ending position in a x,y window. Calculate
* a set of points that would best make a line between the points.
*/
void interpolate_points(const int c_x1, const int c_y1, const int c_x2, const int c_y2, std::vector<SDL_Point>& vec_points);


#endif // !LINEDRAW_HPP
