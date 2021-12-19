#include <vector>
#include <iostream>
#include "Preprocessor.hpp"

/**
 * @brief      This class describes an article.
 */
class Article {

	private:
		unsigned id_;
		std::vector<Token> token_;
		std::string line_;
		float vectorSize_;
		std::vector<float> cosine_;

	public:

		// Builder & Destroyer
		Article (void);
		~Article (void);

		// Getter
		unsigned get_Id (void) const;
		std::vector<Token> get_Token (void) const;
		std::string get_Line (void) const;
		float get_VectorSize (void) const;
		std::vector<float> get_Cosines (void) const;

		// Setter
		void set_Id (unsigned newId);
		void set_Token (std::vector<Token> newToken);
		void set_Line (std::string newLine);
		void set_VectorSize (float newVectorSize);

		// Functions
		void generateTokens (void);
		bool containsWord (std::string str);
		void generateItemMetrics (unsigned i, unsigned N, unsigned dfx);
		void generateVectorSize (void);
		void generateNormalizedValue (void);
		void addCosine (float tmp);
};