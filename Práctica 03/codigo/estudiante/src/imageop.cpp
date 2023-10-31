/**
 * @file imageop.cpp
 * @brief Fichero con definiciones para el resto de métodos de la clase Image
 */

#include <iostream>
#include <cmath>
#include <image.h>
#include <fstream>
#include <cassert>
bool Image::operator==(const Image & other) const{

    bool iguales = true;

    // Han de tener las mismas filas y columnas.
    iguales &= this->get_rows() == other.get_rows();
    iguales &= this->get_cols() == other.get_cols();

    int i=0;
    while (iguales && i<this->size()){

        // Compara cada píxel
        iguales = this->get_pixel(i) == other.get_pixel(i);
        i++;
    }

    return iguales;
}


double Image::Mean(int i, int j, int height, int width) const {

    double mean = 0;

    if (height * width!= 0) { // Si hay puntos
        // Se acumulan las sumas de los píxeles en cuestión.
        for (int fil = i; fil < i + height; fil++)
            for (int col = j; col < j + width; col++)
                mean += get_pixel(fil, col);

        // Se divide entre el número de puntos.
        mean /= height * width;
    }

    return mean;
}


// Genera una imagen aumentada 2x.
Image Image::Zoom2X() const{

    const int NFILS = 2*get_rows()-1;
    const int NCOLS = 2*get_cols()-1;

    // Genero mi imagen aumentada con todos los píxeles a 0.
    Image zoomed(NFILS, NCOLS);

    // Itero sobre cada pixel para cambiarlo
    for(int fil=0; fil<NFILS; ++fil)
        for(int col=0; col<NCOLS; col++){

            // Píxel original
            if (fil%2==0 && col%2==0) {
                byte original_pixel = get_pixel(fil/2, col/2);
                zoomed.set_pixel(fil, col, original_pixel);
            }

                // Pixel insertado. Hay que calcular la media.
            else {

                byte average_pixel;

                // Como (int) trunca, tenemos que al dividir entre dos nos quedamos con la fila o columna deseada
                // El operador % nos permite diferenciar si la columna, fila, o ambas son insertadas.
                average_pixel = (byte)round(Mean((int)(fil/2), (int)(col/2), 1+fil%2, 1+col%2));

                zoomed.set_pixel(fil, col, average_pixel);
            }
        }

    return zoomed;
}

// Genera un icono como reducción de una imagen.
Image Image::Subsample(int factor) const{

    Image icono = Image((int)(get_rows()/factor), (int)(get_cols()/factor));

    for(int fil=0; fil<icono.get_rows(); fil++)
        for(int col=0; col<icono.get_cols(); col++){

            // Cada pixel resultante es la media de un cuadrado de lado factor
            byte average = round(Mean(factor*fil, factor*col, factor, factor));
            icono.set_pixel(fil, col, average);
        }

    return icono;
}

void Image::Invert() {
    for (int i = 0; i < this->size(); ++i)
        this->set_pixel(i,255-(this->get_pixel(i)));
}

Image Image::Crop(int nrow, int ncol, int height, int width) const {
    Image return_img(height,width);
    // Rellenamos la imagen resultante
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            return_img.set_pixel(i,j,this->get_pixel(nrow+i,ncol+j));
    return return_img;
}



void Image::AdjustContrast (byte in1, byte in2, byte out1, byte out2){

	/*
	 * Realizamos la siguiente transformación lineal:
	 * T(k) = k' = out1 + [((out2 – out1) / (in2 – in1)) * (k – in1)]
	 */

	// Distinguimos en cada intervalo:
	const double primer_M = (double)(out1)/(double)(in1);
	const double segundo_M = (double)(out2 - out1)/(double)(in2 - in1);
	const double tercer_M = (double)(255-out2)/(double)(255 - in2);

	for (int k=0; k<size(); k++) {

		byte pixel_original = get_pixel(k);
		byte pixel_interpolado;

		if (pixel_original < in1){
			pixel_interpolado = (byte)round((primer_M * (pixel_original)));
		} else if (pixel_original > in2){
			pixel_interpolado = (byte)round(out2 + (tercer_M * (pixel_original - in2)));
		} else{ // pixel_original \in [in1,in2]
			pixel_interpolado = (byte)round(out1 + (segundo_M * (pixel_original - in1)));
		}

		set_pixel(k, pixel_interpolado);
	}
}

void Image::ShuffleRows_noeff() {
    const int p = 9973;
    Image temp(rows,cols);
    int newr;
    for (int r=0; r<rows; r++){
        newr = r*p % rows; // En la fila r metemos la fila newr
        for (int c=0; c<cols;c++)
            temp.set_pixel(r, c, get_pixel(newr, c)); // Para cada elemento de la fila r,
                                                                    // introducimos el correspondiente de newr

    }
    Copy(temp);
}

void Image::ShuffleRows_eff() {
    const int p = 9973;

	// Copiamos el vector de punteros a filas para rellenar el nuevo con originales
	
    byte ** aux_img = new byte * [rows];
    for (int i = 0; i < rows; i++)
        aux_img[i] = img[i];

    // Shuffleamos
    int new_pos;
    for (int i = 0; i < rows; i++) {
        new_pos = (p*i) % rows;
        img[i] = aux_img[new_pos];
    }

    delete [] aux_img;
}

bool Image::MySave (const char *file_path) const{
    std::ofstream f(file_path);
    bool res= true;

    if (f){
        f << "P5" << std::endl;
        f << cols << ' ' << rows << std::endl;
        f << 255 << std::endl;
        for (int fila = 0; fila < get_rows();++fila )
            f.write(reinterpret_cast<char const *>(img[fila]), cols);
        if (!f)
            res=false;
    }
    return res;
}











