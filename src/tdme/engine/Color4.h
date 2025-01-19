#pragma once

#include <array>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/math/Math.h>

using std::array;

using tdme::math::Math;

/**
 * Color 4 definition class
 * @author Andreas Drewke
 */
class tdme::engine::Color4
{
protected:
	array<float, 4> data { 0.0f, 0.0f, 0.0f, 1.0f };

public:
	/**
	 * Public constructor
	 */
	inline Color4() {
	}

	/**
	 * Public constructor
	 * @param r red component
	 * @param g green component
	 * @param b blue component
	 * @param a alpha component
	 */
	inline Color4(float r, float g, float b, float a) {
		data[0] = r;
		data[1] = g;
		data[2] = b;
		data[3] = a;
	}

	/**
	 * Public constructor
	 * @param color color as array
	 */
	inline Color4(const array<float, 4>& color) {
		this->data = color;
	}

	/**
	 * Public constructor
	 * @param color color
	 */
	inline Color4(const Color4& color) {
		data = color.data;
	}

	/**
	 * Sets this color by its components
	 * @param r red component
	 * @param g green component
	 * @param b blue component
	 * @param a alpha component
	 */
	inline void set(float r, float g, float b, float a) {
		data[0] = r;
		data[1] = g;
		data[2] = b;
		data[3] = a;
	}

	/**
	 * Sets this color by array
	 * @param color color as array
	 */
	inline void set(const array<float, 4>& color) {
		this->data = color;
	}

	/**
	 * Sets this color by given color
	 * @param color color
	 */
	inline void set(const Color4& color) {
		data = color.data;
	}

	/**
	 * @returns red component
	 */
	inline float getRed() const {
		return data[0];
	}

	/**
	 * Sets red component
	 * @param red red component
	 */
	inline void setRed(float red) {
		data[0] = red;
	}

	/**
	 * @returns green component
	 */
	inline float getGreen() const {
		return data[1];
	}

	/**
	 * Sets green component
	 * @param green green component
	 */
	inline void setGreen(float green) {
		data[1] = green;
	}

	/**
	 * @returns blue component
	 */
	inline float getBlue() const {
		return data[2];
	}

	/**
	 * Sets blue component
	 * @param blue blue component
	 */
	inline void setBlue(float blue) {
		data[2] = blue;
	}

	/**
	 * @returns alpha component
	 */
	inline float getAlpha() const {
		return data[3];
	}

	/**
	 * Sets alpha component
	 * @param alpha alpha component
	 */
	inline void setAlpha(float alpha) {
		data[3] = alpha;
	}

	/**
	 * Adds a scalar
	 * @param scalar scalar
	 * @returns this color
	 */
	inline Color4& add(float scalar) {
		data[0] += scalar;
		data[1] += scalar;
		data[2] += scalar;
		data[3] += scalar;
		return *this;
	}

	/**
	 * Adds a color
	 * @param color color
	 * @returns this color
	 */
	inline Color4& add(const Color4& color) {
		data[0] += color.data[0];
		data[1] += color.data[1];
		data[2] += color.data[2];
		data[3] += color.data[3];
		return *this;
	}

	/**
	 * Subtracts a scalar
	 * @param scalar scalar
	 * @returns this color
	 */
	inline Color4& sub(float scalar) {
		data[0] -= scalar;
		data[1] -= scalar;
		data[2] -= scalar;
		data[3] -= scalar;
		return *this;
	}

	/**
	 * Subtracts a color
	 * @param color color
	 * @returns this color
	 */
	inline Color4& sub(const Color4& color) {
		data[0] -= color.data[0];
		data[1] -= color.data[1];
		data[2] -= color.data[2];
		data[3] -= color.data[3];
		return *this;
	}

	/**
	 * Scales this color
	 * @param scalar scalar
	 * @returns this color
	 */
	inline Color4& scale(float scalar) {
		data[0] *= scalar;
		data[1] *= scalar;
		data[2] *= scalar;
		data[3] *= scalar;
		return *this;
	}

	/**
	 * Scales this color
	 * @param color color
	 * @returns this color
	 */
	inline Color4& scale(const Color4& color) {
		data[0] *= color.data[0];
		data[1] *= color.data[1];
		data[2] *= color.data[2];
		data[3] *= color.data[3];
		return *this;
	}

	/**
	 * Compares this color with given color
	 * @param color color
	 * @param tolerance tolerance per color component
	 * @returns equality
	 */
	inline bool equals(const Color4& color, float tolerance = Math::EPSILON) const {
		return (this == &color) ||
			(
				Math::abs(data[0] - color.data[0]) < tolerance &&
				Math::abs(data[1] - color.data[1]) < tolerance &&
				Math::abs(data[2] - color.data[2]) < tolerance &&
				Math::abs(data[3] - color.data[3]) < tolerance
			);
	}

	/**
	 * Interpolates between a and b by 0f<=t<=1f linearly
	 * @param a color a
	 * @param b color b
	 * @param t t
	 * @returns interpolated color
	 */
	inline static Color4 interpolateLinear(const Color4& a, const Color4& b, float t) {
		return Color4(
			(b.data[0] * t) + ((1.0f - t) * a.data[0]),
			(b.data[1] * t) + ((1.0f - t) * a.data[1]),
			(b.data[2] * t) + ((1.0f - t) * a.data[2]),
			(b.data[3] * t) + ((1.0f - t) * a.data[3])
		);
	}

	/**
	 * @returns color as array
	 */
	inline const array<float, 4>& getArray() const {
		return data;
	}

	/**
	 * Clones this color
	 * @returns new cloned color
	 */
	inline Color4 clone() const {
		return Color4(*this);
	}

	/**
	 * Array access operator
	 * @param i index
	 * @returns color component
	 */
	inline float& operator[](int i) {
		return data[i];
	}

	/**
	 * Const array access operator
	 * @param i index
	 * @returns color component
	 */
	inline const float& operator[](int i) const {
		return data[i];
	}

	/**
	 * Operator + scalar
	 * @param scalar scalar
	 * @returns new color (this + scalar)
	 */
	inline Color4 operator +(const float scalar) const {
		auto r = this->clone().add(scalar);
		return r;
	}

	/**
	 * Operator + color
	 * @param color color
	 * @returns new color (this + color)
	 */
	inline Color4 operator +(const Color4& color) const {
		auto r = this->clone().add(color);
		return r;
	}

	/**
	 * Operator - scalar
	 * @param scalar scalar
	 * @returns new color (this - scalar)
	 */
	inline Color4 operator -(const float scalar) const {
		auto r = this->clone().sub(scalar);
		return r;
	}

	/**
	 * Operator - color
	 * @param color color
	 * @returns new color (this - color)
	 */
	inline Color4 operator -(const Color4& color) const {
		auto r = this->clone().sub(color);
		return r;
	}

	/**
	 * Operator * scalar
	 * @param scalar scalar
	 * @returns new color (this * scalar)
	 */
	inline Color4 operator *(const float scalar) const {
		auto r = this->clone().scale(scalar);
		return r;
	}

	/**
	 * Operator * color
	 * @param color color
	 * @returns new color (this * color)
	 */
	inline Color4 operator *(const Color4& color) const {
		auto r = this->clone().scale(color);
		return r;
	}

	/**
	 * Operator / scalar
	 * @param scalar scalar
	 * @returns new color (this / scalar)
	 */
	inline Color4 operator /(const float scalar) const {
		auto vInverted = Color4(1.0f / scalar, 1.0f / scalar, 1.0f / scalar, 1.0f / scalar);
		auto r = this->clone().scale(vInverted);
		return r;
	}

	/**
	 * Operator / color
	 * @param color color
	 * @returns new color (this / color)
	 */
	inline Color4 operator /(const Color4& color) const {
		auto vInverted = Color4(1.0f / color[0], 1.0f / color[1], 1.0f / color[2], 1.0f / color[3]);
		auto r = this->clone().scale(vInverted);
		return r;
	}

	/**
	 * Operator += scalar
	 * @param scalar scalar
	 * @returns this color
	 */
	inline Color4& operator +=(const float scalar) {
		return this->add(scalar);
	}

	/**
	 * Operator += color
	 * @param color color
	 * @returns this color
	 */
	inline Color4& operator +=(const Color4& color) {
		return this->add(color);
	}

	/**
	 * Operator -= scalar
	 * @param scalar scalar
	 * @returns this color
	 */
	inline Color4& operator -=(const float scalar) {
		return this->sub(scalar);
	}

	/**
	 * Operator -= color
	 * @param color color
	 * @returns this color
	 */
	inline Color4& operator -=(const Color4& color) {
		return this->sub(color);
	}

	/**
	 * Operator *= scalar
	 * @param scalar scalar
	 * @returns this color
	 */
	inline Color4& operator *=(const float scalar) {
		return this->scale(scalar);
	}

	/**
	 * Operator *= color
	 * @param color color
	 * @returns this color
	 */
	inline Color4& operator *=(const Color4& color) {
		return this->scale(color);
	}

	/**
	 * Operator /= scalar
	 * @param scalar scalar
	 * @returns this color
	 */
	inline Color4& operator /=(const float scalar) {
		auto vInverted = Color4(1.0f / scalar, 1.0f / scalar, 1.0f / scalar, 1.0f / scalar);
		return this->scale(vInverted);
	}

	/**
	 * Operator /= color
	 * @param color color
	 * @returns this color
	 */
	inline Color4& operator /=(const Color4& color) {
		auto vInverted = Color4(1.0f / color[0], 1.0f / color[1], 1.0f / color[2], 1.0f / color[3]);
		return this->scale(vInverted);
	}

	/**
	 * Equality comparison operator
	 * @param color color
	 * @returns equality
	 */
	inline bool operator ==(const Color4& color) const {
		return this->equals(color);
	}

	/**
	 * Non equality comparison operator
	 * @param color color
	 * @returns non equality
	 */
	inline bool operator !=(const Color4& color) const {
		return this->equals(color) == false;
	}

};
