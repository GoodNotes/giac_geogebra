#include "ContextBridge.hpp"
#include "giac.h"

ContextBridge::ContextBridge() {
	c = new giac::context();
}


ContextBridge::~ContextBridge() {
	std::cout << "[DEBUG] " << __FUNCTION__ << " called for giac::context: " << c << "\n";
	delete c;
}
