#include "Token.hpp"
#include <ctype.h>
#include <algorithm>

/**
 * @brief      This class describes a preprocessor.
 */
class Preprocessor {

	private:
		std::vector<Token> vector_;
		std::string string_;

	public:

		// Builders & Destroyer
		Preprocessor (void);
		Preprocessor (std::string line);
		~Preprocessor (void);

		// Getters 
		std::vector<Token> get_Vector (void) const;
		std::string get_String (void) const;

		// Setters
		void set_Vector (std::vector<Token> newVector);
		void set_String (std::string newString);

		// Functions
		void generateWords (void);
		std::string preprocessor (std::string str);
		void printVector (void);
		int hasToken (std::string str);
};