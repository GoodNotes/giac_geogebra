#include "GenBridge.hpp"
#include "giac.h"
#include "GiacBridgeMutex.hpp"
#include "vecteur.h"
#include <pthread.h>
#include <sstream>
#include <stdexcept>

bool GenBridge::checkAndClearIdentifierCorruption(string& outLastPointerHex) {
	GiacBridgeLock lock;
	bool detected = giac::giac_identifier_corruption_detected;
	const void * lastPointer = giac::giac_identifier_corruption_last_pointer;
	giac::giac_identifier_corruption_detected = false;
	giac::giac_identifier_corruption_last_pointer = nullptr;
	if (detected) {
		std::ostringstream oss;
		oss << lastPointer;
		outLastPointerHex = oss.str();
	}
	return detected;
}

GenBridge::GenBridge(string expression, ContextBridge& context) {
	GiacBridgeLock lock;
	g = new giac::gen(expression, context.c);
}

GenBridge::GenBridge(giac::gen* g) {
	GiacBridgeLock lock;
	this->g = g;
}

GenBridge::~GenBridge() {
	GiacBridgeLock lock;
	delete g;
}

void GenBridge::resetTimeout() {
	GiacBridgeLock lock;
	g->resetTimeout();
}

void GenBridge::selfEval(int level, ContextBridge& context) {
	GiacBridgeLock lock;
	try {
		giac::gen* newg = new giac::gen(g->eval(level, context.c));
		delete g;
		g = newg;
	} catch (...) {
		throw "Error in selfEval: giac::gen::eval() failed";
	}
}

GenBridge* GenBridge::eval(int level, ContextBridge& context) {
	GiacBridgeLock lock;
	GenBridge* pointer = nullptr;
	auto evalptr = g->eval(level, context.c);
	auto giacptr = new giac::gen(evalptr);
	pointer = new GenBridge(giacptr);
	return pointer;
}

string GenBridge::print(ContextBridge& context) {
	GiacBridgeLock lock;
	string result = g->print(context.c);
	return result;
}

GenBridge* GenBridge::lname(ContextBridge& context) {
	GiacBridgeLock lock;
	GenBridge* pointer = nullptr;
	pointer = new GenBridge(new giac::gen("lname(" + g->print(context.c) + ")", context.c));
	pointer->selfEval(1, context);
	return pointer;
}

int GenBridge::type() {
	GiacBridgeLock lock;
	int result = g->type;
	return result;
}

int GenBridge::lenght() {
	GiacBridgeLock lock;
	int result;
	if (g->type == 7) { // type is vector
		giac::vecteur* v = g->_VECTptr;
		result = v->size();
	} else {
		result = 1;
	}
	return result;
}

int GenBridge::isNull() {
	GiacBridgeLock lock;
	int result = (g) ? 0 : 1;
	return result;
}

void GenBridge::getListVector(vector<GenBridge*>& list) {
	GiacBridgeLock lock;
	if (g->type == 7) { // type is vector
		giac::vecteur* v = g->_VECTptr;
		for (int i = 0; i < v->size(); i++) {
			list.push_back(new GenBridge(new giac::gen(v->at(i))));
		}
	} else {
		throw "Error in getListVector: type is not vector";
	}
}

int GenBridge::equalSign(GenBridge& other) {
	GiacBridgeLock lock;
	int result = *g == *other.g;
	return result;
}

GenBridge* GenBridge::left(ContextBridge& context) {
	GiacBridgeLock lock;
	GenBridge* pointer = nullptr;
	pointer = new GenBridge(new giac::gen("left(" + g->print(context.c) + ")", context.c));
	pointer->selfEval(1, context);
	return pointer;
}

GenBridge* GenBridge::right(ContextBridge& context) {
	GiacBridgeLock lock;
	GenBridge* pointer = nullptr;
	pointer = new GenBridge(new giac::gen("right(" + g->print(context.c) + ")", context.c));
	pointer->selfEval(1, context);
	return pointer;
}

GenBridge* GenBridge::canonicalForm(ContextBridge& context) {
	GiacBridgeLock lock;
	GenBridge* pointer = nullptr;
	pointer = new GenBridge(new giac::gen("canonical_form(" + g->print(context.c) + ")", context.c));
	pointer->selfEval(1, context);
	return pointer;
}

GenBridge* GenBridge::regroup(ContextBridge& context) {
	GiacBridgeLock lock;
	GenBridge* pointer = nullptr;
	pointer = new GenBridge(new giac::gen("regroup(" + g->print(context.c) + ")", context.c));
	pointer->selfEval(1, context);
	return pointer;
}

GenBridge* GenBridge::simplify(ContextBridge& context) {
	GiacBridgeLock lock;
	GenBridge* pointer = nullptr;
	pointer = new GenBridge(new giac::gen("simplify(" + g->print(context.c) + ")", context.c));
	pointer->selfEval(1, context);
	return pointer;
}

GenBridge* GenBridge::operator+(GenBridge& other) {
	GiacBridgeLock lock;
	GenBridge* result = nullptr;
	result = new GenBridge(new giac::gen(*g + *other.g));
	return result;
}

GenBridge* GenBridge::operator-(GenBridge& other) {
	GiacBridgeLock lock;
	GenBridge* result = nullptr;
	result = new GenBridge(new giac::gen(*g - *other.g));
	return result;
}

GenBridge* GenBridge::operator*(GenBridge& other) {
	GiacBridgeLock lock;
	GenBridge* result = nullptr;
	result = new GenBridge(new giac::gen(*g * *other.g));
	return result;
}

GenBridge* GenBridge::operator/(GenBridge& other) {
	GiacBridgeLock lock;
	GenBridge* result = nullptr;
	result = new GenBridge(new giac::gen(*g / *other.g));
	return result;
}

GenBridge* GenBridge::operator-() {
	GiacBridgeLock lock;
	GenBridge* result = nullptr;
	result = new GenBridge(new giac::gen(-*g));
	return result;
}
