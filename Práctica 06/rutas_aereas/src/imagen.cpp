/**
 * @file imagen.cpp
 * @brief Fichero de implementación del TDA Imagen
 *
 *
 * @author Arturo Olivares Martos
 * @author Daniel Hidalgo Chica
 */

#include "imagen.h"
#include "imagenES.h"
#include "string.h"
#include <cmath>
#include <cassert>
#include <iostream>

using namespace std;

Imagen::Imagen()
{
    data = 0;
    nf = nc = 0;
}

Imagen::Imagen(int f, int c)
{
    nf = f;
    nc = c;
    data = new Pixel *[nf];
    for (int i = 0; i < nf; i++)
    {
        data[i] = new Pixel[nc];
        for (int j = 0; j < nc; j++)
        {
            data[i][j].r = 255;
            data[i][j].g = 255;
            data[i][j].b = 255;
            data[i][j].transp = 255;
        }
    }
}

void Imagen::borrar()
{
    for (int i = 0; i < nf; i++)
        delete[] data[i];
    delete[] data;
}

void Imagen::copiar(const Imagen &img)
{

    nf = img.nf;
    nc = img.nc;
    data = new Pixel *[nf];
    for (int i = 0; i < nf; i++)
    {
        data[i] = new Pixel[nc];
        for (int j = 0; j < nc; j++)
        {
            data[i][j] = img.data[i][j];
        }
    }
}

Imagen& Imagen::operator=(const Imagen &img)
{
    if (this != &img)
    {
        borrar();
        copiar(img);
    }
    return *this;
}

Pixel Imagen::media_pixeles(const Pixel& p1, const Pixel& p2) const{
    Pixel ret_p;
    ret_p.r = (p1.r + p2.r) / 2;
    ret_p.g = (p1.g + p2.g) / 2;
    ret_p.b = (p1.b + p2.b) / 2;
    ret_p.transp = 255;
    return ret_p;
}

void Imagen::LeerImagen(const char *img_path, const string &mascara_path)
{
    int f, c;
    unsigned char *aux, *aux_mask;

    LeerTipoImagen(img_path, f, c);
    aux = new unsigned char[f * c * 3];
    LeerImagenPPM(img_path, f, c, aux);
    if (mascara_path != "")
    {
        int fm, cm;
        LeerTipoImagen(mascara_path.c_str(), fm, cm);
        aux_mask = new unsigned char[fm * cm];
        LeerImagenPGM(mascara_path.c_str(), fm, cm, aux_mask);
    }
    else
    {
        aux_mask = 0;
    }

    Imagen img(f, c);
    int total = f * c * 3;
    for (int i = 0; i < total; i += 3)
    {
        int posi = i / (c * 3);
        int posj = (i % (c * 3)) / 3;

        img.data[posi][posj].r = aux[i];
        img.data[posi][posj].g = aux[i + 1];
        img.data[posi][posj].b = aux[i + 2];
        if (aux_mask != 0)
            img.data[posi][posj].transp = aux_mask[i / 3];
        else
            img.data[posi][posj].transp = 255;
    }

    *this = img;
    if (aux_mask != 0)
        delete[] aux_mask;
    delete[] aux;
}

void Imagen::EscribirImagen(const char img_path[]) const
{
    unsigned char *aux = new unsigned char[nf * nc * 3];
    unsigned char *m = new unsigned char[nf * nc];

    int total = nf * nc * 3;

    for (int i = 0; i < total; i += 3)
    {
        int posi = i / (nc * 3);
        int posj = (i % (nc * 3)) / 3;

        aux[i] = data[posi][posj].r;
        aux[i + 1] = data[posi][posj].g;
        aux[i + 2] = data[posi][posj].b;
        m[i / 3] = data[posi][posj].transp;
    }

    if (!EscribirImagenPPM(img_path, aux, nf, nc))
    {
        cerr << "Ha habido un problema en la escritura de " << img_path << endl;
    }

    delete[] aux;

    string n_aux = "mascara_";
    n_aux = n_aux + img_path;
    size_t found = n_aux.find(".ppm");

    if (found != string::npos)
    {
        n_aux = n_aux.substr(0, found);
    }

    n_aux = n_aux + ".pgm";

    if (!EscribirImagenPGM(n_aux.c_str(), m, nf, nc))
    {
        cerr << "Ha habido un problema en la escritura de " << n_aux << endl;
    }


    delete[] m;
}

void Imagen::PutImagen(int posi, int posj, const Imagen & img, Tipo_Pegado t){
    assert(posi + img.nf < nf && posj + img.nc < nc);

    for (int i = 0; i < img.nf; i++)
        for (int j = 0; j < img.nc; j++)
            if (posi + i >= 0 && posi + i < nf && posj + j >= 0 && posj + j < nc)
            {
                if (img(i,j).transp != 0) {
                    if (t == OPACO)
                        (*this).operator()(posi + i, posj + j) = img(i, j);
                    else if (t == BLENDING) {
                        (*this).operator()(posi + i, posj + j) = media_pixeles((*this).operator()(posi + i, posj + j), img(i, j));
                    }
                }
            }
}

const Pixel &Imagen::operator()(int i, int j) const {
    assert(i >= 0 && i < nf && j >= 0 && j < nc);
	return data[i][j];
}

Pixel &Imagen::operator()(int i, int j) {
    assert(i >= 0 && i < nf && j >= 0 && j < nc);
	return data[i][j];
}

Imagen Imagen::Rota(double angulo) const {
    double rads=angulo;
    double coseno = cos(angulo);
    double seno = sin(angulo);
    //Para obtener las dimensiones de la imagen
    int rcorners[4],ccorners[4];
    int newimgrows,newimgcols;
    double new_row_min,new_col_min,new_row_max,new_col_max;
    double inter,inter1;
    rcorners[0]=0;
    rcorners[1]=0;
    ccorners[0]=0;
    ccorners[2]=0;
    rcorners[2]=getFilas()-1;
    rcorners[3]=getFilas()-1;
    ccorners[1]=getColumnas()-1;
    ccorners[3]=getColumnas()-1;
    new_row_min=0;
    new_col_min=0;
    new_row_max=0;
    new_col_max=0;
    newimgrows=0;
    newimgcols=0;
    for(int count=0;count<4;count++){
        inter=rcorners[count]*coseno+ccorners[count]*seno;

        if(inter<new_row_min)
            new_row_min=inter;
        if(inter>new_row_max)
            new_row_max=inter;
        inter1=-rcorners[count]*seno+ccorners[count]*coseno;

        if(inter1<new_col_min)
            new_col_min=inter1;
        if(inter1>new_col_max)
            new_col_max=inter1;
    }

    newimgrows=(unsigned)ceil((double)new_row_max-new_row_min);
    newimgcols=(unsigned)ceil((double)new_col_max-new_col_min);

    Imagen Iout(newimgrows,newimgcols);
    for(int rows=0;rows<newimgrows;rows++){
        for(int cols=0;cols<newimgcols;cols++){
            float oldrowcos=((float)rows+new_row_min)*cos(-rads);
            float oldrowsin=((float)rows+new_row_min)*sin(-rads);
            float oldcolcos=((float)cols+new_col_min)*cos(-rads);
            float oldcolsin=((float)cols+new_col_min)*sin(-rads);
            float old_row=oldrowcos+oldcolsin;
            float old_col=-oldrowsin+oldcolcos;
            old_row=ceil((double)old_row);
            old_col=ceil((double)old_col);
            if ((old_row >= 0) && (old_row < getFilas()) &&
                (old_col >= 0) && (old_col < getColumnas())) {
                Iout(rows, cols) = (*this).operator()(old_row, old_col);
            } else {
	            Iout(rows, cols).r = Iout(rows, cols).g = Iout(rows, cols).b = 255;
				Iout(rows, cols).transp = 0;
            }
        }
    }
    return Iout;
}

// TODO Ambos Iteradores