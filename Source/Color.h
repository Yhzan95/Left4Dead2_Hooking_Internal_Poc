// Colors Class RGBA

#pragma once

class Color
{
public:
	Color() { *((int*)this) = 0; }
	Color(int r, int g, int b, int a = 255) { SetColor(r, g, b, a); }

	void SetColor(int r, int g, int b, int a = 255) {
		_color[0] = (unsigned char)r;
		_color[1] = (unsigned char)g;
		_color[2] = (unsigned char)b;
		_color[3] = (unsigned char)a;
	}

	int r() const { return _color[0]; }
	int g() const { return _color[1]; }
	int b() const { return _color[2]; }
	int a() const { return _color[3]; }

	static Color Red() { return Color(255, 0, 0); }
	static Color Green() { return Color(0, 255, 0); }
	static Color Blue() { return Color(0, 0, 255); }
	static Color Yellow() { return Color(255, 255, 0); }
	static Color Cyan() { return Color(0, 255, 255); }
	static Color White() { return Color(255, 255, 255); }
	static Color Grey() { return Color(128, 128, 128); }

private:
	unsigned char _color[4];
};
