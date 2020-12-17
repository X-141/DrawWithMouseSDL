#include "LineDraw.hpp"
#include "WindowDecl.hpp"

#include <cmath>

void calculate_points(const int c_x, const int c_y, SDL_Point points[13]) {
	int points_pos = 0;
	int offset_x;

	if ((c_x >= 0 && (c_y - 2) >= 0) && (c_x <= WINDOW_WIDTH && (c_y - 2) <= WINDOW_HEIGHT)) {
		points[points_pos++] = { c_x, c_y - 2 };
	}

	if ((c_x >= 0 && (c_y + 2) >= 0) && (c_x <= WINDOW_WIDTH && (c_y + 2) <= WINDOW_HEIGHT)) {
		points[points_pos++] = { c_x, c_y + 2 };
	}

	for (offset_x = c_x - 2; offset_x <= c_x + 2; ++offset_x) {
		if ((offset_x >= 0 && c_y >= 0) && (offset_x <= WINDOW_WIDTH && c_y <= WINDOW_HEIGHT)) {
			points[points_pos++] = { offset_x, c_y };
		}
	}

	for (offset_x = c_x - 1; offset_x <= c_x + 1; ++offset_x) {
		if (offset_x >= 0 && offset_x <= WINDOW_WIDTH) {
			if ((c_y - 1) >= 0 && (c_y - 1) <= WINDOW_HEIGHT) {
				points[points_pos++] = { offset_x, c_y - 1 };
			}

			if ((c_y + 1) >= 0 && (c_y + 1) <= WINDOW_HEIGHT) {
				points[points_pos++] = { offset_x, c_y + 1 };
			}
		}
	}

}

void draw_line_TopDown(const int c_y1, const int c_y2, const float m, const float b, std::vector<SDL_Point>& vec_points) {
	register float calcd_x;
	// Here we calculate the exact x coordinate position for
	// each y position from c_y1 to c_y2.
	for (int pos = c_y1; pos <= c_y2; ++pos) {
		calcd_x = (pos - b) / m; // x = ( y - b) / m;
		// Determine which pixel in the x position to color.
		if (calcd_x - static_cast<int>(calcd_x) < static_cast<float>(.5))
			vec_points.push_back({ static_cast<int>(std::floor(calcd_x)), pos });
		else
			vec_points.push_back({ static_cast<int>(std::ceil(calcd_x)), pos });
	}
}

void draw_line_DownTop(const int c_y1, const int c_y2, const float m, const float b, std::vector<SDL_Point>& vec_points) {
	register float calcd_x;
	// Here we calculate the exact x coordinate position for
	// each y position from c_y1 to c_y2.
	for (int pos = c_y1; pos >= c_y2; --pos) {
		calcd_x = (pos - b) / m; // x = ( y - b) / m;
		// Determine which pixel in the x position to color.
		if (calcd_x - static_cast<int>(calcd_x) < static_cast<float>(.5))
			vec_points.push_back({ static_cast<int>(std::floor(calcd_x)), pos });
		else
			vec_points.push_back({ static_cast<int>(std::ceil(calcd_x)), pos });
	}
}

void draw_lineLeftRight(const int c_x1, const int c_x2, const float m, const float b, std::vector<SDL_Point>& vec_points) {
	register float calcd_y;
	// Here we calculate the exact y coordinate position for
	// each x from c_x1 to c_x2. 
	for (int pos = c_x1; pos <= c_x2; ++pos) {
		calcd_y = (m * pos) + b; // y = mx + b
		// Determine which pixel in the y position to color.
		if (calcd_y - static_cast<int>(calcd_y) < static_cast<float>(.5))
			vec_points.push_back({ pos, static_cast<int>(std::floor(calcd_y)) });
		else
			vec_points.push_back({ pos, static_cast<int>(std::ceil(calcd_y)) });
	}
}

void draw_lineRightLeft(const int c_x1, const int c_x2, const float m, const float b, std::vector<SDL_Point>& vec_points) {
	register float calcd_y;
	// Here we calculate the exact y coordinate position for
	// each x from c_x1 to c_x2. 
	for (int pos = c_x1; pos >= c_x2; --pos) {
		calcd_y = (m * pos) + b; // y = mx + b
		// Determine which pixel in the y position to color.
		if (calcd_y - static_cast<int>(calcd_y) < static_cast<float>(.5))
			vec_points.push_back({ pos, static_cast<int>(std::floor(calcd_y)) });
		else
			vec_points.push_back({ pos, static_cast<int>(std::ceil(calcd_y)) });
	}
}

void draw_lineLinear(const int c_x1, const int c_x2, const float m, const float b, std::vector<SDL_Point>& vec_points) {
	// From whichever is the smallest x, create a linear line to big x.
	for (int pos = std::min(c_x1, c_x2); pos <= std::max(c_x1, c_x2); ++pos)
		vec_points.push_back({ pos, static_cast<int>((m * pos) + b) });
}

void interpolate_points(const int c_x1, const int c_y1, const int c_x2, const int c_y2, std::vector<SDL_Point>& vec_points) {
	const float delta_x = static_cast<float>(c_x2 - c_x1);
	const float delta_y = static_cast<float>(c_y2 - c_y1);

	if (delta_x == 0 && delta_y == 0)
		return;

	// If vertical line, we just iterate over length and fill pixels
	if (delta_x == 0) {
		for (int pos = std::min(c_y1, c_y2); pos <= std::max(c_y1, c_y2); pos++)
			vec_points.push_back({ c_x1, pos });
		return;
	}
	// If horizontal line, we do much the same
	else if (delta_y == 0) {
		for (int pos = std::min(c_x1, c_x2); pos <= std::max(c_x1, c_x2); pos++)
			vec_points.push_back({ pos, c_y1 });
		return;
	}

	const float abs_x = std::abs(delta_x);
	const float abs_y = std::abs(delta_y);
	const float m = static_cast<float>(delta_y / delta_x); // rise / run
	const float b = c_y1 - (m * c_x1); // b = y - mx

	if (abs_y > abs_x) { // If rise is greater than run
		// We need to determine which direction the line is heading.
		if (delta_y > 0) { // Handle case where ending y coordinate is greater than starting y.
			draw_line_TopDown(c_y1, c_y2, m, b, vec_points);
		}
		else { // Otherwise, starting y is greater than ending y coordinate.
			draw_line_DownTop(c_y1, c_y2, m, b, vec_points);
		}
	}
	else if (abs_y < abs_x) { // run is greater
		// We need to determine which direction the line is heading.
		if (delta_x > 0) { // Handle case where ending x coordinate is greater than starting x
			draw_lineLeftRight(c_x1, c_x2, m, b, vec_points);
		}
		else { // Otherwise, starting x is greater than ending y coordinate.
			draw_lineRightLeft(c_x1, c_x2, m, b, vec_points);
		}
	}
	else { // equal. This means its a linear function.
		// We do not need to determine the line heading.
		draw_lineLinear(c_x1, c_x2, m, b, vec_points);
	}
}
