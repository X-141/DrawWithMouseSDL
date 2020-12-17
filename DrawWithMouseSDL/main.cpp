/*
Copyright (c) 2020 Sean Phillips.
All rights reserved.

Redistribution and use in source and binary forms are permitted provided that the above copyright notice 
and this paragraph are duplicated in all such forms and that any documentation, advertising materials, and other materials 
related to such distribution and use acknowledge that the software was developed by seanphillips141@outlook.com. 
The name of the seanphillips141@outlook.com may not be used to endorse or promote products 
derived from this software without specific prior written permission.
THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, 
WITHOUT LIMITATION, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
*/

#include <iostream>
#include <chrono>
#include <thread>

#include "TestCases.hpp"

#include <SDL.h>
#include <SDL_video.h>

#include "LineDraw.hpp"
#include "WindowDecl.hpp"

/* sleep x milliseconds */
inline void sleep_millisecond(const int x) { std::this_thread::sleep_for(std::chrono::milliseconds(1)); }

//int main(int argc, char* argv[]) {
//	testing::InitGoogleTest(&argc, argv);
//	return RUN_ALL_TESTS();
//}

int main(int argc, char* argv[]) {
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_Event event_object;

	if(SDL_Init(SDL_INIT_EVERYTHING) != 0) return -1;

	SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderPresent(renderer);

	int x_pos, y_pos;
	int x_original, y_original;
	bool mouse_down = false;
	SDL_Point points[13];
	std::vector<SDL_Point> vec_points;
	vec_points.reserve(256);
	
	while (1) {
		SDL_PollEvent(&event_object);
		
		switch (event_object.type) {
		
		case SDL_MOUSEMOTION:
			if (mouse_down) {
				while (1) {
					SDL_PollEvent(&event_object);
					if (event_object.type == SDL_MOUSEBUTTONUP) {
						mouse_down = false;
						break;
					}
					SDL_GetMouseState(&x_pos, &y_pos);
					interpolate_points(x_original, y_original, x_pos, y_pos, vec_points);
					x_original = x_pos;
					y_original = y_pos;
					while (!vec_points.empty()) {
						auto inter_point = vec_points.back();
						calculate_points(inter_point.x, inter_point.y, points);
						SDL_RenderDrawPoints(renderer, points, 13);
						vec_points.pop_back();
					}
					SDL_RenderPresent(renderer);
					sleep_millisecond(1);
				}
			}
			break;

		case SDL_MOUSEBUTTONDOWN:
			SDL_GetMouseState(&x_pos, &y_pos);
			calculate_points(x_pos, y_pos, points);
			SDL_RenderDrawPoints(renderer, points, 13);
			SDL_RenderPresent(renderer);
			x_original = x_pos;
			y_original = y_pos;
			mouse_down = true;
			break;
		
		case SDL_MOUSEBUTTONUP:
			mouse_down = false;
			break;

		default:
			break;
		}
		sleep_millisecond(1);
	}
	return 0;
}