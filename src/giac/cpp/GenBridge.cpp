#include "GenBridge.hpp"
#include "giac.h"
#include "vecteur.h"
#include <pthread.h>
#include <stdexcept>


GenBridge::GenBridge(string expression, ContextBridge& context) {
#ifdef HAVE_LIBPTHREAD
	static pthread_mutex_t gen_mutex = PTHREAD_MUTEX_INITIALIZER;
	if (pthread_mutex_lock(&gen_mutex) != 0) {
		throw std::runtime_error("Failed to lock gen mutex");
	}
#endif
	try {
		g = new giac::gen(expression, context.c);
	} catch (...) {
#ifdef HAVE_LIBPTHREAD
		pthread_mutex_unlock(&gen_mutex);
#endif
		throw;
	}
#ifdef HAVE_LIBPTHREAD
	if (pthread_mutex_unlock(&gen_mutex) != 0) {
		throw std::runtime_error("Failed to unlock gen mutex");
	}
#endif
}

GenBridge::GenBridge(giac::gen* g) {
#ifdef HAVE_LIBPTHREAD
	static pthread_mutex_t gen_mutex = PTHREAD_MUTEX_INITIALIZER;
	if (pthread_mutex_lock(&gen_mutex) != 0) {
		throw std::runtime_error("Failed to lock gen mutex");
	}
#endif
	try {
		this->g = g;
	} catch (...) {
#ifdef HAVE_LIBPTHREAD
		pthread_mutex_unlock(&gen_mutex);
#endif
		throw;
	}
#ifdef HAVE_LIBPTHREAD
	if (pthread_mutex_unlock(&gen_mutex) != 0) {
		throw std::runtime_error("Failed to unlock gen mutex");
	}
#endif
}

GenBridge::~GenBridge() {
#ifdef HAVE_LIBPTHREAD
	static pthread_mutex_t gen_mutex = PTHREAD_MUTEX_INITIALIZER;
	if (pthread_mutex_lock(&gen_mutex) != 0) {
		throw std::runtime_error("Failed to lock gen mutex");
	}
#endif
	delete g;
#ifdef HAVE_LIBPTHREAD
	if (pthread_mutex_unlock(&gen_mutex) != 0) {
		throw std::runtime_error("Failed to unlock gen mutex");
	}
#endif
}

void GenBridge::resetTimeout() {
#ifdef HAVE_LIBPTHREAD
	static pthread_mutex_t gen_mutex = PTHREAD_MUTEX_INITIALIZER;
	if (pthread_mutex_lock(&gen_mutex) != 0) {
		throw std::runtime_error("Failed to lock gen mutex");
	}
#endif
	g->resetTimeout();
#ifdef HAVE_LIBPTHREAD
	if (pthread_mutex_unlock(&gen_mutex) != 0) {
		throw std::runtime_error("Failed to unlock gen mutex");
	}
#endif
}

void GenBridge::selfEval(int level, ContextBridge& context) {
#ifdef HAVE_LIBPTHREAD
	static pthread_mutex_t gen_mutex = PTHREAD_MUTEX_INITIALIZER;
	if (pthread_mutex_lock(&gen_mutex) != 0) {
		throw std::runtime_error("Failed to lock gen mutex");
	}
#endif
	try {
		giac::gen* newg = new giac::gen(g->eval(level, context.c));
		delete g;
		g = newg;
	} catch (...) {
#ifdef HAVE_LIBPTHREAD
		pthread_mutex_unlock(&gen_mutex);
#endif
		throw "Error in selfEval: giac::gen::eval() failed";
	}
#ifdef HAVE_LIBPTHREAD
	if (pthread_mutex_unlock(&gen_mutex) != 0) {
		throw std::runtime_error("Failed to unlock gen mutex");
	}
#endif
}

GenBridge* GenBridge::eval(int level, ContextBridge& context) {
#ifdef HAVE_LIBPTHREAD
	static pthread_mutex_t gen_mutex = PTHREAD_MUTEX_INITIALIZER;
	if (pthread_mutex_lock(&gen_mutex) != 0) {
		throw std::runtime_error("Failed to lock gen mutex");
	}
#endif
	GenBridge* pointer = nullptr;
	try {
		auto evalptr = g->eval(level, context.c);
		auto giacptr = new giac::gen(evalptr);
		pointer = new GenBridge(giacptr);
	} catch (...) {
#ifdef HAVE_LIBPTHREAD
		pthread_mutex_unlock(&gen_mutex);
#endif
		throw;
	}
#ifdef HAVE_LIBPTHREAD
	if (pthread_mutex_unlock(&gen_mutex) != 0) {
		throw std::runtime_error("Failed to unlock gen mutex");
	}
#endif
	return pointer;
}

string GenBridge::print(ContextBridge& context) {
#ifdef HAVE_LIBPTHREAD
	static pthread_mutex_t gen_mutex = PTHREAD_MUTEX_INITIALIZER;
	if (pthread_mutex_lock(&gen_mutex) != 0) {
		throw std::runtime_error("Failed to lock gen mutex");
	}
#endif
	string result = g->print(context.c);
#ifdef HAVE_LIBPTHREAD
	if (pthread_mutex_unlock(&gen_mutex) != 0) {
		throw std::runtime_error("Failed to unlock gen mutex");
	}
#endif
	return result;
}

GenBridge* GenBridge::lname(ContextBridge& context) {
#ifdef HAVE_LIBPTHREAD
	static pthread_mutex_t gen_mutex = PTHREAD_MUTEX_INITIALIZER;
	if (pthread_mutex_lock(&gen_mutex) != 0) {
		throw std::runtime_error("Failed to lock gen mutex");
	}
#endif
	GenBridge* pointer = nullptr;
	try {
		pointer = new GenBridge(new giac::gen("lname(" + g->print(context.c) + ")", context.c));
		pointer->selfEval(1, context);
	} catch (...) {
#ifdef HAVE_LIBPTHREAD
		pthread_mutex_unlock(&gen_mutex);
#endif
		throw;
	}
#ifdef HAVE_LIBPTHREAD
	if (pthread_mutex_unlock(&gen_mutex) != 0) {
		throw std::runtime_error("Failed to unlock gen mutex");
	}
#endif
	return pointer;
}

int GenBridge::type() {
#ifdef HAVE_LIBPTHREAD
	static pthread_mutex_t gen_mutex = PTHREAD_MUTEX_INITIALIZER;
	if (pthread_mutex_lock(&gen_mutex) != 0) {
		throw std::runtime_error("Failed to lock gen mutex");
	}
#endif
	int result = g->type;
#ifdef HAVE_LIBPTHREAD
	if (pthread_mutex_unlock(&gen_mutex) != 0) {
		throw std::runtime_error("Failed to unlock gen mutex");
	}
#endif
	return result;
}

int GenBridge::lenght() {
#ifdef HAVE_LIBPTHREAD
	static pthread_mutex_t gen_mutex = PTHREAD_MUTEX_INITIALIZER;
	if (pthread_mutex_lock(&gen_mutex) != 0) {
		throw std::runtime_error("Failed to lock gen mutex");
	}
#endif
	int result;
	if (g->type == 7) { // type is vector
		giac::vecteur* v = g->_VECTptr;
		result = v->size();
	} else {
		result = 1;
	}
#ifdef HAVE_LIBPTHREAD
	if (pthread_mutex_unlock(&gen_mutex) != 0) {
		throw std::runtime_error("Failed to unlock gen mutex");
	}
#endif
	return result;
}

int GenBridge::isNull() {
#ifdef HAVE_LIBPTHREAD
	static pthread_mutex_t gen_mutex = PTHREAD_MUTEX_INITIALIZER;
	if (pthread_mutex_lock(&gen_mutex) != 0) {
		throw std::runtime_error("Failed to lock gen mutex");
	}
#endif
	int result = (g) ? 0 : 1;
#ifdef HAVE_LIBPTHREAD
	if (pthread_mutex_unlock(&gen_mutex) != 0) {
		throw std::runtime_error("Failed to unlock gen mutex");
	}
#endif
	return result;
}

void GenBridge::getListVector(vector<GenBridge*>& list) {
#ifdef HAVE_LIBPTHREAD
	static pthread_mutex_t gen_mutex = PTHREAD_MUTEX_INITIALIZER;
	if (pthread_mutex_lock(&gen_mutex) != 0) {
		throw std::runtime_error("Failed to lock gen mutex");
	}
#endif
	try {
		if (g->type == 7) { // type is vector
			giac::vecteur* v = g->_VECTptr;
			for (int i = 0; i < v->size(); i++) {
				list.push_back(new GenBridge(new giac::gen(v->at(i))));
			}
		} else {
			throw "Error in getListVector: type is not vector";
		}
	} catch (...) {
#ifdef HAVE_LIBPTHREAD
		pthread_mutex_unlock(&gen_mutex);
#endif
		throw;
	}
#ifdef HAVE_LIBPTHREAD
	if (pthread_mutex_unlock(&gen_mutex) != 0) {
		throw std::runtime_error("Failed to unlock gen mutex");
	}
#endif
}

int GenBridge::equalSign(GenBridge& other) {
#ifdef HAVE_LIBPTHREAD
	static pthread_mutex_t gen_mutex = PTHREAD_MUTEX_INITIALIZER;
	if (pthread_mutex_lock(&gen_mutex) != 0) {
		throw std::runtime_error("Failed to lock gen mutex");
	}
#endif
	int result = *g == *other.g;
#ifdef HAVE_LIBPTHREAD
	if (pthread_mutex_unlock(&gen_mutex) != 0) {
		throw std::runtime_error("Failed to unlock gen mutex");
	}
#endif
	return result;
}

GenBridge* GenBridge::left(ContextBridge& context) {
#ifdef HAVE_LIBPTHREAD
	static pthread_mutex_t gen_mutex = PTHREAD_MUTEX_INITIALIZER;
	if (pthread_mutex_lock(&gen_mutex) != 0) {
		throw std::runtime_error("Failed to lock gen mutex");
	}
#endif
	GenBridge* pointer = nullptr;
	try {
		pointer = new GenBridge(new giac::gen("left(" + g->print(context.c) + ")", context.c));
		pointer->selfEval(1, context);
	} catch (...) {
#ifdef HAVE_LIBPTHREAD
		pthread_mutex_unlock(&gen_mutex);
#endif
		throw;
	}
#ifdef HAVE_LIBPTHREAD
	if (pthread_mutex_unlock(&gen_mutex) != 0) {
		throw std::runtime_error("Failed to unlock gen mutex");
	}
#endif
	return pointer;
}

GenBridge* GenBridge::right(ContextBridge& context) {
#ifdef HAVE_LIBPTHREAD
	static pthread_mutex_t gen_mutex = PTHREAD_MUTEX_INITIALIZER;
	if (pthread_mutex_lock(&gen_mutex) != 0) {
		throw std::runtime_error("Failed to lock gen mutex");
	}
#endif
	GenBridge* pointer = nullptr;
	try {
		pointer = new GenBridge(new giac::gen("right(" + g->print(context.c) + ")", context.c));
		pointer->selfEval(1, context);
	} catch (...) {
#ifdef HAVE_LIBPTHREAD
		pthread_mutex_unlock(&gen_mutex);
#endif
		throw;
	}
#ifdef HAVE_LIBPTHREAD
	if (pthread_mutex_unlock(&gen_mutex) != 0) {
		throw std::runtime_error("Failed to unlock gen mutex");
	}
#endif
	return pointer;
}

GenBridge* GenBridge::canonicalForm(ContextBridge& context) {
#ifdef HAVE_LIBPTHREAD
	static pthread_mutex_t gen_mutex = PTHREAD_MUTEX_INITIALIZER;
	if (pthread_mutex_lock(&gen_mutex) != 0) {
		throw std::runtime_error("Failed to lock gen mutex");
	}
#endif
	GenBridge* pointer = nullptr;
	try {
		pointer = new GenBridge(new giac::gen("canonical_form(" + g->print(context.c) + ")", context.c));
		pointer->selfEval(1, context);
	} catch (...) {
#ifdef HAVE_LIBPTHREAD
		pthread_mutex_unlock(&gen_mutex);
#endif
		throw;
	}
#ifdef HAVE_LIBPTHREAD
	if (pthread_mutex_unlock(&gen_mutex) != 0) {
		throw std::runtime_error("Failed to unlock gen mutex");
	}
#endif
	return pointer;
}

GenBridge* GenBridge::regroup(ContextBridge& context) {
#ifdef HAVE_LIBPTHREAD
	static pthread_mutex_t gen_mutex = PTHREAD_MUTEX_INITIALIZER;
	if (pthread_mutex_lock(&gen_mutex) != 0) {
		throw std::runtime_error("Failed to lock gen mutex");
	}
#endif
	GenBridge* pointer = nullptr;
	try {
		pointer = new GenBridge(new giac::gen("regroup(" + g->print(context.c) + ")", context.c));
		pointer->selfEval(1, context);
	} catch (...) {
#ifdef HAVE_LIBPTHREAD
		pthread_mutex_unlock(&gen_mutex);
#endif
		throw;
	}
#ifdef HAVE_LIBPTHREAD
	if (pthread_mutex_unlock(&gen_mutex) != 0) {
		throw std::runtime_error("Failed to unlock gen mutex");
	}
#endif
	return pointer;
}

GenBridge* GenBridge::simplify(ContextBridge& context) {
#ifdef HAVE_LIBPTHREAD
	static pthread_mutex_t gen_mutex = PTHREAD_MUTEX_INITIALIZER;
	if (pthread_mutex_lock(&gen_mutex) != 0) {
		throw std::runtime_error("Failed to lock gen mutex");
	}
#endif
	GenBridge* pointer = nullptr;
	try {
		pointer = new GenBridge(new giac::gen("simplify(" + g->print(context.c) + ")", context.c));
		pointer->selfEval(1, context);
	} catch (...) {
#ifdef HAVE_LIBPTHREAD
		pthread_mutex_unlock(&gen_mutex);
#endif
		throw;
	}
#ifdef HAVE_LIBPTHREAD
	if (pthread_mutex_unlock(&gen_mutex) != 0) {
		throw std::runtime_error("Failed to unlock gen mutex");
	}
#endif
	return pointer;
}

GenBridge* GenBridge::operator+(GenBridge& other) {
#ifdef HAVE_LIBPTHREAD
	static pthread_mutex_t gen_mutex = PTHREAD_MUTEX_INITIALIZER;
	if (pthread_mutex_lock(&gen_mutex) != 0) {
		throw std::runtime_error("Failed to lock gen mutex");
	}
#endif
	GenBridge* result = nullptr;
	try {
		result = new GenBridge(new giac::gen(*g + *other.g));
	} catch (...) {
#ifdef HAVE_LIBPTHREAD
		pthread_mutex_unlock(&gen_mutex);
#endif
		throw;
	}
#ifdef HAVE_LIBPTHREAD
	if (pthread_mutex_unlock(&gen_mutex) != 0) {
		throw std::runtime_error("Failed to unlock gen mutex");
	}
#endif
	return result;
}

GenBridge* GenBridge::operator-(GenBridge& other) {
#ifdef HAVE_LIBPTHREAD
	static pthread_mutex_t gen_mutex = PTHREAD_MUTEX_INITIALIZER;
	if (pthread_mutex_lock(&gen_mutex) != 0) {
		throw std::runtime_error("Failed to lock gen mutex");
	}
#endif
	GenBridge* result = nullptr;
	try {
		result = new GenBridge(new giac::gen(*g - *other.g));
	} catch (...) {
#ifdef HAVE_LIBPTHREAD
		pthread_mutex_unlock(&gen_mutex);
#endif
		throw;
	}
#ifdef HAVE_LIBPTHREAD
	if (pthread_mutex_unlock(&gen_mutex) != 0) {
		throw std::runtime_error("Failed to unlock gen mutex");
	}
#endif
	return result;
}

GenBridge* GenBridge::operator*(GenBridge& other) {
#ifdef HAVE_LIBPTHREAD
	static pthread_mutex_t gen_mutex = PTHREAD_MUTEX_INITIALIZER;
	if (pthread_mutex_lock(&gen_mutex) != 0) {
		throw std::runtime_error("Failed to lock gen mutex");
	}
#endif
	GenBridge* result = nullptr;
	try {
		result = new GenBridge(new giac::gen(*g * *other.g));
	} catch (...) {
#ifdef HAVE_LIBPTHREAD
		pthread_mutex_unlock(&gen_mutex);
#endif
		throw;
	}
#ifdef HAVE_LIBPTHREAD
	if (pthread_mutex_unlock(&gen_mutex) != 0) {
		throw std::runtime_error("Failed to unlock gen mutex");
	}
#endif
	return result;
}

GenBridge* GenBridge::operator/(GenBridge& other) {
#ifdef HAVE_LIBPTHREAD
	static pthread_mutex_t gen_mutex = PTHREAD_MUTEX_INITIALIZER;
	if (pthread_mutex_lock(&gen_mutex) != 0) {
		throw std::runtime_error("Failed to lock gen mutex");
	}
#endif
	GenBridge* result = nullptr;
	try {
		result = new GenBridge(new giac::gen(*g / *other.g));
	} catch (...) {
#ifdef HAVE_LIBPTHREAD
		pthread_mutex_unlock(&gen_mutex);
#endif
		throw;
	}
#ifdef HAVE_LIBPTHREAD
	if (pthread_mutex_unlock(&gen_mutex) != 0) {
		throw std::runtime_error("Failed to unlock gen mutex");
	}
#endif
	return result;
}

GenBridge* GenBridge::operator-() {
#ifdef HAVE_LIBPTHREAD
	static pthread_mutex_t gen_mutex = PTHREAD_MUTEX_INITIALIZER;
	if (pthread_mutex_lock(&gen_mutex) != 0) {
		throw std::runtime_error("Failed to lock gen mutex");
	}
#endif
	GenBridge* result = nullptr;
	try {
		result = new GenBridge(new giac::gen(-*g));
	} catch (...) {
#ifdef HAVE_LIBPTHREAD
		pthread_mutex_unlock(&gen_mutex);
#endif
		throw;
	}
#ifdef HAVE_LIBPTHREAD
	if (pthread_mutex_unlock(&gen_mutex) != 0) {
		throw std::runtime_error("Failed to unlock gen mutex");
	}
#endif
	return result;
}