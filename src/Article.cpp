#include "../include/Article.hpp"

/**
 * @brief      Constructs a new instance.
 */
Article::Article (void) {
	set_Id(0);
}

/**
 * @brief      Destroys the object.
 */
Article::~Article (void) {}

/**
 * @brief      Gets the identifier.
 *
 * @return     The identifier.
 */
unsigned Article::get_Id (void) const {
	return id_;
}

/**
 * @brief      Gets the token.
 *
 * @return     The token.
 */
std::vector<Token> Article::get_Token (void) const {
	return token_;
}

/**
 * @brief      Gets the line.
 *
 * @return     The line.
 */
std::string Article::get_Line (void) const {
	return line_;
}

/**
 * @brief      Gets the vector size.
 *
 * @return     The vector size.
 */
float Article::get_VectorSize (void) const {
    return vectorSize_;
}

std::vector<float> Article::get_Cosines (void) const {
    return cosine_;
}

/**
 * @brief      Sets the identifier.
 *
 * @param[in]  newId  The new identifier
 */
void Article::set_Id (unsigned newId) {
	id_ = newId;
}

/**
 * @brief      Sets the token.
 *
 * @param[in]  newToken  The new token
 */
void Article::set_Token (std::vector<Token> newToken) {
	token_ = newToken;
}

/**
 * @brief      Sets the line.
 *
 * @param[in]  newLine  The new line
 */
void Article::set_Line (std::string newLine) {
	line_ = newLine;
}

/**
 * @brief      Sets the vector size.
 *
 * @param[in]  newVectorSize  The new vector size
 */
void Article::set_VectorSize (float newVectorSize) {
    vectorSize_ = newVectorSize;
}

/**
 * @brief      Generate the tokens
 */
void Article::generateTokens (void) {
	Preprocessor newPreprocessor(line_);
	newPreprocessor.generateWords();
	token_ = newPreprocessor.get_Vector();
}

/**
 * @brief      Searchs if the article tokens vector contains a certain word
 *
 * @param[in]  str   The string
 *
 * @return     true if it contains the word, false otherwise
 */
bool Article::containsWord (std::string str) {
    for (unsigned i = 0; i < token_.size(); i++) {
        if (token_[i].get_Name() == str)
            return true;
    }
    return false;
}

/**
 * @brief      Generates the idf and tf-idf 
 *
 * @param[in]  i     Token position in vector
 * @param[in]  N     Ammount of documents
 * @param[in]  dfx   Ammount of documents with X word
 */
void Article::generateItemMetrics (unsigned i, unsigned N, unsigned dfx) {
    token_[i].set_Idf(N, dfx);
    token_[i].set_Tf_Idf();
}

/**
 * @brief      Generate the size vector
 */
void Article::generateVectorSize (void) {
    vectorSize_ = 0.0;
    for (unsigned i = 0; i < token_.size(); i++) {
        vectorSize_ += (token_[i].get_Tf_Idf() * token_[i].get_Tf_Idf());
    }
    vectorSize_ = std::sqrt(vectorSize_);
}

/**
 * @brief      Generate the normalized value 
 */
void Article::generateNormalizedValue (void) {
    for (unsigned i = 0; i < token_.size(); i++) {
        token_[i].set_NormalizedValue(token_[i].get_Tf_Idf() / get_VectorSize());
    }
}

/**
 * @brief      Adds a cosine.
 *
 * @param[in]  tmp   The temporary
 */
void Article::addCosine (float tmp) {
    cosine_.push_back(tmp);
}