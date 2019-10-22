/**
	* Author: David Wong
	* Project: CS230 Lab 6
	* File Name: Intersection2D.cpp
**/

// Includes //
#include "stdafx.h"
#include "Intersection2D.h"

bool PointCircleIntersection(const Vector2D& point, const Circle& circle)
{
	// Check whether the distance from the circle's center to the point is smaller than the circle's
	// radius, if so the the point and circle collide
	return point.DistanceSquared(circle.center) <= circle.radius * circle.radius;
}

bool PointRectangleIntersection(const Vector2D& point, const BoundingRectangle& rect)
{
	// Check whether the point is inside the bounds of the rectangle
	return point.x < rect.right && point.x > rect.left && point.y < rect.top && point.y > rect.bottom;
}

bool CircleCircleIntersection(const Circle& c1, const Circle& c2)
{
	// Check whether two circles are colliding with each other by comparing the distance between their centers
	// and seeing if that distance is smaller than the addition of both circles' radii, if that distance is smaller
	// than the sum of the radii, the the circles are colliding
	return c1.center.DistanceSquared(c2.center) <= (c1.radius + c2.radius) * (c1.radius + c2.radius);
}

bool RectangleRectangleIntersection(const BoundingRectangle& r1, const BoundingRectangle& r2)
{
	// Check whether the rectangles are colliding with each other by checking all the ways that they would
	// not be colliding and if one of the checks fails then we confirm they are colliding
	return !(r1.right < r2.left || r1.left > r2.right || r1.top < r2.bottom || r1.bottom > r2.top);
}

bool RectangleCircleIntersection(const BoundingRectangle& rect, const Circle& circle)
{
	Vector2D pointClosestToCircle = circle.center;
	// Find the point closest to the circle
	if (pointClosestToCircle.x < rect.left)
		pointClosestToCircle.x = rect.left;
	else if (pointClosestToCircle.x > rect.right)
		pointClosestToCircle.x = rect.right;

	if (pointClosestToCircle.y < rect.bottom)
		pointClosestToCircle.y = rect.bottom;
	else if (pointClosestToCircle.y > rect.top)
		pointClosestToCircle.y = rect.top;
	
	// If the distance between the closest point on the rectangle to the center of the circle
	// is smaller than the circle's radius, then they are colliding
	return PointCircleIntersection(pointClosestToCircle, circle);
}