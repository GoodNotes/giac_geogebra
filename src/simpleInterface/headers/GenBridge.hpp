#include "ContextBridge.hpp"
#include <string>
#include <vector>

using namespace std;
namespace giac {
	class gen;	
}

class GenBridge {
public:
	giac::gen* g;
	GenBridge(string expression, ContextBridge& context);
	GenBridge(giac::gen* g);
	~GenBridge();
	void selfEval(int level, ContextBridge& context);
	void resetTimeout();
	GenBridge* eval(int level, ContextBridge& context);
	string print(ContextBridge& context);
	int type();
	GenBridge* lname(ContextBridge& context);
	void getListVector(vector<GenBridge*>& list);
	int lenght();
	int isNull();
	int equalSign(GenBridge& other);
	GenBridge* left(ContextBridge& context);
	GenBridge* right(ContextBridge& context);
	GenBridge* canonicalForm(ContextBridge& context);
	GenBridge* regroup(ContextBridge& context);
	GenBridge* simplify(ContextBridge& context);
	GenBridge* operator+(GenBridge& other);
	GenBridge* operator-(GenBridge& other);
	GenBridge* operator*(GenBridge& other);
	GenBridge* operator/(GenBridge& other);
	GenBridge* operator-();

	// Polls giac's internal "identifier name looked corrupted" flag (set
	// defensively whenever giac reads an identificateur::id_name that doesn't
	// look like a plausible string) and clears it. Returns true if corruption
	// was detected since the last call, in which case outLastPointerHex is set
	// to the rejected pointer value (for diagnostics/telemetry only -- the
	// underlying memory is not safe to read). Call this after any top-level
	// giac operation so a corruption event isn't silently swallowed.
	static bool checkAndClearIdentifierCorruption(string& outLastPointerHex);
};
