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

![Imagen de la clase Recomendation.hpp]()

He decidido explicar el código desarrollado siguiendo el algoritmo ya que considero es la mejor manera de entenderlo. Por tanto, se comienza generando los artículos. Para ello, abre el fichero pasado como argumento, lee línea por línea del documento y crea su respectivo artículo con cada una de ellas almacenándolos en el atributo detallado anteriormente (vector de artículos). Además, genera los token de cada uno. Esto se realiza llamando al método de la clase Artículo denominado "generateTokens". En este, se crea un objeto de tipo Preprocessor al cual se le pasa al constructor de esa clase la línea que se está analizando. 

A continuación, se generan las palabras. Para realizar esto se utilizan tres métodos de la clase "Preprocessor" bien diferenciados. Antes de su explicación se puede observar a continuación una imagen de la misma.

![Imagen de la clase Preprocessor.hpp]()

En primer lugar, "generateWords". Este se encarga de saltarse los espacios en blanco y los saltos de líneas, y llama a su vez a los siguientes métodos cuando tiene almacenada la palabra completa. En segundo lugar, "preprocessor", convierte a minúscula toda la palabra y les quita todos los signos de puntuación que no se necesitan almacenar en el string que retorna como resultado. Una vez se tienen las palabras como se quieren, se comprueba si cada una se encuentra en el vector de tokens (atributo de la clase Preprocessor), en caso de que no lo esté, crea un nuevo Token y mete en dicho vector la nueva palabra creada. En caso contrario, no la mete pero incrementa el TF de esa palabra. Por último, utiliza "hasToken" que comprueba si el nombre de esa palabra ya está almacenada en el vector final y retorna la posición en la que se encuentra en el vector (en caso de que no esté retorna -1). Se puede observar a continuación el código de los tres métodos. 

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

Por otro lado, se generan las tablas. Este método se encarga de recorrer cada artículo y calcular el número de documentos en N (articles_.size()) en los que la palabra clave x aparece, esto es, dfx. Acto seguido, se calcula el IDF y TF-IDF.  

### 4. Ejemplo de uso. 