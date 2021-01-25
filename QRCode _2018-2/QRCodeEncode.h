#ifndef _QR_ENCODE_H
#define _QR_ENCODE_H

#include <string.h>
#include <stdio.h>

#include <stdlib.h>
#include "Matrix.h"
#include "QRCode.h"

#define BITS_MODE 4
#define BINARIO 2
#define DECIMAL 10

#define PBM 1
#define PGM 2
#define PPM 3

#define BLACK '1'
#define WHITE '0'

enum Correcao {_L = 0, _M, _Q, _H };
enum Modes {NUMERIC = 0, ALPHANUMERIC, BYTE_MODE};
enum ErrorCorrection { CW_COLUMN=0, NUM_CODIGOS_CORRETORES, BLOCKS_COLUMN};
enum {NOTHING=0, PROCESSO, INFO};
enum {_1 = 0, _2, _3};

const char caracteres[]="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ $%*+-./:"; // nao tem virgula


typedef struct {
    int row, col;
} Coord;
typedef struct {
    unsigned char *elements;
    int tamBits;
} VetorChar;

typedef struct {
    //int penalty[4];
    unsigned char mask;

    VetorChar errorBits;
    VetorChar codStringFormat;
} DataMask;
typedef struct {
    unsigned char blocks; // não passa de 50 //vou fazer um cast //tabela
    unsigned char pcPerBlock;
    unsigned char ccPerBlock;
    VetorChar palavrasCodigo;
    VetorChar codigosCorretores;

    VetorChar interleavedPC;
    VetorChar interleavedCC;
    VetorChar finalMessage;
    VetorChar finalMsgBits;
} CodeWords;
typedef struct {
    unsigned char *modeInd;
    VetorChar countInd;
    VetorChar modeEncode;
    VetorChar strFinal;
} Bits;
typedef struct {
    char *text;
    int tamanho;
    char mode;
    Bits bits;
} Text;

typedef struct {
    char *name;
    int type;
    Matrix *m;
    Matrix *mcopia;
} Image;
typedef struct {
    char show;
    char version;
    char correction;
    Text fraseInfo;
    CodeWords cw;
    DataMask dataMask;
    Image image;
    Coord *dataPosition;

} QRInfo;

void AnaliseDeDados(QRInfo *qr);
void SmallestVersionData(QRInfo *qr);
void SetBits(QRInfo *qr);
void SetCodeWords(QRInfo *qr);
void StructureFinalMessage(QRInfo *qr);
void AddFinderPatterns(QRInfo *qr);
void AddAlignmentPatterns(QRInfo *qr);
void AddTimingPatterns(QRInfo *qr);
void AddReservedAreas(QRInfo *qr);

void GetDataPositions(QRInfo *qr);
void PlaceDataBits(QRInfo *qr);

void FormatInformation(QRInfo *qr);
void PutFormatStringBits(QRInfo *qr, Matrix *matrix);
void DeterminingBestMask(QRInfo *qr);
void AddMask(QRInfo *qr, Matrix *matrix);

void saveImage(Image i);

void Teste_printTableUC(unsigned char *v, int tam) {
    int i;
    for(i=0; i<tam; i++) {
        printf("%i ", v[i]);
        if((i+1)%5==0)
            printf("\n");
        if((i+1)%15==0)
            printf("\n");
    }
}
void showQR(QRInfo *qr) {
    if(qr->show == PROCESSO) {

        printf("\ntext: %s\n", qr->fraseInfo.text);
        printf("mode: %i\n", qr->fraseInfo.mode);
        printf("version: %i\n", qr->version);
        printf("level: %i\n", qr->correction);

        printf("\nmode indicator: %s\n", qr->fraseInfo.bits.modeInd);
        printf("count indicator: %s\n", qr->fraseInfo.bits.countInd.elements);
        printf("mode encode: %s\n\n", qr->fraseInfo.bits.modeEncode.elements);

        printf("bitsMode: %i\n", BITS_MODE);
        printf("bitsCount: %i\n", qr->fraseInfo.bits.countInd.tamBits);
        printf("bitsEncode: %i\n", qr->fraseInfo.bits.modeEncode.tamBits);
        printf("bitsTotal: %i\n\n", qr->fraseInfo.bits.strFinal.tamBits);
        printf("str final: %s\n\n", qr->fraseInfo.bits.strFinal.elements);

        printf("num blocos: %i\n\n", qr->cw.blocks);
        printf("num palavras codigo por bloco: %i\n", qr->cw.pcPerBlock);
        printf("num total de palavras codigo: %i\n\n", qr->cw.palavrasCodigo.tamBits);
        printf("num codigos corretores por bloco: %i\n", qr->cw.ccPerBlock);
        printf("num total de codigos corretores: %i\n\n", qr->cw.codigosCorretores.tamBits);


        printf("Palavras codigo: tamBits - %i\n", qr->cw.palavrasCodigo.tamBits);
        Teste_printTableUC(qr->cw.palavrasCodigo.elements, qr->cw.palavrasCodigo.tamBits);
        printf("\n\nCodigos corretores: tamBits - %i\n", qr->cw.codigosCorretores.tamBits);
        Teste_printTableUC(qr->cw.codigosCorretores.elements, qr->cw.codigosCorretores.tamBits);

        fprintf(stdout, "\n\nPC inter: tamBits - %i\n", qr->cw.interleavedPC.tamBits);
        Teste_printTableUC(qr->cw.interleavedPC.elements, qr->cw.interleavedPC.tamBits);
        fprintf(stdout, "\n\nCC inter: tamBits - %i\n", qr->cw.interleavedCC.tamBits);
        Teste_printTableUC(qr->cw.interleavedCC.elements, qr->cw.interleavedCC.tamBits);

        fprintf(stdout, "\n\nFinal msg: tam - %i\n", qr->cw.finalMessage.tamBits);
        Teste_printTableUC(qr->cw.finalMessage.elements, qr->cw.finalMessage.tamBits);

        fprintf(stdout, "\n\nMsg final de bits - %i\n", qr->cw.finalMsgBits.tamBits);
        fprintf(stdout, "%s\n\n", qr->cw.finalMsgBits.elements);
    } else if(qr->show == INFO) {
        fprintf(stdout, "\nImage: %s\n", qr->image.name);
        fprintf(stdout, "\nText Entered: %s\n", qr->fraseInfo.text);
        fprintf(stdout, "Error Correction: %i\n", qr->correction);
        fprintf(stdout, "Version: %i\n", qr->version+1);
        fprintf(stdout, "Modules: %i x %i pixels\n", qr->image.m->R, qr->image.m->C);
        fprintf(stdout, "Data bits - %s\n\n", qr->cw.finalMsgBits.elements);
        fprintf(stdout, "Mask:  %i\n\n", qr->dataMask.mask);

        M_print(qr->image.m);
    }

}

void QR_free(QRInfo *qr);
void QRCodeMain(char *text, char error, char *version, char* mask) {
    QRInfo *qr;
    qr = (QRInfo *) malloc(1*sizeof(QRInfo));
    qr->show = INFO;
    qr->fraseInfo.tamanho = strlen(text);
    qr->fraseInfo.text = (char*) calloc(qr->fraseInfo.tamanho, sizeof(char));
    qr->fraseInfo.text = text;
    qr->correction = error;

    char *name;
    name = "QRCode";
    qr->image.type = PBM;
    qr->image.name = (char*)calloc(15, sizeof(char));
    int i;
    for(i=0; name[i]; i++){
        qr->image.name[i] = name[i];
    }

    AnaliseDeDados(qr);
    SmallestVersionData(qr);
    SetBits(qr);
    SetCodeWords(qr);
    StructureFinalMessage(qr);
    int modules = 21 + 4*qr->version;
    qr->image.m = M_create(1, modules, modules);

    AddFinderPatterns(qr);
    if(qr->version!=_1)
        AddAlignmentPatterns(qr);
    AddTimingPatterns(qr);

    *M_at(qr->image.m, _1, (unsigned int)4*(qr->version+1)+9, 8)= BLACK;

    AddReservedAreas(qr);
    GetDataPositions(qr);
    PlaceDataBits(qr);


    DeterminingBestMask(qr);

    FormatInformation(qr);
    PutFormatStringBits(qr, qr->image.m);
    AddMask(qr, qr->image.m);

    saveImage(qr->image);
    showQR(qr);

    fromDecimal(DECIMAL, (int)qr->version+1, version, 1);
    fromDecimal(DECIMAL, (int)qr->dataMask.mask, mask, 1);
    QR_free(qr);
}
void QR_free(QRInfo *qr) {
    LOGS(qr->show, printf("\n-------------------\n");)
    free(qr->fraseInfo.text);
    LOGS(qr->show, printf("Liberou text\n");)
    free(qr->fraseInfo.bits.modeInd);
    LOGS(qr->show, printf("Liberou mode\n");)
    free(qr->fraseInfo.bits.countInd.elements);
    LOGS(qr->show, printf("Liberou count\n");)
    free(qr->fraseInfo.bits.countInd.elements);
    LOGS(qr->show, printf("Liberou encode\n");)
    free(qr->fraseInfo.bits.strFinal.elements);
    LOGS(qr->show, printf("Liberou str\n");)

    free(qr->cw.palavrasCodigo.elements);
    LOGS(qr->show, printf("Liberou palavras codigo\n");)
    free(qr->cw.codigosCorretores.elements);
    LOGS(qr->show, printf("Liberou codigos corretores\n");)

    free(qr->cw.interleavedPC.elements);
    LOGS(qr->show, printf("Liberou PC inter\n");)
    free(qr->cw.interleavedCC.elements);
    LOGS(qr->show, printf("Liberou CC inter\n");)
    free(qr->cw.finalMessage.elements);
    LOGS(qr->show, printf("Liberou final msg uc\n");)
    free(qr->cw.finalMsgBits.elements);
    LOGS(qr->show, printf("Liberou final msg de bits uc\n");)

    M_free(qr->image.m);
    LOGS(qr->show, printf("Liberou Matrix\n");)

    free(qr->image.name);
    LOGS(qr->show, printf("Liberou image name\n");)

    free(qr->dataMask.errorBits.elements);
    LOGS(qr->show, printf("Liberou error bits da mask\n");)

    free(qr->dataMask.codStringFormat.elements);
    LOGS(qr->show, printf("Liberou codStringFormat da mask\n");)
    free(qr);
    LOGS(qr->show, printf("Liberou tudo");)
    LOGS(qr->show, printf("\n-------------------\n");)
}
char comparaCaracteres(char letra, int inicio, int fim);
void AnaliseDeDados(QRInfo *qr) {
    int i;
    qr->fraseInfo.mode = NUMERIC;
    for(i=0; qr->fraseInfo.text[i]; i++) {
        if(!comparaCaracteres(qr->fraseInfo.text[i], 0, 44)) {
            qr->fraseInfo.mode = BYTE_MODE;
            break;
        } else if(qr->fraseInfo.mode == NUMERIC)
            if(comparaCaracteres(qr->fraseInfo.text[i], 10, 44))
                qr->fraseInfo.mode = ALPHANUMERIC;
    }
}
char comparaCaracteres(char letra, int inicio, int fim) {
    int i;
    for(i=inicio; i<=fim; i++) {
        if(letra==caracteres[i])
            return '1';
    }
    return 0;
}

void readFileChar(char *name, char v[], int tam);
void SmallestVersionData(QRInfo *qr) {
    Matrix *version;
    version = M_create(3, 4, 3);

    char v[36];
    readFileChar("CapacitiesTable.bin", v, 36);
    M_fill(version, v, v + sizeof(v)/sizeof(char));

    int i, bestVersion = 0;
    LOGS(qr->show, printf("tamanho da frase: %i\n", qr->fraseInfo.tamanho);)
    for(i=0; i<3; i++)
        if(qr->fraseInfo.tamanho<=(int)*M_at(version, i, (unsigned int)qr->correction, (unsigned int) qr->fraseInfo.mode)) {
            bestVersion = i;
            break;
        }

    qr->version = bestVersion;
    LOGS(qr->show, printf("versao %i - tamanho maximo: %i\n\n", qr->version+1, *M_at(version, bestVersion, (unsigned int)qr->correction, (unsigned int) qr->fraseInfo.mode));)

    M_free(version);
}
void readFileChar(char *name, char v[], int tam) {
    FILE *fp;
    if((fp = fopen(name, "rb"))!= NULL) {
        fread(v, tam, sizeof(char), fp);
        fclose(fp);
    } else
        fprintf(stdout, "erro ao abrir o arquivo");
}
void NumericEncode(QRInfo *qr);
void fromDecimal(int base, int dec, char *bits, int tam);
void AlphanumericEncode(QRInfo *qr);
void ByteEncode(QRInfo *qr);
void SetBits(QRInfo *qr) {
    qr->fraseInfo.bits.strFinal.tamBits = BITS_MODE;
    qr->fraseInfo.bits.modeInd = (unsigned char*) calloc(BITS_MODE, sizeof(unsigned char));
    switch(qr->fraseInfo.mode) {
        case NUMERIC:
            qr->fraseInfo.bits.modeInd = "0001";
            NumericEncode(qr);
            qr->fraseInfo.bits.countInd.tamBits = 10;
            break;
        case ALPHANUMERIC:
            qr->fraseInfo.bits.modeInd = "0010";
            AlphanumericEncode(qr);
            qr->fraseInfo.bits.countInd.tamBits = 9;
            break;
        case BYTE_MODE:
            qr->fraseInfo.bits.modeInd = "0100";
            ByteEncode(qr);
            qr->fraseInfo.bits.countInd.tamBits = 8;
            break;
    }
    qr->fraseInfo.bits.strFinal.tamBits += qr->fraseInfo.bits.countInd.tamBits + qr->fraseInfo.bits.modeEncode.tamBits;

    qr->fraseInfo.bits.countInd.elements = (unsigned char*) calloc(qr->fraseInfo.bits.countInd.tamBits+1, sizeof(unsigned char));
    qr->fraseInfo.bits.strFinal.elements = (unsigned char*) calloc(qr->fraseInfo.bits.strFinal.tamBits+1, sizeof(unsigned char));

    fromDecimal(BINARIO, qr->fraseInfo.tamanho, qr->fraseInfo.bits.countInd.elements, qr->fraseInfo.bits.countInd.tamBits);
    strcat(qr->fraseInfo.bits.strFinal.elements, qr->fraseInfo.bits.modeInd);
    strcat(qr->fraseInfo.bits.strFinal.elements, qr->fraseInfo.bits.countInd.elements);

    strcat(qr->fraseInfo.bits.strFinal.elements, qr->fraseInfo.bits.modeEncode.elements);
}
void fromDecimal(int base, int dec, char *bits, int tam) {
    int i;
    for(i=tam-1; i>=0; i--) {
        bits[i]=dec%base+'0';
        dec/=base;
        if(bits[i]>'9')
            bits[i]='A'-1+(bits[i]-'9');
    }
    bits[tam]=0;
}

int strToInt(char *bits);
void NumericEncode(QRInfo *qr) {
    LOGS(qr->show, printf("\t----Modo Numerico---\n");)
    int grupos3 = qr->fraseInfo.tamanho/3, bitsporgrupo = 0;
    switch(qr->fraseInfo.tamanho%3) {
        case 1:
            bitsporgrupo = 4;
            break;
        case 2:
            bitsporgrupo = 7;
            break;
    }
    int nGrupos = grupos3 + !!bitsporgrupo;
    qr->fraseInfo.bits.modeEncode.tamBits = grupos3*10 + bitsporgrupo;
    qr->fraseInfo.bits.modeEncode.elements = (unsigned char*)calloc(qr->fraseInfo.bits.modeEncode.tamBits+1,sizeof(unsigned char));

    Matrix *aux;
    aux = M_create(1, nGrupos, 3);
    M_fill(aux, qr->fraseInfo.text, qr->fraseInfo.text + qr->fraseInfo.tamanho);

    unsigned char number[4];
    unsigned char *auxBits;
    auxBits = (unsigned char*) calloc(10, sizeof(unsigned char));
    int i, index;

    for(index=0; index<nGrupos; index++) {
        for(i=0; i<3; i++)
            number[i] = *M_at(aux, _1, index, i);
        number[i]=0;

        LOGS(qr->show, printf("*%s -> ", number);)
        if(index!= nGrupos-1)
            fromDecimal(2, strToInt(number), auxBits, 10);
        else
            fromDecimal(2, strToInt(number), auxBits, bitsporgrupo);
        LOGS(qr->show, printf("*%s\n", auxBits);)
        strcat(qr->fraseInfo.bits.modeEncode.elements, auxBits);
    }
    free(auxBits);
    M_free(aux);
    LOGS(qr->show, printf("\t-------------------\n\n");)
}
int strToInt(char *bits) {
    int dec=0, i;
    for(i=0; bits[i]; i++) {
        if(bits[i]>='0' && bits[i]<='9') {
            dec=dec*10+(bits[i]-'0');
        }
    }
    return dec;
}
int posicaoCaractere(char c);
void AlphanumericEncode(QRInfo *qr) {
    LOGS(qr->show, printf("\t----Modo AlphaNumerico---\n");)
    int row = qr->fraseInfo.tamanho/2 + !!(qr->fraseInfo.tamanho%2);

    Matrix *aux;
    aux = M_create(1, row,2);
    M_fill(aux, qr->fraseInfo.text, qr->fraseInfo.text+qr->fraseInfo.tamanho);

    unsigned char *bits;
    bits = (unsigned char*)calloc(11, sizeof(unsigned char));
    qr->fraseInfo.bits.modeEncode.tamBits = 11*(qr->fraseInfo.tamanho/2) + 6*(qr->fraseInfo.tamanho%2);
    qr->fraseInfo.bits.modeEncode.elements = (unsigned char*)calloc(qr->fraseInfo.bits.modeEncode.tamBits+1, sizeof(unsigned char));

    LOGS(qr->show, printf("Fez a conta para com as posicoes de cada par e transforma em binario:\n");)
    int num, i;
    for(i=0; i<row; i++) {
        if(i==row-1 && qr->fraseInfo.tamanho%2) {
            num = posicaoCaractere(*M_at(aux, _1, i, 0));
            LOGS(qr->show, fprintf(stdout, "posicao da letra = %i ", num);)
            fromDecimal(2, num, bits, 6);
            LOGS(qr->show, printf("--- %s\n", bits);)
        } else {
            num = 45 * posicaoCaractere(*M_at(aux, _1, i, 0)) + posicaoCaractere(*M_at(aux, _1, i, 1));
            LOGS(qr->show, printf("%i- 45* %i (%c) + %i (%c) = %i ", i, posicaoCaractere(*M_at(aux, _1, i, 0)), *M_at(aux, _1, i, 0), posicaoCaractere(*M_at(aux, _1, i, 1)), *M_at(aux, _1, i, 1), num);)
            fromDecimal(2, num, bits, 11);
            LOGS(qr->show, printf("--- %s\n", bits);)
        }
        strcat(qr->fraseInfo.bits.modeEncode.elements, bits);
    }

    free(bits);
    M_free(aux);
    LOGS(qr->show, printf("\n\t-------------------\n\n");)
}
int posicaoCaractere(char c) {
    int i;
    for(i=0; i<44; i++)
        if(c==caracteres[i])
            return i;
}
void ByteEncode(QRInfo *qr) {
    LOGS(qr->show, printf("\t----Modo Byte---\n");)
    qr->fraseInfo.bits.modeEncode.tamBits = 8*qr->fraseInfo.tamanho;

    qr->fraseInfo.bits.modeEncode.elements = (unsigned char*)calloc(qr->fraseInfo.bits.modeEncode.tamBits+1, sizeof(unsigned char));
    int i, num;
    unsigned char bits[8];
    for(i=0; i< qr->fraseInfo.tamanho; i++) {
        num = qr->fraseInfo.text[i];
        fromDecimal(BINARIO, num, bits, 8);
        LOGS(qr->show, printf("%c - %x - %i - %s\n", num, num, num, bits);)
        strcat(qr->fraseInfo.bits.modeEncode.elements, bits);
    }
    LOGS(qr->show, printf("\n\t-------------------\n\n");)
}

void Teste_writeFile(char *name, int *v, int tam);
int toDecimal(int base, char bin[]);
void setCodigosCorretores(QRInfo *qr);
void SetCodeWords(QRInfo *qr) {
    LOGS(qr->show, printf("\t----Set Code Words---\n");)
    char v[36];
    readFileChar("ErrorCorrectionTable.bin", v, 36);

    Matrix *tabela;
    tabela = M_create(3, 4, 3);
    M_fill(tabela, v, v+36);

    qr->cw.blocks = (unsigned char) *M_at(tabela, qr->version, qr->correction, BLOCKS_COLUMN);
    qr->cw.palavrasCodigo.tamBits = (int)*M_at(tabela, qr->version, qr->correction, CW_COLUMN);
    qr->cw.codigosCorretores.tamBits = (int)*M_at(tabela, qr->version, qr->correction, NUM_CODIGOS_CORRETORES)*qr->cw.blocks;

    qr->cw.pcPerBlock = (unsigned char) qr->cw.palavrasCodigo.tamBits / qr->cw.blocks;
    qr->cw.ccPerBlock = (unsigned char)*M_at(tabela, qr->version, qr->correction, NUM_CODIGOS_CORRETORES);
    M_free(tabela);

    LOGS(qr->show, Q(qr->cw.blocks, "blocos de acordo com a TABELA"))

    qr->cw.palavrasCodigo.elements = (unsigned char*)calloc(qr->cw.palavrasCodigo.tamBits, sizeof(unsigned char));

    int index, i, grupos_8 = qr->fraseInfo.bits.strFinal.tamBits/8 + !!(qr->fraseInfo.bits.strFinal.tamBits%8);
    Matrix *strBits;
    strBits = M_create(1, grupos_8, 8);
    M_fill(strBits, qr->fraseInfo.bits.strFinal.elements, qr->fraseInfo.bits.strFinal.elements + qr->fraseInfo.bits.strFinal.tamBits);


    char number[9];
    int enchimento[]= {236, 17}, zero = 0;

    for(index=0; index<qr->cw.palavrasCodigo.tamBits; index++) {
        if(index<grupos_8) {
            for(i=0; i<8; i++) {
                if(index*strBits->C + i < qr->fraseInfo.bits.strFinal.tamBits)
                    number[i] = *M_at(strBits, _1, index, i);
                else
                    number[i] = '0';
            }
            number[i]=0;

            qr->cw.palavrasCodigo.elements[index] = toDecimal(2, number);

        } else {
            qr->cw.palavrasCodigo.elements[index] = enchimento[zero];
            zero = !zero;
        }
    }
    M_free(strBits);


    setCodigosCorretores(qr);
    LOGS(qr->show, printf("\n\t-------------------\n\n");)
}
int toDecimal(int base, char bin[]) {
    int i, dec=0, potencia=1, b;
    for(i=strlen(bin)-1; i>=0; i--) {
        if(bin[i]<='9')
            b=bin[i]-'0';
        else
            b=bin[i]-'A'+10;

        dec+=b*potencia;
        potencia*=base;
    }
    return dec;
}

void atribuiVetores(VetorChar dest, int inicio, unsigned char *dini, unsigned char *dend);
void setCodigosCorretores(QRInfo *qr) {
    int i, index=0, bloco;
    qr->cw.codigosCorretores.elements = (unsigned char*)calloc(qr->cw.codigosCorretores.tamBits, sizeof(unsigned char));

    LOGS(qr->show, printf("\t----Set Codigos Corretores---\n");)
    unsigned short *dados;
    dados = (unsigned short*)calloc(qr->cw.pcPerBlock, sizeof(unsigned short));
    unsigned char *cod;


    for(bloco=0; bloco <qr->cw.blocks; bloco++) {
        LOGS(qr->show, printf("Palavras codigo do bloco %i [dados]:\n", bloco+1);)
        for(i=0; i<qr->cw.pcPerBlock; i++) {
            dados[i] = (unsigned short) qr->cw.palavrasCodigo.elements[index];
            LOGS(qr->show, printf("%i ", dados[i]);)
            index++;
        }

        cod = CodigosCorretores(dados, (unsigned short)qr->cw.pcPerBlock, (unsigned short)qr->cw.ccPerBlock);

        atribuiVetores(qr->cw.codigosCorretores, bloco*qr->cw.ccPerBlock, cod, cod +qr->cw.ccPerBlock);

        LOGS(qr->show, printf("\n\nCodigos corretores do bloco %i [qr->cw.codigosCorretores.elements]:\n", bloco+1);)
        LOGS(qr->show, Teste_printTableUC(qr->cw.codigosCorretores.elements + bloco*qr->cw.ccPerBlock, (int) qr->cw.ccPerBlock); )
        LOGS(qr->show, Q(qr->cw.pcPerBlock, "palavras codigo por bloco ai em cima"))
        LOGS(qr->show, Q(qr->cw.ccPerBlock, "codigos corretores por bloco ai em cima"))
        LOGS(qr->show, printf("\n\n");)
    }

    free(cod);
    free(dados);
    LOGS(qr->show, printf("\n\t-------------------\n\n");)
}
void atribuiVetores(VetorChar dest, int inicio, unsigned char *dini, unsigned char *dend) {
    int i, index=0;
    for(i=inicio; i<dest.tamBits; i++)
        if(dini+index<dend)
            dest.elements[i] = dini[index++];
}

void Teste_writeFile(char *name, int *v, int tam) {
    FILE *fp;
    if((fp = fopen(name, "wb"))!= NULL) {
        fwrite(v, tam, sizeof(int), fp);
        fclose(fp);
    } else
        fprintf(stdout, "erro ao abrir o arquivo");
}

void finalMsgToBits(QRInfo *qr);
void StructureFinalMessage(QRInfo *qr) {

    qr->cw.interleavedPC.elements = (unsigned char*)calloc(qr->cw.palavrasCodigo.tamBits, sizeof(unsigned char));
    qr->cw.interleavedPC.tamBits = qr->cw.palavrasCodigo.tamBits;
    qr->cw.interleavedCC.elements = (unsigned char*)calloc(qr->cw.codigosCorretores.tamBits, sizeof(unsigned char));
    qr->cw.interleavedCC.tamBits = qr->cw.codigosCorretores.tamBits;
    qr->cw.finalMessage.elements = (unsigned char*)calloc(qr->cw.palavrasCodigo.tamBits+qr->cw.codigosCorretores.tamBits, sizeof(unsigned char));
    qr->cw.finalMessage.tamBits = qr->cw.palavrasCodigo.tamBits+qr->cw.codigosCorretores.tamBits;

    int i=0, numBloco=0, j, index=0;
    LOGS(qr->show, printf("\t----Structure Final Message---\n");)
    Matrix *pc;
    pc = M_create(1, (unsigned int)qr->cw.blocks, (unsigned int)qr->cw.pcPerBlock);
    LOGS(qr->show, printf("\n\nOrganizando palavras codigo:\n");)
    M_fill(pc, qr->cw.palavrasCodigo.elements, qr->cw.palavrasCodigo.elements+qr->cw.palavrasCodigo.tamBits);
    for(j=0; j<(int)qr->cw.pcPerBlock; j++)
        for(numBloco=0; numBloco<(int)qr->cw.blocks && numBloco*pc->C+ j < qr->cw.palavrasCodigo.tamBits; numBloco++) {
            qr->cw.interleavedPC.elements[i] = *M_at(pc, _1, numBloco, j);
            qr->cw.finalMessage.elements[index] = qr->cw.interleavedPC.elements[i];
            i++;
            index++;
        }

    LOGS(qr->show, Teste_printTableUC(qr->cw.interleavedPC.elements, qr->cw.interleavedPC.tamBits);)


    i=0;
    Matrix *cc;
    cc = M_create(1, (unsigned int)qr->cw.blocks, (unsigned int)qr->cw.ccPerBlock);
    LOGS(qr->show, fprintf(stdout, "\n\nOrganizando codigos corretores:\n");)
    M_fill(cc, qr->cw.codigosCorretores.elements, qr->cw.codigosCorretores.elements+qr->cw.codigosCorretores.tamBits);

    for(j=0; j<(int)qr->cw.ccPerBlock; j++)
        for(numBloco=0; numBloco<(int)qr->cw.blocks && numBloco*cc->C+ j < qr->cw.codigosCorretores.tamBits; numBloco++) {
            qr->cw.interleavedCC.elements[i] = *M_at(cc, _1, numBloco, j);
            qr->cw.finalMessage.elements[index] = qr->cw.interleavedCC.elements[i];
            i++;
            index++;
        }

    LOGS(qr->show, Teste_printTableUC(qr->cw.interleavedCC.elements, qr->cw.interleavedCC.tamBits);)

    LOGS(qr->show, fprintf(stdout, "\n\nFinal msg:\n\n");)
    LOGS(qr->show, Teste_printTableUC(qr->cw.finalMessage.elements, qr->cw.finalMessage.tamBits);)

    M_free(pc);
    M_free(cc);
    LOGS(qr->show, printf("\n\t-------------------\n\n");)
    finalMsgToBits(qr);
}
void finalMsgToBits(QRInfo *qr) {
    LOGS(qr->show, printf("\t----Passing Structure Final Message to Bits---\n");)

    int bitsRestantes=0, i, bit;
    if(qr->version!=0)
        bitsRestantes = 7;
    qr->cw.finalMsgBits.tamBits = 8*qr->cw.finalMessage.tamBits + bitsRestantes;
    qr->cw.finalMsgBits.elements = (unsigned char*)calloc(qr->cw.finalMsgBits.tamBits+1, sizeof(unsigned char));

    int num;

    for(i=0; i<qr->cw.finalMessage.tamBits; i++) {
        num = (int)qr->cw.finalMessage.elements[i];
        fromDecimal(BINARIO, num, qr->cw.finalMsgBits.elements+8*i, 8);
    }
    for(i= i*8; i<qr->cw.finalMsgBits.tamBits; i++) {
        qr->cw.finalMsgBits.elements[i]= '0';
    }
    qr->cw.finalMsgBits.elements[i]=0;
    LOGS(qr->show, printf("\n\t-------------------\n\n");)
}





void drawFinderPattern(QRInfo *qr, int x, int y);
void AddFinderPatterns(QRInfo *qr) {
    drawFinderPattern(qr, 0, 0);
    drawFinderPattern(qr, (int)qr->image.m->C - 7, 0);
    drawFinderPattern(qr, 0, (int)qr->image.m->R - 7);
}
void drawFinderPattern(QRInfo *qr, int x, int y) {
    int i, lado=7;
    for(i=0; i<lado; i++) {
        *M_at(qr->image.m, _1, x+i, y) = *M_at(qr->image.m, _1, x, y+i) = *M_at(qr->image.m, _1, x+i, y+lado-1) = *M_at(qr->image.m, _1, x+lado-1, y+i) = BLACK;
        if(i<lado-2)
            *M_at(qr->image.m, _1, x+i+1, y+1) = *M_at(qr->image.m, _1, x+i+1, y+lado-2) = *M_at(qr->image.m, _1, x+1, y+1+i) = *M_at(qr->image.m, _1, x+lado-2, y+1+i) = WHITE;
    }
    lado = 3;
    for(i=0; i<lado; i++)
        *M_at(qr->image.m, _1, x+2+i, y+2) = *M_at(qr->image.m, _1, x+2+i, y+2+lado-1) = *M_at(qr->image.m, _1, x+2, y+2+i) = *M_at(qr->image.m, _1, x+2+lado-1, y+2+i) = BLACK;

    *M_at(qr->image.m, _1, x+3, y+3) = BLACK;


    lado = 7;
    for(i=0; i<=lado; i++) {
        if(x==0 && y==0)
            *M_at(qr->image.m, _1, y+lado, x+i) = *M_at(qr->image.m, _1, y+i, x+lado) = WHITE;
        else if(x==(int)qr->image.m->C - 7 && y==0)
            *M_at(qr->image.m, _1, y+i, x-1) = *M_at(qr->image.m, _1, y+lado, x+i-1) = WHITE;
        else if(x==0 && y==(int)qr->image.m->R - 7)
            *M_at(qr->image.m, _1, y-1, x+i) = *M_at(qr->image.m, _1, y+i-1, x+lado) = WHITE;
    }
}

void drawSquare(QRInfo *qr, int y, int x, int lado, unsigned char MODULE);
void drawAlignmentPattern(QRInfo *qr, int linha, int coluna);
void AddAlignmentPatterns(QRInfo *qr) {

    int coord[2],i, j;
    switch(qr->version) {
        case _2:
            coord[0]=6;
            coord[1]=18;
            break;
        case _3:
            coord[0]=6;
            coord[1]=22;
            break;
    }
    for(i=0; i<2; i++)
        for(j=0; j<2; j++)
            if(*M_at(qr->image.m,_1, coord[i], coord[j])!=BLACK && *M_at(qr->image.m,_1, coord[i], coord[j])!=WHITE)
                drawAlignmentPattern(qr, coord[i], coord[j]);
}
void drawAlignmentPattern(QRInfo *qr, int linha, int coluna) {
    drawSquare(qr, linha, coluna, 1, BLACK);
    drawSquare(qr, linha-1, coluna-1, 3, WHITE);
    drawSquare(qr, linha-2, coluna-2, 5, BLACK);
}
void drawSquare(QRInfo *qr, int y, int x, int lado, unsigned char MODULE) {
    int i;
    for(i=0; i<lado; i++) {

        *M_at(qr->image.m, _1, x+i, y) = *M_at(qr->image.m, _1, x, y+i) = *M_at(qr->image.m, _1, x+i, y+lado-1) = *M_at(qr->image.m, _1, x+lado-1, y+i) = MODULE;
    }
}

void AddTimingPatterns(QRInfo *qr) {
    unsigned char module[]= {BLACK, WHITE}, i, j=6;
    for(i=6; i<qr->image.m->R; i++) {
        if(*M_at(qr->image.m,_1, i, j)!=BLACK && *M_at(qr->image.m,_1, i, j)!=WHITE) {
            *M_at(qr->image.m,_1, i, j) = module[(i+j)%2];
            *M_at(qr->image.m,_1, j, i) = module[(i+j)%2];
        }
    }
}

void drawLine(QRInfo *qr, Coord inicio, Coord fim, unsigned char MODULE);
void AddReservedAreas(QRInfo *qr) {

    Coord i= {8, 0}, f= {8, 8};
    drawLine(qr, i, f, 'F');
    i.row=0;
    i.col=8;
    f.row=8;
    f.col=8;
    drawLine(qr, i, f, 'F');
    i.row= 8;
    i.col=qr->image.m->C-8;
    f.row=8;
    f.col=qr->image.m->C-1;
    drawLine(qr, i, f, 'F');
    i.row= qr->image.m->C-8;
    i.col=8;
    f.row=qr->image.m->C-1;
    f.col=8;
    drawLine(qr, i, f, 'F');



}
void drawLine(QRInfo *qr, Coord inicio, Coord fim, unsigned char MODULE) {
    int i;
    if(inicio.row == fim.row) {
        for(i=inicio.col; i<=fim.col; i++)
            if(*M_at(qr->image.m, _1, inicio.row, i)!=BLACK && *M_at(qr->image.m, _1, inicio.row, i)!=WHITE)
                *M_at(qr->image.m, _1, inicio.row, i) = MODULE;

    } else
        for(i=inicio.row; i<=fim.row; i++)
            if(*M_at(qr->image.m, _1, i, inicio.col)!=BLACK && *M_at(qr->image.m, _1, i, inicio.col)!=WHITE)
                *M_at(qr->image.m, _1, i, inicio.col) = MODULE;
}

void GetDataPositions(QRInfo *qr) {
    qr->dataPosition =(Coord*) calloc(qr->cw.finalMsgBits.tamBits, sizeof(Coord));
    int i, j, index=0;
    for(i=0; i<qr->image.m->R; i++) {
        for(j=0; j<qr->image.m->C; j++) {
            if(!(int)*M_at(qr->image.m, _1, i, j)) {
                qr->dataPosition[index].row = i;
                qr->dataPosition[index].col = j;

                index++;
            }
        }
    }
}

void downwardPlacement(QRInfo *qr, Coord pos, int *index);
void upwardPlacement(QRInfo *qr, Coord pos, int *index);
void PlaceDataBits(QRInfo *qr) {
    int index=0;
    Coord pos= {qr->image.m->R-1,qr->image.m->C-1};
    while(pos.col>=0) {
        upwardPlacement(qr, pos, &index);
        pos.col -= 2;
        pos.row = 0;
        if(pos.col==6)
            pos.col--;
        downwardPlacement(qr, pos, &index);
        pos.col -= 2;
        pos.row = qr->image.m->R-1;
    }
}
void upwardPlacement(QRInfo *qr, Coord pos, int *index) {
    int i, j;
    for(i=pos.row; i>=0; i--)
        for(j=pos.col; j>=pos.col-1; j--) {
            if(!(int)*M_at(qr->image.m, _1, i, j)) {
                *M_at(qr->image.m, _1, i, j) = qr->cw.finalMsgBits.elements[*index];
                *index+=1;
            }
        }
}
void downwardPlacement(QRInfo *qr, Coord pos, int *index) {
    int i, j;
    for(i=pos.row; i<qr->image.m->R; i++) {
        for(j=pos.col; j>=pos.col-1; j--) {
            if(!(int)*M_at(qr->image.m, _1, i, j)) {
                *M_at(qr->image.m, _1, i, j) = qr->cw.finalMsgBits.elements[*index];
                *index+=1;
            }
        }
    }
}



void evaluationCondition1(QRInfo *qr, int *penalty);
void evaluationCondition2(QRInfo *qr, int *penalty);
void evaluationCondition3(QRInfo *qr, int *penalty);
void evaluationCondition4(QRInfo *qr, int *penalty);

void DeterminingBestMask(QRInfo *qr) {
    int i, penalty[8], menor;

    qr->image.mcopia = M_create(qr->image.m->E, qr->image.m->R, qr->image.m->C);
    M_fill(qr->image.mcopia, qr->image.m->elements, qr->image.m->elements + qr->image.m->E*qr->image.m->R*qr->image.m->C);

    for(i=0; i<8; i++) {
        qr->dataMask.mask = (unsigned char) i;
        FormatInformation(qr);
        PutFormatStringBits(qr, qr->image.mcopia);
        AddMask(qr, qr->image.mcopia);

        evaluationCondition1(qr, &penalty[i]);
        printf("mask %i - penalty #1: %i\n", qr->dataMask.mask, penalty[i]);

        evaluationCondition2(qr, &penalty[i]);
        printf("mask %i - penalty #2: %i\n", qr->dataMask.mask, penalty[i]);

        evaluationCondition3(qr, &penalty[i]);
        printf("mask %i - penalty #3: %i\n", qr->dataMask.mask, penalty[i]);
        evaluationCondition4(qr, &penalty[i]);
        printf("mask %i - penalty #4: %i\n", qr->dataMask.mask, penalty[i]);

    }

    menor = penalty[0];
    for(i=0; i<8; i++) {
        if(menor >= penalty[i]) {
            menor = penalty[i];
            qr->dataMask.mask = (unsigned char)i;
        }
    }
    M_free(qr->image.mcopia);
}
void FormatInformation(QRInfo *qr) {
    qr->dataMask.errorBits.tamBits = 5;
    qr->dataMask.errorBits.elements = (unsigned char*)calloc((int) qr->dataMask.errorBits.tamBits+1, sizeof(unsigned char));
    switch (qr->correction) {
        case _L:
            qr->dataMask.errorBits.elements[0] = '0';
            qr->dataMask.errorBits.elements[1] = '1';
            break;
        case _M:
            qr->dataMask.errorBits.elements[0] = '0';
            qr->dataMask.errorBits.elements[1] = '0';
            break;
        case _Q:
            qr->dataMask.errorBits.elements[0] = '1';
            qr->dataMask.errorBits.elements[1] = '1';
            break;
        case _H:
            qr->dataMask.errorBits.elements[0] = '1';
            qr->dataMask.errorBits.elements[1] = '0';
            break;
    }
    fromDecimal(BINARIO, (int) qr->dataMask.mask, qr->dataMask.errorBits.elements+2, 3);

    printf("%s\n\n", qr->dataMask.errorBits.elements);

    qr->dataMask.codStringFormat.tamBits = 16;
    switch(qr->correction) {
        case _L:
            switch(qr->dataMask.mask) {
                case 0:
                    qr->dataMask.codStringFormat.elements = "111011111000100";
                    break;
                case 1:
                    qr->dataMask.codStringFormat.elements = "111001011110011";
                    break;
                case 2:
                    qr->dataMask.codStringFormat.elements = "111110110101010";
                    break;
                case 3:
                    qr->dataMask.codStringFormat.elements = "111100010011101";
                    break;
                case 4:
                    qr->dataMask.codStringFormat.elements = "110011000101111";
                    break;
                case 5:
                    qr->dataMask.codStringFormat.elements = "110001100011000";
                    break;
                case 6:
                    qr->dataMask.codStringFormat.elements = "110110001000001";
                    break;
                case 7:
                    qr->dataMask.codStringFormat.elements = "110100101110110";
                    break;
            }
            break;
        case _M:
            switch(qr->dataMask.mask) {
                case 0:
                    qr->dataMask.codStringFormat.elements = "101010000010010";
                    break;
                case 1:
                    qr->dataMask.codStringFormat.elements = "101000100100101";
                    break;
                case 2:
                    qr->dataMask.codStringFormat.elements = "101111001111100";
                    break;
                case 3:
                    qr->dataMask.codStringFormat.elements = "101101101001011";
                    break;
                case 4:
                    qr->dataMask.codStringFormat.elements = "100010111111001";
                    break;
                case 5:
                    qr->dataMask.codStringFormat.elements = "100000011001110";
                    break;
                case 6:
                    qr->dataMask.codStringFormat.elements = "100111110010111";
                    break;
                case 7:
                    qr->dataMask.codStringFormat.elements = "100101010100000";
                    break;
            }
            break;
        case _Q:
            switch(qr->dataMask.mask) {
                case 0:
                    qr->dataMask.codStringFormat.elements = "011010101011111";
                    break;
                case 1:
                    qr->dataMask.codStringFormat.elements = "011000001101000";
                    break;
                case 2:
                    qr->dataMask.codStringFormat.elements = "011111100110001";
                    break;
                case 3:
                    qr->dataMask.codStringFormat.elements = "011101000000110";
                    break;
                case 4:
                    qr->dataMask.codStringFormat.elements = "010010010110100";
                    break;
                case 5:
                    qr->dataMask.codStringFormat.elements = "010000110000011";
                    break;
                case 6:
                    qr->dataMask.codStringFormat.elements = "010111011011010";
                    break;
                case 7:
                    qr->dataMask.codStringFormat.elements = "010101111101101";
                    break;
            }
            break;
        case _H:
            switch(qr->dataMask.mask) {
                case 0:
                    qr->dataMask.codStringFormat.elements = "001011010001001";
                    break;
                case 1:
                    qr->dataMask.codStringFormat.elements = "001001110111110";
                    break;
                case 2:
                    qr->dataMask.codStringFormat.elements = "001110011100111";
                    break;
                case 3:
                    qr->dataMask.codStringFormat.elements = "001100111010000";
                    break;
                case 4:
                    qr->dataMask.codStringFormat.elements = "000011101100010";
                    break;
                case 5:
                    qr->dataMask.codStringFormat.elements = "000001001010101";
                    break;
                case 6:
                    qr->dataMask.codStringFormat.elements = "000110100001100";
                    break;
                case 7:
                    qr->dataMask.codStringFormat.elements = "000100000111011";
                    break;
            }
            break;
    }

    printf("%s\n\n", qr->dataMask.codStringFormat.elements);


}
void PutFormatStringBits(QRInfo *qr, Matrix *matrix) {
    unsigned int i, indexLine=0, indexCol=0;
    for(i=0; i<matrix->C; i++) {
        if(*M_at(matrix, _1, matrix->R-1-i, 8)=='F')
            *M_at(matrix, _1, matrix->R-1-i, 8) = qr->dataMask.codStringFormat.elements[indexCol++];
        if(*M_at(matrix, _1, 8, i)=='F' && i!=8) {
            *M_at(matrix, _1, 8, i) = qr->dataMask.codStringFormat.elements[indexLine++];
        }

    }
}

void evaluationCondition1(QRInfo *qr, int *penalty) {
    unsigned int i, j;
    int samemodule = 1;
    *penalty = 0;
    for (i = 0; i < qr->image.mcopia->R; i++) {
        for (j = 0; j < qr->image.mcopia->C - 1; j++) {
            if (*M_at(qr->image.mcopia, _1, i, j) == *M_at(qr->image.mcopia, _1, i, j + 1)) {
                samemodule++;
                if (j == qr->image.mcopia->C - 2 && samemodule >= 5)
                    *penalty = *penalty + 3 + (!!(samemodule - 5) * (samemodule - 5));

            } else {
                if (samemodule >= 5)
                    *penalty = *penalty + 3 + (!!(samemodule - 5) * (samemodule - 5));
                samemodule = 1;

            }

        }

        samemodule = 1;
    }
    printf("*penalty line : %i\n", *penalty);

    for (j = 0; j < qr->image.mcopia->C; j++){
        for (i = 0; i < qr->image.mcopia->R - 1; i++) {
            if (*M_at(qr->image.mcopia, _1, i, j) == *M_at(qr->image.mcopia, _1, i+1, j)) {
                samemodule++;
                if (i == qr->image.mcopia->R - 2 && samemodule >= 5)
                    *penalty = *penalty + 3 + (!!(samemodule - 5) * (samemodule - 5));

            } else {
                if (samemodule >= 5)
                    *penalty = *penalty + 3 + (!!(samemodule - 5) * (samemodule - 5));
                samemodule = 1;

            }
        }
        samemodule = 1;
    }
    printf("*penalty col + line: %i\n", *penalty);
}
void evaluationCondition2(QRInfo *qr, int *penalty) {
    int i, j, square2x2=0;
    for(i=0; i<qr->image.mcopia->R-1; i++) {
        for(j=0; j<qr->image.mcopia->C-1; j++) {
            if(*M_at(qr->image.mcopia, _1, i, j)==*M_at(qr->image.mcopia, _1, i, j+1)&&
               *M_at(qr->image.mcopia, _1, i, j)==*M_at(qr->image.mcopia, _1, i+1, j)&&
               *M_at(qr->image.mcopia, _1, i, j)==*M_at(qr->image.mcopia, _1, i+1, j+1))
                square2x2++;
        }
    }
    printf("mask %i - square2x2 = %i\n", qr->dataMask.mask, square2x2);
    *penalty = *penalty + square2x2*3;
}
void evaluationCondition3(QRInfo *qr, int *penalty) {
int i, j, auxi, index1=0, index2=0;
    unsigned char pattern1[]="10111010000";
    unsigned char pattern2[]="00001011101";
    for(i=0; i<qr->image.mcopia->R; i++){
        for(j=0; j<qr->image.mcopia->C-11; j++){
            for(auxi = j; auxi<j+11; auxi++){
                if(*M_at(qr->image.mcopia, _1, i, auxi)==pattern1[index1]){
                    index1++;
                    if(index1==11) {
                        *penalty = *penalty + 40;
                        index1 = 0;
                    }
                }else{
                    index1 = 0;
                }
                if(*M_at(qr->image.mcopia, _1, i, auxi)==pattern2[index2]){
                    index2++;
                    if(index2==11){
                        *penalty = *penalty + 40;
                        index2=0;
                    }
                }else{
                    index2 = 0;
                }
            }
            index1 = 0; index2 = 0;
        }
        index1 = 0; index2 = 0;
    }



    for(j=0; j<qr->image.mcopia->C; j++){
        for(i=0; i<qr->image.mcopia->R-11; i++){
            for(auxi = i; auxi<i+11; auxi++){
                if(*M_at(qr->image.mcopia, _1, auxi, j)==pattern1[index1]){
                    index1++;
                    if(index1==11) {
                        *penalty = *penalty + 40;
                        index1 = 0;
                    }
                }else{
                    index1 = 0;
                }
                if(*M_at(qr->image.mcopia, _1, auxi, j)==pattern2[index2]){
                    index2++;
                    if(index2==11){
                        *penalty = *penalty + 40;
                        index2=0;
                    }
                }else{
                    index2 = 0;
                }
            }
            index1 = 0; index2 = 0;
        }
        index1 = 0; index2 = 0;
    }

}
void evaluationCondition4(QRInfo *qr, int *penalty) {
    int totalmodules = qr->image.mcopia->R*qr->image.mcopia->R, darkmodules=0;
    unsigned int i, j, percent;
    for(i=0; i<qr->image.mcopia->R; i++) {
        for(j=0; j<qr->image.mcopia->C; j++) {
            if(*M_at(qr->image.mcopia, _1, i, j) == BLACK)
                darkmodules++;
        }
    }
    percent = (darkmodules*100)/totalmodules;
    int previousM5 = (percent%5)? percent-5 : percent - (percent%5);
    int nextM5 = percent + (5-(percent%5));

    int num1, num2;
    num1= (unsigned)(previousM5 - 50)/5;
    num2 = (unsigned)(nextM5 -50)/5;
    *penalty = *penalty + ((num1<num2)? num1*10 : num2*10);
}

void AddMask(QRInfo *qr, Matrix *matrix) {
    int index=0, i, j, regra;
    for(index=0; index<qr->cw.finalMsgBits.tamBits; index++) {
        i=qr->dataPosition[index].row;
        j=qr->dataPosition[index].col;
        switch(qr->dataMask.mask) {
            case 0:
                regra = (i + j)%2;
                break;
            case 1:
                regra = (i)%2;
                break;
            case 2:
                regra = (j)%3;
                break;
            case 3:
                regra = (i + j)%3;
                break;
            case 4:
                regra = ((i/2) + (j/3))%2;
                break;
            case 5:
                regra = (i*j)%2 + (i*j)%3;
                break;
            case 6:
                regra = ((i*j)%2 + (i*j)%3)%2;
                break;
            case 7:
                regra = ((i + j)%2 + (i*j)%3)%2;
                break;
        }
        if(regra == 0) {
            *M_at(matrix, _1, i, j) = (!(*M_at(matrix, _1, i, j)-'0') )+ '0';
        }
    }

}



void readFileInt(char *name, int *num);
void writeFileInt(char *name, int num);
void saveImage(Image image) {
    FILE *fp;
    int i, j, num;
    readFileInt("Enumeration.bin", &num);
    num = num + 1;
    if(num==1000){
        num=1;
    }
    writeFileInt("Enumeration.bin", num);

    fromDecimal(DECIMAL, num, image.name + 6, 3);

    switch(image.type) {
        case PBM:
            strcat(image.name, ".pbm");
            break;
        case PGM:
            strcat(image.name, ".pgm");
            break;
        case PPM:
            strcat(image.name, ".ppm");
            break;
    }

    printf("image name: %s\n", image.name);

    if((fp = fopen(image.name, "w"))!= NULL) {
        fprintf(fp, "P%d\n%d %d\n", image.type, image.m->R+8, image.m->C+8);
        for(i=0; i<image.m->R+8; i++) {
            for(j=0; j<image.m->C+8; j++) {
                if(i<4 || j<4 || i>image.m->R+8-1 -4 || j>image.m->C+8-1 -4)
                    fprintf(fp, "%c ", '0');
                else
                    fprintf(fp, "%d ", !!(int) (*M_at(image.m, _1, i-4, j-4) - '0'));
            }
            fprintf(fp, "\n");
        }
        fclose(fp);
    } else
        fprintf(stdout, "Error: impossible to open the file\n");

    const char command[96] = "C:\\Users\\MULTI_E-FIS_MECS\\Documents\\CodeBlocks-codes\\QRCode_2_FINAL\\";
    strcat(command, image.name);
    printf("%s", command);
    system(command);

}
void readFileInt(char *name, int *num){
    FILE *fp;
    if((fp = fopen(name, "rb"))!= NULL) {
        fread(num, 1, sizeof(int), fp);
        fclose(fp);
    } else
        fprintf(stdout, "erro ao abrir o arquivo");
}
void writeFileInt(char *name, int num){
    FILE *fp;
    if((fp = fopen(name, "wb"))!= NULL) {
        fwrite(&num, 1, sizeof(int), fp);
        fclose(fp);
    } else
        fprintf(stdout, "erro ao abrir o arquivo");
}

#endif
