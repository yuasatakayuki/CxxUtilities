/*
 * Parameters.hh
 *
 *  Created on: Dec 25, 2013
 *      Author: yuasa
 */

#ifndef PARAMETERS_HH_
#define PARAMETERS_HH_

#include "../Exception.hh"

namespace CxxUtilities {
class ParameterType {
public:
	enum Type {
		IntegerUnsigned8bit, //
		IntegerUnsigned16bit, //
		IntegerUnsigned32bit, //
		IntegerUnsigned64bit, //
		IntegerSigned8bit, //
		IntegerSigned16bit, //
		IntegerSigned32bit, //
		IntegerSigned64bit, //
		Float, //
		Double, //
		String, //
		Array, //
		Map //
	};

public:
	static std::string toString(ParameterType::Type type) {
		std::string result;
		switch (type) {
		case IntegerUnsigned8bit:
			result = "IntegerUnsigned8bit";
			break;
		case IntegerUnsigned16bit:
			result = "IntegerUnsigned16bit";
			break;
		case IntegerUnsigned32bit:
			result = "IntegerUnsigned32bit";
			break;
		case IntegerUnsigned64bit:
			result = "IntegerUnsigned64bit";
			break;
		case IntegerSigned8bit:
			result = "IntegerSigned8bit";
			break;
		case IntegerSigned16bit:
			result = "IntegerSigned16bit";
			break;
		case IntegerSigned32bit:
			result = "IntegerSigned32bit";
			break;
		case IntegerSigned64bit:
			result = "IntegerSigned64bit";
			break;
		case Float:
			result = "Float";
			break;
		case Double:
			result = "Double";
			break;
		case String:
			result = "String";
			break;
		case Array:
			result = "Array";
			break;
		case Map:
			result = "Map";
			break;

		default:
			result = "Undefined status";
			break;
		}
		return result;
	}
};

class ParameterException: public CxxUtilities::Exception {
public:
	enum {
		UndefinedParameterWasAccessed, //
		TypeMismatch //
	};

public:

};

class Parameter {
public:
	std::string name;
	ParameterType::Type type;
	void* variable;

public:
	Parameter(std::string name, ParameterType::Type type, void* variable) {
		this->name = name;
		this->type = type;
		this->variable = variable;
	}

public:
	void setUnsignedInteger8bit(uint8_t value) {
		*((uint8_t*) variable) = value;
	}
	void setUnsignedInteger16bit(uint16_t value) {
		*((uint16_t*) variable) = value;
	}
	void setUnsignedInteger32bit(uint32_t value) {
		*((uint32_t*) variable) = value;
	}
	void setUnsignedInteger64bit(uint64_t value) {
		*((uint64_t*) variable) = value;
	}

public:
	void setSignedInteger8bit(int8_t value) {
		*((int8_t*) variable) = value;
	}
	void setSignedInteger16bit(int16_t value) {
		*((int16_t*) variable) = value;
	}
	void setSignedInteger32bit(int32_t value) {
		*((int32_t*) variable) = value;
	}
	void setSignedInteger64bit(int64_t value) {
		*((int64_t*) variable) = value;
	}

public:
	void setFloat(float value) {
		*((float*) variable) = value;
	}
	void setDouble(double value) {
		*((double*) variable) = value;
	}

public:
	void setString(std::string str) {
		*((std::string*) variable) = str;
	}

public:
	void setArray(const std::vector<Parameter*> array) {
		*((std::vector<Parameter*>*) variable) = array;
	}

public:
	void setArray(const std::vector<Parameter*>* array) {
		*((std::vector<Parameter*>*) variable) = *array;
	}

public:
	void setMap(std::map<std::string, Parameter*> map) {
		*((std::map<std::string, Parameter*>*) variable) = map;
	}

public:
	void setMap(std::map<std::string, Parameter*>* map) {
		*((std::map<std::string, Parameter*>*) variable) = *map;
	}

public:
	uint8_t getAsUnsignedInteger8bit() {
		return *((uint8_t*) variable);
	}
	uint16_t getAsUnsignedInteger16bit() {
		return *((uint16_t*) variable);
	}
	uint32_t getAsUnsignedInteger32bit() {
		return *((uint32_t*) variable);
	}
	uint64_t getAsUnsignedInteger64bit() {
		return *((uint64_t*) variable);
	}

public:
	uint8_t getAsSignedInteger8bit() {
		return *((int8_t*) variable);
	}
	uint16_t getAsSignedInteger16bit() {
		return *((int16_t*) variable);
	}
	uint32_t getAsSignedInteger32bit() {
		return *((int32_t*) variable);
	}
	uint64_t getAsSignedInteger64bit() {
		return *((int64_t*) variable);
	}

public:
	float getAsFloat() {
		return *((float*) variable);
	}
	double getAsDouble() {
		return *((double*) variable);
	}

public:
	std::string getAsString() {
		return *((std::string*) variable);
	}

public:
	std::vector<Parameter*> getAsArray() {
		return *((std::vector<Parameter*>*) variable);
	}

public:
	std::map<std::string, Parameter*> getAsMap() {
		return *((std::map<std::string, Parameter*>*) variable);
	}

};

class Parameters {
private:
	std::map<std::string, Parameter*> parameterMap;

public:
	Parameters() {
	}

public:
	virtual ~Parameters() {
		std::map<std::string, Parameter*>::iterator it = parameterMap.begin();
		while (it != parameterMap.end()) {
			delete it->second;
			it++;
		}
	}

public:
	void define(std::string parameterName, uint8_t* variable) {
		Parameter* parameter = new Parameter(parameterName, ParameterType::IntegerUnsigned8bit, (void*) variable);
		parameterMap[parameterName] = parameter;
	}

public:
	void define(std::string parameterName, uint16_t* variable) {
		Parameter* parameter = new Parameter(parameterName, ParameterType::IntegerUnsigned16bit, (void*) variable);
		parameterMap[parameterName] = parameter;
	}

public:
	void define(std::string parameterName, uint32_t* variable) {
		Parameter* parameter = new Parameter(parameterName, ParameterType::IntegerUnsigned32bit, (void*) variable);
		parameterMap[parameterName] = parameter;
	}

public:
	void define(std::string parameterName, uint64_t* variable) {
		Parameter* parameter = new Parameter(parameterName, ParameterType::IntegerUnsigned64bit, (void*) variable);
		parameterMap[parameterName] = parameter;
	}

public:
	void define(std::string parameterName, int8_t* variable) {
		Parameter* parameter = new Parameter(parameterName, ParameterType::IntegerSigned8bit, (void*) variable);
		parameterMap[parameterName] = parameter;
	}

public:
	void define(std::string parameterName, int16_t* variable) {
		Parameter* parameter = new Parameter(parameterName, ParameterType::IntegerSigned16bit, (void*) variable);
		parameterMap[parameterName] = parameter;
	}

public:
	void define(std::string parameterName, int32_t* variable) {
		Parameter* parameter = new Parameter(parameterName, ParameterType::IntegerSigned32bit, (void*) variable);
		parameterMap[parameterName] = parameter;
	}

public:
	void define(std::string parameterName, float* variable) {
		Parameter* parameter = new Parameter(parameterName, ParameterType::Float, (void*) variable);
		parameterMap[parameterName] = parameter;
	}

public:
	void define(std::string parameterName, double* variable) {
		Parameter* parameter = new Parameter(parameterName, ParameterType::Double, (void*) variable);
		parameterMap[parameterName] = parameter;
	}

public:
	void define(std::string parameterName, int64_t* variable) {
		Parameter* parameter = new Parameter(parameterName, ParameterType::IntegerSigned64bit, (void*) variable);
		parameterMap[parameterName] = parameter;
	}

public:
	void define(std::string parameterName, std::string* variable) {
		Parameter* parameter = new Parameter(parameterName, ParameterType::String, (void*) variable);
		parameterMap[parameterName] = parameter;
	}

public:
	void define(std::string parameterName, std::vector<Parameter*>* variable) {
		Parameter* parameter = new Parameter(parameterName, ParameterType::Array, (void*) variable);
		parameterMap[parameterName] = parameter;
	}

public:
	void define(std::string parameterName, std::map<std::string, Parameter*> variable) {
		Parameter* parameter = new Parameter(parameterName, ParameterType::Map, (void*) variable);
		parameterMap[parameterName] = parameter;
	}

public:
	ParameterType::Type getParamterType(std::string parameterName) throw (ParameterException) {
		if (parameterMap.find(parameterName) != parameterMap.end()) {
			return parameterMap[parameterName]->type;
		} else {
			throw ParameterException(ParameterException::UndefinedParameterWasAccessed);
		}
	}

public:
	bool isDefined(std::string parameterName) {
		if (parameterMap.find(parameterName) != parameterMap.end()) {
			return true;
		} else {
			return false;
		}
	}

public:
	template<typename T>
	T as(std::string parameterName) throw (ParameterException) {
		ParameterType::Type type = getParamterType(parameterName);
		switch (type) {
		case ParameterType::IntegerUnsigned8bit:
			return asIntegerUnsigned8bit(parameterName);
			break;
		case ParameterType::IntegerUnsigned16bit:
			return asIntegerUnsigned16bit(parameterName);
			break;
		case ParameterType::IntegerUnsigned32bit:
			return asIntegerUnsigned32bitparameterName);
			break;
		case ParameterType::IntegerUnsigned64bit:
			return asIntegerUnsigned64bit(parameterName);
			break;
		case ParameterType::IntegerSigned8bit:
			return asIntegerSigned8bit(parameterName);
			break;
		case ParameterType::IntegerSigned16bit:
			return asIntegerSigned16bit(parameterName);
			break;
		case ParameterType::IntegerSigned32bit:
			return asIntegerSigned32bit(parameterName);
			break;
		case ParameterType::IntegerSigned64bit:
			return asIntegerSigned64bit(parameterName);
			break;
		case ParameterType::Float:
			return asFloat(parameterName);
			break;
		case ParameterType::Double:
			return asDouble(parameterName);
			break;
		case ParameterType::String:
			return asString(parameterName);
			break;
		case ParameterType::Array:
			return asArray(parameterName);
			break;
		case ParameterType::Map:
			return asMap(parameterName);
			break;
		default:
			throw ParameterException(ParameterException::UndefinedParameterWasAccessed);
			break;
		}
	}

public:
	uint8_t asIntegerUnsigned8bit(std::string parameterName) {
		switch (type) {
		case ParameterType::IntegerUnsigned8bit:
			return asIntegerUnsigned8bit(parameterName);
			break;
		case ParameterType::IntegerUnsigned16bit:
			return asIntegerUnsigned16bit(parameterName);
			break;
		case ParameterType::IntegerUnsigned32bit:
			return asIntegerUnsigned32bitparameterName);
			break;
		case ParameterType::IntegerUnsigned64bit:
			return asIntegerUnsigned64bit(parameterName);
			break;
		case ParameterType::IntegerSigned8bit:
			return asIntegerSigned8bit(parameterName);
			break;
		case ParameterType::IntegerSigned16bit:
			return asIntegerSigned16bit(parameterName);
			break;
		case ParameterType::IntegerSigned32bit:
			return asIntegerSigned32bit(parameterName);
			break;
		case ParameterType::IntegerSigned64bit:
			return asIntegerSigned64bit(parameterName);
			break;
		case ParameterType::Float:
			return asFloat(parameterName);
			break;
		case ParameterType::Double:
			return asDouble(parameterName);
			break;
		case ParameterType::String:
			return asString(parameterName);
			break;
		case ParameterType::Array:
			return asArray(parameterName);
			break;
		case ParameterType::Map:
			return asMap(parameterName);
			break;
		default:
			throw ParameterException(ParameterException::UndefinedParameterWasAccessed);
			break;
		}
	}
}
;
}

#endif /* PARAMETERS_HH_ */
