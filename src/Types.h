#pragma once
#include <string>

namespace myType {
	struct Vector2 {	
		int x;
		int y;

		Vector2() 
		{
			x = 0;
			y = 0;
		}

		Vector2(int _x, int _y) 
		{
			x = _x;
			y = _y;
		}

		bool operator==(const Vector2 a)
		{
			return (x == a.x && y == a.y);
		}

		myType::Vector2 operator*(const int e)
		{
			return myType::Vector2(x * e, y * e);
		}
	};

	struct Rect {
		Vector2 position;
		int w;
		int h;

		Rect() 
		{
			position = Vector2();
			w = 0;
			h = 0;
		}

		Rect(int _x, int _y, int _w, int _h) 
		{
			position.x = _x;
			position.y = _y;
			w = _w;
			h = _h;
		}

		Rect(Vector2 r, int _w, int _h) 
		{
			position.x = r.x;
			position.y = r.y;
			w = _w;
			h = _h;
		}

		Rect(int _x, int _y, Vector2 r) 
		{
			position.x = _x;
			position.y = _y;
			w = r.x;
			h = r.y;
		}

		Rect(Vector2 e, Vector2 r) 
		{
			position.x = e.x;
			position.y = e.y;
			w = r.x;
			h = r.y;
		}
	};

	struct Color
	{
		int r;
		int g;
		int b;
		int a;

		Color()
		{
			r = 0;
			g = 0;
			b = 0;
			a = 0;
		}

		Color(int _r, int _g, int _b, int _a) {
			r = _r;
			g = _g;
			b = _b;
			a = _a;
		}
	};

	struct Font
	{
		std::string path;
		int size;
		std::string id;


		Font(std::string _path, int _size, std::string _id) {
			path = _path;
			size = _size;
			id = _id;
		}
	};

	struct Text
	{
		std::string text;
		Color color;
		std::string id;

		Text(std::string _text, Color _color, std::string _id) {
			text = _text;
			color = _color;
			id = _id;
		}
	};

	struct AudioFile
	{
		std::string name;
		std::string path;

		AudioFile(std::string n, std::string p) {
			name = n;
			path = p;
		}
	};
}