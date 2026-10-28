#include <iostream>
#include <cstdlib>
#include <string>
#include <stdexcept>
#include <assert.h>
#include <ctime>
#include <unistd.h>

using namespace std;

const int grandezzaMagazzino = 29;
const int quantitaIngrediente = 1;
double budget = 500000;

struct ingredienti {
    string nomeIngredienti [6];
    //int quantitàIngrediente[6]; per semplicità abbiamo deciso che le quantità degli ingredienti sono tutte 1
};

struct allergeni {
    int glutine;
    int latte;
    int molluschi;
    int uova;
    int pesce;
    int arachidi;
    int crostacei;
};

struct piatto {
    string portata;
    string nomePiatto;
    ingredienti ingredienti;
    allergeni allergeni;
    int piattoVegano;
    int piattoVegetariano;
    int piattoReligioni;
};

struct menu {
    piatto piatti[5];
};

struct menuOLd {
    piatto antipasto;
    piatto primo;
    piatto secondo;
    piatto contorno;
    piatto dolce;
};
menu menuSettimana[7];
menu menuVegani[7];
menu menuVegetariani[7];
menu menuReligioni[7];
menu menuAllergeni[7];

piatto listaAntipasti[14];
piatto listaPrimi[14];
piatto listaSecondi[14];
piatto listaContorni[5];
piatto listaDolci[14];

bool menuGlutine = false, menuLatte = false, menuMolluschi = false, menuUova = false, menuPesce = false, menuArachidi = false, menuCrostacei = false;

struct magazzinoSt {
    string nomeIngrediente;
    int quantitaMagazzino;
    double prezzoIngrediente;
};
magazzinoSt magazzino [grandezzaMagazzino];
magazzinoSt carrello [grandezzaMagazzino];

int primaPosizVuotaMagazzino = 0;
int primaPosizVuotaCarrello = 0;

int inserimentoInteri (string stampa, int nMin, int nMax, string errore){       // serve per verificare che nell'input dell'utente non ci siano lettere e il numero inserito sia dentro i limiti scelti
    int scelta;
    while (true){
        cout << stampa << endl;
        string input;
        cin >> input;
        try {
            scelta = stoi(input);
            if (scelta < nMin || scelta > nMax) {
                throw out_of_range(errore);
            }
            break;
        }
        catch (invalid_argument) {
            cout << "Errore: Inserire solo numeri." << endl;
        }
        catch (out_of_range& e) {
            cout << "Errore: " << e.what() << "inserire un numero compreso tra " << nMin << " e " << nMax << endl;
        }
    }
    return scelta;
}

int ricercaMagazzino (string _nomeIngrediente){     // controlla se un ingrediente è gia nel magazzino o no
    for (int i = 0; i < grandezzaMagazzino; i++){
        if (magazzino[i].nomeIngrediente == _nomeIngrediente){
            return i;
        }
    }
    return -1;
}

int ricercaCarrello (string _nomeIngrediente){      // controlla se un ingrediente è gia nel carrello o no
    for (int i = 0; i < grandezzaMagazzino; i++){
        if (carrello[i].nomeIngrediente == _nomeIngrediente){
            return i;
        }
    }
    return -1;
}

void stampaCarrello (){     // stampa il carrello
    cout << "carrello degli ingredienti mancanti: " << endl;
    for (int i = 0; i < primaPosizVuotaCarrello; i++){
        cout << carrello[i].nomeIngrediente << "\t";
        cout << carrello[i].quantitaMagazzino << "\t";
        cout << carrello[i].prezzoIngrediente * carrello[i].quantitaMagazzino << endl;
        
    }
    cout << "budget rimanente: " << budget << endl;
}

void bugdgetFinito (){ // serve in caso di fine dei fondi si richiede all utente di aggiungere altri fondi per acquistare gli ingredienti mancanti
    int fondi = 0;
    if (budget <= 10){
        fondi = inserimentoInteri("i fondi per acqustare le scorte stanno per terminare per favore inserire altri fondi (minimo 10, massimo 500000)", 10, 500000, "Numero non valido");
        budget += fondi;
    }
}

bool aggiungiIngredienteACarello (string _nomeIngrediente, double _prezzoIngrediente){      // aggiunge gli ingredienti mancanti nel carrello, controlla se si ha abbastanza budget, se si si procede con l'acquisto degli ingredienti mancanti
    //se le quantità non fossero tutte 1 avrei bisogno di un altro parametro per la quantità
    if (_prezzoIngrediente > budget){
        return false;
    }
    int i = ricercaCarrello(_nomeIngrediente);
    if (i == -1){
        i = primaPosizVuotaCarrello;
        primaPosizVuotaCarrello ++;
    }
    carrello[i].nomeIngrediente = _nomeIngrediente;
    carrello[i].quantitaMagazzino += quantitaIngrediente;
    carrello[i].prezzoIngrediente = _prezzoIngrediente;
    budget -= _prezzoIngrediente;
    bugdgetFinito();
    return true;
}

bool controlloQuantitaMagazzino (string _nomeIngrediente){  // controlla se ci sono abbastanza quantità per ogni ingrediente
    //se le quantità non fossero tutte 1 avrei bisogno di un altro parametro per la quantità
    bool magazzinoOk;
    int i = ricercaMagazzino(_nomeIngrediente);
    if (i == -1){
        magazzinoOk = false;
    }
    if (magazzino[i].quantitaMagazzino >= quantitaIngrediente){
        magazzinoOk = true;
    }
    if (magazzinoOk == false){
        magazzinoOk = aggiungiIngredienteACarello(_nomeIngrediente, magazzino[i].prezzoIngrediente);
    }
    return magazzinoOk;
}

void aggiungiIngredienteAMagazzino (string _nomeIngrediente, int _quantitaMagazzino, double _prezzoIngrediente){       // aggiunge dentro al magazzino gli ingredienti
    int i = ricercaMagazzino(_nomeIngrediente);
    if (i == -1){
        i = primaPosizVuotaMagazzino;
        primaPosizVuotaMagazzino ++;
    }
    magazzino[i].nomeIngrediente = _nomeIngrediente;
    magazzino[i].quantitaMagazzino += _quantitaMagazzino;
    magazzino[i].prezzoIngrediente = _prezzoIngrediente;
}
/*
void stampaMagazzino (){    // stampa il magazzino
    cout << "ingredienti presenti nel magazzino: " << endl;
    for (int i = 0; i < primaPosizVuotaMagazzino; i++){
        cout << magazzino[i].nomeIngrediente << "\t";
        cout << magazzino[i].quantitaMagazzino << "\t";
        cout << magazzino[i].prezzoIngrediente << endl;
    }
}
*/
void aggiungiPiattoALista(piatto _lista[], int i, piatto piattoInserimento){
    _lista[i] = piattoInserimento;
}
/*
void stampaListaPiatti (piatto listaStampa[]){  // stampa tutti i piatti
    for (int i = 0; i < 14; i++){
        cout << endl;
        cout << listaStampa[i].portata << "\n";
        cout << listaStampa[i].nomePiatto << "\n";
        for (int j = 0; j < 6; j ++){
            cout << listaStampa[i].ingredienti.nomeIngredienti[j] << "\t";
        }
        cout << endl;
        cout << listaStampa[i].allergeni.glutine << "\t";
        cout << listaStampa[i].allergeni.latte << "\t";
        cout << listaStampa[i].allergeni.molluschi << "\t";
        cout << listaStampa[i].allergeni.uova << "\t";
        cout << listaStampa[i].allergeni.pesce << "\t";
        cout << listaStampa[i].allergeni.arachidi << "\t";
        cout << listaStampa[i].allergeni.crostacei << "\n";
        cout << listaStampa[i].piattoVegano << "\t";
        cout << listaStampa[i].piattoVegetariano << "\t";
        cout << listaStampa[i].piattoReligioni << "\n\n";
    }
}
*/
void scriviMenuSettimana (menu _menuS[], string _nomeMenu, FILE* pFOut){    // inserimento dei piatti del menu della settimana dentro al file txt
    string piattoGiorno, giorno;
    fputc ('\n', pFOut);
    fputc ('\n', pFOut);
    fputs (_nomeMenu.c_str(), pFOut);
    fputc ('\n', pFOut);
    fputc ('\n', pFOut);
    for (int i = 0; i < 7; i++){
        giorno = to_string(i + 1);
        piattoGiorno = "piatti del giorno " + giorno;
        fputs (piattoGiorno.c_str(), pFOut);
        fputc ('\n', pFOut);
        for (int j = 0; j < 5; j++){
            fputs (_menuS[i].piatti[j].portata.c_str(), pFOut);
            fputc ('\t', pFOut);
            fputs ("nome piatto: ", pFOut);
            fputs (_menuS[i].piatti[j].nomePiatto.c_str(), pFOut);
            fputc ('\n', pFOut);
        }
    }
}

void richiamoStampaMenuSett (){     // richiama funzione per inserire il menu della settimana e i suoi menu alternativi dentro un file txt
    FILE* pFOut;
    pFOut = fopen("/Users/micheleukmar/testfile/menuSettimana.txt","w");
    scriviMenuSettimana(menuSettimana, "menù normale:", pFOut);
    scriviMenuSettimana(menuVegani, "menù per vegani:", pFOut);
    scriviMenuSettimana(menuVegetariani, "menù per vegetariani:", pFOut);
    scriviMenuSettimana(menuReligioni, "menù per problemi religiosi:", pFOut);
    scriviMenuSettimana(menuAllergeni, "menù per allergeni:", pFOut);
    fclose(pFOut);
    
}

bool checkIngredientiPiatto2Giorni (piatto piattoG1, piatto piattoG0){      // controllo degli ingredienti tra due giorni di fila per accertarsi che non ci siano ripetizioni
    for (int p1 = 0; p1 < 6; p1++){
        for (int p0 = 0; p0 < 6; p0++){
            if (piattoG1.ingredienti.nomeIngredienti[p1] == "pasta" || piattoG0.ingredienti.nomeIngredienti[p0] == "pasta"){
                continue;
            }
            if ((piattoG1.ingredienti.nomeIngredienti[p1] != "" && piattoG0.ingredienti.nomeIngredienti[p0] != "") && (piattoG1.ingredienti.nomeIngredienti[p1] == piattoG0.ingredienti.nomeIngredienti[p0])){
                cout << "è stato inserito un piatto che contiene degli ingredienti contenuti anche nel piatto del giorno precedente " << endl;
                return false;
            }
        }
    }
    return true;
}

bool allergieC  (piatto listaPiatti[], int sceltaPiatto){    // controllo tra allergeni nei piatti e allergeni scetli dall utente
    if ((menuGlutine == true && listaPiatti[sceltaPiatto].allergeni.glutine == 1) || (menuLatte == true && listaPiatti[sceltaPiatto].allergeni.latte == 1) || (menuMolluschi == true && listaPiatti[sceltaPiatto].allergeni.molluschi == 1) || (menuUova == true && listaPiatti[sceltaPiatto].allergeni.uova == 1) || (menuPesce == true && listaPiatti[sceltaPiatto].allergeni.pesce == 1) || (menuArachidi == true && listaPiatti[sceltaPiatto].allergeni.arachidi == 1) || (menuCrostacei == true && listaPiatti[sceltaPiatto].allergeni.crostacei == 1)){
        return false;
    }
    return true;
}

int scegliPiattoAlternativo (piatto listaPiatti[], int sceltaPiatto, int i, int nPiatto, int dimLista, bool allergia, bool vegano, bool vegetariano, bool religione, string scritta){       // chiede all utende in caso di particolari allergeni o se nel piatto sono presenti cose che non vanno bene per vegani, vegetariani o motivi religiosi un piatto alternativo da mettere nell apposito menu alternativo
    bool ingredientiOk = true;
    if ((allergieC(listaPiatti, sceltaPiatto) == false && allergia == true) || (listaPiatti[sceltaPiatto].piattoVegano == 0 && vegano == true) || (listaPiatti[sceltaPiatto].piattoVegetariano == 0 && vegetariano == true) || (listaPiatti[sceltaPiatto].piattoReligioni == 0 && religione == true)){
        do {
            do {
                sceltaPiatto = inserimentoInteri(scritta, 0, dimLista - 1, "è stato selezionato un piatto non adatto.");
            } while ((allergia == true && allergieC(listaPiatti, sceltaPiatto) == false && checkIngredientiPiatto2Giorni(listaPiatti[sceltaPiatto], menuAllergeni[i - 1].piatti[nPiatto])) || (vegano == true && listaPiatti[sceltaPiatto].piattoVegano == 0 && checkIngredientiPiatto2Giorni(listaPiatti[sceltaPiatto], menuVegani[i - 1].piatti[nPiatto])) || (vegetariano == true && listaPiatti[sceltaPiatto].piattoVegetariano == 0 && checkIngredientiPiatto2Giorni(listaPiatti[sceltaPiatto], menuVegetariani[i - 1].piatti[nPiatto])) || (religione == true && listaPiatti[sceltaPiatto].piattoReligioni == 0 && checkIngredientiPiatto2Giorni(listaPiatti[sceltaPiatto], menuReligioni[i - 1].piatti[nPiatto])));
            for (int z = 0; z < 6; z++){
                ingredientiOk = controlloQuantitaMagazzino(listaPiatti[sceltaPiatto].ingredienti.nomeIngredienti[z]);
            }
        }while (ingredientiOk == false);
    }
    return sceltaPiatto;
}

int scegliPiatto (piatto listaPiatti[],int nPiatto, int i, int dimLista){   // chiede all utente di scegliere tra la lista di piatti mostrata il piatto da inserire dentro al menu e richiama le funzioni necessarie per i vari controlli
    int sceltaPiatto;
    bool ingredientiOk = true;
    for (int j = 0; j < dimLista; j++){
        cout << j << " = " << listaPiatti[j].nomePiatto << "\n";
    }
    do {
        do {
            sceltaPiatto = inserimentoInteri("inserire il numero del piatto che si vuole scegliere \n", 0, dimLista - 1, "Numero non valido.");
            if (i == 0){
                break;
            }
        } while (checkIngredientiPiatto2Giorni(listaPiatti[sceltaPiatto], menuSettimana[i - 1].piatti[nPiatto]));
        for (int z = 0; z < 6; z++){
            ingredientiOk = controlloQuantitaMagazzino(listaPiatti[sceltaPiatto].ingredienti.nomeIngredienti[z]);
        }
    } while (ingredientiOk == false);
    return sceltaPiatto;
}

void sceltaAllergeni (){    // chiede all utente gli allergeni che si vogliono evitare e per cui generare un menu alternativo
    int sceltaAllergie, rifare;
    cout << "\n inserire possibili allergeni che si vogliono evitare" << endl;
    do {
        sceltaAllergie = inserimentoInteri("scegliere tra: \n 1 = allergia al glutine \n 2 = allergia al latte \n 3 = allergia ai molluschi \n 4 = allergia alle uova \n 5 = allergia al pesce \n 6 = allergia agli arachidi \n 7 = allergia ai crostacei \n 8 = nessun allergeno \n scelta: ", 1, 8, "Numero non valido.");
        switch (sceltaAllergie){
            case 1:
                menuGlutine = true;
                break;
            case 2:
                menuLatte = true;
                break;
            case 3:
                menuMolluschi = true;
                break;
            case 4:
                menuUova = true;
                break;
            case 5:
                menuPesce = true;
                break;
            case 6:
                menuArachidi = true;
                break;
            case 7:
                menuCrostacei = true;
                break;
        }
        if (sceltaAllergie == 8){
            break;
        }
        rifare = inserimentoInteri("premere 1 se si vuole inserire un altro allergeno, altrimenti premere un qualsiasi altro numero", 0, 9, "Numero non valido.");
    } while (rifare == 1);
}

void generaMenuSettimana (){    // richiama tutte le funzioni necessarie per far scegliere all'utente i piatti da inserire nel menu e nei menu alternativi per esigenze
    for (int i = 0; i < 7; i++){
        cout << "scegliere i piatti del giorno " << i + 1 << endl;
        int sceltaPiatto, sceltaPiattoSost;
        sceltaPiatto = scegliPiatto(listaAntipasti, 0, i, 14);
        menuSettimana[i].piatti[0] = listaAntipasti[sceltaPiatto];
        sceltaPiattoSost = scegliPiattoAlternativo(listaAntipasti, sceltaPiatto, i, 0, 14, true, false, false, false, "è stato inserito un piatto che contiene allergeni, scegliere un piatto alternativo");
        menuAllergeni[i].piatti[0] = listaAntipasti[sceltaPiattoSost];
        sceltaPiattoSost = scegliPiattoAlternativo(listaAntipasti, sceltaPiatto, i, 0, 14, false, true, false, false, "il piatto inserito contriene ingredienti che i vegani non possono mangiare, scegliere un piatto alternativo");
        menuVegani[i].piatti[0] = listaAntipasti[sceltaPiattoSost];
        sceltaPiattoSost = scegliPiattoAlternativo(listaAntipasti, sceltaPiatto, i, 0, 14, false, false, true, false, "il piatto inserito contriene ingredienti che i vegetariani non possono mangiare, scegliere un piatto alternativo");
        menuVegetariani[i].piatti[0] = listaAntipasti[sceltaPiattoSost];
        sceltaPiattoSost = scegliPiattoAlternativo(listaAntipasti, sceltaPiatto, i, 0, 14, false, false, false, true, "il piatto inserito contriene ingredienti che non si possono mangiare per motivi religiosi, scegliere un piatto alternativo");
        menuReligioni[i].piatti[0] = listaAntipasti[sceltaPiattoSost];
        
        sceltaPiatto = scegliPiatto(listaPrimi, 1, i, 14);
        menuSettimana[i].piatti[1] = listaPrimi[sceltaPiatto];
        sceltaPiattoSost = scegliPiattoAlternativo(listaPrimi, sceltaPiatto, i, 0, 14, true, false, false, false, "è stato inserito un piatto che contiene allergeni, scegliere un piatto alternativo");
        menuAllergeni[i].piatti[1] = listaPrimi[sceltaPiattoSost];
        sceltaPiattoSost = scegliPiattoAlternativo(listaPrimi, sceltaPiatto, i, 0, 14, false, true, false, false, "il piatto inserito contriene ingredienti che i vegani non possono mangiare, scegliere un piatto alternativo");
        menuVegani[i].piatti[1] = listaPrimi[sceltaPiattoSost];
        sceltaPiattoSost = scegliPiattoAlternativo(listaPrimi, sceltaPiatto, i, 0, 14, false, false, true, false, "il piatto inserito contriene ingredienti che i vegetariani non possono mangiare, scegliere un piatto alternativo");
        menuVegetariani[i].piatti[1] = listaPrimi[sceltaPiattoSost];
        sceltaPiattoSost = scegliPiattoAlternativo(listaPrimi, sceltaPiatto, i, 0, 14, false, false, false, true, "il piatto inserito contriene ingredienti che non si possono mangiare per motivi religiosi, scegliere un piatto alternativo");
        menuReligioni[i].piatti[1] = listaPrimi[sceltaPiattoSost];
        
        sceltaPiatto = scegliPiatto(listaSecondi, 2, i, 14);
        menuSettimana[i].piatti[2] = listaSecondi[sceltaPiatto];
        sceltaPiattoSost = scegliPiattoAlternativo(listaSecondi, sceltaPiatto, i, 0, 14, true, false, false, false, "è stato inserito un piatto che contiene allergeni, scegliere un piatto alternativo");
        menuAllergeni[i].piatti[2] = listaSecondi[sceltaPiattoSost];
        sceltaPiattoSost = scegliPiattoAlternativo(listaSecondi, sceltaPiatto, i, 0, 14, false, true, false, false, "il piatto inserito contriene ingredienti che i vegani non possono mangiare, scegliere un piatto alternativo");
        menuVegani[i].piatti[2] = listaSecondi[sceltaPiattoSost];
        sceltaPiattoSost = scegliPiattoAlternativo(listaSecondi, sceltaPiatto, i, 0, 14, false, false, true, false, "il piatto inserito contriene ingredienti che i vegetariani non possono mangiare, scegliere un piatto alternativo");
        menuVegetariani[i].piatti[2] = listaSecondi[sceltaPiattoSost];
        sceltaPiattoSost = scegliPiattoAlternativo(listaSecondi, sceltaPiatto, i, 0, 14, false, false, false, true, "il piatto inserito contriene ingredienti che non si possono mangiare per motivi religiosi, scegliere un piatto alternativo");
        menuReligioni[i].piatti[2] = listaSecondi[sceltaPiattoSost];
        
        sceltaPiatto = scegliPiatto(listaContorni, 3, i, 5);
        menuSettimana[i].piatti[3] = listaContorni[sceltaPiatto];
        sceltaPiattoSost = scegliPiattoAlternativo(listaContorni, sceltaPiatto, i, 0, 5, true, false, false, false, "è stato inserito un piatto che contiene allergeni, scegliere un piatto alternativo");
        menuAllergeni[i].piatti[3] = listaContorni[sceltaPiattoSost];
        sceltaPiattoSost = scegliPiattoAlternativo(listaContorni, sceltaPiatto, i, 0, 5, false, true, false, false, "il piatto inserito contriene ingredienti che i vegani non possono mangiare, scegliere un piatto alternativo");
        menuVegani[i].piatti[3] = listaContorni[sceltaPiattoSost];
        sceltaPiattoSost = scegliPiattoAlternativo(listaContorni, sceltaPiatto, i, 0, 5, false, false, true, false, "il piatto inserito contriene ingredienti che i vegetariani non possono mangiare, scegliere un piatto alternativo");
        menuVegetariani[i].piatti[3] = listaContorni[sceltaPiattoSost];
        sceltaPiattoSost = scegliPiattoAlternativo(listaContorni, sceltaPiatto, i, 0, 5, false, false, false, true, "il piatto inserito contriene ingredienti che non si possono mangiare per motivi religiosi, scegliere un piatto alternativo");
        menuReligioni[i].piatti[3] = listaContorni[sceltaPiattoSost];
        
        sceltaPiatto = scegliPiatto(listaDolci, 4, i, 14);
        menuSettimana[i].piatti[4] = listaDolci[sceltaPiatto];
        sceltaPiattoSost = scegliPiattoAlternativo(listaDolci, sceltaPiatto, i, 0, 14, true, false, false, false, "è stato inserito un piatto che contiene allergeni, scegliere un piatto alternativo");
        menuAllergeni[i].piatti[4] = listaDolci[sceltaPiattoSost];
        sceltaPiattoSost = scegliPiattoAlternativo(listaDolci, sceltaPiatto, i, 0, 14, false, true, false, false, "il piatto inserito contriene ingredienti che i vegani non possono mangiare, scegliere un piatto alternativo");
        menuVegani[i].piatti[4] = listaDolci[sceltaPiattoSost];
        sceltaPiattoSost = scegliPiattoAlternativo(listaDolci, sceltaPiatto, i, 0, 14, false, false, true, false, "il piatto inserito contriene ingredienti che i vegetariani non possono mangiare, scegliere un piatto alternativo");
        menuVegetariani[i].piatti[4] = listaDolci[sceltaPiattoSost];
        sceltaPiattoSost = scegliPiattoAlternativo(listaDolci, sceltaPiatto, i, 0, 14, false, false, false, true, "il piatto inserito contriene ingredienti che non si possono mangiare per motivi religiosi, scegliere un piatto alternativo");
        menuReligioni[i].piatti[4] = listaDolci[sceltaPiattoSost];
    }
}

void randomMenuAlternativi (piatto listaPiatti[],int nPiatto, int i, int dimLista, int sceltaPiatto, menu menuAlternativo[], bool allergia, bool vegano, bool vegetariano, bool religione){     // controllo di allergeni, vegani, vegetariani e religioni per generare i menu alternativi randomici
    bool ingredientiOk = true;
    if ((allergieC(listaPiatti, sceltaPiatto) == false && allergia == true) || (listaPiatti[sceltaPiatto].piattoVegano == 0 && vegano == true) || (listaPiatti[sceltaPiatto].piattoVegetariano == 0 && vegetariano == true) || (listaPiatti[sceltaPiatto].piattoReligioni == 0 && religione == true)){
        do {
            do {
                sceltaPiatto = rand () % dimLista;
            } while ((allergia == true && allergieC(listaPiatti, sceltaPiatto) == false && checkIngredientiPiatto2Giorni(listaPiatti[sceltaPiatto], menuAllergeni[i - 1].piatti[nPiatto])) || (vegano == true && listaPiatti[sceltaPiatto].piattoVegano == 0 && checkIngredientiPiatto2Giorni(listaPiatti[sceltaPiatto], menuVegani[i - 1].piatti[nPiatto])) || (vegetariano == true && listaPiatti[sceltaPiatto].piattoVegetariano == 0 && checkIngredientiPiatto2Giorni(listaPiatti[sceltaPiatto], menuVegetariani[i - 1].piatti[nPiatto])) || (religione == true && listaPiatti[sceltaPiatto].piattoReligioni == 0 && checkIngredientiPiatto2Giorni(listaPiatti[sceltaPiatto], menuReligioni[i - 1].piatti[nPiatto])));
            for (int z = 0; z < 6; z++){
                ingredientiOk = controlloQuantitaMagazzino(listaPiatti[sceltaPiatto].ingredienti.nomeIngredienti[z]);
            }
        } while (ingredientiOk == false);
    }
    menuAlternativo[i].piatti[nPiatto] = listaPiatti[sceltaPiatto];
}

void piattoRandom (piatto listaPiatti[],int nPiatto, int i, int dimLista){  // crea il piatto base randomicamente e richiama le funzioni per gli appositi controlli
    int sceltaPiatto;
    bool ingredientiOk = true;
    do {
        do {
            sceltaPiatto = rand () % dimLista;
        }while (checkIngredientiPiatto2Giorni (listaPiatti[sceltaPiatto], menuSettimana[i - 1].piatti[nPiatto]) == false);
        for (int z = 0; z < 6; z++){
            ingredientiOk = controlloQuantitaMagazzino(listaPiatti[sceltaPiatto].ingredienti.nomeIngredienti[z]);
        }
    } while (ingredientiOk == false);
    menuSettimana[i].piatti[nPiatto] = listaPiatti[sceltaPiatto];
    randomMenuAlternativi(listaPiatti, nPiatto, i, dimLista, sceltaPiatto, menuAllergeni, true, false, false, false);
    randomMenuAlternativi(listaPiatti, nPiatto, i, dimLista, sceltaPiatto, menuVegani, false, true, false, false);
    randomMenuAlternativi(listaPiatti, nPiatto, i, dimLista, sceltaPiatto, menuVegetariani, false, false, true, false);
    randomMenuAlternativi(listaPiatti, nPiatto, i, dimLista, sceltaPiatto, menuReligioni, false, false, false, true);
}

void generaMenuSettRandom (){   // richiama il generamento random per creare tutti i piatti in maniera randomica
    for (int i = 0; i < 7; i++){
        piattoRandom(listaAntipasti, 0, i, 14);
        piattoRandom(listaPrimi, 1, i, 14);
        piattoRandom(listaSecondi, 2, i, 14);
        piattoRandom(listaContorni, 3, i, 5);
        piattoRandom(listaDolci, 4, i, 14);
    }
}


piatto creaPiatto (string _portata, string _nomePiatto, ingredienti _ingredienti, allergeni _allergeni, int _piattoVegano, int _piattoVegetariano, int _piattoReligioni){    // serve a togliere gli spazi negli ingredienti vuoti per non creare problemi con il controllo ingredienti
    piatto inserisciPiatto;
    inserisciPiatto.portata = _portata;
    inserisciPiatto.nomePiatto = _nomePiatto;
    inserisciPiatto.ingredienti = _ingredienti;
    for (int i = 0; i < 6; i++){
        if (inserisciPiatto.ingredienti.nomeIngredienti[i] == " "){
            inserisciPiatto.ingredienti.nomeIngredienti[i] = "";
        }
    }
    inserisciPiatto.allergeni = _allergeni;
    inserisciPiatto.piattoVegano = _piattoVegano;
    inserisciPiatto.piattoVegetariano = _piattoVegetariano;
    inserisciPiatto.piattoReligioni = _piattoReligioni;
    
    return inserisciPiatto;
}

bool leggiFileA(int j, piatto _lista[]){    // legge tutti i file txt delle liste dei piatti e li mette megli appositi struct chiamati listaPiatto
    char riga [200];
    FILE* pFIn;
    int i = 0;
    switch (j){
    case 0:
        pFIn = fopen("/Users/micheleukmar/testfile/antipasti.txt","r");
        break;
    case 1:
        pFIn = fopen("/Users/micheleukmar/testfile/primi.txt","r");
        break;
    case 2:
        pFIn = fopen("/Users/micheleukmar/testfile/secondi.txt","r");
        break;
    case 3:
        pFIn = fopen("/Users/micheleukmar/testfile/contorni.txt","r");
        break;
    case 4:
        pFIn = fopen("/Users/micheleukmar/testfile/dolci.txt","r");
        break;
        default:
            pFIn = NULL;
    }
    if(pFIn != NULL){
        while(fgets(riga,200,pFIn) != NULL){
            aggiungiPiattoALista(_lista,i,
                                 creaPiatto(strtok(riga,","),strtok(NULL,","), {strtok(NULL,","),strtok(NULL,","),strtok(NULL,","),strtok(NULL,","),strtok(NULL,","),strtok(NULL,",")}, {stoi((strtok(NULL,","))),stoi((strtok(NULL,","))),stoi((strtok(NULL,","))),stoi((strtok(NULL,","))),stoi((strtok(NULL,","))),stoi((strtok(NULL,","))),stoi((strtok(NULL,",")))}, stoi((strtok(NULL,","))),stoi((strtok(NULL,","))),stoi((strtok(NULL,",")))));
            i++;
        }
    }
     fclose(pFIn);
     return true;
}

bool letturaMagazzino(){    // legge il file txt del magazzino e aggiunge dentro lo struct magazzino tutti gi ingredienti presenti nel file
    char riga[100];
    FILE* pFIn;
    
    pFIn = fopen("/Users/micheleukmar/testfile/magazzino.txt","r");
    
    if (pFIn != NULL){
        while(fgets(riga,100,pFIn) != NULL){
            aggiungiIngredienteAMagazzino(strtok(riga,","),stoi(strtok(NULL,",")),stod(strtok(NULL,",")));
        }
    }
    fclose(pFIn);
    return true;
}

int main (){    // scegli se creare il menu random o con inserimento e richiamo di tutte le funzioni iniziali
    int sceltaRifare, sceltaMenu;
    cout << "benvenuti da ScamPizza la mensa migliore di napoli \n";
    do {
        sceltaMenu = inserimentoInteri("premere 1 per generare il menù random oppure premere 2 per scegliere i piatti da inserire", 1, 2, "Numero non valido.");
        leggiFileA(0, listaAntipasti);
        leggiFileA(1, listaPrimi);
        leggiFileA(2, listaSecondi);
        leggiFileA(3, listaContorni);
        leggiFileA(4, listaDolci);
        //stampaListaPiatti(listaAntipasti);
        //stampaListaPiatti(listaPrimi);
        //stampaListaPiatti(listaSecondi);
        //stampaListaPiatti(listaContorni);
        //stampaListaPiatti(listaDolci);
        letturaMagazzino();
        //stampaMagazzino();
        sceltaAllergeni();
        switch (sceltaMenu){
            case 1:
                generaMenuSettRandom();
                break;
            case 2:
                generaMenuSettimana();
                break;
        }
        stampaCarrello();
        cout << "\n\n\n ecco il menù settimanale" << endl;
        richiamoStampaMenuSett();
        sleep(1);
        string command = "open /Users/micheleukmar/testfile/menuSettimana.txt";
        system(command.c_str());
        sleep(2);
        string html = "open /Users/micheleukmar/testfile/forseFunziona/ristornate.html";
        system(html.c_str());
        sceltaRifare = inserimentoInteri("premere 1 per generare un altro menu oppure 2 per uscire dal programma", 1, 2, "Numero non valido.");
    } while (sceltaRifare == 1);
 return 0;
}
