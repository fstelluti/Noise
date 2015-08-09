#pragma once
#include <vector>
#include <glm/gtx/spline.hpp>


class Curve{
public:
	virtual glm::vec3 getPosition(float t) const = 0;
	virtual void nextPoint() = 0;
	virtual glm::vec3 getTangent(float t) const{
		return  getPosition(t+0.2) - getPosition(t);
	}
};


class LinearCurve: public Curve{
public:
	LinearCurve(std::vector<glm::vec3> points){
		this->points = points;
		currentPoints[0] = 0;
		currentPoints[1] = 1;
	}
	virtual glm::vec3 getPosition(float t) const{
		return glm::mix(
			points[currentPoints[0]],
			points[currentPoints[1]],
		t);
	}
	virtual void nextPoint(){
		currentPoints[0] = currentPoints[1];
		for(int i = 1; i < 2; i++){
			currentPoints[i] = (currentPoints[0] + i)%points.size();// currentPoints[i+1];
		}
		int i = 0;
	}

private:
	//all points
	std::vector<glm::vec3> points;
	//current indexes
	int currentPoints[2];
};

