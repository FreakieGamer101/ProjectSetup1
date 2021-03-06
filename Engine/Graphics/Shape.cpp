#include "pch.h"
#include "core.h"
#include "Shape.h"
#include "Math/Matrix33.h"
#include "Math/Transform.h"
#include <fstream>

bool nc::Shape::Load(const std::string& filename) {
	bool success = false;
	std::ifstream stream(filename);
	if (stream.is_open()) {
		success = true;

		//read colour
		stream >> m_color;

		//get number of points
		std::string line;
		std::getline(stream, line);
		size_t size;
		size = stoi(line);//string to int

		//read points
		for (size_t i = 0; i < size; i++) {
			Vector2 v;
			stream >> v;
			m_points.push_back(v);
		}

		//read points when you don't know how many there are in the file
		/*while (!stream.eof()) {
			Vector2 point;
			stream >> point;
			if (!stream.eof()) {
				m_points.push_back(point);
			}
		}*/

		stream.close();
	}

	//get radius
	m_radius = 0;
	for (size_t i = 0; i < m_points.size(); i++) {
		nc::Vector2 p1 = m_points[i];
		float length = p1.Length();
		if (length > m_radius) m_radius = length;
	}
	return success;
}

void nc::Shape::Draw(Core::Graphics& graphics, nc::Vector2 position, float scale, float angle)
{
	graphics.SetColor(m_color);

	Matrix33 mxScale;
	mxScale.Scale(scale);
	Matrix33 mxRotate;
	mxRotate.Rotate(angle);
	Matrix33 mxTranslate;
	mxTranslate.Translate(position);

	Matrix33 mx;
	mx = mxScale * mxRotate *mxTranslate;

	for (size_t i = 0; i < m_points.size() - 1; i++) {
		//local or object space points
		nc::Vector2 p1 = m_points[i]; // * 5.0f on both to scale to 5x the size
		nc::Vector2 p2 = m_points[i + 1];

		//scale / rotate / transform
		p1 = p1 * mx;
		p2 = p2 * mx;

		graphics.DrawLine(p1.x, p1.y, p2.x, p2.y);
	}
}

void nc::Shape::Draw(Core::Graphics& graphics, const Transform& transform)
{
	graphics.SetColor(m_color);
	
	for (size_t i = 0; i < m_points.size() - 1; i++) {
		//local or object space points
		nc::Vector2 p1 = m_points[i]; // * 5.0f on both to scale to 5x the size
		nc::Vector2 p2 = m_points[i + 1];

		//scale / rotate / transform
		p1 = p1 * transform.matrix;
		p2 = p2 * transform.matrix;

		graphics.DrawLine(p1.x, p1.y, p2.x, p2.y);
	}
}
