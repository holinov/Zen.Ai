#pragma once
/* Standart include file */
#include <iostream>
#include <string>
#include <vector>
#include <map>

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
	HasId(IdType id): _id(id) {};
	inline const IdType id(){ return _id; }
	inline void id(IdType id) { _id=id; }
};

class HasName {
private:
	std::string _name;
public:
	HasName() {};
	HasName(std::string name): _name(name) {};
	inline const std::string name(){ return _name; }
	inline void name(std::string name) { _name=name; }
};