#include "../include/Recomendation.hpp"

/**
 * @brief      Constructs a new instance.
 */
Recomendation::Recomendation (void) {}

/**
 * @brief      Constructs a new instance.
 *
 * @param[in]  inputFile  The input file
 */
Recomendation::Recomendation (std::string inputFile) {
	fileName_ = inputFile;
	generateArticles();
	generateTables();
	printTables();
	printTableCosine();
}

/**
 * @brief      Destroys the object.
 */
Recomendation::~Recomendation (void) {}

void Recomendation::generateArticles (void) {
	std::ifstream file(fileName_, std::ios::in);
	if (file.fail()) {
		std::cout << std::endl << "Error 404, file not found." << std::endl;
		exit(1);
	}
	while (!file.eof()) {
		std::string line = "";
		std::getline(file, line);
		Article newArticle;
		newArticle.set_Line(line);
		newArticle.generateTokens();
		articles_.push_back(newArticle);
	}
	file.close();
}

/**
 * @brief      Generates the tables for each article
 */
void Recomendation::generateTables (void) {
	for (unsigned art = 0; art < articles_.size(); art++) {
		for (unsigned i = 0; i < articles_[art].get_Token().size(); i++) {
			unsigned dfx = 0;
			std::string word = articles_[art].get_Token()[i].get_Name();
			for (unsigned j = 0; j < articles_.size(); j++) {
				if (articles_[j].containsWord(word))
					dfx++;
			}
			articles_[art].generateItemMetrics(i, articles_.size(), dfx);
		}
		articles_[art].generateVectorSize();
		articles_[art].generateNormalizedValue();
	}
	calculateCosines();
}

/**
 * @brief      Prints tables.
 */
void Recomendation::printTables (void) {
	for (unsigned art = 0; art < articles_.size(); art++) {
		std::cout << "\n\n\n\nTabla Artículo " << art << ":\nIndice\tTérmino\t\tTF\t\tIDF\t\tTF-IDF\t\tValor Normalizado";
		for (unsigned i = 0; i < articles_[art].get_Token().size(); i++) {
			std::cout << std::endl;
			std::cout << i;
			std::cout << "\t" << articles_[art].get_Token()[i].get_Name();
			if (articles_[art].get_Token()[i].get_Name().length() < 8) {
				std::cout << "\t";
			}
			std::cout << "\t" << articles_[art].get_Token()[i].get_Ammount();
			std::cout << "\t\t" << std::setprecision(4) << articles_[art].get_Token()[i].get_Idf();
			std::cout << "\t\t" << std::setprecision(4) << articles_[art].get_Token()[i].get_Tf_Idf();
			std::cout << "\t\t" << std::setprecision(4) << articles_[art].get_Token()[i].get_NormalizedValue();
		}
	}
}

/**
 * @brief      Calculate the cosines
 */
void Recomendation::calculateCosines (void) {
	for (unsigned i = 0; i < articles_.size(); i++) {
		for (unsigned j = 0; j < articles_.size(); j++) {
			float cosine = 0;
			if (j != i) {
				for (unsigned k = 0; k < articles_[i].get_Token().size(); k++) {
					for (unsigned w = 0; w < articles_[j].get_Token().size(); w++) {
						if (articles_[i].get_Token()[k].get_Name() == articles_[j].get_Token()[w].get_Name()) {
							cosine += (articles_[i].get_Token()[k].get_NormalizedValue() * articles_[j].get_Token()[w].get_NormalizedValue());
							break;
						}
					}
				}
			}
			articles_[i].addCosine(cosine);
		}
	}
}

void Recomendation::printTableCosine (void) {
	for (unsigned i = 0; i < articles_.size(); i++) {
		std::cout << std::endl << std::endl << "Similaridad del artículo: " << i;
		for (unsigned j = 0; j < articles_.size(); j++) {
			if (i != j)
				std::cout << "\ncos(" << i << ", " << j << ") = " << articles_[i].get_Cosines()[j];
		}
	}
}