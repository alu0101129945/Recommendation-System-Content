#include "../include/Preprocessor.hpp"

/**
 * @brief      Constructs a new instance.
 */
Preprocessor::Preprocessor (void) {
	set_String("");
}

/**
 * @brief      Constructs a new instance.
 *
 * @param[in]  line  The line
 */
Preprocessor::Preprocessor (std::string line) {
	set_String(line);
}

/**
 * @brief      Destroys the object.
 */
Preprocessor::~Preprocessor (void) {}

/**
 * @brief      Gets the vector.
 *
 * @return     The vector.
 */
std::vector<Token> Preprocessor::get_Vector (void) const {
	return vector_;
}

/**
 * @brief      Gets the string.
 *
 * @return     The string.
 */
std::string Preprocessor::get_String (void) const {
	return string_;
}

/**
 * @brief      Sets the vector.
 *
 * @param[in]  newVector  The new vector
 */
void Preprocessor::set_Vector (std::vector<Token> newVector) {
	vector_ = newVector;
}

/**
 * @brief      Sets the string.
 *
 * @param[in]  newString  The new string
 */
void Preprocessor::set_String (std::string newString) {
	string_ = newString;
}

/**
 * @brief      Generates the words and push them into the vector
 */
void Preprocessor::generateWords (void) {
	unsigned counter = 0;
	std::string tmp = "";
	while (counter < string_.length()) {
		if (string_[counter] != ' ' and string_[counter] != '\n')
			tmp += string_[counter];
		else {
			std::string newWord = preprocessor(tmp);	
			int pos = hasToken(newWord);
			if (pos == -1) {
				Token newToken(newWord);
				vector_.push_back(newWord);
			}
			else {
				vector_[pos].increase();
			}
			tmp = "";
		}
		counter++;
	}
}

/**
 * @brief      Preprocess the word converting it to lower case and deleting the symbols.
 *
 * @param[in]  str   The string
 *
 * @return     The preprocessed word
 */
std::string Preprocessor::preprocessor (std::string str) {
	std::transform(str.begin(), str.end(),str.begin(), ::tolower);
	std::string result = "";
	for (unsigned i = 0; i < str.length(); i++) {
		if (str[i] != '.' and str[i] != ',' and str[i] != '-' and str[i] != '\'' and str[i] != '%' and str[i] != ';' and str[i] != ':') 
			result += str[i];
	}
	return result;
}

/**
 * @brief      Searchs if a token already exist
 *
 * @param[in]  str   The string
 *
 * @return     The position of the token in the vector
 */
int Preprocessor::hasToken (std::string str) {
	for (unsigned i = 0; i < vector_.size(); i++) {
		if (vector_[i].get_Name() == str)
			return i;
	}
	return -1;
}