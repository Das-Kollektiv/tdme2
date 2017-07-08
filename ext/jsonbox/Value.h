/**
 * @version $Id: d52ccf08d9542823c30a8e3a3b0d0e157ca2d975 $
 */

#pragma once

#include <string>
#include <iostream>

#include "JsonException.h"

namespace tdme {
namespace ext {
namespace jsonbox {

class Array;
class Object;

/**
 * Represents a json value. Can be a string, an integer, a floating point
 * number, an object, an array, a boolean value or a null value. To put it
 * simply, it acts a lot like a variant. Objects are actually a map of
 * strings and values while an array is a deque of values.
 * The user doesn't have to worry about character escaping in strings,
 * the i/o algorithms take care of that for the user.
 * @see TDMEJson::Array
 * @see TDMEJson::Object
 */
class Value {
	/**
	 * Output operator overload. Outputs the value as valid JSON. Does not
	 * do any indentation.
	 * @param output Output stream in which the valid JSON is written.
	 * @param v Value to be output in the stream.
	 * @return Output parameter with the valud json written into it.
	 */
	friend std::ostream &operator<<(std::ostream &output, const Value &v);
public:
	/**
	 * Represents the different types a value can be. A value can only be
	 * one of these types at a time. The UNKNOWN type is only used
	 * temporarily internally when loading values from an input stream or
	 * file.
	 */
	enum Type {
		STRING,
		INTEGER,
		DOUBLE,
		OBJECT,
		ARRAY,
		BOOLEAN,
		NULL_VALUE,
		UNKNOWN
	};

	/**
	 * Replaces characters with their JSON equivalent. The only difference
	 * from escapeAllCharacters is that the solidi won't be escaped in this
	 * method.
	 * @param str String to have its characters escaped.
	 * @return Copy of the recieved string, but with the concerned
	 * characters escaped.
	 * @see TDMEJson::Value::escapeAllCharacters(const std::string& str)
	 */
	static std::string escapeMinimumCharacters(const std::string &str);

	/**
	 * Replaces characters with its JSON equivalent for escape characters.
	 * So for example, if in the string there is the newline character '\n',
	 * it will be replaced by the two characters '\' and 'n'.
	 * @param str String make a copy and have its characters escaped.
	 * @return Copy of the recieved string, but with the concerned
	 * characters escaped.
	 * @see TDMEJson::Value::escapeMinimumCharacters(const std::string& str)
	 */
	static std::string escapeAllCharacters(const std::string &str);

	/**
	 * Escapes a character to its unicode equivalent. This function only
	 * takes characters from '/0' to '/x1f'.
	 * @param charToEscape Character to escape, must be between '\0' and
	 * '\x1f'.
	 * @return String with the character escaped in the format "\u00xx".
	 * "xx" being the hexadecimal ASCII code of the character escaped.
	 */
	static const std::string escapeToUnicode(char charToEscape);

	/**
	 * Default constructor. Makes the value null.
	 */
	Value();

	/**
	 * Loads the value from an input stream. If there is more than one value
	 * in the input stream, they are ignored. Only the first value is read.
	 * @param input Input stream to load the value from. Can also be an
	 * input file stream.
	 */
	Value(std::istream &input);

	/**
	 * Constructs the value from a string.
	 * @param newString String used as the value.
	 */
	Value(const std::string &newString);

	/**
	 * Constructs the value from a C-style string.
	 * @param newCString C-style string used as the value.
	 */
	Value(const char *newCString);

	/**
	 * Constructs the value from an integer.
	 * @param newInt Integer used as the value.
	 */
	Value(int newInt);

	/**
	 * Constructs the value from a double.
	 * @param newDouble Double used as the value.
	 */
	Value(double newDouble);

	/**
	 * Constructs the value from an object.
	 * @param newObject Object used as the value.
	 */
	Value(const Object &newObject);

	/**
	 * Constructs the value from an array.
	 * @param newArray Array used as the value.
	 */
	Value(const Array &newArray);

	/**
	 * Constructs the value from a boolean.
	 * @param newBoolean Boolean used as the value.
	 */
	Value(bool newBoolean);

	/**
	 * Copy constructor.
	 * @param src Value to make a copy of.
	 */
	Value(const Value &src);

	/**
	 * Destructor. Frees up the memory used by the value's allocated
	 * pointers.
	 */
	~Value();

	/**
	 * Assignation operator overload.
	 * @param src Value to copy.
	 * @return Reference to the modified value.
	 */
	Value &operator=(const Value &src);

	/**
	 * Checks if the current value is equal to the right hand side value.
	 * @param rhs Right hand side value to check for equality with.
	 * @return True if the contents of the two values are equal, false if
	 * not.
	 */
	bool operator==(const Value &rhs) const;

	/**
	 * Checks if the current value is different from the right hand side
	 * value.
	 * @param rhs Right hand side value to check for not equality with.
	 * @return True if the contents of the two values are different, false
	 * if not.
	 */
	bool operator!=(const Value &rhs) const;

	/**
	 * Checks if the contents of instance are lexicographically less than
	 * the contents of the right hand side value.
	 * @param rhs Right hand side value to check.
	 * @return True if the contents of of the instance are lexicographically
	 * less than the contents of the right hand side value.
	 */
	bool operator <(const Value &rhs) const;

	/**
	 * Checks if the contents of instance are lexicographically less than or
	 * equal the contents of the right hand side value.
	 * @param rhs Right hand side value to check.
	 * @return True if the contents of of the instance are lexicographically
	 * less than or equal the contents of the right hand side value.
	 */
	bool operator <=(const Value &rhs) const;

	/**
	 * Checks if the contents of instance are lexicographically greater than
	 * the contents of the right hand side value.
	 * @param rhs Right hand side value to check.
	 * @return True if the contents of of the instance are lexicographically
	 * greater than the contents of the right hand side value.
	 */
	bool operator >(const Value &rhs) const;

	/**
	 * Checks if the contents of instance are lexicographically greater than
	 * or equal the contents of the right hand side value.
	 * @param rhs Right hand side value to check.
	 * @return True if the contents of of the instance are lexicographically
	 * greater than or equal the contents of the right hand side value.
	 */
	bool operator >=(const Value &rhs) const;

	/**
	 * Bracket operator overload. If the value doesn't represent an object,
	 * it is changed to do so and accesses the object's member value. If
	 * the object's member doesn't exist, it is created.
	 * @param key Key identifier of the object's value to get.
	 * @throws JsonException if type is not an object
	 * @return Reference to the object's member's value.
	 */
	Value &operator[](const std::string &key) throw (JsonException);

	/**
	 * Bracket operator overload. If the value doesn't represent an object,
	 * it is changed to do so and accesses the object's member value. If
	 * the object's member doesn't exist, it is created.
	 * @param key Key identifier of the object's value to get.
	 * @throws JsonException if type is not an object
	 * @return Reference to the object's member's value.
	 */
	Value &operator[](const char *key) throw (JsonException);

	/**
	 * Bracket operator overload. If the value doesn't represent an array,
	 * it is changed to do so and accesses the array's value at the
	 * specified index. To make sure the index value exists when it creates
	 * the array, it initializes the array with empty values up to the
	 * required index. If the value already represents an array and the
	 * index is too high for the size of the array, undefined behavior
	 * happens (no bounds checking is done).
	 * @param index Index of the value to get.
	 * @throws JsonException if type is not an array
	 * @return Reference to the value at the received index in the array.
	 */
	Value &operator[](size_t index) throw (JsonException);

	/**
	 * Gets the value's type.
	 * @return Value's type, does not return Type::UNKOWN, would return
	 * NULL_VALUE if no type has been given to the value yet.
	 * @see TDMEJson::Type
	 */
	Type getType() const;

	/**
	 * Checks if the value is a string.
	 * @return True if the value contains a string, false if not.
	 */
	bool isString() const;
	/**
	 * Checks if the value is an integer.
	 * @return True if the value contains an integer, false if not.
	 */
	bool isInteger() const;

	/**
	 * Checks if the value is a double.
	 * @return True if the value contains a double, false if not.
	 */
	bool isDouble() const;

	/**
	 * Checks if the value is an object.
	 * @return True if the value contains an object, false if not.
	 */
	bool isObject() const;

	/**
	 * Checks if the value is an array.
	 * @return True if the value contains an array, false if not.
	 */
	bool isArray() const;

	/**
	 * Checks if the value is a boolean.
	 * @return True if the value contains a boolean, false if not.
	 */
	bool isBoolean() const;

	/**
	 * Checks if the value is null.
	 * @return True if the value contains nothing.
	 */
	bool isNull() const;

	/**
	 * Gets the value's string value.
	 * @throws JsonException if type does not match
	 * @return Value's string value
	 * contain a string.
	 */
	const std::string &getString() const throw (JsonException);

	/**
	 * Sets the value as a string.
	 * @param newString New string value that the Value will contain. If the
	 * value's type is changed if necessary to contain the integer.
	 */
	void setString(const std::string &newString);

	/**
	 * Gets the value's integer value.
	 * @throws JsonException if type does not match
	 * @return Value's integer value
	 * integer.
	 */
	int getInt() const throw (JsonException);

	/**
	 * Sets the value as an integer.
	 * @param newInt New integer value that the Value will contain. The
	 * value's type is changed if necessary to contain the integer.
	 */
	void setInt(int newInt);

	/**
	 * Gets the value's double value.
	 * @throws JsonException if type does not match
	 * @return Value's double value
	 * double.
	 */
	double getDouble() const throw (JsonException);

	/**
	 * Sets the value as a double.
	 * @param newDouble New double value that the Value will contain. The
	 * value's type is changed if necessary to contain the double.
	 */
	void setDouble(double newDouble);

	/**
	 * Gets the value's object value.
	 * @throws JsonException if type does not match
	 * @return Value's object value
	 * contain an object.
	 */
	const Object &getObject() const throw (JsonException);

	/**
	 * Sets the value as a JSON object.
	 * @param newObject New object value that the Value will contain. The
	 * value's type is changed if necessary to contain the object.
	 */
	void setObject(const Object &newObject);

	/**
	 * Gets the value's array value.
	 * @throws JsonException if type does not match
	 * @return Value's array value
	 * contain an array.
	 */
	const Array &getArray() const throw (JsonException);

	/**
	 * Sets the value as a JSON array.
	 * @param newArray New array value that the Value will contain. The
	 * value's type is changed if necessary to contain the array.
	 */
	void setArray(const Array &newArray);

	/**
	 * Gets the value's boolean value.
	 * @throws JsonException if type does not match
	 * @return Value's boolean value
	 * a boolean.
	 */
	bool getBoolean() const throw (JsonException);

	/**
	 * Sets the value as a boolean.
	 * @param newBoolean New boolean value that the Value will contain. The
	 * value's type is changed if necessary to contain the boolean.
	 */
	void setBoolean(bool newBoolean);

	/**
	 * Sets the value as a null value.
	 */
	void setNull();

	/**
	 * Loads the current value from a string containing the JSON to parse.
	 * @param json String containing the JSON to parse.
	 */
	void loadFromString(const std::string &json);

	/**
	 * Loads a Value from a stream containing valid JSON in UTF-8. Does not
	 * read the stream if it is in UTF-32 or UTF-16. All the json escape
	 * sequences in string values are converted to their char equivalent,
	 * including unicode characters. Unicode characters that use two "\u"
	 * sequences are interpreted as two unicode characters, so it doesn't
	 * support perfect parsing.
	 * @param input Input stream to read from. Can be a file stream.
	 * @throws JsonException
	 */
	void loadFromStream(std::istream &input) throw (JsonException);

	/**
	 * Loads a value from a file. Loads the file then calls the
	 * loadFromStream(...) method.
	 * @param filePath Path to the JSON file to load.
	 * @throws JsonException
	 * @see TDMEJson::Value::loadFromStream
	 */
	void loadFromFile(const std::string &filePath) throw (JsonException);

	/**
	 * Writes the value to an output stream in valid JSON. Uses the
	 * overloaded output operator.
	 * @param output Output stream to write the value to.
	 * @param indent Specifies if the output is to have nice indentation or
	 * not.
	 * @param escapeAll Specifies if all the JSON escapable characters
	 * should be escaped or not.
	 * @see TDMEJson::Value::operator<<(std::ostream& output, const Value& v)
	 * @see TDMEJson::Value::escapeAllCharacters
	 * @see TDMEJson::Value::escapeMinimumCharacters
	 */
	void writeToStream(std::ostream &output, bool indent = true,
					   bool escapeAll = false) const;

	/**
	 * Writes the value to a JSON file. Uses writeToStream(...).
	 * @param filePath Path to the file to write.
	 * @param indent Specifies if the output is to have nice indentation or
	 * not.
	 * @param escapeAll Specifies if all the JSON escapable characters
	 * should be escaped or not.
	 * @see TDMEJson::Value::writeToStream
	 */
	void writeToFile(const std::string &filePath, bool indent = true,
					 bool escapeAll = false) const throw (JsonException);
private:
	/**
	 * Union used to contain the pointer to the value's data.
	 */
	union ValueDataPointer {
		std::string *stringValue;
		int *intValue;
		double *doubleValue;
		Object *objectValue;
		Array *arrayValue;
		bool *boolValue;

		/**
		 * Default constructor. Puts the pointers at NULL.
		 */
		ValueDataPointer();

		/**
		 * Parameterized constructor.
		 * @param newConstStringValue Pointer to set to the string pointer.
		 */
		ValueDataPointer(std::string *newStringValue);

		/**
		 * Parameterized constructor.
		 * @param newConstIntValue Pointer to set to the int pointer.
		 */
		ValueDataPointer(int *newIntValue);

		/**
		 * Parameterized constructor.
		 * @param newConstDoubleValue Pointer to set to the double pointer.
		 */
		ValueDataPointer(double *newDoubleValue);

		/**
		 * Parameterized constructor.
		 * @param newConstObjectValue Pointer to set to the object pointer.
		 */
		ValueDataPointer(Object *newObjectValue);

		/**
		 * Parameterized constructor.
		 * @param newConstArrayValue Pointer to set to the array pointer.
		 */
		ValueDataPointer(Array *newArrayValue);

		/**
		 * Parameterized constructor.
		 * @param newConstBoolValue Pointer to set to the bool pointer.
		 */
		ValueDataPointer(bool *newBoolValue);
	};

	/**
	 * Empty string returned by getString() when the value doesn't contain a
	 * string.
	 * @see TDMEJson::Value::getString
	 */
	static const std::string EMPTY_STRING;

	/**
	 * Default int value returned by getInt() when the value doesn't contain
	 * an integer.
	 * @see TDMEJson::Value::getInt
	 */
	static const int EMPTY_INT = 0;

	/**
	 * Default double value returned by getDouble() when the value doesn't
	 * contain a double.
	 * @see TDMEJson::Value::getDouble
	 */
	static const double EMPTY_DOUBLE;

	/**
	 * Default empty object value returned by getObject() when the value
	 * doesn't contain an object.
	 * @see TDMEJson::Value::getObject
	 */
	static const Object EMPTY_OBJECT;

	/**
	 * Default empty array value returned by getArray() when the value
	 * doesn't contain an array.
	 * @see TDMEJson::Value::getArray
	 */
	static const Array EMPTY_ARRAY;

	/**
	 * Default boolean value returned by getBoolean() when the value doesn't
	 * contain a boolean.
	 * @see TDMEJson::Value::getBoolean
	 */
	static const bool EMPTY_BOOL = false;

	/**
	 * Checks if the char given is a hex digit.
	 * @return True if the char contains an hexadecimal digit (0-9, a-f or
	 * A-F).
	 */
	static bool isHexDigit(char digit);

	/**
	 * Checks if the char given is a JSON whitespace.
	 * @return True if the char is either a space, a horizontal tab, a line
	 * feed or a carriage return.
	 */
	static bool isWhiteSpace(char whiteSpace);

	/**
	 * Reads a JSON string from an input stream.
	 * @param input Input stream to read the string value from.
	 * @param result UTF-8 string read from the input stream.
	 * @throws JsonException
	 */
	static void readString(std::istream &input, std::string &result) throw (JsonException);

	/**
	 * Reads a JSON object from an input stream.
	 * @param input Input stream to read the object from.
	 * @param result Object read from the input stream.
	 * @throws JsonException
	 */
	static void readObject(std::istream &input, Object &result) throw (JsonException);

	/**
	 * Reads a JSON array from an input stream.
	 * @param input Input stream to read the array from.
	 * @param result Array read from the input stream.
	 */
	static void readArray(std::istream &input, Array &result);

	/**
	 * Reads a JSON number from an input stream.
	 * @param input Input stream to read the array from.
	 * @param result Value containing the integer or the double read from
	 * the input stream.
	 * @throws JsonExceptioon
	 */
	static void readNumber(std::istream &input, Value &result) throw (JsonException);

	/**
	 * Advances through the input stream until it reaches a character that
	 * is not a whitespace.
	 * @param input Input stream to read the whitespace characters from.
	 * @param currentCharacter Char in which each character read is
	 * temporarily stored. After the method is called, this char contains
	 * the first non white space character reached.
	 */
	static void readToNonWhiteSpace(std::istream &input,
									char &currentCharacter);

	/**
	 * Frees up the dynamic memory allocated by the value.
	 */
	void clear();

	/**
	 * Outputs the value in JSON format.
	 * @param output Output stream used to output the value in JSON format.
	 * @param indent Specifies if the JSON being output must be indented or
	 * not. False is to output the JSON in compact format.
	 * @param escapeAll Specifies if the strings must escape all characters
	 * or only the minimum.
	 * @see TDMEJson::Value::escapeAllCharacters(const std::string str)
	 * @see TDMEJson::Value::escapeMinimumCharacters(const std::string str)
	 * @see TDMEJson::Value::output(std::ostream& output, unsigned int& level, bool indent, bool escapeAll)
	 */
	void output(std::ostream &output, bool indent = true,
				bool escapeAll = false) const;

	/**
	 * Type of data the value contains.
	 */
	Type type;

	/**
	 * Pointer to the Value's data.
	 */
	ValueDataPointer data;
};

};
};
};
