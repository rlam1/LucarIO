/*
	LucarIO - Un intento de Agar.IO para molestar a Fernando
	16/NOV/2019 - Copyright (C) 2019 Rodolfo Lam. All rights reserved.
*/
#pragma once

template<typename T>
struct Point
{
	T x;
	T y;
};

template<typename T>
struct Rect
{
	Point<T> xy;
	Point<T> wh;
};
