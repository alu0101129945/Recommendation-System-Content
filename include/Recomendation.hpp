#include "Article.hpp"
#include <cmath>
#include <fstream>

/**
 * @brief      This class describes a recomendation.
 */
class Recomendation {

	private:
		std::vector<Article> articles_;
		std::string fileName_;

	public:

		// Builders & Destroyer
		Recomendation (void);
		Recomendation (std::string inputFile);
		~Recomendation (void);

		// Functions
		void generateArticles (void);
		void runProgram (void);
		void generateTables (void);
		void printTables (void);
		void calculateTableCosine (void);
		void calculateCosines (void);
		void printTableCosine (void);
};