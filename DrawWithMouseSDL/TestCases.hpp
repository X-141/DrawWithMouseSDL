#pragma once
#include "LineDraw.hpp"
#include <gtest/gtest.h>
#include <vector>

/**
* Help with test cases.
* Makes sure that the points being calculated are what we expect.
*/
bool compare_points(const std::vector<SDL_Point>& calcd_points, const std::vector<SDL_Point>& test_points) {
	assert(calcd_points.size() == test_points.size());

	for (int pos = 0; pos < calcd_points.size(); ++pos) {
		auto calcd_point = calcd_points.at(pos);
		auto test_point = test_points.at(pos);
		std::cout << "calcd point: (" << calcd_point.x << "," << calcd_point.y << ")\n";
		std::cout << "test point: (" << test_point.x << "," << test_point.y << ")\n";
		if (!(calcd_point.x == test_point.x && calcd_point.y == test_point.y))
			return false;
	}
	return true;
}

TEST(TopDownTest, case_1) {
	std::vector<SDL_Point> vec_points;
	std::vector<SDL_Point> comparison_points =
	{
		{3, 1}, {3,2}, {4,3}, {4,4}, {5,5}, {5,6}
	};

	int x_1, y_1, x_2, y_2;
	x_1 = 3; y_1 = 1;
	x_2 = 5; y_2 = 6;
	interpolate_points(x_1, y_1, x_2, y_2, vec_points);
	ASSERT_TRUE(compare_points(vec_points, comparison_points));
}

TEST(DownTopTest, case_1) {
	std::vector<SDL_Point> vec_points;
	std::vector<SDL_Point> comparison_points =
	{
		{5,6}, {5,5}, {4,4}, {4,3}, {3,2}, {3, 1}
	};

	int x_1, y_1, x_2, y_2;
	x_1 = 5; y_1 = 6;
	x_2 = 3; y_2 = 1;
	interpolate_points(x_1, y_1, x_2, y_2, vec_points);
	ASSERT_TRUE(compare_points(vec_points, comparison_points));
}

TEST(LeftRightTest, case_1) {
	std::vector<SDL_Point> vec_points;
	std::vector<SDL_Point> comparison_points =
	{
		{6,2}, {7,2}, {8,3}, {9,3}, {10, 3}, {11,4}, {12,4}
	};

	int x_1, y_1, x_2, y_2;
	x_1 = 6; y_1 = 2;
	x_2 = 12; y_2 = 4;
	interpolate_points(x_1, y_1, x_2, y_2, vec_points);
	ASSERT_TRUE(compare_points(vec_points, comparison_points));
}

TEST(RightLeftTest, case_1) {
	std::vector<SDL_Point> vec_points;
	std::vector<SDL_Point> comparison_points =
	{
		{12,4}, {11,4}, {10, 3}, {9,3}, {8,3}, {7,2}, {6,2}
	};

	int x_1, y_1, x_2, y_2;
	x_1 = 12; y_1 = 4;
	x_2 = 6; y_2 = 2;
	interpolate_points(x_1, y_1, x_2, y_2, vec_points);
	ASSERT_TRUE(compare_points(vec_points, comparison_points));
}

TEST(LinearTest, case_1) {
	std::vector<SDL_Point> vec_points;
	std::vector<SDL_Point> comparison_points =
	{
		{6, 11}, {7, 10}, {8, 9}, {9, 8}
	};

	int x_1, y_1, x_2, y_2;
	x_1 = 6; y_1 = 11;
	x_2 = 9; y_2 = 8;
	interpolate_points(x_1, y_1, x_2, y_2, vec_points);
	ASSERT_TRUE(compare_points(vec_points, comparison_points));
}

TEST(LinearTest, case_2) {
	std::vector<SDL_Point> vec_points;
	std::vector<SDL_Point> comparison_points =
	{
		{6, 11}, {7, 10}, {8, 9}, {9, 8}
	};

	int x_1, y_1, x_2, y_2;
	x_1 = 9; y_1 = 8;
	x_2 = 6; y_2 = 11;
	interpolate_points(x_1, y_1, x_2, y_2, vec_points);
	ASSERT_TRUE(compare_points(vec_points, comparison_points));
}

TEST(HorizontalTest, case_1) {
	std::vector<SDL_Point> vec_points;
	std::vector<SDL_Point> comparison_points =
	{
		{6, 13}, {7, 13}, {8, 13}, {9, 13}, {10, 13}
	};

	int x_1, y_1, x_2, y_2;
	x_1 = 6; y_1 = 13;
	x_2 = 10; y_2 = 13;
	interpolate_points(x_1, y_1, x_2, y_2, vec_points);
	ASSERT_TRUE(compare_points(vec_points, comparison_points));
}

TEST(VerticalTest, case_1) {
	std::vector<SDL_Point> vec_points;
	std::vector<SDL_Point> comparison_points =
	{
		{3,11}, {3, 12}, {3, 13}, {3, 14}
	};

	int x_1, y_1, x_2, y_2;
	x_1 = 3; y_1 = 11;
	x_2 = 3; y_2 = 14;
	interpolate_points(x_1, y_1, x_2, y_2, vec_points);
	ASSERT_TRUE(compare_points(vec_points, comparison_points));
}