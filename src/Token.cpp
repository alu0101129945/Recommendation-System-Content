#include "../include/Token.hpp"

/**
 * @brief      Constructs a new instance.
 */
Token::Token (void) {
	set_Name("");
	set_Ammount(0);
}

/**
 * @brief      Constructs a new instance.
 *
 * @param[in]  name  The name
 */
Token::Token (std::string name) {
	set_Name(name);
	set_Ammount(1);
}

/**
 * @brief      Destroys the object.
 */
Token::~Token (void) {}

/**
 * @brief      Gets the name.
 *
 * @return     The name.
 */
std::string Token::get_Name(void) const {
	return name_;
}

/**
 * @brief      Gets the ammount.
 *
 * @return     The ammount.
 */
unsigned Token::get_Ammount (void) const {
	return ammount_;
}

/**
 * @brief      Gets the idf.
 *
 * @return     The idf.
 */
float Token::get_Idf (void) const {
    return idf_;
}   

/**
 * @brief      Gets the tf idf.
 *
 * @return     The tf idf.
 */
float Token::get_Tf_Idf (void) const {
    return tf_idf_;
}

/**
 * @brief      Gets the normalized value
 *
 * @return     The normalized value
 */
float Token::get_NormalizedValue (void) const {
    return normalizedValue_;
}

/**
 * @brief      Sets the name.
 *
 * @param[in]  name  The name
 */
void Token::set_Name (std::string name) {
	name_ = name;
}

/**
 * @brief      Sets the ammount.
 *
 * @param[in]  ammount  The ammount
 */
void Token::set_Ammount (unsigned ammount) {
	ammount_ = ammount;
}

/**
 * @brief      Sets the idf.
 *
 * @param[in]  N     The new value
 * @param[in]  dfx   The new value
 */
void Token::set_Idf (unsigned N, unsigned dfx) {
    idf_ = std::log10(N / dfx);
}

/**
 * @brief      Sets the tf-idf.
 */
void Token::set_Tf_Idf (void) {
    tf_idf_ = ammount_ * idf_;
}


/**
 * @brief      Sets the normalized value
 *
 * @param[in]  newNormalizedValue  The new normalized value
 */
void Token::set_NormalizedValue (float newNormalizedValue) {
    normalizedValue_ = newNormalizedValue;
}

/**
 * @brief      Equality operator.
 *
 * @param[in]  otherToken  The other token
 *
 * @return     The result of the equality
 */
bool Token::operator== (const Token& otherToken) const {
	return (get_Name() == otherToken.get_Name());
}

/**
 * @brief      Equality operator.
 *
 * @param[in]  str   The string
 *
 * @return     The result of the equality
 */
bool Token::operator== (const std::string& str) const {
	return (get_Name() == str);
}

/**
 * @brief      Assignment operator.
 *
 * @param[in]  otherToken  The other token
 *
 * @return     The result of the assignment
 */
Token& Token::operator= (const Token& otherToken) {
	this -> set_Name(otherToken.get_Name());
	this -> set_Ammount(otherToken.get_Ammount());
	return *this;
}

/**
 * @brief      Incremetates the ammount in 1.
 */
void Token::increase (void) {
	ammount_++;
}