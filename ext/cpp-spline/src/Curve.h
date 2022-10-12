#ifndef _H__CURVE_H
#define _H__CURVE_H

#include "Vector.h"
#include <vector>
#include <cassert>

class Curve
{
public:
	Curve();
	virtual ~Curve();

protected:
	std::vector<Vector> _way_points;
public:
	void add_way_point(const Vector& point);
	void clear();

protected:
	void add_node(const Vector& node);
	virtual void _on_way_point_added()=0;

protected:
	std::vector<Vector> _nodes;
	std::vector<double> _distances;
public:
	Vector node(int i) const { return _nodes[i]; }
	double length_from_starting_point(int i) const { return _distances[i]; }
	bool has_next_node(int i) const { return static_cast<int>(_nodes.size()) > i; }
	int node_count() const {  return static_cast<int>(_nodes.size()); }
	bool is_empty() { return _nodes.empty(); }
	double total_length() const
	{
		assert(!_distances.empty());
		return _distances[_distances.size() - 1];
	}

protected:
	int _steps;
public:
	void increment_steps(int steps) { _steps+=steps; }
	void set_steps(int steps) { _steps = steps; }
};

#endif