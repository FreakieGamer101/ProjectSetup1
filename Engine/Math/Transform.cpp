#include "pch.h"
#include "Transform.h"

namespace nc{
	std::istream& nc::operator>>(std::istream& stream, Transform& transform){
		stream >> transform.position;

		std::string line;
		std::getline(stream, line);
		transform.scale = stof(line); //string to float
		
		std::getline(stream, line);
		transform.angle = stof(line);

		return stream;
	}
	void Transform::Update(){
		Matrix33 mxScale;
		mxScale.Scale(scale);
		Matrix33 mxRotate;
		mxRotate.Rotate(angle);
		Matrix33 mxTranslate;
		mxTranslate.Translate(position);

		matrix = mxScale * mxRotate * mxTranslate;
	}
}
