# Sistemas de Recomendación Basado en Modelos de Contenido
## Laura Cañizares Herrera - ALU0101129945

### 1. Introducción.
A modo de introducción, se detalla un informe de la práctica de Sistemas de recomendación basada en modelos de contenido de la asignatura Gestión del conocimiento en las Organizaciones del grado de Ingeniería Informática.

Esta práctica se ha realizado con el lenguaje de programación C++, el editor de código Visual Studio Code y la ayuda de las transparencias aportadas por el profesorado de la asignatura.

Un Sistema de recomendación basado en contenido es aquel que tiene en cuenta algunos datos del historial del usuario e intenta predecir lo que busca y las sugerencias similares que podría mostrarle. Este tipo de sistemas es uno de los que tiene mayor presencia en la actualidad. Con ellos se puede descubrir opciones que se ajusten a las características de los productos o contenidos que se han disfrutado con anterioridad y elegir elementos similares nuevos.

### 2. Estructura del proyecto.
En el directorio /src se encuentran los archivos .cpp que contienen el código fuente de las clases. En /include los .hpp de cada una de las mismas. En la carpeta inputs el fichero de entrada que contiene los diferentes artículos de cada documento. En /image las imágenes añadidas al README.md. Y por último, en el /build se encuentra el makefile para automatizar la tarea de ejecución realizando simplemente un "make run".

![Imagen estructura de directorios](https://github.com/alu0101129945/Recommendation-System-Content/blob/master/image/Screenshot_20211219_174454.png)

### 3. Descripción del código desarrollado.
En primer lugar, se ha decidido modular el código en cuatro clases diferenciables: Recomendation, Article, Preprocessor y Token. La clase encargada de poner en marcha el sistema recomendador es la denominada "Recomendation". Esta tiene como atributos un vector de artículos y el nombre del fichero que se le pasa como argumento en la ejecución del programa al constructor de dicha clase. 

![Imagen de la clase Recomendation.hpp](https://github.com/alu0101129945/Recommendation-System-Content/blob/master/image/ClaseRecomendation.png)

He decidido explicar el código desarrollado siguiendo el algoritmo ya que considero es la mejor manera de entenderlo. Por tanto, se comienza generando los artículos. Para ello, abre el fichero pasado como argumento, lee línea por línea del documento y crea su respectivo artículo con cada una de ellas almacenándolos en el atributo detallado anteriormente (vector de artículos). Además, genera los token de cada uno. Esto se realiza llamando al método de la clase Artículo denominado "generateTokens". En este, se crea un objeto de tipo Preprocessor al cual se le pasa al constructor de esa clase la línea que se está analizando. 

A continuación, se generan las palabras. Para realizar esto se utilizan tres métodos de la clase "Preprocessor" bien diferenciados. Antes de su explicación se puede observar a continuación una imagen de la misma.

![Imagen de la clase Preprocessor.hpp](https://github.com/alu0101129945/Recommendation-System-Content/blob/master/image/ClasePreprocessor.png)

En primer lugar, "generateWords". Este se encarga de saltarse los espacios en blanco y los saltos de líneas, y llama a su vez a los siguientes métodos cuando tiene almacenada la palabra completa. En segundo lugar, "preprocessor", convierte a minúscula toda la palabra y les quita todos los signos de puntuación que no se necesitan almacenar en el string que retorna como resultado. Una vez se tienen las palabras como se quieren, se comprueba si cada una se encuentra en el vector de tokens (atributo de la clase Preprocessor), en caso de que no lo esté, crea un nuevo Token y mete en dicho vector la nueva palabra creada. En caso contrario, no la mete pero incrementa el TF de esa palabra (método de la clase Token que incrementa el número de veces que aparece la palabra en el documento, es decir, guarda en el atributo ammount su frecuencia). Por último, utiliza "hasToken" que comprueba si el nombre de esa palabra ya está almacenada en el vector final y retorna la posición en la que se encuentra en el vector (en caso de que no esté retorna -1). Se puede observar a continuación el código de los tres métodos. 

1. GenerateWords.
~~~
void Preprocessor::generateWords (void) {
	unsigned counter = 0;
	std::string tmp = "";
	while (counter < string_.length()) {
		if (string_[counter] != ' ' and string_[counter] != '\n') {
			tmp += string_[counter];
		}
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
~~~

2. preprocessor.
~~~
std::string Preprocessor::preprocessor (std::string str) {
	std::transform(str.begin(), str.end(),str.begin(), ::tolower);
	std::string result = "";
	for (unsigned i = 0; i < str.length(); i++) {
		if (str[i] != '.' and str[i] != ',' and str[i] != '-' and str[i] != '\'' and str[i] != '%' and str[i] != ';' and str[i] != ':') {
			result += str[i];
		}
	}
	return result;
}
~~~

3. HasToken.
~~~
int Preprocessor::hasToken (std::string str) {
	for (unsigned i = 0; i < vector_.size(); i++) {
		if (vector_[i].get_Name() == str) {
			return i;
		}
	}
	return -1;
}
~~~

Por otro lado, se generan las tablas. Este método se encarga de recorrer cada artículo y calcular con cada palabra el número de documentos en N (articles_.size()) en los que dicha palabra aparece, esto es, dfx. Para ello utiliza un método de la clase Article denominado "containsWord" que devuelve un booleano (true en caso de que coincida el nombre de alguna palabra del vector de tokens con la que está analizando en ese momento). 

- ContainsWord.
~~~
bool Article::containsWord (std::string str) {
    for (unsigned i = 0; i < token_.size(); i++) {
        if (token_[i].get_Name() == str) {
            return true;
        }
    }
    return false;
}
~~~

Acto seguido, se calcula el IDF y TF-IDF. Mediante el método "generateItemMetrics" el cual recibe por parámetro la posición del token en el vector (i), la cantidad de documentos (N) y el dfx (cantidad de documentos con X palabra), invoca los respectivos setters de la clase Token que realizan los cálculos correspondientes. 

- GenerateItemMetrics.
~~~
void Article::generateItemMetrics (unsigned i, unsigned N, unsigned dfx) {
    token_[i].set_Idf(N, dfx);
    token_[i].set_Tf_Idf();
}
~~~

- Set_Idf.
~~~
void Token::set_Idf (unsigned N, unsigned dfx) {
    idf_ = std::log10(N / dfx);
}
~~~

- Set_Tf-Idf.
Ammount es la cantidad de veces (frecuencia) que aparece la palabra en el documento.
~~~
void Token::set_Tf_Idf (void) {
    tf_idf_ = ammount_ * idf_;
}
~~~

La clase Token por tanto queda reflejada de la siguiente manera. 

![Imagen de la clase Token]()

A continuación, se comienza a realizar el proceso de normalización del vector con el método "generateVectorSize". Para ello, se calcula la longitud del mismo como la raíz cuadrada de la suma de los valores al cuadrado de cada TF-IDF en el vector. 

- GenerateVectorSize.
~~~
void Article::generateVectorSize (void) {
    vectorSize_ = 0.0;
    for (unsigned i = 0; i < token_.size(); i++) {
        vectorSize_ += (token_[i].get_Tf_Idf() * token_[i].get_Tf_Idf());
    }
    vectorSize_ = std::sqrt(vectorSize_);
}
~~~

Luego, cada vector de términos es dividido por la longitud del vector del documento para obtener el vector normalizado mediante la función "generateNormalizedValue" que se puede observar a continuación.

- GenerateNormalizedValue.
~~~
void Article::generateNormalizedValue (void) {
    for (unsigned i = 0; i < token_.size(); i++) {
        token_[i].set_NormalizedValue(token_[i].get_Tf_Idf() / get_VectorSize());
    }
}
~~~

De esta manera, queda explicada los métodos más relevantes de la clase Article. 

![Imagen de la clase Article.hpp]()

Una vez obtenidos los vectores normalizados, se calculan los valores del coseno para averiguar la similaridad entre los artículos. Para ello, mediante el método denominado "calculateCosines", simplemente se suma el producto de los vectores de ambos artículos, es decir, en el primer bucle i se recorre el vector de artículos, acto seguido,se recorre con j el mismo vector para evitar que se realicen los cálculos con el mismo artículo, entonces, cuando no coincidan i y j, se recorre el vector de tokens de cada uno de los artículos para realizar la similaridad con aquellos tokens que coincidan en ambos. Por último, se añade el resultado en el vector de float denominado cosine_ en la clase Article. 

- CalculateCosines.
~~~
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
~~~

Finalmente, se muestran todos los resultados por pantalla tal y como se pide en el guión de la práctica como se podrá observar en el siguiente apartado del informe. 

### 4. Ejemplo de uso. 