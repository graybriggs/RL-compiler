
#ifndef SYMBOL_TABLE
#define SYMBOL_TABLE

#include <unordered_set>


/*
	The symbol table is mostly concerned with the storing of
	identifiers and their attributes

*/


enum Scope { GLOBAL, LOCAL_BLOCK, FUNCTION_BLOCK };  // in the global block scope or in a local scope or function block. Variables declared in function parameters use FUNCTION_BLOCK scope
enum State { INITIALIZED, UNINITIALIZED, NOT_APPLICABLE } // has the variable been initialized. NOT_APPLICABLE for function name identifiers
enum VariableType { INTEGER, FLOATING_POINT, STRING, USER_DEFINED }; // current type of the variable
enum IdentifierType { VARIABLE, CONST, FUNCTION }; // is the identifier for a variable or function // const will be added later

struct Token;

struct Symbol {

	Scope scope;
	State State;
	VariableType variable_type;
	IdentifierType id_type;

	TokenType type;
	std::string symbol_name;
	
};

struct SymbolTable {

	std::unordered_list<Symbol> symbol_table;
};


// Create a new symbol table and pass its parent table
// This is used for identifiers in local scopes

void symtbl_create(const SymbolTable& parent_table, SymbolTable local_table);

void symtbl_insert(SymbolTable& table, Symbol sym, Token tok);
Token symtbl_lookup(const SymbolTable& table, const Symbol sym) const;



/*
//Example:

SymbolTable global_scope_symbols;

SymbolTable some_local_scope;
symtbl_create(global_scope_symbols, some_local_scope);
*/


#endif