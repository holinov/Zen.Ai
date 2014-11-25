#pragma once
/* Standart include file */
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "log.h"

#ifdef WIN_PATH
	const char cPathSeparator = '\\';
#else
	const char cPathSeparator = '/';
#endif

typedef unsigned long IdType;

class HasId {
private:
	IdType _id;
public:
	HasId() {};
	HasId(const IdType id): _id(id) {};
	inline const IdType id() const { return _id; }
	inline void id(const IdType id) { _id=id; }
};

class HasName {
private:
	std::string _name;
public:
	HasName() {};
	HasName(std::string name): _name(name) {};
	inline const std::string name() const { return _name; }
	inline void name(const std::string name) { _name=name; }
};